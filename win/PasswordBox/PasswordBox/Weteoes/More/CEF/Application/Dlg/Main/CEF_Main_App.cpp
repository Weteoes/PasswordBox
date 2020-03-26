#include <pch.h>
#ifndef CEF_Main_App_CPP
#define CEF_Main_App_CPP

#include "CEF_Main_App.h"
#include "CEF_Main_V8Handler.h"

void CEF_Main_App::OnWebKitInitialized_() {
    std::string Code =
        "if (typeof WeteoesBrowser == 'undefined') var WeteoesBrowser = {};"
        "if (typeof WeteoesBrowser.app == 'undefined') WeteoesBrowser.app = {};"
        "WeteoesBrowser.app.Login = function() {"
        "    native function Login();"
        "    return Login();"
        "};";
    CefRegisterExtension("V8/CEF_Main", Code, new CEF_Main_V8Handler());
}

#endif