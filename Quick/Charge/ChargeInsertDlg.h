#pragma once
#include "afxwin.h"


// CChargeInsertDlg ��ȭ �����Դϴ�.

class CXTPGridChargeControl;

class CChargeInsertDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeInsertDlg)

public:
	CChargeInsertDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CChargeInsertDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CHARGE_INSERT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CXTPListCtrl2 m_lstStart;
	CXTPListCtrl2 m_lstDest;

	CXTPGridChargeControl *m_plstDong;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();

	void InitList(); 
	long m_nCol;
	CFlatEdit2 m_edtCharge;
	CString m_strCharge;
	afx_msg void OnBnClickedCancel();
};
