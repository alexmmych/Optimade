#pragma once

#include "C:/cef/include/cef_client.h"
#include "../HeaderFiles/Window.h"

class CefHandler : public CefClient, public CefRenderHandler, public CefLifeSpanHandler {
public:
	CefHandler();
	~CefHandler();

	virtual CefRefPtr<CefRenderHandler> GetRenderHandler() OVERRIDE {
		return this;
	}

	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE {
		return this;
	}

	//CefLifeSpandHandler method:
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;


	//CefRenderHandler methods:
	virtual void GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)  OVERRIDE;
	virtual bool GetScreenInfo(CefRefPtr<CefBrowser> browser, CefScreenInfo& screen_info) OVERRIDE;
	virtual void OnPaint(
		CefRefPtr<CefBrowser> browser,
		PaintElementType type,
		const RectList& dirtyRects,
		const void* buffer,
		int width, int height) OVERRIDE;

	static CefHandler* GetInstance();

	CefRefPtr<CefBrowserHost> host;

private:

	IMPLEMENT_REFCOUNTING(CefHandler);
};