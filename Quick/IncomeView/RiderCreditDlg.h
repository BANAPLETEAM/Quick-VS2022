#pragma once

class CRiderCreditDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderCreditDlg)

public:
	CRiderCreditDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRiderCreditDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RIDER_CREDIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	long m_nCompany;
	long m_nRNo;
	CString m_sRName;
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnBnClickedInputBtn();
	CXTPListCtrl19 m_List;
	CEdit m_ChargeEdt;
	CEdit m_MemoEdt;
	CStatic m_SumStc;
	afx_msg void OnBnClickedDeleteBtn();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnDelete();
	CDateTimeCtrl m_ctlDate;
	CDateTimeCtrl m_ctlTime;
	COleDateTime m_dtDate;
	COleDateTime m_dtTime;
};
