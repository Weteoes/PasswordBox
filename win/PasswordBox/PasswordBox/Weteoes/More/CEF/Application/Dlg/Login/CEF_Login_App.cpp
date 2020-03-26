#include <pch.h>
#ifndef CEF_Login_App_CPP
#define CEF_Login_App_CPP

#include "CEF_Login_App.h"
#include "CEF_Login_V8Handler.h"

void CEF_Login_App::OnWebKitInitialized_() {
    std::string Code =
        "if (typeof WeteoesBrowser == 'undefined') var WeteoesBrowser = {};"
        "if (typeof WeteoesBrowser.app == 'undefined') WeteoesBrowser.app = {};"
        "WeteoesBrowser.app.Login = function() {"
        "    native function Login();"
        "    return Login();"
        "};";
    CefRegisterExtension("V8/CEF_Login", Code, new CEF_Login_V8Handler());
}

#endif