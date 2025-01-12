#include "../main.hpp"

void load_libsysboard() {
	Glib::Dispatcher* dispatcher_callback = new Glib::Dispatcher();

	dispatcher_callback->connect([&]() {
		sysboard_window = sysboard_create(config_sysboard);
	});

	std::thread([&, dispatcher_callback]() {
		std::cout << "Loading: libsysboard.so" << std::endl;
		void* handle = dlopen("libsysboard.so", RTLD_LAZY);
		if (!handle) {
			std::cerr << "Cannot open library: " << dlerror() << '\n';
			return;
		}

		sysboard_create = (sysboard_create_func)dlsym(handle, "sysboard_create");
		sysboard_signal = (sysboard_signal_func)dlsym(handle, "sysboard_signal");

		const char* dlsym_error = dlerror();
		if (dlsym_error) {
			std::cerr << "Cannot load symbols: " << dlsym_error << '\n';
			dlclose(handle);
			return;
		}

		config_sysboard = load_config("board");
		dispatcher_callback->emit();
	}).detach();
}
