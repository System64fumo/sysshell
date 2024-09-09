#pragma once
#include <string>

struct config_hud {
	std::string position = "bottom";
	char orientation = 'h';
	int width = 300;
	int height = 50;
	int icon_size = 26;
	bool show_percentage = true;
	std::string margins = "0 0 0 0";
	int desired_timeout = 3;
	int transition_time = 250;
	std::string backlight_path = "";
	std::string monitors = "audio_in,audio_out,brightness";
	std::string keyboard = "";
};

class syshud {};
using syshud_create_func = syshud* (*)(const config_hud &cfg);
inline syshud_create_func syshud_create;
inline syshud *syshud_window;
