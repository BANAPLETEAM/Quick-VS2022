
// CReportForm12 폼 뷰입니다.

class CSmsRecord : public CXTPGridRecord
{
protected:

	class CXTPGridRecordItemMyPerNumber : public CXTPGridRecordItemNumber
	{
	public:
		CXTPGridRecordItemMyPerNumber(long nProcessRate) : CXTPGridRecordItemNumber(nProcessRate)
		{
		}

		CString GetCaption(CXTPGridColumn* )
		{
			char buffer[10];
			return CString(ltoa(GetValue(), buffer, 10)) + "%";
		}
	};	

	class CXTPGridRecordItemMyHyponNumber : public CXTPGridRecordItemNumber
	{
	public:
		CXTPGridRecordItemMyHyponNumber(long nProcessRate) : CXTPGridRecordItemNumber(nProcessRate)
		{
		}

		CString GetCaption(CXTPGridColumn* )
		{
			char buffer[10];
			int nValue = GetValue();

			if(nValue == 0)
				return "-";
			else
				return CString(itoa(nValue, buffer, 10)) ;
		}
	};	

	class CXTPGridRecordItemMyFormatNumber : public CXTPGridRecordItemNumber
	{
	public:
		CXTPGridRecordItemMyFormatNumber(long nProcessRate) : CXTPGridRecordItemNumber(nProcessRate)
		{
		}

		CString GetCaption(CXTPGridColumn* )
		{
			return LF->GetMyNumberFormat(GetValue());
		}
	};	



public:
	CSmsRecord::CSmsRecord();
	CSmsRecord::CSmsRecord(CString sDate,  long nBannerCount, long nAllocateCount,
		long nBannerCompleteCount, long nAllocateCompleteCount, 
		long nBannerFailCount, long nAllocateFailCount, long nCompletePer, long nRealCompletePer,
		long n0, long n1, long n2, long n3, long n4, long n5, long n6,long nCustomerError, long nServiceError);
public:
	void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);

	long m_nBannerCount;
	long m_nBannerCompleteCount;
	long m_nBannerFaileCount;
	long m_nAllocateCount;
	long m_nAllocateCompleteCount;
	long m_nAllocateFailCount;
};

class CReportForm12 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm12)

protected:
	CReportForm12();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CReportForm12();

public:
	enum { IDD = IDD_REPORT12 };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CXTPGridControl m_wndReport;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtFromCtl;
	CDateTimeCtrl m_dtToCtl;
	CDateButton m_DateBtn;
	CButton m_RefreshBtn;

	void RefreshList();
	afx_msg void OnBnClickedRefreshBtn();
	virtual void OnInitialUpdate();
};


