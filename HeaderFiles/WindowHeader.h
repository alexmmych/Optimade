//This is the header file which defines the window class for "WindowClass.cpp".

#pragma once
#include "LoopHeader.h"

/*The main class which creates the window and connects other classes together*/
class Window : public Loop 
{
private:

	//Variables used in the functions of this class.

	HINSTANCE HandleInstance;
	const LPCWSTR WindowClass = L"WindClass1";
	const LPCWSTR WindowName = L"Window";

	static HWND WindowHandle;

	static UINT width;
	static UINT height;

	RECT windowRect;

	//These functions are the processes which are called when a "Window" class is created.

	//Creates and declares the window class.
	void CreateWindowClass();

	//Creates the actual window.
	void CreateAWindow();

	//Shows the window.
	void ShowAWindow();

//The window procedure callback.
	static LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

public:
//Constructor and destructor.

	Window();
	~Window();

	static HWND GetWindowHandle() { return WindowHandle; };

};

//Note: Surprisingly good commenting on my part for one of my first actual projects.
