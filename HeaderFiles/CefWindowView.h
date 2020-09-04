#pragma once

#include "C:/cef/include/cef_app.h"
#include "../HeaderFiles/Window.h"
#include "../HeaderFiles/CefHandler.h"
#include "../HeaderFiles/pch.h"

class WindowView : public CefApp, public CefBrowserProcessHandler, public CefRenderProcessHandler {
public:
	WindowView();
	~WindowView();

// CefApp methods:
	
	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE {
		return this;
	}

	virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE {
		return this;
	}

// CefBrowserProcessHandler methods:
	virtual void OnContextInitialized() OVERRIDE;
	virtual void OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line) OVERRIDE;

//CefRenderProcessHandler methods:
	virtual void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) OVERRIDE;
	virtual void OnBrowserDestroyed(CefRefPtr<CefBrowser>browser) OVERRIDE;

private:
	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(WindowView);

};

class MyV8Handler : public CefV8Handler {
public:
  MyV8Handler() {}

  virtual bool Execute(const CefString& name,
	  CefRefPtr<CefV8Value> object,
	  const CefV8ValueList& arguments,
	  CefRefPtr<CefV8Value>& retval,
	  CefString& exception) OVERRIDE;

  // Provide the reference counting implementation for this class.
private:
  IMPLEMENT_REFCOUNTING(MyV8Handler);
};