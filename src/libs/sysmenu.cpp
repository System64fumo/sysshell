#include "../main.hpp"
#include <filesystem>

void load_libsysmenu() {
	Glib::Dispatcher* dispatcher_callback = new Glib::Dispatcher();

	dispatcher_callback->connect([&]() {
		sysmenu_window = sysmenu_create(config_sysmenu);
	});

	std::thread([&, dispatcher_callback]() {
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

		config_sysmenu = load_config("menu");
		dispatcher_callback->emit();
	}).detach();
}
