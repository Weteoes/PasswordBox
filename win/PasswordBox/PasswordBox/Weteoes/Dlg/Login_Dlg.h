
// PasswordBoxDlg.h: 头文件
//

#pragma once


// CPasswordBoxDlg 对话框
class Login_Dlg : public CDialogEx
{
// 构造
public:
	Login_Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Login };
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
	DECLARE_MESSAGE_MAP()

private:
	void Ready();
	void Ready_Dlg();
	void Ready_CEF();

public:
	afx_msg void OnBnClickedOk();
};
