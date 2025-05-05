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

	int UserIn(HWND hWndA, HWND hWndB, HWND hWndC);
	// User input and validation.

	double StringToDouble(const std::string& str);
	// Function to convert string to double.

	std::string ToString(double num);
	// Convert to string.

	void FinLoanCalcThunk(FinLoan* obj, void(FinLoan::*calc)());
	// Input conversion and calls to Calculate functions using pointer.

	void CalcFinLoanPrincipal();
	// Calculates the loan amount.

	void CalcFinLoanRate();
	// Calculates the annual interst rate.
	// Calls NRFuncRate() and NRFuncRate_Prime to calculate the annual interest
	// rate with annual compounding.

	double NRFuncRate(double RT);
	// Uses the Newton-Raphson Method to calculate annual interest rate with
	// annual compounding. RT is the rate as it updates.

	double NRFuncRate_Prime(double RT);
	// Derivative function for the Newton-Raphson Method used to calculate annual 
	// interest rate with annual compounding. RT is the rate as it updates.

	void CalcFinLoanMonths();
	// Calculates the number of months to pay the loan.

	void CalcFinLoanPayment();
	// Calculates the monthly payment.

	void HandleToString(HWND hwnd, const std::string& str) { msgBxStrMap[hwnd] = str; }
	// Function to associate an HWND with a string.

	std::string GetStringFromHandle(HWND hwnd); 
	// Function to get the string associated with an HWND.

	 
	std::map<HWND, std::string> msgBxStrMap;	// Map to associate HWND with strings.
	static BOOL flWndCreated;	// Flag for window created.
	static FinLoan finLoanObj;

private:
	HINSTANCE hInst;

	static FinLoan* inst;	// To use with InstFinLoanWnd().

	typedef void(FinLoan::*fncPtr)();		// Function Pointer.
	fncPtr calc;

	// Variables.
	double principal;	// Original amount of loan.
	double monthRate;	// Monthly rate.
	double rate;		// Annual rate.
	double monthPay;	// Monthly payment.
	int months;			// Number of monthly payments.
	double result;		// Final result.

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
