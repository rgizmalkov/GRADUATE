// Tab3.cpp: файл реализации
//

#include "stdafx.h"
#include "DialogProject.h"
#include "Tab3.h"
#include "afxdialogex.h"


// диалоговое окно CTab3

IMPLEMENT_DYNAMIC(CTab3, CDialogEx)

CTab3::CTab3(CWnd* pParent /*=NULL*/)
	: CDialogEx(TAB3, pParent)
{

}

CTab3::~CTab3()
{
}

void CTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTab3, CDialogEx)
END_MESSAGE_MAP()


// обработчики сообщений CTab3
