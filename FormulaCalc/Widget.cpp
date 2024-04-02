// Widget.cpp

#include "Widget.h"


HWND Widget::RLabel(int posx, int posy, int width, int height, const char* text, HWND hWnd)
{
	HWND Rlbl_hWnd = CreateWindowEx(WS_EX_RIGHT, "static", text,
		WS_VISIBLE | WS_CHILD,
		posx, posy, width, height, hWnd, nullptr, nullptr, nullptr);
	HFONT hfVol = CreateFont(/*size=*/-14, 0, 0, 0, FW_NORMAL, 0, 0, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "MS Sans Serif");
	SendMessage(Rlbl_hWnd, WM_SETFONT, (WPARAM)hfVol, 0);

	return Rlbl_hWnd;
}

HWND Widget::LLabel(int posx, int posy, int width, int height, const char* text, HWND hWnd)
{
	HWND Llbl_hWnd = CreateWindowEx(WS_EX_LEFT, "static", text,
		WS_VISIBLE | WS_CHILD,
		posx, posy, width, height, hWnd, nullptr, nullptr, nullptr);
	HFONT hfVol = CreateFont(/*size=*/-14, 0, 0, 0, FW_NORMAL, 0, 0, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "MS Sans Serif");
	SendMessage(Llbl_hWnd, WM_SETFONT, (WPARAM)hfVol, 0);

	return Llbl_hWnd;
}

HWND Widget::GroupBox(int posx, int posy, int width, int height, const char* text, HWND hWnd, HINSTANCE hInst)
{
	HWND GrpBx_hWnd = CreateWindow(
		"BUTTON",
		text,
		WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		posx, posy, width, height, hWnd, nullptr, 
		hInst, nullptr);

	return GrpBx_hWnd;
}

HWND Widget::InputBox(int posx, int posy, int width, int height, HWND hWnd)
{
	HWND InptBx_hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE, "Edit", "",
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_EX_CONTROLPARENT,
		posx, posy, width, height, hWnd, NULL, NULL, NULL);

	return InptBx_hWnd;
}

HWND Widget::ComboBox(int posx, int posy, int width, int height, const char* text, HWND hWnd, HINSTANCE hInst)
{
	HWND CmbBx_hWnd = CreateWindow(
		"COMBOBOX",
		text,
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
		posx, posy, width, height, hWnd, nullptr, hInst, nullptr);
	//HFONT hfText = CreateFont(/*size=*/-14, 0, 0, 0, FW_NORMAL, 0, 0, 0,
	//    ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS Sans Serif"));
	//SendMessage(hComboBox, WM_SETFONT, (WPARAM)hfText, 0);

	return CmbBx_hWnd;
}

HWND Widget::Button(int posx, int posy, int width, int height, const char* text, HWND hWnd, HMENU option)
{
	HWND Btn_hWnd = CreateWindow(
		"BUTTON",
		text,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
		posx, posy, width, height, hWnd, option, nullptr, nullptr);

	return Btn_hWnd;
}

HWND Widget::ButtonDef(int posx, int posy, int width, int height, const char* text, HWND hWnd, HMENU option)
{
	HWND btnDef_hWnd = CreateWindow(
		"BUTTON",
		text,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
		posx, posy, width, height, hWnd, option, nullptr, nullptr);

	return btnDef_hWnd;
}

HWND Widget::ButtonRadio(int posx, int posy, int width, int height, const char* text, HWND hWnd, HMENU option)
{
	HWND btnRad_hWnd = CreateWindow(
		"BUTTON",
		text,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTORADIOBUTTON,
		posx, posy, width, height, hWnd, option, nullptr, nullptr);

	return btnRad_hWnd;
}

HWND Widget::ResultBox(int posx, int posy, int width, int height, HWND hWnd)
{
	HWND Rslt_hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE, "static", "",
		WS_VISIBLE | WS_CHILD,
		posx, posy, width, height, hWnd, nullptr, nullptr, nullptr);

	return Rslt_hWnd;
}

HWND Widget::MsgBox(int posx, int posy, int width, int height, HWND hWnd, HMENU option)
{
	HWND Msg_hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE, "static", "",
		WS_VISIBLE | WS_CHILD,
		posx, posy, width, height, hWnd, option, nullptr, nullptr);

	return Msg_hWnd;
}

HWND Widget::CreateWnd(int posx, int posy, int width, int height, const char* name, const char* className, 
				WNDPROC wndProc, WNDCLASSEX& wcex, HINSTANCE& hInst, int nCmdShow)
{
	wcex.hInstance = hInst;
	wcex.lpszClassName = className;
	wcex.lpfnWndProc = (WNDPROC)wndProc;	// Window procedure.
	wcex.style = CS_DBLCLKS;					// Catch double-clicks
	wcex.cbSize = sizeof(WNDCLASSEX);

	// Use default icon and mouse-pointer
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);

	wcex.lpszMenuName = NULL;					// No menu
	wcex.cbClsExtra = 0;						// No extra bytes after the window class
	wcex.cbWndExtra = 0;						// structure or the window instance

	// Use Windows's default colour as the background of the window
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);

	if (!RegisterClassEx(&wcex))
	{
		throw GTWND_LAST_EXCEPT();
	}

	HWND hWnd = CreateWindowEx(
		0,						// Extended possibilites for variation.
		className,				// Classname.
		name,					// Title Text.
		WS_OVERLAPPEDWINDOW,	// Default window.
		posx,					// The position
		posy,					// where the window ends up on the screen.
		width,                  // The programs width
		height,                 // and height in pixels.
		HWND_DESKTOP,			// The window is a child-window to desktop
		NULL,					// Menu
		hInst,					// Program Instance handler.
		NULL					// Window Creation data.
	);

	// Check for error.
	if (hWnd == nullptr)
	{
		throw GTWND_LAST_EXCEPT();
	}

	// Make the window visible on the screen
	ShowWindow(hWnd, nCmdShow);

	return hWnd;
}




