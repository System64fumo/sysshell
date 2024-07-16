#include "config_parser.hpp"

#include <libsysbar.hpp>
#include <libsyshud.hpp>
#include <libsysmenu.hpp>

#include <gtkmm/application.h>
#include <iostream>
#include <dlfcn.h>

sysmenu *sysmenu_window;
syshud *syshud_window;
sysbar *sysbar_window;

void handle_signal(int signum) {
	sysmenu_signal(sysmenu_window, signum);
}

void load_libsysbar() {
	void* handle = dlopen("libsysbar.so", RTLD_LAZY);
	if (!handle) {
		std::cerr << "Cannot open library: " << dlerror() << '\n';
		exit(1);
	}

	sysbar_create = (sysbar_create_func)dlsym(handle, "sysbar_create");

	const char* dlsym_error = dlerror();
	if (dlsym_error) {
		std::cerr << "Cannot load symbols: " << dlsym_error << '\n';
		dlclose(handle);
		exit(1);
	}

	config_bar cfg;
	config_parser config(std::string(getenv("HOME")) + "/.config/sys64/bar/config.conf");

	std::string position = config.get_value("main", "position");
	if (position != "empty")
		cfg.position = std::stoi(position);

	std::string size = config.get_value("main", "size");
	if (size != "empty")
		cfg.size = std::stoi(size);

	std::string verbose = config.get_value("main", "verbose");
	if (verbose == "true")
		cfg.verbose = true;

	std::string m_start = config.get_value("main", "m_start");
	if (m_start != "empty")
		cfg.m_start = m_start;

	std::string m_center = config.get_value("main", "m_center");
	if (m_center != "empty")
		cfg.m_center = m_center;

	std::string m_end = config.get_value("main", "m_end");
	if (m_end != "empty")
		cfg.m_end = m_end;

	sysbar_window = sysbar_create(cfg);
}

void load_libsyshud() {
	void* handle = dlopen("libsyshud.so", RTLD_LAZY);
	if (!handle) {
		std::cerr << "Cannot open library: " << dlerror() << '\n';
		exit(1);
	}

	syshud_create = (syshud_create_func)dlsym(handle, "syshud_create");

	const char* dlsym_error = dlerror();
	if (dlsym_error) {
		std::cerr << "Cannot load symbols: " << dlsym_error << '\n';
		dlclose(handle);
		exit(1);
	}

	config_hud cfg;
	config_parser config(std::string(getenv("HOME")) + "/.config/sys64/hud/config.conf");

	std::string cfg_position = config.get_value("main", "position");
	if (!cfg_position.empty())
		cfg.position = cfg_position;

	std::string cfg_orientation = config.get_value("main", "orientation");
	if (!cfg_orientation.empty())
		cfg.orientation = cfg_orientation[0];

	std::string cfg_width = config.get_value("main", "width");
	if (!cfg_width.empty())
		cfg.width = std::stoi(cfg_width);

	std::string cfg_height = config.get_value("main", "height");
	if (!cfg_height.empty())
		cfg.height = std::stoi(cfg_height);

	std::string cfg_icon_size = config.get_value("main", "icon_size");
	if (!cfg_icon_size.empty())
		cfg.icon_size = std::stoi(cfg_icon_size);

	std::string cfg_percentage = config.get_value("main", "percentage");
	if (cfg_percentage == "true")
		cfg.show_percentage = true;
	else if (cfg_percentage == "false")
		cfg.show_percentage = false;

	std::string cfg_margins = config.get_value("main", "margins");
	if (!cfg_margins.empty())
		cfg.margins = cfg_margins;

	std::string cfg_timeout = config.get_value("main", "timeout");
	if (!cfg_timeout.empty())
		cfg.desired_timeout = std::stoi(cfg_timeout);

	std::string cfg_transition = config.get_value("main", "transition");
	if (!cfg_transition.empty())
		cfg.transition_time = std::stoi(cfg_transition);

	std::string cfg_backlight = config.get_value("main", "backlight");
	if (cfg_backlight != "empty")
		cfg.backlight_path = cfg_backlight;

	std::string cfg_monitors = config.get_value("main", "monitors");
	if (!cfg_monitors.empty())
		cfg.monitors = cfg_monitors;

	syshud_window = syshud_create(cfg);
}

void load_libsysmenu() {
	void* handle = dlopen("libsysmenu.so", RTLD_LAZY);
	if (!handle) {
		std::cerr << "Cannot open library: " << dlerror() << '\n';
		exit(1);
	}

	sysmenu_create = (sysmenu_create_func)dlsym(handle, "sysmenu_create");
	sysmenu_signal = (sysmenu_signal_func)dlsym(handle, "sysmenu_signal");

	const char* dlsym_error = dlerror();
	if (dlsym_error) {
		std::cerr << "Cannot load symbols: " << dlsym_error << '\n';
		dlclose(handle);
		exit(1);
	}

	config_menu cfg;
	config_parser config(std::string(getenv("HOME")) + "/.config/sys64/menu/config.conf");

	std::string cfg_start_hidden = config.get_value("main", "start-hidden");
	cfg.starthidden = (cfg_start_hidden == "true");

	std::string cfg_searchbar = config.get_value("main", "searchbar");
	cfg.searchbar = (cfg_searchbar == "true");

	std::string cfg_icon_size = config.get_value("main", "icon-size");
	if (cfg_icon_size != "empty")
		cfg.icon_size = std::stoi(cfg_icon_size);

	std::string cfg_dock_icon_size = config.get_value("main", "dock-icon-size");
	if (cfg_dock_icon_size != "empty")
		cfg.dock_icon_size = std::stoi(cfg_dock_icon_size);

	std::string cfg_app_margins = config.get_value("main", "app-margins");
	if (cfg_app_margins != "empty")
		cfg.app_margin = std::stoi(cfg_app_margins);

	std::string cfg_name_under_icon = config.get_value("main", "name-under-icon");
	cfg.name_under_icon = (cfg_name_under_icon == "true");

	std::string cfg_scroll_bars = config.get_value("main", "scroll-bars");
	cfg.scroll_bars = (cfg_scroll_bars == "true");

	std::string cfg_name_length = config.get_value("main", "name-length");
	if (cfg_name_length != "empty")
		cfg.max_name_length = std::stoi(cfg_name_length);

	std::string cfg_items_per_row = config.get_value("main", "items-per-row");
	if (cfg_items_per_row != "empty")
		cfg.items_per_row = std::stoi(cfg_items_per_row);

	std::string cfg_width = config.get_value("main", "width");
	if (cfg_width != "empty")
		cfg.width = std::stoi(cfg_width);

	std::string cfg_height =  config.get_value("main", "height");
	if (cfg_height != "empty")
		cfg.height=std::stoi(cfg_height);

	std::string cfg_monitor =  config.get_value("main", "monitor");
	if (cfg_monitor != "empty")
		cfg.main_monitor=std::stoi(cfg_monitor);

	std::string cfg_layer_shell =  config.get_value("main", "layer-shell");
	cfg.layer_shell = (cfg_layer_shell == "true");

	std::string cfg_fullscreen =  config.get_value("main", "fullscreen");
	cfg.fill_screen = (cfg_fullscreen == "true");

	std::string cfg_dock_items =  config.get_value("main", "dock-items");
	if (!cfg_dock_items.empty()) {
		cfg.dock_items = cfg_dock_items;
		cfg.layer_shell = true;
		cfg.fill_screen = true;
	}

	sysmenu_window = sysmenu_create(cfg);
}

int main() {
	auto app = Gtk::Application::create("funky.sys64.sysshell");
	app->hold();

	load_libsysbar();
	load_libsyshud();
	load_libsysmenu();

	// Catch signals
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	signal(SIGRTMIN, handle_signal); // Not really needed

	return app->run();
}
