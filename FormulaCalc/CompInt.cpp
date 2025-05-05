// CompInt.cpp
// Compound Interest

#include "CompInt.h"

CompInt CompInt::compIntObj;
CompInt* CompInt::inst = nullptr;
BOOL CompInt::compIntWndCreated = 0;

CompInt::CompInt()
{
    accAmount = 0.0;
    principal = 0.0;
    rate = 0.0;
    annRate = 0.0;
    intAmount = 0.0;
    compNum = 0.0;
    time = 0.0;

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
            //calc = &FinLoan::CalcFinLoanPayment;
            CompIntCalcThunk(&compIntObj, &CompInt::CalcAccruedPrinInt);
            //MessageBox(m_hWnd, "Calculate", "You Pressed", MB_OK);
            break;

        case COMPINT_CALC_RATE_BUTTON:
            CompIntCalcThunk(&compIntObj, &CompInt::CalcRate);
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
            0, 270, 270, 480, 350, GetParent(m_hWnd));
        ShowWindow(m_hWnd, SW_SHOW);
        compIntWndCreated = 1;
    }
}

void CompInt::CompIntInterface()
{
    // Lablels.
    hLblCalculate = Widget::RLabel(-5, 25, 150, 30, "Calculate:", m_hWnd);
    hLblCompound = Widget::RLabel(-5, 160, 150, 30, "Compound:", m_hWnd);

    hLblResult = Widget::RLabel(-5, 245, 150, 30, "Result:", m_hWnd);

    // ComboBoxes.
    hComboBoxCalculate = Widget::ComboBoxID(150, 25, 265, 150, "", m_hWnd, (HMENU)COMPINT_COMBOBOX_CALC, hInst);
    hComboBoxCompound = Widget::ComboBoxID(150, 160, 175, 150, "", m_hWnd, (HMENU)COMPINT_COMBOBOX_COMPOUND, hInst);
    CompIntDlgList(m_hWnd, COMPINT_COMBOBOX_CALC);
    CompoundDlgList(m_hWnd, COMPINT_COMBOBOX_COMPOUND);

    // Result Box. 
    hRsltCompInt = Widget::ResultBox(150, 240, 110, 30, m_hWnd);


    // Buttons.
    hBtnClear = Widget::Button(350, 190, 90, 30, "Clear", m_hWnd, (HMENU)COMPINT_CLEAR_BUTTON);
    hBtnClose = Widget::Button(350, 260, 90, 30, "Close", m_hWnd, (HMENU)COMPINT_CLOSE_BUTTON);


}

void CompInt::CompIntAccruedInterface()
{
    // Labels
    hLblPrincipal = Widget::RLabel(-5, 85, 150, 30, "Principal $:", m_hWnd);
    hLblAnnRate = Widget::RLabel(-5, 125, 150, 30, "Annual Rate %:", m_hWnd);
    hLblTime = Widget::RLabel(-5, 205, 150, 30, "Time (in years):", m_hWnd);

    // Input boxes.
    hInPrincipal = Widget::InputBox(150, 80, 80, 30, m_hWnd);
    hInAnnRate = Widget::InputBox(150, 120, 80, 30, m_hWnd);
    hInTime = Widget::InputBox(150, 200, 80, 30, m_hWnd);

    // Buttons.
    hBtnCalc = Widget::Button(350, 140, 90, 30, "Calculate", m_hWnd, (HMENU)COMPINT_CALC_ACCRUED_BUTTON);

}

void CompInt::CompIntPrinAInterface()
{
    // Labels
    hLblAccAmount = Widget::RLabel(-5, 85, 150, 30, "Principal + Interest $:", m_hWnd);
    hLblAnnRate = Widget::RLabel(-5, 125, 150, 30, "Annual Rate %:", m_hWnd);
    hLblTime = Widget::RLabel(-5, 205, 150, 30, "Time (in years):", m_hWnd);

    // Input boxes.
    hInAccAmount = Widget::InputBox(150, 80, 80, 30, m_hWnd);
    hInAnnRate = Widget::InputBox(150, 120, 80, 30, m_hWnd);
    hInTime = Widget::InputBox(150, 200, 80, 30, m_hWnd);

    // Buttons.
    hBtnCalc = Widget::Button(350, 140, 90, 30, "Calculate", m_hWnd, (HMENU)COMPINT_CALC_RATE_BUTTON);
}

void CompInt::CompIntPrinIInterface()
{
    // Labels
    hLblIntAmount = Widget::RLabel(-5, 85, 150, 30, "Total Interest $:", m_hWnd);
    hLblAnnRate = Widget::RLabel(-5, 125, 150, 30, "Annual Rate %:", m_hWnd);
    hLblTime = Widget::RLabel(-5, 205, 150, 30, "Time (in years):", m_hWnd);

    // Input boxes.
    hInIntAmount = Widget::InputBox(150, 80, 80, 30, m_hWnd);
    hInAnnRate = Widget::InputBox(150, 120, 80, 30, m_hWnd);
    hInTime = Widget::InputBox(150, 200, 80, 30, m_hWnd);

    // Buttons.
    hBtnCalc = Widget::Button(350, 140, 90, 30, "Calculate", m_hWnd, (HMENU)COMPINT_CALC_RATE_BUTTON);
}

void CompInt::CompIntRateInterface()
{
    // Labels
    hLblPrincipal = Widget::RLabel(-5, 85, 150, 30, "Principal $:", m_hWnd);
    hLblAccAmount = Widget::RLabel(-5, 125, 150, 30, "Accrued Amount $:", m_hWnd);
    hLblTime = Widget::RLabel(-5, 205, 150, 30, "Time (in years):", m_hWnd);

    // Input boxes.
    hInPrincipal = Widget::InputBox(150, 80, 80, 30, m_hWnd);
    hInAccAmount = Widget::InputBox(150, 120, 80, 30, m_hWnd);
    hInTime = Widget::InputBox(150, 200, 80, 30, m_hWnd);

    // Buttons.
    hBtnCalc = Widget::Button(350, 140, 90, 30, "Calculate", m_hWnd, (HMENU)COMPINT_CALC_RATE_BUTTON);

}

void CompInt::CompIntTimeInterface()
{
    // Labels
    hLblAccAmount = Widget::RLabel(-5, 85, 150, 30, "Principal + Interest $:", m_hWnd);
    hLblPrincipal = Widget::RLabel(-5, 125, 150, 30, "Principal $:", m_hWnd);
    hLblAnnRate = Widget::RLabel(-5, 205, 150, 30, "Annual Rate %:", m_hWnd);

    // Input boxes.
    hInAccAmount = Widget::InputBox(150, 80, 80, 30, m_hWnd);
    hInPrincipal = Widget::InputBox(150, 120, 80, 30, m_hWnd);
    hInAnnRate = Widget::InputBox(150, 200, 80, 30, m_hWnd);

    // Buttons.
    hBtnCalc = Widget::Button(350, 140, 90, 30, "Calculate", m_hWnd, (HMENU)COMPINT_CALC_RATE_BUTTON);
}

void CompInt::ClearCompIntWnd()
{
    DestroyWindow(hLblPrincipal);
    DestroyWindow(hLblAccAmount);
    DestroyWindow(hLblAnnRate);
    DestroyWindow(hLblTime);
    //DestroyWindow(hLblResult);
    DestroyWindow(hInPrincipal);
    DestroyWindow(hInAccAmount);
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
    SendDlgItemMessage(hWnd, id, CB_ADDSTRING, 0, (LPARAM)TEXT("Monthly"));

    // Set the initial selection
    SendDlgItemMessage(hWnd, id, CB_SETCURSEL, 0, 0);
}

void CompInt::CalcCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    // Combo Box logic.
    if (HIWORD(wParam) == CBN_SELCHANGE)
    {
        // User selected item.
        int selectedIndex = (int)SendDlgItemMessage(hWnd, COMPINT_COMBOBOX_CALC, CB_GETCURSEL, 0, 0);	// Get the index.
        char selectedText[256] = {};    // Array for listbox items.
        SendDlgItemMessage(hWnd, COMPINT_COMBOBOX_CALC, CB_GETLBTEXT, selectedIndex, (LPARAM)selectedText);

        switch (selectedIndex)
        {
        case 0:
            //MessageBox(hWnd, "Total P + I", nullptr, MB_OK);
            ClearCompIntWnd();
            ClearCompIntText();
            CompIntAccruedInterface();
            break;
        case 1:
            //MessageBox(hWnd, "Principal Using A", nullptr, MB_OK);
            ClearCompIntWnd();
            ClearCompIntText();
            CompIntPrinAInterface();
            break;
        case 2:
            //MessageBox(hWnd, "Principal Using I", nullptr, MB_OK);
            ClearCompIntWnd();
            ClearCompIntText();
            CompIntPrinIInterface();
            break;
        case 3:
            //MessageBox(hWnd, "Rate", nullptr, MB_OK);
            ClearCompIntWnd();
            ClearCompIntText();
            CompIntRateInterface();
            break;
        case 4:
            //MessageBox(hWnd, "Time", nullptr, MB_OK);
            ClearCompIntWnd();
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
            break;
        case 1:
            //MessageBox(hWnd, "Daily", nullptr, MB_OK);
            compNum = 365;
            break;
        case 2:
            MessageBox(hWnd, "Weekly", nullptr, MB_OK);
            compNum = 52;
            break;
        case 3:
            MessageBox(hWnd, "Biweekly", nullptr, MB_OK);
            compNum = 26;
            break;
        case 4:
            //MessageBox(hWnd, "Monthly", nullptr, MB_OK);
            compNum = 12;
            break;
        }
    }
}

void CompInt::ClearCompIntText()
{
    const char* emptyText = "";

    SetWindowText(hInPrincipal, emptyText);
    SetWindowText(hInAccAmount, emptyText);
    SetWindowText(hInAnnRate, emptyText);
    SetWindowText(hInTime, emptyText);
    SetWindowText(hRsltCompInt, emptyText);
}

void CompInt::ReInit()
{
    accAmount = 0.0;
    principal = 0.0;
    rate = 0.0;
    annRate = 0.0;
    intAmount = 0.0;
    //compNum = 0.0;
    time = 0.0;
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
    ss.precision(3);

    ss << num;

    return ss.str();
}

void CompInt::CompIntCalcThunk(CompInt* obj, void(CompInt::* calc)())
{
    ReInit();

    // Retrieve input box text.
    GetWindowText(hInPrincipal, principalText, 100);
    GetWindowText(hInAccAmount, accAmountText, 100);
    GetWindowText(hInAnnRate, annRateText, 100);
    GetWindowText(hInTime, timeText, 100);

    // Calculate.
    (obj->*calc)();
}

void CompInt::CalcCompoundInt()
{
    int inOk = UserIn(hInPrincipal, hInAnnRate, hInTime);

    if (inOk)
    {
        // Convert  to double.
        principal = strtod(accAmountText, nullptr);
        accAmount = strtod(principalText, nullptr);
        rate = strtod(rateText, nullptr);
        time = strtod(timeText, nullptr);

        double intRate = rate * 0.01 / 12;  // Convert to decimal and get monthly rate.
        accAmount = principal * (pow((1 + intRate), compNum * time));

        // Display.
        std::string resultString = ToString(accAmount); // Get the string.
        strcpy_s(resultText, resultString.c_str());   // Convert to C-string

        SetWindowText(hRsltCompInt, resultText);	// Display the result.

    }
}

void CompInt::CalcAccruedPrinInt()
{
    int inOk = UserIn(hInPrincipal, hInAnnRate, hInTime);

    if (inOk)
    {
        // Convert  to double.
        principal = strtod(principalText, nullptr);
        annRate = strtod(annRateText, nullptr);
        time = strtod(timeText, nullptr);

        rate = annRate / 100;
        accAmount = principal * (pow((1 + (rate / compNum)), (compNum * time)));

        // Display.
        std::string resultString = ToString(accAmount); // Get the string.
        strcpy_s(resultText, resultString.c_str());   // Convert to C-string

        SetWindowText(hRsltCompInt, resultText);	// Display the result.

    }
}

void CompInt::CalcPrinAccrued()
{

}

void CompInt::CalcPrinInt()
{

}

void CompInt::CalcRate()
{
    int inOk = UserIn(hInPrincipal, hInAccAmount, hInTime);

    if (inOk)
    {
        // Convert  to double.
        principal = strtod(principalText, nullptr);
        accAmount = strtod(accAmountText, nullptr);
        time = strtod(timeText, nullptr);

        // Calculate
        rate = compNum * (pow((accAmount / principal), 1 / (compNum * time)) - 1);
        annRate = rate * 100.0;

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

}
