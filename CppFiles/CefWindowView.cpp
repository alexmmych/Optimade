#include "../HeaderFiles/CefWindowView.h"

WindowView::WindowView() {}

void WindowView::OnContextInitialized() {
	CefRefPtr<CefCommandLine> command_line = CefCommandLine::GetGlobalCommandLine();

// SimpleHandler implements browser-level callbacks.
	CefRefPtr<CefHandler> handler(new CefHandler);

// Specify CEF browser settings here.
	CefBrowserSettings browser_settings;

	std::string url;

	url = "C:/Optimade/Resources/Website.html";
//	url = "https://www.google.com";

	CefWindowInfo window_info;

//Creates the window.

	RECT rcClient;
	HWND WindowHandle = Window::GetInstance()->GetWindowHandle();

	GetWindowRect(WindowHandle, &rcClient);

	window_info.SetAsChild(WindowHandle, rcClient);

	// Create the first browser window.
	CefBrowserHost::CreateBrowser(window_info, handler, url, browser_settings,
		nullptr, nullptr);
}

void WindowView::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) {
	CefRefPtr<CefV8Value> object = context->GetGlobal();
	CefRefPtr<CefV8Handler> handler = new MyV8Handler();

	CefRefPtr<CefV8Value> hide = CefV8Value::CreateFunction("hide", handler);
	CefRefPtr<CefV8Value> size = CefV8Value::CreateFunction("size", handler);

	object->SetValue("hide", hide, V8_PROPERTY_ATTRIBUTE_NONE);
	object->SetValue("size", size, V8_PROPERTY_ATTRIBUTE_NONE);
}

void WindowView::OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line) {
	command_line->AppendSwitch("disable-gpu");
	command_line->AppendSwitch("no-sanbox");
}

void WindowView::OnBrowserDestroyed(CefRefPtr<CefBrowser> browser) {
	Window::GetInstance()->CloseWindow();
}

WindowView::~WindowView() {

}

bool MyV8Handler::Execute(const CefString& name,
	CefRefPtr<CefV8Value> object,
	const CefV8ValueList& arguments,
	CefRefPtr<CefV8Value>& retval,
	CefString& exception) {

	CefRefPtr<CefBrowser> browser = CefV8Context::GetCurrentContext()->GetBrowser();
	CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(name);
	browser->GetMainFrame()->SendProcessMessage(PID_BROWSER, message);

	return true;
}