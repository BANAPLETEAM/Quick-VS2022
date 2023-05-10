#pragma once



// CShareTansferMyRequest 대화 상자입니다.

class CShareTansferMyRequest : public CMyDialog
{
	DECLARE_DYNAMIC(CShareTansferMyRequest)

public:
	CShareTansferMyRequest(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CShareTansferMyRequest();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SHARE_TRANSFER_MY_REQUEST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	void Refresh();
	CString ReturnType(int ntype);
	
	afx_msg void OnCustomdrawList ( NMHDR* pNMHDR, LRESULT* pResult );
	virtual BOOL OnInitDialog();
	
	CDateTimeCtrl m_dtTo;
	CDateTimeCtrl m_dtFrom;
	COleDateTime m_dtFromValue;
	COleDateTime m_dtToValue;
	afx_msg void OnBnClickedRefreshBtn();
	CDateButton m_DateBtn;
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
};
