
/*********************************************************************************************************************/
/*                                                                                                                   */
/*   This is the file which uses the class definitons in "WindowHeader.h" and creates a window class when called.    */
/*   For more info on each process visit "WindowHeader.h".                                                           */
/*                                                                                                                   */
/*********************************************************************************************************************/

#include "../HeaderFiles/pch.h"
#include "../HeaderFiles/WindowHeader.h"

LONG Window::width = 1000;
LONG Window::height = 1000;
HWND Window::WindowHandle = nullptr;
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
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hbrBackground = NULL;
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
}

Window::~Window()
{
	UnregisterClassW(WindowClass, HandleInstance);
}

LRESULT CALLBACK Window::WindowProcedure(HWND hwind, UINT msg, WPARAM wparam, LPARAM lparam)
{
	RECT rcClient;
	MARGINS margins;
	GetWindowRect(hwind, &rcClient);

	switch (msg)
	{
	case WM_ACTIVATE: {
		// Extend the frame into the client area.
		HRESULT hr = S_OK;

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
			rcClient.right - rcClient.left,
			rcClient.bottom - rcClient.top,
			SWP_FRAMECHANGED);
		break;
	}
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwind, &ps);

		FillRect(hdc, &ps.rcPaint, (HBRUSH)GetStockObject(COLOR_WINDOW + 1));

		HTHEME hTheme = OpenThemeData(NULL, L"CompositedWindow::Window");

		HBRUSH blackBrush = CreateSolidBrush(RGB(32, 32, 32));

		CreateCompatibleDC(hdc);

		int cx = rcClient.right - rcClient.left;
		int cy = rcClient.bottom - rcClient.top;

		// Define the BITMAPINFO structure used to draw text.
		// Note that biHeight is negative. This is done because
		// DrawThemeTextEx() needs the bitmap to be in top-to-bottom
		// order.
		BITMAPINFO dib = { 0 };
		dib.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		dib.bmiHeader.biWidth = cx;
		dib.bmiHeader.biHeight = -cy;
		dib.bmiHeader.biPlanes = 1;
		dib.bmiHeader.biCompression = BI_RGB;

		// Setup the theme drawing options.
		DTTOPTS DttOpts = { sizeof(DTTOPTS) };
		DttOpts.dwFlags = DTT_COMPOSITED | DTT_GLOWSIZE | DTT_TEXTCOLOR ;
		DttOpts.iGlowSize = 15;
		DttOpts.crText = RGB(255,255,255);

		// Select a font.
		LOGFONTW lgFont;
		HFONT hFontOld = NULL;

		GetThemeSysFont(hTheme, TMT_CAPTIONFONT, &lgFont);
		HFONT hFont = CreateFontIndirectW(&lgFont);
		hFontOld = (HFONT)SelectObject(hdc, hFont);

		RECT barRect{ 0,0,width,30 };
		RECT title{ 5,0,width,30 };


		FillRect(hdc, &barRect, (HBRUSH)(blackBrush));

		DrawThemeTextEx(
			hTheme,
			hdc,
			NULL,
			NULL,
			L"Optimade",
			-1,
			DT_VCENTER | DT_SINGLELINE,
			&title,
			&DttOpts);

		// DrawFrameControl(hdc, &barRect, DFC_CAPTION, DFCS_CAPTIONCLOSE);

		break;
	}
	case WM_NCCALCSIZE: {
		if (lparam) {
			// Calculate new NCCALCSIZE_PARAMS based on custom NCA inset.
			NCCALCSIZE_PARAMS* pncsp = reinterpret_cast<NCCALCSIZE_PARAMS*>(lparam);

			pncsp->rgrc[0].left = pncsp->rgrc[0].left + 0;
			pncsp->rgrc[0].top = pncsp->rgrc[0].top + 0;
			pncsp->rgrc[0].right = pncsp->rgrc[0].right - 0;
			pncsp->rgrc[0].bottom = pncsp->rgrc[0].bottom - 0;

			return 0;
		}
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
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	return DefWindowProcW(hwind, msg, wparam, lparam);
	}
}
