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

	HWND browserWindow = GetWindow(host->GetWindowHandle(), GW_CHILD);

	UINT_PTR uIdSubclass;
	DWORD_PTR dwRefData;

	SetWindowSubclass(browserWindow, Window::SubclassWindowProcedure, uIdSubclass, dwRefData);

	SetWindowPos(host->GetWindowHandle(), HWND_TOP, 0, 35, Window::width, Window::height, SWP_SHOWWINDOW);
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

