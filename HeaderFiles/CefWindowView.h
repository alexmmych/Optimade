#pragma once

#include "C:/cef/include/cef_app.h"
#include "../HeaderFiles/Window.h"

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

private:
	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(WindowView);

};
