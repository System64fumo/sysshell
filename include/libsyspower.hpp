#pragma once

class syspower {};
using syspower_create_func = syspower* (*)(const std::map<std::string, std::map<std::string, std::string>>&);
inline syspower_create_func syspower_create;
inline syspower* syspower_window;
inline std::map<std::string, std::map<std::string, std::string>> config_syspower;
