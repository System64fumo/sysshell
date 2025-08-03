#pragma once
#include "config_parser.hpp"

#include <libsysauth.hpp>
#include <libsysbar.hpp>
#include <libsysboard.hpp>
#include <libsyshud.hpp>
#include <libsyslock.hpp>
#include <libsysmenu.hpp>
#include <libsyspower.hpp>

#include "extras/clipboard.hpp"

#include <glibmm/dispatcher.h>
#include <dlfcn.h>
#include <thread>

void load_libsysauth();
void load_libsysbar();
void load_libsysboard();
void load_libsyshud();
void load_libsyslock();
void load_libsysmenu();
void load_libsyspower();

inline clipboard* cl;

std::map<std::string, std::map<std::string, std::string>> load_config(const std::string&);

inline struct config_shell {
	std::string load = "auth,bar,board,hud,lock,menu,power";
} cfg_shell;
