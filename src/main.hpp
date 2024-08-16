#pragma once
#include "config_parser.hpp"

#include <libsysbar.hpp>
#include <libsysboard.hpp>
#include <libsyshud.hpp>
#include <libsyslock.hpp>
#include <libsysmenu.hpp>
#include <libsyspower.hpp>

#include <iostream>
#include <dlfcn.h>

void load_libsysbar();
void load_libsysboard();
void load_libsyshud();
void load_libsyslock();
void load_libsysmenu();
void load_libsyspower();
