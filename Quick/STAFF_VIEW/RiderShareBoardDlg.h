#pragma once

#define WM_TWITTER_UPDATE WM_USER+100
#define WM_TWITTER_WRITE WM_USER+101

class CSmallTalkEditDlg;
class CAddRiderShareInfoDlg;

class CSmallTalkRecord : public CXTPGridRecord
{ 
public: 
	CSmallTalkRecord(long nTNo, 
		COleDateTime dtGenerate,
		long nWNo,
		long nWCompany,
		long nParentID,
		CString strWName,
		CString strMessage,
		long nRiderCompany,
		long nRNo,
		CString strRName)
	{
		char buffer[10];
		m_nTNo = nTNo;
		m_dt = dtGenerate;
		m_nWNo = nWNo;
		m_nWCompany = nWCompany;
		m_nTNo = nTNo;
		m_nRNo = nRNo;
		m_nRiderCompany = nRiderCompany;
		m_strRName = strRName;

		if(nParentID == 0)
			AddItem(new CXTPGridRecordItemText(itoa(nTNo, buffer, 10)));
		else
			AddItem(new CXTPGridRecordItemText(""));

		AddItem(new CXTPGridRecordItemText(dtGenerate.Format("%m-%d %H:%M:%S")));
		AddItem(new CXTPGridRecordItemText(strWName));
		AddItem(new CXTPGridRecordItemText(strMessage));

		if(nRiderCompany > 0 && nRNo > 0)
			AddItem(new CXTPGridRecordItemText(m_ci.GetName(nRiderCompany) + "/" + strRName));
		else
			AddItem(new CXTPGridRecordItemText(""));
 
		if(nParentID == 0)
		{
			AddItem(new CXTPGridRecordItemText("답글"));
			AddItem(new CXTPGridRecordItemText("배차제한"));
		}
		else
		{
			AddItem(new CXTPGridRecordItemText(""));
			AddItem(new CXTPGridRecordItemText(""));
		}
	}

	long m_nTNo;
	COleDateTime m_dt;
	long m_nWNo;
	long m_nWCompany;
	long m_nRNo;
	long m_nRiderCompany;
	CString m_strRName;

protected:

	void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{  
		if(pDrawArgs->pColumn && pDrawArgs->pRow)
		{
			int nCol = pDrawArgs->pColumn->GetItemIndex();
			int nRow = pDrawArgs->pRow->GetIndex();
			CSmallTalkRecord *pRecord = ((CSmallTalkRecord*)pDrawArgs->pRow->GetRecord());

			COleDateTime dtCur = COleDateTime::GetCurrentTime();
			COleDateTimeSpan span = dtCur - pRecord->m_dt;

			long nHour = span.GetTotalHours();
			long nMinute = span.GetTotalMinutes(); 
			long nSecond = span.GetTotalSeconds(); 

			if(dtCur.GetYear() == pRecord->m_dt.GetYear() &&
				dtCur.GetMonth() == pRecord->m_dt.GetMonth() &&
				dtCur.GetDay() == pRecord->m_dt.GetDay()) //같은날
			{
				if(nCol == 1)
				{ 
					if(nSecond < 60)
						pItemMetrics->strText.Format("%d초전", nSecond);
					else if(nMinute < 60)
						pItemMetrics->strText.Format("%d분전", nMinute);
					else if(nHour < 12)
						pItemMetrics->strText.Format("%d시간전", nHour);
					else
						pItemMetrics->strText = pRecord->m_dt.Format("%m-%d %H:%M");
				}		

				CString strTemp = pRecord->GetItem(3)->GetCaption(NULL);

				if(strTemp.Find("┗") > 0)
					pItemMetrics->clrBackground = RGB(0xFF, 0xFF, 0x99); 
				else
					pItemMetrics->clrBackground = RGB(230, 255, 230);

				pItemMetrics->pFont = &pDrawArgs->pControl->GetPaintManager()->m_fontBoldText;

			}
			else
			{  
				if(nCol == 1)
					pItemMetrics->strText = pRecord->m_dt.Format("%m-%d %H:%M");
			}

			if(nCol == 4)
				pItemMetrics->clrForeground = RGB(0, 0, 255);
			if(nCol == 5)
				pItemMetrics->clrForeground = RGB(0, 255, 0);
			if(nCol == 6)
				pItemMetrics->clrForeground = RGB(255, 0, 0);			
		}
	}
};

class CRiderShareBoardDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderShareBoardDlg)

public:
	CRiderShareBoardDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRiderShareBoardDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RIDER_SHARE_BOARD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CAddRiderShareInfoDlg *m_pAddRiderShareInfoDlg;
	CSmallTalkEditDlg *m_pSmallTalkEditDlg;
	CXTPGridControl m_wndTwiReport;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_From;
	CDateTimeCtrl m_To;
	CDateButton m_btnDate;
	long m_nParentID;

	long m_nRiderCompany;
	long m_nRNo;
	CString m_strRName;

	virtual BOOL OnInitDialog();
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedRefreshBtn();
	void OpenSmallTalkEdit(long nParentID, CString strText);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	static BOOL UpdateTwitter(long nParentID, CString strMsg);
	static BOOL WriteTwitter(long nParentID,CString strMsg, long nRiderCompany = 0, long nRNo = 0, CString strRName = 0);

	LONG OnTwitterUpdate(WPARAM wParam, LPARAM lParam);
	LONG OnTwitterWrite(WPARAM wParam, LPARAM lParam);

	afx_msg void OnUpdateTwitter();
	afx_msg void OnDeleteTwitter();
	afx_msg void OnSeeTwitter();

	void RefreshList();
	void MoveTalkEdit(BOOL bUpdate);
	void AddRiderInfo();
	BOOL DeleteTwitter(long nParent);
	void OpenAddRiderShareInfoDlg(long nRiderCompany = 0, long nRNo = 0, CString strRName = "");
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedInsertBtn();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

