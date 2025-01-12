#include "../main.hpp"

void load_libsyshud() {
	Glib::Dispatcher* dispatcher_callback = new Glib::Dispatcher();

	dispatcher_callback->connect([&]() {
		syshud_window = syshud_create(config_syshud);
	});

	std::thread([&, dispatcher_callback]() {
		std::printf("Loading: libsyshud.so\n");
		void* handle = dlopen("libsyshud.so", RTLD_LAZY);
		if (!handle) {
			std::fprintf(stderr, "Cannot open library: %s\n", dlerror());
			return;
		}

		syshud_create = (syshud_create_func)dlsym(handle, "syshud_create");

		const char* dlsym_error = dlerror();
		if (dlsym_error) {
			std::fprintf(stderr, "Cannot load symbols: %s\n", dlsym_error);
			dlclose(handle);
			return;
		}

		config_syshud = load_config("hud");
		dispatcher_callback->emit();
	}).detach();
}
