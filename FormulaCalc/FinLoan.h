// FinLoan.h

#pragma once

#include "Window.h"

class FinLoan : public BaseWindow<FinLoan>
{
public:
	FinLoan();

	FinLoan(const FinLoan&) = delete;
	FinLoan& operator=(const FinLoan&) = delete;

	~FinLoan();

	const char* ClassName() const { return "FinLoanClass"; }
	LRESULT CALLBACK HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void FinLoanWnd();
	// Creates the Finance Loan Window.

	void FinLoanInterface();
	// The Finance Loan Window interface.

	void FinLoanAmountInterface();
	// Labels and text boxes for amount calculation.

	void FinLoanRateInterface();
	// Labels and text boxes for rate calculation.

	void FinLoanMonthsInterface();
	// Labels and text boxes for number of months calculation.

	void FinLoanPaymentInterface();
	// Labels and text boxes for Payment calculation.

	void FinLoanDlgList(HWND hWnd);
	// Creates the list in the combo box.

	void ComboBoxCommand(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	// Combobox selection conditions.

	void ClearFinLoanWnd();
	// Clears the window (removes the interface).

	void ClearFinLoanText();
	// Clears the text boxes.

	void ReInit();
	// Reinitialize values (Reset to 0).

	int UserIn();
	// User input and validation.

	double StringToDouble(const std::string& str);
	// Function to convert string to double.

	std::string ToString(double num);
	// Convert to string.

	void CalcFinLoan();
	// Calculates the quadratic formula.

	static BOOL flWndCreated;	// Flag for window created.
	static FinLoan finLoanObj;

private:
	HINSTANCE hInst;

	static FinLoan* inst;	// To use with InstFinLoanWnd().

	// Labels.
	HWND hLblAmount;
	HWND hLblRate;
	HWND hLblMonths;

	// Input Boxes.
	HWND hInAmount;
	HWND hInRate;
	HWND hInMonths;

	//Result boxes.
	HWND hRsltFinLoan;
	

	// Buttons
	HWND hBtnCalc;
	HWND hBtnClear;
	HWND hBtnClose;
};
