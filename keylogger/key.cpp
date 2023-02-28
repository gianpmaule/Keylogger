#pragma once

#include "key.h"

const WinState Key::WINPRESSED = 0b0000000100000000;
const WinState Key::WINTOGGLED = 0x0000000000000001;

Key::Key(BYTE vk)
	: vk(vk)
	, pressed(false)
	, alternating(false)
	, toggled(false) {}

void Key::setState(WinState state) {
	bool oldpressed = pressed;

	pressed = state & WINPRESSED;
	alternating = oldpressed != pressed ? true : false;
	toggled = state & WINTOGGLED;
}

bool Key::isPressed() const {
	return pressed;
}
bool Key::isAlternating() const {
	return alternating;
}
bool Key::isToggled() const {
	return toggled;
}
