#pragma once

class syshud {};
using syshud_create_func = syshud* (*)(const std::map<std::string, std::map<std::string, std::string>>&);
inline syshud_create_func syshud_create;
inline syshud *syshud_window;
