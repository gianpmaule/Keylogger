#pragma once
#include "keyboard.h"

const int Keyboard::KEYBOARDSIZE = 255;

Keyboard::Keyboard(milliseconds polling) : keys(), polling(polling) {
	keys.reserve(KEYBOARDSIZE);

	for (BYTE i = 0; i < KEYBOARDSIZE; i++) { 
		keys.push_back(Key(i));
	}
} 

void Keyboard::setKeyState(BYTE index, SHORT state) {
	keys[index].setState(state);
}

const std::vector<Key>& Keyboard::getKeys() const {
	return keys;
}