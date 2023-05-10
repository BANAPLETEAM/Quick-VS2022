#pragma once

class CShowRiderInfoDlg;
// CRiderCancelLogDlg ��ȭ �����Դϴ�.

class CRiderCancelLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderCancelLogDlg)

public:
	CRiderCancelLogDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRiderCancelLogDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RIDER_CANCEL_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CDateButton m_DateBtn;
	CXTPListCtrl3 m_wndReport;
	CShowRiderInfoDlg *m_pParent;
	CRect m_ParentRect;

	CDateTimeCtrl m_dtFromCtl;
	CDateTimeCtrl m_dtToCtl;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;

	afx_msg void OnBnClickedRefreshBtn();
	void Moving();
	void RefreshList();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
