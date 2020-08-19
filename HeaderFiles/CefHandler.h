#pragma once

#include "C:/cef/include/cef_client.h"

class CefHandler : public CefClient, public CefLifeSpanHandler {
public:
	CefHandler();
	~CefHandler();

//All of the CefClient methods:

	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE {
		return this;
	}

//All of the CefLifeSpan methods:

	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

private:

	IMPLEMENT_REFCOUNTING(CefHandler);
};