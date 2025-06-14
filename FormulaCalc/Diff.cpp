// Derivatives

#include "Diff.h"

BOOL Diff::diffWndCreated = 0;

Diff::Diff()
    :
    hInst(nullptr),
    defaultInterface(false),
    hBtnClose(nullptr)


{
}

Diff::~Diff()
{

}

LRESULT Diff::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int wmId = LOWORD(wParam);
	int wmEvent = HIWORD(wParam);

    switch (uMsg)
    {
    case WM_COMMAND:
        switch (wmId)
        {
        case DIFF_CLOSE_BTN:
            diffWndCreated = 0;
            UnregisterClass("DiffClass", GetModuleHandle(NULL));
            DestroyWindow(m_hWnd);

            return 0;
        }

        break;

    case WM_CREATE:
        DiffInterface();
        break;

    case WM_SETFOCUS:
        SetFocus(m_hWnd);
        break;

    case WM_DESTROY:
        diffWndCreated = 0;
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

Diff& Diff::InstDiffWnd()
{
    static Diff inst;
    return inst;
}

HINSTANCE Diff::GetInstance() noexcept
{
    return InstDiffWnd().hInst;
}

void Diff::DiffInterface()
{
    // Buttons.
    hBtnClose = Widget::Button(350, 260, 90, 30, "Close", m_hWnd, (HMENU)DIFF_CLOSE_BTN);
}

void Diff::DiffWnd()
{
    if (diffWndCreated)
        SetFocus(m_hWnd);
    else
    {
        CreateWnd("Differentiation", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE,
            0, 270, 270, 480, 350, GetParent(m_hWnd));
        ShowWindow(m_hWnd, SW_SHOW);
        diffWndCreated = 1;
    }
}

void Diff::ClearDiffText()
{

}

void Diff::ReInit()
{

}

int Diff::UserIn()
{
    return 0;
}

