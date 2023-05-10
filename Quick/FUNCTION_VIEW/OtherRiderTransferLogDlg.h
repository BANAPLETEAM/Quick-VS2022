#pragma once



class CXTPListCtrl52 : public CXTPListCtrl2
{
public:
	virtual void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics) 
	{
		int nCol = pDrawArgs->pColumn->GetItemIndex();
		int nRow = pDrawArgs->pRow->GetIndex();

		long nCompany = GetItemLong(nRow);

		if(m_ci.IsCrossCompany(nCompany)) 
			pItemMetrics->clrBackground = RGB(255, 235, 235);
	}
};
// COtherRiderTransferLogDlg 대화 상자입니다.

class COtherRiderTransferLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(COtherRiderTransferLogDlg)

public:
	COtherRiderTransferLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~COtherRiderTransferLogDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_OTHER_RIDER_TRANSFER_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl m_dtFrom;
	CDateTimeCtrl m_dtTo;
	COleDateTime m_From;
	COleDateTime m_To;

	CDateButton m_btnDate;
	CXTPListCtrl52 m_lstReport;

	virtual BOOL OnInitDialog();
	void RefreshList();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
