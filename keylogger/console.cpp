#pragma once
#include "console.h"

Console::Console()
	: handle()
	, visible(false)
{
	AllocConsole();
	handle = FindWindowA("ConsoleWindowClass", NULL);
	hide();
}

void Console::show() {
	ShowWindow(handle, SW_SHOWMINIMIZED);
}
void Console::hide() {
	ShowWindow(handle, SW_HIDE);
}
void Console::toggleWindow(const std::vector<Key>& keys) {
	auto& alt = keys[VK_MENU];
	auto& t = keys['T'];

	if (alt.isPressed() && t.isPressed() && t.isAlternating()) {
		visible ? hide() : show();
		visible = !visible;
	}
	
}