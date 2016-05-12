
// DialogProjectDlg.h : ���� ���������
//

#pragma once
#include "Tab1.h"
#include "Tab2.h"
#include "Tab3.h"



// ���������� ���� CDialogProjectDlg
class CDialogProjectDlg : public CDialogEx
{
private:
	CTab1 tab1;
	CTab2 tab2;
	CTab3 tab3;
	CTabCtrl* pTabCtrl;
// ��������
public:
	CDialogProjectDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGPROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTabctr(NMHDR *pNMHDR, LRESULT *pResult);
};
