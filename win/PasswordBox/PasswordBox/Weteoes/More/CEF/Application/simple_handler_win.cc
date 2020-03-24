#include <pch.h>
#include "simple_handler.h"
#include <windows.h>
#include <Weteoes/More/CEF/include/cef_browser.h>

void SimpleHandler::PlatformTitleChange(CefRefPtr<CefBrowser> browser,
                                        const CefString& title) {
  CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
  SetWindowText(hwnd, title.ToString().c_str());
}
