// Differentiation calculations.

#pragma once

#include "Window.h"

class Diff : public BaseWindow<Diff>
{
public:
	Diff();

	Diff(const Diff&) = delete;
	Diff& operator=(const Diff&) = delete;

	~Diff();

	const char* ClassName() const { return "DerivClass"; }
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



	static BOOL diffWndCreated;	// Flag for window created.
	static Diff diffObj;

private:

	HINSTANCE hInst;

	static Diff* inst;	// To use with InstDiffWnd().

	// Variables.

	// Radio Buttons.

	// Labels.

	// Input/Result.

	// Buttons.


};

