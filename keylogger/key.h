#pragma once
#include <windows.h>

class Key {
private:
	SHORT state;
	bool alternating;
	
	static const int PRESSED;
	static const int TOGGLED;
public:
	const BYTE value;		
	Key(BYTE value);

	void setState(SHORT state);

	bool isPressed() const;
	bool isTriggered() const;
	bool isToggled() const;
};