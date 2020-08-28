
/*********************************************************************************************************************/
/*                                                                                                                   */
/*   This is the file which uses the class definitons in "WindowHeader.h" and creates a window class when called.    */
/*   For more info on each process visit "WindowHeader.h".                                                           */
/*                                                                                                                   */
/*********************************************************************************************************************/

#include "../HeaderFiles/Window.h"
#include "../HeaderFiles/pch.h"

LONG Window::width = 1000;
LONG Window::height = 1000;
Window* Window::ptrInstance = nullptr;


Window::Window()
	:
	HandleInstance(GetModuleHandle(nullptr)),
	windowRect{0,0,width,height}//Makes "HandleInstance" the hInstance of "WinMain".
{

	CreateWindowClass();

	CreateAWindow();

	std::cout << "Status: Window class created.\n";

	ShowAWindow();

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
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hbrBackground = NULL;
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = WindowClass;
	wcx.hIconSm = NULL;     //To do: Make small icon aswell.

	RegisterClassExW(&wcx);

}

void Window::CreateAWindow()
{

	AdjustWindowRect(&windowRect, WS_EX_LAYERED, FALSE);

	WindowHandle = CreateWindowExW
	(
		WS_EX_TRANSPARENT,

		WindowClass,

		WindowName,

		WS_POPUP, 

		250, //X location of window

		50, //Y location of window (it's 0 because "CW_USEDEFAULT" on the "X" parameter overwrites it).

		windowRect.right - windowRect.left, //Width parameter of window.

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
	SetWindowPos(WindowHandle, HWND_TOP, 0, 0, 100, 100, SWP_SHOWWINDOW);
	SetWindowPos(WindowHandle, HWND_TOP, 100, 50, width, height, SWP_SHOWWINDOW);
}

Window::~Window()
{
	UnregisterClassW(WindowClass, HandleInstance);
}

LRESULT CALLBACK Window::WindowProcedure(HWND hwind, UINT msg, WPARAM wparam, LPARAM lparam)
{

	RECT rcClient;
	LRESULT result;
	GetWindowRect(hwind, &rcClient);
	POINT mouse;

	CefRefPtr<CefHandler> handle = CefHandler::GetInstance();

	switch (msg)
	{
	case WM_ACTIVATE: {
		// Extend the frame into the client area.
		HRESULT hr = S_OK;
		MARGINS margins;

		margins.cxLeftWidth = rcClient.left;
		margins.cxRightWidth = rcClient.right;
		margins.cyBottomHeight = rcClient.bottom;
		margins.cyTopHeight = rcClient.top;

		hr = DwmExtendFrameIntoClientArea(hwind, &margins);

		break;
	}
	case WM_CREATE: {
		// Inform the application of the frame change.
		SetWindowPos(hwind,
			NULL,
			rcClient.left, rcClient.top,
			(rcClient.right - rcClient.left) - 100,
			(rcClient.bottom - rcClient.top) - 100,
			SWP_FRAMECHANGED);
		break;
	}
	case WM_PARENTNOTIFY: {
		switch (wparam) {
		case WM_LBUTTONDOWN: {
			GetCursorPos(&mouse);
			ScreenToClient(hwind, &mouse);
			std::cout << "Got click" << std::endl;
			SendMessageW(hwind, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(mouse.x, mouse.y));
			break;
		}
		}
	}
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwind, &ps);

		EndPaint(hwind, &ps);

		break;
	}
	case WM_NCLBUTTONDOWN: {
		std::cout << "Non-client click" << std::endl;
		break;
	}
	case WM_NCCALCSIZE: {
		if (lparam) {
			// Calculate new NCCALCSIZE_PARAMS based on custom NCA inset.
			NCCALCSIZE_PARAMS* pncsp = reinterpret_cast<NCCALCSIZE_PARAMS*>(lparam);

			pncsp->rgrc[0].left = pncsp->rgrc[0].left + 5;
			pncsp->rgrc[0].top = pncsp->rgrc[0].top + 5;
			pncsp->rgrc[0].right = pncsp->rgrc[0].right - 5;
			pncsp->rgrc[0].bottom = pncsp->rgrc[0].bottom - 5;

			return 0;
		}
		break;
	}
	//When WM_NCHITTEST is sent, it checks to see if the cursor is found in the corners and gives a leeway of 10 pixels for the user.
	case WM_NCHITTEST: {
		GetCursorPos(&mouse);
		ScreenToClient(hwind, &mouse);

		return HTCAPTION;

		//Top part of the window
		if (mouse.y <= 50) {
			//Right corner
			if (mouse.x >= width - 10 && mouse.y <= 10) {
				return HTTOPRIGHT;
			}
			//Left corner
			if (mouse.x <= 10 && mouse.y <= 10) {
				return HTTOPLEFT;
			}
			//Top part
			if (mouse.y <= 10) {
				return HTTOP;
			}
			//Window caption
			return HTCAPTION;
		}

		//Bottom part of the window
		if (mouse.y >= height - 10) {
			//Right corner
			if (mouse.x >= width - 10) {
				return HTBOTTOMRIGHT;
			}
			//Left corner
			if (mouse.x <= 10) {
				return HTBOTTOMLEFT;
			}
			//Bottom part 
			return HTBOTTOM;
		}

		//Left part of the window 
		if (mouse.x <= 10) {
			return HTLEFT;
		}

		//Right part of the window
		if (mouse.x >= width - 10) {
			return HTRIGHT;
		}

		break;
	}
	case WM_TIMER: {
		switch (wparam) {
		case ID_TIMER: {
			if (handle.get() == nullptr) {
				PostQuitMessage(0);
				return 0;
			}
			break;
		}
		}
	}
	case WM_SIZING: {
		GetWindowRect(hwind, &rcClient);

		width = rcClient.right - rcClient.left;
		height = rcClient.bottom - rcClient.top;

		if (handle.get() == nullptr) {
			PostQuitMessage(0);
			return 0;
		}

		handle->m_browser->GetHost()->WasResized();

		//The x and y variables specify how much space is there between the parent window and the browser, it is set to 10 in order to be resizable but if a video is played it
		//is highly noticeable.
		SetWindowPos(handle->browserWindow, HWND_TOP, 0, 0, width, height, SWP_SHOWWINDOW);

	
		break;
	}
	case WM_CLOSE: {
		PostQuitMessage(0);
		break;
	}
	case WM_KEYDOWN:
	{
		switch (wparam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}

	}
	return DefWindowProcW(hwind, msg, wparam, lparam);
}
