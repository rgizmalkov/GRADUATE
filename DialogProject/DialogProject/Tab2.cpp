// Tab2.cpp: файл реализации
//

#include "stdafx.h"
#include "DialogProject.h"
#include "Tab2.h"
#include "afxdialogex.h"


// диалоговое окно CTab2

IMPLEMENT_DYNAMIC(CTab2, CDialogEx)

CTab2::CTab2(CWnd* pParent /*=NULL*/)
	: CDialogEx(TAB2, pParent)
{

}

CTab2::~CTab2()
{
}

void CTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTab2, CDialogEx)
END_MESSAGE_MAP()


// обработчики сообщений CTab2
