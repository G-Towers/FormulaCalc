// Integration calculations.

#pragma once
#include "Window.h"

class Integrate : public BaseWindow<Integrate>
{
private:
	Integrate();
	~Integrate();

public:
	
	Integrate(const Integrate&) = delete;
	Integrate& operator=(const Integrate&) = delete;


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

	// Map to associate HWND with error strings. Used for input validation.
	std::map<HWND, std::string> msgBxStrMap;

	static BOOL integrateWndCreated;	// Flag for window created.


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