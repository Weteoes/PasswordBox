﻿#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"
#include <string>
#include <thread>
#include <vector>
using namespace std;

#include <Weteoes/Application/CEF/AppCef.h>

#include <Weteoes/Dll/WeteoesDll.h>
#include <Weteoes/Dll/ManagementDll.h>
#include <Weteoes/Dll/SRWDll.h>
#include <Weteoes/Dll/ConfigDll.h>
#include <Weteoes/Dll/LogDll.h>
#include <Weteoes/Variable.h>

#include <exports.h> // 公开接口

#endif //PCH_H