// VolWnd.h

#pragma once

#include "Window.h"

#define VOLUME_CLEAR_BUTTON					40008
#define VOLUME_CLOSE_BUTTON					40009

#define VOLUME_CALCULATE_TRI_BUTTON			40010
#define VOLUME_CALCULATE_RECT_BUTTON		40011
#define VOLUME_CALCULATE_SPHERE_BUTTON		40012
#define VOLUME_CALCULATE_CYLINDER_BUTTON	40013
#define VOLUME_CALCULATE_CONE_BUTTON		40014
#define VOLUME_CALCULATE_FRUSTUM_BUTTON	40015
#define VOLUME_CALCULATE_PYRAMID_BUTTON		40016

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

	void VolumeWndObj(VolWnd& obj);
	// experiment with window objects.

	void ClearVolumeText();
	// Clears all text boxes and resets the combobox.

	void ClearVolumeWnd();
	// Clears the window (removes the interface).

	void VolumeDlgList(HWND hWnd);
	// List in volume combo box (a simplified method).

	void ComboBoxCommand(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	// Combobox selection conditions.



	~VolWnd();

	static BOOL wndCreated;	// Volume window is created.

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