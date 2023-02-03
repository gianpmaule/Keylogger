#pragma once
#include "key.h"

constexpr int Key::PRESSED = 0x8000;
constexpr int Key::TOGGLED = 0x0001;

Key::Key(BYTE value)
	: value(value)
	, state(0)
	, alternating(false) {}

void Key::setState(SHORT state) {
	bool oldpressed = isPressed();
	this->state = state;
	bool curpressed = isPressed();

	alternating = oldpressed != curpressed ? true : false;
}

bool Key::isPressed() const {
	return (state & PRESSED);
}
bool Key::isToggled() const {
	return (GetKeyState(value) & TOGGLED);
}
bool Key::isAlternating() const {
	return alternating;
}