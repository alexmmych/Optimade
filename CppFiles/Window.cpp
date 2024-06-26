
/*********************************************************************************************************************/
/*                                                                                                                   */
/*   This is the file which uses the class definitons in "WindowHeader.h" and creates a window class when called.    */
/*   For more info on each process visit "WindowHeader.h".                                                           */
/*                                                                                                                   */
/*********************************************************************************************************************/

#include "../HeaderFiles/Window.h"

LONG Window::width = 1000;
LONG Window::height = 1000;

LONG Window::windowX = 100;
LONG Window::windowY = 50;

Window* Window::ptrInstance = nullptr;

int Window::paintRef = 0;

Window::Window()
	:
	HandleInstance(GetModuleHandle(nullptr)),
	windowRect{0,0,width,height} 
{

	CreateWindowClass();

	CreateAWindow();

	std::cout << "Status: Window class created.\n";

	ShowAWindow();

}

HICON Window::GetIcon() {
	return (HICON) LoadImageW(HandleInstance, MAKEINTRESOURCEW(IDI_ICON1),IMAGE_ICON,NULL,NULL,LR_DEFAULTSIZE);
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
	wcx.hIcon = GetIcon();     //To do: Create and apply an icon here.
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
		WS_EX_LAYERED,

		WindowClass,

		WindowName,

		WS_POPUP, 

		250, //X location of window

		50, //Y location of window.

		windowRect.right - windowRect.left, //Width parameter of window.

		windowRect.bottom - windowRect.top, //Height parameter of window.

		NULL, //Window Parent parameter.

		NULL, //Window Menu parameter.

		HandleInstance,

		NULL //Window "LpParam" parameter, don't know how to use it so null (To do: figure out what it does and where to use it).
	);

	//Sets the main window to be black, creating the black edges.
	SetLayeredWindowAttributes(WindowHandle, RGB(0, 0, 0), 255, LWA_ALPHA);

}

void Window::ShowAWindow()
{
	ShowWindow(WindowHandle, SW_RESTORE);

	std::cout << "Status: Window created successfully\n";
}

Window::~Window()
{
	UnregisterClassW(WindowClass, HandleInstance);
}

LRESULT CALLBACK Window::WindowProcedure(HWND hwind, UINT msg, WPARAM wparam, LPARAM lparam)
{
	RECT rcClient;
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
			HWND_TOP,
			rcClient.left, rcClient.top,
			(rcClient.right - rcClient.left),
			(rcClient.bottom - rcClient.top),
			SWP_FRAMECHANGED);
		break;
	}
	case WM_PAINT: {
		std::cout << "Window is being painted" << std::endl;

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwind, &ps);
		GetWindowRect(hwind, &rcClient);

		if (handle.get() != nullptr && handle->m_browser != nullptr) {
			SetWindowRgn(handle->m_browser->GetHost()->GetWindowHandle(), CreateRoundRectRgn(0, 0, width - 10, height - 10, 20, 20), TRUE);
		}

		EndPaint(hwind, &ps);

		if (paintRef < 4) {
			paintRef++;
		}

		break;
	}
	case WM_NCCALCSIZE: {
		if (lparam) {
			// Calculate new NCCALCSIZE_PARAMS based on custom NCA inset.
			NCCALCSIZE_PARAMS* pncsp = reinterpret_cast<NCCALCSIZE_PARAMS*>(lparam);

			//The +/- 5 allows us to create a small border around CEF in which WM_NCHITTEST messages go through.
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
			if (handle.get() == nullptr || handle->m_browser.get() == nullptr) {
				PostQuitMessage(0);
				return 0;
			}

			break;
		}
		}
	}
	case WM_SIZING: {
		GetWindowRect(hwind, &rcClient);

		//Resets width and height values
		width = rcClient.right - rcClient.left;
		height = rcClient.bottom - rcClient.top;
		windowX = rcClient.left;
		windowY = rcClient.top;

		//Checks if CEF's handle is nullptr, in order to make sure that no calls to a nullptr instance are done.
		if (handle.get() == nullptr) {
			PostQuitMessage(0);
			return 0;
		}

		SetWindowPos(handle->m_browser->GetHost()->GetWindowHandle(), HWND_TOP, 0, 0, width, height, SWP_SHOWWINDOW);

		handle->m_browser->GetHost()->WasResized();

		break;
	}
	case WM_CLOSE: {
		PostQuitMessage(0);
		break;
	}
	case WM_SETFOCUS: {
		std::cout << "Window got focus" << std::endl;
		break;
	}
	case WM_ENTERSIZEMOVE: {
		std::cout << "Window entered resizing" << std::endl;
		break;
	}
	case WM_EXITSIZEMOVE: {
		std::cout << "Window resized" << std::endl;

		//Resets width and height values
		width = rcClient.right - rcClient.left;
		height = rcClient.bottom - rcClient.top;
		windowX = rcClient.left;
		windowY = rcClient.top;

		if (handle.get() != nullptr) {

			//Resizes the main window by 10 pixels in order to flush the faulty pixels which are left behind on minimizng.
			SetWindowPos(Window::GetInstance()->GetWindowHandle(), NULL, windowX + 10, windowY + 10, width + 10, height + 10, SWP_FRAMECHANGED);
			SetWindowPos(Window::GetInstance()->GetWindowHandle(), NULL, windowX, windowY, width + 10, height + 5, SWP_FRAMECHANGED);
		}

		break;
	}
	/*
	case WM_KEYDOWN:
	{
		switch (wparam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);		//It's no longer necessary to use WM_KEYDOWN since we don't have focus of the main window anymore. 
			break;
		}
	}
	*/

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}

	}
	return DefWindowProcW(hwind, msg, wparam, lparam);
}
