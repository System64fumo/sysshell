#include "main.hpp"

#include <gtk4-layer-shell.h>
#include <gtkmm/application.h>
#include <filesystem>

void handle_signal(int signum) {
	// TODO: Prevent sysmenu from working when syslock is locked
	if (signum == 36)
		sysbar_signal(sysbar_window, 10);
	else if (signum == 37)
		sysbar_signal(sysbar_window, 12);
	else if (signum == 38)
		sysbar_signal(sysbar_window, 34);
	else if (signum == 10 || signum == 12 || signum == 34)
		sysmenu_signal(sysmenu_window, signum);
	else if (signum == 35)
		syslock_lock(syslock_window);
	else if (signum == 39) {
		// TODO: Show other windows
		// TODO: Only show if another instance is not already running
		syspower_window = syspower_create(cfg_power);
	}
	else if (signum == 40) {
		sysboard_signal(sysboard_window, 10);
	}
	else if (signum == 41) {
		sysboard_signal(sysboard_window, 12);
	}
	else if (signum == 42) {
		sysboard_signal(sysboard_window, 34);
	}
}

int main() {
	auto app = Gtk::Application::create("funky.sys64.sysshell");
	app->hold();

	// This is required for linking to work properly
	bool supported = gtk_layer_is_supported();
	if (!supported) {
		std::cerr << "I've got a sneaking suspision that your compositor doesn't support gtk layer shell.." << std::endl;
		return 1;
	}

	// Parse the config
	std::string config_path;
	if (std::filesystem::exists(std::string(getenv("HOME")) + "/.config/sys64/shell/config.conf"))
		config_path = std::string(getenv("HOME")) + "/.config/sys64/shell/config.conf";
	else if (std::filesystem::exists("/usr/share/sys64/shell/config.conf"))
		config_path = "/usr/share/sys64/shell/config.conf";
	else
		config_path = "/usr/local/share/sys64/shell/config.conf";
	
	config_parser config(config_path);

	std::string libraries = config.get_value("main", "load");
	if (libraries != "empty")
		cfg_shell.load = libraries;

	// Load libraries
	std::istringstream iss(cfg_shell.load);
	std::string library;
	while (std::getline(iss, library, ',')) {
		if (library == "bar")
			load_libsysbar();
		else if (library == "board")
			load_libsysboard();
		else if (library == "hud")
			load_libsyshud();
		else if (library == "lock")
			load_libsyslock();
		else if (library == "menu")
			load_libsysmenu();
		else if (library == "power")
			load_libsyspower();
		else {
			std::fprintf(stderr, "Cannot load \"%s\"\n", library.c_str());
		}
	}

	// Catch signals
	// TODO: Add a config to assign custom signals to each action
	signal(SIGRTMIN+2, handle_signal);	// sysbar: show
	signal(SIGRTMIN+3, handle_signal);	// sysbar: hide
	signal(SIGRTMIN+4, handle_signal);	// sysbar: toggle

	signal(SIGRTMIN+6, handle_signal);	// sysboard: show
	signal(SIGRTMIN+7, handle_signal);	// sysboard: hide
	signal(SIGRTMIN+8, handle_signal);	// sysboard: toggle

	signal(SIGUSR1, handle_signal);		// sysmenu: show
	signal(SIGUSR2, handle_signal);		// sysmenu: hide
	signal(SIGRTMIN, handle_signal);	// sysmenu: toggle

	signal(SIGRTMIN+1, handle_signal);	// syslock: lock

	signal(SIGRTMIN+5, handle_signal);	// syspower: show

	return app->run();
}
