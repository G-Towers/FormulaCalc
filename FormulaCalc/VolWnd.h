// VolWnd.h

#pragma once

#include "Window.h"

class VolWnd : public BaseWindow<VolWnd>
{
private:
	VolWnd();
	// Constructor to initialize the Volume Window.

	~VolWnd();
	// Destructor to clean up the Volume Window.

public:
	
	VolWnd(const VolWnd&) = delete;
	VolWnd& operator=(const VolWnd&) = delete;

	const char* ClassName() const { return "VolWndClass"; }
	LRESULT CALLBACK HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	// Main window procedure for VolWnd class.

	static LRESULT CALLBACK VolWndInputProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	// Subclass input box procedure for handling input messages to enable TAB key navigation.
	// Each input box is subclassed and intercepted by the TAB key in their respective window procedure.
	// This allows the focus to be set manually to the next input box.

	static INT_PTR CALLBACK VolWndDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	// Dialog procedure for the modal dialog box used in the Volume Window.

	static VolWnd& InstVolWnd();
	// Singleton to instantiate an object only once.

	static HINSTANCE GetInstance() noexcept;
	// Gets the handle to the instance.

	void VolumeWnd();
	// Creates the Volume Window.

	void VolumeInterface();
	// The Calculate Volume Dialog box interface.

	void VolTriInterface();
	// Labels and text boxes for triangular prism volume calculation.

	void VolRectInterface();
	// Labels and text boxes for rectangular prism volume calculation.

	void VolSphereInterface();
	// Labels and text boxes for sphere volume calculation.

	void VolCylinderInterface();
	// Labels and text boxes for cylinder volume calculation.

	void VolConeInterface();
	// Labels and text boxes for cone volume calculation.

	void VolFrusConeInterface();
	// Labels and text boxes for frustum of a cone volume calculation.

	void VolPyramidInterface();
	// Labels and text boxes for pyramid volume calculation.

	void HideInputControls();
	// Hides all input controls (text boxes, labels).

	void ClearVolumeText();
	// Clears all text boxes and resets the combobox.

	void ClearVolumeWnd();
	// Clears the window (removes the interface).

	void VolumeDlgList(HWND hWnd);
	// List in volume combo box (a simplified method).

	void ComboBoxCommand(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	// Combobox selection conditions.

	void ReInit();
	// Reinitialize values (Reset to 0).

	int UserIn(HWND hWndA, HWND hWndB, HWND hWndC);
	// User input and validation.

	int UserIn(HWND hWndA, HWND hWndB);
	// Overloaded user input and validation.

	int UserIn(HWND hWndA);
	// Overloaded user input and validation.

	void HandleToString(HWND hwnd, const std::string& str) { msgBxStrMap[hwnd] = str; }
	// Function to associate an HWND with a string.

	void GetErrorStrings();
	// Gets error strings for user input validation.

	std::string GetStringFromHandle(HWND hwnd);
	// Function to get the string associated with an HWND.

	void VolumeInputThunk(VolWnd* obj, void(VolWnd::*calc)());
	// Input conversion and calls to Calculate functions using pointer.

	void CalcVolTriangle();
	// Calculates volume of a triangular prism.

	void CalcVolRectangle();
	// Calculates volume of a rectangular prism.

	void CalcVolSphere();
	// Calculates volume of a sphere.

	void CalcVolCylinder();
	// Calculates volume of a cylinder.

	void CalcVolCone();
	// Calculates volume of a cone.

	void CalcVolFrustum();
	// Calculates volume of the frustum of a cone.

	void CalcVolPyramid();
	// Calculates volume of the frustum of a cone.

	std::string ToString(double num);
	// Convert double to string.
	

	std::map<HWND, std::string> msgBxStrMap;	// Map to associate HWND with strings.
	static BOOL volWndCreated;	// Volume window is created.

private:

	HINSTANCE hInst;
	bool defaultInterface;	// Default interface flag.

	const double PI = 3.141592654;
	double length, base, height, width, radius,
		lowRadius, result;


	typedef void(VolWnd::* fncPtr)();		// Function Pointer.
	fncPtr calc;

	HBITMAP hBitmap;	// Image handle for loading bitmap image.
	HBITMAP hBitmap2;

	HWND hStatBitmap;	// Bitmap static image.
	HWND hBtnBitmap;	// Bitmap button image.

	HWND hComboBoxSelItem;	// ComboBox.

	// Char arrays.
	char charArrA[100] = { "" };
	char charArrB[100] = { "" };
	char charArrC[100] = { "" };
	char charArrD[100] = { "" };
	char charArrE[100] = { "" };
	char charArrF[100] = { "" };

	char resultText[100] = { "" };

	// Labels
	HWND hLengthLabel;
	HWND hBaseLabel;
	HWND hWidthLabel;
	HWND hHeightLabel;
	HWND hRadiusLabel;
	HWND hLowRadiusLabel;
	HWND hResultLabel;

	// Input Boxes.
	HWND hLengthBox;
	HWND hBaseBox;
	HWND hWidthBox;
	HWND hHeightBox;
	HWND hRadiusBox;
	HWND hLowRadiusBox;
	HWND hResultBox;	// Calculation Result.

	// Buttons.
	HWND hTriCalcBtn;		// Calculate Button.
	HWND hRectCalcBtn;
	HWND hSphereCalcBtn;
	HWND hCylinderCalcBtn;
	HWND hConeCalcBtn;
	HWND hFrusConeCalcBtn;
	HWND hPyramidCalcBtn;


	HWND hClearBtn;
	HWND hCloseBtn;
	

};


