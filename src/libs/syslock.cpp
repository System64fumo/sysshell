#include "../main.hpp"
#include <filesystem>

void load_libsyslock() {
	std::cout << "Loading: libsyslock.so" << std::endl;
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

	syslock_window = syslock_create(load_config("lock"));
}
