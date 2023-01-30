#pragma once
#include <vector>
#include <chrono>

#include "key.h"

using milliseconds = std::chrono::milliseconds;
using namespace std::literals::chrono_literals;

class Keyboard {
private:
	std::vector<Key> keys;

protected:
	static const int KEYBOARDSIZE;
	void setKeyState(BYTE index, SHORT state);

public:
	milliseconds polling;

	Keyboard(milliseconds polling);

	const std::vector<Key>& const getKeys() const;
};