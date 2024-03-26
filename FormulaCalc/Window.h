// Window.h

#pragma once

#include <Windows.h>
#include <iostream>
#include <sstream>
#include "GTException.h"
#include "Widget.h"
#include "resource.h"
//#include "VolWnd.h"

//HINSTANCE hInst = GetModuleHandle(NULL);

//VolWnd& volumeWin = VolWnd::instVolWnd();

template <class DERIVED_TYPE>
class BaseWindow
{
public:
	class Exception : public GTException
	{
	public:
		Exception(int line, const char* file, HRESULT hr) noexcept
			:
			GTException(line, file),
			hr(hr)
		{}
		const char* what() const noexcept override
		{
			std::ostringstream oss;
			oss << GetType() << std::endl
				<< "[Error Code] " << GetErrorCode() << std::endl
				<< "[Description] " << GetErrorString() << std::endl
				<< GetOriginString();
			whatBuffer = oss.str();
			return whatBuffer.c_str();
		}
		virtual const char* GetType() const noexcept { return "GT Window Exception"; }
		static std::string TranslateErrorCode(HRESULT hr) noexcept
		{
			char* pMsgBuf = nullptr;
			// windows will allocate memory for err string and make our pointer point to it
			DWORD nMsgLen = FormatMessage(
				FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr
			);

			// 0 string length returned indicates a failure
			if (nMsgLen == 0)
			{
				return "Unidentified error code";
			}

			// copy error string from windows-allocated buffer to std::string
			std::string errorString = pMsgBuf;

			// free windows buffer
			LocalFree(pMsgBuf);
			return errorString;
		}

		HRESULT GetErrorCode() const noexcept { return hr; }
		std::string GetErrorString() const noexcept { return TranslateErrorCode(hr); }

	private:
		HRESULT hr;

	};

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		// Associate class instance with a window handle (HWND) so that member functions 
		// can be called in response to window messages.
		// Allows the WindowProc static function to forward messages to the appropriate 
		// instance’s member function for handling.
		DERIVED_TYPE* pThis = NULL;
		if (uMsg == WM_NCCREATE)
		{
			// Cast lParam to CREATESTRUCT* for WM_CREATE message data.
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;

			// Retrieve the pointer to your class instance passed in lpCreateParams.
			pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;

			// Store the class instance pointer in the window's user data.
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

			// Set the HWND member of your class instance.
			pThis->m_hWnd = hwnd;
		}
		else
		{
			// Retrieve the pointer to the class instance from the window's user data.
			// Access the object that was previously stored with SetWindowLongPtr during 
			// the WM_CREATE message handling.
			pThis = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		}
		if (pThis)
		{
			return pThis->HandleMessage(uMsg, wParam, lParam);
		}
		else
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}

	}

	BaseWindow() 
		: 
		m_hWnd(NULL) 
	{}

	void CreateWnd(
		const char* lpWindowName, DWORD dwStyle, DWORD dwExStyle = 0,
		int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT,
		HWND hWndParent = 0, HMENU hMenu = 0 )

	{
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(wc);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = DERIVED_TYPE::WindowProc;		
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = GetModuleHandle(NULL);
		wc.hIcon = NULL;
		wc.hCursor = nullptr;
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.lpszMenuName = MAKEINTRESOURCE(hMenu);
		wc.lpszClassName = ClassName();
		wc.hIconSm = NULL;
		RegisterClassEx(&wc);

		m_hWnd = CreateWindowEx(
			dwExStyle, 
			ClassName(), 
			lpWindowName, 
			dwStyle, 
			x, 
			y,
			nWidth, 
			nHeight, 
			hWndParent, 
			NULL, 
			GetModuleHandle(NULL), 
			this
		);

		// Check for error.
		if (m_hWnd == nullptr)
		{
			MessageBox(m_hWnd,  "Window Failed", "Failure..", MB_OK);
			//throw GTWND_LAST_EXCEPT();
		}

	}

	HWND GetWinHandle() const { return m_hWnd; }

protected:
	virtual const char* ClassName() const = 0;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	HWND m_hWnd;

};

class MainWindow : public BaseWindow<MainWindow>
{
public:
	const char* ClassName() const { return "MainWndClass"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void MainInterface(const HWND& hWnd, const HINSTANCE hInst);
	// The main window interface, lables, textboxes and buttons.

	void ComboBoxList(HWND hWnd);
	// Memory allocation and buffer for the combobox list.

	void ComboBoxCommand(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	// Combobox selection conditions.

private:

};


// Error exception helper macros.
#define GTWND_EXCEPT( hr ) BaseWindow<MainWindow>::Exception( __LINE__,__FILE__,hr )
#define GTWND_LAST_EXCEPT() BaseWindow<MainWindow>::Exception( __LINE__,__FILE__,GetLastError() )

