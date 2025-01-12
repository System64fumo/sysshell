#include "../main.hpp"
#include <filesystem>

void load_libsysbar() {
	Glib::Dispatcher* dispatcher_callback = new Glib::Dispatcher();

	dispatcher_callback->connect([&]() {
		sysbar_window = sysbar_create(config_sysbar);
	});

	std::thread([&, dispatcher_callback]() {
		std::cout << "Loading: libsysbar.so" << std::endl;

		void* handle = dlopen("libsysbar.so", RTLD_LAZY);
		if (!handle) {
			std::cerr << "Cannot open library: " << dlerror() << '\n';
			return;
		}

		sysbar_create = (sysbar_create_func)dlsym(handle, "sysbar_create");
		sysbar_signal = (sysbar_signal_func)dlsym(handle, "sysbar_signal");

		const char* dlsym_error = dlerror();
		if (dlsym_error) {
			std::cerr << "Cannot load symbols: " << dlsym_error << '\n';
			dlclose(handle);
			return;
		}

		config_sysbar = load_config("bar");
		dispatcher_callback->emit();
	}).detach();
}
