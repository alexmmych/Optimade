#include "../HeaderFiles/CefWindowView.h"
#include "../HeaderFiles/CefHandler.h"

WindowView::WindowView() {}

void WindowView::OnContextInitialized() {
	CefRefPtr<CefCommandLine> command_line = CefCommandLine::GetGlobalCommandLine();

// SimpleHandler implements browser-level callbacks.
	CefRefPtr<CefHandler> handler(new CefHandler);

// Specify CEF browser settings here.
	CefBrowserSettings browser_settings;

	std::string url;

	url = "https://google.com";

	CefWindowInfo window_info;

//Creates the window.
	Window::Instance();

	RECT rcClient;
	HWND WindowHandle = Window::GetWindowHandle();

	GetWindowRect(WindowHandle, &rcClient);

	window_info.SetAsChild(WindowHandle, rcClient);

	// Create the first browser window.
	CefBrowserHost::CreateBrowser(window_info, handler, url, browser_settings,
		nullptr, nullptr);
}

WindowView::~WindowView() {

}