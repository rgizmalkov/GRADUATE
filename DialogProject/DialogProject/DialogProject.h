
// DialogProject.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CDialogProjectApp:
// � ���������� ������� ������ ��. DialogProject.cpp
//

class CDialogProjectApp : public CWinApp
{
public:
	CDialogProjectApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CDialogProjectApp theApp;