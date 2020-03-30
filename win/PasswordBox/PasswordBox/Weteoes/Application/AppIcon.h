#ifndef AppIconClass_H
#define AppIconClass_H
#include <Windows.h>
#define WM_IconMsg (WM_USER + 101)

class AppIconClass
{
public:
	static NOTIFYICONDATA m_NotifyIcon;

	bool Icon_Add(HWND, HINSTANCE);
	void Icon_Remove();
};
#endif // !AppIconClass_