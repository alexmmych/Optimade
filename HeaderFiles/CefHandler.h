#pragma once

#include "C:/cef/include/cef_client.h"
#include "../HeaderFiles/Window.h"

class CefHandler : public CefClient, public CefLifeSpanHandler{
public:
	CefHandler();
	~CefHandler();

	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE {
		return this;
	}

	//LifeSpanHandler method:
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;

	HWND WindowBrowser;

	static CefHandler* GetInstance();

private:

	IMPLEMENT_REFCOUNTING(CefHandler);
};