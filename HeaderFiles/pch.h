#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers.
#endif

#include <windows.h>
#include <dwmapi.h>
#include <vssym32.h>
#include <Uxtheme.h>

#pragma comment (lib, "dwmapi.lib")
#pragma comment (lib, "UxTheme.lib")

#pragma comment (lib, "libcef.lib")
#pragma comment(lib,"libcef_dll_wrapper.lib")


#include "cef_app.h"
#include "internal\cef_win.h"
#include "internal\cef_types_wrappers.h"
#include "cef_client.h"
#include "cef_browser.h"
#include "cef_base.h"


#include <iostream>
#include <string>
