#pragma once



// CShareTansferMyRequest ��ȭ �����Դϴ�.

class CShareTansferMyRequest : public CMyDialog
{
	DECLARE_DYNAMIC(CShareTansferMyRequest)

public:
	CShareTansferMyRequest(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CShareTansferMyRequest();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SHARE_TRANSFER_MY_REQUEST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
