#pragma once
#include "keyboard.h"

namespace LayoutFactory {
		//layout[VK_ESCAPE] = { L"[ESC]" };
		//layout[VK_F1] = { L"[F1]" };
		//layout[VK_F2] = { L"[F2]" };
		//layout[VK_F3] = { L"[F3]" };
		//layout[VK_F4] = { L"[F4]" };
		//layout[VK_F5] = { L"[F5]" };
		//layout[VK_F6] = { L"[F6]" };
		//layout[VK_F7] = { L"[F7]" };
		//layout[VK_F8] = { L"[F8]" };
		//layout[VK_F9] = { L"[F9]" };
		//layout[VK_F10] = { L"[F10]" };
		//layout[VK_F11] = { L"[F11]" };
		//layout[VK_F12] = { L"[F12]" };
		//layout[VK_SNAPSHOT] = { L"[PRTSC]" };
		//layout[VK_SCROLL] = { L"[SCR LK]" };
		//layout[VK_PAUSE] = { L"[PAUSE]" };
		//layout[VK_OEM_3] = { L"`", L"~" };
		//layout['1'] = { L"1", L"!", L"¡", L"¹" };
		//layout['2'] = { L"2", L"@", L"²" };
		//layout['3'] = { L"3", L"#", L"³" };
		//layout['4'] = { L"4", L"$", L"¤", L"£" };
		//layout['5'] = { L"5", L"%", L"€" };
		//layout['6'] = { L"6", L"^", L"¼" };
		//layout['7'] = { L"7", L"&", L"½" };
		//layout['8'] = { L"8", L"*", L"¾" };
		//layout['9'] = { L"9", L"(", L"‘" };
		//layout['0'] = { L"0", L")", L"’" };
		//layout[VK_OEM_MINUS] = { L"-", L"_", L"¥" };
		//layout[VK_OEM_PLUS] = { L"=", L"+", L"×", L"÷" };
		//layout[VK_BACK] = { L"[BACK]" };
		//layout[VK_INSERT] = { L"[INS]" };
		//layout[VK_HOME] = { L"[HOME]" };
		//layout[VK_PRIOR] = { L"[PG UP]" };
		//layout[VK_NUMLOCK] = { L"[NUM LK]" };
		//layout[VK_DIVIDE] = { L"/" };
		//layout[VK_MULTIPLY] = { L"*" };
		//layout[VK_SUBTRACT] = { L"-" };
		//layout[VK_TAB] = { L"[TAB]" };
		//layout['Q'] = { L"q", L"Q", L"ä", L"Ä" };
		//layout['W'] = { L"w", L"W", L"å", L"Å" };
		//layout['E'] = { L"e", L"E", L"é", L"É" };
		//layout['R'] = { L"r", L"R", L"®" };
		//layout['T'] = { L"t", L"T", L"þ", L"Þ" };
		//layout['Y'] = { L"y", L"Y", L"ü", L"Ü" };
		//layout['U'] = { L"u", L"U", L"ú", L"Ú" };
		//layout['I'] = { L"i", L"I", L"í", L"Í" };
		//layout['O'] = { L"o", L"O", L"ó", L"Ó" };
		//layout['P'] = { L"p", L"P", L"ö", L"Ö" };
		//layout[VK_OEM_4] = { L"[", L"{", L"«" };
		//layout[VK_OEM_6] = { L"]", L"}", L"»" };
		//layout[VK_OEM_102] = { L"\\", L" | ", L"¬", L"¦" };
		//layout[VK_DELETE] = { L"[DELETE]" };
		//layout[VK_END] = { L"[END]" };
		//layout[VK_NEXT] = { L"[PG DW]" };
		//layout[VK_NUMPAD7] = { L"7" };
		//layout[VK_NUMPAD8] = { L"8" };
		//layout[VK_NUMPAD9] = { L"9" };
		//layout[VK_ADD] = { L"+" };
		//layout[VK_CAPITAL] = { L"[CAPS LK]" };
		//layout['A'] = { L"a", L"A", L"á", L"Á" };
		//layout['S'] = { L"s", L"S", L"ß", L"§" };
		//layout['D'] = { L"d", L"D", L"ð", L"Ð" };
		//layout['F'] = { L"f", L"F" };
		//layout['G'] = { L"g", L"G" };
		//layout['H'] = { L"h", L"H" };
		//layout['J'] = { L"j", L"J" };
		//layout['K'] = { L"k", L"K" };
		//layout['L'] = { L"l", L"L", L"ø", L"Ø" };
		//layout[VK_OEM_1] = { L";", L":", L"¶", L"°" };
		//layout[VK_OEM_7] = { L"'", L"\"", L"´", L"¨" };
		//layout[VK_RETURN] = { L"[RETURN]" };
		//layout[VK_NUMPAD4] = { L"4" };
		//layout[VK_NUMPAD5] = { L"5" };
		//layout[VK_NUMPAD6] = { L"6" };
		//layout[VK_LSHIFT] = { L"[LSHIFT]" };
		//layout['Z'] = { L"z", L"Z", L"æ", L"Æ" };
		//layout['X'] = { L"x", L"X" };
		//layout['C'] = { L"c", L"C", L"©", L"¢" };
		//layout['V'] = { L"v", L"V" };
		//layout['B'] = { L"b", L"B" };
		//layout['N'] = { L"n", L"N", L"ñ", L"Ñ" };
		//layout['M'] = { L"m", L"M", L"µ" };
		//layout[VK_OEM_COMMA] = { L",", L"<", L"ç", L"Ç" };
		//layout[VK_OEM_PERIOD] = { L".", L">" };
		//layout[VK_OEM_2] = { L"/", L"?", L"¿" };
		//layout[VK_RSHIFT] = { L"[RSHIFT]" };
		//layout[VK_UP] = { L"[UP]" };
		//layout[VK_NUMPAD1] = { L"1" };
		//layout[VK_NUMPAD2] = { L"2" };
		//layout[VK_NUMPAD3] = { L"3" };
		////layout[VK_RETURN] = { L"[Return]" }; ENTER KEY LOW RIGHT NOT DIFFERENTIATED
		//layout[VK_LCONTROL] = { L"[LCTRL]" };
		//layout[VK_LWIN] = { L"[LWIN]" };
		//layout[VK_LMENU] = { L"[LALT]" };
		//layout[VK_SPACE] = { L" " };
		//layout[VK_RMENU] = { L"[ALTGR]" };
		//layout[VK_RWIN] = { L"[RWIN]" };
		//layout[VK_APPS] = { L"[MENU]" };
		//layout[VK_RCONTROL] = { L"[RCTRL]" };
		//layout[VK_LEFT] = { L"[LEFT]" };
		//layout[VK_DOWN] = { L"[DOWN]" };
		//layout[VK_RIGHT] = { L"[RIGHT]" };
		//layout[VK_NUMPAD0] = { L"0"};
		//layout[VK_DECIMAL] = { L"."};
	}

Keyboard::Keyboard()
	: keys()
	, polling(1ms)
	, layout() 
{
	keys.reserve(KEYBOARDSIZE);
	changeLayout(L"KBDUSX");

	for (BYTE i = 0; i < KEYBOARDSIZE; i++) {
		keys.push_back(Key(i));
	}
}

bool Keyboard::changeLayout(const wchar_t* DLLName) {
	if (layoutDLL) FreeLibrary(layoutDLL);
	layoutDLL = LoadLibraryW(DLLName); 

	if (layoutDLL) {
		auto KbdLayerDescriptor = GetProcAddress(layoutDLL, "KbdLayerDescriptor");
		layout = (KBDTABLES*)KbdLayerDescriptor();

		return true;
	}
	return false;
}

void Keyboard::setKeyState(BYTE index, SHORT state) {
	keys[index].setState(state);
}

const std::vector<Key>& Keyboard::getKeys() const {
	return keys;
}



