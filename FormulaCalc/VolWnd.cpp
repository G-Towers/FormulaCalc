// VolWnd.cpp

#include "VolWnd.h"
#include "WinMsgMap.h"

const double PI = 3.141592654;
VolWnd VolWnd::volObj;	// Initialize volObj.
MSG msg;

VolWnd::VolWnd()
{
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
	hCalcBtn = nullptr;
	hClearBtn = nullptr;
	hCloseBtn = nullptr;
}

LRESULT CALLBACK VolWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Print wParam and lParam to immediate window.
	static WinMsgMap mm;
	OutputDebugString(mm(uMsg, wParam, lParam).c_str());

	int wmId = LOWORD(wParam);

	switch (uMsg)
	{
	case WM_COMMAND:
	{
		VolWnd::ComboBoxCommand(m_hWnd, uMsg, wParam, lParam);

		switch (wmId)
		{
		case VOLUME_CALCULATE_TRI_BUTTON:
			VolumeInputThunk(&CalcVolTriangle);
			break;
		case VOLUME_CALCULATE_RECT_BUTTON:
			VolumeInputThunk(&CalcVolRectangle);
			break;
		case VOLUME_CALCULATE_SPHERE_BUTTON:
			VolumeInputThunk(&CalcVolSphere);
			break;
		case VOLUME_CALCULATE_CYLINDER_BUTTON:
			VolumeInputThunk(&CalcVolCylinder);
			break;
		case VOLUME_CALCULATE_CONE_BUTTON:
			VolumeInputThunk(&CalcVolCone);
			break;
		case VOLUME_CALCULATE_FRUSTUM_BUTTON:
			VolumeInputThunk(&CalcVolFrustum);
			break;
		case VOLUME_CALCULATE_PYRAMID_BUTTON:
			VolumeInputThunk(&CalcVolPyramid);
			break;
		case VOLUME_CLEAR_BUTTON:
			ClearVolumeText();
			break;
		case VOLUME_CLOSE_BUTTON:
			DestroyWindow(m_hWnd);
			UnregisterClass("VolWndClass", GetModuleHandle(NULL));
			break;
		}
	}
	break;
	case WM_CREATE:
		// Call to the interface function.
		//Interface::MainInterface(m_hWnd, GetModuleHandle(NULL));
		VolumeInterface();
		VolTriInterface();
		break;
	case WM_SETFOCUS:
		SetFocus(volObj.hLengthBox);
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
		DestroyWindow(m_hWnd);
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
	if (!inst)
	{
		inst = new VolWnd();
	}

	return *inst;
}

void VolWnd::VolumeInterface()
{
	// To get the handle to a dialog box.
	//HWND hVolDlg = GetDlgItem(NULL, IDD_VOLUME_DIALOG);

	hComboBoxSelItem = Widget::ComboBox(25, 25, 175, 150, "", m_hWnd, GetModuleHandle(NULL));	// The combobox window.
	//ComboBoxList(hComboBoxSelItem);	// Items in the combobox.
	VolumeDlgList(m_hWnd);

	// Results.
	hResultLabel = Widget::RLabel(60, 215, 50, 25, "Result:", m_hWnd);
	hResultBox = Widget::ResultBox(120, 210, 150, 25, m_hWnd);

	// Buttons.
	hClearBtn = Widget::Button(320, 190, 90, 30, "Clear", m_hWnd, (HMENU)VOLUME_CLEAR_BUTTON);
	hCloseBtn = Widget::Button(350, 260, 90, 30, "Close", m_hWnd, (HMENU)VOLUME_CLOSE_BUTTON);
}

void VolWnd::VolTriInterface()
{
	// Text labels.
	hLengthLabel = Widget::RLabel(60, 85, 50, 25, "Length:", m_hWnd);
	hBaseLabel = Widget::RLabel(60, 125, 50, 25, "Base:", m_hWnd);
	hHeightLabel = Widget::RLabel(60, 165, 50, 25, "Height:", m_hWnd);

	// Input boxes.
	hLengthBox = Widget::InputBox(120, 80, 150, 25, m_hWnd);
	hBaseBox = Widget::InputBox(120, 120, 150, 25, m_hWnd);
	hHeightBox = Widget::InputBox(120, 160, 150, 25, m_hWnd);

	// Calculate.
	hCalcBtn = Widget::Button(320, 140, 90, 30, "Calculate", m_hWnd, (HMENU)VOLUME_CALCULATE_TRI_BUTTON);
}

void VolWnd::VolRectInterface()
{
	// Text labels.
	hLengthLabel = Widget::RLabel(60, 85, 50, 25, "Length:", m_hWnd);
	hWidthLabel = Widget::RLabel(60, 125, 50, 25, "Width:", m_hWnd);
	hHeightLabel = Widget::RLabel(60, 165, 50, 25, "Height:", m_hWnd);

	// Input boxes.
	hLengthBox = Widget::InputBox(120, 80, 150, 25, m_hWnd);
	hWidthBox = Widget::InputBox(120, 120, 150, 25, m_hWnd);
	hHeightBox = Widget::InputBox(120, 160, 150, 25, m_hWnd);

	// Calculate.
	hCalcBtn = Widget::Button(320, 140, 90, 30, "Calculate", m_hWnd, (HMENU)VOLUME_CALCULATE_RECT_BUTTON);
}

void VolWnd::VolSphereInterface()
{
	// Text labels.
	hRadiusLabel = Widget::RLabel(60, 85, 50, 25, "Radius:", m_hWnd);

	// Input boxes.
	hRadiusBox = Widget::InputBox(120, 80, 150, 25, m_hWnd);

	// Calculate.
	hCalcBtn = Widget::Button(320, 140, 90, 30, "Calculate", m_hWnd, (HMENU)VOLUME_CALCULATE_SPHERE_BUTTON);
}

void VolWnd::VolCylinderInterface()
{
	// Text labels.
	hRadiusLabel = Widget::RLabel(60, 85, 50, 25, "Radius:", m_hWnd);
	hHeightLabel = Widget::RLabel(60, 165, 50, 25, "Height:", m_hWnd);

	// Input boxes.
	hRadiusBox = Widget::InputBox(120, 80, 150, 25, m_hWnd);
	hHeightBox = Widget::InputBox(120, 160, 150, 25, m_hWnd);

	// Calculate.
	hCalcBtn = Widget::Button(320, 140, 90, 30, "Calculate", m_hWnd, (HMENU)VOLUME_CALCULATE_CYLINDER_BUTTON);
}

void VolWnd::VolConeInterface()
{
	// Text labels.
	hRadiusLabel = Widget::RLabel(60, 85, 50, 25, "Radius:", m_hWnd);
	hHeightLabel = Widget::RLabel(60, 165, 50, 25, "Height:", m_hWnd);

	// Input boxes.
	hRadiusBox = Widget::InputBox(120, 80, 150, 25, m_hWnd);
	hHeightBox = Widget::InputBox(120, 160, 150, 25, m_hWnd);

	// Calculate.
	hCalcBtn = Widget::Button(320, 140, 90, 30, "Calculate", m_hWnd, (HMENU)VOLUME_CALCULATE_CONE_BUTTON);
}

void VolWnd::VolFrusConeInterface()
{
	// Text labels.
	hRadiusLabel = Widget::RLabel(60, 75, 50, 35, "Upper  Radius:", m_hWnd);
	hLowRadiusLabel = Widget::RLabel(60, 115, 50, 35, "Lower  Radius:", m_hWnd);
	hHeightLabel = Widget::RLabel(60, 165, 50, 25, "Height:", m_hWnd);

	// Input boxes.
	hRadiusBox = Widget::InputBox(120, 80, 150, 25, m_hWnd);
	hLowRadiusBox = Widget::InputBox(120, 120, 150, 25, m_hWnd);
	hHeightBox = Widget::InputBox(120, 160, 150, 25, m_hWnd);

	// Calculate.
	hCalcBtn = Widget::Button(320, 140, 90, 30, "Calculate", m_hWnd, (HMENU)VOLUME_CALCULATE_FRUSTUM_BUTTON);
}

void VolWnd::VolPyramidInterface()
{
	// Text labels.
	hBaseLabel = Widget::RLabel(60, 125, 50, 25, "Base:", m_hWnd);
	hHeightLabel = Widget::RLabel(60, 165, 50, 25, "Height:", m_hWnd);

	// Input boxes.
	hBaseBox = Widget::InputBox(120, 120, 150, 25, m_hWnd);
	hHeightBox = Widget::InputBox(120, 160, 150, 25, m_hWnd);

	// Calculate.
	hCalcBtn = Widget::Button(320, 140, 90, 30, "Calculate", m_hWnd, (HMENU)VOLUME_CALCULATE_PYRAMID_BUTTON);
}

void VolWnd::VolumeWnd()
{

	if (volWndCreated)
		SetFocus(m_hWnd);
	else
	{
		CreateWnd("Volume", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE,
			0, 250, 250, 480, 350, GetParent(m_hWnd));
		ShowWindow(VolWnd::volObj.GetWinHandle(), SW_SHOW);
		volWndCreated = 1;
	}
	
}

void VolWnd::ClearVolumeText()
{
	const char* emptyText = "";

	SetWindowText(hLengthBox, emptyText);
	SetWindowText(hBaseBox, emptyText);
	SetWindowText(hWidthBox, emptyText);
	SetWindowText(hHeightBox, emptyText);
	SetWindowText(hRadiusBox, emptyText);
	SetWindowText(hLowRadiusBox, emptyText);
	SetWindowText(hResultBox, emptyText);
	
	//SendMessage(hComboBoxSelItem, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);	// Reset to first item.
	SetFocus(volObj.hLengthBox);
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
	DestroyWindow(hCalcBtn);
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
		// User selected an item
		int selectedIndex = (int)SendDlgItemMessage(hWnd, NULL, CB_GETCURSEL, 0, 0);	// Get the index.
		char selectedText[256] = {};
		SendDlgItemMessage(hWnd, NULL, CB_GETLBTEXT, selectedIndex, (LPARAM)selectedText);
		
		//MessageBox(hWnd, (LPCSTR)selectedText, "Selected Item", MB_OK);
		//SetWindowText(hTextBox, (LPCSTR)selectedText); // set the text of the edit box
		
		switch (selectedIndex)
		{
		case 0:
			ClearVolumeWnd();
			ClearVolumeText();
			VolTriInterface();
			SetFocus(hLengthBox);
			break;
		case 1:
			ClearVolumeWnd();
			ClearVolumeText();
			VolRectInterface();
			SetFocus(hLengthBox);
			break;
		case 2:
			ClearVolumeWnd();
			ClearVolumeText();
			VolSphereInterface();
			SetFocus(hRadiusBox);
			break;
		case 3:
			ClearVolumeWnd();
			ClearVolumeText();
			VolCylinderInterface();
			SetFocus(hRadiusBox);
			break;
		case 4:
			ClearVolumeWnd();
			ClearVolumeText();
			VolConeInterface();
			SetFocus(hRadiusBox);
			break;
		case 5:
			ClearVolumeWnd();
			ClearVolumeText();
			VolFrusConeInterface();
			SetFocus(hRadiusBox);
			break;
		case 6:
			ClearVolumeWnd();
			ClearVolumeText();
			VolPyramidInterface();
			SetFocus(hBaseBox);
			break;
		}

	}

}

VolWnd::~VolWnd()
{
	//DestroyWindow(m_hWnd);
	//UnregisterClass("VolWndClass", GetModuleHandle(NULL));
}

void VolumeInputThunk(double(* calc)())
{
	VolWnd::volObj.length = 0.0;
	VolWnd::volObj.base = 0.0;
	VolWnd::volObj.height = 0.0;
	VolWnd::volObj.width = 0.0;
	VolWnd::volObj.radius = 0.0;
	VolWnd::volObj.lowRadius = 0.0;
	VolWnd::volObj.result = 0.0;

	char lengthText[100] = { "" }, baseText[100] = { "" }, heightText[100] = { "" },
		widthText[100] = { "" }, radiusText[100] = { "" }, lowRadiusText[100] = { "" },
		resultText[100] = { "" };

	std::string resultString;

	// Retrieve input box text.
	GetWindowText(VolWnd::volObj.hLengthBox, lengthText, 100);
	GetWindowText(VolWnd::volObj.hBaseBox, baseText, 100);
	GetWindowText(VolWnd::volObj.hHeightBox, heightText, 100);
	GetWindowText(VolWnd::volObj.hWidthBox, widthText, 100);
	GetWindowText(VolWnd::volObj.hRadiusBox, radiusText, 100);
	GetWindowText(VolWnd::volObj.hLowRadiusBox, lowRadiusText, 100);

	// Convert  to double.
	VolWnd::volObj.length = strtod(lengthText, nullptr);
	VolWnd::volObj.base = strtod(baseText, nullptr);
	VolWnd::volObj.height = strtod(heightText, nullptr);
	VolWnd::volObj.width = strtod(widthText, nullptr);
	VolWnd::volObj.radius = strtod(radiusText, nullptr);
	VolWnd::volObj.lowRadius = strtod(lowRadiusText, nullptr);

	// Calculate the volume.
	VolWnd::volObj.result = calc();

	resultString = ToString(VolWnd::volObj.result); // Get the string.
	strcpy_s(resultText, resultString.c_str());   // Convert to C-string

	SetWindowText(VolWnd::volObj.hResultBox, resultText);	// Display the result.
}

double CalcVolTriangle()
{
	// Calculate the volume.
	double calcResult = (1.0 / 2.0) * VolWnd::volObj.length * VolWnd::volObj.base * VolWnd::volObj.height;

	return calcResult;
}

double CalcVolRectangle()
{
	// Calculate the volume.
	double calcResult = VolWnd::volObj.length * VolWnd::volObj.width * VolWnd::volObj.height;

	return calcResult;
}

double CalcVolSphere()
{
	// Calculate the volume.
	double calcResult = (4.0 / 3.0) * PI * VolWnd::volObj.radius * 
		VolWnd::volObj.radius * VolWnd::volObj.radius;

	return calcResult;
}

double CalcVolCylinder()
{
	// Calculate the volume.
	double calcResult = PI * VolWnd::volObj.radius *
		VolWnd::volObj.radius * VolWnd::volObj.height;

	return calcResult;
}

double CalcVolCone()
{
	// Calculate the volume.
	double calcResult = (1.0 / 3.0) * PI * VolWnd::volObj.radius *
		VolWnd::volObj.radius * VolWnd::volObj.height;

	return calcResult;
}

double CalcVolFrustum()
{
	// Calculate the volume.
	double calcResult = (1.0 / 3.0) * PI * VolWnd::volObj.height *
		(VolWnd::volObj.lowRadius * VolWnd::volObj.lowRadius + 
			VolWnd::volObj.lowRadius * VolWnd::volObj.radius +
			VolWnd::volObj.radius * VolWnd::volObj.radius);

	return calcResult;
}

double CalcVolPyramid()
{
	// Calculate the volume.
	double calcResult = (1.0 / 3.0) * VolWnd::volObj.base *
		VolWnd::volObj.base * VolWnd::volObj.height;

	return calcResult;
}

std::string ToString(double num)
{
	std::stringstream ss;    // Declare a string stream var.

	// Set the decimal point.
	ss.setf(std::ios::fixed);
	ss.setf(std::ios::showpoint);
	ss.precision(3);

	ss << num;	// Output to stream.

	return ss.str();	// Return as string.
}