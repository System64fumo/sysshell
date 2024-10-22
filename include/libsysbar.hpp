#pragma once
#include <map>
#include <string>

class sysbar {};
using sysbar_create_func = sysbar* (*)(const std::map<std::string, std::map<std::string, std::string>> &cfg);
inline sysbar_create_func sysbar_create;
using sysbar_signal_func = void (*)(sysbar*, int);
inline sysbar_signal_func sysbar_signal;
inline sysbar *sysbar_window;
