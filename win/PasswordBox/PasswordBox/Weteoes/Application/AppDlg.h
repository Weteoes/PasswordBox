#pragma once
#ifndef AppDlgClass_H
#define AppDlgClass_H
class AppDlgClass {

public:
	void Exit();												// 退出程序
	void Close();												// 关闭窗口
	void Minimize(bool postCloseMsg = false);					// 最小化窗口
	void Minimize(HWND dlg_HWND, bool postCloseMsg = false);	// 最小化窗口(通过窗口句柄)
	void Show(bool moveCenter = false);							// 显示窗口
	void Show(HWND dlg_HWND);									// 显示窗口(通过窗口句柄)
	void SetSize(int width, int height);						// 设置窗口大小
	void MoveCenter();											// 移动窗口到中间
	void MoveCenter(HWND dlg_HWND);								// 移动窗口到中间(通过窗口句柄)

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