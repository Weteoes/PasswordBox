#include <pch.h>
#ifndef CEF_Handler_CPP
#define CEF_Handler_CPP
#include "CEF_Handler.h"
#include <sstream>
#include <Weteoes/Variable.h>
#include <Weteoes/Application/AppConfig.h>
#include <Weteoes/More/CEF/include/base/cef_bind.h>
#include <Weteoes/More/CEF/include/cef_app.h>
#include <Weteoes/More/CEF/include/views/cef_browser_view.h>
#include <Weteoes/More/CEF/include/views/cef_window.h>
#include <Weteoes/More/CEF/include/wrapper/cef_closure_task.h>
#include <Weteoes/More/CEF/include/wrapper/cef_helpers.h>

namespace {

CEF_Handler* g_instance = NULL;

}  // namespace

CEF_Handler::CEF_Handler(bool use_views)
    : use_views_(use_views), is_closing_(false) {
  //DCHECK(!g_instance);
  g_instance = this;
}

CEF_Handler::~CEF_Handler() {
  g_instance = NULL;
}

// static
CEF_Handler* CEF_Handler::GetInstance() {
  return g_instance;
}

int CEF_Handler::GetBrowserListIndex() {
    return (int)browser_list_.size();
}

CefRefPtr<CefBrowser> CEF_Handler::GetBrowserbyIndex(int index) {
    if (browser_list_.size() < index + 1) {
        return NULL;
    }
    BrowserList::iterator iter = browser_list_.begin();
    advance(iter, index);
    CefRefPtr<CefBrowser> a = *iter;
    return a;
}

void CEF_Handler::OnTitleChange(CefRefPtr<CefBrowser> browser,
                                  const CefString& title) {
  CEF_REQUIRE_UI_THREAD();

  if (use_views_) {
    // Set the title of the window using the Views framework.
    CefRefPtr<CefBrowserView> browser_view =
        CefBrowserView::GetForBrowser(browser);
    if (browser_view) {
      CefRefPtr<CefWindow> window = browser_view->GetWindow();
      if (window)
        window->SetTitle(title);
    }
  } else {
    // Set the title of the window using platform APIs.
    PlatformTitleChange(browser, VariableClass::appConfig.Get_SoftwareName());
  }
}
void CEF_Handler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();
  //if (!GetBrowser()) {
  //    base::AutoLock lock_scope(lock_);
  //    browser_ = browser;
  //}
  // Add to the list of existing browsers.
  browser_list_.push_back(browser);
}

bool CEF_Handler::DoClose(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();

  // Closing the main window requires special handling. See the DoClose()
  // documentation in the CEF header for a detailed destription of this
  // process.
  if (browser_list_.size() == 1) {
    // Set a flag to indicate that the window close should be allowed.
    is_closing_ = true;
  }

  // Allow the close. For windowed browsers this will result in the OS close
  // event being sent.
  return false;
}

void CEF_Handler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();

  // Remove from the list of existing browsers.
  BrowserList::iterator bit = browser_list_.begin();
  for (; bit != browser_list_.end(); ++bit) {
    if ((*bit)->IsSame(browser)) {
      browser_list_.erase(bit);
      break;
    }
  }

  if (browser_list_.empty()) {
    // All browser windows have closed. Quit the application message loop.
    CefQuitMessageLoop();
  }
}
void CEF_Handler::OnLoadError(CefRefPtr<CefBrowser> browser,
                                CefRefPtr<CefFrame> frame,
                                ErrorCode errorCode,
                                const CefString& errorText,
                                const CefString& failedUrl) {
  CEF_REQUIRE_UI_THREAD();

  // Don't display an error for downloaded files.
  if (errorCode == ERR_ABORTED)
    return;
  //DlgClass().Dlg_Close();
  Sleep(1000);
  browser->Reload();
  // Display a load error message.
  //std::string data = TEXT("<html><body>Network connection timeout</body></html>");
  //frame->LoadString(data, failedUrl);
}

void CEF_Handler::CloseAllBrowsers(bool force_close) {
  if (!CefCurrentlyOn(TID_UI)) {
    // Execute on the UI thread.
    CefPostTask(TID_UI, base::Bind(&CEF_Handler::CloseAllBrowsers, this,
                                   force_close));
    return;
  }

  if (browser_list_.empty())
    return;

  BrowserList::const_iterator it = browser_list_.begin();
  for (; it != browser_list_.end(); ++it)
    (*it)->GetHost()->CloseBrowser(force_close);
}
enum MyMenu {
	Menu_Ready,
	Menu_F12
};
void CEF_Handler::OnBeforeContextMenu(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefContextMenuParams> params,
	CefRefPtr<CefMenuModel> model)
{
	model->AddItem(Menu_Ready, "Ready");
	model->AddItem(Menu_F12, "DevTools");
	//model->Clear();
}

bool CEF_Handler::OnContextMenuCommand(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefContextMenuParams> params,
	int command_id,
	EventFlags event_flags) {
	switch (command_id)
	{
	case Menu_Ready: {
		browser->Reload();
		break;
	}
	case Menu_F12:{
		CefWindowInfo windowInfo;
		CefBrowserSettings setting;
		windowInfo.SetAsPopup(browser->GetHost()->GetWindowHandle(), "DevTools");
		browser->GetHost()->ShowDevTools(windowInfo, this, setting, CefPoint());
		break;
	}
	default:
		break;
	}
	return false;
}

void CEF_Handler::PlatformTitleChange(CefRefPtr<CefBrowser> browser,
    const CefString& title) {
    CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
    SetWindowText(hwnd, title.ToString().c_str());
}

#endif