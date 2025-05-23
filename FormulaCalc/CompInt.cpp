// CompInt.cpp
// Compound Interest

#include "CompInt.h"

CompInt CompInt::compIntObj;
CompInt* CompInt::inst = nullptr;
BOOL CompInt::compIntWndCreated = 0;

CompInt::CompInt()
{
	hInst = nullptr;
    calc = nullptr;

    accAmount = 0.0;
    principal = 0.0;
    rate = 0.0;
    annRate = 0.0;
    intAmount = 0.0;
    compNum = 0.0;
    time = 0.0;

	result = 0.0;

    // Initialize char arrays to empty strings
    std::memset(principalText, '\0', sizeof(principalText));
    std::memset(accAmountText, '\0', sizeof(accAmountText));
    std::memset(intAmountText, '\0', sizeof(intAmountText));
    std::memset(annRateText, '\0', sizeof(annRateText));
    std::memset(rateText, '\0', sizeof(rateText));
    std::memset(timeText, '\0', sizeof(timeText));
    std::memset(resultText, '\0', sizeof(resultText));
    std::memset(charArrA, '\0', sizeof(charArrA));
    std::memset(charArrB, '\0', sizeof(charArrB));
    std::memset(charArrC, '\0', sizeof(charArrC));
    std::memset(charArrD, '\0', sizeof(charArrD));

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

    hBtnCalc = nullptr;
    hBtnClear = nullptr;
    hBtnClose = nullptr;

}

CompInt::~CompInt()
{

}

LRESULT CompInt::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int wmId = LOWORD(wParam);
    int wmEvent = HIWORD(wParam);

    switch (uMsg)
    {
    case WM_COMMAND:
        CalcCommand(m_hWnd, wParam, lParam);
        CompoundCommand(m_hWnd, wParam, lParam);

        switch (wmId)
        {
        case COMPINT_CLEAR_BUTTON:
            ClearCompIntText();
            break;

        case COMPINT_CALC_ACCRUED_BUTTON:
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

        case COMPINT_CALC_RATE_BUTTON:
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

    case WM_CREATE:
        CompIntInterface();
        CompIntAccruedInterface();
        break;
    case WM_SETFOCUS:
        SetFocus(compIntObj.m_hWnd);
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

    // Result Box. 
    hRsltCompInt = Widget::ResultBox(180, 300, 110, 30, m_hWnd);

    // Buttons.
    hBtnClear = Widget::Button(430, 210, 90, 30, "Clear", m_hWnd, (HMENU)COMPINT_CLEAR_BUTTON);
    hBtnClose = Widget::Button(430, 260, 90, 30, "Close", m_hWnd, (HMENU)COMPINT_CLOSE_BUTTON);

}

void CompInt::CompIntAccruedInterface()
{
    // Labels
    ShowWindow(hLblPrincipal, SW_SHOW);
    ShowWindow(hLblAnnRate, SW_SHOW);
    ShowWindow(hLblTime, SW_SHOW);

    // Input boxes.
    ShowWindow(hInPrincipal, SW_SHOW);
    ShowWindow(hInAnnRate, SW_SHOW);
    ShowWindow(hInTime, SW_SHOW);

    // Hide others
    ShowWindow(hLblAccAmount, SW_HIDE);
    ShowWindow(hInAccAmount, SW_HIDE);
    ShowWindow(hLblIntAmount, SW_HIDE);
    ShowWindow(hInIntAmount, SW_HIDE);

    // Buttons.
    hBtnCalc = Widget::Button(430, 140, 90, 30, "Calculate", m_hWnd, (HMENU)COMPINT_CALC_ACCRUED_BUTTON);

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

	// Hide others
	ShowWindow(hLblPrincipal, SW_HIDE);
	ShowWindow(hInPrincipal, SW_HIDE);
	ShowWindow(hLblIntAmount, SW_HIDE);
	ShowWindow(hInIntAmount, SW_HIDE);

    // Buttons.
    hBtnCalc = Widget::Button(430, 140, 90, 30, "Calculate", m_hWnd, (HMENU)COMPINT_PRINCA_BUTTON);
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

	// Hide others
	ShowWindow(hLblPrincipal, SW_HIDE);
	ShowWindow(hInPrincipal, SW_HIDE);
	ShowWindow(hLblAccAmount, SW_HIDE);
	ShowWindow(hInAccAmount, SW_HIDE);

    // Buttons.
    hBtnCalc = Widget::Button(430, 140, 90, 30, "Calculate", m_hWnd, (HMENU)COMPINT_PRINCI_BUTTON);
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

	// Hide others
	ShowWindow(hLblIntAmount, SW_HIDE);
	ShowWindow(hInIntAmount, SW_HIDE);
	ShowWindow(hLblAnnRate, SW_HIDE);
	ShowWindow(hInAnnRate, SW_HIDE);

    // Buttons.
    hBtnCalc = Widget::Button(430, 140, 90, 30, "Calculate", m_hWnd, (HMENU)COMPINT_CALC_RATE_BUTTON);

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

	// Hide others
	ShowWindow(hLblIntAmount, SW_HIDE);
	ShowWindow(hInIntAmount, SW_HIDE);
	ShowWindow(hLblTime, SW_HIDE);
	ShowWindow(hInTime, SW_HIDE);

    // Buttons.
    hBtnCalc = Widget::Button(430, 140, 90, 30, "Calculate", m_hWnd, (HMENU)COMPINT_TIME_BUTTON);
}

void CompInt::HideAllInputControls()
{
	// Labels
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
    DestroyWindow(hBtnCalc);
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

        // User selected item.
        int selectedIndex = (int)SendDlgItemMessage(hWnd, COMPINT_COMBOBOX_CALC, CB_GETCURSEL, 0, 0);	// Get the index.
        char selectedText[256] = {};    // Array for listbox items.
        SendDlgItemMessage(hWnd, COMPINT_COMBOBOX_CALC, CB_GETLBTEXT, selectedIndex, (LPARAM)selectedText);

        switch (selectedIndex)
        {
        case 0:
            //MessageBox(hWnd, "Total P + I", nullptr, MB_OK);
            //ClearCompIntWnd();
            //ClearCompIntText();
            CompIntAccruedInterface();
            break;
        case 1:
            //MessageBox(hWnd, "Principal Using A", nullptr, MB_OK);
            //ClearCompIntWnd();
            //ClearCompIntText();
            CompIntPrinAInterface();
            break;
        case 2:
            //MessageBox(hWnd, "Principal Using I", nullptr, MB_OK);
            //ClearCompIntWnd();
            //ClearCompIntText();
            CompIntPrinIInterface();
            break;
        case 3:
            //MessageBox(hWnd, "Rate", nullptr, MB_OK);
            //ClearCompIntWnd();
            //ClearCompIntText();
            CompIntRateInterface();
            break;
        case 4:
            //MessageBox(hWnd, "Time", nullptr, MB_OK);
            //ClearCompIntWnd();
            //ClearCompIntText();
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
    accAmount = 0.0;
    principal = 0.0;
    rate = 0.0;
    annRate = 0.0;
    intAmount = 0.0;
    //compNum = 0.0;
    time = 0.0;

    // Initialize char arrays to empty strings
    std::memset(principalText, '\0', sizeof(principalText));
    std::memset(accAmountText, '\0', sizeof(accAmountText));
    std::memset(intAmountText, '\0', sizeof(intAmountText));
    std::memset(annRateText, '\0', sizeof(annRateText));
    std::memset(rateText, '\0', sizeof(rateText));
    std::memset(timeText, '\0', sizeof(timeText));
    std::memset(resultText, '\0', sizeof(resultText));
    std::memset(charArrA, '\0', sizeof(charArrA));
    std::memset(charArrB, '\0', sizeof(charArrB));
    std::memset(charArrC, '\0', sizeof(charArrC));
    std::memset(charArrD, '\0', sizeof(charArrD));
}

int CompInt::UserIn(HWND hWndA, HWND hWndB, HWND hWndC)
{
    // Declare variables.
    int swVal;
    double dblResult = 0.0;
    std::string strResult;

    GetWindowText(hWndA, charArrA, 100);	// Retrieve hWndA.
    GetWindowText(hWndB, charArrB, 100);    // Retrieve hWndB.
    GetWindowText(hWndC, charArrC, 100);	// Retrieve hWndC.

    // Map message strings to input boxes.
    HandleToString(hInPrincipal, "Principal is not a valid number!\nPlease enter Principal as a valid number."
        "\nSee -- Help \\ Info-- for more information.");

    HandleToString(hInAccAmount, "Accrued Amount is not a valid number!\nPlease enter the amount as a valid number."
        "\nSee -- Help \\ Info-- for more information.");

    HandleToString(hInIntAmount, "Interest Amount is not a valid number!\nPlease enter the amount as a valid number."
        "\nSee -- Help \\ Info-- for more information.");

    HandleToString(hInAnnRate, "Annual Interest Rate is not a valid number!\nPlease enter Annual Interest Rate as a valid number."
        "\nSee -- Help \\ Info-- for more information.");

    HandleToString(hInTime, "Time is not a valid number!\nPlease enter Time as a valid number."
        "\nSee -- Help \\ Info-- for more information.");

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

void CompInt::CompIntCalcThunk(CompInt* obj, void(CompInt::* calc)())
{
    ReInit();

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

    // Calculate.
    (obj->*calc)();
}

void CompInt::CalcCompoundInt()
{
    int inOk = UserIn(hInPrincipal, hInAnnRate, hInTime);

    if (inOk)
    {    
        double intRate = rate * 0.01 / 12;  // Convert to decimal and get monthly rate.
        accAmount = principal * (pow((1 + intRate), compNum * time));

        // Display.
        std::string resultString = ToString(accAmount); // Get the string.
        strcpy_s(resultText, resultString.c_str());   // Convert to C-string

        SetWindowText(hRsltCompInt, resultText);	// Display the result.

    }
}

void CompInt::CalcAccrued()
{
    int inOk = UserIn(hInPrincipal, hInAnnRate, hInTime);

    if (inOk)
    {
        rate = annRate / 100;
        accAmount = principal * (pow((1 + (rate / compNum)), (compNum * time)));

        // Display.
        std::string resultString = "$ " + ToString(accAmount); // Get the string.
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
        std::string resultString = "$ " + ToString(principal); // Get the string.
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
        std::string resultString = "$ " + ToString(principal); // Get the string.
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
        std::string resultString = ToString(annRate) + " %"; // Get the string.
        strcpy_s(resultText, resultString.c_str());   // Convert to C-string

        SetWindowText(hRsltCompInt, resultText);	// Display the result.

    }
}

void CompInt::CalcRatePercent()
{

}

void CompInt::CalcTime()
{
    int inOk = UserIn(hInAccAmount, hInPrincipal, hInAnnRate);

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
        std::string resultString = "$ " + ToString(accAmount); // Get the string.
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
        std::string resultString = "$ " + ToString(principal); // Get the string.
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
        std::string resultString = "$ " + ToString(principal); // Get the string.
        strcpy_s(resultText, resultString.c_str());   // Convert to C-string
        SetWindowText(hRsltCompInt, resultText);	// Display the result.
    }
}

void CompInt::CalcContRate()
{
    int inOk = UserIn(hInPrincipal, hInAccAmount, hInTime);

    if (inOk)
    {
        // Calculate
        rate = log(accAmount / principal) / time;
        annRate = rate * 100.0; // Convert to percentage.

        // Display.
        std::string resultString = ToString(annRate) + " %"; // Get the string.
        strcpy_s(resultText, resultString.c_str());   // Convert to C-string

        SetWindowText(hRsltCompInt, resultText);	// Display the result.

    }
}

void CompInt::CalcContTime()
{
	int inOk = UserIn(hInAccAmount, hInPrincipal, hInAnnRate);

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
