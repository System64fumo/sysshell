#include "../main.hpp"

void load_libsyspower() {
	std::cout << "Loading: libsyspower.so" << std::endl;
	void* handle = dlopen("libsyspower.so", RTLD_LAZY);
	if (!handle) {
		std::cerr << "Cannot open library: " << dlerror() << '\n';
		return;
	}

	syspower_create = (syspower_create_func)dlsym(handle, "syspower_create");

	const char* dlsym_error = dlerror();
	if (dlsym_error) {
		std::cerr << "Cannot load symbols: " << dlsym_error << '\n';
		dlclose(handle);
		return;
	}

	config_parser config(std::string(getenv("HOME")) + "/.config/sys64/power/config.conf");

	std::string cfg_position = config.get_value("main", "position");
	if (cfg_position != "empty")
		cfg_power.position = std::stoi(cfg_position);

	std::string cfg_monitor =  config.get_value("main", "monitor");
	if (cfg_monitor != "empty")
		cfg_power.main_monitor = std::stoi(cfg_monitor);

	std::string cfg_transition = config.get_value("main", "transition-duration");
	if (cfg_transition != "empty")
		cfg_power.transition_duration = std::stoi(cfg_transition);
}
