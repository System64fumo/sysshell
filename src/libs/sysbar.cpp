#include "../main.hpp"

void load_libsysbar() {
	void* handle = dlopen("libsysbar.so", RTLD_LAZY);
	if (!handle) {
		std::cerr << "Cannot open library: " << dlerror() << '\n';
		return;
	}

	sysbar_create = (sysbar_create_func)dlsym(handle, "sysbar_create");
	sysbar_signal = (sysbar_signal_func)dlsym(handle, "sysbar_signal");

	const char* dlsym_error = dlerror();
	if (dlsym_error) {
		std::cerr << "Cannot load symbols: " << dlsym_error << '\n';
		dlclose(handle);
		return;
	}

	std::cout << "Loading: libsysbar.so" << std::endl;

	config_bar cfg;
	config_parser config(std::string(getenv("HOME")) + "/.config/sys64/bar/config.conf");

	std::string position = config.get_value("main", "position");
	if (position != "empty")
		cfg.position = std::stoi(position);

	std::string size = config.get_value("main", "size");
	if (size != "empty")
		cfg.size = std::stoi(size);

	std::string verbose = config.get_value("main", "verbose");
	if (verbose == "true")
		cfg.verbose = true;

	std::string cfg_main_monitor = config.get_value("main", "main-monitor");
	if (cfg_main_monitor != "empty")
		cfg.main_monitor = std::stoi(cfg_main_monitor);

	std::string m_start = config.get_value("main", "m_start");
	if (m_start != "empty")
		cfg.m_start = m_start;

	std::string m_center = config.get_value("main", "m_center");
	if (m_center != "empty")
		cfg.m_center = m_center;

	std::string m_end = config.get_value("main", "m_end");
	if (m_end != "empty")
		cfg.m_end = m_end;

	sysbar_window = sysbar_create(cfg);
}
