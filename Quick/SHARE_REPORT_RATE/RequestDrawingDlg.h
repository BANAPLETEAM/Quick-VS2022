#pragma once


// CRequestDrawingDlg 대화 상자입니다.






class CAccountLogRecord : public CXTPGridRecord
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
			const char *dayofweek[] = {"일", "월", "화", "수", "목", "금", "토"};
			CString strDayOfWeek;

			if (m_odtValue.GetStatus() == COleDateTime::null)
				return _T("-");

			strDayOfWeek.Format("(%s)", dayofweek[m_odtValue.GetDayOfWeek() - 1]);
			return m_odtValue.Format(m_strFormatString) + strDayOfWeek;
		}
	};

public:
	CAccountLogRecord(COleDateTime dtGenerate,CString sState,long nDeposit,long nBalance,CString sEtc);

protected:
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);

};



class CWaitDrawingRecord : public CXTPGridRecord
{
protected:

	class CMyDateRecordItem : public CXTPGridRecordItemDateTime
	{
	public:
		CMyDateRecordItem(COleDateTime dtDateTime)
			: CXTPGridRecordItemDateTime(dtDateTime)
		{
			m_strFormatString = _T("%m/%d %H:%M");
		}
		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			if (m_odtValue.GetStatus() == COleDateTime::null)
				return _T("-");

			return m_odtValue.Format(m_strFormatString);
		}
	};

	class CXTPGridRecordItemMyNumber: public CXTPGridRecordItemNumber
	{
	public:
		CXTPGridRecordItemMyNumber(long nValue) : CXTPGridRecordItemNumber(nValue)
		{
		}

		CString GetCaption(CXTPGridColumn* )
		{
			if((long)GetValue() == 0)
				return "";
			return LF->GetMyNumberFormat((long)GetValue());
		}
	};	



public:

	CWaitDrawingRecord(long nCompany,
		COleDateTime dtGenerate,
		CString strCompany, 
		long nBalance,
		CString strState, 
		long nRequestBalance,
		CString strBank,
		CString strAccount,
		CString strDeposit,
		CString strEtc,
		CString strReason,
		long nBankCode,
		CString strPhone,
		BOOL bRcpIntMode1);


	long m_nCompany;
	long m_nBalance;
	long m_nRequestBalance;
	long m_nBankCode;
	CString m_strPhone;
	BOOL m_bRcpIntMode1;

protected:
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);

};

class CRequestDrawingDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRequestDrawingDlg)

public:
	CRequestDrawingDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRequestDrawingDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_REQUEST_DRAWING_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnBnClickedDarwingBtn();
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnCbnSelchangeLogTypeCombo();

public:
	CXTPGridControl m_wndReport;
	CXTPGridControl m_lstWait;
	CComboBox m_cmbBank;
	CEdit m_edtAccount;
	CEdit m_edtDepositName;
	CEdit m_edtPhone;
	CEdit m_edtAmount;
	CEdit m_edtShareBalance;
	CEdit m_edtCompany;
	CEdit m_edtEtc;
	CComboBox m_cmbLogType;

	long m_nCompany;

public:
	static void MakeBankList(CComboBox *pCombo);
	void RefreshDrawingInfo();
	void CancelRequestDrawing();
;
};
