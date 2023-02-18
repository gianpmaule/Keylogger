#pragma once
#include <Windows.h>

using WinState = SHORT;

class Key {
private:
	bool pressed;
	bool alternating;
	bool toggled;
public:
	const BYTE vk;	
	Key(BYTE vk);

	static const WinState WINPRESSED; //GETKEYSTATE PRESSED IDENTIFIER BIT
	static const WinState WINTOGGLED; //GETKEYSTATE TOGGLED IDENTIFIER BIT
	void setState(WinState state);

	bool isPressed() const;
	bool isAlternating() const;
	bool isToggled() const;
};