#include "key.h"

Key::Key(BYTE value, std::string description)
	: value(value)
	, description(std::string(description))
	, state(0)
	, alternating(false) {}

bool Key::isPressed() {
	return (state & PRESSED);
}
bool Key::isTriggered() {
	bool triggered = isPressed() && alternating;
	alternating = false;
	return triggered;
}
bool Key::isToggled() {
	return (GetKeyState(value) & TOGGLED);
}