#pragma once


// CMyAllianceManagerDlg 대화 상자입니다.


class CMyAllianceRecord : public CXTPGridRecord
{
protected:


	class CGiveTakeRateRecordItemNumber : public CXTPGridRecordItemNumber
	{
	public:
		CGiveTakeRateRecordItemNumber(double nValue)
			: CXTPGridRecordItemNumber(nValue, _T("%0.1f%%"))
		{

		}

		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			CString strCaption;
			
			if(m_dValue > 1000)
				strCaption = "절대발주사";
			else if(m_dValue < 10)
				strCaption = "절대수주사";
			else
				strCaption.Format(m_strFormatString, m_dValue);

			return strCaption;
		}
	};



	class CMyRecordItemDateTime : public CXTPGridRecordItemDateTime
	{
	public:
		CMyRecordItemDateTime(COleDateTime dtDateTime)
			: CXTPGridRecordItemDateTime(dtDateTime)
		{
			m_strFormatString = _T("%m-%d %H:%M");
		}
	};


	class CShareSecRecordItem : public CXTPGridRecordItem
	{
	public:
		CShareSecRecordItem(UINT nValue)
		{
			m_nValue = nValue;
			GetEditOptions(NULL)->AddConstraint(_T("즉시"), 1);
			GetEditOptions(NULL)->AddConstraint(_T("5초"), 5);
			GetEditOptions(NULL)->AddConstraint(_T("10초"), 10);
			GetEditOptions(NULL)->AddConstraint(_T("15초"), 15);
			GetEditOptions(NULL)->AddConstraint(_T("20초"), 20);
			GetEditOptions(NULL)->AddConstraint(_T("30초"), 30);
			GetEditOptions(NULL)->AddConstraint(_T("40초"), 40);
			GetEditOptions(NULL)->AddConstraint(_T("50초"), 50);
			GetEditOptions(NULL)->AddConstraint(_T("1분"), 60);
			GetEditOptions(NULL)->AddConstraint(_T("알수없음"), 9999);
			GetEditOptions(NULL)->m_bConstraintEdit = FALSE;
			GetEditOptions(NULL)->m_bAllowEdit = FALSE;		
			GetEditOptions(NULL)->AddComboButton();

			m_bDirtyFlag = FALSE;	
		}

		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			CXTPGridRecordItemConstraint* pConstraint = GetEditOptions(NULL)->FindConstraint(m_nValue);
			if(pConstraint == NULL)
			{
				long nValue = 9999;
				pConstraint = GetEditOptions(NULL)->FindConstraint(nValue);
			}

			ASSERT(pConstraint);
			return pConstraint->m_strConstraint;
		}

		virtual void OnConstraintChanged(XTP_REPORTRECORDITEM_ARGS* pItemArgs, CXTPGridRecordItemConstraint* pConstraint)
		{
			m_nValue = (long)pConstraint->m_dwData;
			m_bDirtyFlag = TRUE;
		}
		BOOL GetValue()
		{
			return m_nValue;
		}
	protected:
		long m_nValue;

	public:
		BOOL m_bDirtyFlag;
	};

public:
	CMyAllianceRecord::CMyAllianceRecord(long nShareCode1, CString strName, 
					CString strPhone, long nShareSec, 
					long nGiveCall, long nTakeCall, 
					COleDateTime dtTime);
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);


	long GetShareSec()
	{
		CShareSecRecordItem *pRecordItem = (CShareSecRecordItem*)GetItem(2);
		return pRecordItem->GetValue();
	}

	long GetDirtyFlag()
	{
		CShareSecRecordItem *pRecordItem = (CShareSecRecordItem*)GetItem(2);
		return pRecordItem->m_bDirtyFlag;
	}


public:
	long m_nShareCode1;




};


class CMyAllianceManagerDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CMyAllianceManagerDlg)

public:
	CMyAllianceManagerDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMyAllianceManagerDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MY_ALLIANCE_MANAGER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void RefreshList();
	afx_msg void OnBnClickedSaveBtn();


	CXTPGridControl m_wndReport;
};
