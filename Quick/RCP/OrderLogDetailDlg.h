#pragma once
#include "afxwin.h"
#include "PPTooltip.h"

class COrderLogRecord : public CXTPGridRecord
{

public:
	COrderLogRecord :: COrderLogRecord(int nCount, COleDateTime dtLog, int nState, int nWNo, int nWCompany,
		CString sLog, int nRNo, int nRCompany, CString strWName, int nColor);

	void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics);

	long m_nColor;
	long m_nWNo;
	long m_nRiderCompany;
	long m_nRNo;

protected:
	class CXTPGridRecordItemStateNumber : public CXTPGridRecordItemNumber
	{
	public:
		CXTPGridRecordItemStateNumber(long nProcessRate):CXTPGridRecordItemNumber(nProcessRate)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			return LF->GetStateString((long)GetValue());
		}

	};
	class CXTPGridRecordItemRNoNumber : public CXTPGridRecordItemNumber
	{
	public:
		CString m_strWName;

		CXTPGridRecordItemRNoNumber(long nProcessRate):CXTPGridRecordItemNumber(nProcessRate)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			int nValue = (long)GetValue();

			if(nValue == m_ui.nWNo)
				return "본인";
			else if(nValue == -1)
				return "기사";
			else if(nValue == -2)
				return "서버";
			else
			{
				CString strWno;
 
				if(!m_strWName.IsEmpty())
					strWno.Format("%s(%d)", m_strWName, nValue);
				else
					strWno.Format("%d",nValue);

				return strWno;
			}
		}
	};

	class CXTPGridRecordItemCompanyNumber : public CXTPGridRecordItemNumber
	{
	public:
		CXTPGridRecordItemCompanyNumber(long nProcessRate):CXTPGridRecordItemNumber(nProcessRate)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			long nValues = (long)GetValue();

			if(nValues == 0)
				return "";
			else
				return m_ci.GetBranchName(nValues);
		}		
	};

	class CXTPGridRecordItemEmptyZeroNumber : public CXTPGridRecordItemNumber
	{
	public:
		CXTPGridRecordItemEmptyZeroNumber(long nProcessRate):CXTPGridRecordItemNumber(nProcessRate)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			long nValues = (long)GetValue();



			if(nValues == 0)
				return "";
			else
			{
				char buffer[20];
				return itoa(nValues, buffer,10);
			}
		}		
	};

	class CXTPGridRecordItemMyDateTime : public CXTPGridRecordItemDateTime
	{
	public:
		CXTPGridRecordItemMyDateTime(COleDateTime dtDateTime)
			: CXTPGridRecordItemDateTime(dtDateTime)
		{
			m_strFormatString = _T("%m-%d %H:%M:%S");
		}

	};

};

class COrderChangeRecord : public CXTPGridRecord
{
protected:
	class CXTPGridRecordItemCompanyNumber : public CXTPGridRecordItemNumber
	{
	public:
		CXTPGridRecordItemCompanyNumber(long nProcessRate):CXTPGridRecordItemNumber(nProcessRate)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			return m_ci.GetBranchName((long)GetValue());
		}		
	};

	class CXTPGridRecordItemMyDateTime : public CXTPGridRecordItemDateTime
	{
	public:
		CXTPGridRecordItemMyDateTime(COleDateTime dtDateTime)
			: CXTPGridRecordItemDateTime(dtDateTime)
		{
			m_strFormatString = _T("%m-%d %H:%M:%S");
		}

	};


public:
	COrderChangeRecord :: COrderChangeRecord(int nCount, int nRNo, CString strEditor, int nWCompany, COleDateTime dtLog,	
		CString sState, CString sBeforeEtc, CString sAfterEtc, int nColor);
	COrderChangeRecord :: COrderChangeRecord(int nCount, CString sState, CString sBeforeEtc, CString sAfterEtc, int nColor);

	void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics);

	int m_nColor;
	int m_nCount;
	CString m_sState;
	CString m_sBeforeEtc;
	CString m_sAfterEtc;
};


class COrderLogDetailDlg : public CMyDialog
{
	DECLARE_DYNAMIC(COrderLogDetailDlg)

public:
	COrderLogDetailDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~COrderLogDetailDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ORDER_LOG_DETAIL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnPaint();
	afx_msg void OnBnClickedCancel();
	afx_msg void NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result);
	afx_msg void OnBnClickedRiderInfoBtn();
	afx_msg void OnBnClickedReAllocateBtn();
	afx_msg void  OnReAllocate();
	afx_msg void  OnRiderInfo();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint point);
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);

	CString GetFoodOrderState(BOOL bFoodOrder, COleDateTime dtFoodComplete);
	CString GetReservedState(long nReserved, COleDateTime dtReserved);
	void CompareMap();
	void ReFreshOrderLogReport(BOOL bFullSearch);
	void ReFreshOrderChangeReport();
	void InsertChangeChildRecord(int nCount, CString sChange, CString sBefore, CString sAfter, CXTPGridRecord* pMainRecord, CPoint cpColor);

	CXTPGridControl m_lstOrderLog;
	CXTPGridControl m_lstOrderChange;

	MAP_EDIT_HISTORY m_EditHistoryMap;
	CPPToolTip m_tooltip;

	long m_nOrderCompany;
	long m_nTNo;
	long m_nState;

	BOOL m_bCross;

	CStatic m_stcRect;
	CMyStatic m_stc;

	CButton m_CancelBtn;
	CPoint m_cpColor[50];

	BOOL m_bFullSearch;

	afx_msg void OnBnClickedRefreshBtn();
};
