// StanDev.cpp

#include "StanDev.h"
StanDev StanDev::stanDevObj;
StanDev* StanDev::inst = nullptr;
BOOL StanDev::sdWndCreated = 0;

StanDev::StanDev()
{
    hInst = GetModuleHandle(NULL);

    count = 0;
    dev = 0.0;
    mean = 0.0;
    sum = 0.0;

    hPopBtn = nullptr;
    hSampBtn = nullptr;

    hInputLabel = nullptr;
    hSumLabel = nullptr;
    hMeanLabel = nullptr;
    hDevResultLabel = nullptr;

    hStanDevInput = nullptr;
    hSumResult = nullptr;
    hMeanResult = nullptr;
    hStanDevResult = nullptr;
    
    hCalcBtn = nullptr;
    hClearBtn = nullptr;
    hCloseBtn = nullptr;

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
        StanDevInterface();
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
    // Radio Buttons
    stanDevObj.hPopBtn = Widget::ButtonRadio(30, 20, 150, 30, "Population", m_hWnd, NULL);
    stanDevObj.hSampBtn = Widget::ButtonRadio(30, 50, 150, 30, "Sample", m_hWnd, NULL);

    // Labels
    stanDevObj.hInputLabel = Widget::LLabel(30, 95, 150, 30, "Input:", m_hWnd);
    stanDevObj.hInputLabel = Widget::RLabel(60, 135, 150, 30, "Sum of Squares:", m_hWnd);
    stanDevObj.hInputLabel = Widget::RLabel(60, 175, 150, 30, "Mean:", m_hWnd);
    stanDevObj.hDevResultLabel = Widget::RLabel(60, 215, 150, 30, "Standard Deviation:", m_hWnd);

    // input/result Boxes.
    stanDevObj.hStanDevInput = Widget::InputBox(70, 90, 230, 30, m_hWnd);      // Input.

    stanDevObj.hSumResult = Widget::ResultBox(220, 130, 80, 30, m_hWnd);        // Sum.
    stanDevObj.hMeanResult = Widget::ResultBox(220, 170, 80, 30, m_hWnd);       // Mean
    stanDevObj.hStanDevResult = Widget::ResultBox(220, 210, 80, 30, m_hWnd);    // Standard Deviation.

    // Buttons.
    stanDevObj.hClearBtn = Widget::Button(350, 190, 90, 30, "Clear", m_hWnd, (HMENU)VOLUME_CLEAR_BUTTON);
    stanDevObj.hCloseBtn = Widget::Button(350, 260, 90, 30, "Close", m_hWnd, (HMENU)VOLUME_CLOSE_BUTTON);

    // Calculate.
    stanDevObj.hCalcBtn = Widget::Button(350, 140, 90, 30, "Calculate", m_hWnd, (HMENU)STANDEV_CALCULATE);
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

void StanDev::CalculateDev(const double arr[], int sizeUsed, double& avg, double& dev)
{
    // Declare variables.
    double next = 0.0,
        avgSum = 0.0,
        devSum = 0.0;

    int avgCount = 0,
        devCount = 0;

    // Read all the numbers in the array, add them up and calculate the average.
    for (int i = 0; i < sizeUsed; i++)
    {
        avgSum += arr[i];
        avgCount++;
    }
    avg = avgSum / avgCount;    // Calculate the average.

    // Read all the numbers in the array to calculate the standard deviation.
    for (int i = 0; i < sizeUsed; i++)
    {
        devSum += pow(arr[i] - avg, 2);
        devCount++;
    }
    dev = sqrt(devSum / (devCount));    // Or for Sample (devCount - 1).
}


