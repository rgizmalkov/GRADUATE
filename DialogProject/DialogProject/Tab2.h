#pragma once


// ���������� ���� CTab2

class CTab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab2)

public:
	CTab2(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CTab2();

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = TAB2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
};
