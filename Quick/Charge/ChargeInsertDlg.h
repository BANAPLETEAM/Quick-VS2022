#pragma once
#include "afxwin.h"


// CChargeInsertDlg 대화 상자입니다.

class CXTPGridChargeControl;

class CChargeInsertDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeInsertDlg)

public:
	CChargeInsertDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChargeInsertDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHARGE_INSERT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
