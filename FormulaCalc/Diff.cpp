// Derivatives

#include "Diff.h"

Diff Diff::diffObj;
Diff* Diff::inst = nullptr;
BOOL Diff::diffWndCreated = 0;

Diff::Diff()
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

        }

        break;

    case WM_CREATE:

        break;
    case WM_SETFOCUS:
        SetFocus(diffObj.m_hWnd);
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
    if (!inst)
    {
        inst = new Diff();
    }

    return *inst;
}

HINSTANCE Diff::GetInstance() noexcept
{
    return diffObj.hInst;
}

void Diff::DiffInterface()
{

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

