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
	void listen(const std::vector<Key>& keys);
	void toggleWindow();
	void destroyWindow();
};