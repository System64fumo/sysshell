#pragma once

class sysauth {};
using sysauth_create_func = sysauth* (*)(const std::map<std::string, std::map<std::string, std::string>>&);
inline sysauth_create_func sysauth_create;
inline sysauth* sysauth_window;
inline std::map<std::string, std::map<std::string, std::string>> config_sysauth;
