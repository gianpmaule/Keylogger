#pragma once
#include <Windows.h>
#include <vector>
#include <chrono>
#include <kbd.h>
#include "key.h"

using milliseconds = std::chrono::milliseconds;
using namespace std::literals::chrono_literals;
using Layout = VK_TO_WCHARS10;

class Keyboard {
private:
	std::vector<Key> keys;

	std::vector<Layout> keysLayout;
	const KBDTABLES* locale;
	static const std::vector<Layout> getKeysLayout(const KBDTABLES* locale);

	HMODULE layoutDLL;
protected:
	void setKeyState(BYTE index, SHORT state);
public:
	const milliseconds polling;
	const static int KEYBOARDSIZE = 255;

	Keyboard();

	bool changeLayout(const wchar_t* DLLName);

	const std::vector<Key>& getKeys() const;
	const std::vector<Layout>& getKeysLayout() const;
	const KBDTABLES& getLocale() const;
	
};