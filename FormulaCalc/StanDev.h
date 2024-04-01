// StanDev.h

#pragma once

#include "Window.h"

class StanDev : public BaseWindow<StanDev>
{
public:
	StanDev();

	StanDev(const StanDev&) = delete;
	StanDev& operator=(const StanDev&) = delete;

	~StanDev();

	const char* ClassName() const { return "StanDevClass"; }
	LRESULT CALLBACK HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	static StanDev& InstStanDevWnd();
	// Singleton to instantiate an object only once.

	void InitDlg(HWND hWndOwner, HWND hDlg);

	static HINSTANCE GetInstance() noexcept;	// Gets the handle to the instance.

	void StanDevInterface();
	// The Standard Deviation Window interface.

	void StanDevWnd();
	// Creates the Standard Deviation Window.

	static BOOL sdWndCreated;

public:
	
	HINSTANCE hInst;

	static StanDev stanDevObj;
	static StanDev* inst;	// To use with InstVolWnd().

};
