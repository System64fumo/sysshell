#include "../main.hpp"

void load_libsysmenu() {
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

	std::cout << "Loading: libsysmenu.so" << std::endl;

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

	std::string cfg_anchors =  config.get_value("main", "anchors");
	if (cfg_anchors != "empty")
		cfg.anchors = cfg_anchors;

	std::string cfg_width = config.get_value("main", "width");
	if (cfg_width != "empty")
		cfg.width = std::stoi(cfg_width);

	std::string cfg_height = config.get_value("main", "height");
	if (cfg_height != "empty")
		cfg.height = std::stoi(cfg_height);

	std::string cfg_monitor = config.get_value("main", "monitor");
	if (cfg_monitor != "empty")
		cfg.main_monitor = std::stoi(cfg_monitor);

	std::string cfg_layer_shell = config.get_value("main", "layer-shell");
	cfg.layer_shell = (cfg_layer_shell == "true");

	std::string cfg_dock_items = config.get_value("main", "dock-items");
	if (!cfg_dock_items.empty()) {
		cfg.dock_items = cfg_dock_items;
		cfg.layer_shell = true;
		cfg.anchors = "top right bottom left";
	}

	sysmenu_window = sysmenu_create(cfg);
}
