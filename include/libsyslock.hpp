#pragma once

struct config_lock {
	bool start_unlocked = false;
	bool keypad_enabled = false;
	int pw_length = -1;
	int main_monitor = 0;
	bool debug = false;
};

class syslock {};
using syslock_create_func = syslock* (*)(const config_lock &cfg);
inline syslock_create_func syslock_create;
using syslock_lock_func = void (*)(syslock*);
inline syslock_lock_func syslock_lock;
inline syslock *syslock_window;
