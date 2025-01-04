#pragma once
#include <unordered_map>

struct config_power {
	int position = 4;
	int main_monitor = 0;
	int transition_duration = 1000;
	std::unordered_map<uint, std::string> hotkeys = {
		{0x075, "shutdown"},
		{0x072, "reboot"},
		{0x06c, "logout"},
		{0x073, "suspend"},
		{0x063, "cancel"},
		{0xff1b, "cancel"}
	};
};

class syspower {};
using syspower_create_func = syspower* (*)(const config_power &cfg);
inline syspower_create_func syspower_create;
inline syspower *syspower_window;
inline config_power cfg_power;
