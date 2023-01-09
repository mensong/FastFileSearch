
// TestDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include <map>

// CTestDlg 对话框
class CTestDlg : public CDialogEx
{
// 构造
public:
	CTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	std::map<TCHAR, class CDriveIndex*> m_mpIndexs;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnsearch();
	CComboBox m_cmbPans;
};
