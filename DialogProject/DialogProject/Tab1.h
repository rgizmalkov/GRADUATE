#pragma once


// ���������� ���� CTab1

class CTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab1)

public:
	CTab1(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CTab1();

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = TAB1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditidp1();
	CString fid;
	afx_msg void OnEnChangePrinteditp1();
	CString _mwindow;
	afx_msg void OnBnClickedButton1();
};
