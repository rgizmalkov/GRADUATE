#pragma once


// диалоговое окно CTab3

class CTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab3)

public:
	CTab3(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CTab3();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = TAB3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
};
