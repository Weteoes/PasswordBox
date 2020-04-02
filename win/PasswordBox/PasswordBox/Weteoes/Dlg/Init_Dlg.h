
// PasswordBoxDlg.h: 头文件
//

#pragma once


// CPasswordBoxDlg 对话框
class Init_Dlg : public CDialogEx
{
// 构造
public:
	Init_Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Init };
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
	afx_msg LRESULT OnNotifyMsg(WPARAM, LPARAM); // 托盘图标事件
	afx_msg LRESULT OnTaskBarRestart(WPARAM, LPARAM); // 托盘图标重启
	DECLARE_MESSAGE_MAP()

private:
	void Ready();
	void Ready_Dlg();
	void Ready_CEF();
	void Ready_Icon();

private:
	void IconMenu_Exit();

private:
	int browserListIndex;

public:
	afx_msg void OnBnClickedOk();
	virtual void OnCancel();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
