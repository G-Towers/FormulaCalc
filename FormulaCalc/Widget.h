// Widget.h

#pragma once

#include "Window.h"


namespace Widget
{
	HWND RLabel(int posx, int posy, int width, int height, const char* text, HWND hWnd);
	HWND LLabel(int posx, int posy, int width, int height, const char* text, HWND hWnd);
	HWND GroupBox(int posx, int posy, int width, int height, const char* text, HWND hWnd, HINSTANCE hInst);
	HWND InputBox(int posx, int posy, int width, int height, HWND hWnd);
	HWND InputBoxMulti(int posx, int posy, int width, int height, HWND hWnd);
	HWND ComboBox(int posx, int posy, int width, int height, const char* text, HWND hWnd, HINSTANCE hInst);
	HWND Button(int posx, int posy, int width, int height, const char* text, HWND hWnd, HMENU option);
	HWND ButtonDef(int posx, int posy, int width, int height, const char* text, HWND hWnd, HMENU option);
	HWND ButtonRadio(int posx, int posy, int width, int height, const char* text, HWND hWnd, HMENU option);
	HWND ResultBox(int posx, int posy, int width, int height, HWND hWnd);
	HWND MsgBox(int posx, int posy, int width, int height, HWND hWnd, HMENU option);

	HWND CreateWnd(int posx, int posy, int width, int height, const char* name, const char* className, 
			WNDPROC wndProc, WNDCLASSEX& wcex, HINSTANCE& hInst, int nCmdShow);

};

