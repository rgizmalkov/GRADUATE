#pragma once


// ���������� ���� CTab3

class CTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab3)

public:
	CTab3(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CTab3();

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = TAB3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
};
