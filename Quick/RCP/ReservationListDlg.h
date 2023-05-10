#pragma once


typedef struct {
	long nCompany;
	COleDateTime dt;
}SMS_RESERVATION;

// CReservationListDlg ��ȭ �����Դϴ�.

class CReservationListDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CReservationListDlg)

public:
	CReservationListDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CReservationListDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SMS_RESERVATION_LIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_List;
	long m_nCompany;
	BOOL m_bIntegrated;
	void RefreshList();

	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnLvnDeleteitemList1(NMHDR *pNMHDR, LRESULT *pResult);
};
