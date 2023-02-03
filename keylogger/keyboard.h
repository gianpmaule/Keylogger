#pragma once
#include <Windows.h>
#include <vector>
#include <chrono>
#include <kbd.h>
#include "key.h"

using milliseconds = std::chrono::milliseconds;
using namespace std::literals::chrono_literals;

class Keyboard {
private:
	std::vector<Key> keys;
	HMODULE layoutDLL;
protected:
	const KBDTABLES* layout;
	void setKeyState(BYTE index, SHORT state);
public:
	const milliseconds polling;
	Keyboard();

	bool changeLayout(const wchar_t* DLLName);

	const std::vector<Key>& getKeys() const;

	const static int KEYBOARDSIZE = 255;
};