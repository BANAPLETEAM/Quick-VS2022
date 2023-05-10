#pragma once


typedef struct {
	long nCompany;
	COleDateTime dt;
}SMS_RESERVATION;

// CReservationListDlg 대화 상자입니다.

class CReservationListDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CReservationListDlg)

public:
	CReservationListDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CReservationListDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_SMS_RESERVATION_LIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
