#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers.
#endif

#include <windows.h>

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
