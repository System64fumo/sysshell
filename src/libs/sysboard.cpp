#include "../main.hpp"

void load_libsysboard() {
	void* handle = dlopen("libsysboard.so", RTLD_LAZY);
	if (!handle) {
		std::cerr << "Cannot open library: " << dlerror() << '\n';
		return;
	}

	sysboard_create = (sysboard_create_func)dlsym(handle, "sysboard_create");
	sysboard_signal = (sysboard_signal_func)dlsym(handle, "sysboard_signal");

	const char* dlsym_error = dlerror();
	if (dlsym_error) {
		std::cerr << "Cannot load symbols: " << dlsym_error << '\n';
		dlclose(handle);
		return;
	}

	std::cout << "Loading: libsysboard.so" << std::endl;

	config_board cfg;
	config_parser config(std::string(getenv("HOME")) + "/.config/sys64/board/config.conf");

	std::string cfg_margin = config.get_value("main", "margin");
	if (cfg_margin != "empty")
		cfg.margin = std::stoi(cfg_margin);

	std::string cfg_height_multiplier = config.get_value("main", "height-multiplier");
	if (cfg_height_multiplier != "empty")
		cfg.height_multiplier = std::stod(cfg_height_multiplier);

	std::string cfg_layout = config.get_value("main", "layout");
	if (cfg_layout != "empty")
		cfg.layout = cfg_layout;

	sysboard_window = sysboard_create(cfg);
}
