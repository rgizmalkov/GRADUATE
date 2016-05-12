
// DialogProjectDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "DialogProject.h"
#include "DialogProjectDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// диалоговое окно CDialogProjectDlg



CDialogProjectDlg::CDialogProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOGPROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDialogProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDialogProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, TABCTR, &CDialogProjectDlg::OnTcnSelchangeTabctr)
END_MESSAGE_MAP()


// обработчики сообщений CDialogProjectDlg

BOOL CDialogProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	pTabCtrl = (CTabCtrl*)GetDlgItem(TABCTR);
	//Tab1 init
	tab1.Create(TAB1, pTabCtrl);

	TCITEM item1;
	item1.mask = TCIF_TEXT | TCIF_PARAM;
	item1.lParam = (LPARAM)& tab1;
	item1.pszText = _T("Search");
	pTabCtrl->InsertItem(0, &item1);

	CRect rcItem;
	pTabCtrl->GetItemRect(0, &rcItem);
	tab1.SetWindowPos(NULL, rcItem.left, rcItem.bottom, rcItem.right - 1, rcItem.top - 1, SWP_NOSIZE | SWP_NOZORDER);
	//Tab2 init////////////////////////
	tab2.Create(TAB2, pTabCtrl);

	TCITEM item2;
	item2.mask = TCIF_TEXT | TCIF_PARAM;
	item2.lParam = (LPARAM)& tab2;
	item2.pszText = _T("Add/drop");
	pTabCtrl->InsertItem(1, &item2);

	CRect rcItem2;
	pTabCtrl->GetItemRect(0, &rcItem2);
	tab2.SetWindowPos(NULL, rcItem2.left, rcItem2.bottom, rcItem2.right, rcItem2.top, SWP_NOSIZE | SWP_NOZORDER);
	//Tab3 init/////////////////////////
	tab3.Create(TAB3, pTabCtrl);

	TCITEM item3;
	item3.mask = TCIF_TEXT | TCIF_PARAM;
	item3.lParam = (LPARAM)& tab3;
	item3.pszText = _T("Collisions");
	pTabCtrl->InsertItem(2, &item3);

	CRect rcItem3;
	pTabCtrl->GetItemRect(0, &rcItem3);
	tab3.SetWindowPos(NULL, rcItem3.left, rcItem3.bottom, rcItem3.right - 1, rcItem3.top - 1, SWP_NOSIZE | SWP_NOZORDER);
	////////////////////////////////////
	tab1.ShowWindow(SW_SHOW);
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CDialogProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CDialogProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CDialogProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDialogProjectDlg::OnTcnSelchangeTabctr(NMHDR *pNMHDR, LRESULT *pResult)
{

	int ii = pTabCtrl->GetCurSel();
	
	//std::cout << ii << '\n';
	//CString sMsg;
	//std::string s = std::to_string(ii);
	//sMsg.Format(_T("%S"), s.c_str());

	//MessageBox(sMsg, L"Message", MB_OK | MB_ICONINFORMATION);
	tab1.ShowWindow(ii == 0 ? SW_SHOW : SW_HIDE);
	tab2.ShowWindow(ii == 1 ? SW_SHOW : SW_HIDE);
	tab3.ShowWindow(ii == 2 ? SW_SHOW : SW_HIDE);

	// TODO: добавьте свой код обработчика уведомлений
	// TODO: добавьте свой код обработчика уведомлений
	*pResult = 0;
}
