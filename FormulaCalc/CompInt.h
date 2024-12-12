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

	void CompIntDlgList(HWND hWnd);
	// Creates the list in the combo box.

	void ComboBoxCommand(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	// Combobox selection conditions.

	void CompIntText();
	// Clears the text boxes.

	void ReInit();
	// Reinitialize values (Reset to 0).

	int UserIn();
	// User input and validation.

	static BOOL compIntWndCreated;	// Flag for window created.
	static CompInt compIntObj;

private:

	HINSTANCE hInst;

	static CompInt* inst;	// To use with InstDiffWnd().

	// Variables.
	double finAmount;	// Final Amount (principal + accrued interest)
	double principal;	// Principal starting amount.
	double rate;		// Annual nominal interest rate as a decimal.
	int ratePercent;	// Nominal interest rate as a percent (ratePrecent = rate / 100).
	double intAmount;	// Interest Amount.
	int compNum;		// Number of compounding periods.
	double time;		// Time in years as a decimal.

	// Radio Buttons.

	// Labels.

	// Input/Result.

	// Buttons.
	HWND hBtnCalc;
	HWND hBtnClear;
	HWND hBtnClose;

};
