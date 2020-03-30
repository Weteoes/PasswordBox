#include <pch.h>
#include "AppIcon.h"
#include <resource.h>

NOTIFYICONDATA AppIconClass::m_NotifyIcon; //����

bool AppIconClass::Icon_Add(HWND Dlg_HWND, HINSTANCE Dlg_HINSTANCE) {
	start:
	m_NotifyIcon.cbSize = sizeof(NOTIFYICONDATA);     // �ṹ��С
	m_NotifyIcon.hWnd = Dlg_HWND;                 // ����������Ϣ�Ĵ��ھ��
	m_NotifyIcon.uID = IDI_ICON1;                 // Ӧ�ó����ж��������ͼ��ID
	m_NotifyIcon.hIcon = LoadIcon(Dlg_HINSTANCE, MAKEINTRESOURCE(IDI_ICON1)); // ����ͼ����
	wcscpy_s((wchar_t*)m_NotifyIcon.szTip, 128, (wchar_t*)AppConfigClass::Get_SoftwareName().c_str()); // ͼ����ʾ��ʾ�ַ���
	m_NotifyIcon.uCallbackMessage = WM_IconMsg;//WM_USER_NOTIFY;               // �Զ�����Ϣ,����ͼ�귢�͵���Ϣ
	m_NotifyIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;       // ��������
	/* ���ͼ�� */
	if (!Shell_NotifyIcon(NIM_ADD, &m_NotifyIcon)) { //���ʧ��
		Sleep(1000);
		goto start;
	}
	return true;
}
void AppIconClass::Icon_Remove() {
	Shell_NotifyIcon(NIM_DELETE, &m_NotifyIcon);
}