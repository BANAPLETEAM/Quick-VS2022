#pragma once

// CBranchReportTransferDlg ��ȭ �����Դϴ�.
class CBranchReportMainDlg;

class CBranchRecord :public CXTPGridRecord
{
protected:
	class CXTPGridRecordItemMyNumber : public CXTPGridRecordItemNumber
	{
	public:
		CXTPGridRecordItemMyNumber(long nProcessRate) : CXTPGridRecordItemNumber(nProcessRate)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			return m_ci.GetName((long)GetValue());
		}
	};

	class CXTPGridRecordItemMyNumber1 : public CXTPGridRecordItemNumber
	{
	public:
		CXTPGridRecordItemMyNumber1(long nProcessRate) : CXTPGridRecordItemNumber(nProcessRate)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			return m_ci.GetBranchName((long)GetValue());
		}
	};


public:
	CBranchRecord::CBranchRecord(long nCompany, CString sTel, CString sBranchName, bool bIsAllianceHead);

	void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);

	long m_nCompany;
	bool m_bIsAllianceHead;

};

class CBranchReportTransferDlg : public CMyFormView
{
	DECLARE_DYNCREATE(CBranchReportTransferDlg)

public:
	CBranchReportTransferDlg();           // ǥ�� �������Դϴ�.
	virtual ~CBranchReportTransferDlg();


// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_BRANCH_REPORT_TRANSFER_DLG };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	
public:
	CXTPGridControl m_wndReport;
	
	void RefreshList();
	void RefreshMoney();
	void MakeRequestWindow(bool bMake);
	bool IsRequest(int nCompany);
	virtual void OnInitialUpdate();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnBnClickedRefreshAllBtn();
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnBnClickedTransferBtn();
};
