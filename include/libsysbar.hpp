#pragma once
#include <string>

struct config_bar {
	int position = 0;
	int size = 40;
	bool verbose = false;
	int main_monitor = 0;
	std::string m_start = "clock,weather,tray";
	std::string m_center = "hyprland";
	std::string m_end = "volume,network,notification";
};

class sysbar {};
using sysbar_create_func = sysbar* (*)(const config_bar &cfg);
inline sysbar_create_func sysbar_create;
using sysbar_signal_func = void (*)(sysbar*, int);
inline sysbar_signal_func sysbar_signal;
inline sysbar *sysbar_window;
