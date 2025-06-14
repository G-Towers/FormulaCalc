// Window.cpp

#include "Window.h"
#include "VolWnd.h"
#include "StanDev.h"
#include "QuadForm.h"
#include "Diff.h"
#include "Integrate.h"
#include "FinLoan.h"
#include "CompInt.h"
#include "WinMsgMap.h"

HINSTANCE hInst = GetModuleHandle(NULL);

// Global vector to hold StanDev windows.
std::vector<StanDev*> stanDevWindows;	// Holds multiple instances of StanDev windows.

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
			VolWnd::InstVolWnd().VolumeWnd();
			break;

		case ID_STATISTICS_STANDARDDEVIATION:
		{
			StanDev* newStanDev = new StanDev();
			newStanDev->StanDevWnd();
			stanDevWindows.push_back(newStanDev);
			break;
		}

		case ID_ALGEBRA_QUADRATICFORMULA:
			QuadForm::InstQuadFormWnd().QuadFormWnd();
			break;

		case ID_CALCULUS_DIFFRENTIATION:
			Diff::InstDiffWnd().DiffWnd();
			break;

		case ID_CALCULUS_INTEGRATION:
			Integrate::InstIntegrateWnd().IntegrateWnd();
			break;

		case ID_FINANCE_COMPOUNDINTEREST:
			CompInt::InstCompIntWnd().CompIntWnd();
			break;

		case ID_FINANCE_LOAN:
			FinLoan::InstFinLoanWnd().FinLoanWnd();
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

		PostQuitMessage(0);
		return 0;
	case WM_DESTROY:

		PostQuitMessage(0);

		return 0;
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

	memset(&itemBuff, 0, sizeof(itemBuff));   // Allocate memory for the buffer and set to 0.

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
	//BOOL gResult;

	char Item1[100] = "";
	char Item2[100] = "";
	char Item3[100] = "";


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

		}
		else
		{
			//SetWindowText(hWnd, Item1);	
			MessageBox(hWnd, "Item 1 Selected.", (LPCSTR)ListItem, MB_OK);
		}

	}
}




