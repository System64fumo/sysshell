#include "../main.hpp"

void load_libsysboard() {
	std::cout << "Loading: libsysboard.so" << std::endl;
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

	sysboard_window = sysboard_create(load_config("board"));
}
