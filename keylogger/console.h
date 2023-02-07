#pragma once
#include <Windows.h>
#include "keyboard.h"

class Console {
private:
	HWND handle;
	bool visible;
	
	void hide();
	void show();
public:
	Console();
	void toggleWindow(const std::vector<Key>& keys);
};