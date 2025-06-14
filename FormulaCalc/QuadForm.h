// QuadForm.h

#pragma once

#include "Window.h"

class QuadForm : public BaseWindow<QuadForm>
{
private:
	QuadForm();
	~QuadForm();

public:
	
	QuadForm(const QuadForm&) = delete;
	QuadForm& operator=(const QuadForm&) = delete;
	

	const char* ClassName() const { return "QuadFormClass"; }
	LRESULT CALLBACK HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	static QuadForm& InstQuadFormWnd();
	// Singleton to instantiate an object only once.

	static HINSTANCE GetInstance() noexcept;
	// Gets the handle to the instance.

	void QuadFormWnd();
	// Creates the Quadratic Formula Window.

	void QuadFormInterface();
	// The Quadratic Formula Window interface.

	void ClearQuadFormText();
	// Clears the text boxes.

	void ReInit();
	// Reinitialize values (Reset to 0).

	int UserIn();
	// User input and validation.

	double StringToDouble(const std::string& str);
	// Function to convert string to double.

	std::string ToString(double num);
	// Convert to string.

	void CalcQuadForm();
	// Calculates the quadratic formula.

	static BOOL qfWndCreated;	// Flag for window created.

private:

	HINSTANCE hInst;
	bool defaultInterface;	// Flag for default interface (initial calculation window).

	// Variables.
	double dblA;
	double dblB;
	double dblC;
	double dblDiscrim;
	double dblResultPlus;
	double dblResultMinus;

	char charA[256] = {};
	char charB[256] = {};
	char charC[256] = {};
	char charResultPlus[256] = {};
	char charResultMinus[256] = {};

	// Labels
	HWND hStanFormEq;
	HWND hALbl;
	HWND hBLbl;
	HWND hCLbl;
	HWND hResultLblPlus;
	HWND hResultLblMinus;

	// Input Boxes.
	HWND hAIn;
	HWND hBIn;
	HWND hCIn;

	// Result Boxes.
	HWND hQuadFormResultPlus;
	HWND hQuadFormResultMinus;

	// Buttons.
	HWND hClearBtn;
	HWND hCloseBtn;
	HWND hCalcBtn;

};