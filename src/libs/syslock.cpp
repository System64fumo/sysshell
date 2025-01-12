#include "../main.hpp"

void load_libsyslock() {
	Glib::Dispatcher* dispatcher_callback = new Glib::Dispatcher();

	dispatcher_callback->connect([&]() {
		syslock_window = syslock_create(config_syslock);
	});

	std::thread([&, dispatcher_callback]() {
		std::printf("Loading: libsyslock.so\n");
		void* handle = dlopen("libsyslock.so", RTLD_LAZY);
		if (!handle) {
			std::fprintf(stderr, "Cannot open library: %s\n", dlerror());
			return;
		}

		syslock_create = (syslock_create_func)dlsym(handle, "syslock_create");
		syslock_lock = (syslock_lock_func)dlsym(handle, "syslock_lock");

		const char* dlsym_error = dlerror();
		if (dlsym_error) {
			std::fprintf(stderr, "Cannot load symbols: %s\n", dlsym_error);
			dlclose(handle);
			return;
		}

		config_syslock = load_config("lock");
		dispatcher_callback->emit();
	}).detach();
}
