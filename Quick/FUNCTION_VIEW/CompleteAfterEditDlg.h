#pragma once

class CCompleteAfterEditDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCompleteAfterEditDlg)

public:
	CCompleteAfterEditDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCompleteAfterEditDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_COMPLETE_AFTER_EDIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CXTPListCtrl37 m_List;
	virtual BOOL OnInitDialog();

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtFromCtl;
	CDateTimeCtrl m_dtToCtl;
	CDateButton m_DateBtn;

	static BOOL IsDifferentPayType(long nPrePayType, long nPayType);
	static BOOL IsDifferentState(long nPreState, long nState);

	CString GetLeftDate(COleDateTime dtDate);
	CString GetRequestState(long nRequestState);
	void InitColumn(BOOL bRequest);
	void RefreshList();
	long GetAbilMoney();

	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedRequestBtn();
	afx_msg void OnBnClickedMyRequestBtn();
	afx_msg void OnBnClickedCloseBtn();
};
