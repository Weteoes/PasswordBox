#include "pch.h"

AppDlgClass::Dlg AppDlgClass::Dlg_; // 记录窗口位置

void AppDlgClass::Exit() {
	VariableClass::appIconClass.Icon_Remove(); // 移除托盘图标
	exit(0);
}

void AppDlgClass::Close() {
	dlg_HWND = VariableClass::dlg_HWND; // 获取当前活动句柄
	SetWindowText(dlg_HWND, "Close");
	PostMessage(dlg_HWND, WM_CLOSE, 0, 0);
	VariableClass::dlg_HWND = NULL; // 清空句柄
}

void AppDlgClass::Minimize() {
	dlg_HWND = VariableClass::dlg_HWND; // 获取当前活动句柄
	Dlg_SetNowRect(); // 保存现在的窗口信息
	// 移动窗口位置
	int nFullWidth = GetSystemMetrics(SM_CXSCREEN), // 获取屏幕大小
		nFullHeight = GetSystemMetrics(SM_CYSCREEN);
	SetWindowPos(dlg_HWND, NULL, nFullWidth, nFullHeight, 0, 0, SWP_NOSIZE);  // 设置0像素,移到最角落,不然会存在阴影

	ShowWindow(dlg_HWND, SW_HIDE);
}

void AppDlgClass::Show(bool moveCenter) {
	dlg_HWND = VariableClass::dlg_HWND; // 获取当前活动句柄
	// 窗口移动到中间
	if (moveCenter) { MoveCenter(); }
	else {
		Dlg a = Dlg_GetRect(); // 获取保存的窗口信息
		SetWindowPos(dlg_HWND, NULL, a.x, a.y, 0, 0, SWP_NOSIZE);  // 还原上次位置
	}
	ShowWindow(dlg_HWND, SW_SHOW);
}

void AppDlgClass::SetSize(int width, int height) {
	// 设置窗口大小
	dlg_HWND = VariableClass::dlg_HWND; // 获取当前活动句柄
	if (dlg_HWND == NULL) {
		SetSize(width, height);
	}
	Dlg_SetNowRect(); // 保存现在的窗口信息
	SetWindowPos(dlg_HWND, NULL, Dlg_.x, Dlg_.y, width, height, 0);
	MoveCenter(); // 窗口移动到中间
}

void AppDlgClass::MoveCenter() {
	dlg_HWND = VariableClass::dlg_HWND; // 获取当前活动句柄
	int nFullWidth = GetSystemMetrics(SM_CXSCREEN), // 获取屏幕大小
		nFullHeight = GetSystemMetrics(SM_CYSCREEN);
	CRect rect;
	GetWindowRect(dlg_HWND, &rect);
	int x = (nFullWidth - (rect.right - rect.left)) / 2,
		y = (nFullHeight - (rect.bottom - rect.top)) / 2;
	SetWindowPos(dlg_HWND, NULL, x, y, 0, 0, SWP_NOSIZE);
}

void AppDlgClass::Dlg_SetNowRect(bool SetWH) {
	dlg_HWND = VariableClass::dlg_HWND; // 获取当前活动句柄
	CRect DlgCRect;
	GetWindowRect(dlg_HWND, &DlgCRect); // 获取在屏幕中的坐标
	Dlg_.x = DlgCRect.left;
	Dlg_.y = DlgCRect.top;
	if (SetWH) { // 设置宽高
		Dlg_.width = DlgCRect.right - DlgCRect.left;
		Dlg_.height = DlgCRect.bottom - DlgCRect.top;
	}
}

AppDlgClass::Dlg AppDlgClass::Dlg_GetRect() {
	Dlg a;
	if (Dlg_.x == 0 || Dlg_.y == 0) { // 不存在值
		int width = GetSystemMetrics(SM_CXSCREEN),
			height = GetSystemMetrics(SM_CYSCREEN); // 获取屏幕分辨率
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