// CompInt.cpp
// Compound Interest

#include "CompInt.h"

CompInt CompInt::compIntObj;
CompInt* CompInt::inst = nullptr;
BOOL CompInt::compIntWndCreated = 0;

CompInt::CompInt()
{
    finAmount = 0.0;
    principal = 0.0;
    rate = 0.0;
    ratePercent = 0.0;
    intAmount = 0.0;
    compNum = 0.0;
    time = 0.0;

    hLblPrincipal = nullptr;
    hLblAnnRate = nullptr;
    hLblCompound = nullptr;
    hLblTime = nullptr;

    hLblResult = nullptr;
    hInPrincipal = nullptr;
    hInAnnRate = nullptr;
    hInCompound = nullptr;
    hInTime = nullptr;

    hRsltCompInt = nullptr;

    hComboBoxSelItem = nullptr;
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

        case COMPINT_CALC_AMOUNT_BUTTON:
            //calc = &FinLoan::CalcFinLoanPayment;
            //FinLoanCalcThunk(&finLoanObj, &FinLoan::CalcFinLoanPayment);
            MessageBox(m_hWnd, "Calculate", "You Pressed", MB_OK);
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

void CompInt::CompIntInterface()
{
    // ComboBoxes.
    hComboBoxSelItem = Widget::ComboBoxID(25, 25, 265, 150, "", m_hWnd, (HMENU)COMPINT_COMBOBOX_CALC, hInst);
    hComboBoxCompound = Widget::ComboBoxID(105, 160, 175, 150, "", m_hWnd, (HMENU)COMPINT_COMBOBOX_COMPOUND, hInst);
    CompIntDlgList(m_hWnd, COMPINT_COMBOBOX_CALC);
    CompoundDlgList(m_hWnd, COMPINT_COMBOBOX_COMPOUND);

    // Labels
    hLblPrincipal = Widget::RLabel(45, 85, 150, 30, "Principal $:", m_hWnd);
    hLblAnnRate = Widget::RLabel(45, 125, 150, 30, "Annual Rate %:", m_hWnd);
    hLblCompound = Widget::RLabel(-50, 165, 150, 30, "Compound:", m_hWnd);
    hLblTime = Widget::RLabel(45, 205, 150, 30, "Time:", m_hWnd);

    // Input boxes.
    hInPrincipal = Widget::InputBox(200, 80, 80, 30, m_hWnd);
    hInAnnRate = Widget::InputBox(200, 120, 80, 30, m_hWnd);
    hInTime = Widget::InputBox(200, 200, 80, 30, m_hWnd);

    // Result label and input box.
    hLblResult = Widget::RLabel(15, 245, 150, 30, "Result:", m_hWnd);
    hRsltCompInt = Widget::ResultBox(170, 240, 110, 30, m_hWnd);


    // Buttons.
    hBtnClear = Widget::Button(350, 190, 90, 30, "Clear", m_hWnd, (HMENU)COMPINT_CLEAR_BUTTON);
    hBtnClose = Widget::Button(350, 260, 90, 30, "Close", m_hWnd, (HMENU)COMPINT_CLOSE_BUTTON);

    hBtnCalc = Widget::Button(350, 140, 90, 30, "Calculate", m_hWnd, (HMENU)COMPINT_CALC_AMOUNT_BUTTON);

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

void CompInt::CompIntDlgList(HWND hWnd, int id)
{
    // Add items to the combo box (NULL for ID).
    SendDlgItemMessage(hWnd, id, CB_ADDSTRING, 0, (LPARAM)TEXT("Total P + I"));
    SendDlgItemMessage(hWnd, id, CB_ADDSTRING, 0, (LPARAM)TEXT("Principal Using A"));
    SendDlgItemMessage(hWnd, id, CB_ADDSTRING, 0, (LPARAM)TEXT("Principal Using I"));
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
            MessageBox(hWnd, "Total P + I", nullptr, MB_OK);
            break;
        case 1:
            MessageBox(hWnd, "Principal Using A", nullptr, MB_OK);
            break;
        case 2:
            MessageBox(hWnd, "Principal Using I", nullptr, MB_OK);
            break;
        case 3:
            MessageBox(hWnd, "Rate", nullptr, MB_OK);
            break;
        case 4:
            MessageBox(hWnd, "Time", nullptr, MB_OK);
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
            MessageBox(hWnd, "Continuous", nullptr, MB_OK);
            break;
        case 1:
            MessageBox(hWnd, "Daily", nullptr, MB_OK);
            break;
        case 2:
            MessageBox(hWnd, "Weekly", nullptr, MB_OK);
            break;
        case 3:
            MessageBox(hWnd, "Biweekly", nullptr, MB_OK);
            break;
        case 4:
            MessageBox(hWnd, "Monthly", nullptr, MB_OK);
            break;
        }
    }
}

void CompInt::ClearCompIntText()
{
    const char* emptyText = "";

    SetWindowText(hInPrincipal, emptyText);
    SetWindowText(hInAnnRate, emptyText);
    SetWindowText(hInCompound, emptyText);
    SetWindowText(hInTime, emptyText);
    SetWindowText(hRsltCompInt, emptyText);
}

void CompInt::ReInit()
{

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
    HandleToString(hInCompound, "Monthly Payment is not a valid number!\nPlease enter Monthly Payment as a valid number."
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
    // Retrieve input box text.
    GetWindowText(hInPrincipal, amountText, 100);
    GetWindowText(hInAnnRate, rateText, 100);
    GetWindowText(hInCompound, monthsText, 100);
    GetWindowText(hInTime, monthPayText, 100);

    // Convert  to double.
    principal = strtod(amountText, nullptr);
    rate = strtod(rateText, nullptr);
    compNum = (int)strtod(monthsText, nullptr);
    //monthPay = strtod(monthPayText, nullptr);

    // Calculate.
    (obj->*calc)();
}

void CompInt::CalcCompoundInt()
{
    int inOk = UserIn(hInPrincipal, hInAnnRate, hInTime);

    if (inOk)
    {
        double intRate = rate * 0.01 / 12;
        finAmount = principal * (pow((1 + intRate), compNum * time));

        // Display.
        std::string resultString = ToString(finAmount); // Get the string.
        strcpy_s(resultText, resultString.c_str());   // Convert to C-string

        SetWindowText(hRsltCompInt, resultText);	// Display the result.

    }
}
