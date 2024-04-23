// QuadForm.cpp

#include "QuadForm.h"

QuadForm QuadForm::quadFormObj;
QuadForm* QuadForm::inst = nullptr;
BOOL QuadForm::qfWndCreated = 0;

QuadForm::QuadForm()
{
    hInst = GetModuleHandle(NULL);

    dblA = 0.0;
    dblB = 0.0;
    dblC = 0.0;
    dblResultPlus = 0.0;
    dblResultMinus = 0.0;

    hStanFormEq = nullptr;
    hALbl = nullptr;
    hBLbl = nullptr;
    hCLbl = nullptr;
    hResultLblPlus = nullptr;
    hResultLblMinus = nullptr;
    hAIn = nullptr;
    hBIn = nullptr;
    hCIn = nullptr;
    hClearBtn = nullptr;
    hCloseBtn = nullptr;
    hCalcBtn = nullptr;
    hQuadFormResultPlus = nullptr;
    hQuadFormResultMinus = nullptr;
}

QuadForm::~QuadForm()
{

}

LRESULT QuadForm::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int wmId = LOWORD(wParam);
    int wmEvent = HIWORD(wParam);

    switch (uMsg)
    {
    case WM_COMMAND:
        switch (wmId)
        {
        case QUADFORM_CLEAR_BUTTON:
            ClearQuadFormText();
            break;
        case QUADFORM_CALC_BUTTON:
            CalcQuadForm();
            break;
        case QUADFORM_CLOSE_BUTTON:
            qfWndCreated = 0;
            UnregisterClass("QuadFormClass", GetModuleHandle(NULL));
            DestroyWindow(m_hWnd);
            
            return 0;

        }
        break;

    case WM_CREATE:
        QuadFormInterface();
        break;
    case WM_SETFOCUS:
        SetFocus(m_hWnd);
        break;
    case WM_DESTROY:
        qfWndCreated = 0;
        UnregisterClass("QuadFormClass", hInst);
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
    return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
}

void QuadForm::QuadFormWnd()
{
    if (qfWndCreated)
        SetFocus(m_hWnd);
    else
    {
        CreateWnd("Quadratic Formula", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE,
            0, 270, 270, 480, 350, GetParent(m_hWnd));
        ShowWindow(m_hWnd, SW_SHOW);
        qfWndCreated = 1;
    }
}

void QuadForm::QuadFormInterface()
{
    // Labels.
    hStanFormEq = Widget::RLabelBold(140, 25, 150, 30, "ax^2 + bx + c = 0", m_hWnd);

    hALbl = Widget::RLabel(45, 85, 150, 30, "a = ", m_hWnd);
    hBLbl = Widget::RLabel(45, 125, 150, 30, "b = ", m_hWnd);
    hCLbl = Widget::RLabel(45, 165, 150, 30, "c = ", m_hWnd);
    hResultLblPlus = Widget::RLabel(45, 205, 150, 30, "Result:   x = ", m_hWnd);
    hResultLblMinus = Widget::RLabel(45, 245, 150, 30, "Result:  -x = ", m_hWnd);

    // Input Boxes.
    hAIn = Widget::InputBox(200, 80, 80, 30, m_hWnd);       // Input box A.
    hBIn = Widget::InputBox(200, 120, 80, 30, m_hWnd);      // Input box B.
    hCIn = Widget::InputBox(200, 160, 80, 30, m_hWnd);      // Input box C.

    // Result boxes
    hQuadFormResultPlus = Widget::ResultBox(200, 200, 80, 30, m_hWnd);
    hQuadFormResultMinus = Widget::ResultBox(200, 240, 80, 30, m_hWnd);

    // Buttons.
    hCloseBtn = Widget::Button(350, 260, 90, 30, "Close", m_hWnd, (HMENU)QUADFORM_CLOSE_BUTTON);
    hClearBtn = Widget::Button(350, 190, 90, 30, "Clear", m_hWnd, (HMENU)QUADFORM_CLEAR_BUTTON);

    // Calculate.
    hCalcBtn = Widget::Button(350, 140, 90, 30, "Calculate", m_hWnd, (HMENU)QUADFORM_CALC_BUTTON);

}

void QuadForm::ClearQuadFormText()
{
    const char* emptyText = "";

    SetWindowText(hAIn, emptyText);
    SetWindowText(hBIn, emptyText);
    SetWindowText(hCIn, emptyText);
    SetWindowText(hQuadFormResultPlus, emptyText);
    SetWindowText(hQuadFormResultMinus, emptyText);

    ReInit();

    SetFocus(hAIn);
}

void QuadForm::ReInit()
{
    dblA = 0.0;
    dblB = 0.0;
    dblC = 0.0;
    dblResultPlus = 0.0;
    dblResultMinus = 0.0;
}

int QuadForm::UserIn()
{
    // Declare variables.
    int swVal;
    double dblResult = 0.0;
    std::string strResult;

    GetWindowText(hAIn, charA, 256);	// Retrieve A.
    GetWindowText(hBIn, charB, 256);	// Retrieve B.
    GetWindowText(hCIn, charC, 256);	// Retrieve C.

    // Validate user input.
    if (strcmp(charA, "") == 0 || strcmp(charB, "") == 0 || strcmp(charC, "") == 0)
    {
        swVal = MessageBoxEx(m_hWnd, "You are missing input!\nPlease enter values.",
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

    for (size_t i = 0; i < strlen(charA); i++)
    {
        if (!isdigit(charA[i]) && charA[i] != '.')
        {
            swVal = MessageBoxEx(m_hWnd, "a: is not a valid number!\nPlease enter a: as a valid number."
                "\nSee -- Help \\ Info-- for more information.", NULL, MB_OKCANCEL | MB_ICONERROR, NULL);

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

    for (size_t i = 0; i < strlen(charB); i++)
    {
        if (!isdigit(charB[i]) && charB[i] != '.')
        {
            swVal = MessageBoxEx(m_hWnd, "b: is not a valid number!\nPlease enter b: as a valid number."
                "\nSee -- Help \\ Info-- for more information.", NULL, MB_OKCANCEL | MB_ICONERROR, NULL);

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

    for (size_t i = 0; i < strlen(charC); i++)
    {
        if (!isdigit(charC[i]) && charC[i] != '.')
        {
            swVal = MessageBoxEx(m_hWnd, "c: is not a valid number!\nPlease enter c: as a valid number."
                "\nSee -- Help \\ Info-- for more information.", NULL, MB_OKCANCEL | MB_ICONERROR, NULL);

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

double QuadForm::StringToDouble(const std::string& str)
{
    return std::stod(str);
}

std::string QuadForm::ToString(double num)
{
    std::stringstream ss;    // Declare a string stream var.

    // Set the decimal point.
    ss.setf(std::ios::fixed);
    ss.setf(std::ios::showpoint);
    ss.precision(3);

    ss << num;

    return ss.str();
}

void QuadForm::CalcQuadForm()
{
    UserIn();

    // Convert to double.
    dblA = StringToDouble(charA);
    dblB = StringToDouble(charB);
    dblC = StringToDouble(charC);

    // Calculate quadratic formula.
    dblResultPlus = ( -(dblB) + sqrt(pow(dblB, 2) - 4 * dblA * dblC) )
        / (2 * dblA);

    dblResultMinus = ( -(dblB) - sqrt(pow(dblB, 2) - 4 * dblA * dblC) )
        / (2 * dblA);

    // Get strings.
    std::string strResultPlus = ToString(dblResultPlus);
    std::string strResultMinus = ToString(dblResultMinus);

    // Convert to c-strings.
    strcpy_s(charResultPlus, strResultPlus.c_str());
    strcpy_s(charResultMinus, strResultMinus.c_str());

    // Display the results.
    SetWindowText(hQuadFormResultPlus, charResultPlus);
    SetWindowText(hQuadFormResultMinus, charResultMinus);

}
