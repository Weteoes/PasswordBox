#pragma once
#ifndef AppDlgClass_H
#define AppDlgClass_H
class AppDlgClass {

public:
	void Exit();												// �˳�����
	void Close();												// �رմ���
	void Minimize(bool postCloseMsg = false);					// ��С������
	void Minimize(HWND dlg_HWND, bool postCloseMsg = false);	// ��С������(ͨ�����ھ��)
	void Show(bool moveCenter = false);							// ��ʾ����
	void Show(HWND dlg_HWND);									// ��ʾ����(ͨ�����ھ��)
	void SetSize(int width, int height);						// ���ô��ڴ�С
	void MoveCenter();											// �ƶ����ڵ��м�
	void MoveCenter(HWND dlg_HWND);								// �ƶ����ڵ��м�(ͨ�����ھ��)

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