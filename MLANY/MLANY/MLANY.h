
// MLANY.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMLANYApp: 
// �йش����ʵ�֣������ MLANY.cpp
//

class CMLANYApp : public CWinApp
{
public:
	CMLANYApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMLANYApp theApp;