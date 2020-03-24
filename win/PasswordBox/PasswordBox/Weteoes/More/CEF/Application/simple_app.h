// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_
#define CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_

#include <atltypes.h>
#include <Weteoes/More/CEF/include/cef_app.h>
#include <Weteoes/More/CEF/Application/simple_handler.h>

// Implement application-level callbacks for the browser process.
class SimpleApp :
	public CefApp,
	public CefBrowserProcessHandler,
	public CefRenderProcessHandler {
 public:
  SimpleApp();

  // CefApp methods:
  virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE {
    return this;
  }
  //OnContextCreated
  virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE {
	  return this;
  }
  virtual void OnWebKitInitialized() OVERRIDE;
  virtual void OnContextCreated(
	  CefRefPtr<CefBrowser> browser,
	  CefRefPtr<CefFrame> frame,
	  CefRefPtr<CefV8Context> context) OVERRIDE;



  // CefBrowserProcessHandler methods:
  //void OnContextInitialized();
  virtual void OnContextInitialized() OVERRIDE;
  virtual void OnBeforeCommandLineProcessing(const CefString &process_type, CefRefPtr<CefCommandLine> command_line) OVERRIDE;


 private:
  // Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(SimpleApp);
public:
	static HWND CEF_HWND;
	static CRect CEF_CRect;
};

#endif  // CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_
