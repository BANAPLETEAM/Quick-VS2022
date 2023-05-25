#pragma once
#include "afxwin.h"


// CSmsNewBulkConfirmDlg 대화 상자입니다.


class CXTPSmsNewBulkConfirmControl : public CXTPListCtrl2
{
public:
	void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{
		CXTPGridRecord *pRecord = pDrawArgs->pRow->GetRecord();
		/*long nCol = pDrawArgs->pColumn->GetIndex();

		if(nCol > 7)
			pItemMetrics->clrForeground = RGB(0, 0, 255);*/
 
		CString strDate = pRecord->GetItem(1)->GetCaption(NULL);
		CString strCount = pRecord->GetItem(3)->GetCaption(NULL);
		CString strSucessCount = pRecord->GetItem(4)->GetCaption(NULL);
		CString strFailCount = pRecord->GetItem(5)->GetCaption(NULL);
		CString strResultWaitCount = pRecord->GetItem(6)->GetCaption(NULL);
		CString strCancel = pRecord->GetItem(7)->GetCaption(NULL);

		COleDateTime dtDate(atoi(strDate.Left(4)), atoi(strDate.Mid(5, 2)), atoi(strDate.Mid(8, 2)), atoi(strDate.Mid(11, 2)), atoi(strDate.Mid(14, 2)), 0);

		COleDateTime dtBaseTime = COleDateTime::GetCurrentTime();

		if(dtBaseTime.GetHour() <= 7)
			dtBaseTime = dtBaseTime + COleDateTimeSpan(1, 0, 0, 0);
	
		dtBaseTime = COleDateTime(dtBaseTime.GetYear(), dtBaseTime.GetMonth(), dtBaseTime.GetDay(), 7, 0, 0);


		if(dtDate > dtBaseTime && strCancel.IsEmpty() && atoi(strCount) != atoi(strSucessCount) + atoi(strFailCount) + atoi(strResultWaitCount))
		{
			pItemMetrics->clrBackground = RGB(150, 255, 150);
		}
	}
};

class CSmsNewBulkConfirmDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSmsNewBulkConfirmDlg)

public:
	CSmsNewBulkConfirmDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSmsNewBulkConfirmDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SMS_NEW_BULK_CONFIRM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtpFrom;
	CDateTimeCtrl m_dtpTo;	
	CDateButton m_btnData;

	CXTPSmsNewBulkConfirmControl m_lstBulk;

	void CheckFilter();
	
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRefreshListBtn();
	afx_msg void OnBulkReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	CButton m_chkSms;
	CButton m_chkLms;
	CButton m_chkMms;
	afx_msg void OnCancelBulk();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnBnClickedSmsCheck();
	afx_msg void OnBnClickedLmsCheck();
	afx_msg void OnBnClickedMmsCheck();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedCancelRevBtn();
	CFlatEdit2 m_edtSearch;
	afx_msg void OnEnChangeSearchEdit();
	void RefreshList();
};
