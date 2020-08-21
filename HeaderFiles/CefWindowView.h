#pragma once

#include "C:/cef/include/cef_app.h"
#include "../HeaderFiles/Window.h"
#include "../HeaderFiles/CefHandler.h"

class WindowView : public CefApp, public CefBrowserProcessHandler {
public:
	WindowView();
	~WindowView();

// CefApp methods:
	
	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
		OVERRIDE {
		return this;
	}

// CefBrowserProcessHandler methods:
	virtual void OnContextInitialized() OVERRIDE;
	virtual void OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line) OVERRIDE;

private:
	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(WindowView);

};
