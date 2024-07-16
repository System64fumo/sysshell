#include <string>

struct config_bar {
	int position = 0;
	int size = 40;
	bool verbose = false;
	std::string m_start = "clock,weather,tray";
	std::string m_center = "hyprland";
	std::string m_end = "volume,network,notification";
};

class sysbar {};
using sysbar_create_func = sysbar* (*)(const config_bar &cfg);
sysbar_create_func sysbar_create;
