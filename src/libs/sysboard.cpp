#include "../main.hpp"

void load_libsysboard() {
	Glib::Dispatcher* dispatcher_callback = new Glib::Dispatcher();

	dispatcher_callback->connect([&]() {
		sysboard_window = sysboard_create(config_sysboard);
	});

	std::thread([&, dispatcher_callback]() {
		std::printf("Loading: libsysboard.so\n");
		void* handle = dlopen("libsysboard.so", RTLD_LAZY);
		if (!handle) {
			std::fprintf(stderr, "Cannot open library: %s\n", dlerror());
			return;
		}

		sysboard_create = (sysboard_create_func)dlsym(handle, "sysboard_create");
		sysboard_signal = (sysboard_signal_func)dlsym(handle, "sysboard_signal");

		const char* dlsym_error = dlerror();
		if (dlsym_error) {
			std::fprintf(stderr, "Cannot load symbols: %s\n", dlsym_error);
			dlclose(handle);
			return;
		}

		config_sysboard = load_config("board");
		dispatcher_callback->emit();
	}).detach();
}
