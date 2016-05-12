#pragma once


// диалоговое окно CTab2

class CTab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab2)

public:
	CTab2(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CTab2();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = TAB2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
};
