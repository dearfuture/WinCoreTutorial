
// Test_Dlg.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTest_DlgApp:
// �йش����ʵ�֣������ Test_Dlg.cpp
//

class CTest_DlgApp : public CWinApp
{
public:
	CTest_DlgApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTest_DlgApp theApp;