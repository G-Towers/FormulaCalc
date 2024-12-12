// CompInt.cpp
// Compound Interest

#include "CompInt.h"

CompInt CompInt::compIntObj;
CompInt* CompInt::inst = nullptr;
BOOL CompInt::compIntWndCreated = 0;

CompInt::CompInt()
{

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
        switch (wmId)
        {

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
    // ComboBox.
    HWND hComboBoxSelItem = Widget::ComboBox(25, 25, 265, 150, "", m_hWnd, hInst);
    CompIntDlgList(m_hWnd);

    // Buttons.
    hBtnClear = Widget::Button(350, 190, 90, 30, "Clear", m_hWnd, (HMENU)FINLOAN_CLEAR_BUTTON);
    hBtnClose = Widget::Button(350, 260, 90, 30, "Close", m_hWnd, (HMENU)FINLOAN_CLOSE_BUTTON);

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

void CompInt::CompIntDlgList(HWND hWnd)
{
    // Add items to the combo box (NULL for ID).
    SendDlgItemMessage(hWnd, NULL, CB_ADDSTRING, 0, (LPARAM)TEXT("Total P + I"));
    SendDlgItemMessage(hWnd, NULL, CB_ADDSTRING, 0, (LPARAM)TEXT("Principal Using A"));
    SendDlgItemMessage(hWnd, NULL, CB_ADDSTRING, 0, (LPARAM)TEXT("Principal Using I"));
    SendDlgItemMessage(hWnd, NULL, CB_ADDSTRING, 0, (LPARAM)TEXT("Rate"));
    SendDlgItemMessage(hWnd, NULL, CB_ADDSTRING, 0, (LPARAM)TEXT("Time"));

    // Set the initial selection
    SendDlgItemMessage(hWnd, NULL, CB_SETCURSEL, 0, 0);
}

void CompInt::ComboBoxCommand(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // Combo Box, simplified.
    if (HIWORD(wParam) == CBN_SELCHANGE)
    {
        // User selected an item
        int selectedIndex = (int)SendDlgItemMessage(hWnd, NULL, CB_GETCURSEL, 0, 0);	// Get the index.
        char selectedText[256] = {};
        SendDlgItemMessage(hWnd, NULL, CB_GETLBTEXT, selectedIndex, (LPARAM)selectedText);

        switch (selectedIndex)
        {
        case 0:
            break;

        case 1:
            break;

        case 2:
            break;

        }
    }

}

void CompInt::CompIntText()
{

}

void CompInt::ReInit()
{

}

int CompInt::UserIn()
{
    return 0;
}
