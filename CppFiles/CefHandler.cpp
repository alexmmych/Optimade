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
}

void CefHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) {

	//Get the parent window's handle and rectangle
	HWND handle = Window::GetWindowHandle();
	RECT rectangle;

	GetWindowRect(handle, &rectangle);

	//The width and the height of the window.
	int width = rectangle.right - rectangle.left;
	int height = rectangle.bottom - rectangle.right;

	//The x and y coordinates.
	int x = rectangle.left;
	int y = rectangle.top;

	rect.Set(x, y, width, height);
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

