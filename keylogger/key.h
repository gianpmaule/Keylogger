#pragma once
#include <Windows.h>

class Keyboard;

class Key {
private:
	SHORT state;
	bool alternating;
protected:
	void setState(SHORT state);
public:
	const BYTE value;		
	Key(BYTE value);

	bool isPressed() const;
	bool isAlternating() const;
	bool isToggled() const;

	static const int PRESSED;
	static const int TOGGLED;

	friend Keyboard;
};