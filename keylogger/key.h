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
	static const int PRESSED;
	static const int TOGGLED;

	Key(BYTE value);

	bool isPressed() const;
	bool isAlternating() const;
	bool isToggled() const;

	friend Keyboard;
};