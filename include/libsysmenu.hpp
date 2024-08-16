#pragma once
#include <string>

struct config_menu {
	bool starthidden = false;
	bool searchbar = true;
	int icon_size = 32;
	int dock_icon_size = 64;
	int app_margin = 4;
	bool name_under_icon = false;
	bool scroll_bars = false;
	ulong max_name_length = 30;
	int items_per_row = 1;
	std::string anchors = "";
	int width = 400;
	int height = 600;
	int main_monitor = 0;
	bool layer_shell = true;
	std::string dock_items = "";
};

class sysmenu {};
using sysmenu_create_func = sysmenu* (*)(const config_menu &cfg);
inline sysmenu_create_func sysmenu_create;
using sysmenu_signal_func = void (*)(sysmenu*, int);
inline sysmenu_signal_func sysmenu_signal;
inline sysmenu *sysmenu_window;
