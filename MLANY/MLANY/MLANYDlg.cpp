
// MLANYDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MLANY.h"
#include "MLANYDlg.h"
#include "afxdialogex.h"
#include"resource.h"
#include<fstream>
#include"LAN.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMLANYDlg 对话框



CMLANYDlg::CMLANYDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMLANYDlg::IDD, pParent)
	, FirstVT(_T(""))
	, Grammer(_T(""))
	, LastVT(_T(""))
	, PreForm(_T(""))
	, input(_T(""))
	, PROCESS(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMLANYDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITFIS, FirstVT);
	DDX_Text(pDX, IDC_EDITGRAM, Grammer);
	DDX_Text(pDX, IDC_EDITLAS, LastVT);
	DDX_Text(pDX, IDC_EDITPRE, PreForm);
	DDX_Control(pDX, IDC_EDITFIS, FIS_ED);
	DDX_Control(pDX, IDC_EDITGRAM, GRAM_ED);
	DDX_Control(pDX, IDC_EDITLAS, LAS_ED);
	DDX_Control(pDX, IDC_EDITPRE, PRE_ED);
	DDX_Text(pDX, IDC_EDITINPUT, input);
	DDX_Text(pDX, IDC_EDITPROCESS, PROCESS);
	DDX_Control(pDX, IDC_EDITPROCESS, ED_PRO);
}

BEGIN_MESSAGE_MAP(CMLANYDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONGRAM, &CMLANYDlg::OnBnClickedButtongram)
	ON_BN_CLICKED(IDC_BUTTONALY, &CMLANYDlg::OnBnClickedButtonaly)
	ON_BN_CLICKED(IDC_BUTTONPRO, &CMLANYDlg::OnBnClickedButtonpro)
END_MESSAGE_MAP()


// CMLANYDlg 消息处理程序

BOOL CMLANYDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMLANYDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMLANYDlg::OnPaint()
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
HCURSOR CMLANYDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMLANYDlg::OnBnClickedButtongram()
{
	// TODO:  在此添加控件通知处理程序代码
	CString filepathname;    //弹出对话框并读取文件
	CString filename;
	filepathname = "";
	filename = "";
	CFileDialog FileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, CString("ALL File (*.*)|*.*||"), AfxGetMainWnd());
	if (FileDlg.DoModal() == IDOK){
		filepathname = FileDlg.GetPathName();
		filename = FileDlg.GetFileName();
	}
	if (filepathname){
		lany.Main_Function(filepathname, Grammer, FirstVT, LastVT, PreForm);
		GRAM_ED.SetWindowTextW(Grammer);
	}
	else
	MessageBox(filepathname);
}


void CMLANYDlg::OnBnClickedButtonaly()
{
	// TODO:  在此添加控件通知处理程序代码
	FIS_ED.SetWindowTextW(FirstVT);
	LAS_ED.SetWindowTextW(LastVT);
	PRE_ED.SetWindowTextW(PreForm);
}


void CMLANYDlg::OnBnClickedButtonpro()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	lany.Include_Process(input, PROCESS);
	ED_PRO.SetWindowTextW(PROCESS);
}
