#pragma once

#define MAX_STRING_COUNT 6

typedef struct
{
	COleDateTime dtEdit;
	long nRiderCompany;
	long nRNo;
	CString sRName;
	long nWNo;
	CString sWName;
	long nDepositType;
	long nDepositAllocateType;
	long nFixedDeposit;
	long nPayMentDay;
	CString sMyCallRateType;
	CString sOtherCallRateType;
	CString item[MAX_STRING_COUNT];
}DEPOSIT_EDIT_HISTORY;


class CRiderDepositRecord : public CXTPGridRecord
{
public:
	CRiderDepositRecord :: CRiderDepositRecord(int nCount, COleDateTime dtLog, int nRNo, CString sRName,
		int nWNo, CString sWName, CString sState, CString sBeforeEtc, CString sAfterEtc, BOOL bHead)
	{
		char buffer[10];

		if(bHead) 
		{
			sWName = (CString)itoa(nWNo, buffer, 10) + "/" + sWName;
			sRName = (CString)itoa(nRNo, buffer, 10) + "/" + sRName;

			AddItem(new CXTPGridRecordItemNumber(nCount));
			AddItem(new CXTPGridRecordItemText(sWName));
			AddItem(new CXTPGridRecordItemText(sRName));
			AddItem(new CXTPGridRecordItemText(dtLog.Format("%y-%m-%d %H:%M")));
		}
		else
		{
			AddItem(new CXTPGridRecordItemText(""));
			AddItem(new CXTPGridRecordItemText(""));
			AddItem(new CXTPGridRecordItemText(""));
			AddItem(new CXTPGridRecordItemText(""));
		}
		
		AddItem(new CXTPGridRecordItemText(sState));
		AddItem(new CXTPGridRecordItemText(sBeforeEtc));
		AddItem(new CXTPGridRecordItemText(sAfterEtc));

		m_sBeforeEtc = sBeforeEtc;
		m_sAfterEtc = sAfterEtc;

		m_bLine = FALSE;
	}

	CRiderDepositRecord :: CRiderDepositRecord(CString strDummy)
	{
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));

		m_bLine = TRUE;
	}

	
	void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
	{
		long nCol = pDrawArgs->pColumn->GetIndex();

		if(m_bLine == FALSE)
			pItemMetrics->clrBackground = RGB(210, 245, 200);// RGB(255, 51, 0);
		
		if(m_sBeforeEtc != m_sAfterEtc)	
		{
			if(nCol == 4)
				pItemMetrics->clrBackground = RGB(245, 200, 210);
			else if(nCol == 5 || nCol == 6)
				pItemMetrics->clrBackground = RGB(210, 200, 245);
		}
	}

public:
	BOOL m_bLine;
	CString m_sBeforeEtc;
	CString m_sAfterEtc;
};

typedef map <long, DEPOSIT_EDIT_HISTORY> DEPOSIT_EDIT_HISTORY_MAP;

class CRiderDepositEditHistoryDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderDepositEditHistoryDlg)

public:
	CRiderDepositEditHistoryDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRiderDepositEditHistoryDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RIDER_DEPOSIT_EDIT_HISTORY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CXTPListCtrl2 m_Report;
	long m_nRiderCompany;
	long m_nRNo;

	DEPOSIT_EDIT_HISTORY_MAP m_EditHistoryMap;

	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	void RefreshList();
	void CompareMap();
	CString GetDepositType(long nDepositType);
	CString GetPayMentDay(long nDepositType, long nPayMentDay);
};
