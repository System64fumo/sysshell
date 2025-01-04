#include "../main.hpp"
#include <filesystem>

void load_libsysbar() {
	std::cout << "Loading: libsysbar.so" << std::endl;

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

	sysbar_window = sysbar_create(load_config("bar"));
}
