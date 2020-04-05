#include "pch.h"
#include "CreateDlg.h"
#include <Weteoes/Dlg/Init_Dlg.h>
#include <Weteoes/Dlg/Login_Dlg.h>
#include <Weteoes/Dlg/Main_Dlg.h>
#include <Weteoes/Dlg/ChangePassword_Dlg.h>

void CreateDlgClass::init() {
	VariableClass::appDlgClass.Minimize();
	if (Init_Dlg::dlg_HWND != NULL) {
		// 有窗口
		VariableClass::dlg_CEF = Init_Dlg::dlg_CEF;
		VariableClass::dlg_HWND = Init_Dlg::dlg_HWND;
		VariableClass::appDlgClass.Show(true);
	}
	else {
		Init_Dlg a;
		a.DoModal();
	}
}

void CreateDlgClass::login() {
	VariableClass::appDlgClass.Minimize();
	if (Login_Dlg::dlg_HWND != NULL) {
		// 有窗口
		VariableClass::dlg_CEF = Login_Dlg::dlg_CEF;
		VariableClass::dlg_HWND = Login_Dlg::dlg_HWND;
		VariableClass::appDlgClass.Show(true);
	}
	else {
		Login_Dlg a;
		a.DoModal();
	}
}

void CreateDlgClass::main() {
	VariableClass::appDlgClass.Minimize();
	if (Main_Dlg::dlg_HWND != NULL) {
		// 有窗口
		VariableClass::dlg_CEF = Main_Dlg::dlg_CEF;
		VariableClass::dlg_HWND = Main_Dlg::dlg_HWND;
		VariableClass::appDlgClass.Show(true);
	}
	else {
		Main_Dlg a;
		a.DoModal();
	}
}

void CreateDlgClass::changePassword() {
	if (ChangePassword_Dlg::dlg_HWND != NULL) {
		// 有窗口
		VariableClass::dlg_CEF = ChangePassword_Dlg::dlg_CEF;
		VariableClass::dlg_HWND = ChangePassword_Dlg::dlg_HWND;
		VariableClass::appDlgClass.Show(true);
	}
	else {
		ChangePassword_Dlg a;
		a.DoModal();
	}
}
