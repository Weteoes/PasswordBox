#include <pch.h>
#include "simple_app.h"
#include "simple_handler.h"
#include <Weteoes/More/CEF/include/cef_browser.h>
#include <Weteoes/More/CEF/include/cef_command_line.h>
#include <Weteoes/More/CEF/include/views/cef_browser_view.h>
#include <Weteoes/More/CEF/include/views/cef_window.h>
#include <Weteoes/More/CEF/include/wrapper/cef_helpers.h>
#include <Weteoes/More/CEF/Config.h>
#include <Weteoes/Application/CEF/AppCef.h>
#include <Weteoes/Application/AppConfig.h>
#include "V8/V8Handler.h"

namespace {

// When using the Views framework this object provides the delegate
// implementation for the CefWindow that hosts the Views-based browser.
class SimpleWindowDelegate : public CefWindowDelegate {
 public:
  explicit SimpleWindowDelegate(CefRefPtr<CefBrowserView> browser_view)
      : browser_view_(browser_view) {}

  void OnWindowCreated(CefRefPtr<CefWindow> window) OVERRIDE {
    // Add the browser view and show the window.
    window->AddChildView(browser_view_);
    window->Show();

    // Give keyboard focus to the browser view.
    browser_view_->RequestFocus();
  }

  void OnWindowDestroyed(CefRefPtr<CefWindow> window) OVERRIDE {
    browser_view_ = NULL;
  }

  bool CanClose(CefRefPtr<CefWindow> window) OVERRIDE {
    // Allow the window to close if the browser says it's OK.
    CefRefPtr<CefBrowser> browser = browser_view_->GetBrowser();
    if (browser)
      return browser->GetHost()->TryCloseBrowser();
    return true;
  }

 private:
  CefRefPtr<CefBrowserView> browser_view_;

  IMPLEMENT_REFCOUNTING(SimpleWindowDelegate);
  DISALLOW_COPY_AND_ASSIGN(SimpleWindowDelegate);
};

}  // namespace
SimpleApp::SimpleApp() {}
CRect SimpleApp::CEF_CRect; //ÊÓÍ¼×ø±ê
HWND SimpleApp::CEF_HWND; //´°¿Ú¾ä±ú

void SimpleApp::OnBeforeCommandLineProcessing(const CefString & process_type, CefRefPtr<CefCommandLine> command_line)
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

void SimpleApp::OnContextInitialized() {
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
  CefRefPtr<SimpleHandler> CEF_handler = new SimpleHandler(use_views);

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
    CefWindow::CreateTopLevelWindow(new SimpleWindowDelegate(browser_view));
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


void SimpleApp::OnWebKitInitialized() {
	std::string Code =
		"var Weteoes_App;"
		"if (!Weteoes_App) Weteoes_App = {};"
		"(function() {"
		"  Weteoes_App.SystemMenu = {"
		"    Exit:function(){"
		"      native function SystemMenu_Exit();"
		"      return SystemMenu_Exit();"
		"    },"
		"    Mini:function(){"
		"      native function SystemMenu_Mini();"
		"      return SystemMenu_Mini();"
		"    },"
		"  };"
		"  Weteoes_App.Login = {"
		"    Login:function(w){"
		"      native function Login(w);"
		"      return Login(w);"
		"    }"
		"  };"
		"  Weteoes_App.Main = {"
		"    All:{"
		"      Get_w:function(){"
		"        native function Get_w();"
		"        return Get_w();"
		"      },"
		"      Set_Language:function(name){"
		"        native function Set_Language(name);"
		"        return Set_Language(name);"
		"      }"
		"    },"
		"    Setting:{"
		"      Get_ComputerName:function(){"
		"        native function Get_ComputerName();"
		"        return Get_ComputerName();"
		"      },"
		"      Set_ComputerName:function(name){"
		"        native function Set_ComputerName(name);"
		"        return Set_ComputerName(name);"
		"      }"
		"    },"
		"    About:{"
		"      Get_Version:function(){"
		"        native function Get_Version();"
		"        return Get_Version();"
		"      }"
		"    },"
		"    Control:{"
		"      ControlComputer:function(computerName){"
		"        native function ControlComputer(computerName);"
		"        return ControlComputer(computerName);"
		"      }"
		"    },"
		"  };"
		"})();";
	CefRegisterExtension("v8/test", Code, new V8Handler_Class());
}
void SimpleApp::OnContextCreated(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefV8Context> context) {
}