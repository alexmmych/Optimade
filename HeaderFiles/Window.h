//This is the header file which defines the window class for "WindowClass.cpp".

#pragma once
#include "../HeaderFiles/pch.h"
#include "../HeaderFiles/Loop.h"
#include "../HeaderFiles/CefHandler.h"
#include "../Resources/resource.h"

//The main class which creates the window and connects other classes together
class Window {
private:

	static Window* ptrInstance;

	//Constructor and destructor
	Window();
	~Window();

	//Essential variables of this class.
	HINSTANCE HandleInstance;

	const LPCWSTR WindowClass = L"WindClass1";
	const LPCWSTR WindowName = L"Optimade";

	HWND WindowHandle;
	RECT windowRect;

	//These functions are the processes which are called when a "Window" class is created.

	//Creates and declares the window class.
	void CreateWindowClass();

	//Creates the actual window.
	void CreateAWindow();

	//Shows the window.
	void ShowAWindow();

	//Returns the icon to the window.
	HICON GetIcon();

//The window procedure callback of the main window.
	static LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

public:

	//Functions to get the handles.
	HWND GetWindowHandle() { return WindowHandle; };
	HINSTANCE GetHandleInstance() { return HandleInstance; };

	//Closes the window
	void CloseWindow();


	//Variables representing the width and height of the window.
	static LONG width;
	static LONG height;
	static LONG windowX;
	static LONG windowY;


	//Static function in order for the class to work as a singleton.
	static Window* GetInstance() {
		if (!ptrInstance) {
			ptrInstance = new Window();
		}
		return ptrInstance;
	}

};

