#pragma once
#ifndef AppDlgClass_H
#define AppDlgClass_H
class AppDlgClass {

public:
	void Close(); // 关闭窗口
	void Minimize(); // 最小化窗口
	void Show(); // 显示窗口

private:
	HWND dlg_HWND;

private:
	//记录窗口信息
	void Dlg_SetNowRect(bool = false); // 设置Dlg变量
	struct Dlg {
		int x, y;
		int width, height;
	};
	static Dlg Dlg_;
	AppDlgClass::Dlg Dlg_GetRect();  // 获取Dlg记录
};
#endif