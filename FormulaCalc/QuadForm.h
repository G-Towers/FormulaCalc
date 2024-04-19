// QuadForm.h

#pragma once

#include "Window.h"

class QuadForm : public BaseWindow<QuadForm>
{
public:
	QuadForm();

	QuadForm(const QuadForm&) = delete;
	QuadForm& operator=(const QuadForm&) = delete;

	~QuadForm();

	const char* ClassName() const { return "QuadFormClass"; }
	LRESULT CALLBACK HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void QuadFormWnd();
	// Creates the Quadratic Formula Window.


	static BOOL qfWndCreated;	// Flag for window created.
	static QuadForm quadFormObj;

private:
	HINSTANCE hInst;

	static QuadForm* inst;	// To use with InstStanDevWnd().


};