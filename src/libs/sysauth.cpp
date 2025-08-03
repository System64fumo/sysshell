#include "../main.hpp"

void load_libsysauth() {
	std::printf("Loading: libsysauth.so\n");
	void* handle = dlopen("libsysauth.so", RTLD_LAZY);
	if (!handle) {
		std::fprintf(stderr, "Cannot open library: %s\n", dlerror());
		return;
	}

	sysauth_create = (sysauth_create_func)dlsym(handle, "sysauth_create");

	const char* dlsym_error = dlerror();
	if (dlsym_error) {
		std::fprintf(stderr, "Cannot load symbols: %s\n", dlsym_error);
		dlclose(handle);
		return;
	}

	config_sysauth = load_config("auth");
	sysauth_window = sysauth_create(config_sysauth);
}
