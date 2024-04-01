// StanDev.cpp

#include "StanDev.h"
StanDev StanDev::stanDevObj;
StanDev* StanDev::inst = nullptr;
BOOL StanDev::sdWndCreated = 0;

StanDev::StanDev()
{
    hInst = GetModuleHandle(NULL);
}

StanDev::~StanDev()
{

}

LRESULT StanDev::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:

        break;
    case WM_CREATE:

        break;
    case WM_SETFOCUS:
        SetFocus(m_hWnd);
        break;
    case WM_DESTROY:
        DestroyWindow(m_hWnd);
        UnregisterClass("VolWndClass", GetModuleHandle(NULL));
        sdWndCreated = 0;
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

StanDev& StanDev::InstStanDevWnd()
{
    if (!inst)
    {
        inst = new StanDev();
    }

    return *inst;
}

void StanDev::InitDlg(HWND hWndOwner, HWND hDlg)
{
    //HWND hwndOwner;
    RECT rc, rcDlg, rcOwner;

    // Get the owner window and dialog box rectangles. 

    if ((hWndOwner = GetParent(hDlg)) == NULL)
    {
        hWndOwner = GetDesktopWindow();
    }

    GetWindowRect(hWndOwner, &rcOwner);
    GetWindowRect(hDlg, &rcDlg);
    CopyRect(&rc, &rcOwner);

    // Offset the owner and dialog box rectangles so that right and bottom 
    // values represent the width and height, and then offset the owner again 
    // to discard space taken up by the dialog box. 

    OffsetRect(&rcDlg, -rcDlg.left, -rcDlg.top);
    OffsetRect(&rc, -rc.left, -rc.top);
    OffsetRect(&rc, -rcDlg.right, -rcDlg.bottom);

    // The new position is the sum of half the remaining space and the owner's 
    // original position. 

    SetWindowPos(hDlg,
        HWND_TOP,
        rcOwner.left + (rc.right / 2),
        rcOwner.top + (rc.bottom / 2),
        0, 0,          // Ignores size arguments. 
        SWP_NOSIZE);

    

}

HINSTANCE StanDev::GetInstance() noexcept
{
    return stanDevObj.hInst;
}

void StanDev::StanDevInterface()
{

}

void StanDev::StanDevWnd()
{
    if (StanDev::stanDevObj.sdWndCreated)
        SetFocus(StanDev::stanDevObj.GetWinHandle());
    else
    {
        StanDev::stanDevObj.CreateWnd("Standard Deviation", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE,
            0, 270, 270, 480, 350, GetParent(m_hWnd));
        ShowWindow(StanDev::stanDevObj.GetWinHandle(), SW_SHOW);
        StanDev::stanDevObj.sdWndCreated = 1;
    }
}


