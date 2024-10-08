#pragma once

struct config_board {
	int margin = 10;
	double height_multiplier = 0.75;
	std::string layout = "full";
};

class sysboard {};
using sysboard_create_func = sysboard* (*)(const config_board &cfg);
inline sysboard_create_func sysboard_create;
using sysboard_signal_func = void (*)(sysboard*, int);
inline sysboard_signal_func sysboard_signal;
inline sysboard *sysboard_window;
