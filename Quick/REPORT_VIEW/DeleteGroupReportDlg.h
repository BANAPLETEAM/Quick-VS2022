#pragma once

class CDeleteGroupRecord : public CXTPGridRecord
{
public:
	class CCheckRecord : public CXTPGridRecordItem
	{
	public:
		CCheckRecord(BOOL bCheck)
		{
			HasCheckbox(TRUE);
			SetChecked(bCheck);
		}

	};

	


	CDeleteGroupRecord::CDeleteGroupRecord(COleDateTime dtReportStart, COleDateTime dtReportEnd,
		CString sReportState, long nUnCollection, long nBillCollection,long nReceivableAmount,
							long nID, long nReportState, long nGNo, BOOL bCheck)
	{
		CString strReportDay = dtReportStart.Format("%y-%m-%d") + " ~ " + dtReportEnd.Format("%y-%m-%d");
		CString strNo;
		strNo.Format("%ld", nID);

		AddItem(new CCheckRecord(bCheck));
		AddItem(new CXTPGridRecordItemText(strNo));
		AddItem(new CXTPGridRecordItemText(strReportDay));
		AddItem(new CXTPGridRecordItemText(sReportState));
		AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(nUnCollection)));
		AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(nBillCollection)));
		AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(nReceivableAmount)));

		m_nID = nID;
		m_nGNo = nGNo;
		m_nReportState = nReportState;
	}

	void CDeleteGroupRecord::GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{		
		int nCol = pDrawArgs->pColumn->GetIndex();
		int nRow = pDrawArgs->pRow->GetIndex();

		CDeleteGroupRecord *pReocrd = (CDeleteGroupRecord*)pDrawArgs->pRow->GetRecord();

		if(pReocrd->m_nReportState == 10 && nCol == 2 )
			pItemMetrics->clrForeground= RGB(255, 0, 0);
		else if(pReocrd->m_nReportState == 20 && nCol == 2 )
			pItemMetrics->clrForeground= RGB(0, 0, 255);
	};

public:
	long m_nID;
	long m_nGNo;
	long m_nReportState;
};


// CDeleteGroupReportDlg 대화 상자입니다.

class CDeleteGroupReportDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CDeleteGroupReportDlg)

public:
	CDeleteGroupReportDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDeleteGroupReportDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DELETE_GROUP_REPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	long m_nGNo;
	long m_nApplyReportID;
	BOOL m_bRefresh;
	CXTPListCtrl2 m_Report;
	void RefreshList();
	virtual BOOL OnInitDialog();
	static CString GetReportState(long nReportState);
	void CheckReportAbil(long &nCount, BOOL &bHasBillCollection, CString &sID);
	afx_msg void OnBnClickedMakeBtn();
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
};
