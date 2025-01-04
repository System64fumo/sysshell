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
}
