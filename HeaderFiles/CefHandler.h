#pragma once

#define ID_TIMER 1

#include "C:/cef/include/cef_client.h"
#include "../HeaderFiles/Window.h"

class CefHandler : public CefClient, public CefRenderHandler, public CefLifeSpanHandler, public CefLoadHandler {
public:
	CefHandler();
	~CefHandler();

	virtual CefRefPtr<CefRenderHandler> GetRenderHandler() OVERRIDE {
		return this;
	}

	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE {
		return this;
	}

	virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE {
		return this;
	}

	//CefLoadHandler method:
	virtual void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, TransitionType transition_type) OVERRIDE;

	//CefLifeSpandHandler method:
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;


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

	CefRefPtr<CefBrowser> m_browser;
	HWND browserWindow;

private:

	IMPLEMENT_REFCOUNTING(CefHandler);
};

//The window procedure callback of the browser window. 
LRESULT CALLBACK SubclassWindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);