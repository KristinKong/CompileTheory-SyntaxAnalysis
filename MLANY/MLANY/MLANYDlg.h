
// MLANYDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include"resource.h"
#include"LAN.h"


// CMLANYDlg �Ի���
class CMLANYDlg : public CDialogEx
{
// ����
public:
	CMLANYDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MLANY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit3();
	// FirstVT
	CString FirstVT;
	// Grammer
	CString Grammer;
	// LastVT
	CString LastVT;
	// PreForm	// PreForm
	CString PreForm;
	CEdit FIS_ED;
	CEdit GRAM_ED;
	CEdit LAS_ED;
	CEdit PRE_ED;
	afx_msg void OnBnClickedButtongram();
	afx_msg void OnBnClickedButtonaly();
	CLAN lany;
	CString input;
	CString PROCESS;
	CEdit ED_PRO;
	afx_msg void OnBnClickedButtonpro();
};
