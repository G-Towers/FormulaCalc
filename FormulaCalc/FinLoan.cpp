// FinLoan.cpp
// Finance Loan

#include "FinLoan.h"

FinLoan FinLoan::finLoanObj;
FinLoan* FinLoan::inst = nullptr;
BOOL FinLoan::flWndCreated = 0;

FinLoan::FinLoan()
{
    hInst = GetModuleHandle(NULL);

    amount = 0.0;
    monthRate = 0.0;
    rate = 0.0;
    monthPay = 0.0;
    months = 0;
    //result = 0.0;

    hLblMonthPay = nullptr;
    hLblAmount = nullptr;
    hLblRate = nullptr;
    hLblMonths = nullptr;
    hLblResult = nullptr;

    hInMonthPay = nullptr;
    hInAmount = nullptr;
    hInRate = nullptr;
    hInMonths = nullptr;

    hRsltFinLoan = nullptr;

    hBtnCalc = nullptr;
    hBtnClear = nullptr;
    hBtnClose = nullptr;
}

FinLoan::~FinLoan()
{

}

LRESULT FinLoan::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int wmId = LOWORD(wParam);
    int wmEvent = HIWORD(wParam);

    switch (uMsg)
    {
    case WM_COMMAND:
        ComboBoxCommand(m_hWnd, uMsg, wParam, lParam);

        switch (wmId)
        {
        case FINLOAN_CALC_AMOUNT_BUTTON:
            //calc = &FinLoan::CalcFinLoanAmount;
            FinLoanCalcThunk(&finLoanObj, &FinLoan::CalcFinLoanAmount);
            break;

        case FINLOAN_CALC_RATE_BUTTON:
            //calc = &FinLoan::CalcFinLoanRate;
            FinLoanCalcThunk(&finLoanObj, &FinLoan::CalcFinLoanRate);
            break;

        case FINLOAN_CALC_MONTHS_BUTTON:
            //calc = &FinLoan::CalcFinLoanMonths;
            FinLoanCalcThunk(&finLoanObj, &FinLoan::CalcFinLoanMonths);
            break;

        case FINLOAN_CALC_PAYMENT_BUTTON:
            //calc = &FinLoan::CalcFinLoanPayment;
            FinLoanCalcThunk(&finLoanObj, &FinLoan::CalcFinLoanPayment);
            break;

        case FINLOAN_CLEAR_BUTTON:
            ClearFinLoanText();
            break;
        
        case FINLOAN_CLOSE_BUTTON:
            flWndCreated = 0;
            UnregisterClass("FinLoanClass", GetModuleHandle(NULL));
            DestroyWindow(m_hWnd);

            return 0;

        }
        break;

    case WM_CREATE:
        FinLoanInterface();
        FinLoanAmountInterface();
        break;
    case WM_SETFOCUS:
        SetFocus(m_hWnd);
        break;

    case WM_DESTROY:
        flWndCreated = 0;
        UnregisterClass("FinLoanClass", hInst);
        DestroyWindow(m_hWnd);

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
    return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
}

void FinLoan::FinLoanWnd()
{
    if (flWndCreated)
        SetFocus(m_hWnd);
    else
    {
        CreateWnd("Finance Loan", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE,
            0, 270, 270, 480, 350, GetParent(m_hWnd));
        ShowWindow(m_hWnd, SW_SHOW);
        flWndCreated = 1;
    }
}

void FinLoan::FinLoanInterface()
{
    // ComboBox.
    HWND hComboBoxSelItem = Widget::ComboBox(25, 25, 265, 150, "", m_hWnd, hInst);
    FinLoanDlgList(m_hWnd);

    // Buttons.
    hBtnClear = Widget::Button(350, 190, 90, 30, "Clear", m_hWnd, (HMENU)FINLOAN_CLEAR_BUTTON);
    hBtnClose = Widget::Button(350, 260, 90, 30, "Close", m_hWnd, (HMENU)FINLOAN_CLOSE_BUTTON);
}

void FinLoan::FinLoanAmountInterface()
{
    // Labels
    hLblRate = Widget::RLabel(45, 85, 150, 30, "Interest Rate: %", m_hWnd);
    hLblMonths = Widget::RLabel(45, 125, 150, 30, "Number of Months:", m_hWnd);
    hLblMonthPay = Widget::RLabel(45, 165, 150, 30, "Monthly Payment: $", m_hWnd);

    // Input boxes.
    hInRate = Widget::InputBox(200, 80, 80, 30, m_hWnd);
    hInMonths = Widget::InputBox(200, 120, 80, 30, m_hWnd);
    hInMonthPay = Widget::InputBox(200, 160, 80, 30, m_hWnd);

    // Result label and input box.
    hLblResult = Widget::RLabel(15, 205, 150, 30, "Loan Amount: $", m_hWnd);
    hRsltFinLoan = Widget::ResultBox(170, 200, 110, 30, m_hWnd);

    // Buttons.
    hBtnCalc = Widget::Button(350, 140, 90, 30, "Calculate", m_hWnd, (HMENU)FINLOAN_CALC_AMOUNT_BUTTON);

}

void FinLoan::FinLoanRateInterface()
{
    // Labels
    hLblAmount = Widget::RLabel(45, 85, 150, 30, "Loan Amount: $", m_hWnd);
    hLblMonths = Widget::RLabel(45, 125, 150, 30, "Number of Months:", m_hWnd);
    hLblMonthPay = Widget::RLabel(45, 165, 150, 30, "Monthly Payment: $", m_hWnd);

    // Input boxes.
    hInAmount = Widget::InputBox(200, 80, 80, 30, m_hWnd);
    hInMonths = Widget::InputBox(200, 120, 80, 30, m_hWnd);
    hInMonthPay = Widget::InputBox(200, 160, 80, 30, m_hWnd);

    // Result label and input box.
    hLblResult = Widget::RLabel(15, 205, 150, 30, "Annual Interest Rate: %", m_hWnd);
    hRsltFinLoan = Widget::ResultBox(170, 200, 110, 30, m_hWnd);

    // Buttons.
    hBtnCalc = Widget::Button(350, 140, 90, 30, "Calculate", m_hWnd, (HMENU)FINLOAN_CALC_RATE_BUTTON);
}

void FinLoan::FinLoanMonthsInterface()
{
    // Labels
    hLblAmount = Widget::RLabel(45, 85, 150, 30, "Loan Amount: $", m_hWnd);
    hLblRate = Widget::RLabel(45, 125, 150, 30, "Interest Rate: %", m_hWnd);
    hLblMonthPay = Widget::RLabel(45, 165, 150, 30, "Monthly Payment: $", m_hWnd);

    // Input boxes.
    hInAmount = Widget::InputBox(200, 80, 80, 30, m_hWnd);
    hInRate = Widget::InputBox(200, 120, 80, 30, m_hWnd);
    hInMonthPay = Widget::InputBox(200, 160, 80, 30, m_hWnd);

    // Result label and input box.
    hLblResult = Widget::RLabel(15, 205, 150, 30, "Number of Months: ", m_hWnd);
    hRsltFinLoan = Widget::ResultBox(170, 200, 110, 30, m_hWnd);

    // Buttons.
    hBtnCalc = Widget::Button(350, 140, 90, 30, "Calculate", m_hWnd, (HMENU)FINLOAN_CALC_MONTHS_BUTTON);
}

void FinLoan::FinLoanPaymentInterface()
{
    // Labels
    hLblAmount = Widget::RLabel(45, 85, 150, 30, "Loan Amount: $", m_hWnd);
    hLblRate = Widget::RLabel(45, 125, 150, 30, "Interest Rate: %", m_hWnd);
    hLblMonths = Widget::RLabel(45, 165, 150, 30, "Number of Months:", m_hWnd);

    // Input boxes.
    hInAmount = Widget::InputBox(200, 80, 80, 30, m_hWnd);
    hInRate = Widget::InputBox(200, 120, 80, 30, m_hWnd);
    hInMonths = Widget::InputBox(200, 160, 80, 30, m_hWnd);

    // Result label and input box.
    hLblResult = Widget::RLabel(15, 205, 150, 30, "Monthly Payment: $", m_hWnd);
    hRsltFinLoan = Widget::ResultBox(170, 200, 110, 30, m_hWnd);

    // Buttons.
    hBtnCalc = Widget::Button(350, 140, 90, 30, "Calculate", m_hWnd, (HMENU)FINLOAN_CALC_PAYMENT_BUTTON);
}

void FinLoan::FinLoanDlgList(HWND hWnd)
{
    // Add items to the combo box (NULL for ID).
    SendDlgItemMessage(hWnd, NULL, CB_ADDSTRING, 0, (LPARAM)TEXT("Loan Amount"));
    SendDlgItemMessage(hWnd, NULL, CB_ADDSTRING, 0, (LPARAM)TEXT("Interest Rate"));
    SendDlgItemMessage(hWnd, NULL, CB_ADDSTRING, 0, (LPARAM)TEXT("Number of Months"));
    SendDlgItemMessage(hWnd, NULL, CB_ADDSTRING, 0, (LPARAM)TEXT("Monthly Payment"));

    // Set the initial selection
    SendDlgItemMessage(hWnd, NULL, CB_SETCURSEL, 0, 0);
}

void FinLoan::ComboBoxCommand(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
            ClearFinLoanWnd();
            ClearFinLoanText();
            FinLoanAmountInterface();
            //SetFocus(hLengthBox);
            break;
        case 1:
            ClearFinLoanWnd();
            ClearFinLoanText();
            FinLoanRateInterface();
            //SetFocus(hLengthBox);
            break;
        case 2:
            ClearFinLoanWnd();
            ClearFinLoanText();
            FinLoanMonthsInterface();
            //SetFocus(hRadiusBox);
            break;
        case 3:
            ClearFinLoanWnd();
            ClearFinLoanText();
            FinLoanPaymentInterface();
            //SetFocus(hRadiusBox);
            break;

        }

    }
}

void FinLoan::ClearFinLoanWnd()
{
    DestroyWindow(hLblMonthPay);
    DestroyWindow(hLblAmount);
    DestroyWindow(hLblRate);
    DestroyWindow(hLblMonths);
    DestroyWindow(hLblResult);
    DestroyWindow(hInMonthPay);
    DestroyWindow(hInAmount);
    DestroyWindow(hInRate);
    DestroyWindow(hInMonths);
    DestroyWindow(hRsltFinLoan);
    DestroyWindow(hBtnCalc);
}

void FinLoan::ClearFinLoanText()
{
    const char* emptyText = "";

    SetWindowText(hInMonthPay, emptyText);
    SetWindowText(hInAmount, emptyText);
    SetWindowText(hInRate, emptyText);
    SetWindowText(hInMonths, emptyText);
    SetWindowText(hRsltFinLoan, emptyText);

}

void FinLoan::ReInit()
{
    amount = 0.0;
    rate = 0.0;
    monthPay = 0.0;
    months = 0;
}

int FinLoan::UserIn(HWND hWndA, HWND hWndB, HWND hWndC)
{
    // Declare variables.
    int swVal;
    double dblResult = 0.0;
    std::string strResult;

    GetWindowText(hWndA, charArrA, 100);	// Retrieve hWndA.
    GetWindowText(hWndB, charArrB, 100);    // Retrieve hWndB.
    GetWindowText(hWndC, charArrC, 100);	// Retrieve hWndC.

    // Map message strings to input boxes.
    HandleToString(hInAmount, "Loan Amount is not a valid number!\nPlease enter Loan Amount as a valid number."
        "\nSee -- Help \\ Info-- for more information.");
    HandleToString(hInMonthPay, "Monthly Payment is not a valid number!\nPlease enter Monthly Payment as a valid number."
        "\nSee -- Help \\ Info-- for more information.");
    HandleToString(hInRate, "Interest Rate is not a valid number!\nPlease enter Interest Rate as a valid number."
        "\nSee -- Help \\ Info-- for more information.");
    HandleToString(hInMonths, "Months is not a valid number!\nPlease enter Months as a valid number."
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

double FinLoan::StringToDouble(const std::string& str)
{
    return std::stod(str);
}

std::string FinLoan::ToString(double num)
{
    std::stringstream ss;    // Declare a string stream var.

    // Set the decimal point.
    ss.setf(std::ios::fixed);
    ss.setf(std::ios::showpoint);
    ss.precision(2);

    ss << num;

    return ss.str();
}

void FinLoan::FinLoanCalcThunk(FinLoan* obj, double(FinLoan::* calc)())
{
    // Retrieve input box text.
    GetWindowText(hInAmount, amountText, 100 );
    GetWindowText(hInRate, rateText, 100);
    GetWindowText(hInMonths, monthsText, 100);
    GetWindowText(hInMonthPay, monthPayText, 100);

    // Convert  to double.
    amount = strtod(amountText, nullptr);
    rate = strtod(rateText, nullptr);
    months = (int)strtod(monthsText, nullptr);
    monthPay = strtod(monthPayText, nullptr);

    // Calculate.
    double result = (obj->*calc)();


    // Display.
    std::string resultString = ToString(result); // Get the string.
    strcpy_s(resultText, resultString.c_str());   // Convert to C-string

    SetWindowText(hRsltFinLoan, resultText);	// Display the result.

}

double FinLoan::CalcFinLoanAmount()
{
    int inOk = UserIn(hInRate, hInMonths, hInMonthPay);

    if (inOk)
    {
        double intRate = rate * 0.01 / 12;
        double rsltAmt = (monthPay / intRate) * (1 - (1 / (pow((1 + intRate), months))));

        return rsltAmt;
    }

    return 0;
}

double FinLoan::CalcFinLoanRate()
{
    int inOk = UserIn(hInAmount, hInMonths, hInMonthPay);

    if (inOk)
    {
        double r0 = 0.01;           // Initial guess for the interest rate (1%).
        double r1 = 0.0;
        double tol = 0.000001;      // Tolerance level.
        int max_iterations = 20;    // Maximum number of iterations.


        for (int i = 0; i < max_iterations; ++i)
        {
            double funcRate = NRFuncRate(r0);
            double funcRate_Prime = NRFuncRate_Prime(r0);

            if (fabs(funcRate_Prime) < tol)
            {
                return 0;
                //break;
            }

            r1 = r0 - funcRate / funcRate_Prime; // Newton-Raphson iteration.

            if (fabs(r1 - r0) < tol)  // Check for convergence
            {
                // Convert to annual percentage rate and return.
                return (pow(1 + r1, 12) - 1) * 100;

            }

            r0 = r1; // Update guess for next iteration.
        }
    }

    return 0;

}

double FinLoan::NRFuncRate(double RT)
{
    return amount * RT - monthPay * (1 - 1 / pow(1 + RT, months));
}

double FinLoan::NRFuncRate_Prime(double RT)
{
    return amount - monthPay * months * pow(1 + RT, -(months + 1));
}

double FinLoan::CalcFinLoanMonths()
{
    int inOk = UserIn(hInAmount, hInRate, hInMonthPay);

    if (inOk)
    {
        double intRate = rate * 0.01 / 12;
        double rsltAmt = log((monthPay / intRate) / ((monthPay / intRate) - amount))
            / log(1 + intRate);

        return rsltAmt;
    }

    return 0;
}

double FinLoan::CalcFinLoanPayment()
{
    int inOk = UserIn(hInAmount, hInRate, hInMonths);

    if (inOk)
    {
        double intRate = rate * 0.01 / 12;
        double rsltAmt = (amount * intRate * (pow((1 + intRate), months)))
            / (pow((1 + intRate), months) - 1);

        return rsltAmt;
    }

    return 0;
}

std::string FinLoan::GetStringFromHandle(HWND hwnd)
{
    auto it = msgBxStrMap.find(hwnd);
    if (it != msgBxStrMap.end()) {
        return it->second;
    }

    return ""; // Return an empty string if the handle is not found.
}
