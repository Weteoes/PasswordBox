#pragma once
#ifndef AppDlgClass_H
#define AppDlgClass_H
class AppDlgClass {

public:
	void Exit(); // �˳�����
	void Close(); // �رմ���
	void Minimize(); // ��С������
	void Show(bool moveCenter = false); // ��ʾ����
	void SetSize(int width, int height); // ���ô��ڴ�С
	void MoveCenter(); // �ƶ����ڵ��м�

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