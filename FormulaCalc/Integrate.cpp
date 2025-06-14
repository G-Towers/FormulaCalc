// Integration

#include "Integrate.h"

BOOL Integrate::integrateWndCreated = 0;

Integrate::Integrate()
    :
    hInst(nullptr),
    defaultInterface(false),
    hBtnClose(nullptr)

{
}

Integrate::~Integrate()
{

}

LRESULT Integrate::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int wmId = LOWORD(wParam);
    int wmEvent = HIWORD(wParam);

    switch (uMsg)
    {
    case WM_COMMAND:
        switch (wmId)
        {
        case INTEGRATE_CLOSE_BTN:
            integrateWndCreated = 0;
            UnregisterClass("IntegrateClass", GetModuleHandle(NULL));
            DestroyWindow(m_hWnd);

            return 0;
        }

        break;

    case WM_CREATE:
        IntegrateInterface();
        break;

    case WM_SETFOCUS:
        SetFocus(m_hWnd);
        break;

    case WM_DESTROY:
        integrateWndCreated = 0;
        UnregisterClass("DerivClass", hInst);
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

Integrate& Integrate::InstIntegrateWnd()
{
    static Integrate inst;
    return inst;
}

HINSTANCE Integrate::GetInstance() noexcept
{
    return InstIntegrateWnd().hInst;
}

void Integrate::IntegrateInterface()
{
    // Buttons.
    hBtnClose = Widget::Button(350, 260, 90, 30, "Close", m_hWnd, (HMENU)INTEGRATE_CLOSE_BTN);
}

void Integrate::IntegrateWnd()
{
    if (integrateWndCreated)
        SetFocus(m_hWnd);
    else
    {
        CreateWnd("Integration", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE,
            0, 270, 270, 480, 350, GetParent(m_hWnd));
        ShowWindow(m_hWnd, SW_SHOW);
        integrateWndCreated = 1;
    }
}

void Integrate::ClearIntegrateText()
{

}

void Integrate::ReInit()
{

}

int Integrate::UserIn()
{
    return 0;
}
