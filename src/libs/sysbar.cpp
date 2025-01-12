#include "../main.hpp"

void load_libsysbar() {
	Glib::Dispatcher* dispatcher_callback = new Glib::Dispatcher();

	dispatcher_callback->connect([&]() {
		sysbar_window = sysbar_create(config_sysbar);
	});

	std::thread([&, dispatcher_callback]() {
		std::printf("Loading: libsysbar.so");

		void* handle = dlopen("libsysbar.so", RTLD_LAZY);
		if (!handle) {
			std::fprintf(stderr, "Cannot open library: %s\n", dlerror());
			return;
		}

		sysbar_create = (sysbar_create_func)dlsym(handle, "sysbar_create");
		sysbar_signal = (sysbar_signal_func)dlsym(handle, "sysbar_signal");

		const char* dlsym_error = dlerror();
		if (dlsym_error) {
			std::fprintf(stderr, "Cannot load symbols: %s\n", dlsym_error);
			dlclose(handle);
			return;
		}

		config_sysbar = load_config("bar");
		dispatcher_callback->emit();
	}).detach();
}
