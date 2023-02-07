#pragma once
#include "keyboard.h"
#include <iostream>
//namespace LayoutFactory {
//		layout[VK_ESCAPE] = { L"[ESC]" };
//		layout[VK_F1] = { L"[F1]" };
//		layout[VK_F2] = { L"[F2]" };
//		layout[VK_F3] = { L"[F3]" };
//		layout[VK_F4] = { L"[F4]" };
//		layout[VK_F5] = { L"[F5]" };
//		layout[VK_F6] = { L"[F6]" };
//		layout[VK_F7] = { L"[F7]" };
//		layout[VK_F8] = { L"[F8]" };
//		layout[VK_F9] = { L"[F9]" };
//		layout[VK_F10] = { L"[F10]" };
//		layout[VK_F11] = { L"[F11]" };
//		layout[VK_F12] = { L"[F12]" };
//		layout[VK_SNAPSHOT] = { L"[PRTSC]" };
//		layout[VK_SCROLL] = { L"[SCR LK]" };
//		layout[VK_PAUSE] = { L"[PAUSE]" };
//		layout[VK_BACK] = { L"[BACK]" };
//		layout[VK_INSERT] = { L"[INS]" };
//		layout[VK_HOME] = { L"[HOME]" };
//		layout[VK_PRIOR] = { L"[PG UP]" };
//		layout[VK_NUMLOCK] = { L"[NUM LK]" };
//		layout[VK_TAB] = { L"[TAB]" };
//		layout[VK_DELETE] = { L"[DELETE]" };
//		layout[VK_END] = { L"[END]" };
//		layout[VK_NEXT] = { L"[PG DW]" };
//		layout[VK_CAPITAL] = { L"[CAPS LK]" };
//		layout[VK_RETURN] = { L"[RETURN]" };
//		layout[VK_LSHIFT] = { L"[LSHIFT]" };
//		layout[VK_RSHIFT] = { L"[RSHIFT]" };
//		layout[VK_UP] = { L"[UP]" };
//		layout[VK_LCONTROL] = { L"[LCTRL]" };
//		layout[VK_LWIN] = { L"[LWIN]" };
//		layout[VK_LMENU] = { L"[LALT]" };
//		layout[VK_RMENU] = { L"[ALTGR]" };
//		layout[VK_RWIN] = { L"[RWIN]" };
//		layout[VK_APPS] = { L"[MENU]" };
//		layout[VK_RCONTROL] = { L"[RCTRL]" };
//		layout[VK_LEFT] = { L"[LEFT]" };
//		layout[VK_DOWN] = { L"[DOWN]" };
//		layout[VK_RIGHT] = { L"[RIGHT]" };
//	}

Keyboard::Keyboard()
	: keys()
	, polling(1ms)
	, locale(nullptr) 
{
	keys.reserve(KEYBOARDSIZE);
	changeLayout(L"KBDUSX");

	for (BYTE i = 0; i < KEYBOARDSIZE; i++) {
		keys.push_back(Key(i));
	}
}

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
			KeyLayout newKeyLayout = { keyLayout->VirtualKey, keyLayout->Attributes };

			for (int i = 0; i < keysLayout->nModifications; i++) {
				newKeyLayout.wch[i] = keyLayout->wch[i];
			}

			newKeysLayout.push_back(newKeyLayout);
		}
	}
	return newKeysLayout;
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

void Keyboard::setKeyState(BYTE index, SHORT state) {
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



