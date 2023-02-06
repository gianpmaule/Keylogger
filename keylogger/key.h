#pragma once
#include <Windows.h>

class Keyboard;

class Key {
private:
	SHORT state;
	bool alternating;
public:
	const BYTE value;		
	static const int PRESSED;
	static const int TOGGLED;

	Key(BYTE value);
	void setState(SHORT state);

	bool isPressed() const;
	bool isAlternating() const;
	bool isToggled() const;
};