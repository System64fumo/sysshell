#pragma once

class sysboard {};
using sysboard_create_func = sysboard* (*)(const std::map<std::string, std::map<std::string, std::string>>&);
inline sysboard_create_func sysboard_create;
using sysboard_signal_func = void (*)(sysboard*, int);
inline sysboard_signal_func sysboard_signal;
inline sysboard* sysboard_window;
inline std::map<std::string, std::map<std::string, std::string>> config_sysboard;
