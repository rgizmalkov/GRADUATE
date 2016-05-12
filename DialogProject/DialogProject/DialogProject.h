
// DialogProject.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CDialogProjectApp:
// О реализации данного класса см. DialogProject.cpp
//

class CDialogProjectApp : public CWinApp
{
public:
	CDialogProjectApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CDialogProjectApp theApp;