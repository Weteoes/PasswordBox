#pragma once
#ifndef CEF_Init_App_H
#define CEF_Init_App_H

#include <Weteoes/More/CEF/Application/CEF_App.h>

class CEF_App_Ready : public CEF_App {
    virtual void OnWebKitInitialized_();
};
#endif