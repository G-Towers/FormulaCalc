// Differentiation calculations.

#pragma once
#include "Window.h"

class Diff : public BaseWindow<Diff>
{
private:
	Diff();
	~Diff();

public:

	Diff(const Diff&) = delete;
	Diff& operator=(const Diff&) = delete;

	const char* ClassName() const { return "DiffClass"; }
	LRESULT CALLBACK HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	static Diff& InstDiffWnd();
	// Singleton to instantiate an object only once.

	static HINSTANCE GetInstance() noexcept;
	// Gets the handle to the instance.

	void DiffInterface();
	// The Differentiation Window interface.

	void DiffWnd();
	// Creates the Differentiation Window.

	void ClearDiffText();
	// Clears the text boxes.

	void ReInit();
	// Reinitialize values (Reset to 0).

	int UserIn();
	// User input and validation.

	// Map to associate HWND with error strings. Used for input validation.
	std::map<HWND, std::string> msgBxStrMap;

	static BOOL diffWndCreated;	// Flag for window created.


private:

	HINSTANCE hInst;
	bool defaultInterface;	// Flag for default interface (initial calculation window).


	// Variables.

	// Radio Buttons.

	// Labels.

	// Input/Result.

	// Buttons.
	HWND hBtnClose;

};

