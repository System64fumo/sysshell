#include "../main.hpp"
#include <filesystem>

void load_libsyshud() {
	Glib::Dispatcher* dispatcher_callback = new Glib::Dispatcher();

	dispatcher_callback->connect([&]() {
		syshud_window = syshud_create(config_syshud);
	});

	std::thread([&, dispatcher_callback]() {
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

		config_syshud = load_config("hud");
		dispatcher_callback->emit();
	}).detach();
}
