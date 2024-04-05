// StanDev.cpp

#include "StanDev.h"
StanDev StanDev::stanDevObj;
StanDev* StanDev::inst = nullptr;
BOOL StanDev::sdWndCreated = 0;

StanDev::StanDev()
{
    hInst = GetModuleHandle(NULL);

    count = 0;
    arrSize = 0;
    dev = 0.0;
    mean = 0.0;
    meanSum = 0.0;
    devSum = 0.0;
    
    arr = new double[arrSize];

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
    int wmId = LOWORD(wParam);
    int wmEvent = HIWORD(wParam);

    switch (uMsg)
    {
    case WM_COMMAND:
        switch (wmId)
        {
        //case STANDEV_POP_RADIO:
        //    if (wmEvent == BN_CLICKED)
        //        CalcStanDevPop();
        //    break;
        //case STANDEV_SMPL_RADIO:
        //    if (wmEvent == BN_CLICKED)
        //        CalcStanDevSmpl();
        //    break;
        case STANDEV_CALCULATE:
            if (wmEvent == BN_CLICKED)
            {
                BOOL sdPopChecked = SendMessage(GetDlgItem(m_hWnd, STANDEV_POP_RADIO), 
                    BM_GETCHECK, 0, 0) == BST_CHECKED;
                BOOL sdSmplChecked = SendMessage(GetDlgItem(m_hWnd, STANDEV_SMPL_RADIO),
                    BM_GETCHECK, 0, 0) == BST_CHECKED;
                if (sdPopChecked)
                    CalcStanDevPop();
                else if (sdSmplChecked)
                    CalcStanDevSmpl();

            }
            break;

        case STANDEV_CLEAR_BUTTON:

            break;
        case STANDEV_CLOSE_BUTTON:
            DestroyWindow(m_hWnd);
            UnregisterClass("VolWndClass", GetModuleHandle(NULL));
            sdWndCreated = 0;
            return 0;
            //break;
         }
        break;

    case WM_CREATE:
        StanDevInterface();
        break;
    case WM_SETFOCUS:
        SetFocus(stanDevObj.hStanDevInput);
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

HINSTANCE StanDev::GetInstance() noexcept
{
    return stanDevObj.hInst;
}

void StanDev::StanDevInterface()
{
    // Radio Buttons
    hPopBtn = Widget::ButtonRadio(30, 20, 150, 30, "Population", m_hWnd, (HMENU)STANDEV_POP_RADIO);
    hSampBtn = Widget::ButtonRadio(30, 50, 150, 30, "Sample", m_hWnd, (HMENU)STANDEV_SMPL_RADIO);
    SendMessage(hPopBtn, BM_SETCHECK, BST_CHECKED, 0);   // Set initial state.

    // Labels
    hInputLabel = Widget::LLabel(30, 95, 150, 30, "Input:", m_hWnd);
    hInputLabel = Widget::RLabel(60, 155, 150, 30, "Sum of Squares:", m_hWnd);
    hInputLabel = Widget::RLabel(60, 195, 150, 30, "Mean:", m_hWnd);
    hDevResultLabel = Widget::RLabel(60, 235, 150, 30, "Standard Deviation:", m_hWnd);

    // input/result Boxes.
    hStanDevInput = Widget::InputBoxMulti(70, 90, 230, 45, m_hWnd);      // Input.

    hSumResult = Widget::ResultBox(220, 150, 80, 30, m_hWnd);        // Sum.
    hMeanResult = Widget::ResultBox(220, 190, 80, 30, m_hWnd);       // Mean
    hStanDevResult = Widget::ResultBox(220, 230, 80, 30, m_hWnd);    // Standard Deviation.

    // Buttons.
    hClearBtn = Widget::Button(350, 190, 90, 30, "Clear", m_hWnd, (HMENU)STANDEV_CLEAR_BUTTON);
    hCloseBtn = Widget::Button(350, 260, 90, 30, "Close", m_hWnd, (HMENU)STANDEV_CLOSE_BUTTON);

    // Calculate.
    hCalcBtn = Widget::Button(350, 140, 90, 30, "Calculate", m_hWnd, (HMENU)STANDEV_CALCULATE);
}

void StanDev::StanDevWnd()
{
    if (sdWndCreated)
        SetFocus(m_hWnd);
    else
    {
        CreateWnd("Standard Deviation", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE,
            0, 270, 270, 480, 350, GetParent(m_hWnd));
        ShowWindow(m_hWnd, SW_SHOW);
        sdWndCreated = 1;
    }
}

void StanDev::UserIn()
{
    // Declare variables.
    int index = 0;
    int swVal;
    double dblUserIn, dblDevResult = 0.0;
    char charUserIn[100], charDevResult[100];
    std::string strDevResult;
    //std::istringstream iss;    // Declare a string stream var.

    GetWindowText(hStanDevInput, charUserIn, 100);	// Retrieve the volume text.

    // Validate user input.
    if (strcmp(charUserIn, "") == 0)
    {
        swVal = MessageBoxEx(m_hWnd, "You are missing input!\nPlease enter values.",
            NULL, MB_OKCANCEL | MB_ICONERROR, NULL);

        switch (swVal)
        {
        case IDCANCEL:
            DestroyWindow(m_hWnd);
            break;

        case IDOK:
            //return 0;
            break;

        }
    }

    for (size_t i = 0; i < strlen(charUserIn); i++)
    {
        if (!isdigit(charUserIn[i]) && charUserIn[i] != '.' && charUserIn[i] != ' ' && charUserIn[i] != ',')
        {
            swVal = MessageBoxEx(m_hWnd, "Input is not a valid number!\nPlease enter Input as a valid number."
                "\nSee -- Help \\ Info-- for more information.", NULL, MB_OKCANCEL | MB_ICONERROR, NULL);

            switch (swVal)
            {
            case IDCANCEL:
                DestroyWindow(m_hWnd);
                break;

            case IDOK:
                //return 0;
                break;

            }
        }
    }

    // Create string stream from char array.
    std::istringstream iss(charUserIn);
    std::string token;
    while (iss >> token)

    // Read the input.


    // Convert  to double.
    dblUserIn = strtod(charUserIn, NULL);

    // Add to array.
    for (int i = 0; i < arrSize; i++)
    {
        std::cin >> arr[i];
    }
    //if ((sizeUsed > 0) && (sizeUsed <= MAX_ARR_SIZE))
    //{
    //    for (int i = 1; i <= sizeUsed; i++)
    //    {
    //        cout << "Enter number " << i << ": ";
    //        while (!(cin >> arr[i - 1]))
    //        {

    //            cout << "Error: Enter only valid integer values.\n"
    //                << "Enter number " << i << ": ";
    //            cin.clear();
    //            cin.ignore(25, '\n');

    //        }

    //    }
    //}

}

void StanDev::CalcMean()
{
    // Read all the numbers in the array, add them up and calculate the average.
    for (int i = 0; i < arrSize; i++)
    {
        meanSum += arr[i];
        count++;
    }
    mean = meanSum / count;    // Calculate the average.
}

void StanDev::CalcStanDevPop()
{
    // User input.
    UserIn();

    // Calculate the mean.
    //CalcMean();

    //// Read all the numbers in the array to calculate the standard deviation (Population).
    //for (int i = 0; i < arrSize; i++)
    //{
    //    devSum += pow(arr[i] - mean, 2);
    //    //devCount++;
    //}
    //dev = sqrt(devSum / (count));    // Or for Sample (devCount - 1).


    // Convert result to char* arr.
    //sprintf_s(lengthText, "%f", lengthNum);

    // test.
    std::string strDevResult = "POP";
    char charDevResult[100];
    //strDevResult = ToString(dblDevResult); // Get the string.
    strcpy_s(charDevResult, strDevResult.c_str());   // Convert to C-string

    SetWindowTextA(hStanDevResult, charDevResult);	// Display the result.
}

void StanDev::CalcStanDevSmpl()
{
    // User input.
    //UserIn();

    // Calculate the mean.
    //CalcMean();

    //// Read all the numbers in the array to calculate the standard deviation (Sample).
    //for (int i = 0; i < arrSize; i++)
    //{
    //    devSum += pow(arr[i] - mean, 2);
    //    //devCount++;
    //}
    //dev = sqrt(devSum / (count - 1));

    // test.
    std::string strDevResult = "SMPL";
    char charDevResult[100];
    //strDevResult = ToString(dblDevResult); // Get the string.
    strcpy_s(charDevResult, strDevResult.c_str());   // Convert to C-string

    SetWindowTextA(hStanDevResult, charDevResult);	// Display the result.
}

std::string StanDev::ToString(double num)
{
    std::stringstream ss;    // Declare a string stream var.

    // Set the decimal point.
    ss.setf(std::ios::fixed);
    ss.setf(std::ios::showpoint);
    ss.precision(3);

    ss << num;

    return ss.str();
}




