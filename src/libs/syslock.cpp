#include "../main.hpp"
#include <filesystem>

void load_libsyslock() {
	Glib::Dispatcher* dispatcher_callback = new Glib::Dispatcher();

	dispatcher_callback->connect([&]() {
		syslock_window = syslock_create(config_syslock);
	});

	std::thread([&, dispatcher_callback]() {
		std::cout << "Loading: libsyslock.so" << std::endl;
		void* handle = dlopen("libsyslock.so", RTLD_LAZY);
		if (!handle) {
			std::cerr << "Cannot open library: " << dlerror() << '\n';
			return;
		}

		syslock_create = (syslock_create_func)dlsym(handle, "syslock_create");
		syslock_lock = (syslock_lock_func)dlsym(handle, "syslock_lock");

		const char* dlsym_error = dlerror();
		if (dlsym_error) {
			std::cerr << "Cannot load symbols: " << dlsym_error << '\n';
			dlclose(handle);
			return;
		}

		config_syslock = load_config("lock");
		dispatcher_callback->emit();
	}).detach();
}
