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

	void FinLoanCalcThunk(FinLoan* obj, double(FinLoan::*calc)());
	// Input conversion and calls to Calculate functions using pointer.

	double CalcFinLoanAmount();
	// Calculates the loan amount.

	double CalcFinLoanRate();
	// Calculates the loan interst rate.

	double CalcFinLoanMonths();
	// Calculates the number of months to pay the loan.

	double CalcFinLoanPayment();
	// Calculates the monthly payment.


	static BOOL flWndCreated;	// Flag for window created.
	static FinLoan finLoanObj;

private:
	HINSTANCE hInst;

	static FinLoan* inst;	// To use with InstFinLoanWnd().

	typedef double(FinLoan::*fncPtr)();		// Function Pointer.
	fncPtr calc;

	// Variables.
	double amount;
	double rate;
	double monthPay;
	int months;
	//double result;

	// Char arrays.
	char amountText[100] = { "" };
	char monthPayText[100] = { "" };
	char rateText[100] = { "" };
	char monthsText[100] = { "" };
	char resultText[100] = { "" };

	// Labels.
	HWND hLblMonthPay;
	HWND hLblAmount;
	HWND hLblRate;
	HWND hLblMonths;
	HWND hLblResult;

	// Input Boxes.
	HWND hInMonthPay;
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
