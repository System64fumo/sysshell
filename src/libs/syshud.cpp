#include "../main.hpp"
#include <filesystem>

void load_libsyshud() {
	std::cout << "Loading: libsyshud.so" << std::endl;
	void* handle = dlopen("libsyshud.so", RTLD_LAZY);
	if (!handle) {
		std::cerr << "Cannot open library: " << dlerror() << '\n';
		return;
	}

	syshud_create = (syshud_create_func)dlsym(handle, "syshud_create");

	const char* dlsym_error = dlerror();
	if (dlsym_error) {
		std::cerr << "Cannot load symbols: " << dlsym_error << '\n';
		dlclose(handle);
		return;
	}

	syshud_window = syshud_create(load_config("hud"));
}
