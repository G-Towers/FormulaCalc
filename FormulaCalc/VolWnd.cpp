// VolWnd.cpp

#include "VolWnd.h"
#include "WinMsgMap.h"

BOOL VolWnd::volWndCreated = 0;

const double PI = 3.141592654;

MSG msg;

VolWnd::VolWnd()
{
	defaultInterface = 0;
	length = 0.0;
	base = 0.0;
	height = 0.0;
	width = 0.0;
	radius = 0.0;
	lowRadius = 0.0;
	result = 0.0;

	hLengthLabel = nullptr;
	hBaseLabel = nullptr;
	hWidthLabel = nullptr;
	hHeightLabel = nullptr;
	hRadiusLabel = nullptr;
	hLowRadiusLabel = nullptr;
	hResultLabel = nullptr;

	hComboBoxSelItem = nullptr;

	hLengthBox = nullptr;
	hBaseBox = nullptr;
	hWidthBox = nullptr;
	hHeightBox = nullptr;
	hRadiusBox = nullptr;
	hLowRadiusBox = nullptr;
	hResultBox = nullptr;

	hTriCalcBtn = nullptr;
	hRectCalcBtn = nullptr;
	hSphereCalcBtn = nullptr;
	hCylinderCalcBtn = nullptr;
	hConeCalcBtn = nullptr;
	hFrusConeCalcBtn = nullptr;
	hPyramidCalcBtn = nullptr;

	hClearBtn = nullptr;
	hCloseBtn = nullptr;
}

VolWnd::~VolWnd()
{
	// Destroy all owned windows/controls
	SafeDestroyWindow(hLengthLabel);
	SafeDestroyWindow(hBaseLabel);
	SafeDestroyWindow(hWidthLabel);
	SafeDestroyWindow(hHeightLabel);
	SafeDestroyWindow(hRadiusLabel);
	SafeDestroyWindow(hLowRadiusLabel);

	SafeDestroyWindow(hResultLabel);

	SafeDestroyWindow(hComboBoxSelItem);

	SafeDestroyWindow(hLengthBox);
	SafeDestroyWindow(hBaseBox);
	SafeDestroyWindow(hWidthBox);
	SafeDestroyWindow(hHeightBox);
	SafeDestroyWindow(hRadiusBox);
	SafeDestroyWindow(hLowRadiusBox);

	SafeDestroyWindow(hResultBox);

	SafeDestroyWindow(hTriCalcBtn);
	SafeDestroyWindow(hRectCalcBtn);
	SafeDestroyWindow(hSphereCalcBtn);
	SafeDestroyWindow(hCylinderCalcBtn);
	SafeDestroyWindow(hConeCalcBtn);
	SafeDestroyWindow(hFrusConeCalcBtn);
	SafeDestroyWindow(hPyramidCalcBtn);

	SafeDestroyWindow(hClearBtn);
	SafeDestroyWindow(hCloseBtn);

	// Clear any maps or containers
	msgBxStrMap.clear();

}

LRESULT CALLBACK VolWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Print wParam and lParam to immediate window.
	// Becareful with this, it causes a crash when closing the main window.
	//static WinMsgMap mm;
	//OutputDebugString(mm(uMsg, wParam, lParam).c_str());

	int wmId = LOWORD(wParam);

	switch (uMsg)
	{
	case WM_COMMAND:
	{
		VolWnd::ComboBoxCommand(m_hWnd, uMsg, wParam, lParam);

		switch (wmId)
		{
		case VOLUME_CALCULATE_TRI_BUTTON:
			VolumeInputThunk(this, &VolWnd::CalcVolTriangle);
			break;
		case VOLUME_CALCULATE_RECT_BUTTON:
			VolumeInputThunk(this, &VolWnd::CalcVolRectangle);
			break;
		case VOLUME_CALCULATE_SPHERE_BUTTON:
			VolumeInputThunk(this, &VolWnd::CalcVolSphere);
			break;
		case VOLUME_CALCULATE_CYLINDER_BUTTON:
			VolumeInputThunk(this, &VolWnd::CalcVolCylinder);
			break;
		case VOLUME_CALCULATE_CONE_BUTTON:
			VolumeInputThunk(this, &VolWnd::CalcVolCone);
			break;
		case VOLUME_CALCULATE_FRUSTUM_BUTTON:
			VolumeInputThunk(this, &VolWnd::CalcVolFrustum);
			break;
		case VOLUME_CALCULATE_PYRAMID_BUTTON:
			VolumeInputThunk(this, &VolWnd::CalcVolPyramid);
			break;
		case VOLUME_CLEAR_BUTTON:
			ClearVolumeText();
			break;
		case VOLUME_CLOSE_BUTTON:
			DestroyWindow(m_hWnd);
			//UnregisterClass("VolWndClass", GetModuleHandle(NULL));
			break;
		}
	}
	break;
	case WM_CREATE:
		// Call to the interface function.
		//Interface::MainInterface(m_hWnd, GetModuleHandle(NULL));
		VolumeInterface();
		//VolTriInterface();
		break;
	case WM_SETFOCUS:
		SetFocus(InstVolWnd().hLengthBox);
		break;

	//case WM_GETDLGCODE:
	//	return DLGC_WANTTAB;

	//case WM_KEYDOWN:
	//	if (IsDialogMessage(volObj.GetWinHandle(), (LPMSG)&uMsg)) // call IsDialogMessage with the window handle and the message
	//	{
	//		return 0; // the message has been processed by IsDialogMessage
	//	}
	//	switch (wParam)
	//	{
	//	case VK_TAB:

	//		break;
	//	}

	//	break;
		
	case WM_DESTROY:
		//DestroyWindow(m_hWnd);
		UnregisterClass("VolWndClass", GetModuleHandle(NULL));
		volWndCreated = 0;
		//PostQuitMessage(0);
		return 0;

	//case WM_CLOSE:
	//	PostQuitMessage(0);
	//	return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(m_hWnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
		EndPaint(m_hWnd, &ps);
	}

	return 0;

	//default:
		
	}

	return DefWindowProc(m_hWnd, uMsg, wParam, lParam);

	//return TRUE;
}

VolWnd& VolWnd::InstVolWnd()
{
	static VolWnd inst;
	return inst;
}

HINSTANCE VolWnd::GetInstance() noexcept
{
	return InstVolWnd().hInst;
}

void VolWnd::VolumeWnd()
{

	if (volWndCreated)
		SetFocus(m_hWnd);
	else
	{
		CreateWnd("Volume", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE,
			0, 250, 250, 480, 350, GetParent(m_hWnd));
		ShowWindow(m_hWnd, SW_SHOW);
		volWndCreated = 1;
	}

}

void VolWnd::VolumeInterface()
{
	// To get the handle to a dialog box.
	//HWND hVolDlg = GetDlgItem(NULL, IDD_VOLUME_DIALOG);

	hComboBoxSelItem = Widget::ComboBox(25, 25, 175, 150, "", m_hWnd, GetModuleHandle(NULL));	// The combobox window.
	//ComboBoxList(hComboBoxSelItem);	// Items in the combobox.
	VolumeDlgList(m_hWnd);

	// Text labels.
	hLengthLabel = Widget::RLabel(60, 85, 50, 25, "Length:", m_hWnd);
	hBaseLabel = Widget::RLabel(60, 125, 50, 25, "Base:", m_hWnd);
	hWidthLabel = Widget::RLabel(60, 125, 50, 25, "Width:", m_hWnd);
	hHeightLabel = Widget::RLabel(60, 165, 50, 25, "Height:", m_hWnd);
	hRadiusLabel = Widget::RLabel(60, 85, 50, 25, "Radius:", m_hWnd);
	hLowRadiusLabel = Widget::RLabel(60, 115, 50, 30, "Lower Radius:", m_hWnd);
	hResultLabel = Widget::RLabel(60, 215, 50, 25, "Result:", m_hWnd);

	// Input boxes.
	hLengthBox = Widget::InputBox(120, 80, 150, 25, m_hWnd);
	hBaseBox = Widget::InputBox(120, 120, 150, 25, m_hWnd);
	hHeightBox = Widget::InputBox(120, 160, 150, 25, m_hWnd);
	hWidthBox = Widget::InputBox(120, 120, 150, 25, m_hWnd);
	hRadiusBox = Widget::InputBox(120, 80, 150, 25, m_hWnd);
	hLowRadiusBox = Widget::InputBox(120, 120, 150, 25, m_hWnd);
	hResultBox = Widget::ResultBox(120, 210, 150, 25, m_hWnd);

	// Buttons.
	hTriCalcBtn = Widget::Button(320, 140, 90, 30, "Calculate", m_hWnd, (HMENU)VOLUME_CALCULATE_TRI_BUTTON);
	hRectCalcBtn = Widget::Button(320, 140, 90, 30, "Calculate", m_hWnd, (HMENU)VOLUME_CALCULATE_RECT_BUTTON);
	hSphereCalcBtn = Widget::Button(320, 140, 90, 30, "Calculate", m_hWnd, (HMENU)VOLUME_CALCULATE_SPHERE_BUTTON);
	hCylinderCalcBtn = Widget::Button(320, 140, 90, 30, "Calculate", m_hWnd, (HMENU)VOLUME_CALCULATE_CYLINDER_BUTTON);
	hConeCalcBtn = Widget::Button(320, 140, 90, 30, "Calculate", m_hWnd, (HMENU)VOLUME_CALCULATE_CONE_BUTTON);
	hFrusConeCalcBtn = Widget::Button(320, 140, 90, 30, "Calculate", m_hWnd, (HMENU)VOLUME_CALCULATE_FRUSTUM_BUTTON);
	hPyramidCalcBtn = Widget::Button(320, 140, 90, 30, "Calculate", m_hWnd, (HMENU)VOLUME_CALCULATE_PYRAMID_BUTTON);

	hClearBtn = Widget::Button(320, 190, 90, 30, "Clear", m_hWnd, (HMENU)VOLUME_CLEAR_BUTTON);
	hCloseBtn = Widget::Button(350, 260, 90, 30, "Close", m_hWnd, (HMENU)VOLUME_CLOSE_BUTTON);

	if (defaultInterface == 0)
	{
		// Show the default interface.
		VolTriInterface();
		defaultInterface = 1;

		// Set focus to the first input box.
		SetFocus(hLengthBox);
	}
}

void VolWnd::VolTriInterface()
{
	// Text labels.
	ShowWindow(hLengthLabel, SW_SHOW);
	ShowWindow(hBaseLabel, SW_SHOW);
	ShowWindow(hHeightLabel, SW_SHOW);

	// Input boxes.
	ShowWindow(hLengthBox, SW_SHOW);
	ShowWindow(hBaseBox, SW_SHOW);
	ShowWindow(hHeightBox, SW_SHOW);

	// Calculate.
	ShowWindow(hTriCalcBtn, SW_SHOW);

	// Hide other controls.
	ShowWindow(hWidthLabel, SW_HIDE);
	ShowWindow(hRadiusLabel, SW_HIDE);
	ShowWindow(hLowRadiusLabel, SW_HIDE);
	
	ShowWindow(hWidthBox, SW_HIDE);
	ShowWindow(hRadiusBox, SW_HIDE);
	ShowWindow(hLowRadiusBox, SW_HIDE);
	
	ShowWindow(hRectCalcBtn, SW_HIDE);
	ShowWindow(hSphereCalcBtn, SW_HIDE);
	ShowWindow(hCylinderCalcBtn, SW_HIDE);
	ShowWindow(hConeCalcBtn, SW_HIDE);
	ShowWindow(hFrusConeCalcBtn, SW_HIDE);
	ShowWindow(hPyramidCalcBtn, SW_HIDE);


}

void VolWnd::VolRectInterface()
{
	// Text labels.
	ShowWindow(hLengthLabel, SW_SHOW);
	ShowWindow(hWidthLabel, SW_SHOW);
	ShowWindow(hHeightLabel, SW_SHOW);

	// Input boxes.
	ShowWindow(hLengthBox, SW_SHOW);
	ShowWindow(hWidthBox, SW_SHOW);
	ShowWindow(hHeightBox, SW_SHOW);

	// Calculate.
	ShowWindow(hRectCalcBtn, SW_SHOW);

	// Hide other controls.
	ShowWindow(hBaseLabel, SW_HIDE);
	ShowWindow(hRadiusLabel, SW_HIDE);
	ShowWindow(hLowRadiusLabel, SW_HIDE);
	
	ShowWindow(hBaseBox, SW_HIDE);
	ShowWindow(hRadiusBox, SW_HIDE);
	ShowWindow(hLowRadiusBox, SW_HIDE);

	ShowWindow(hTriCalcBtn, SW_HIDE);
	ShowWindow(hSphereCalcBtn, SW_HIDE);
	ShowWindow(hCylinderCalcBtn, SW_HIDE);
	ShowWindow(hConeCalcBtn, SW_HIDE);
	ShowWindow(hFrusConeCalcBtn, SW_HIDE);
	ShowWindow(hPyramidCalcBtn, SW_HIDE);
		
}

void VolWnd::VolSphereInterface()
{
	// Text labels.
	ShowWindow(hRadiusLabel, SW_SHOW);

	// Input boxes.
	ShowWindow(hRadiusBox, SW_SHOW);

	// Calculate.
	ShowWindow(hSphereCalcBtn, SW_SHOW);

	// Hide other controls.
	ShowWindow(hLengthLabel, SW_HIDE);
	ShowWindow(hBaseLabel, SW_HIDE);
	ShowWindow(hWidthLabel, SW_HIDE);
	ShowWindow(hHeightLabel, SW_HIDE);
	
	ShowWindow(hLengthBox, SW_HIDE);
	ShowWindow(hBaseBox, SW_HIDE);
	ShowWindow(hWidthBox, SW_HIDE);
	ShowWindow(hHeightBox, SW_HIDE);
		
	ShowWindow(hTriCalcBtn, SW_HIDE);
	ShowWindow(hRectCalcBtn, SW_HIDE);
	ShowWindow(hCylinderCalcBtn, SW_HIDE);
	ShowWindow(hConeCalcBtn, SW_HIDE);
	ShowWindow(hFrusConeCalcBtn, SW_HIDE);
	ShowWindow(hPyramidCalcBtn, SW_HIDE);

}

void VolWnd::VolCylinderInterface()
{
	// Text labels.
	ShowWindow(hRadiusLabel, SW_SHOW);
	ShowWindow(hHeightLabel, SW_SHOW);

	// Input boxes.
	ShowWindow(hRadiusBox, SW_SHOW);
	ShowWindow(hHeightBox, SW_SHOW);

	// Calculate.
	ShowWindow(hCylinderCalcBtn, SW_SHOW);

	// Hide other controls.
	ShowWindow(hLengthLabel, SW_HIDE);
	ShowWindow(hBaseLabel, SW_HIDE);
	ShowWindow(hWidthLabel, SW_HIDE);
	ShowWindow(hLowRadiusLabel, SW_HIDE);

	ShowWindow(hLengthBox, SW_HIDE);
	ShowWindow(hBaseBox, SW_HIDE);
	ShowWindow(hWidthBox, SW_HIDE);
	ShowWindow(hLowRadiusBox, SW_HIDE);

	ShowWindow(hTriCalcBtn, SW_HIDE);
	ShowWindow(hRectCalcBtn, SW_HIDE);
	ShowWindow(hSphereCalcBtn, SW_HIDE);
	ShowWindow(hConeCalcBtn, SW_HIDE);
	ShowWindow(hFrusConeCalcBtn, SW_HIDE);
	ShowWindow(hPyramidCalcBtn, SW_HIDE);

}

void VolWnd::VolConeInterface()
{
	// Text labels.
	ShowWindow(hRadiusLabel, SW_SHOW);
	ShowWindow(hHeightLabel, SW_SHOW);

	// Input boxes.
	ShowWindow(hRadiusBox, SW_SHOW);
	ShowWindow(hHeightBox, SW_SHOW);

	// Calculate.
	ShowWindow(hConeCalcBtn, SW_SHOW);

	// Hide other controls.
	ShowWindow(hLengthLabel, SW_HIDE);
	ShowWindow(hBaseLabel, SW_HIDE);
	ShowWindow(hWidthLabel, SW_HIDE);
	ShowWindow(hLowRadiusLabel, SW_HIDE);

	ShowWindow(hLengthBox, SW_HIDE);
	ShowWindow(hBaseBox, SW_HIDE);
	ShowWindow(hWidthBox, SW_HIDE);
	ShowWindow(hLowRadiusBox, SW_HIDE);

	ShowWindow(hTriCalcBtn, SW_HIDE);
	ShowWindow(hRectCalcBtn, SW_HIDE);
	ShowWindow(hSphereCalcBtn, SW_HIDE);
	ShowWindow(hCylinderCalcBtn, SW_HIDE);
	ShowWindow(hFrusConeCalcBtn, SW_HIDE);
	ShowWindow(hPyramidCalcBtn, SW_HIDE);

}

void VolWnd::VolFrusConeInterface()
{
	// Text labels.
	ShowWindow(hRadiusLabel, SW_SHOW);
	ShowWindow(hLowRadiusLabel, SW_SHOW);
	ShowWindow(hHeightLabel, SW_SHOW);

	// Input boxes.
	ShowWindow(hRadiusBox, SW_SHOW);
	ShowWindow(hLowRadiusBox, SW_SHOW);
	ShowWindow(hHeightBox, SW_SHOW);

	// Calculate.
	ShowWindow(hFrusConeCalcBtn, SW_SHOW);

	// Hide other controls.
	ShowWindow(hLengthLabel, SW_HIDE);
	ShowWindow(hBaseLabel, SW_HIDE);
	ShowWindow(hWidthLabel, SW_HIDE);

	ShowWindow(hLengthBox, SW_HIDE);
	ShowWindow(hBaseBox, SW_HIDE);
	ShowWindow(hWidthBox, SW_HIDE);

	ShowWindow(hTriCalcBtn, SW_HIDE);
	ShowWindow(hRectCalcBtn, SW_HIDE);
	ShowWindow(hSphereCalcBtn, SW_HIDE);
	ShowWindow(hCylinderCalcBtn, SW_HIDE);
	ShowWindow(hConeCalcBtn, SW_HIDE);
	ShowWindow(hPyramidCalcBtn, SW_HIDE);
}

void VolWnd::VolPyramidInterface()
{
	// Text labels.
	ShowWindow(hBaseLabel, SW_SHOW);
	ShowWindow(hHeightLabel, SW_SHOW);

	// Input boxes.
	ShowWindow(hBaseBox, SW_SHOW);
	ShowWindow(hHeightBox, SW_SHOW);

	// Calculate.
	ShowWindow(hPyramidCalcBtn, SW_SHOW);

	// Hide other controls.
	ShowWindow(hLengthLabel, SW_HIDE);
	ShowWindow(hWidthLabel, SW_HIDE);
	ShowWindow(hRadiusLabel, SW_HIDE);
	ShowWindow(hLowRadiusLabel, SW_HIDE);

	ShowWindow(hLengthBox, SW_HIDE);
	ShowWindow(hWidthBox, SW_HIDE);
	ShowWindow(hRadiusBox, SW_HIDE);
	ShowWindow(hLowRadiusBox, SW_HIDE);

	ShowWindow(hTriCalcBtn, SW_HIDE);
	ShowWindow(hRectCalcBtn, SW_HIDE);
	ShowWindow(hSphereCalcBtn, SW_HIDE);
	ShowWindow(hCylinderCalcBtn, SW_HIDE);
	ShowWindow(hConeCalcBtn, SW_HIDE);
	ShowWindow(hFrusConeCalcBtn, SW_HIDE);


}

void VolWnd::HideInputControls()
{
	// Labels.
	ShowWindow(hLengthLabel, SW_HIDE);
	ShowWindow(hBaseLabel, SW_HIDE);
	ShowWindow(hWidthLabel, SW_HIDE);
	ShowWindow(hHeightLabel, SW_HIDE);
	ShowWindow(hRadiusLabel, SW_HIDE);
	ShowWindow(hLowRadiusLabel, SW_HIDE);

	// Input boxes.
	ShowWindow(hLengthBox, SW_HIDE);
	ShowWindow(hBaseBox, SW_HIDE);
	ShowWindow(hWidthBox, SW_HIDE);
	ShowWindow(hHeightBox, SW_HIDE);
	ShowWindow(hRadiusBox, SW_HIDE);
	ShowWindow(hLowRadiusBox, SW_HIDE);

	// Buttons.
	ShowWindow(hTriCalcBtn, SW_HIDE);
	ShowWindow(hRectCalcBtn, SW_HIDE);
	ShowWindow(hSphereCalcBtn, SW_HIDE);
	ShowWindow(hCylinderCalcBtn, SW_HIDE);
	ShowWindow(hConeCalcBtn, SW_HIDE);
	ShowWindow(hFrusConeCalcBtn, SW_HIDE);
	ShowWindow(hPyramidCalcBtn, SW_HIDE);

}



void VolWnd::ClearVolumeText()
{
	const char* emptyText = "";

	// Guard Window handles before setting text.
	if (hLengthBox && IsWindow(hLengthBox)) SetWindowText(hLengthBox, emptyText);
	if (hBaseBox && IsWindow(hBaseBox)) SetWindowText(hBaseBox, emptyText);
	if (hWidthBox && IsWindow(hWidthBox)) SetWindowText(hWidthBox, emptyText);
	if (hHeightBox && IsWindow(hHeightBox)) SetWindowText(hHeightBox, emptyText);
	if (hRadiusBox && IsWindow(hRadiusBox)) SetWindowText(hRadiusBox, emptyText);
	if (hLowRadiusBox && IsWindow(hLowRadiusBox)) SetWindowText(hLowRadiusBox, emptyText);
	if (hResultBox && IsWindow(hResultBox)) SetWindowText(hResultBox, emptyText);
	
	//SendMessage(hComboBoxSelItem, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);	// Reset to first item.
	//SetFocus(InstVolWnd().hLengthBox);
}

void VolWnd::ClearVolumeWnd()
{
	DestroyWindow(hLengthLabel);
	DestroyWindow(hBaseLabel);
	DestroyWindow(hWidthLabel);
	DestroyWindow(hHeightLabel);
	DestroyWindow(hRadiusLabel);
	DestroyWindow(hLowRadiusLabel);

	DestroyWindow(hLengthBox);
	DestroyWindow(hBaseBox);
	DestroyWindow(hWidthBox);
	DestroyWindow(hHeightBox);
	DestroyWindow(hRadiusBox);
	DestroyWindow(hLowRadiusBox);

}

void VolWnd::VolumeDlgList(HWND hWnd)
{
	// Add items to the combo box (NULL for ID).
	SendDlgItemMessage(hWnd, NULL, CB_ADDSTRING, 0, (LPARAM)TEXT("Triangular Prism"));
	SendDlgItemMessage(hWnd, NULL, CB_ADDSTRING, 0, (LPARAM)TEXT("Rectangular Prism"));
	SendDlgItemMessage(hWnd, NULL, CB_ADDSTRING, 0, (LPARAM)TEXT("Sphere"));
	SendDlgItemMessage(hWnd, NULL, CB_ADDSTRING, 0, (LPARAM)TEXT("Cylinder"));
	SendDlgItemMessage(hWnd, NULL, CB_ADDSTRING, 0, (LPARAM)TEXT("Cone"));
	SendDlgItemMessage(hWnd, NULL, CB_ADDSTRING, 0, (LPARAM)TEXT("Frustum of a Cone"));
	SendDlgItemMessage(hWnd, NULL, CB_ADDSTRING, 0, (LPARAM)TEXT("Regular Pyramid"));

	// Set the initial selection
	SendDlgItemMessage(hWnd, NULL, CB_SETCURSEL, 0, 0);
}

void VolWnd::ComboBoxCommand(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Combo Box, simplified.
	if (HIWORD(wParam) == CBN_SELCHANGE)
	{
		// Hide all input controls first.
		HideInputControls();

		// Reset to default interface.
		defaultInterface = 0;

		// User selected an item
		int selectedIndex = (int)SendDlgItemMessage(hWnd, NULL, CB_GETCURSEL, 0, 0);	// Get the index.
		char selectedText[256] = {};
		SendDlgItemMessage(hWnd, NULL, CB_GETLBTEXT, selectedIndex, (LPARAM)selectedText);
		
		//MessageBox(hWnd, (LPCSTR)selectedText, "Selected Item", MB_OK);
		//SetWindowText(hTextBox, (LPCSTR)selectedText); // set the text of the edit box
		
		switch (selectedIndex)
		{
		case 0:
			ClearVolumeText();
			VolTriInterface();
			//SetFocus(hLengthBox);
			break;
		case 1:
			ClearVolumeText();
			VolRectInterface();
			//SetFocus(hLengthBox);
			break;
		case 2:
			ClearVolumeText();
			VolSphereInterface();
			//SetFocus(hRadiusBox);
			break;
		case 3:
			ClearVolumeText();
			VolCylinderInterface();
			//SetFocus(hRadiusBox);
			break;
		case 4:
			ClearVolumeText();
			VolConeInterface();
			//SetFocus(hRadiusBox);
			break;
		case 5:
			ClearVolumeText();
			VolFrusConeInterface();
			//SetFocus(hRadiusBox);
			break;
		case 6:
			ClearVolumeText();
			VolPyramidInterface();
			//SetFocus(hBaseBox);
			break;
		}

	}

}

void VolWnd::ReInit()
{
	length = 0.0;
	base = 0.0;
	height = 0.0;
	width = 0.0;
	radius = 0.0;
	lowRadius = 0.0;
	result = 0.0;
}

int VolWnd::UserIn(HWND hWndA, HWND hWndB, HWND hWndC)
{
	// Declare variables.
	int swVal;
	double dblResult = 0.0;
	std::string strResult;

	GetWindowText(hWndA, charArrA, 100);	// Retrieve hWndA.
	GetWindowText(hWndB, charArrB, 100);    
	GetWindowText(hWndC, charArrC, 100);

	GetErrorStrings();

	// Validate user input.
	if (strcmp(charArrA, "") == 0 || strcmp(charArrB, "") == 0 || strcmp(charArrC, "") == 0)
	{
		swVal = MessageBoxEx(m_hWnd, "You are missing input!\nPlease enter all values.",
			NULL, MB_OKCANCEL | MB_ICONERROR, NULL);

		switch (swVal)
		{
		case IDCANCEL:
			DestroyWindow(m_hWnd);
			return 0;

		case IDOK:
			return 0;

		}

	}

	for (size_t i = 0; i < strlen(charArrA); i++)
	{
		if (!isdigit(charArrA[i]) && charArrA[i] != '.' && charArrA[i] != ',')
		{
			swVal = MessageBoxEx(m_hWnd, GetStringFromHandle(hWndA).c_str(), NULL, MB_OKCANCEL | MB_ICONERROR, NULL);

			switch (swVal)
			{
			case IDCANCEL:
				DestroyWindow(m_hWnd);
				return 0;

			case IDOK:
				return 0;

			}
		}
	}

	for (size_t i = 0; i < strlen(charArrB); i++)
	{
		if (!isdigit(charArrB[i]) && charArrB[i] != '.' && charArrB[i] != ',')
		{
			swVal = MessageBoxEx(m_hWnd, GetStringFromHandle(hWndB).c_str(), NULL, MB_OKCANCEL | MB_ICONERROR, NULL);

			switch (swVal)
			{
			case IDCANCEL:
				DestroyWindow(m_hWnd);
				return 0;

			case IDOK:
				return 0;

			}
		}
	}

	for (size_t i = 0; i < strlen(charArrC); i++)
	{
		if (!isdigit(charArrC[i]) && charArrC[i] != '.' && charArrC[i] != ',')
		{
			swVal = MessageBoxEx(m_hWnd, GetStringFromHandle(hWndC).c_str(), NULL, MB_OKCANCEL | MB_ICONERROR, NULL);

			switch (swVal)
			{
			case IDCANCEL:
				DestroyWindow(m_hWnd);
				return 0;

			case IDOK:
				return 0;

			}
		}
	}



	return (BOOL)TRUE;
}

int VolWnd::UserIn(HWND hWndA, HWND hWndB)
{
	int swVal;
	double dblResult = 0.0;
	std::string strResult;

	GetWindowText(hWndA, charArrA, 100);
	GetWindowText(hWndB, charArrB, 100);

	GetErrorStrings();

	// Check if nothing is entered.
	if (strcmp(charArrA, "") == 0 || strcmp(charArrB, "") == 0)
	{
		swVal = MessageBoxEx(m_hWnd, "You are missing input!\nPlease enter all values.",
			NULL, MB_OKCANCEL | MB_ICONERROR, NULL);

		switch (swVal)
		{
		case IDCANCEL:
			DestroyWindow(m_hWnd);
			return 0;

		case IDOK:
			return 0;

		}

	}

	for (size_t i = 0; i < strlen(charArrA); i++)
	{
		if (!isdigit(charArrA[i]) && charArrA[i] != '.' && charArrA[i] != ',')
		{
			swVal = MessageBoxEx(m_hWnd, GetStringFromHandle(hWndA).c_str(), NULL, MB_OKCANCEL | MB_ICONERROR, NULL);

			switch (swVal)
			{
			case IDCANCEL:
				DestroyWindow(m_hWnd);
				return 0;

			case IDOK:
				return 0;

			}
		}
	}

	for (size_t i = 0; i < strlen(charArrB); i++)
	{
		if (!isdigit(charArrB[i]) && charArrB[i] != '.' && charArrB[i] != ',')
		{
			swVal = MessageBoxEx(m_hWnd, GetStringFromHandle(hWndB).c_str(), NULL, MB_OKCANCEL | MB_ICONERROR, NULL);

			switch (swVal)
			{
			case IDCANCEL:
				DestroyWindow(m_hWnd);
				return 0;

			case IDOK:
				return 0;

			}
		}
	}

	return (BOOL)TRUE;
}

int VolWnd::UserIn(HWND hWndA)
{
	int swVal;
	double dblResult = 0.0;
	std::string strResult;

	GetWindowText(hWndA, charArrA, 100);

	GetErrorStrings();

	// Check if nothing is entered.
	if (strcmp(charArrA, "") == 0)
	{
		swVal = MessageBoxEx(m_hWnd, "You are missing input!\nPlease enter all values.",
			NULL, MB_OKCANCEL | MB_ICONERROR, NULL);

		switch (swVal)
		{
		case IDCANCEL:
			DestroyWindow(m_hWnd);
			return 0;

		case IDOK:
			return 0;

		}

	}

	for (size_t i = 0; i < strlen(charArrA); i++)
	{
		if (!isdigit(charArrA[i]) && charArrA[i] != '.' && charArrA[i] != ',')
		{
			swVal = MessageBoxEx(m_hWnd, GetStringFromHandle(hWndA).c_str(), NULL, MB_OKCANCEL | MB_ICONERROR, NULL);

			switch (swVal)
			{
			case IDCANCEL:
				DestroyWindow(m_hWnd);
				return 0;

			case IDOK:
				return 0;

			}
		}
	}


	return (BOOL)TRUE;
}

void VolWnd::GetErrorStrings()
{
	// Map message strings to input boxes.
	HandleToString(hLengthBox, "Length is not a valid number!\nPlease enter Length as a valid number."
		"\nSee -- Help \\ Info-- for more information.");
	HandleToString(hBaseBox, "Base is not a valid number!\nPlease enter Base as a valid number."
		"\nSee -- Help \\ Info-- for more information.");
	HandleToString(hWidthBox, "Width is not a valid number!\nPlease enter Width as a valid number."
		"\nSee -- Help \\ Info-- for more information.");
	HandleToString(hHeightBox, "Height is not a valid number!\nPlease enter Height as a valid number."
		"\nSee -- Help \\ Info-- for more information.");
	HandleToString(hRadiusBox, "Radius is not a valid number!\nPlease enter Radius as a valid number."
		"\nSee -- Help \\ Info-- for more information.");
	HandleToString(hLowRadiusBox, "Lower Radius is not a valid number!\nPlease enter Lower Radius as a valid number."
		"\nSee -- Help \\ Info-- for more information.");
}

std::string VolWnd::GetStringFromHandle(HWND hwnd)
{
	auto it = msgBxStrMap.find(hwnd);
	if (it != msgBxStrMap.end()) {
		return it->second;
	}

	return ""; // Return an empty string if the handle is not found.
}

void VolWnd::VolumeInputThunk(VolWnd* obj, void(VolWnd::*calc)())
{
	ReInit();

	char lengthText[100] = { "" }, baseText[100] = { "" }, heightText[100] = { "" },
		widthText[100] = { "" }, radiusText[100] = { "" }, lowRadiusText[100] = { "" },
		resultText[100] = { "" };

	std::string resultString;

	// Retrieve input box text.
	GetWindowText(hLengthBox, lengthText, 100);
	GetWindowText(hBaseBox, baseText, 100);
	GetWindowText(hHeightBox, heightText, 100);
	GetWindowText(hWidthBox, widthText, 100);
	GetWindowText(hRadiusBox, radiusText, 100);
	GetWindowText(hLowRadiusBox, lowRadiusText, 100);

	// Convert  to double.
	length = strtod(lengthText, nullptr);
	base = strtod(baseText, nullptr);
	height = strtod(heightText, nullptr);
	width = strtod(widthText, nullptr);
	radius = strtod(radiusText, nullptr);
	lowRadius = strtod(lowRadiusText, nullptr);

	// Calculate the volume.
	(obj->*calc)();

}

void VolWnd::CalcVolTriangle()
{
	int inOk = UserIn(hLengthBox, hBaseBox, hHeightBox);

	if (inOk)
	{
		double result = (1.0 / 2.0) * length * base * height;

		std::string resultString = ToString(result); // Get the string.
		strcpy_s(resultText, resultString.c_str());   // Convert to C-string

		SetWindowText(hResultBox, resultText);	// Display the result.
	}

}

void VolWnd::CalcVolRectangle()
{
	int inOk = UserIn(hLengthBox, hWidthBox, hHeightBox);

	if (inOk)
	{
		double result = length * width * height;

		std::string resultString = ToString(result);
		strcpy_s(resultText, resultString.c_str());

		SetWindowText(hResultBox, resultText);
	}

}

void VolWnd::CalcVolSphere()
{
	int inOk = UserIn(hRadiusBox);

	if (inOk)
	{
		double result = (4.0 / 3.0) * PI * radius *
			radius * radius;

		std::string resultString = ToString(result);
		strcpy_s(resultText, resultString.c_str());

		SetWindowText(hResultBox, resultText);
	}

}

void VolWnd::CalcVolCylinder()
{
	int inOk = UserIn(hHeightBox, hRadiusBox);
	
	if (inOk)
	{
		double result = PI * radius * radius * height;

		std::string resultString = ToString(result);
		strcpy_s(resultText, resultString.c_str());

		SetWindowText(hResultBox, resultText);
	}

}

void VolWnd::CalcVolCone()
{
	int inOk = UserIn(hRadiusBox, hHeightBox);

	if (inOk)
	{
		double result = (1.0 / 3.0) * PI * radius *
			radius * height;

		std::string resultString = ToString(result);
		strcpy_s(resultText, resultString.c_str());

		SetWindowText(hResultBox, resultText);
	}

}

void VolWnd::CalcVolFrustum()
{
	int inOk = UserIn(hRadiusBox, hLowRadiusBox, hHeightBox);

	if (inOk)
	{
		double result = (1.0 / 3.0) * PI * height * (lowRadius *
			lowRadius + lowRadius * radius + radius * radius);

		std::string resultString = ToString(result);
		strcpy_s(resultText, resultString.c_str());

		SetWindowText(hResultBox, resultText);
	}

}

void VolWnd::CalcVolPyramid()
{
	int inOk = UserIn(hBaseBox, hHeightBox);

	if (inOk)
	{
		double result = (1.0 / 3.0) * base * base * height;

		std::string resultString = ToString(result);
		strcpy_s(resultText, resultString.c_str());

		SetWindowText(hResultBox, resultText);
	}

}

std::string VolWnd::ToString(double num)
{
	std::stringstream ss;    // Declare a string stream var.

	// Set the decimal point.
	ss.setf(std::ios::fixed);
	ss.setf(std::ios::showpoint);
	ss.precision(3);

	ss << num;	// Output to stream.

	return ss.str();	// Return as string.
}


