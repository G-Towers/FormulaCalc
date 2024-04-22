// QuadForm.cpp

#include "QuadForm.h"

QuadForm QuadForm::quadFormObj;
QuadForm* QuadForm::inst = nullptr;
BOOL QuadForm::qfWndCreated = 0;

QuadForm::QuadForm()
{
    hInst = GetModuleHandle(NULL);

    hStanFormEq = nullptr;
    hA = nullptr;
    hB = nullptr;
    hC = nullptr;
    hAIn = nullptr;
    hBIn = nullptr;
    hCIn = nullptr;
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

        //case QUADFORM_CLEAR_BUTTON:
        //    ClearStanDevText();
        //    break;
        //case QUADFORM_CLOSE_BUTTON:
        //    DestroyWindow(m_hWnd);
        //    UnregisterClass("QuadFormClass", GetModuleHandle(NULL));
        //    qfWndCreated = 0;
        //    return 0;
        //    //break;
        }
        //break;

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

    hA = Widget::RLabel(45, 85, 150, 30, "a = ", m_hWnd);
    hB = Widget::RLabel(45, 125, 150, 30, "b = ", m_hWnd);
    hC = Widget::RLabel(45, 165, 150, 30, "c = ", m_hWnd);

    // Input Boxes.
    hAIn = Widget::InputBox(200, 80, 80, 30, m_hWnd);       // Input box A.
    hBIn = Widget::InputBox(200, 120, 80, 30, m_hWnd);      // Input box B.
    hCIn = Widget::InputBox(200, 160, 80, 30, m_hWnd);      // Input box C.


}
