#pragma once
#ifndef CEF_WindowDelegate_H
#define CEF_WindowDelegate_H
#include <Weteoes/More/CEF/include/views/cef_browser_view.h>
#include <Weteoes/More/CEF/include/views/cef_window.h>

namespace {
    class CEF_WindowDelegate : public CefWindowDelegate {
    public:
        explicit CEF_WindowDelegate(CefRefPtr<CefBrowserView> browser_view)
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

        IMPLEMENT_REFCOUNTING(CEF_WindowDelegate);
        DISALLOW_COPY_AND_ASSIGN(CEF_WindowDelegate);
    };
}
#endif