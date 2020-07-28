#include "pch.h"

AppDlgClass::Dlg AppDlgClass::Dlg_; // 记录窗口位置

void AppDlgClass::Exit() {
	VariableClass::appIconClass.Icon_Remove(); // 移除托盘图标
	exit(0);
}

void AppDlgClass::Close() {
	// 获取当前活动句柄
	dlg_HWND = VariableClass::dlg_HWND;
	SetWindowText(dlg_HWND, "Close");
	PostMessage(dlg_HWND, WM_CLOSE, 0, 0);
	VariableClass::dlg_HWND = NULL; // 清空句柄
}

void AppDlgClass::Minimize(bool postCloseMsg) {
	// 获取当前活动句柄
	dlg_HWND = VariableClass::dlg_HWND;
	Minimize(dlg_HWND, postCloseMsg);
}

void AppDlgClass::Minimize(HWND dlg_HWND, bool postCloseMsg) {
	if (postCloseMsg) {
		// 发送关闭窗口事件
		::PostMessage(dlg_HWND, WM_CLOSE, NULL, NULL); 
	}
	// 保存现在的窗口信息
	Dlg_SetNowRect();
	// 获取屏幕大小
	int nFullWidth = GetSystemMetrics(SM_CXSCREEN), 
		nFullHeight = GetSystemMetrics(SM_CYSCREEN);
	// 移动窗口位置,设置0像素,移到最角落,不然会存在阴影
	SetWindowPos(dlg_HWND, NULL, nFullWidth, nFullHeight, 0, 0, SWP_NOSIZE);  

	ShowWindow(dlg_HWND, SW_HIDE);
}

void AppDlgClass::Show(bool moveCenter) {
	// 获取当前活动句柄
	dlg_HWND = VariableClass::dlg_HWND;
	// 窗口移动到中间
	if (moveCenter) { MoveCenter(); }
	else {
		// 获取保存的窗口信息
		Dlg a = Dlg_GetRect();
		// 还原上次位置
		SetWindowPos(dlg_HWND, NULL, a.x, a.y, 0, 0, SWP_NOSIZE);  
	}
	ShowWindow(dlg_HWND, SW_SHOW);
}

void AppDlgClass::Show(HWND dlg_HWND) {
	MoveCenter(dlg_HWND); // 窗口移动到中间
	ShowWindow(dlg_HWND, SW_SHOW);
}

// 设置窗口大小
void AppDlgClass::SetSize(int width, int height) {
	// 获取当前活动句柄
	dlg_HWND = VariableClass::dlg_HWND;
	if (dlg_HWND == NULL) {
		Sleep(50);
		SetSize(width, height);
	}
	// 保存现在的窗口信息
	Dlg_SetNowRect(); 
	SetWindowPos(dlg_HWND, NULL, Dlg_.x, Dlg_.y, width, height, 0);
	MoveCenter(); // 窗口移动到中间
}

void AppDlgClass::MoveCenter(HWND dlg_HWND) {
	// 获取屏幕大小
	int nFullWidth = GetSystemMetrics(SM_CXSCREEN), 
		nFullHeight = GetSystemMetrics(SM_CYSCREEN);
	CRect rect;
	GetWindowRect(dlg_HWND, &rect);
	int x = (nFullWidth - (rect.right - rect.left)) / 2,
		y = (nFullHeight - (rect.bottom - rect.top)) / 2;
	SetWindowPos(dlg_HWND, NULL, x, y, 0, 0, SWP_NOSIZE);
}

void AppDlgClass::MoveCenter() {
	// 获取当前活动句柄
	dlg_HWND = VariableClass::dlg_HWND; 
	MoveCenter(dlg_HWND);
}

void AppDlgClass::Dlg_SetNowRect(bool SetWH) {
	// 获取当前活动句柄
	dlg_HWND = VariableClass::dlg_HWND; 
	CRect DlgCRect;
	// 获取在屏幕中的坐标
	GetWindowRect(dlg_HWND, &DlgCRect); 
	Dlg_.x = DlgCRect.left;
	Dlg_.y = DlgCRect.top;
	if (SetWH) { 
		// 设置宽高
		Dlg_.width = DlgCRect.right - DlgCRect.left;
		Dlg_.height = DlgCRect.bottom - DlgCRect.top;
	}
}

AppDlgClass::Dlg AppDlgClass::Dlg_GetRect() {
	Dlg a;
	// 不存在值
	if (Dlg_.x == 0 || Dlg_.y == 0) { 
		// 获取屏幕分辨率
		int width = GetSystemMetrics(SM_CXSCREEN),
			height = GetSystemMetrics(SM_CYSCREEN); 
		a.x = (width - Dlg_.width) / 2;
		a.y = (height - Dlg_.height) / 2 - 20;
	}
	else {
		a.x = Dlg_.x;
		a.y = Dlg_.y;
	}
	Dlg_.width == 0 ? a.width = 300 : a.width = Dlg_.width;
	Dlg_.height == 0 ? a.height = 400 : a.height = Dlg_.height;
	return a;
}