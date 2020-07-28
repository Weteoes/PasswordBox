#include "pch.h"

AppDlgClass::Dlg AppDlgClass::Dlg_; // ��¼����λ��

void AppDlgClass::Exit() {
	VariableClass::appIconClass.Icon_Remove(); // �Ƴ�����ͼ��
	exit(0);
}

void AppDlgClass::Close() {
	// ��ȡ��ǰ����
	dlg_HWND = VariableClass::dlg_HWND;
	SetWindowText(dlg_HWND, "Close");
	PostMessage(dlg_HWND, WM_CLOSE, 0, 0);
	VariableClass::dlg_HWND = NULL; // ��վ��
}

void AppDlgClass::Minimize(bool postCloseMsg) {
	// ��ȡ��ǰ����
	dlg_HWND = VariableClass::dlg_HWND;
	Minimize(dlg_HWND, postCloseMsg);
}

void AppDlgClass::Minimize(HWND dlg_HWND, bool postCloseMsg) {
	if (postCloseMsg) {
		// ���͹رմ����¼�
		::PostMessage(dlg_HWND, WM_CLOSE, NULL, NULL); 
	}
	// �������ڵĴ�����Ϣ
	Dlg_SetNowRect();
	// ��ȡ��Ļ��С
	int nFullWidth = GetSystemMetrics(SM_CXSCREEN), 
		nFullHeight = GetSystemMetrics(SM_CYSCREEN);
	// �ƶ�����λ��,����0����,�Ƶ������,��Ȼ�������Ӱ
	SetWindowPos(dlg_HWND, NULL, nFullWidth, nFullHeight, 0, 0, SWP_NOSIZE);  

	ShowWindow(dlg_HWND, SW_HIDE);
}

void AppDlgClass::Show(bool moveCenter) {
	// ��ȡ��ǰ����
	dlg_HWND = VariableClass::dlg_HWND;
	// �����ƶ����м�
	if (moveCenter) { MoveCenter(); }
	else {
		// ��ȡ����Ĵ�����Ϣ
		Dlg a = Dlg_GetRect();
		// ��ԭ�ϴ�λ��
		SetWindowPos(dlg_HWND, NULL, a.x, a.y, 0, 0, SWP_NOSIZE);  
	}
	ShowWindow(dlg_HWND, SW_SHOW);
}

void AppDlgClass::Show(HWND dlg_HWND) {
	MoveCenter(dlg_HWND); // �����ƶ����м�
	ShowWindow(dlg_HWND, SW_SHOW);
}

// ���ô��ڴ�С
void AppDlgClass::SetSize(int width, int height) {
	// ��ȡ��ǰ����
	dlg_HWND = VariableClass::dlg_HWND;
	if (dlg_HWND == NULL) {
		Sleep(50);
		SetSize(width, height);
	}
	// �������ڵĴ�����Ϣ
	Dlg_SetNowRect(); 
	SetWindowPos(dlg_HWND, NULL, Dlg_.x, Dlg_.y, width, height, 0);
	MoveCenter(); // �����ƶ����м�
}

void AppDlgClass::MoveCenter(HWND dlg_HWND) {
	// ��ȡ��Ļ��С
	int nFullWidth = GetSystemMetrics(SM_CXSCREEN), 
		nFullHeight = GetSystemMetrics(SM_CYSCREEN);
	CRect rect;
	GetWindowRect(dlg_HWND, &rect);
	int x = (nFullWidth - (rect.right - rect.left)) / 2,
		y = (nFullHeight - (rect.bottom - rect.top)) / 2;
	SetWindowPos(dlg_HWND, NULL, x, y, 0, 0, SWP_NOSIZE);
}

void AppDlgClass::MoveCenter() {
	// ��ȡ��ǰ����
	dlg_HWND = VariableClass::dlg_HWND; 
	MoveCenter(dlg_HWND);
}

void AppDlgClass::Dlg_SetNowRect(bool SetWH) {
	// ��ȡ��ǰ����
	dlg_HWND = VariableClass::dlg_HWND; 
	CRect DlgCRect;
	// ��ȡ����Ļ�е�����
	GetWindowRect(dlg_HWND, &DlgCRect); 
	Dlg_.x = DlgCRect.left;
	Dlg_.y = DlgCRect.top;
	if (SetWH) { 
		// ���ÿ��
		Dlg_.width = DlgCRect.right - DlgCRect.left;
		Dlg_.height = DlgCRect.bottom - DlgCRect.top;
	}
}

AppDlgClass::Dlg AppDlgClass::Dlg_GetRect() {
	Dlg a;
	// ������ֵ
	if (Dlg_.x == 0 || Dlg_.y == 0) { 
		// ��ȡ��Ļ�ֱ���
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