#include "../HeaderFiles/CefHandler.h"

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
	host = browser->GetHost();

	SetWindowPos(host->GetWindowHandle(), HWND_TOP, 10, 35, Window::width, Window::height, SWP_SHOWWINDOW);
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

