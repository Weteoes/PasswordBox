#include <pch.h>
#include "APP_Dll_SWR.h"

void APP_Dll_SWR::Start(int type) {
	std::thread socket(&APP_Dll_SWR::Start_thread, this, type); socket.detach();
}

void APP_Dll_SWR::Start_thread(int type) {
	switch (type) {
		case 0: { // UI ·þÎñ
			std::string a = WeteoesDll::Basics_GetNowFilePath() + std::string("UI");
			SRWDll::Web_Entrance(a.c_str());
			break;
		}
	}
}