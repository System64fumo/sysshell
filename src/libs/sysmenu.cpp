#include "../main.hpp"
#include <filesystem>

void load_libsysmenu() {
	std::cout << "Loading: libsysmenu.so" << std::endl;
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

	sysmenu_window = sysmenu_create(load_config("menu"));
}
