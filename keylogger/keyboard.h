#pragma once

#include "key.h"

#include <Windows.h>
#include <vector>
#include <chrono>
#include <kbd.h>

using namespace std::literals::chrono_literals;
using milliseconds = std::chrono::milliseconds;
using DLL = HMODULE;
using KeyLayout = VK_TO_WCHARS10;
struct NonPrintableKey {
	BYTE virtualKey;
	const WCHAR* description;
};

class Keyboard {
private:
	std::vector<Key> keys;

	DLL locale;
	const KBDTABLES* layout;
	std::vector<KeyLayout> keysLayout;

	static const std::vector<NonPrintableKey> nonPrintableKeys;
	static const std::vector<KeyLayout> makeKeysLayout(const KBDTABLES* layout);
protected:
	WCHAR loadedDeadKey;
	void setKeyState(BYTE index, WinState state);
public:
	const milliseconds polling;
	const static BYTE KEYBOARDSIZE;

	Keyboard();

	bool changeLayout(const char* dll);

	const KBDTABLES& getLayout() const;
	const std::vector<Key>& getKeys() const;
	const std::vector<KeyLayout>& getKeysLayout() const;
	const std::vector<NonPrintableKey>& getNonPrintableKeys() const;
};