// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_App_H
#define CEF_App_H

#include <atltypes.h>
#include <Weteoes/More/CEF/include/cef_app.h>

// Implement application-level callbacks for the browser process.
class CEF_App :
	public CefApp,
	public CefBrowserProcessHandler,
	public CefRenderProcessHandler {
 public:
     CEF_App();

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
  IMPLEMENT_REFCOUNTING(CEF_App);

private:
    virtual void OnWebKitInitialized_() = 0;
};

#endif