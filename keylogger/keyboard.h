#pragma once
#include <Windows.h>
#include <vector>
#include <chrono>
#include <kbd.h>
#include "key.h"

using namespace std::literals::chrono_literals;

using milliseconds = std::chrono::milliseconds;
using KeyLayout = VK_TO_WCHARS10;
using DLL = HMODULE;

class Keyboard {
private:
	DLL locale;
	const KBDTABLES* layout;

	std::vector<Key> keys;
	std::vector<KeyLayout> keysLayout;

	static const std::vector<KeyLayout> makeKeysLayout(const KBDTABLES* layout);
protected:
	void setKeyState(BYTE index, SHORT state);
public:
	const milliseconds polling;
	const static int KEYBOARDSIZE = 255;

	Keyboard();

	bool changeLayout(const wchar_t* DLLName);

	const KBDTABLES& getLayout() const;
	const std::vector<Key>& getKeys() const;
	const std::vector<KeyLayout>& getKeysLayout() const;
};