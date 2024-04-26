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
    meanSum = 0.0;
    devSum = 0.0;

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
                    CalcStanDev(sdPopChecked);
                else if (sdSmplChecked)
                    CalcStanDev(sdPopChecked);

            }
            break;

        case STANDEV_CLEAR_BUTTON:
            ClearStanDevText();
            break;
        case STANDEV_CLOSE_BUTTON:
            sdWndCreated = 0;
            UnregisterClass("StanDevClass", hInst);
            DestroyWindow(m_hWnd);
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
        sdWndCreated = 0;
        UnregisterClass("StanDevClass", hInst);
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
    hDevResultLabel = Widget::RLabelBold(60, 155, 150, 30, "Standard Deviation:", m_hWnd);
    hMeanLabel = Widget::RLabel(60, 195, 150, 30, "Mean:", m_hWnd);
    hSumLabel = Widget::RLabel(60, 235, 150, 30, "Sum of Squares:", m_hWnd);

    // input/result Boxes.
    hStanDevInput = Widget::InputBoxMulti(70, 90, 230, 45, m_hWnd);  // Input.

    hStanDevResult = Widget::ResultBox(220, 150, 80, 30, m_hWnd);    // Standard Deviation.
    hMeanResult = Widget::ResultBox(220, 190, 80, 30, m_hWnd);       // Mean
    hSumResult = Widget::ResultBox(220, 230, 80, 30, m_hWnd);        // Sum.

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

void StanDev::ClearStanDevText()
{
    const char* emptyText = "";

    SetWindowText(hStanDevInput, emptyText);
    SetWindowText(hStanDevResult, emptyText);
    SetWindowText(hMeanResult, emptyText);
    SetWindowText(hSumResult, emptyText);

    ReInit();

    SetFocus(hStanDevInput);

}

void StanDev::ReInit()
{
    count = 0;
    dev = 0.0;
    mean = 0.0;
    meanSum = 0.0;
    devSum = 0.0;
}

int StanDev::UserIn()
{
    // Declare variables.
    int index = 0;
    int swVal;
    double dblDevResult = 0.0;
    std::string strDevResult;
    

    GetWindowText(hStanDevInput, charArr, 256);	// Retrieve the volume text.

    // Validate user input.
    if (strcmp(charArr, "") == 0)
    {
        swVal = MessageBoxEx(m_hWnd, "You are missing input!\nPlease enter values.",
            NULL, MB_OKCANCEL | MB_ICONERROR, NULL);

        switch (swVal)
        {
        case IDCANCEL:
            DestroyWindow(m_hWnd);
            return 0;
            //break;

        case IDOK:
            return 0;
            //break;

        }
    }

    for (size_t i = 0; i < strlen(charArr); i++)
    {
        if (!isdigit(charArr[i]) && charArr[i] != '.' && charArr[i] != ' ' &&
            charArr[i] != ',' && charArr[i] != '\n')
        {
            swVal = MessageBoxEx(m_hWnd, "Input is not a valid number!\nPlease enter Input as a valid number."
                "\nSee -- Help \\ Info-- for more information.", NULL, MB_OKCANCEL | MB_ICONERROR, NULL);

            switch (swVal)
            {
            case IDCANCEL:
                DestroyWindow(m_hWnd);
                return 0;
                //break;

            case IDOK:
                return 0;
                //break;

            }
        }
    }
    return (BOOL)TRUE;

}

std::vector<std::string> StanDev::split(const char* input, char delimiter)
{
    std::vector<std::string> result;    // Vector of strings.
    //std::vector<std::string> tempVec;   // temporary vector.
    std::istringstream iss(input);
    std::string token;
    std::string combined;
    // Character to be removed
    char charToRemove = ',';

    // Remove white space.
    while (iss >> token)
    {
        result.push_back(token);
    }
    
    // Remove all commas.
    // Iterate over each string in the vector and remove commas.
    for (auto& str : result) 
    {
        str.erase(std::remove(str.begin(), str.end(), ','), str.end());
        //str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    }

    token.clear();  // Clear the token.

    //
    result.erase(std::remove(result.begin(), result.end(), ""), result.end());

    //// Remove trailing commas from the vector.
    //for (std::string& str : result)
    //{
    //    if (!str.empty() && str.back() == ',') 
    //    {
    //        str.erase(str.size() - 1);
    //    }
    //}

    // Iterate through the vector and create char arr.
    for (const auto& str : result)
    {
        combined += str;
        combined += ", ";
    }
    // Remove trailing comma.
    combined = combined.substr(0, combined.find_last_of(","));

    // Removes all commas in a string.
    //combined.erase(std::remove(combined.begin(), combined.end(), ','), combined.end());   
     
    const char* charIn = combined.c_str();   // convert to char arr.
    result = {}; // Reset result.

    SetWindowText(hStanDevInput, charIn);

    for (const char* c = charIn; *c != '\0'; ++c) // Use pointer to iterate through the char array.
    {
        if (*c == delimiter)
        {
            result.push_back(token);    // Add to the vector.
            token.clear();  // Empty the string.
        }
        else
        {
            if (*c != ' ')  // Ignore spaces.
                token += *c;    // Add to the string.
        }

    }
    if (!token.empty()) // If string is not empty.
    {
        result.push_back(token);    // Add to the vector.
    }

    return result;
}

double StanDev::stringToDouble(const std::string& str)
{
    return std::stod(str);
}

void StanDev::CalcMean(std::vector<double>& vec)
{
    // Read all the numbers in the array, add them up and calculate the average.
    for (int i = 0; i < vec.size(); i++)
    {
        meanSum += vec[i];
        count++;
    }
    mean = meanSum / count;    // Calculate the average.
}

void StanDev::CalcStanDev(BOOL& eqOpt)
{
    char charDev[256];
    char charMean[256];
    char charSum[256];
    std::string strDev = "";
    std::string strMean = "";
    std::string strSum = "";

    //// Lambdas.
    //auto eqModPop = [this]() {dev = sqrt(devSum / count); };
    //auto eqModSmpl = [this]() {dev = sqrt(devSum / (count - 1)); };

    // User input.
    int inOk = UserIn();

    if (inOk)   // Process only if input is valid.
    {
        // Split using custom delimiter
        std::vector<std::string> strVec = split(charArr, ',');

        // Create a vector of doubles with the same size as the string vector.
        std::vector<double> dblVec(strVec.size());

        // Split using custom delimiter
        strVec = split(charArr, ',');

        // Convert each string to a double and store it in the double vector using lambda.
        std::transform(strVec.begin(), strVec.end(), dblVec.begin(),
            [](const std::string& str) { return std::stod(str); });

        ReInit();   // Re-Initialize.

        // Calculate the mean.
        CalcMean(dblVec);

        // Read all the numbers in the array to calculate the standard deviation (Population).
        for (int i = 0; i < dblVec.size(); i++)
        {
            devSum += pow(dblVec[i] - mean, 2);
            //count++;
        }

        // Determine which calculation to apply.
        if (eqOpt)
            dev = sqrt(devSum / count);
        else
            dev = sqrt(devSum / (count - 1));

        strDev = ToString(dev); // Get the string.  
        strMean = ToString(mean); // Get the Mean.
        strSum = ToString(devSum); // Get the sum of squares.

        strcpy_s(charDev, strDev.c_str());   // Convert to C-string
        strcpy_s(charMean, strMean.c_str());
        strcpy_s(charSum, strSum.c_str());

        SetWindowText(hSumResult, charSum);
        SetWindowText(hMeanResult, charMean);
        SetWindowText(hStanDevResult, charDev);	// Display the result.
    }

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




