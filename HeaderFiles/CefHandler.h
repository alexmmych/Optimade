#pragma once

#define ID_TIMER 1

#include "C:/cef/include/cef_client.h"
#include "../HeaderFiles/Window.h"


//CefHandler class used to access CEF functions and parameteres.

//Note: Methods are the functions which are going to be used from the inherited classes.

class CefHandler : public CefClient, public CefRenderHandler, public CefLifeSpanHandler, public CefLoadHandler, public CefKeyboardHandler {
public:

	//Constructor and destructor.
	CefHandler();
	~CefHandler();

	//Handlers for the inherited classes so they may work.
	virtual CefRefPtr<CefRenderHandler> GetRenderHandler() OVERRIDE {
		return this;
	}

	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE {
		return this;
	}

	virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE {
		return this;
	}

	//CefClient method:
	virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) OVERRIDE;
	
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

	//Allows to get the Instance of the handler, similar to a singleton.
	static CefHandler* GetInstance();

	//Variables used in the methods.
	WNDPROC SubclassWndProc;
	CefRefPtr<CefBrowser> m_browser;
	HWND browserWindow;

	//Bool which tells if the window is maximized or not.
	bool maximized = false;

	//Function for resizing the window. Visual Studio thinks it doesn't have a definition.
	void WindowResize(bool fullscreen);

private:

	IMPLEMENT_REFCOUNTING(CefHandler);

};

//The window procedure callback of the browser window allowing to record keyboard strokes and window information. 
LRESULT CALLBACK SubclassWindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

//Last known x and y position of the window. Outside of class and static so it's easier to access inside of the callback.
static int lastX;
static int lastY;

