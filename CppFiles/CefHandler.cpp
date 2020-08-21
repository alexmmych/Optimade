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
	WindowBrowser = browser->GetHost()->GetWindowHandle();
}


CefHandler::~CefHandler() {
	cef_instance = nullptr;
}

