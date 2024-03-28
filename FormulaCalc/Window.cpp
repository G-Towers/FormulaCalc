// Window.cpp

#include "Window.h"
#include "VolWnd.h"
#include "WinMsgMap.h"

BOOL VolWnd::wndCreated = 0;
VolWnd* pVolWnd = nullptr;
VolWnd* VolWnd::inst = nullptr;
HINSTANCE hInst = GetModuleHandle(NULL);

//pVolWnd = reinterpret_cast<VolWnd*>(GetWindowLongPtr(VolWnd::volObj.GetWinHandle(), GWLP_USERDATA));

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;

	}
	return (INT_PTR)FALSE;
}

// Message handler for Info box.
INT_PTR CALLBACK Info(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;

	}
	return (INT_PTR)FALSE;
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//// Print wParam and lParam to immediate window.
	//static WinMsgMap mm;
	//OutputDebugString(mm(uMsg, wParam, lParam).c_str());

	int wmId = LOWORD(wParam);

	switch (uMsg)
	{
	case WM_COMMAND:
	{
		// Combo box.
		ComboBoxCommand(m_hWnd, uMsg, wParam, lParam);

		// Parse the menu selections:
		switch (wmId)
		{
		case ID_HELP_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), m_hWnd, About);
			break;

		case ID_HELP_INFO:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), m_hWnd, Info);
			break;

		case ID_CALCULATE_VOLUME:
			VolWnd::volObj.VolumeWnd();	
			break;

		case ID_FILE_EXIT:
			if (MessageBox(m_hWnd, " Are you sure you want to quit?", "Quit?", MB_OKCANCEL | MB_ICONEXCLAMATION) == IDOK)
			{
				PostQuitMessage(0);
			}
			return 0;

		default:
			return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
		}
	}
	break;

	case WM_CREATE:
		// Call to the interface function.
		MainInterface(m_hWnd, GetModuleHandle(NULL));
		break;
	case WM_SETFOCUS:
		SetFocus(m_hWnd);
		break;
	case WM_CLOSE:

		// Post a WM_CLOSE message to the window
		//PostMessage(m_hWnd, WM_CLOSE, 0, 0);
		//if (VolWnd::wndCreated)
		//{
		//	PostMessage(pVolWnd->GetWinHandle(), WM_CLOSE, 0, 0);
		//}
		//	//MessageBox(m_hWnd, "Window Open", "Please close Volume to continue.", MB_OK);
		//else
		PostQuitMessage(0);
		return 0;
	//case WM_DESTROY:
		//if (IsWindowVisible(VolWnd::volObj.GetWinHandle()))
		//{
		//	MessageBox(m_hWnd, "Window Open", "Please close Volume to continue.", MB_OK);
		//}

		//PostQuitMessage(0);

		//return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(m_hWnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)CreateSolidBrush(RGB(220, 220, 255)));
		EndPaint(m_hWnd, &ps);
	}

	return 0;

	//default:
		
	}
	return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
	//return TRUE;
}

void MainWindow::MainInterface(const HWND& hWnd, const HINSTANCE hInst)
{
	HWND hComboBoxSelItem = Widget::ComboBox(25, 25, 265, 150, "", hWnd, hInst);	// The combobox window.
	ComboBoxList(hComboBoxSelItem);	// Items in the combobox.
	HWND hRadBut = Widget::ButtonRadio(120, 120, 80, 30, "Button", hWnd);
}

void MainWindow::ComboBoxList(HWND hWnd)
{
	// Item list for combobox.
	const char itemList[3][50] =
	{
		"Item 1",
		"Item 2",
		"Item 3"

	};

	char itemBuff[80];		// Buffer for comboBox list.

	memset(&itemBuff, 0, sizeof(itemBuff));   // Allocate memory for the tube buffer and set to 0.

	for (int k = 0; k <= 2; k++)	// Traverse the array.
	{
		strcpy_s(itemBuff, sizeof(itemBuff) / sizeof(char), (char*)itemList[k]);

		// Add string to combobox.
		// Load the combobox with item list.  
		// Send a CB_ADDSTRING message to load each item.
		SendMessage(hWnd, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)itemBuff);
	}

	// Send the CB_SETCURSEL message to display an initial item 
	// in the selection field.
	SendMessage(hWnd, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
}

void MainWindow::ComboBoxCommand(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//MSG volMsg = { 0 };
	//BOOL gResult;

	char Item1[100] = "";
	char Item2[100] = "";
	char Item3[100] = "";

	// Retrieve the pointer
	//pVolWnd = reinterpret_cast<VolWnd*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	//pVolWnd = reinterpret_cast<VolWnd*>(GetWindowLongPtr(hWnd, GWLP_WNDPROC));


	// ComboBox
	if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == 0)	// Why does this work???
		// If the user makes a selection from the list:
		//   Send CB_GETCURSEL message to get the index of the selected list item.
		//   Send CB_GETLBTEXT message to get the item.
		//   Display the item in a messagebox.
	{
		int ItemIndex = (UINT)SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
			(WPARAM)0, (LPARAM)0);
		const char* ListItem[256] = { 0 };
		(TCHAR)SendMessage((HWND)lParam, (UINT)CB_GETLBTEXT,
			(WPARAM)ItemIndex, (LPARAM)ListItem);

		if (ItemIndex == (WPARAM)1)
		{
			//OutputDebugString(mm(msg, wParam, lParam).c_str());
			//SetWindowText(hWnd, Item2);
			//ShowWindow(Window(), SW_SHOW);

			MessageBox(hWnd, "Item 2 Selected.", (LPCSTR)ListItem, MB_OK);
		}

		else if (ItemIndex == (WPARAM)2)
		{
			//SetWindowText(hWnd, Item3);
			MessageBox(hWnd, "Item 3 Selected", (LPCSTR)ListItem, MB_OK);
			//WinObject();
			//WinFunction();
			//{
				// Singleton instantiation.
				//VolWnd& volumeWin = VolWnd::instVolWnd();

				//if (VolWnd::volObj.wndCreated)
				//	SetFocus(VolWnd::volObj.GetWinHandle());
				//else
				//{
				//	VolWnd::volObj.CreateWnd("Volume Window", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE, 
				//		0, 250, 250, 480, 350, GetParent(hWnd));
				//	ShowWindow(VolWnd::volObj.GetWinHandle(), SW_SHOW);
				//	VolWnd::volObj.wndCreated = 1;

					// Extract ptr to window class from creation data.
					//const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
					//pVolWnd = static_cast<VolWnd*>(pCreate->lpCreateParams);
					// Set WinAPI-managed user data to store ptr to window class.
					//SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pVolWnd));

					//while ((gResult = GetMessage(&volMsg, NULL, 0, 0)) > 0)
					//{
					//	// To use tabstops.
					//	if (!IsDialogMessage(volumeWin.GetWinHandle(), &volMsg))
					//	{
					//		TranslateMessage(&volMsg);
					//		DispatchMessage(&volMsg);
					//	}
					//}
					//return (int)volMsg.wParam;
				//}
			//}
		}
		else
		{
			//SetWindowText(hWnd, Item1);	
			MessageBox(hWnd, "Item 1 Selected.", (LPCSTR)ListItem, MB_OK);
		}

	}
}




