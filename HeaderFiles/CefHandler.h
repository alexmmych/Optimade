#pragma once

#include "C:/cef/include/cef_client.h"

class CefHandler : public CefClient {
public:
	CefHandler();
	~CefHandler();

	CefHandler* GetInstance();

private:

	IMPLEMENT_REFCOUNTING(CefHandler);
};