#pragma once

class sysmenu {};
using sysmenu_create_func = sysmenu* (*)(const std::map<std::string, std::map<std::string, std::string>>&);
inline sysmenu_create_func sysmenu_create;
using sysmenu_signal_func = void (*)(sysmenu*, int);
inline sysmenu_signal_func sysmenu_signal;
inline sysmenu *sysmenu_window;
