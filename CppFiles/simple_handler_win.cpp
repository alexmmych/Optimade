// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "C:/Optimade/HeaderFiles/simple_handler.h"

#include <windows.h>
#include <string>

#include "C:/cef/include/cef_browser.h"

void SimpleHandler::PlatformTitleChange(CefRefPtr<CefBrowser> browser,
                                        const CefString& title) {
  CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
  SetWindowTextW(hwnd, std::wstring(title).c_str());
}
