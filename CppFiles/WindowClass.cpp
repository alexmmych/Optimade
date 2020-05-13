
/*********************************************************************************************************************/
/*                                                                                                                   */
/*   This is the file which uses the class definitons in "WindowHeader.h" and creates a window class when called.    */
/*   For more info on each process visit "WindowHeader.h".                                                           */
/*                                                                                                                   */
/*********************************************************************************************************************/

#include "../HeaderFiles/pch.h"
#include "../HeaderFiles/WindowHeader.h"

UINT Window::width = 1920;
UINT Window::height = 1080;
HWND Window::WindowHandle = nullptr;


Window::Window()
	:
	HandleInstance(GetModuleHandle(nullptr)),
	windowRect{ 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) }//Makes "HandleInstance" the hInstance of "WinMain".
{

	CreateWindowClass();

	CreateAWindow();

	std::cout << "Status: Window class created.\n";

	ShowAWindow();

	MessageLoop();

}

void Window::CreateWindowClass()
{
	WNDCLASSEXW wcx = { 0 };
	wcx.cbSize = sizeof(wcx);
	wcx.style = CS_VREDRAW | CS_HREDRAW;
	wcx.lpfnWndProc = WindowProcedure;
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = HandleInstance;
	wcx.hIcon = NULL;     //To do: Create and apply an icon here.
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);     //Idea: Maybe a custom cursor?
	wcx.hbrBackground = NULL;     //To do: Replace with a call to the drawing process of Direct3D.
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = WindowClass;
	wcx.hIconSm = NULL;     //To do: Make small icon aswell.

	RegisterClassExW(&wcx);

}

void Window::CreateAWindow()
{

	AdjustWindowRect(&windowRect, WS_EX_OVERLAPPEDWINDOW, FALSE);

	WindowHandle = CreateWindowExW
	(
		WS_EX_OVERLAPPEDWINDOW, //To do: Allow user to make a fullscreen with "WS_POPUP"

		WindowClass,

		WindowName,

		WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, //Makes the boxes to destroy, minimize and maximize the window.

		CW_USEDEFAULT, //X location of window

		0, //Y location of window (it's 0 because "CW_USEDEFAULT" on the "X" parameter overwrites it).

		windowRect.right - windowRect.left , //Width parameter of window.

		windowRect.bottom - windowRect.top, //Height parameter of window (it's 0 because "CW_USEDEFAULT" on the "Width" parameter overwrites it)

		//To do: Create an option to change width and height of the window.     Ex: 1920x1080.

		NULL, //Window Parent parameter.

		NULL, //Window Menu parameter.

		HandleInstance,

		NULL //Window "LpParam" parameter, don't know how to use it so null (To do: figure out what it does and where to use it).
	);

}

void Window::ShowAWindow()
{
	ShowWindow(WindowHandle, SW_SHOWDEFAULT);  //Re-do this, maybe it causes the problem.
	std::cout << "Status: Window created successfully\n";
}

Window::~Window()
{
	UnregisterClassW(WindowClass, HandleInstance);
}

LRESULT CALLBACK Window::WindowProcedure(HWND hwind, UINT msg, WPARAM wparam, LPARAM lparam)
{


	switch (msg)
	{
	case WM_CREATE: {

		break;
	}
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
	{
		switch (wparam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProcW(hwind, msg, wparam, lparam);
}
