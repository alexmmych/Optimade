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
	host = browser->GetHost();
	
	SetWindowPos(host->GetWindowHandle(), HWND_TOP, 0, 35, Window::width, Window::height, SWP_SHOWWINDOW);

	//Sets browser window handle as a child.
	HWND browserWindow = GetWindow(host->GetWindowHandle(), GW_CHILD);

	//This function subclasses the browser window, allowing to use a WndProc instead of CEF default.
	SetWindowSubclass(browserWindow, &SubclassWindowProcedure, 1, 0);
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



CefHandler::~CefHandler() {
	cef_instance = nullptr;
}


LRESULT CALLBACK SubclassWindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{

	switch (message) {

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			//MessageBox(hWnd,"hi","hi",MB_OK|MB_ICONEXCLAMATION);
			PostQuitMessage(0);
			break;
		}
	}

	case WM_NCDESTROY:
		RemoveWindowSubclass(hWnd, &SubclassWindowProcedure, 1);
		break;

	}
	return DefSubclassProc(hWnd, message, wParam, lParam);
}