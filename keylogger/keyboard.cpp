#pragma once

#include "keyboard.h"

#include <iostream>

Keyboard::Keyboard()
	: keys()
	, polling(1ms)
	, locale(nullptr) 
	, layout(nullptr)
	, loadedDeadKey(0)
{
	changeLayout("KBDUSX");

	keys.reserve(KEYBOARDSIZE);
	for (BYTE i = 0; i < KEYBOARDSIZE; i++) {
		keys.emplace_back(i);
	}
}

bool Keyboard::changeLayout(const char* dll) {
	if (locale) FreeLibrary(locale);

	locale = LoadLibraryA(dll);

	if (locale) {
		auto KbdLayerDescriptor = GetProcAddress(locale, "KbdLayerDescriptor");

		layout = (KBDTABLES*)KbdLayerDescriptor();
		keysLayout = makeKeysLayout(layout);

		return true;
	}
	return false;
}

void Keyboard::setKeyState(BYTE index, WinState state) {
	keys.at(index).setState(state);
}

const KBDTABLES& Keyboard::getLayout() const {
	return *layout;
}
const std::vector<Key>& Keyboard::getKeys() const {
	return keys;
}
const std::vector<KeyLayout>& Keyboard::getKeysLayout() const {
	return keysLayout;
}
const std::vector<NonPrintableKey>& Keyboard::getNonPrintableKeys() const {
	return nonPrintableKeys;
}

const BYTE Keyboard::KEYBOARDSIZE = 255;
const std::vector<NonPrintableKey> Keyboard::nonPrintableKeys{
	{VK_ESCAPE, L"[ESC]"},
	{VK_F1, L"[F1]"},
	{VK_F2, L"[F2]"},
	{VK_F3, L"[F3]"},
	{VK_F4, L"[F4]"},
	{VK_F5, L"[F5]"},
	{VK_F6, L"[F6]"},
	{VK_F7, L"[F7]"},
	{VK_F8, L"[F8]"},
	{VK_F9, L"[F9]"},
	{VK_F10, L"[F10]"},
	{VK_F11, L"[F11]"},
	{VK_F12, L"[F12]"},
	{VK_SNAPSHOT, L"[PRTSC]"},
	{VK_SCROLL, L"[SCR LK]"},
	{VK_PAUSE, L"[PAUSE]"},
	{VK_BACK, L"[BACK]"},
	{VK_INSERT, L"[INS]"},
	{VK_HOME, L"[HOME]"},
	{VK_PRIOR, L"[PG UP]"},
	{VK_NUMLOCK, L"[NUM LK]"},
	{VK_TAB, L"[TAB]"},
	{VK_DELETE, L"[DELETE]"},
	{VK_END, L"[END]"},
	{VK_NEXT, L"[PG DW]"},
	{VK_CAPITAL, L"[CAPS LK]"},
	{VK_RETURN, L"[RETURN]"},
	{VK_LSHIFT, L"[LSHIFT]"},
	{VK_RSHIFT, L"[RSHIFT]"},
	{VK_UP, L"[UP]"},
	{VK_LCONTROL, L"[LCTRL]"},
	{VK_LWIN, L"[LWIN]"},
	{VK_LMENU, L"[LALT]"},
	{VK_RMENU, L"[ALTGR]"},
	{VK_RWIN, L"[RWIN]"},
	{VK_APPS, L"[MENU]"},
	{VK_RCONTROL, L"[RCTRL]"},
	{VK_LEFT, L"[LEFT]"},
	{VK_DOWN, L"[DOWN]"},
	{VK_RIGHT, L"[RIGHT]"}
};
const std::vector<KeyLayout> Keyboard::makeKeysLayout(const KBDTABLES* layout) {
	std::vector<KeyLayout> newKeysLayout;

	for (auto* keysLayout = layout->pVkToWcharTable
		; keysLayout->pVkToWchars
		; keysLayout++)
	{
		for (auto* keyLayout = keysLayout->pVkToWchars
			; keyLayout->VirtualKey
			; keyLayout = (VK_TO_WCHARS1*)(((PBYTE)keyLayout) + keysLayout->cbSize)) //yes this is pointer arithmetic at its finest
		{
			switch (keyLayout->VirtualKey) {
				case VK_ESCAPE: continue;
				case VK_F1: continue;
				case VK_F2: continue;
				case VK_F3: continue;
				case VK_F4: continue;
				case VK_F5: continue;
				case VK_F6: continue;
				case VK_F7: continue;
				case VK_F8: continue;
				case VK_F9: continue;
				case VK_F10: continue;
				case VK_F11: continue;
				case VK_F12: continue;
				case VK_SNAPSHOT: continue;
				case VK_SCROLL: continue;
				case VK_PAUSE: continue;
				case VK_BACK: continue;
				case VK_INSERT: continue;
				case VK_HOME: continue;
				case VK_PRIOR: continue;
				case VK_NUMLOCK: continue;
				case VK_TAB: continue;
				case VK_DELETE: continue;
				case VK_END: continue;
				case VK_NEXT: continue;
				case VK_CAPITAL: continue;
				case VK_RETURN: continue;
				case VK_LSHIFT: continue;
				case VK_RSHIFT: continue;
				case VK_UP: continue;
				case VK_LCONTROL: continue;
				case VK_LWIN: continue;
				case VK_LMENU: continue;
				case VK_RMENU: continue;
				case VK_RWIN: continue;
				case VK_APPS: continue;
				case VK_RCONTROL: continue;
				case VK_LEFT: continue;
				case VK_DOWN: continue;
				case VK_RIGHT: continue;
			}

			KeyLayout newKeyLayout{ 
				keyLayout->VirtualKey, 
				keyLayout->Attributes 
			};

			for (int i = 0; i < keysLayout->nModifications; i++) {
				newKeyLayout.wch[i] = keyLayout->wch[i];
			}

			newKeysLayout.push_back(newKeyLayout);
		}
	}
	return newKeysLayout;
}