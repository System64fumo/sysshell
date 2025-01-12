#include "../main.hpp"

void load_libsysmenu() {
	Glib::Dispatcher* dispatcher_callback = new Glib::Dispatcher();

	dispatcher_callback->connect([&]() {
		sysmenu_window = sysmenu_create(config_sysmenu);
	});

	std::thread([&, dispatcher_callback]() {
		std::printf("Loading: libsysmenu.so\n");
		void* handle = dlopen("libsysmenu.so", RTLD_LAZY);
		if (!handle) {
			std::fprintf(stderr, "Cannot open library: %s\n", dlerror());
			return;
		}

		sysmenu_create = (sysmenu_create_func)dlsym(handle, "sysmenu_create");
		sysmenu_signal = (sysmenu_signal_func)dlsym(handle, "sysmenu_signal");

		const char* dlsym_error = dlerror();
		if (dlsym_error) {
			std::fprintf(stderr, "Cannot load symbols: %s\n", dlsym_error);
			dlclose(handle);
			return;
		}

		config_sysmenu = load_config("menu");
		dispatcher_callback->emit();
	}).detach();
}
