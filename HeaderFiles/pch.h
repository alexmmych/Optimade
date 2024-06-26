#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers.
#endif

#include <windows.h>
#include <dwmapi.h>
#include <vssym32.h>
#include <Uxtheme.h>
#include <windowsx.h>

#include <CommCtrl.h>
#pragma comment(lib, "Comctl32.lib")

#pragma comment (lib, "dwmapi.lib")
#pragma comment (lib, "UxTheme.lib")

#pragma comment (lib, "libcef.lib")
#pragma comment(lib,"libcef_dll_wrapper.lib")


#pragma comment (lib,"user32.lib")
#pragma comment (lib,"gdi32.lib")
#pragma comment (lib,"kernel32.lib")
#pragma comment(lib, "comctl32.lib")

#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")


#include "cef_app.h"
#include "internal\cef_win.h"
#include "internal\cef_types_wrappers.h"
#include "cef_client.h"
#include "cef_browser.h"
#include "cef_base.h"



#include <iostream>
#include <string>
