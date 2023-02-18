#pragma once
#include "console.h"
#include <locale>

Console::Console()
	: handle()
	, visible(true)
{
	setlocale(LC_ALL, "");

	AllocConsole();
	handle = FindWindowA("ConsoleWindowClass", NULL);
	show();
}

void Console::listen(const std::vector<Key>& keys) {
	const auto& alt = keys[VK_MENU];
	const auto& t = keys['T'];
	const auto& x = keys['X'];
	
	const bool toggle = alt.isPressed() && t.isPressed() && t.isAlternating();
	const bool kill = alt.isPressed() && x.isPressed() && x.isAlternating();

	if (toggle) {
		toggleWindow();
	}
	if (kill) {
		destroyWindow();
	}
}
void Console::toggleWindow() {
	visible ? hide() : show();
	visible = !visible;
}
void Console::show() {
	ShowWindow(handle, SW_SHOWDEFAULT);
}
void Console::hide() {
	ShowWindow(handle, SW_HIDE);
}
void Console::destroyWindow() {
	SendMessageW(handle, WM_CLOSE, 0, 0);
}