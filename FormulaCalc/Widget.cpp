// Widget.cpp

#include "Widget.h"
#include <tchar.h>

HWND Widget::RLabel(int posx, int posy, int width, int height, const char* text, HWND hWnd)
{
	HWND Rlbl_hWnd = CreateWindowEx(WS_EX_RIGHT, "static", text,
		WS_VISIBLE | WS_CHILD,
		posx, posy, width, height, hWnd, nullptr, nullptr, nullptr);
	HFONT hfLabel = CreateFont( 16,			// Height
							  5,			// Width
							  0,			// Escapement
							  0,			// Orientation
							  FW_NORMAL,	// Weight
							  0,			// Italic
							  0,			// Underline
							  0,			// Strikeout
							  ANSI_CHARSET,			// Character set.
							  OUT_DEFAULT_PRECIS,	// Output precision.
							  CLIP_DEFAULT_PRECIS,	// Clip precision
							  DEFAULT_QUALITY,		// Quality
							  DEFAULT_PITCH,		// Pitch and family
							  "MS Sans Serif"		// Font
							  );

	// Error handling. 
	if (!Rlbl_hWnd)
	{
		MessageBox(NULL, "Failed to create right-aligned label.", "Error", MB_OK | MB_ICONERROR);
		Rlbl_hWnd = nullptr; // Set to nullptr if creation fails.
		return Rlbl_hWnd; // Return nullptr if creation fails.
	}

	// Set the font for the label.
	SendMessage(Rlbl_hWnd, WM_SETFONT, (WPARAM)hfLabel, 0);

	return Rlbl_hWnd;
}

HWND Widget::RLabelBold(int posx, int posy, int width, int height, const char* text, HWND hWnd)
{
	HWND RlblBld_hWnd = CreateWindowEx(WS_EX_RIGHT, "static", text,
		WS_VISIBLE | WS_CHILD,
		posx, posy, width, height, hWnd, nullptr, nullptr, nullptr);
	HFONT hfVol = CreateFont(16, 5, 0, 0, FW_BOLD, 0, 0, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "MS Sans Serif");

	// Error handling.
	if (!RlblBld_hWnd)
	{
		MessageBox(NULL, "Failed to create right-aligned bold label.", "Error", MB_OK | MB_ICONERROR);
		RlblBld_hWnd = nullptr; // Set to nullptr if creation fails.
		return RlblBld_hWnd; // Return nullptr if creation fails.
	}

	// Set the font for the label.
	SendMessage(RlblBld_hWnd, WM_SETFONT, (WPARAM)hfVol, 0);

	return RlblBld_hWnd;
}

HWND Widget::LLabel(int posx, int posy, int width, int height, const char* text, HWND hWnd)
{
	HWND Llbl_hWnd = CreateWindowEx(WS_EX_LEFT, "static", text,
		WS_VISIBLE | WS_CHILD,
		posx, posy, width, height, hWnd, nullptr, nullptr, nullptr);
	HFONT hfVol = CreateFont(16, 5, 0, 0, FW_NORMAL, 0, 0, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "MS Sans Serif");

	// Error handling.
	if (!Llbl_hWnd)
	{
		MessageBox(NULL, "Failed to create left-aligned label.", "Error", MB_OK | MB_ICONERROR);
		Llbl_hWnd = nullptr; // Set to nullptr if creation fails.
		return Llbl_hWnd; // Return nullptr if creation fails.
	}

	// Set the font for the label.
	SendMessage(Llbl_hWnd, WM_SETFONT, (WPARAM)hfVol, 0);

	return Llbl_hWnd;
}

HWND Widget::LLabelBold(int posx, int posy, int width, int height, const char* text, HWND hWnd)
{
	HWND LlblBld_hWnd = CreateWindowEx(WS_EX_LEFT, "static", text,
		WS_VISIBLE | WS_CHILD,
		posx, posy, width, height, hWnd, nullptr, nullptr, nullptr);
	HFONT hfVol = CreateFont(16, 5, 0, 0, FW_BOLD, 0, 0, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "MS Sans Serif");

	// Error handling.
	if (!LlblBld_hWnd)
	{
		MessageBox(NULL, "Failed to create left-aligned bold label.", "Error", MB_OK | MB_ICONERROR);
		LlblBld_hWnd = nullptr; // Set to nullptr if creation fails.
		return LlblBld_hWnd; // Return nullptr if creation fails.
	}

	return LlblBld_hWnd;
}

HWND Widget::GroupBox(int posx, int posy, int width, int height, const char* text, HWND hWnd, HINSTANCE hInst)
{
	HWND GrpBx_hWnd = CreateWindow(
		"BUTTON",
		text,
		WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		posx, posy, width, height, hWnd, nullptr, 
		hInst, nullptr);

	// Error handling.
	if (!GrpBx_hWnd)
	{
		MessageBox(NULL, "Failed to create group box.", "Error", MB_OK | MB_ICONERROR);
		GrpBx_hWnd = nullptr; // Set to nullptr if creation fails.
		return GrpBx_hWnd; // Return nullptr if creation fails.
	}

	return GrpBx_hWnd;
}

HWND Widget::InputBox(int posx, int posy, int width, int height, HWND hWnd)
{
	HWND InptBx_hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE, "Edit", "",
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_EX_CONTROLPARENT,
		posx, posy, width, height, hWnd, NULL, NULL, NULL);

	// Error handling.
	if (!InptBx_hWnd)
	{
		MessageBox(NULL, "Failed to create input box.", "Error", MB_OK | MB_ICONERROR);
		InptBx_hWnd = nullptr; // Set to nullptr if creation fails.
		return InptBx_hWnd; // Return nullptr if creation fails.
	}

	return InptBx_hWnd;
}

HWND Widget::InputBoxMulti(int posx, int posy, int width, int height, HWND hWnd)
{
	HWND InptBx_hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE, "Edit", NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_MULTILINE,
		posx, posy, width, height, hWnd, NULL, NULL, NULL);

	// Error handling.
	if (!InptBx_hWnd)
	{
		MessageBox(NULL, "Failed to create multi-line input box.", "Error", MB_OK | MB_ICONERROR);
		InptBx_hWnd = nullptr; // Set to nullptr if creation fails.
		return InptBx_hWnd; // Return nullptr if creation fails.
	}

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

	// Error handling.
	if (!CmbBx_hWnd)
	{
		MessageBox(NULL, "Failed to create combo box.", "Error", MB_OK | MB_ICONERROR);
		CmbBx_hWnd = nullptr; // Set to nullptr if creation fails.
		return CmbBx_hWnd; // Return nullptr if creation fails.
	}

	return CmbBx_hWnd;
}

HWND Widget::ComboBoxID(int posx, int posy, int width, int height, const char* text, HWND hWnd, HMENU id, HINSTANCE hInst)
{
	HWND CmbBx_hWnd = CreateWindow(
		"COMBOBOX",
		text,
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
		posx, posy, width, height, hWnd, id, hInst, nullptr);

	// Error handling.
	if (!CmbBx_hWnd)
	{
		MessageBox(NULL, "Failed to create combo box with ID.", "Error", MB_OK | MB_ICONERROR);
		CmbBx_hWnd = nullptr; // Set to nullptr if creation fails.
		return CmbBx_hWnd; // Return nullptr if creation fails.
	}

	return CmbBx_hWnd;
}

HWND Widget::Button(int posx, int posy, int width, int height, const char* text, HWND hWnd, HMENU option)
{
	HWND Btn_hWnd = CreateWindow(
		"BUTTON",
		text,
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		posx, posy, width, height, 
		hWnd, option, 
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		nullptr);

	// Error handling.
	if (!Btn_hWnd)
	{
		MessageBox(NULL, "Failed to create button.", "Error", MB_OK | MB_ICONERROR);
		Btn_hWnd = nullptr; // Set to nullptr if creation fails.
		return Btn_hWnd; // Return nullptr if creation fails.
	}

	return Btn_hWnd;
}

HWND Widget::ButtonDef(int posx, int posy, int width, int height, const char* text, HWND hWnd, HMENU option)
{
	HWND btnDef_hWnd = CreateWindow(
		"BUTTON",
		text,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
		posx, posy, width, height, hWnd, option, nullptr, nullptr);

	// Error handling.
	if (!btnDef_hWnd)
	{
		MessageBox(NULL, "Failed to create default button.", "Error", MB_OK | MB_ICONERROR);
		btnDef_hWnd = nullptr; // Set to nullptr if creation fails.
		return btnDef_hWnd; // Return nullptr if creation fails.
	}

	return btnDef_hWnd;
}

HWND Widget::ButtonRadio(int posx, int posy, int width, int height, const char* text, HWND hWnd, HMENU option)
{
	HWND btnRad_hWnd = CreateWindow(
		"BUTTON",
		text,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTORADIOBUTTON,
		posx, posy, width, height, hWnd, option, nullptr, nullptr);

	// Error handling.
	if (!btnRad_hWnd)
	{
		MessageBox(NULL, "Failed to create radio button.", "Error", MB_OK | MB_ICONERROR);
		btnRad_hWnd = nullptr; // Set to nullptr if creation fails.
		return btnRad_hWnd; // Return nullptr if creation fails.
	}

	return btnRad_hWnd;
}

HWND Widget::ResultBox(int posx, int posy, int width, int height, HWND hWnd)
{
	HWND Rslt_hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE, "static", "",
		WS_VISIBLE | WS_CHILD,
		posx, posy, width, height, hWnd, nullptr, nullptr, nullptr);

	// Error handling.
	if (!Rslt_hWnd)
	{
		MessageBox(NULL, "Failed to create result box.", "Error", MB_OK | MB_ICONERROR);
		Rslt_hWnd = nullptr; // Set to nullptr if creation fails.
		return Rslt_hWnd; // Return nullptr if creation fails.
	}

	return Rslt_hWnd;
}

HWND Widget::MsgBox(int posx, int posy, int width, int height, HWND hWnd, HMENU option)
{
	HWND Msg_hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE, "static", "",
		WS_VISIBLE | WS_CHILD,
		posx, posy, width, height, hWnd, option, nullptr, nullptr);

	// Error handling.
	if (!Msg_hWnd)
	{
		MessageBox(NULL, "Failed to create message box.", "Error", MB_OK | MB_ICONERROR);
		Msg_hWnd = nullptr; // Set to nullptr if creation fails.
		return Msg_hWnd; // Return nullptr if creation fails.
	}

	return Msg_hWnd;
}

HWND Widget::ImageStatic(int posx, int posy, int width, int height, const char* text, HWND hWnd, HBITMAP hImage, HINSTANCE hInst)
{
	HWND ImgSt_hWnd = CreateWindow(
		"static",
		text,
		 WS_VISIBLE | WS_CHILD | SS_BITMAP,
		posx, posy, width, height, hWnd, nullptr, hInst, nullptr);

	// Error handling.
	if (!ImgSt_hWnd)
	{
		MessageBox(NULL, "Failed to create static image.", "Error", MB_OK | MB_ICONERROR);
		ImgSt_hWnd = nullptr; // Set to nullptr if creation fails.
		return ImgSt_hWnd; // Return nullptr if creation fails.
	}

	SendMessage(ImgSt_hWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);

	return ImgSt_hWnd;
}

HWND Widget::ImageBtn(int posx, int posy, int width, int height, const char* text, HWND hWnd, HBITMAP hImage, HMENU option)
{
	HWND ImgBtn_hWnd = CreateWindow(
		"BUTTON",
		text,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_BITMAP,
		posx, posy, width, height, hWnd, option, nullptr, nullptr);

	// Error handling.
	if (!ImgBtn_hWnd)
	{
		MessageBox(NULL, "Failed to create image button.", "Error", MB_OK | MB_ICONERROR);
		ImgBtn_hWnd = nullptr; // Set to nullptr if creation fails.
		return ImgBtn_hWnd; // Return nullptr if creation fails.
	}

	SendMessage(ImgBtn_hWnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);

	return ImgBtn_hWnd;
}

HBITMAP Widget::LoadBitmapImage(HWND hWnd, const char* fileName, int width, int height)
{
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, width, height, 
		LR_LOADFROMFILE| LR_DEFAULTCOLOR | LR_LOADTRANSPARENT |LR_CREATEDIBSECTION
	);

	if (hBitmap == NULL)
	{
		MessageBox(hWnd, "Failed to load image.", "Error", MB_OK | MB_ICONERROR);
		return hBitmap;
	}

	// Set the bitmap to the static control
	//SendMessage(hWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);

	return hBitmap;
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

INT_PTR Widget::StaticModalDialog(HWND hParent, const char* title, const char* message,
	const char* imagePath, int width, int height)
{
	// Register dialog class
	static bool classRegistered = false;
	if (!classRegistered)
	{
		WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
		wcex.lpfnWndProc = DefDlgProc;
		wcex.hInstance = GetModuleHandle(NULL);
		wcex.lpszClassName = "StaticModalDialogClass";
		wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
		wcex.style = CS_DBLCLKS;
		RegisterClassEx(&wcex);
		classRegistered = true;
	}

	// Create dialog template in memory
	DLGTEMPLATE* pDlgTemplate;

	//LPWORD lpw;
	//LPWSTR lpwsz;
	//int nchar;

	pDlgTemplate = (DLGTEMPLATE*)GlobalAlloc(GPTR, sizeof(DLGTEMPLATE));

	if (!pDlgTemplate) 
		return -1;

	// Define dialog template
	pDlgTemplate->style = WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | DS_MODALFRAME; // | DS_CENTER;
	pDlgTemplate->dwExtendedStyle = 0;
	pDlgTemplate->cdit = 0;
	pDlgTemplate->x = 50;	// Position of the dialog on the screen.
	pDlgTemplate->y = 50;
	pDlgTemplate->cx = width;
	pDlgTemplate->cy = height;
	
	// Initialize dialog data.
	DialogData dlgData = 
	{ 
		title, 
		message, 
		imagePath, 
		width, 
		height 
	};

	// Create and show the dialog
	INT_PTR result = DialogBoxIndirectParam(
		GetModuleHandle(NULL),
		pDlgTemplate,
		hParent,
		VolWndDlgProc,
		(LPARAM)&dlgData
	);

	GlobalFree(pDlgTemplate);	// Free the dialog template memory.

	return result;

}



