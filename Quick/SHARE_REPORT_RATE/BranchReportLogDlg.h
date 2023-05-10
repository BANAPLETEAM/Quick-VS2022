#pragma once
#include "afxwin.h"

class CAccountRecord : public CXTPGridRecord
{
protected:
	class CMyDateRecordItem : public CXTPGridRecordItemDateTime
	{
	public:
		CMyDateRecordItem(COleDateTime dtDateTime)
			: CXTPGridRecordItemDateTime(dtDateTime)
		{
			m_strFormatString = _T("%y/%m/%d %H:%M");
		}
		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			const char *dayofweek[] = {"��", "��", "ȭ", "��", "��", "��", "��"};
			CString strDayOfWeek;

			if (m_odtValue.GetStatus() == COleDateTime::null)
				return _T("-");

			strDayOfWeek.Format("(%s)", dayofweek[m_odtValue.GetDayOfWeek() - 1]);
			return m_odtValue.Format(m_strFormatString) + strDayOfWeek;
		}
	};

	class CXTPGridRecordItemChargeNumber : public CXTPGridRecordItemNumber
	{
	public:
		CXTPGridRecordItemChargeNumber(long nProcessRate) : CXTPGridRecordItemNumber(nProcessRate)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			if(GetValue() != -1)
				return ::GetMyNumberFormat((long)GetValue()) + "��";
			else
				return "";			

		}
	};


public:
	void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics);
public:

	CAccountRecord::CAccountRecord(COleDateTime dtGenerate,CString sState,long nDeposit,long nBalance,CString sEtc);
};

// CBranchReportLogDlg �� ���Դϴ�.

class CBranchReportLogDlg : public CMyFormView
{
	DECLARE_DYNCREATE(CBranchReportLogDlg)

protected:
	CBranchReportLogDlg();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CBranchReportLogDlg();

public:
	enum { IDD = IDD_BRANCH_REPORT_LOG_DLG };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CXTPGridControl m_wndReport;

	virtual void OnInitialUpdate();
	afx_msg void OnViewExcel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRefreshBtn();
	void CBranchReportLogDlg::RefreshList();
	int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	CButton m_TransferChk;
	
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
};


