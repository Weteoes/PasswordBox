#include "pch.h"

AppDlgClass::Dlg AppDlgClass::Dlg_; // ��¼����λ��

void AppDlgClass::Exit() {
	VariableClass::appIconClass.Icon_Remove(); // �Ƴ�����ͼ��
	exit(0);
}

void AppDlgClass::Close() {
	dlg_HWND = VariableClass::dlg_HWND; // ��ȡ��ǰ����
	SetWindowText(dlg_HWND, "Close");
	PostMessage(dlg_HWND, WM_CLOSE, 0, 0);
	VariableClass::dlg_HWND = NULL; // ��վ��
}

void AppDlgClass::Minimize() {
	dlg_HWND = VariableClass::dlg_HWND; // ��ȡ��ǰ����
	Dlg_SetNowRect(); // �������ڵĴ�����Ϣ
	// �ƶ�����λ��
	int nFullWidth = GetSystemMetrics(SM_CXSCREEN), // ��ȡ��Ļ��С
		nFullHeight = GetSystemMetrics(SM_CYSCREEN);
	SetWindowPos(dlg_HWND, NULL, nFullWidth, nFullHeight, 0, 0, SWP_NOSIZE);  // ����0����,�Ƶ������,��Ȼ�������Ӱ

	ShowWindow(dlg_HWND, SW_HIDE);
}

void AppDlgClass::Show(bool moveCenter) {
	dlg_HWND = VariableClass::dlg_HWND; // ��ȡ��ǰ����
	// �����ƶ����м�
	if (moveCenter) { MoveCenter(); }
	else {
		Dlg a = Dlg_GetRect(); // ��ȡ����Ĵ�����Ϣ
		SetWindowPos(dlg_HWND, NULL, a.x, a.y, 0, 0, SWP_NOSIZE);  // ��ԭ�ϴ�λ��
	}
	ShowWindow(dlg_HWND, SW_SHOW);
}

void AppDlgClass::SetSize(int width, int height) {
	// ���ô��ڴ�С
	dlg_HWND = VariableClass::dlg_HWND; // ��ȡ��ǰ����
	if (dlg_HWND == NULL) {
		SetSize(width, height);
	}
	Dlg_SetNowRect(); // �������ڵĴ�����Ϣ
	SetWindowPos(dlg_HWND, NULL, Dlg_.x, Dlg_.y, width, height, 0);
	MoveCenter(); // �����ƶ����м�
}

void AppDlgClass::MoveCenter() {
	dlg_HWND = VariableClass::dlg_HWND; // ��ȡ��ǰ����
	int nFullWidth = GetSystemMetrics(SM_CXSCREEN), // ��ȡ��Ļ��С
		nFullHeight = GetSystemMetrics(SM_CYSCREEN);
	CRect rect;
	GetWindowRect(dlg_HWND, &rect);
	int x = (nFullWidth - (rect.right - rect.left)) / 2,
		y = (nFullHeight - (rect.bottom - rect.top)) / 2;
	SetWindowPos(dlg_HWND, NULL, x, y, 0, 0, SWP_NOSIZE);
}

void AppDlgClass::Dlg_SetNowRect(bool SetWH) {
	dlg_HWND = VariableClass::dlg_HWND; // ��ȡ��ǰ����
	CRect DlgCRect;
	GetWindowRect(dlg_HWND, &DlgCRect); // ��ȡ����Ļ�е�����
	Dlg_.x = DlgCRect.left;
	Dlg_.y = DlgCRect.top;
	if (SetWH) { // ���ÿ��
		Dlg_.width = DlgCRect.right - DlgCRect.left;
		Dlg_.height = DlgCRect.bottom - DlgCRect.top;
	}
}

AppDlgClass::Dlg AppDlgClass::Dlg_GetRect() {
	Dlg a;
	if (Dlg_.x == 0 || Dlg_.y == 0) { // ������ֵ
		int width = GetSystemMetrics(SM_CXSCREEN),
			height = GetSystemMetrics(SM_CYSCREEN); // ��ȡ��Ļ�ֱ���
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