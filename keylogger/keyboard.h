#pragma once
#include <Windows.h>
#include <vector>
#include <chrono>
#include <kbd.h>
#include <string>
#include "key.h"

using namespace std::literals::chrono_literals;

using milliseconds = std::chrono::milliseconds;
using DLL = HMODULE;

struct KeyLayout {
	BYTE  VirtualKey;
	BYTE  Attributes;
	std::wstring wch[10];
};

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