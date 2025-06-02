// CompInt.cpp
// Compound Interest

#include "CompInt.h"

CompInt CompInt::compIntObj;
CompInt* CompInt::inst = nullptr;
BOOL CompInt::compIntWndCreated = 0;

CompInt::CompInt()
{
	hInst = nullptr;
	accruedInterface = false;
    calc = nullptr;

    accAmount = 0.0;
    principal = 0.0;
    rate = 0.0;
    annRate = 0.0;
    intAmount = 0.0;
    compNum = 0.0;
    time = 0.0;

	result = 0.0;

    memset(principalText, 0, sizeof(principalText));
	memset(accAmountText, 0, sizeof(accAmountText));
	memset(intAmountText, 0, sizeof(intAmountText));
	memset(annRateText, 0, sizeof(annRateText));
	memset(timeText, 0, sizeof(timeText));
	memset(resultText, 0, sizeof(resultText));

	savedPrincipal = "";
	savedAccAmount = "";
	savedIntAmount = "";
	savedAnnRate = "";
	savedTime = "";
	savedResult = "";


    hGrpInfo = nullptr;

    hLblPrincipal = nullptr;
    hLblAccAmount = nullptr;
    hLblIntAmount = nullptr;
    hLblAnnRate = nullptr;
    hLblTime = nullptr;

    hLblCompound = nullptr;
    hLblCalculate = nullptr;

    hLblResult = nullptr;
    hInPrincipal = nullptr;
    hInAccAmount = nullptr;
    hInIntAmount = nullptr;
    hInAnnRate = nullptr;
    hInTime = nullptr;


    hRsltCompInt = nullptr;

    hComboBoxCalculate = nullptr;
    hComboBoxCompound = nullptr;

    hBtnCalcAcc = nullptr;
    hBtnCalcPrincA = nullptr;
    hBtnCalcPrincI = nullptr;
    hBtnCalcRate = nullptr;
    hBtnCalcTime = nullptr;

    hBtnClear = nullptr;
    hBtnClose = nullptr;

}

CompInt::~CompInt()
{

}

LRESULT CompInt::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    switch (uMsg)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int wmEvent = HIWORD(wParam);

        if (wmId == COMPINT_COMBOBOX_CALC && wmEvent == CBN_SELCHANGE)
            CalcCommand(m_hWnd, wParam, lParam);

        else if (wmId == COMPINT_COMBOBOX_COMPOUND && wmEvent == CBN_SELCHANGE)
            CompoundCommand(m_hWnd, wParam, lParam);

        switch (wmId)
        {
        case COMPINT_CLEAR_BUTTON:
            ClearCompIntText();
            break;

        case COMPINT_ACCRUED_BUTTON:
            (compNum != 0) ? CompIntCalcThunk(&compIntObj, &CompInt::CalcAccrued) :
                CompIntCalcThunk(&compIntObj, &CompInt::CalcContAccruedPrincPlusInt);
            break;

        case COMPINT_PRINCA_BUTTON:
            (compNum != 0) ? CompIntCalcThunk(&compIntObj, &CompInt::CalcPrincAccrued) :
                CompIntCalcThunk(&compIntObj, &CompInt::CalcContPrincAccrued);
            break;

        case COMPINT_PRINCI_BUTTON:
            (compNum != 0) ? CompIntCalcThunk(&compIntObj, &CompInt::CalcPrincInt) :
                CompIntCalcThunk(&compIntObj, &CompInt::CalcContPrincInt);
            break;

        case COMPINT_RATE_BUTTON:
            (compNum != 0) ? CompIntCalcThunk(&compIntObj, &CompInt::CalcRate) :
                CompIntCalcThunk(&compIntObj, &CompInt::CalcContRate);
            break;

        case COMPINT_TIME_BUTTON:
            (compNum != 0) ? CompIntCalcThunk(&compIntObj, &CompInt::CalcTime) :
                CompIntCalcThunk(&compIntObj, &CompInt::CalcContTime);
            break;

        case COMPINT_CLOSE_BUTTON:
            compIntWndCreated = 0;
            UnregisterClass("CompIntClass", GetModuleHandle(NULL));
            DestroyWindow(m_hWnd);

            return 0;

        }

        break;
    }

    case WM_CREATE:
        CompIntInterface();
        CompIntAccruedInterface();
        break;
    case WM_SETFOCUS:
        SetFocus(compIntObj.hInPrincipal);
        break;

    case WM_DESTROY:
        compIntWndCreated = 0;
        UnregisterClass("CompIntClass", hInst);
        DestroyWindow(m_hWnd);

        //PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hWnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
        EndPaint(m_hWnd, &ps);
    }

    return 0;

    }
    return (LRESULT)DefWindowProc(m_hWnd, uMsg, wParam, lParam);
}

LRESULT CompInt::InputBoxProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_KEYDOWN && wParam == VK_TAB)
    {
        HWND hParent = GetParent(hwnd);
        CompInt* pThis = reinterpret_cast<CompInt*>(GetWindowLongPtr(hParent, GWLP_USERDATA));
        if (pThis)
        {
            HWND inputs[] = { pThis->hInPrincipal, pThis->hInAccAmount, pThis->hInIntAmount, pThis->hInAnnRate, pThis->hInTime };
            const int numInputs = sizeof(inputs) / sizeof(inputs[0]);
            for (int i = 0; i < numInputs; ++i)
            {
                if (inputs[i] == hwnd)
                {
                    bool shiftDown = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
                    int dir = shiftDown ? -1 : 1;
                    for (int j = 1; j <= numInputs; ++j)
                    {
                        int idx = (i + dir * j + numInputs) % numInputs;
                        if (inputs[idx] && IsWindowVisible(inputs[idx]) && IsWindowEnabled(inputs[idx]))
                        {
                            SetFocus(inputs[idx]);
                            break;
                        }
                    }
                    break;
                }
            }
            return 0; // Handled
        }
    }

    // Handle ESC key: close the parent window
    if (wParam == VK_ESCAPE) 
    {
        HWND hParent = GetParent(hwnd);
        if (hParent) 
        {
            DestroyWindow(hParent);
        }

        return 0; // Handled
    }

    // ENTER Calculates.
    if (wParam == VK_RETURN) 
    {
        HWND hParent = GetParent(hwnd);
        CompInt* pThis = reinterpret_cast<CompInt*>(GetWindowLongPtr(hParent, GWLP_USERDATA));
        if (pThis)
        {
            // Determine which calculation mode is active by checking which Calculate button is visible
            if (pThis->hBtnCalcAcc && IsWindowVisible(pThis->hBtnCalcAcc))
            {
                if (pThis->compNum != 0)
                    pThis->CompIntCalcThunk(pThis, &CompInt::CalcAccrued);
                else
                    pThis->CompIntCalcThunk(pThis, &CompInt::CalcContAccruedPrincPlusInt);
            }
            else if (pThis->hBtnCalcPrincA && IsWindowVisible(pThis->hBtnCalcPrincA))
            {
                if (pThis->compNum != 0)
                    pThis->CompIntCalcThunk(pThis, &CompInt::CalcPrincAccrued);
                else
                    pThis->CompIntCalcThunk(pThis, &CompInt::CalcContPrincAccrued);
            }
            else if (pThis->hBtnCalcPrincI && IsWindowVisible(pThis->hBtnCalcPrincI))
            {
                if (pThis->compNum != 0)
                    pThis->CompIntCalcThunk(pThis, &CompInt::CalcPrincInt);
                else
                    pThis->CompIntCalcThunk(pThis, &CompInt::CalcContPrincInt);
            }
            else if (pThis->hBtnCalcRate && IsWindowVisible(pThis->hBtnCalcRate))
            {
                if (pThis->compNum != 0)
                    pThis->CompIntCalcThunk(pThis, &CompInt::CalcRate);
                else
                    pThis->CompIntCalcThunk(pThis, &CompInt::CalcContRate);
            }
            else if (pThis->hBtnCalcTime && IsWindowVisible(pThis->hBtnCalcTime))
            {
                if (pThis->compNum != 0)
                    pThis->CompIntCalcThunk(pThis, &CompInt::CalcTime);
                else
                    pThis->CompIntCalcThunk(pThis, &CompInt::CalcContTime);
            }
        }

        return 0; // Handled
    }

    // Suppress beep on TAB key
    if (msg == WM_CHAR && wParam == VK_TAB)
        return 0;

    // Retrieve the original window proc from the property
    WNDPROC oldProc = (WNDPROC)GetProp(hwnd, TEXT("OldEditProc"));
    return CallWindowProc(oldProc, hwnd, msg, wParam, lParam);

}

CompInt& CompInt::InstCompIntWnd()
{
    if (!inst)
    {
        inst = new CompInt();
    }

    return *inst;
}

HINSTANCE CompInt::GetInstance() noexcept
{
    return compIntObj.hInst;
}

void CompInt::CompIntWnd()
{
    if (compIntWndCreated)
        SetFocus(m_hWnd);
    else
    {
        CreateWnd("Compound Interest", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE,
            0, 270, 270, 560, 400, GetParent(m_hWnd));
        ShowWindow(m_hWnd, SW_SHOW);
        compIntWndCreated = 1;
    }
}

void CompInt::CompIntInterface()
{
    // Lablels.
    hLblCalculate = Widget::RLabel(-15, 17, 100, 30, "Calculate:", m_hWnd);
    hLblCompound = Widget::RLabel(75, 203, 100, 30, "Compound:", m_hWnd);

    hLblPrincipal = Widget::RLabel(75, 85, 100, 30, "Principal $:", m_hWnd);
    hLblAccAmount = Widget::RLabel(50, 125, 125, 30, "Principal + Interest $:", m_hWnd);
    hLblIntAmount = Widget::RLabel(75, 85, 100, 30, "Total Interest $:", m_hWnd);
    hLblAnnRate = Widget::RLabel(75, 165, 100, 30, "Annual Rate %:", m_hWnd);
    hLblTime = Widget::RLabel(75, 245, 100, 30, "Time (in years):", m_hWnd);

    hLblResult = Widget::RLabel(75, 305, 100, 30, "Result:", m_hWnd);

    // ComboBoxes.
    hComboBoxCalculate = Widget::ComboBoxID(90, 15, 265, 150, "", m_hWnd, (HMENU)COMPINT_COMBOBOX_CALC, hInst);
    hComboBoxCompound = Widget::ComboBoxID(180, 200, 175, 200, "", m_hWnd, (HMENU)COMPINT_COMBOBOX_COMPOUND, hInst);
    CompIntDlgList(m_hWnd, COMPINT_COMBOBOX_CALC);
    CompoundDlgList(m_hWnd, COMPINT_COMBOBOX_COMPOUND);

    // Groupbox.
    hGrpInfo = Widget::GroupBox(20, 50, 390, 300, "Enter Information", m_hWnd, hInst);

    // Input boxes.
    hInPrincipal = Widget::InputBox(180, 80, 80, 30, m_hWnd);
    hInAccAmount = Widget::InputBox(180, 120, 80, 30, m_hWnd);
    hInIntAmount = Widget::InputBox(180, 80, 80, 30, m_hWnd);
    hInAnnRate = Widget::InputBox(180, 160, 80, 30, m_hWnd);
    hInTime = Widget::InputBox(180, 240, 80, 30, m_hWnd);

    // After creating input boxes in CompIntInterface, subclass and store the original proc
    SetProp(hInPrincipal, TEXT("OldEditProc"), (HANDLE)SetWindowLongPtr(hInPrincipal, GWLP_WNDPROC, (LONG_PTR)&CompInt::InputBoxProc));
    SetProp(hInAccAmount, TEXT("OldEditProc"), (HANDLE)SetWindowLongPtr(hInAccAmount, GWLP_WNDPROC, (LONG_PTR)&CompInt::InputBoxProc));
    SetProp(hInIntAmount, TEXT("OldEditProc"), (HANDLE)SetWindowLongPtr(hInIntAmount, GWLP_WNDPROC, (LONG_PTR)&CompInt::InputBoxProc));
    SetProp(hInAnnRate, TEXT("OldEditProc"), (HANDLE)SetWindowLongPtr(hInAnnRate, GWLP_WNDPROC, (LONG_PTR)&CompInt::InputBoxProc));
    SetProp(hInTime, TEXT("OldEditProc"), (HANDLE)SetWindowLongPtr(hInTime, GWLP_WNDPROC, (LONG_PTR)&CompInt::InputBoxProc));

    // Store 'this' pointer in the parent window for access in InputBoxProc
    SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);

    // Result Box. 
    hRsltCompInt = Widget::ResultBox(180, 300, 110, 30, m_hWnd);

    // Buttons.
    hBtnClear = Widget::Button(430, 210, 90, 30, "Clear", m_hWnd, (HMENU)COMPINT_CLEAR_BUTTON);
    hBtnClose = Widget::Button(430, 260, 90, 30, "Close", m_hWnd, (HMENU)COMPINT_CLOSE_BUTTON);

	// Calculate Buttons.
    hBtnCalcAcc = Widget::Button(430, 140, 90, 30, "Calculate", m_hWnd, (HMENU)COMPINT_ACCRUED_BUTTON);
    hBtnCalcPrincA = Widget::Button(430, 140, 90, 30, "Calculate", m_hWnd, (HMENU)COMPINT_PRINCA_BUTTON);
    hBtnCalcPrincI = Widget::Button(430, 140, 90, 30, "Calculate", m_hWnd, (HMENU)COMPINT_PRINCI_BUTTON);
    hBtnCalcRate = Widget::Button(430, 140, 90, 30, "Calculate", m_hWnd, (HMENU)COMPINT_RATE_BUTTON);
    hBtnCalcTime = Widget::Button(430, 140, 90, 30, "Calculate", m_hWnd, (HMENU)COMPINT_TIME_BUTTON);


}

void CompInt::CompIntAccruedInterface()
{
    if (accruedInterface)
		return; // Already set up.

	accruedInterface = true; // Set the flag.

    // Labels
    ShowWindow(hLblPrincipal, SW_SHOW);
    ShowWindow(hLblAnnRate, SW_SHOW);
    ShowWindow(hLblTime, SW_SHOW);

    // Input boxes.
    ShowWindow(hInPrincipal, SW_SHOW);
    ShowWindow(hInAnnRate, SW_SHOW);
    ShowWindow(hInTime, SW_SHOW);

    // Calculate.
    ShowWindow(hBtnCalcAcc, SW_SHOW);

    // Hide others
    ShowWindow(hLblAccAmount, SW_HIDE);
    ShowWindow(hInAccAmount, SW_HIDE);
    ShowWindow(hLblIntAmount, SW_HIDE);
    ShowWindow(hInIntAmount, SW_HIDE);

    ShowWindow(hBtnCalcPrincA, SW_HIDE);
    ShowWindow(hBtnCalcPrincI, SW_HIDE);
    ShowWindow(hBtnCalcRate, SW_HIDE);
    ShowWindow(hBtnCalcTime, SW_HIDE);

    
}

void CompInt::CompIntPrinAInterface()
{
    // Labels
    ShowWindow(hLblAccAmount, SW_SHOW);
    ShowWindow(hLblAnnRate, SW_SHOW);
    ShowWindow(hLblTime, SW_SHOW);

    // Input boxes.
    ShowWindow(hInAccAmount, SW_SHOW);
    ShowWindow(hInAnnRate, SW_SHOW);
    ShowWindow(hInTime, SW_SHOW);

    // Calculate.
    ShowWindow(hBtnCalcPrincA, SW_SHOW);

	// Hide others
	ShowWindow(hLblPrincipal, SW_HIDE);
	ShowWindow(hInPrincipal, SW_HIDE);
	ShowWindow(hLblIntAmount, SW_HIDE);
	ShowWindow(hInIntAmount, SW_HIDE);

    ShowWindow(hBtnCalcAcc, SW_HIDE);
    ShowWindow(hBtnCalcPrincI, SW_HIDE);
    ShowWindow(hBtnCalcRate, SW_HIDE);
    ShowWindow(hBtnCalcTime, SW_HIDE);

    
}

void CompInt::CompIntPrinIInterface()
{
    // Labels
    ShowWindow(hLblIntAmount, SW_SHOW);
    ShowWindow(hLblAnnRate, SW_SHOW);
    ShowWindow(hLblTime, SW_SHOW);

    // Input boxes.
    ShowWindow(hInIntAmount, SW_SHOW);
    ShowWindow(hInAnnRate, SW_SHOW);
    ShowWindow(hInTime, SW_SHOW);

    // Calculate.
    ShowWindow(hBtnCalcPrincI, SW_SHOW);

	// Hide others
	ShowWindow(hLblPrincipal, SW_HIDE);
	ShowWindow(hInPrincipal, SW_HIDE);
	ShowWindow(hLblAccAmount, SW_HIDE);
	ShowWindow(hInAccAmount, SW_HIDE);

    ShowWindow(hBtnCalcAcc, SW_HIDE);
    ShowWindow(hBtnCalcPrincA, SW_HIDE);
    ShowWindow(hBtnCalcRate, SW_HIDE);
    ShowWindow(hBtnCalcTime, SW_HIDE);

    
}

void CompInt::CompIntRateInterface()
{
    // Labels
    ShowWindow(hLblPrincipal, SW_SHOW);
    ShowWindow(hLblAccAmount, SW_SHOW);
    ShowWindow(hLblTime, SW_SHOW);

    // Input boxes.
    ShowWindow(hInPrincipal, SW_SHOW);
    ShowWindow(hInAccAmount, SW_SHOW);
    ShowWindow(hInTime, SW_SHOW);

    // Calculate.
    ShowWindow(hBtnCalcRate, SW_SHOW);

	// Hide others
	ShowWindow(hLblIntAmount, SW_HIDE);
	ShowWindow(hInIntAmount, SW_HIDE);
	ShowWindow(hLblAnnRate, SW_HIDE);
	ShowWindow(hInAnnRate, SW_HIDE);

    ShowWindow(hBtnCalcAcc, SW_HIDE);
    ShowWindow(hBtnCalcPrincA, SW_HIDE);
    ShowWindow(hBtnCalcPrincI, SW_HIDE);
    ShowWindow(hBtnCalcTime, SW_HIDE);

    
}

void CompInt::CompIntTimeInterface()
{
    // Labels
    ShowWindow(hLblPrincipal, SW_SHOW);
    ShowWindow(hLblAccAmount, SW_SHOW);
    ShowWindow(hLblAnnRate, SW_SHOW);

    // Input boxes.
    ShowWindow(hInPrincipal, SW_SHOW);
    ShowWindow(hInAccAmount, SW_SHOW);
    ShowWindow(hInAnnRate, SW_SHOW);

    // Calculate.
    ShowWindow(hBtnCalcTime, SW_SHOW);

	// Hide others
	ShowWindow(hLblIntAmount, SW_HIDE);
	ShowWindow(hInIntAmount, SW_HIDE);
	ShowWindow(hLblTime, SW_HIDE);
	ShowWindow(hInTime, SW_HIDE);

    ShowWindow(hBtnCalcAcc, SW_HIDE);
    ShowWindow(hBtnCalcPrincA, SW_HIDE);
    ShowWindow(hBtnCalcPrincI, SW_HIDE);
    ShowWindow(hBtnCalcRate, SW_HIDE);

    

}

void CompInt::HideAllInputControls()
{
	// Labels.
    ShowWindow(hLblPrincipal, SW_HIDE);
    ShowWindow(hLblAccAmount, SW_HIDE);
    ShowWindow(hLblIntAmount, SW_HIDE);
    ShowWindow(hLblAnnRate, SW_HIDE);
    ShowWindow(hLblTime, SW_HIDE);

	// Input boxes.
    ShowWindow(hInPrincipal, SW_HIDE);
    ShowWindow(hInAccAmount, SW_HIDE);
    ShowWindow(hInIntAmount, SW_HIDE);
    ShowWindow(hInAnnRate, SW_HIDE);
    ShowWindow(hInTime, SW_HIDE);

    // Buttons.
    ShowWindow(hBtnCalcAcc, SW_HIDE);
    ShowWindow(hBtnCalcPrincA, SW_HIDE);
    ShowWindow(hBtnCalcPrincI, SW_HIDE);
    ShowWindow(hBtnCalcRate, SW_HIDE);
    ShowWindow(hBtnCalcTime, SW_HIDE);

    //ShowWindow(hBtnClear, SW_HIDE);
    //ShowWindow(hBtnClose, SW_HIDE);

}

void CompInt::ClearCompIntWnd()
{
    DestroyWindow(hLblPrincipal);
    DestroyWindow(hLblAccAmount);
    DestroyWindow(hLblIntAmount);
    DestroyWindow(hLblAnnRate);
    DestroyWindow(hLblTime);
    //DestroyWindow(hLblResult);
    DestroyWindow(hInPrincipal);
    DestroyWindow(hInAccAmount);
    DestroyWindow(hInIntAmount);
    DestroyWindow(hInAnnRate);
    DestroyWindow(hInTime);
    //DestroyWindow(hRsltCompInt);
    //DestroyWindow(hBtnCalc);
}


void CompInt::CompIntDlgList(HWND hWnd, int id)
{
    // Add items to the combo box (NULL for ID).
    SendDlgItemMessage(hWnd, id, CB_ADDSTRING, 0, (LPARAM)TEXT("Total Principal + Interest"));
    SendDlgItemMessage(hWnd, id, CB_ADDSTRING, 0, (LPARAM)TEXT("Principal Using Accrued"));
    SendDlgItemMessage(hWnd, id, CB_ADDSTRING, 0, (LPARAM)TEXT("Principal Using Interest"));
    SendDlgItemMessage(hWnd, id, CB_ADDSTRING, 0, (LPARAM)TEXT("Rate"));
    SendDlgItemMessage(hWnd, id, CB_ADDSTRING, 0, (LPARAM)TEXT("Time"));

    // Set the initial selection
    SendDlgItemMessage(hWnd, id, CB_SETCURSEL, 0, 0);
}

void CompInt::CompoundDlgList(HWND hWnd, int id)
{
    // Add items to the combo box (NULL for ID).
    SendDlgItemMessage(hWnd, id, CB_ADDSTRING, 0, (LPARAM)TEXT("Continuous"));
    SendDlgItemMessage(hWnd, id, CB_ADDSTRING, 0, (LPARAM)TEXT("Daily"));
    SendDlgItemMessage(hWnd, id, CB_ADDSTRING, 0, (LPARAM)TEXT("Weekly"));
    SendDlgItemMessage(hWnd, id, CB_ADDSTRING, 0, (LPARAM)TEXT("Biweekly"));
    SendDlgItemMessage(hWnd, id, CB_ADDSTRING, 0, (LPARAM)TEXT("Semimonthly"));
    SendDlgItemMessage(hWnd, id, CB_ADDSTRING, 0, (LPARAM)TEXT("Monthly"));
    SendDlgItemMessage(hWnd, id, CB_ADDSTRING, 0, (LPARAM)TEXT("Bimonthly"));
    SendDlgItemMessage(hWnd, id, CB_ADDSTRING, 0, (LPARAM)TEXT("Quarterly"));
    SendDlgItemMessage(hWnd, id, CB_ADDSTRING, 0, (LPARAM)TEXT("Semiannually"));
    SendDlgItemMessage(hWnd, id, CB_ADDSTRING, 0, (LPARAM)TEXT("Annually"));

    // Set the initial selection
    SendDlgItemMessage(hWnd, id, CB_SETCURSEL, 0, 0);
}

void CompInt::CalcCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    // Combo Box logic.
    if (HIWORD(wParam) == CBN_SELCHANGE)
    {
        // Hide all controls first
        HideAllInputControls();
		ResetInterface(); // Reset the interface.

        // User selected item.
        int selectedIndex = (int)SendDlgItemMessage(hWnd, COMPINT_COMBOBOX_CALC, CB_GETCURSEL, 0, 0);	// Get the index.
        char selectedText[256] = {};    // Array for listbox items.
        SendDlgItemMessage(hWnd, COMPINT_COMBOBOX_CALC, CB_GETLBTEXT, selectedIndex, (LPARAM)selectedText);

        switch (selectedIndex)
        {
        case 0:
            //MessageBox(hWnd, "Total P + I", nullptr, MB_OK);
            ClearCompIntText();
            CompIntAccruedInterface();
            break;
        case 1:
            //MessageBox(hWnd, "Principal Using A", nullptr, MB_OK);
            ClearCompIntText();
            CompIntPrinAInterface();
            break;
        case 2:
            //MessageBox(hWnd, "Principal Using I", nullptr, MB_OK);
            ClearCompIntText();
            CompIntPrinIInterface();
            break;
        case 3:
            //MessageBox(hWnd, "Rate", nullptr, MB_OK);
            ClearCompIntText();
            CompIntRateInterface();
            break;
        case 4:
            //MessageBox(hWnd, "Time", nullptr, MB_OK);
            ClearCompIntText();
            CompIntTimeInterface();
            break;
        }

    }

}

void CompInt::CompoundCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    // Combo Box logic.
    if (HIWORD(wParam) == CBN_SELCHANGE)
    {
        // User selected item.
        int selectedIndex = (int)SendDlgItemMessage(hWnd, COMPINT_COMBOBOX_COMPOUND, CB_GETCURSEL, 0, 0);	// Get the index.
        char selectedText[256] = {};    // Array for listbox items.
        SendDlgItemMessage(hWnd, COMPINT_COMBOBOX_COMPOUND, CB_GETLBTEXT, selectedIndex, (LPARAM)selectedText);

        switch (selectedIndex)
        {
        case 0:
            //MessageBox(hWnd, "Continuous", nullptr, MB_OK);
			compNum = 0;	// Continuous.
            break;
        case 1:
            // Daily.
            compNum = 365;
            break;
        case 2:
            // Weekly.
            compNum = 52;
            break;
        case 3:
            // Biweekly.
            compNum = 26;
            break;
        case 4:
            // Semimonthly.
			compNum = 24;	// 2 times a month.
            break;
        case 5:
            // Monthly.
			compNum = 12;	// 12 times a year.
            break;
        case 6:
			// Bimonthly.
			compNum = 6;	// 6 times a year.
            break;
        case 7:
			// Quarterly.
			compNum = 4;	// 4 times a year.
            break;
        case 8:
			// Semiannually.
			compNum = 2;	// 2 times a year.
            break;
        case 9:
			// Annually.
			compNum = 1;	// 1 time a year.
            break;
        }
    }
}

void CompInt::ClearCompIntText()
{
    const char* emptyText = "";

    SetWindowText(hInPrincipal, emptyText);
    SetWindowText(hInAccAmount, emptyText);
    SetWindowText(hInIntAmount, emptyText);
    SetWindowText(hInAnnRate, emptyText);
    SetWindowText(hInTime, emptyText);
    SetWindowText(hRsltCompInt, emptyText);
}

void CompInt::ReInit()
{
	// Initialize variables to default values.
    principal = 0.0;
    accAmount = 0.0;
    intAmount = 0.0;
    annRate = 0.0;
    time = 0.0;

	// Clear text buffers.
    memset(principalText, 0, sizeof(principalText));
    memset(accAmountText, 0, sizeof(accAmountText));
    memset(intAmountText, 0, sizeof(intAmountText));
    memset(annRateText, 0, sizeof(annRateText));
    memset(timeText, 0, sizeof(timeText));
    memset(resultText, 0, sizeof(resultText));

}

int CompInt::UserIn(HWND hWndA, HWND hWndB, HWND hWndC)
{
    // Declare variables.
    int swVal;
    double dblResult = 0.0;
    char textA[100] = { "" };
    char textB[100] = { "" };
    char textC[100] = { "" };
    std::string strResult;

    GetWindowText(hWndA, textA, 100);	// Retrieve textA.
    GetWindowText(hWndB, textB, 100);   // Retrieve textB.
    GetWindowText(hWndC, textC, 100);	// Retrieve textC.

    // Map message strings to input boxes.
    HandleToString(hInPrincipal, "Principal is not a valid number!\nPlease enter Principal as a valid number."
        "\nSee -- Help \\ Info-- for more information.");

    HandleToString(hInAccAmount, "Accrued Amount is not a valid number!\nPlease enter the amount as a valid number."
        "\nSee -- Help \\ Info-- for more information.");

    HandleToString(hInIntAmount, "Interest Amount is not a valid number!\nPlease enter the amount as a valid number."
        "\nSee -- Help \\ Info-- for more information.");

    HandleToString(hInAnnRate, "Annual Interest Rate is not a valid number!\nPlease enter the interest rate as a valid number."
        "\nSee -- Help \\ Info-- for more information.");

    HandleToString(hInTime, "Time is not a valid number!\nPlease enter Time as a valid number."
        "\nSee -- Help \\ Info-- for more information.");

    // Validate user input.
    if (strcmp(textA, "") == 0 || strcmp(textB, "") == 0 || strcmp(textC, "") == 0)
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

    for (size_t i = 0; i < strlen(textA); i++)
    {
        if (!isdigit(textA[i]) && textA[i] != '.' && textA[i] != ',')
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

    for (size_t i = 0; i < strlen(textB); i++)
    {
        if (!isdigit(textB[i]) && textB[i] != '.' && textB[i] != ',')
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

    for (size_t i = 0; i < strlen(textC); i++)
    {
        if (!isdigit(textC[i]) && textC[i] != '.' && textC[i] != ',')
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

std::string CompInt::GetStringFromHandle(HWND hwnd)
{
    auto it = msgBxStrMap.find(hwnd);
    if (it != msgBxStrMap.end()) {
        return it->second;
    }

    return ""; // Return an empty string if the handle is not found.
}

double CompInt::StringToDouble(const std::string& str)
{
    return std::stod(str);
}

std::string CompInt::ToString(double num)
{
    std::stringstream ss;    // Declare a string stream var.

    // Set the decimal point.
    ss.setf(std::ios::fixed);
    ss.setf(std::ios::showpoint);
    ss.precision(2);

    ss << num;

    return ss.str();
}

void CompInt::GetConvert()
{
    // Retrieve input box text.
    GetWindowText(hInPrincipal, principalText, 100);
    GetWindowText(hInAccAmount, accAmountText, 100);
    GetWindowText(hInIntAmount, intAmountText, 100);
    GetWindowText(hInAnnRate, annRateText, 100);
    GetWindowText(hInTime, timeText, 100);

    // Convert  to double.
    principal = strtod(principalText, nullptr);
    accAmount = strtod(accAmountText, nullptr);
    intAmount = strtod(intAmountText, nullptr);
    annRate = strtod(annRateText, nullptr);
    time = strtod(timeText, nullptr);
}

void CompInt::CompIntCalcThunk(CompInt* obj, void(CompInt::* calc)())
{
    // Clear all.
    ReInit();

    // Get and convert input text.
	GetConvert();	

    // Calculate.
    (obj->*calc)();
}

void CompInt::CalcAccrued()
{
    int inOk = UserIn(hInPrincipal, hInAnnRate, hInTime);

    if (inOk)
    {
        rate = annRate / 100;
        accAmount = principal * (pow((1 + (rate / compNum)), (compNum * time)));

        // Display.
        std::string resultString = "$" + ToString(accAmount); // Get the string.
        strcpy_s(resultText, resultString.c_str());   // Convert to C-string

        SetWindowText(hRsltCompInt, resultText);	// Display the result.

    }
}

void CompInt::CalcPrincAccrued()
{
    int inOk = UserIn(hInAccAmount, hInAnnRate, hInTime);

    if (inOk)
    {
        // Calculate
        rate = annRate / 100.0;
        principal = accAmount / (pow((1 + rate / compNum), (compNum * time)));
        

        // Display.
        std::string resultString = "$" + ToString(principal); // Get the string.
        strcpy_s(resultText, resultString.c_str());   // Convert to C-string

        SetWindowText(hRsltCompInt, resultText);	// Display the result.

    }
}

void CompInt::CalcPrincInt()
{
    int inOk = UserIn(hInIntAmount, hInAnnRate, hInTime);

    if (inOk)
    {
        // Calculate
        rate = annRate / 100.0;
        principal = intAmount / (pow((1 + rate / compNum), (compNum * time) - 1));


        // Display.
        std::string resultString = "$" + ToString(principal); // Get the string.
        strcpy_s(resultText, resultString.c_str());   // Convert to C-string

        SetWindowText(hRsltCompInt, resultText);	// Display the result.

    }
}

void CompInt::CalcRate()
{
    int inOk = UserIn(hInPrincipal, hInAccAmount, hInTime);

    if (inOk)
    {
        // Calculate
        rate = compNum * (pow((accAmount / principal), 1 / (compNum * time)) - 1);
		annRate = rate * 100.0; // Convert to percentage.

        // Display.
        std::string resultString = ToString(annRate) + "%"; // Get the string.
        strcpy_s(resultText, resultString.c_str());   // Convert to C-string

        SetWindowText(hRsltCompInt, resultText);	// Display the result.

    }
}

void CompInt::CalcRatePercent()
{

}

void CompInt::CalcTime()
{
    int inOk = UserIn(hInPrincipal, hInAccAmount, hInAnnRate);

    if (inOk)
    {
        // Calculate
        rate = annRate / 100.0;
        double time = log(accAmount / principal) / (compNum * (log(1 + (rate / compNum))));


        // Display.
        std::string resultString = ToString(time) + " years."; // Get the string.
        strcpy_s(resultText, resultString.c_str());   // Convert to C-string

        SetWindowText(hRsltCompInt, resultText);	// Display the result.

    }
}

void CompInt::CalcContAccruedPrincPlusInt()
{
    int inOk = UserIn(hInPrincipal, hInAnnRate, hInTime);

    if (inOk)
    {
        // Calculate
        rate = annRate / 100.0;
        accAmount = principal * pow(e, (rate * time));

        // Display.
        std::string resultString = "$" + ToString(accAmount); // Get the string.
        strcpy_s(resultText, resultString.c_str());   // Convert to C-string
        SetWindowText(hRsltCompInt, resultText);	// Display the result.
	}
}

void CompInt::CalcContPrincAccrued()
{
    int inOk = UserIn(hInAccAmount, hInAnnRate, hInTime);

    if (inOk)
    {
        // Calculate
        rate = annRate / 100.0;
        principal = accAmount / pow(e, (rate * time));

        // Display.
        std::string resultString = "$" + ToString(principal); // Get the string.
        strcpy_s(resultText, resultString.c_str());   // Convert to C-string
        SetWindowText(hRsltCompInt, resultText);	// Display the result.
    }
}

void CompInt::CalcContPrincInt()
{
    int inOk = UserIn(hInIntAmount, hInAnnRate, hInTime);

    if (inOk)
    {
        // Calculate
        rate = annRate / 100.0;
        principal = intAmount / (pow(e, (rate * time)) - 1);

        // Display.
        std::string resultString = "$" + ToString(principal); // Get the string.
        strcpy_s(resultText, resultString.c_str());   // Convert to C-string
        SetWindowText(hRsltCompInt, resultText);	// Display the result.
    }
}

void CompInt::CalcContRate()
{
    int inOk = UserIn(hInPrincipal, hInAccAmount, hInTime );

    if (inOk)
    {
        // Calculate
        rate = log(accAmount / principal) / time;
        annRate = rate * 100.0; // Convert to percentage.

        // Display.
        std::string resultString = ToString(annRate) + "%"; // Get the string.
        strcpy_s(resultText, resultString.c_str());   // Convert to C-string

        SetWindowText(hRsltCompInt, resultText);	// Display the result.

    }
}

void CompInt::CalcContTime()
{
	int inOk = UserIn(hInPrincipal, hInAccAmount, hInAnnRate);

    if (inOk)
    {
        // Calculate
        rate = annRate / 100.0;
        time = log(accAmount / principal) / rate;

        // Display.
        std::string resultString = ToString(time) + " years."; // Get the string.
        strcpy_s(resultText, resultString.c_str());   // Convert to C-string
        SetWindowText(hRsltCompInt, resultText);	// Display the result.
	}

}

void CompInt::ResetInterface()
{
	accruedInterface = false; // Reset the flag.
}

void CompInt::SaveInputText()
{
    char buf[100];

    if (hInPrincipal)
    {   GetWindowText(hInPrincipal, buf, 100);
        savedPrincipal = buf;
    }
    if (hInAccAmount)
    {   GetWindowText(hInAccAmount, buf, 100);
        savedAccAmount = buf;
    }
    if (hInIntAmount)
    {   GetWindowText(hInIntAmount, buf, 100);
        savedIntAmount = buf;
    }
    if (hInAnnRate)
    {   GetWindowText(hInAnnRate, buf, 100);
        savedAnnRate = buf;
    }
    if (hInTime)
    {   GetWindowText(hInTime, buf, 100);
        savedTime = buf;
    }

}

void CompInt::RestoreInputText()
{
    if (hInPrincipal)
        SetWindowText(hInPrincipal, savedPrincipal.c_str());
    if (hInAccAmount)
        SetWindowText(hInAccAmount, savedAccAmount.c_str());
    if (hInIntAmount)
        SetWindowText(hInIntAmount, savedIntAmount.c_str());
    if (hInAnnRate)
        SetWindowText(hInAnnRate, savedAnnRate.c_str());
    if (hInTime)
        SetWindowText(hInTime, savedTime.c_str());

}
