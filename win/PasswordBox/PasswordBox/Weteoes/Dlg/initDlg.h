
// PasswordBoxDlg.h: 头文件
//

#pragma once


// CPasswordBoxDlg 对话框
class initDlg : public CDialogEx
{
// 构造
public:
	initDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INIT };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnNotifyMsg(WPARAM, LPARAM);			 // 托盘图标事件
	afx_msg LRESULT OnTaskBarRestart(WPARAM, LPARAM);		 // 托盘图标重启
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);			 // F1帮助菜单
	DECLARE_MESSAGE_MAP()

private:
	void Ready();
	bool CreateDlg();
	void ReadyVariable();
	void ReadyIcon();

private:
	void IconMenu_Exit();

private:
	static HWND dlg_HWND;					// 窗口句柄
	static int dlg_CEF;						// CEF句柄ID

public:
	virtual void OnCancel(); // Alt + F4
};
