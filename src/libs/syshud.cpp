#include "../main.hpp"

void load_libsyshud() {
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

	std::cout << "Loading: libsyshud.so" << std::endl;

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

	std::string cfg_keyboard = config.get_value("main", "keyboard");
	if (cfg_keyboard != "empty")
		cfg.keyboard = cfg_keyboard;

	syshud_window = syshud_create(cfg);
}
