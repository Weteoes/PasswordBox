#include <pch.h>

#include "CEF_App.h"
#include "CEF_Handler.h"
#include "CEF_V8Handler.h"
#include <Weteoes/More/CEF/include/cef_browser.h>
#include <Weteoes/More/CEF/include/cef_command_line.h>
#include <Weteoes/More/CEF/include/views/cef_browser_view.h>
#include <Weteoes/More/CEF/include/views/cef_window.h>
#include <Weteoes/More/CEF/include/wrapper/cef_helpers.h>
#include <Weteoes/More/CEF/Config.h>
#include <Weteoes/Application/CEF/AppCef.h>
#include <Weteoes/Application/AppConfig.h>
#include <Weteoes/More/CEF/Application/CEF_WindowDelegate.h>

CEF_App::CEF_App() {}
CRect CEF_App::CEF_CRect; //ÊÓÍ¼×ø±ê
HWND CEF_App::CEF_HWND; //´°¿Ú¾ä±ú

void CEF_App::OnBeforeCommandLineProcessing(const CefString & process_type, CefRefPtr<CefCommandLine> command_line)
{
#ifdef single_process
	command_line->AppendSwitch("single-process");
#endif
#ifdef disable_gpu
	command_line->AppendSwitch("disable-gpu");
	command_line->AppendSwitch("disable-gpu-compositing");
#endif
	command_line->AppendSwitch("no-proxy-server");
}

void CEF_App::OnContextInitialized() {
  CEF_REQUIRE_UI_THREAD();
  CefRefPtr<CefCommandLine> command_line =
      CefCommandLine::GetGlobalCommandLine();
#if defined(OS_WIN) || defined(OS_LINUX)
  // Create the browser using the Views framework if "--use-views" is specified
  // via the command-line. Otherwise, create the browser using the native
  // platform framework. The Views framework is currently only supported on
  // Windows and Linux.
  const bool use_views = command_line->HasSwitch("use-views");
#else
  const bool use_views = false;
#endif
  // SimpleHandler implements browser-level callbacks.
  CefRefPtr<CEF_Handler> CEF_handler = new CEF_Handler(use_views);

  // Specify CEF browser settings here.
  CefBrowserSettings browser_settings;
  CefBrowserSettings browser_settings1;
  std::string url;
  // Check if a "--url=" value was provided via the command-line. If so, use
  // that instead of the default URL.
  //url = command_line->GetSwitchValue("url");

  url = AppCefClass::Url;
  if (url.empty()){
	  url = "http://127.0.0.1/";
  }

  if (use_views) {
    // Create the BrowserView.
    CefRefPtr<CefBrowserView> browser_view = CefBrowserView::CreateBrowserView(
		CEF_handler, url, browser_settings, NULL, NULL, NULL);

    // Create the Window. It will show itself after creation.
    CefWindow::CreateTopLevelWindow(new CEF_WindowDelegate(browser_view));
  } else {
    // Information used when creating the native window.
    CefWindowInfo window_info;
#if defined(OS_WIN)
    // On Windows we need to specify certain flags that will be passed to
    // CreateWindowEx().
    //window_info.SetAsPopup(NULL, "cefsimple");
#endif
	window_info.SetAsChild(CEF_HWND,CEF_CRect);

    // Create the first browser window.
    CefBrowserHost::CreateBrowser(window_info, CEF_handler, url, browser_settings,
                                  NULL, NULL);
  }
}


void CEF_App::OnWebKitInitialized() {
    std::string Code =
        "if (typeof WeteoesBrowser == 'undefined') var WeteoesBrowser = {};"
        "WeteoesBrowser.Dlg = {"
        "    Mouse: {"
        "        Down: function(x, y) { native function Dlg_Mouse_Down(x, y); return Dlg_Mouse_Down(x, y); },"
        "        Move: function(x, y) { native function Dlg_Mouse_Move(x, y); return Dlg_Mouse_Move(x, y); },"
        "        Up: function() { native function Dlg_Mouse_Up(); return Dlg_Mouse_Up(); },"
        "    }"
        //"    native function Login();"
        //"    return Login();"
        "};";
	CefRegisterExtension("V8/CEF", Code, new CEF_V8Handler());
    OnWebKitInitialized_();
}

void CEF_App::OnContextCreated(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefV8Context> context) {
}