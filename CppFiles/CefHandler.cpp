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
	DeleteObject(draggable_region);
	return true;
}

void CefHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
	m_browser = NULL;
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
	browser->GetHost()->Invalidate(type);
}

void CefHandler::OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, TransitionType transition_type) {
	//Removes and sets the subclass, updating it, upon loading another website.
	RemoveWindowSubclass(browserWindow, &SubclassWindowProcedure, 0);
	SetWindowSubclass(browserWindow, &SubclassWindowProcedure, 0, 0);
}

void CefHandler::OnDraggableRegionsChanged(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	const std::vector<CefDraggableRegion>& regions) {

	SetRectRgn(draggable_region, 0, 0, 0, 0);

	for (std::vector<CefDraggableRegion>::const_iterator it = regions.begin(); it != regions.end(); ++it) {
		HRGN region = CreateRectRgn(it->bounds.x, it->bounds.y,
			it->bounds.x + it->bounds.width,
			it->bounds.y + it->bounds.height);
		CombineRgn(draggable_region, draggable_region, region, it->draggable ? RGN_OR : RGN_DIFF);
		DeleteObject(region);
	}
}

bool CefHandler::OnDragEnter(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDragData> dragData, CefDragHandler::DragOperationsMask mask) {
	return false;
}


CefHandler::~CefHandler() {
	cef_instance = nullptr;
}


LRESULT CALLBACK SubclassWindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	POINT mouse;
	switch (message) {

	//WM_PARENTNOTIFY allows us to see WM_LBUTTONDOWN which we weren't able to do before.
	case WM_PARENTNOTIFY: {
		switch (wParam) {
		case WM_LBUTTONDOWN: {
			std::cout << "Sent click" << std::endl;
			break;
		}
		}
		break;
	}
	case WM_MOUSEMOVE: {
		GetCursorPos(&mouse);
		std::cout << "Mouse moved" << std::endl;

		//Moves the window handle to the current position of the mouse.
		MoveWindow(Window::GetInstance()->GetWindowHandle(), mouse.x, mouse.y, Window::GetInstance()->width, Window::GetInstance()->height, false);

		break;
	}

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			CefHandler::GetInstance()->m_browser->GetHost()->CloseBrowser(true);
			break;
		}
	}
	case WM_MOUSEMOVE: {
		GetCursorPos(&mouse);
		std::cout << "Mouse moved" << std::endl;

	
		MoveWindow(Window::GetInstance()->GetWindowHandle(), mouse.x, mouse.y, Window::GetInstance()->width, Window::GetInstance()->height, false);
		

		break;
	}
	case WM_NCDESTROY:
		RemoveWindowSubclass(hWnd, &SubclassWindowProcedure, 0);
		break;
	default: 
		return DefSubclassProc(hWnd, message, wParam, lParam);
	}
	}
	return DefSubclassProc(hWnd, message, wParam, lParam);
}