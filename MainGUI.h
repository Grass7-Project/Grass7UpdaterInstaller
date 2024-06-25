#pragma once

class MainGUI {
public:
	static int Init(HWND &hWnd, HINSTANCE &hInstance);

private:
	static		LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};