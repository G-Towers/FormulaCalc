// StanDev.h

#pragma once

#include "Window.h"

class StanDev : public BaseWindow<StanDev>
{
public:
	StanDev();

	StanDev(const StanDev&) = delete;
	StanDev& operator=(const StanDev&) = delete;

	~StanDev();

	const char* ClassName() const { return "StanDevClass"; }
	LRESULT CALLBACK HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	static StanDev& InstStanDevWnd();
	// Singleton to instantiate an object only once.

	static HINSTANCE GetInstance() noexcept;
	// Gets the handle to the instance.

	void StanDevInterface();
	// The Standard Deviation Window interface.

	void StanDevWnd();
	// Creates the Standard Deviation Window.

	void ClearStanDevText();
	// Clears the text boxes.

	void ReInit();
	// Reinitialize values (Reset to 0).

	int UserIn();
	// User input and validation.

	std::vector<std::string> split(const char* input, char delimiter);
	// Custom function to split char array into a vector of strings.

	double stringToDouble(const std::string& str);
	// Function to convert string to double.

	void CalcMean(std::vector<double>& vec);
	// Calculates the mean.

	void CalcStanDev(BOOL& eqOpt);
	// Calculates the standard deviation for population and sample size.
	// Uses BOOL reference parameter to distinguish between the two calculations.

	std::string ToString(double num);
	// Convert to string.

	static BOOL sdWndCreated;	// Flag for window created.
	static StanDev stanDevObj;

private:
	
	HINSTANCE hInst;
	
	static StanDev* inst;	// To use with InstStanDevWnd().

	// variables
	int count;
	double dev;
	double mean;
	double meanSum;
	double devSum;
	char charArr[256] = {};

	// Radio Buttons
	HWND hPopBtn;
	HWND hSampBtn;

	// Labels
	HWND hInputLabel;
	HWND hSumLabel;
	HWND hMeanLabel;
	HWND hDevResultLabel;

	// Input/result
	HWND hStanDevInput;
	HWND hSumResult;
	HWND hMeanResult;
	HWND hStanDevResult;

	// Buttons.
	HWND hCalcBtn;
	HWND hClearBtn;
	HWND hCloseBtn;

};
