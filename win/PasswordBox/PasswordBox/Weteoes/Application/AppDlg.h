#pragma once
#ifndef AppDlgClass_H
#define AppDlgClass_H
class AppDlgClass {

public:
	void Close(); // �رմ���
	void Minimize(); // ��С������
	void Show(); // ��ʾ����
	void SetSize(int width, int height); // ���ô��ڴ�С

private:
	HWND dlg_HWND;

private:
	//��¼������Ϣ
	void Dlg_SetNowRect(bool = false); // ����Dlg����
	struct Dlg {
		int x, y;
		int width, height;
	};
	static Dlg Dlg_;
	AppDlgClass::Dlg Dlg_GetRect();  // ��ȡDlg��¼
};
#endif