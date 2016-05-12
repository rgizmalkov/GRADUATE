// Tab1.cpp: файл реализации
//

#include "stdafx.h"
#include "DialogProject.h"
#include "Tab1.h"
#include "afxdialogex.h"


// диалоговое окно CTab1

IMPLEMENT_DYNAMIC(CTab1, CDialogEx)

CTab1::CTab1(CWnd* pParent /*=NULL*/)
	: CDialogEx(TAB1, pParent)
	, fid(_T(""))
	, _mwindow(_T(""))
{

}

CTab1::~CTab1()
{
}

void CTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, EDITIDP1, fid);
	DDX_Text(pDX, PRINTEDITP1, _mwindow);
}


BEGIN_MESSAGE_MAP(CTab1, CDialogEx)
	ON_EN_CHANGE(EDITIDP1, &CTab1::OnEnChangeEditidp1)
	ON_EN_CHANGE(PRINTEDITP1, &CTab1::OnEnChangePrinteditp1)
	ON_BN_CLICKED(IDC_BUTTON1, &CTab1::OnBnClickedButton1)
END_MESSAGE_MAP()


// обработчики сообщений CTab1


void CTab1::OnEnChangeEditidp1()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}


void CTab1::OnEnChangePrinteditp1()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}


void CTab1::OnBnClickedButton1()
{


	// TODO: добавьте свой код обработчика уведомлений
}
