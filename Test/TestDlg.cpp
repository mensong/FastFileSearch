
// TestDlg.cpp : ʵ���ļ�
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



// CTestDlg �Ի���



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


// CTestDlg ��Ϣ�������

BOOL CTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	TCHAR szBuf[256] = { 0 };
	DWORD len = GetLogicalDriveStrings(sizeof(szBuf) / sizeof(TCHAR), szBuf);
	for (TCHAR * s = szBuf; *s; s += _tcslen(s) + 1)
	{
		TCHAR pan = s[0];
		m_cmbPans.AddString(CString(pan));

		class CDriveIndex* di = FILESEARCH::Ins().CreateIndex(pan);
		m_mpIndexs.insert(std::make_pair(pan, di));
	}
		
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
