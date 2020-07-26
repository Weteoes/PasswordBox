#include <pch.h>
#include "AppIcon.h"
#include <resource.h>

NOTIFYICONDATA AppIconClass::m_NotifyIcon; //托盘

bool AppIconClass::Icon_Add(HWND Dlg_HWND, HINSTANCE Dlg_HINSTANCE) {
	start:
	m_NotifyIcon.cbSize = sizeof(NOTIFYICONDATA);     // 结构大小
	m_NotifyIcon.hWnd = Dlg_HWND;                 // 接收托盘消息的窗口句柄
	m_NotifyIcon.uID = IDI_ICON1;                 // 应用程序中定义的托盘图标ID
	m_NotifyIcon.hIcon = LoadIcon(Dlg_HINSTANCE, MAKEINTRESOURCE(IDI_ICON1)); // 托盘图标句柄
	string title = AppConfigClass::Get_SoftwareName();
	strcpy_s(m_NotifyIcon.szTip, 128, title.c_str());  // 图标显示提示字符串
	m_NotifyIcon.uCallbackMessage = WM_IconMsg;//WM_USER_NOTIFY;               // 自定义消息,接收图标发送的消息
	m_NotifyIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;       // 设置属性
	/* 添加图标 */
	if (!Shell_NotifyIcon(NIM_ADD, &m_NotifyIcon)) { //如果失败
		Sleep(1000);
		goto start;
	}
	return true;
}
void AppIconClass::Icon_Remove() {
	Shell_NotifyIcon(NIM_DELETE, &m_NotifyIcon);
}