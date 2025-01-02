#include "../main.hpp"
#include <filesystem>

void load_libsysmenu() {
	void* handle = dlopen("libsysmenu.so", RTLD_LAZY);
	if (!handle) {
		std::cerr << "Cannot open library: " << dlerror() << '\n';
		return;
	}

	sysmenu_create = (sysmenu_create_func)dlsym(handle, "sysmenu_create");
	sysmenu_signal = (sysmenu_signal_func)dlsym(handle, "sysmenu_signal");

	const char* dlsym_error = dlerror();
	if (dlsym_error) {
		std::cerr << "Cannot load symbols: " << dlsym_error << '\n';
		dlclose(handle);
		return;
	}

	std::cout << "Loading: libsysmenu.so" << std::endl;

	std::string config_path;
	std::map<std::string, std::map<std::string, std::string>> config;
	std::map<std::string, std::map<std::string, std::string>> config_usr;

	bool cfg_sys = std::filesystem::exists("/usr/share/sys64/menu/config.conf");
	bool cfg_sys_local = std::filesystem::exists("/usr/local/share/sys64/menu/config.conf");
	bool cfg_usr = std::filesystem::exists(std::string(getenv("HOME")) + "/.config/sys64/menu/config.conf");

	// Load default config
	if (cfg_sys)
		config_path = "/usr/share/sys64/menu/config.conf";
	else if (cfg_sys_local)
		config_path = "/usr/local/share/sys64/menu/config.conf";
	else
		std::fprintf(stderr, "No default config found, Things will get funky!\n");

	config = config_parser(config_path).data;

	// Load user config
	if (cfg_usr)
		config_path = std::string(getenv("HOME")) + "/.config/sys64/menu/config.conf";
	else
		std::fprintf(stderr, "No user config found\n");

	config_usr = config_parser(config_path).data;

	// Merge configs
	for (const auto& [key, nested_map] : config_usr)
		config[key] = nested_map;

	// Sanity check
	if (!(cfg_sys || cfg_sys_local || cfg_usr)) {
		std::fprintf(stderr, "No config available, Something ain't right here.");
		return;
	}

	sysmenu_window = sysmenu_create(config);
}
