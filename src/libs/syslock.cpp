#include "../main.hpp"

void load_libsyslock() {
	void* handle = dlopen("libsyslock.so", RTLD_LAZY);
	if (!handle) {
		std::cerr << "Cannot open library: " << dlerror() << '\n';
		return;
	}

	syslock_create = (syslock_create_func)dlsym(handle, "syslock_create");
	syslock_lock = (syslock_lock_func)dlsym(handle, "syslock_lock");

	const char* dlsym_error = dlerror();
	if (dlsym_error) {
		std::cerr << "Cannot load symbols: " << dlsym_error << '\n';
		dlclose(handle);
		return;
	}

	std::cout << "Loading: libsyslock.so" << std::endl;

	config_lock cfg;
	config_parser config(std::string(getenv("HOME")) + "/.config/sys64/lock/config.conf");

	std::string cfg_start_unlocked = config.get_value("main", "start-unlocked");
	cfg.start_unlocked = (cfg_start_unlocked == "true");

	std::string cfg_keypad = config.get_value("main", "keypad");
	cfg.keypad_enabled = (cfg_keypad == "true");

	std::string cfg_pw_length = config.get_value("main", "password-length");
	if (cfg_pw_length != "empty")
		cfg.pw_length = std::stoi(cfg_pw_length);

	std::string cfg_main_monitor = config.get_value("main", "main-monitor");
	if (cfg_main_monitor != "empty")
		cfg.main_monitor = std::stoi(cfg_main_monitor);

	syslock_window = syslock_create(cfg);
}
