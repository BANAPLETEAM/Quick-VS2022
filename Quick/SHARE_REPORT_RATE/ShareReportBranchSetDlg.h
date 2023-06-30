#pragma once


// CShareReportBranchSetDlg 대화 상자입니다.


class CShareReportBranchRecord : public CXTPGridRecord
{
protected:
	class CCallUseRecordItem : public CXTPGridRecordItem
	{
	public:
		CCallUseRecordItem(UINT nValue)
		{ 
			m_nValue = nValue;
			GetEditOptions(NULL)->AddConstraint(_T("X"), 0);
			GetEditOptions(NULL)->AddConstraint(_T("O"), 1);
			GetEditOptions(NULL)->m_bConstraintEdit = FALSE;
			GetEditOptions(NULL)->m_bAllowEdit = TRUE;
			GetEditOptions(NULL)->m_bExpandOnSelect = TRUE;
			GetEditOptions(NULL)->AddComboButton();

			m_bDirtyFlag = FALSE;	
		}

		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			CXTPGridRecordItemConstraint* pConstraint = GetEditOptions(NULL)->FindConstraint(m_nValue);
			if(pConstraint == NULL)
			{
				long nValue = 0;
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
	 
	class CRiderVRBalancePushTypeRecordItem : public CXTPGridRecordItem
	{
	public:
		CRiderVRBalancePushTypeRecordItem(UINT nValue)
		{
			m_nValue = nValue;
			GetEditOptions(NULL)->AddConstraint(_T("지사에충전"), 0);
			GetEditOptions(NULL)->AddConstraint(_T("본사에충전"), 1);
			GetEditOptions(NULL)->m_bConstraintEdit = FALSE;
			GetEditOptions(NULL)->m_bAllowEdit = TRUE;
			GetEditOptions(NULL)->m_bExpandOnSelect = TRUE;
			GetEditOptions(NULL)->AddComboButton();

			m_bDirtyFlag = FALSE;	
		}

		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			CXTPGridRecordItemConstraint* pConstraint = GetEditOptions(NULL)->FindConstraint(m_nValue);
			if(pConstraint == NULL)
			{
				long nValue = 0;
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

	class CCallTypeRecordItem : public CXTPGridRecordItem
	{
	public:
		CCallTypeRecordItem(UINT nValue)
		{
			m_nValue = nValue;
			GetEditOptions(NULL)->AddConstraint(_T("콜접수"), 0);
			GetEditOptions(NULL)->AddConstraint(_T("기사수행"), 1);
			GetEditOptions(NULL)->AddConstraint(_T("콜접수+기사수행"), 2);
			GetEditOptions(NULL)->m_bConstraintEdit = FALSE;
			GetEditOptions(NULL)->m_bAllowEdit = TRUE;
			GetEditOptions(NULL)->m_bExpandOnSelect = TRUE;
			GetEditOptions(NULL)->AddComboButton();

			m_bDirtyFlag = FALSE;	
		}

		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			CXTPGridRecordItemConstraint* pConstraint = GetEditOptions(NULL)->FindConstraint(m_nValue);
			if(pConstraint == NULL)
			{
				long nValue = 0;
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

	class CCallChargeRecordItem : public CXTPGridRecordItem
	{
	public: 
		CCallChargeRecordItem(UINT nValue)
		{
			m_nValue = nValue;
			GetEditOptions(NULL)->AddConstraint(_T("무정산"), 0);
			GetEditOptions(NULL)->AddConstraint(_T("5%지급"), 5);
			GetEditOptions(NULL)->AddConstraint(_T("6%지급"), 6);
			GetEditOptions(NULL)->AddConstraint(_T("7%지급"), 7);
			GetEditOptions(NULL)->AddConstraint(_T("8%지급"), 8);
			GetEditOptions(NULL)->AddConstraint(_T("9%지급"), 9);
			GetEditOptions(NULL)->AddConstraint(_T("10%지급"), 10);
			GetEditOptions(NULL)->AddConstraint(_T("11%지급"), 11);
			GetEditOptions(NULL)->AddConstraint(_T("12%지급"), 12);
			GetEditOptions(NULL)->AddConstraint(_T("13%지급"), 13);
			GetEditOptions(NULL)->AddConstraint(_T("14%지급"), 14);
			GetEditOptions(NULL)->AddConstraint(_T("15%지급"), 15);
			GetEditOptions(NULL)->AddConstraint(_T("16%지급"), 16);
			GetEditOptions(NULL)->AddConstraint(_T("17%지급"), 17);
			GetEditOptions(NULL)->AddConstraint(_T("18%지급"), 18);
			GetEditOptions(NULL)->AddConstraint(_T("19%지급"), 19);
			GetEditOptions(NULL)->AddConstraint(_T("20%지급"), 20);
			GetEditOptions(NULL)->AddConstraint(_T("21%지급"), 21);
			GetEditOptions(NULL)->AddConstraint(_T("22%지급"), 22);
			GetEditOptions(NULL)->AddConstraint(_T("23%지급"), 23);
			GetEditOptions(NULL)->AddConstraint(_T("24%지급"), 24);
			GetEditOptions(NULL)->AddConstraint(_T("25%지급"), 25);
			GetEditOptions(NULL)->AddConstraint(_T("콜당100원"), 100);
			GetEditOptions(NULL)->AddConstraint(_T("콜당200원"), 200);
			GetEditOptions(NULL)->AddConstraint(_T("콜당300원"), 300);
			GetEditOptions(NULL)->AddConstraint(_T("콜당400원"), 400);
			GetEditOptions(NULL)->AddConstraint(_T("콜당500원"), 500);
			GetEditOptions(NULL)->AddConstraint(_T("콜당600원"), 600);
			GetEditOptions(NULL)->AddConstraint(_T("콜당700원"), 700);
			GetEditOptions(NULL)->AddConstraint(_T("콜당800원"), 800);
			GetEditOptions(NULL)->AddConstraint(_T("콜당900원"), 900);
			GetEditOptions(NULL)->AddConstraint(_T("콜당1000원"), 1000);
			GetEditOptions(NULL)->AddConstraint(_T("콜당1100원"), 1100);
			GetEditOptions(NULL)->AddConstraint(_T("콜당1200원"), 1200);
			GetEditOptions(NULL)->AddConstraint(_T("콜당1300원"), 1300);
			GetEditOptions(NULL)->AddConstraint(_T("콜당1400원"), 1400);
			GetEditOptions(NULL)->AddConstraint(_T("콜당1500원"), 1500);
			GetEditOptions(NULL)->AddConstraint(_T("콜당100원제외"), -100);
			GetEditOptions(NULL)->AddConstraint(_T("콜당200원제외"), -200);
			GetEditOptions(NULL)->AddConstraint(_T("콜당300원제외"), -300);
			GetEditOptions(NULL)->AddConstraint(_T("콜당400원제외"), -400);
			GetEditOptions(NULL)->AddConstraint(_T("콜당500원제외"), -500);
			GetEditOptions(NULL)->AddConstraint(_T("콜당600원제외"), -600);
			GetEditOptions(NULL)->AddConstraint(_T("콜당700원제외"), -700);
			GetEditOptions(NULL)->AddConstraint(_T("콜당800원제외"), -800);
			GetEditOptions(NULL)->AddConstraint(_T("콜당900원제외"), -900);
			GetEditOptions(NULL)->AddConstraint(_T("콜당1000원제외"), -1000);
			GetEditOptions(NULL)->AddConstraint(_T("콜당1100원제외"), -1100);
			GetEditOptions(NULL)->AddConstraint(_T("콜당1200원제외"), -1200);
			GetEditOptions(NULL)->AddConstraint(_T("콜당1300원제외"), -1300);
			GetEditOptions(NULL)->AddConstraint(_T("콜당1400원제외"), -1400);
			GetEditOptions(NULL)->AddConstraint(_T("콜당1500원제외"), -1500);
			GetEditOptions(NULL)->AddConstraint(_T("전액모두지급"), 9999);
			GetEditOptions(NULL)->m_bConstraintEdit = FALSE;
			GetEditOptions(NULL)->m_bAllowEdit = TRUE;
			GetEditOptions(NULL)->m_bExpandOnSelect = TRUE;
			GetEditOptions(NULL)->AddComboButton();

			m_bDirtyFlag = FALSE;	
		}

		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			CXTPGridRecordItemConstraint* pConstraint = GetEditOptions(NULL)->FindConstraint(m_nValue);
			if(pConstraint == NULL)
			{
				long nValue = 0;
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
	CShareReportBranchRecord::CShareReportBranchRecord(long nCompany, CString strBranchName, CString strPhone, BOOL bUseBranchShareReport, long nType,
		long nAutoCharge, long nBigAuto, long nDamaCharge, long nRaboCharge, long nBanCharge, long nTruckCharge, long nSubwayCharge, long nRiderCallCharge,
		long nBalance, int nAccountDue, CString strInAccounts, CString strOutAccounts,  CString strReportHistory, BOOL bRiderVRDepositToMain, CString strMID);

	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);

	long GetCallUse()
	{
		CCallTypeRecordItem *pRecordItem = (CCallTypeRecordItem*)GetItem(2);
		return pRecordItem->GetValue();
	}

	long GetCallChargeType()
	{
		CCallTypeRecordItem *pRecordItem = (CCallTypeRecordItem*)GetItem(3);
		return pRecordItem->GetValue();
	}

	long GetCallChargeAuto()
	{
		CCallChargeRecordItem *pRecordItem = (CCallChargeRecordItem*)GetItem(4);
		return pRecordItem->GetValue();
	}

	long GetCallChargeBigAuto()
	{
		CCallChargeRecordItem *pRecordItem = (CCallChargeRecordItem*)GetItem(5);
		return pRecordItem->GetValue();
	}

	long GetCallChargeDama()
	{
		CCallChargeRecordItem *pRecordItem = (CCallChargeRecordItem*)GetItem(6);
		return pRecordItem->GetValue();
	}

	long GetCallChargeRabo()
	{
		CCallChargeRecordItem *pRecordItem = (CCallChargeRecordItem*)GetItem(7);
		return pRecordItem->GetValue();
	}

	long GetCallChargeBan()
	{
		CCallChargeRecordItem *pRecordItem = (CCallChargeRecordItem*)GetItem(8);
		return pRecordItem->GetValue();
	}

	long GetCallChargeTruck()
	{
		CCallChargeRecordItem *pRecordItem = (CCallChargeRecordItem*)GetItem(9);
		return pRecordItem->GetValue();
	}

	long GetCallChargeSubway()
	{
		CCallChargeRecordItem *pRecordItem = (CCallChargeRecordItem*)GetItem(10);
		return pRecordItem->GetValue();
	}

	long GetCallChargeRiderCall()
	{
		CCallChargeRecordItem *pRecordItem = (CCallChargeRecordItem*)GetItem(11);
		return pRecordItem->GetValue();
	}

	long GetRiderVRAccountPushType()
	{
		CRiderVRBalancePushTypeRecordItem *pRecordItem = (CRiderVRBalancePushTypeRecordItem*)GetItem(16);
		return pRecordItem->GetValue();
	}

	CString GetVRAccount()
	{
		//CRiderVRBalancePushTypeRecordItem *pRecordItem = (CRiderVRBalancePushTypeRecordItem*)GetItem(12);
		//return pRecordItem->GetCaption();
		return m_strInAccounts;
	}

	long GetDirtyFlag()
	{
		CCallUseRecordItem *pRecordItem2 = (CCallUseRecordItem*)GetItem(2);
		CCallTypeRecordItem *pRecordItem3 = (CCallTypeRecordItem*)GetItem(3);
		CCallChargeRecordItem *pRecordItem4 = (CCallChargeRecordItem*)GetItem(4);
		CCallChargeRecordItem *pRecordItem5 = (CCallChargeRecordItem*)GetItem(5);
		CCallChargeRecordItem *pRecordItem6 = (CCallChargeRecordItem*)GetItem(6);
		CCallChargeRecordItem *pRecordItem7 = (CCallChargeRecordItem*)GetItem(7);
		CCallChargeRecordItem *pRecordItem8 = (CCallChargeRecordItem*)GetItem(8);
		CCallChargeRecordItem *pRecordItem9 = (CCallChargeRecordItem*)GetItem(9);
		CCallChargeRecordItem *pRecordItem10 = (CCallChargeRecordItem*)GetItem(10);
		CCallChargeRecordItem *pRecordItem11 = (CCallChargeRecordItem*)GetItem(11);
		CCallChargeRecordItem *pRecordItem16 = (CCallChargeRecordItem*)GetItem(16);

		return pRecordItem2->m_bDirtyFlag || pRecordItem3->m_bDirtyFlag || pRecordItem4->m_bDirtyFlag || 
			pRecordItem5->m_bDirtyFlag || pRecordItem6->m_bDirtyFlag || pRecordItem7->m_bDirtyFlag ||
			pRecordItem8->m_bDirtyFlag || pRecordItem9->m_bDirtyFlag || pRecordItem10->m_bDirtyFlag || 
			pRecordItem11->m_bDirtyFlag || pRecordItem16->m_bDirtyFlag;
	}

public:
	long m_nCompany;
	CString m_strInAccounts;
};


class CShareReportBranchSetDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CShareReportBranchSetDlg)

public:
	CShareReportBranchSetDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CShareReportBranchSetDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_SHARE_REPORT_BRANCH_SET_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedSaveBtn();
	afx_msg void OnBnClickedDrawingBtn();
	afx_msg void OnBnClickedIssueBtn();
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedRefreshBtn();

public:
	afx_msg void OnCardInfoDelete();
	afx_msg void OnCardInfoInsert(UINT nFlag);
	void RefreshList();
	void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);

	long m_nCompanyArry[100];
	CXTPGridControl m_wndReport;
	CEdit m_edtAccount;
	CButton m_btnDrawing;
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
};
