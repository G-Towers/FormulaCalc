// VolWnd.h

#pragma once

#include "Window.h"

class VolWnd : public BaseWindow<VolWnd>
{
public:
	VolWnd();

	VolWnd(const VolWnd&) = delete;
	VolWnd& operator=(const VolWnd&) = delete;

	const char* ClassName() const { return "VolWndClass"; }
	LRESULT CALLBACK HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	static VolWnd& InstVolWnd();
	// Singleton to instantiate an object only once.

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

	void VolumeWnd();
	// Creates the Volume Window.

	void ClearVolumeText();
	// Clears all text boxes and resets the combobox.

	void ClearVolumeWnd();
	// Clears the window (removes the interface).

	void VolumeDlgList(HWND hWnd);
	// List in volume combo box (a simplified method).

	void ComboBoxCommand(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	// Combobox selection conditions.



	~VolWnd();

	static BOOL volWndCreated;	// Volume window is created.

public:
	double length, base, height, width, radius,
		lowRadius, result;

	static VolWnd volObj;	// Access the object from anywhere.
	static VolWnd* inst;	// To use with InstVolWnd().

	HWND hComboBoxSelItem;	// ComboBox.

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
	HWND hCalcBtn;
	HWND hClearBtn;
	HWND hCloseBtn;
	

};

void VolumeInputThunk(double(*calc)());
// Input conversion and calls to Calculate functions using pointer.

double CalcVolTriangle();
// Calculates volume of a triangular prism.

double CalcVolRectangle();
// Calculates volume of a rectangular prism.

double CalcVolSphere();
// Calculates volume of a sphere.

double CalcVolCylinder();
// Calculates volume of a cylinder.

double CalcVolCone();
// Calculates volume of a cone.

double CalcVolFrustum();
// Calculates volume of the frustum of a cone.

double CalcVolPyramid();
// Calculates volume of the frustum of a cone.

std::string ToString(double num);
// Convert double to string.