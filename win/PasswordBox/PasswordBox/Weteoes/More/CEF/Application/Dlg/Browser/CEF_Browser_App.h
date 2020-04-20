#pragma once
#ifndef CEF_Browser_App_H
#define CEF_Browser_App_H

#include <Weteoes/More/CEF/Application/CEF_App.h>

class CEF_Browser_App : public CEF_App {
    virtual void OnWebKitInitialized_();
};
#endif