#include <string>
#include <vector>
#include <map>
#include <mutex> // 线程锁
#include <winsock2.h> // 放置于预编译h，要在windows.h前

#include <Weteoes/Dll/WeteoesDll.h>
#include <Weteoes/Dll/ApplicationExports.h>
#include <Weteoes/Dll/ManagementDll.h>
#include <Weteoes/Dll/ConfigDll.h>

#include <Weteoes/Variable.h>
using namespace std;