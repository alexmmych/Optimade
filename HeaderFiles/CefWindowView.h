#pragma once

#include "C:/cef/include/cef_app.h"
#include "../HeaderFiles/Window.h"

class WindowView : public CefApp , public Window {
public:
	WindowView();

	~WindowView();

private:
	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(WindowView);

};
