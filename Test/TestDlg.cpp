
// TestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include <string>
#include <vector>
#include "Test.h"
#include "TestDlg.h"
#include "afxdialogex.h"
#include "../FileSearch/FastFileSearch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CTestDlg 对话框



CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBPAN, m_cmbPans);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNSEARCH, &CTestDlg::OnBnClickedBtnsearch)
END_MESSAGE_MAP()


// CTestDlg 消息处理程序

BOOL CTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	TCHAR szBuf[256] = { 0 };
	DWORD len = GetLogicalDriveStrings(sizeof(szBuf) / sizeof(TCHAR), szBuf);
	for (TCHAR * s = szBuf; *s; s += _tcslen(s) + 1)
	{
		TCHAR pan = s[0];
		m_cmbPans.AddString(CString(pan));

		class CDriveIndex* di = FILESEARCH::Ins().CreateIndex(pan);
		m_mpIndexs.insert(std::make_pair(pan, di));
	}
		
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestDlg::OnBnClickedBtnsearch()
{
	CString sPan;
	m_cmbPans.GetWindowText(sPan);
	if (sPan.IsEmpty())
		return;
	BOOL all = 0;
	WCHAR* result = FILESEARCH::Ins().Search(m_mpIndexs[sPan[0]], L"a", NULL, TRUE, TRUE, 1000, &all);
}
