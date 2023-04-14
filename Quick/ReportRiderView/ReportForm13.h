

typedef struct{
	long nTNo;	
	long nCompany;
	CString sOName;
	CString sSName;
	CString sDName;
	COleDateTime dt1;
	long nPayType;
	long nRiderCompany;
	long nRNo;
	CString sRName;
	long nChargeSum;
	long nChargeTrans;
	long nState;
	BOOL bGiveChargeToRider;
}CREDIT_STRUCT;

class CReportForm13 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm13)

protected:
	CReportForm13();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CReportForm13();

public:
	enum { IDD = IDD_REPORT13 };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRefreshBtn();

	afx_msg void OnViewExcel();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
public:
	CXTPListCtrl6 m_wndReport;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtFromCtl;
	CDateTimeCtrl m_dtToCtl;
	CDateButton m_DateBtn;
	CButton m_RefreshBtn;

	virtual void OnInitialUpdate();
	void RefreshList();

	void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);

	CString GetTransferState(CString sOrder, CString sRider,  BOOL bSuccess);
	CString GetOrderShareType(CREDIT_STRUCT *st);
	CString GetRiderShareType(CREDIT_STRUCT *st);

	BOOL InsertCharge(long nSendMoney, long nTNo, long nRiderCompay, long nRNo, CString sRName);
};



