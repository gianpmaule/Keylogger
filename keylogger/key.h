#pragma once
#include <windows.h>
#include <string>

#define PRESSED 0x8000
#define TOGGLED 0x0001
#define CHARTOLOWER 32

class Key {
	private:
	//The Windows API async keystate (pressed or not)
	SHORT state;

	//Is true when the key is shifting states (pressed and released)
	//Is false otherwise
	bool alternating;

	public:
	//The Windows keyboard key value
	const BYTE value;
	//The name of the key
	const std::string description;

	Key(BYTE value, std::string description);

	bool isPressed();
	//Returns the instant where the key state shifts from released to pressed
	bool isTriggered();
	//Returns whether the key state is toggled (useful with CAPSLK, NUMLK, SCRLK)
	bool isToggled();

	friend class Keylogger;
};