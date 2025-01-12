#include "../main.hpp"

void load_libsyspower() {
	std::printf("Loading: libsyspower.so\n");
	void* handle = dlopen("libsyspower.so", RTLD_LAZY);
	if (!handle) {
		std::fprintf(stderr, "Cannot open library: %s\n", dlerror());
		return;
	}

	syspower_create = (syspower_create_func)dlsym(handle, "syspower_create");

	const char* dlsym_error = dlerror();
	if (dlsym_error) {
		std::fprintf(stderr, "Cannot load symbols: %s\n", dlsym_error);
		dlclose(handle);
		return;
	}
}
