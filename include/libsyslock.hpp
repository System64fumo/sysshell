#pragma once

class syslock {};
using syslock_create_func = syslock* (*)(const std::map<std::string, std::map<std::string, std::string>>&);
inline syslock_create_func syslock_create;
using syslock_lock_func = void (*)(syslock*);
inline syslock_lock_func syslock_lock;
inline syslock* syslock_window;
inline std::map<std::string, std::map<std::string, std::string>> config_syslock;
