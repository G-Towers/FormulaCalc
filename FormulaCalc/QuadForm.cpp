// QuadForm.cpp

#include "QuadForm.h"

QuadForm QuadForm::quadFormObj;
QuadForm* QuadForm::inst = nullptr;
BOOL QuadForm::qfWndCreated = 0;

QuadForm::QuadForm()
{

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
        //QuadFormInterface();
        break;
    case WM_SETFOCUS:
        SetFocus(m_hWnd);
        break;
    case WM_DESTROY:
        DestroyWindow(m_hWnd);
        UnregisterClass("QuadFormClass", GetModuleHandle(NULL));
        qfWndCreated = 0;
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
