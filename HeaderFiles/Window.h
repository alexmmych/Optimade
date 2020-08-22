//This is the header file which defines the window class for "WindowClass.cpp".

#pragma once
#include "../HeaderFiles/Loop.h"
#include "../HeaderFiles/CefHandler.h"

/*The main class which creates the window and connects other classes together*/
class Window {
private:

	static Window* ptrInstance;

	Window();
	~Window();

	//Variables used in the functions of this class.

	HINSTANCE HandleInstance;
	const LPCWSTR WindowClass = L"WindClass1";
	const LPCWSTR WindowName = L"Optimade";

	static HWND WindowHandle;

	RECT windowRect;

	//These functions are the processes which are called when a "Window" class is created.

	//Creates and declares the window class.
	void CreateWindowClass();

	//Creates the actual window.
	void CreateAWindow();

	//Shows the window.
	void ShowAWindow();

//The window procedure callback of the main window.
	static LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

public:

	static HWND GetWindowHandle() { return WindowHandle; };

	static LONG width;
	static LONG height;

	static Window& Instance() {
		if (!ptrInstance) {
			ptrInstance = new Window();
		}
		return *ptrInstance;
	}

};


//Note: Surprisingly good commenting on my part for one of my first actual projects.
