
// MLANYDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMLANYDlg �Ի���



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


// CMLANYDlg ��Ϣ�������

BOOL CMLANYDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMLANYDlg::OnPaint()
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
HCURSOR CMLANYDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMLANYDlg::OnBnClickedButtongram()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString filepathname;    //�����Ի��򲢶�ȡ�ļ�
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	FIS_ED.SetWindowTextW(FirstVT);
	LAS_ED.SetWindowTextW(LastVT);
	PRE_ED.SetWindowTextW(PreForm);
}


void CMLANYDlg::OnBnClickedButtonpro()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	lany.Include_Process(input, PROCESS);
	ED_PRO.SetWindowTextW(PROCESS);
}
