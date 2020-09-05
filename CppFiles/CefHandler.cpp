#include "../HeaderFiles/CefHandler.h"
#include "../HeaderFiles/pch.h"

namespace {
	CefHandler* cef_instance = nullptr;
}

CefHandler::CefHandler() {
	cef_instance = this;
}

CefHandler* CefHandler::GetInstance() {
	return cef_instance;
}

void CefHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
	//Sets host object for the parent window.
	m_browser = browser.get();

	//Sets browser window handle as a child.
	browserWindow = GetWindow(m_browser->GetHost()->GetWindowHandle(), GW_CHILD);
	
	SetWindowPos(m_browser->GetHost()->GetWindowHandle(), HWND_TOP, 0, 0, Window::width, Window::height, SWP_SHOWWINDOW);

	SetTimer(Window::GetInstance()->GetWindowHandle(), ID_TIMER, 1000, (TIMERPROC)NULL);
}

bool CefHandler::DoClose(CefRefPtr<CefBrowser> browser) {

	DestroyWindow(browser->GetHost()->GetWindowHandle());
	RemoveWindowSubclass(CefHandler::GetInstance()->browserWindow, &SubclassWindowProcedure, 0);

	cef_instance = nullptr;

	return true;
}

void CefHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
	m_browser = NULL;
	Window::GetInstance()->CloseWindow();
}

void CefHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) {
}

bool CefHandler::GetScreenInfo(CefRefPtr<CefBrowser> browser, CefScreenInfo& screen_info) {
	//Set the scale factor to 1.
	screen_info.device_scale_factor = 1.0;

	return true;
}

void CefHandler::OnPaint(
	CefRefPtr<CefBrowser> browser,
	PaintElementType type,
	const RectList& dirtyRects,
	const void* buffer,
	int width, int height) {
}

void CefHandler::OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, TransitionType transition_type) {
	//Removes and sets the subclass, updating it, upon loading another website.
	RemoveWindowSubclass(browserWindow, &SubclassWindowProcedure, 0);
	SetWindowSubclass(browserWindow, &SubclassWindowProcedure, 0, 0);
}

CefHandler::~CefHandler() {
	cef_instance = nullptr;
}


bool CefHandler::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) {
	if (message->GetName() == "hide") {
		CloseWindow(Window::GetInstance()->GetWindowHandle());
		return true;
	}

	if (message->GetName() == "size") {
		//If the window is maximized
		if (maximized == false) {

			maximized = true;

			//Saves the logical coordinates and values of the window
			prevWidth = Window::width;
			prevHeight = Window::height;
			prevX = Window::windowX;
			prevY = Window::windowY;

			//Maximized window (-10's and +20's are there in order to make the window fully displayed)
			SetWindowPos(Window::GetInstance()->GetWindowHandle(), NULL, -10, -10, 1920 + 20, 1080 + 20, SWP_FRAMECHANGED);

			return true;
		}
		//If the window is minimized
		if (maximized == true) {

			maximized = false;

			//Minimizes window
			SetWindowPos(Window::GetInstance()->GetWindowHandle(), NULL, prevX, prevY, prevWidth, prevHeight, SWP_FRAMECHANGED);

			//Sleep for a second in order for 'SendMessage' to get a time to process and resize correctly.
			Sleep(1000);

			//Sends the 'WM_EXITSIZEMOVE' message in order make the window rounded again.
			SendMessageW(Window::GetInstance()->GetWindowHandle(), WM_EXITSIZEMOVE, NULL, NULL);

			return true;
		}

	}
}

LRESULT CALLBACK SubclassWindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	POINT mouse;
	HRGN draggable_region;

	switch (message) {
	//WM_PARENTNOTIFY allows us to see WM_LBUTTONDOWN which we weren't able to do before.
	case WM_PARENTNOTIFY: {
		switch (wParam) {
		case WM_LBUTTONDOWN: {
			RECT rect;

			GetCursorPos(&mouse);
			GetWindowRect(hWnd, &rect);


			lastX = mouse.x - rect.left;
			lastY = mouse.y - rect.top;

			std::cout << "Sent click" << std::endl;

			break;
		}
		}
		break;
	}
	case WM_MOUSEMOVE: {
		POINT currentMouse;
		RECT region;
		GetCursorPos(&currentMouse);

		int x = currentMouse.x - lastX;
		int y = currentMouse.y - lastY;

		//Moves the window handle to the current position of the mouse.
		if (lastY <= 50) {
			MoveWindow(Window::GetInstance()->GetWindowHandle(), x, y, Window::GetInstance()->width, Window::GetInstance()->height, false);
		}

		break;

	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			//Set Focus to avoid nullptrs and crashes
			SetFocus(hWnd);

			//Calls functions to close CEF
			CefHandler::GetInstance()->m_browser->GetHost()->CloseBrowser(true);
			break;
		case VK_F5:
			//Set Focus to avoid nullptrs and crashes
			SetFocus(hWnd);

			CefHandler::GetInstance()->m_browser->Reload();
			break;
		}
	}
	case WM_NCDESTROY:
		RemoveWindowSubclass(hWnd, &SubclassWindowProcedure, 0);
		break;
	}
	return DefSubclassProc(hWnd, message, wParam, lParam);
}