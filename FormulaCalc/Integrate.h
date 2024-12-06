// Integration calculations.

#pragma once
#include "Window.h"

class Integrate : public BaseWindow<Integrate>
{
public:
	Integrate();

	Integrate(const Integrate&) = delete;
	Integrate& operator=(const Integrate&) = delete;

	~Integrate();

	const char* ClassName() const { return "IntegrateClass"; }
	LRESULT CALLBACK HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	static Integrate& InstIntegrateWnd();
	// Singleton to instantiate an object only once.

	static HINSTANCE GetInstance() noexcept;
	// Gets the handle to the instance.

	void IntegrateInterface();
	// The Integration Window interface.

	void IntegrateWnd();
	// Creates the Integration Window.

	void ClearIntegrateText();
	// Clears the text boxes.

	void ReInit();
	// Reinitialize values (Reset to 0).

	int UserIn();
	// User input and validation.

	static BOOL integrateWndCreated;	// Flag for window created.
	static Integrate integrateObj;

private:
	HINSTANCE hInst;

	static Integrate* inst;	// To use with InstDiffWnd().

	// Variables.

	// Radio Buttons.

	// Labels.

	// Input/Result.

	// Buttons.
};