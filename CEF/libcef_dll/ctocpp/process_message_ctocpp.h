// Copyright (c) 2020 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=6364b8b5300ddb055b789acf13367f24272feb51$
//

#ifndef CEF_LIBCEF_DLL_CTOCPP_PROCESS_MESSAGE_CTOCPP_H_
#define CEF_LIBCEF_DLL_CTOCPP_PROCESS_MESSAGE_CTOCPP_H_
#pragma once

#if !defined(WRAPPING_CEF_SHARED)
#error This file can be included wrapper-side only
#endif

#include "include/capi/cef_process_message_capi.h"
#include "include/cef_process_message.h"
#include "libcef_dll/ctocpp/ctocpp_ref_counted.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed wrapper-side only.
class CefProcessMessageCToCpp
    : public CefCToCppRefCounted<CefProcessMessageCToCpp,
                                 CefProcessMessage,
                                 cef_process_message_t> {
 public:
  CefProcessMessageCToCpp();
  virtual ~CefProcessMessageCToCpp();

  // CefProcessMessage methods.
  bool IsValid() OVERRIDE;
  bool IsReadOnly() OVERRIDE;
  CefRefPtr<CefProcessMessage> Copy() OVERRIDE;
  CefString GetName() OVERRIDE;
  CefRefPtr<CefListValue> GetArgumentList() OVERRIDE;
};

#endif  // CEF_LIBCEF_DLL_CTOCPP_PROCESS_MESSAGE_CTOCPP_H_
