#pragma once

enum { ALL_BOUND_CALL, OUT_BOUND_CALL, IN_BOUND_CALL };

class CXTPRecFileRecord : public CXTPGridRecord
{
public:
	class CXTPGridRecordItemSec : public CXTPGridRecordItemNumber
	{
	public:
		CXTPGridRecordItemSec(long nSec) : CXTPGridRecordItemNumber(nSec)
		{
		}
		CString GetCaption(CXTPGridColumn* pColumn)
		{
			long nSec = (long)GetValue();
			if(nSec != 0)
				return LF->GetSecondTimeString(nSec);
			return "-";
		}
	};

	class CXTPGridRecordItemBound : public CXTPGridRecordItemNumber
	{
	public:
		CXTPGridRecordItemBound(int nBound) : CXTPGridRecordItemNumber(nBound)
		{
		}
		CString GetCaption(CXTPGridColumn* pColumn)
		{
			if(GetValue() == OUT_BOUND_CALL)
				return "아웃바운드";
			else if(GetValue() == IN_BOUND_CALL)
				return "인바운드";
			return "";
		}
	};

public:
	CXTPRecFileRecord::CXTPRecFileRecord(COleDateTime dtDate,  CString strBranch, CString strTNo, CString strKeyPhoneID, 
		CString strOperator, CString strPhone, int nBound, long nStartMiliSec, long nEndMiliSec, CString strFileName)
	{
		//if(nStartMiliSec > 0 && nEndMiliSec >= 0)
		//	dtDate = dtDate - COleDateTimeSpan(0, 0, 0, nStartMiliSec / 1000);

		CString strDate, strTime;
		strDate.Format("%04d-%02d-%02d(%s)", dtDate.GetYear(), dtDate.GetMonth(), dtDate.GetDay(), LF->GetDay(dtDate));
		strTime.Format("%02d:%02d:%02d", dtDate.GetHour(), dtDate.GetMinute(), dtDate.GetSecond());

		AddItem(new CXTPGridRecordItemText(strDate));
		AddItem(new CXTPGridRecordItemText(strTime));
		AddItem(new CXTPGridRecordItemText(strBranch));
		AddItem(new CXTPGridRecordItemText(strTNo));
		AddItem(new CXTPGridRecordItemText(strKeyPhoneID));
		AddItem(new CXTPGridRecordItemText(strOperator));
		AddItem(new CXTPGridRecordItemText(strPhone));
		AddItem(new CXTPGridRecordItemBound(nBound));
		if(nStartMiliSec > 0 && nEndMiliSec >= 0)
			AddItem(new CXTPGridRecordItemSec((nStartMiliSec - nEndMiliSec) / 1000));
		else
			AddItem(new CXTPGridRecordItemSec(0));
		AddItem(new CXTPGridRecordItemText("재생"));
		AddItem(new CXTPGridRecordItemText("선택"));

		m_dtDate = dtDate;
		m_nBound = nBound;
		m_strFileName = strFileName;
	}

	COleDateTime GetItemDate() { return m_dtDate; }
	int GetItemBound() { return m_nBound; }
	CString GetItemFileName() { return m_strFileName; }

	COleDateTime m_dtDate;
	int m_nBound;
	CString m_strFileName;
};

class CXTPListCtrlFile : public CXTPGridControl
{
public:
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{
		int nCol = pDrawArgs->pColumn->GetItemIndex();
		int nRow = pDrawArgs->pRow->GetIndex();

		if (nCol == 9 || nCol == 10)
			pItemMetrics->clrForeground = RGB(0, 0, 255);
	}
};


class CRcpPageRecordFileForm : public CMyFormView
{
	DECLARE_DYNCREATE(CRcpPageRecordFileForm)

protected:
	CRcpPageRecordFileForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CRcpPageRecordFileForm();


public:
	enum { IDD = IDD_RCP_PAGE_RECORD_FILE_FORM };
#ifdef _DEBUG
	virtual void		AssertValid() const;
	virtual void		Dump(CDumpContext& dc) const;
#endif

protected:
	enum { ALL_BOUND_CALL, OUT_BOUND_CALL, IN_BOUND_CALL };
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewExcel();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedRefresh();
	afx_msg void OnBnClickedRefreshToday();
	afx_msg void OnDtnDatetimechangeDatetimepicker(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnCbnSelchangeBoundType();
	afx_msg void OnBnClickedOrderCheck();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void RefreshList();
	void RefreshListToday();
	void SearchRecord(BOOL bVisible);

public:
	CXTPListCtrlFile m_List;

	COleDateTime m_dtLast;

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;

	CDateTimeCtrl m_dtpFrom;
	CDateTimeCtrl m_dtpTo;
	CDateButton m_btnDate;

	CFlatEdit2 m_edtSearch;
	CString m_strSearchNumber;
	CButton m_chkOrderCheck;

	BOOL m_bTodayRefresh;
	CComboBox m_cmbBoundType;

	int m_nSelectRow;
};