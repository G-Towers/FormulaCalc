// CompInt.h
// Compound Interest
// Compound Interest formula: A = P * (1 + r/n) ^ nt

#pragma once
#include "Window.h"

class CompInt : public BaseWindow<CompInt>
{
public:
	CompInt();

	CompInt(const CompInt&) = delete;
	CompInt& operator=(const CompInt&) = delete;

	~CompInt();

	const char* ClassName() const { return "CompIntClass"; }
	LRESULT CALLBACK HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	static CompInt& InstCompIntWnd();
	// Singleton to instantiate an object only once.

	static HINSTANCE GetInstance() noexcept;
	// Gets the handle to the instance.

	void CompIntInterface();
	// The Compound Interest Window interface.

	void CompIntWnd();
	// Creates the Compound Interest Window.

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

	void CompIntCalcThunk(CompInt* obj, void(CompInt::* calc)());
	// Input conversion and calls to Calculate functions using pointer.

	void CalcCompoundInt();
	// Initial test calculation.


	std::map<HWND, std::string> msgBxStrMap;	// Map to associate HWND with strings.
	static BOOL compIntWndCreated;	// Flag for window created.
	static CompInt compIntObj;

private:

	HINSTANCE hInst;

	static CompInt* inst;	// To use with InstDiffWnd().

	const double e = 2.718281828;		// e.

	// Variables.
	double finAmount;	// Final Amount (principal + accrued interest) (A).
	double principal;	// Principal starting amount (P).
	double rate;		// Annual nominal interest rate as a decimal (r).
	double ratePercent;	// Nominal interest rate as a percent (ratePrecent = rate / 100) (R).
	double intAmount;	// Interest Amount (I).
	double compNum;		// Number of compounding periods per unit of time (n).
	double time;		// Time in years as a decimal, 6 Months = 0.5 years, Months / 12 = years (t).
	double ln;			// Natural log (ln).

	// Char arrays.
	char amountText[100] = { "" };
	char monthPayText[100] = { "" };
	char rateText[100] = { "" };
	char monthsText[100] = { "" };
	char resultText[100] = { "" };

	char charArrA[100] = { "" };
	char charArrB[100] = { "" };
	char charArrC[100] = { "" };
	char charArrD[100] = { "" };

	// Radio Buttons.

	// Labels.
	HWND hLblPrincipal;
	HWND hLblAnnRate;
	HWND hLblCompound;
	HWND hLblTime;

	HWND hLblResult;

	// Input/Result.
	HWND hInPrincipal;
	HWND hInAnnRate;
	HWND hInCompound;
	HWND hInTime;

	HWND hRsltCompInt;

	// ComboBoxes.
	HWND hComboBoxSelItem;
	HWND hComboBoxCompound;


	// Buttons.
	HWND hBtnCalc;
	HWND hBtnClear;
	HWND hBtnClose;

};
