// PasswordBoxDlg.h: 头文件
//

#pragma once
#include <pch.h>

// CPasswordBoxDlg 对话框
class BrowserDlg : public CDialogEx
{
// 构造
public:
	BrowserDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Browser };
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
	void ReadyVariable();
	void ReadyDlg();
	void ReadyCEF();
	void ReadyCEFVariable();


private:
	void SetBorder(UINT nBorder);
	enum {
		BorderStyle_None = 0,
		BorderStyle_Dialog_Frame = 1,
		BorderStyle_Thin = 2,
		BorderStyle_Resizing = 3,
	};

public:
	std::string configCEFUrl = "http://www.weteoes.cn";		// URL
	std::string dlgTitle = "Browser";						// 窗口标题
	std::string browserKey = "";							// Browser Key
	HWND dlg_HWND;											// 窗口句柄
	int dlg_CEF;											// CEF句柄ID
	int browserListIndex;									// 在CEF_Handler中的浏览器ID
	CefRefPtr<CefBrowser> browser;							// 浏览器句柄
	int dlgWidth = 0;										// 默认窗口宽度
	int dlgHeight = 0;										// 默认窗口高度
	int dlgBorderStyle = BorderStyle_None;					// 默认窗口样式

public:
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnCancel(); // Alt + F4
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
};
