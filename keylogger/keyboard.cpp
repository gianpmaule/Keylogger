#pragma once
#include "keyboard.h"
#include <iostream>


Keyboard::Keyboard()
	: keys()
	, polling(1ms)
	, locale(nullptr) 
{
	changeLayout(L"KBDUSX");

	keys.reserve(KEYBOARDSIZE);
	for (BYTE i = 0; i < KEYBOARDSIZE; i++) {
		keys.emplace_back(i);
	}
}

bool Keyboard::changeLayout(const wchar_t* DLLName) {
	if (locale) FreeLibrary(locale);

	locale = LoadLibraryW(DLLName);

	if (locale) {
		auto KbdLayerDescriptor = GetProcAddress(locale, "KbdLayerDescriptor");

		layout = (KBDTABLES*)KbdLayerDescriptor();
		keysLayout = makeKeysLayout(layout);

		return true;
	}
	return false;
}

void Keyboard::setKeyState(BYTE index, WinState state) {
	keys[index].setState(state);
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
			; keyLayout = (VK_TO_WCHARS1*)(((PBYTE)keyLayout) + keysLayout->cbSize))
		{
			if (keyLayout->VirtualKey == VK_ESCAPE || keyLayout->VirtualKey == VK_F1 || keyLayout->VirtualKey == VK_F2 || keyLayout->VirtualKey == VK_F3 || keyLayout->VirtualKey == VK_F4 || keyLayout->VirtualKey == VK_F5 || keyLayout->VirtualKey == VK_F6 || keyLayout->VirtualKey == VK_F7 || keyLayout->VirtualKey == VK_F8 || keyLayout->VirtualKey == VK_F9 || keyLayout->VirtualKey == VK_F10 || keyLayout->VirtualKey == VK_F11 || keyLayout->VirtualKey == VK_F12 || keyLayout->VirtualKey == VK_SNAPSHOT || keyLayout->VirtualKey == VK_SCROLL || keyLayout->VirtualKey == VK_PAUSE || keyLayout->VirtualKey == VK_BACK || keyLayout->VirtualKey == VK_INSERT || keyLayout->VirtualKey == VK_HOME || keyLayout->VirtualKey == VK_PRIOR || keyLayout->VirtualKey == VK_NUMLOCK || keyLayout->VirtualKey == VK_TAB || keyLayout->VirtualKey == VK_DELETE || keyLayout->VirtualKey == VK_END || keyLayout->VirtualKey == VK_NEXT || keyLayout->VirtualKey == VK_CAPITAL || keyLayout->VirtualKey == VK_RETURN || keyLayout->VirtualKey == VK_LSHIFT || keyLayout->VirtualKey == VK_RSHIFT || keyLayout->VirtualKey == VK_UP || keyLayout->VirtualKey == VK_LCONTROL || keyLayout->VirtualKey == VK_LWIN || keyLayout->VirtualKey == VK_LMENU || keyLayout->VirtualKey == VK_RMENU || keyLayout->VirtualKey == VK_RWIN || keyLayout->VirtualKey == VK_APPS || keyLayout->VirtualKey == VK_RCONTROL || keyLayout->VirtualKey == VK_LEFT || keyLayout->VirtualKey == VK_DOWN || keyLayout->VirtualKey == VK_RIGHT) {
				continue;
			}

			KeyLayout newKeyLayout = { keyLayout->VirtualKey, keyLayout->Attributes };

			for (int i = 0; i < keysLayout->nModifications; i++) {
				newKeyLayout.wch[i] = keyLayout->wch[i];
			}

			newKeysLayout.push_back(newKeyLayout);
		}
	}
	return newKeysLayout;
}