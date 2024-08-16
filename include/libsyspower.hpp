#pragma once

struct config_power {
	int position = 4;
	int main_monitor = 0;
	int transition_duration = 1000;
};

class syspower {};
using syspower_create_func = syspower* (*)(const config_power &cfg);
inline syspower_create_func syspower_create;
inline syspower *syspower_window;
inline config_power cfg_power;
