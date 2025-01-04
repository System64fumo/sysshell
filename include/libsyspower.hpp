#pragma once
#include <unordered_map>


class syspower {};
using syspower_create_func = syspower* (*)(const std::map<std::string, std::map<std::string, std::string>> &cfg);
inline syspower_create_func syspower_create;
inline syspower *syspower_window;
