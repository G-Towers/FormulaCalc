// CompInt.h
// Compound Interest
// Compound Interest formula: A = P * (1 + r/n) ^ nt

#pragma once
#include "Window.h"

class CompInt : public BaseWindow<CompInt>
{
private:
	CompInt();
	~CompInt();

public:
	
	// Delete copy/move semantics
	CompInt(const CompInt&) = delete;
	CompInt& operator=(const CompInt&) = delete;

	const char* ClassName() const { return "CompIntClass"; }
	LRESULT CALLBACK HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	// Main window procedure for CompInt class.
	// Handles messages for the Compound Interest Window.

	static LRESULT CALLBACK InputBoxProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	// Subclass input box procedure for handling input messages to enable TAB key navigation.
	// Each input box is subclassed and intercepted by the TAB key in their respective window procedure.
	// This allows the focus to be set manually to the next input box.

	static LRESULT CALLBACK ButtonProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	// Subclass button procedure for handling button messages.

	void HandleTabNavigation(HWND currentControl, bool shiftDown);
	// Handles TAB key navigation between input controls.


	static CompInt& InstCompIntWnd();
	// Singleton to instantiate an object only once.

	static HINSTANCE GetInstance() noexcept;
	// Gets the handle to the instance.

	void CompIntWnd();
	// Creates the Compound Interest Window.

	void CompIntInterface();
	// The Compound Interest Window interface.

	void CompIntAccruedInterface();
	// Interest plus principal, solve for A, accrued amount interface.

	void CompIntPrinAInterface();
	// Solve for P, pricipal using A interface.

	void CompIntPrinIInterface();
	// Solve for P, principal using I interface.

	void CompIntRateInterface();
	// Solve for interest rate interface.

	void CompIntTimeInterface();
	// Solve for time interface.

	void HideAllInputControls();
	// Hides all input controls.

	void ClearCompIntWnd();
	// Clears the window (removes the interface).

	void CompIntDlgList(HWND hWnd, int id);
	// Creates a combobox list for the type of calculation.

	void CompoundDlgList(HWND hwnd, int id);
	// Creates a combobox list for compound length.

	void CalcCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
	// Combobox selection conditions.

	void CompoundCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
	// Combobox selection conditions.

	void ClearCompIntText();
	// Clears the text boxes.

	void ReInit();
	// Reinitialize values (Reset to 0).

	int UserIn(HWND hWndA, HWND hWndB, HWND hWndC);
	// User input and validation.

	void HandleToString(HWND hwnd, const std::string& str) { msgBxStrMap[hwnd] = str; }
	// Function to associate an HWND with a string.

	std::string GetStringFromHandle(HWND hwnd);
	// Function to get the string associated with an HWND.

	double StringToDouble(const std::string& str);
	// Function to convert string to double.

	std::string ToString(double num);
	// Convert to string.

	void GetConvert();
	// Get input from the interface and convert to double.

	void CompIntCalcThunk(CompInt* obj, void(CompInt::* calc)());
	// Retrieves input, handles conversion and calls calculate functions using pointer.

	// ------------------------------- Calculate Functions --------------------------------
	
	/*
		Calculate function variables.

		A = Final amount (pricipal + accrued interest).
		P = Principal starting amount.
		r = Annual nominal interest rate as a decimal (r = R/100).
		R = Anual nominal interest rate as a percent.
		n = Number of compounding periods per unit of time.
		t = time in decimal years (ex: 6 months = 0.5 years). 
			Divide number of months by 12 to get the decimal years.
		I = Interest amount.
		ln = The natural logarithm used for calculating time.

	*/

	void CalcAccrued();
	// Calculate accrued amount, Pricipal + Interest.
	// A = P(1 + r/n)^nt.

	void CalcPrincAccrued();
	// Calculate principal amount, solve for P in terms of A.
	// P = A / (1 + r/n)^nt.

	void CalcPrincInt();
	// Calculate principal amount, solve for P in terms of I.
	// P = I / ((1 + r/n)^nt - 1).

	void CalcRate();
	// Calculate compound interest rate as a decimal.
	// r = n((A/P)^1/nt - 1).

	void CalcRatePercent();
	// Calculate compound interest rate as a percent.
	// R = r * 100. (Convert r to a percent).

	void CalcTime();
	// Calculate time, solve for t (ln is the natural log).
	// t = ln(A/P) / n(ln(1 + r/n)), and
	// t = (ln(A) - ln(P)) / n(ln(1 + r/n)).

	// ------------------------- Continuous Compounding Functions --------------------------
	// To be used when n = infinity.


	void CalcContAccruedPrincPlusInt();
	// Calculate Accrued amount, principal + interest.
	// A = Pe^rt.

	void CalcContPrincAccrued();
	// Calculate pricipal amount, solve for P in terms of A.
	// P = A / e^rt.

	void CalcContPrincInt();
	// Calculate pricipal amount, solve for P in terms of I.
	// P = I / (e^rt - 1).

	void CalcContRate();
	// Calculate compound interest rate as a decimal.
	// r = ln(A/P) / t.

	void CalcContTime();
	// Calculate time, solve for t.
	// t = ln(A/P) / r.	

	void ResetInterface();
	// Reset interface flags to initial state.

	void SaveInputText();
	// Saves input text from the interface.

	void RestoreInputText();
	// Restores input text to the interface.

	std::map<HWND, std::string> msgBxStrMap;	// Map to associate HWND with strings.

	static BOOL compIntWndCreated;	// Flag for window created. 
	// Used to prevent multiple instances of the window.
	

private:

	HINSTANCE hInst;
	bool accruedInterface;	// Flag for default interface (initial calculation window).


	typedef void(CompInt::* fncPtr)();		// Function Pointer.
	fncPtr calc;

	const double e = 2.718281828;		// e.

	// Variables.
	double principal;	// Principal starting amount (P).
	double accAmount;	// Accrued amount (principal + interest) (A).
	double rate;		// Annual nominal interest rate as a decimal (rate = annRate / 100) (r).
	double annRate;		// Nominal interest rate as a percent (annRate = rate * 100) (R).
	double intAmount;	// Interest Amount (I).
	double compNum;		// Number of compounding periods per unit of time (n).
	double time;		// Time in years as a decimal, 6 Months = 0.5 years, Months / 12 = years (t).

	double result;		// Final result.

	// Char arrays for input.
	char principalText[100];
	char accAmountText[100];
	char intAmountText[100];
	char annRateText[100];
	char timeText[100];
	char resultText[100];

	// strings for saves.
	std::string savedPrincipal;
	std::string savedAccAmount;
	std::string savedIntAmount;
	std::string savedAnnRate;
	std::string savedRate;
	std::string savedTime;
	std::string savedResult;


	// Groups.
	HWND hGrpInfo;

	// Radio Buttons.

	// Labels.
	HWND hLblPrincipal;
	HWND hLblAccAmount;
	HWND hLblIntAmount;
	HWND hLblAnnRate;
	HWND hLblTime;

	HWND hLblCalculate;
	HWND hLblCompound;

	HWND hLblResult;

	// Input/Result.
	HWND hInPrincipal;
	HWND hInAccAmount;
	HWND hInIntAmount;
	HWND hInAnnRate;
	HWND hInTime;

	HWND hRsltCompInt;

	// ComboBoxes.
	HWND hComboBoxCalculate;
	HWND hComboBoxCompound;


	// Buttons.
	HWND hBtnCalcAcc;
	HWND hBtnCalcPrincA;
	HWND hBtnCalcPrincI;
	HWND hBtnCalcRate;
	HWND hBtnCalcTime;

	HWND hBtnClear;
	HWND hBtnClose;

};
