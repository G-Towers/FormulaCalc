// Widget.h

#pragma once

#include "Window.h"


namespace Widget
{
	// Define the dialog data structure properly
	struct DialogData
	{
		const char* title; // Title of the dialog.
		const char* message;
		const char* imagePath;
		int width;
		int height;
	};

	// label controls.
	HWND RLabel(int posx, int posy, int width, int height, const char* text, HWND hWnd);
	HWND RLabelBold(int posx, int posy, int width, int height, const char* text, HWND hWnd);
	HWND LLabel(int posx, int posy, int width, int height, const char* text, HWND hWnd);
	HWND LLabelBold(int posx, int posy, int width, int height, const char* text, HWND hWnd);

	// Group controls.
	HWND GroupBox(int posx, int posy, int width, int height, const char* text, HWND hWnd, HINSTANCE hInst);

	// Input controls.
	HWND InputBox(int posx, int posy, int width, int height, HWND hWnd);
	HWND InputBoxMulti(int posx, int posy, int width, int height, HWND hWnd);

	// List controls.
	HWND ComboBox(int posx, int posy, int width, int height, const char* text, HWND hWnd, HINSTANCE hInst);
	HWND ComboBoxID(int posx, int posy, int width, int height, const char* text, HWND hWnd, HMENU id, HINSTANCE hInst);

	// Button controls.
	HWND Button(int posx, int posy, int width, int height, const char* text, HWND hWnd, HMENU option);
	HWND ButtonDef(int posx, int posy, int width, int height, const char* text, HWND hWnd, HMENU option);
	HWND ButtonRadio(int posx, int posy, int width, int height, const char* text, HWND hWnd, HMENU option);

	// Message controls.
	HWND ResultBox(int posx, int posy, int width, int height, HWND hWnd);
	HWND MsgBox(int posx, int posy, int width, int height, HWND hWnd, HMENU option);

	// Image controls
	HWND ImageStatic(int posx, int posy, int width, int height, const char* text, HWND hWnd, HBITMAP hImage, HINSTANCE hInst);
	HWND ImageBtn(int posx, int posy, int width, int height, const char* text, HWND hWnd, HBITMAP hImage, HMENU option);
	HBITMAP LoadBitmapImage(HWND hWnd, const char* fileName, int width, int height);

	// Window creation.
	HWND CreateWnd(int posx, int posy, int width, int height, const char* name, const char* className, 
			WNDPROC wndProc, WNDCLASSEX& wcex, HINSTANCE& hInst, int nCmdShow);

	// Add this to Widget.h
	INT_PTR StaticModalDialog(HWND hParent, const char* title, const char* message,
		const char* imagePath = nullptr,
		int width = 400, int height = 200);

	//INT_PTR SmplModlDlg(HWND hParent, const char* title, const char* message);

};

