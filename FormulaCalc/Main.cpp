// Window using classes.

//#ifndef UNICODE
//#define UNICODE
//#endif

#include "Window.h"
#include "VolWnd.h"
#include "resource.h"

extern MSG msg;
//extern VolWnd* pVolWnd;

int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	try
	{
		MainWindow mainWin;

		mainWin.CreateWnd("Main Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 150, 150, 500, 500, 
			 NULL, (HMENU)IDR_MENU1);

		ShowWindow(mainWin.GetWinHandle(), nCmdShow);

		// Run the message loop.
		MSG msg = { 0 };
		BOOL gResult;

		while ((gResult = GetMessage(&msg, NULL, 0, 0)) > 0)
		{
			//TranslateMessage(&msg); // Translate virtual-key messages into character messages.
			//DispatchMessage(&msg);  // Send message to windows procedure.

			// To use tabstops.
			if (!IsDialogMessage(VolWnd::volObj.GetWinHandle(), &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		// Check GetMessage for error.
		if (gResult == -1)
		{
			throw GTWND_LAST_EXCEPT();
		}

		// wParam here is the value passed to PostQuitMessage.
		return (int)msg.wParam;
	}
	catch (const GTException& e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}

	return -1;


}