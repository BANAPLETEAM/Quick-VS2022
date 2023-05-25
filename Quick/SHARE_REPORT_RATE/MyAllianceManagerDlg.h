#pragma once


// CMyAllianceManagerDlg ��ȭ �����Դϴ�.


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
				strCaption = "������ֻ�";
			else if(m_dValue < 10)
				strCaption = "������ֻ�";
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
			GetEditOptions(NULL)->AddConstraint(_T("���"), 1);
			GetEditOptions(NULL)->AddConstraint(_T("5��"), 5);
			GetEditOptions(NULL)->AddConstraint(_T("10��"), 10);
			GetEditOptions(NULL)->AddConstraint(_T("15��"), 15);
			GetEditOptions(NULL)->AddConstraint(_T("20��"), 20);
			GetEditOptions(NULL)->AddConstraint(_T("30��"), 30);
			GetEditOptions(NULL)->AddConstraint(_T("40��"), 40);
			GetEditOptions(NULL)->AddConstraint(_T("50��"), 50);
			GetEditOptions(NULL)->AddConstraint(_T("1��"), 60);
			GetEditOptions(NULL)->AddConstraint(_T("�˼�����"), 9999);
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
	CMyAllianceManagerDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMyAllianceManagerDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MY_ALLIANCE_MANAGER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void RefreshList();
	afx_msg void OnBnClickedSaveBtn();


	CXTPGridControl m_wndReport;
};
