
#pragma once

#define MODIFY_MILEAGE 6


class CMyTextRecord : public CXTPGridRecordItemText
{
public:
	CMyTextRecord(CString strDummy):CXTPGridRecordItemText(strDummy)
	{
	}
public:
	ST_RIDER_STRUCT *pAllocRiderInfo = NULL;
};

class CXTPGridRecordItemCheck : public CXTPGridRecordItem
{
public:
	CXTPGridRecordItemCheck(BOOL bCheck)
	{
		this->HasCheckbox(TRUE);
		this->SetChecked(bCheck);
	}
};

class CNearRecord : public CXTPGridRecord
{
public:
	CNearRecord::CNearRecord(BOOL bCheck,long nTNo, int nState,int nCarType, int nRunType, int nWayType, CString strBranchName,
		CString strCName,CString strDelayTime,CString strStart, CString strDest,CString strEtc , COleDateTime dt1, 
		int nRankType, BOOL bNearRiderOrder, long m_nOrderCompany);
public:
	long m_nTNo;
	long m_nState;
	long m_nCarType;
	long m_nRunType;
	long m_nWayType;
	int m_nRankType;
	int m_nCompany;

	BOOL m_bNearRiderOrder;
	BOOL m_bCheck;

	virtual void GetItemMetrics (XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
	virtual COLORREF OnColorText(XTP_GRIDRECORDITEM_METRICS* pItemMetrics, int &nRow, int &nCol, int &nItemCol, int &nRankType);
	virtual COLORREF OnColorBack(XTP_GRIDRECORDITEM_METRICS* pItemMetrics, int &nRow, int &nCol, int &nItemCol, int &nRankType);
};


class CAfterReportRecord : public  CXTPGridRecord
{
public:
	CAfterReportRecord::CAfterReportRecord(long nGNo, CString sDate, long nCashCount, long nCashCharge, long nCreditCount, long nCreditCharge,
		long nOnlineCount, long nOnlineCharge, long nTransCount, long nTransCharge);

	CAfterReportRecord::CAfterReportRecord(long nGNo);
};

#include "XTPListCtrl2.h"

class CXTPGridCustomer : public CXTPListCtrlRecord2//public  CXTPGridRecord
{
public:
	CXTPGridCustomer::CXTPGridCustomer(BOOL bMain, ST_CUSTOMER_INFO *info);

public:
	ST_CUSTOMER_INFO *m_info;
};


class CGroupRecord : public  CXTPGridRecord
{
public:
	CGroupRecord::CGroupRecord(ST_CUSTOMER_GROUP_INFOMATION *st);
	void AddSearchData(ST_CUSTOMER_GROUP_INFOMATION *st);
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);

public:
	long m_nGNo;
	long m_nActiveLevel;
	long m_nCredit;

	BOOL m_bSelect;
	
	CString m_strSearchData;
};

class CGroupReportRecord : public  CXTPGridRecord
{
public:
	CGroupReportRecord::CGroupReportRecord();
	CGroupReportRecord::CGroupReportRecord(ST_CUSTOMER_GROUP_INFOMATION *st, BOOL bSumRecord = FALSE);
	CGroupReportRecord::CGroupReportRecord(GROUP_REPORT st, BOOL bSumRecord = FALSE);
	CGroupReportRecord::CGroupReportRecord(ST_GROUP_REPORT st);

	void AddSearchData(ST_CUSTOMER_GROUP_INFOMATION *st);
	virtual	void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);

public:
	long m_nGNo;
	long m_nReportTreeLevel;

	BOOL m_bSumRecord;
	BOOL m_bHasData;

	CString m_strSearchData;
	CString m_strSearchDateData;

	GROUP_REPORT m_stGroup;
};

class CSimpleGroupRecord : public  CXTPGridRecord
{
public:
	CSimpleGroupRecord::CSimpleGroupRecord(ST_CUSTOMER_GROUP_INFOMATION *st);
	void AddSearchData(ST_CUSTOMER_GROUP_INFOMATION *st);
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);

public:
	long m_nGNo;
	long m_nActiveLevel;
	long m_nCredit;

	BOOL m_bSelect;

	CString m_strSearchData;
};

class CCustomerGroupRecord : public CXTPGridRecord
{
public:
	CCustomerGroupRecord()
	{
		m_nGNo = 0;
		m_nActiveLevel = 0;
		m_nCredit = 0;
		m_strSearchData = "";
	}

	CCustomerGroupRecord::CCustomerGroupRecord(ST_CUSTOMER_GROUP_INFOMATION *st);
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
	void AddSearchData(ST_CUSTOMER_GROUP_INFOMATION *st);
public:
	long m_nGNo;
	long m_nActiveLevel;
	long m_nCredit;
	CString m_strSearchData;
};

class CGroupRecord24 : public  CXTPGridRecord
{
public:
	CGroupRecord24::CGroupRecord24(ST_CUSTOMER_GROUP_INFOMATION *st);
	void AddSearchData(ST_CUSTOMER_GROUP_INFOMATION *st);
	virtual void CGroupRecord24::GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);

public:
	long m_nGNo;
	long m_nActiveLevel;
	long m_nCredit;
	BOOL m_bSelect;

	CString m_strSearchData;
};


class CGroupReportRecord24 : public  CXTPGridRecord
{
public:
	CGroupReportRecord24::CGroupReportRecord24();
	CGroupReportRecord24::CGroupReportRecord24(ST_CUSTOMER_GROUP_INFOMATION *st, BOOL bSumRecord = FALSE);
	CGroupReportRecord24::CGroupReportRecord24(GROUP_REPORT st, BOOL bSumRecord = FALSE);
	CGroupReportRecord24::CGroupReportRecord24(ST_GROUP_REPORT st);
	void AddSearchData(ST_CUSTOMER_GROUP_INFOMATION *st);

	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
	
public:
	long m_nGNo;
	long m_nReportTreeLevel;
	BOOL m_bSumRecord;
	BOOL m_bHasData;
	CString m_strSearchData;
	CString m_strSearchDateData;
	GROUP_REPORT m_stGroup;
};

class CMileageRecord : public CXTPGridRecord
{
	class  CMileageNumber :public CXTPGridRecordItemNumber
	{
	public:
		CMileageNumber(long nValue) : CXTPGridRecordItemNumber(nValue) {}
		void MySetValue(long nValue) { SetValue(nValue);}
		void CMileageNumber::OnEditChanged(XTP_REPORTRECORDITEM_ARGS* pArg, LPCTSTR str)
		{
			if(atoi((CString)str) < 0)
			{
				AfxMessageBox("숫자가 아닙니다.",  MB_ICONINFORMATION);
				return;
			}

			if(GetValue() != atol(str) )
			{
				CMileageRecord *pRecord = ((CMileageRecord *)(pArg->pItem->GetRecord()));
				pRecord->m_bDirtyFlag = TRUE;

				SetValue(atol(str));
				SetCaption(str);
			}
		}
	};

	class  CMileageTypeNumber : public CXTPGridRecordItemNumber
	{
	public:
		CMileageTypeNumber(long nValue) : CXTPGridRecordItemNumber( nValue) {}
		CString GetCaption()
		{
			return GetValue() == 0 ? "일반" : "업소" ;
		}
	};

	class  CMileageTelText : public CXTPGridRecordItemText
	{
	public:
		CMileageTelText(CString szText) : CXTPGridRecordItemText(szText)
		{
		}
		CString CMileageTelText::GetCaption(CXTPGridColumn*)
		{
			return GetValue();
			//return LF->GetDashPhoneNumber(GetValue());
		}
	};

public:
	CMileageRecord::CMileageRecord();
	CMileageRecord::CMileageRecord(CString strCName, CString strTel1, CString strTel2,long nCustomerGroup, int nType, long nUseCount, long nMileage, long nCNo, CString strMileageType);

	BOOL m_bDirtyFlag;
	long m_nCNo,m_nAdvertCount;
	CString m_strData[13];
	COleDateTime m_dtLastSentAdvertSMS, m_dtRegister,m_dtLastSentSMS;
};

class CUnBillRecord : public  CXTPGridRecord
{
public:
	CUnBillRecord::CUnBillRecord(long nGNo);
	CUnBillRecord::CUnBillRecord(long nGNo, COleDateTime dtGenerate, long nID, long nAccount, long nBalance, CString strType,
		COleDateTime dtReportStart, COleDateTime dtReportEnd, COleDateTime dtBillCollEction, COleDateTime dtPayMent, COleDateTime dtInputDebit,
		CString sSendEmail,CString sWName,CString sEtc ,long nReceivableAmount, long nUnCollection,long nIndex,BOOL bCancel, BOOL bSUm);

	//CUnBillRecord::CUnBillRecord(long nGNo, COleDateTime dtGenerate, long nID, long nAccount, long nBalance, CString sType,
	//	COleDateTime dtReportStart, COleDateTime dtReportEnd, COleDateTime dtBillCollEction, BOOL bPressBill, BOOL bSUm);
public:
	long m_nGNo;
	long m_nID;
	long m_nIndex;
	long m_nUnBill;
	BOOL m_bPressBill;
	CString m_strDate;
	CString m_strEtc;
	CString m_strType;
	long m_nReceivableAmount;
	long m_nUnCollection;
	BOOL m_bCancel;

};

class CRiderRecord : public CXTPGridRecord
{
public:
	CRiderRecord::CRiderRecord(CString strDate, CString strWeather, CString strWorkTime, CString strChargeType, CString strCreditType, CString strAllCount, BOOL bAbsence);
public:
	CString m_strWorkTime;
	CString m_strChargeType;
	CString m_strCreditType;
	CString m_strAllCount;
};

class CUpdateBoardRecord : public CXTPGridRecord
{
public: 
	CUpdateBoardRecord(long nTNo, 
		COleDateTime dtGenerate,
		long nWNo,
		long nWCompany,
		long nParentID,
		CString strWName,
		CString strMessage,
		CString strLogiStaffName);

	long m_nTNo;
	long m_nWNo;
	long m_nWCompany;
	long m_nParentID;
	COleDateTime m_dt;

protected:
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
};

class CWantTransferRecord : public CXTPGridRecord
{
protected:
	class CXTPGridRecordItemCompanyNumber : public CXTPGridRecordItemNumber
	{
	public:
		CXTPGridRecordItemCompanyNumber(long nProcessRate) : CXTPGridRecordItemNumber(nProcessRate)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			return "";
			//return m_ci.GetBranchName((long)GetValue());
		}
	};

	class CXTPGridRecordItemStateNumber : public CXTPGridRecordItemNumber
	{
	public:
		CXTPGridRecordItemStateNumber(long nProcessRate) : CXTPGridRecordItemNumber(nProcessRate)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			if(GetValue() == 1)
				return "입금대기중";
			else if(GetValue() == 2)
				return "입금완료";
			else if(GetValue() == 4) //사용자거절
				return "거절";
			else
				return "일주일경과"; //3이 일주일이 경과하여 자동 취소 됨
		}
	};


	class CXTPGridRecordItemMyDate : public CXTPGridRecordItemDateTime
	{
	public:
		CXTPGridRecordItemMyDate(COleDateTime dtDateTime)
			: CXTPGridRecordItemDateTime(dtDateTime)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			COleDateTime dtDate = GetValue();

			COleDateTime dtFormat;
			dtFormat.SetDateTime(1999, 01, 01, 01, 01, 01);

			if(dtDate != dtFormat)
				return dtDate.Format("%m-%d %H:%M");
			else
				return "";			
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
			if((long)GetValue() != -1)
				return LF->GetMyNumberFormat((long)GetValue()) + "원";
			else
				return "";
		}
	};

public:
	CWantTransferRecord::CWantTransferRecord(long nID, long nToCompany, CString sMemo, long nState, COleDateTime dtRequest,
		long nRequestCharge, COleDateTime dtReceive, long nReceiveCharge, CString strReceiveMessage);
	void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);

	long m_nState;
};


class CAllianceRecord : public CXTPGridRecord
{
public:

	class CCountRecordItem : public CXTPGridRecordItemText
	{
	public:
		CCountRecordItem(CString strDummy) : CXTPGridRecordItemText(strDummy)
		{
		}

		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			CString strFormat;
			long nChildCount = ((CAllianceRecord*)GetRecord())->GetChilds()->GetCount();
			strFormat.Format("%d개",nChildCount);
			return strFormat;
		}

	};

	CAllianceRecord(long nAllianceID, CString strAllianceName);

	BOOL CheckAllianceID(long nAllianceID)
	{
		return (m_nAllianceID == nAllianceID);
	}

public:
	long m_nAllianceID;
	CString m_strAllianceName;
};




class CMyRecord : public CXTPGridRecord
{
protected:

	class CRcpRateRecordItem : public CXTPGridRecordItem
	{
	public:
		CRcpRateRecordItem(UINT nValue)
		{
			m_nValue = nValue;
			GetEditOptions(NULL)->AddConstraint(_T("23"), 23);
			GetEditOptions(NULL)->AddConstraint(_T("22"), 22);
			GetEditOptions(NULL)->AddConstraint(_T("21"), 21);
			GetEditOptions(NULL)->AddConstraint(_T("20"), 20);
			GetEditOptions(NULL)->AddConstraint(_T("19"), 19);
			GetEditOptions(NULL)->AddConstraint(_T("18"), 18);
			GetEditOptions(NULL)->AddConstraint(_T("17"), 17);
			GetEditOptions(NULL)->AddConstraint(_T("16"), 16);
			GetEditOptions(NULL)->AddConstraint(_T("15"), 15);
			GetEditOptions(NULL)->AddConstraint(_T("14"), 14);
			GetEditOptions(NULL)->AddConstraint(_T("13"), 13);
			GetEditOptions(NULL)->AddConstraint(_T("12"), 12);
			GetEditOptions(NULL)->AddConstraint(_T("11"), 11);
			GetEditOptions(NULL)->AddConstraint(_T("10"), 10);
			GetEditOptions(NULL)->AddConstraint(_T("9"), 9);
			GetEditOptions(NULL)->AddConstraint(_T("8"), 8);
			GetEditOptions(NULL)->AddConstraint(_T("7"), 7);
			GetEditOptions(NULL)->AddConstraint(_T("6"), 6);
			GetEditOptions(NULL)->AddConstraint(_T("5"), 5);


			GetEditOptions(NULL)->AddConstraint(_T("0"), 0);
			GetEditOptions(NULL)->AddConstraint(_T("미공유"), -1);
			GetEditOptions(NULL)->AddConstraint(_T("무정산"), 21);
			GetEditOptions(NULL)->m_bConstraintEdit = FALSE;
			GetEditOptions(NULL)->m_bAllowEdit = TRUE;
			GetEditOptions(NULL)->m_bExpandOnSelect = TRUE;
			GetEditOptions(NULL)->AddComboButton();

			m_bDirtyFlag = FALSE;	
		}

		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			CXTPGridRecordItemConstraint* pConstraint = GetEditOptions(NULL)->FindConstraint(m_nValue);
			if(pConstraint == NULL || ((CMyRecord*)GetRecord())->m_bNoShareA)
			{
				long nValue = -1;
				pConstraint = GetEditOptions(NULL)->FindConstraint(nValue);
			}

			ASSERT(pConstraint);
			return pConstraint->m_strConstraint;
		}

		virtual void OnConstraintChanged(XTP_REPORTRECORDITEM_ARGS* pItemArgs, CXTPGridRecordItemConstraint* pConstraint)
		{
			if(((CMyRecord*)GetRecord())->m_bIsAllianceHead)
				return;


			long nValue = (long)pConstraint->m_dwData;


			if(nValue == -1)
			{
				((CMyRecord*)GetRecord())->m_bNoShareA = TRUE;
			}
			else
			{
				((CMyRecord*)GetRecord())->m_bNoShareA = FALSE;
				if((m_ci.m_nAllianceID > 0 && ((CMyRecord*)GetRecord())->m_nAllianceID > 0))
				{
					//skip
				}
				else
				{
					m_nValue = nValue;
				}
			}

			CXTPGridRecordItem* pItemProcessRate = ((CMyRecord*)GetRecord())->GetItem(5);
			if(m_nValue == 0)
				((CProcessRateRecordItem*)pItemProcessRate)->SetValue(0);
			else
				((CProcessRateRecordItem*)pItemProcessRate)->SetValue(max(0, 20 - m_nValue));


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


	class CProcessRateRecordItem : public CXTPGridRecordItemNumber
	{
	public:
		CProcessRateRecordItem(long nProcessRate)
			: CXTPGridRecordItemNumber(nProcessRate, _T("%2.0f%%"))
		{
		}

		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			if (!m_strCaption.IsEmpty())
				return m_strCaption;

			CString strCaption;

			if(((CMyRecord*)GetRecord())->m_bNoShareA == TRUE)
				strCaption = "미공유";
			else if(m_dValue < 0)
				strCaption = "무정산";
			else if(m_dValue == 21)
				strCaption = "미공유";
			else if(m_dValue == 20)
				strCaption = "0";
			else
				strCaption.Format(m_strFormatString, m_dValue);

			return strCaption;
		}
	};

	class CRcpRateRecordItem2 : public CXTPGridRecordItemNumber
	{
	public:
		CRcpRateRecordItem2(long nRcpRate)
			: CXTPGridRecordItemNumber(nRcpRate, _T("%2.0f%%"))
		{
		}

		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			if (!m_strCaption.IsEmpty())
				return m_strCaption;

			CString strCaption;
			if(m_dValue == -1 || ((CMyRecord*)GetRecord())->m_bNoShareB == TRUE)
				strCaption = "미공유";
			else if(m_dValue == 21)
				strCaption = "무정산";
			else
				strCaption.Format(m_strFormatString, m_dValue);

			return strCaption;
		}
	};

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

	class CShareTimeRecordItem : public CXTPGridRecordItem
	{
	public:
		CShareTimeRecordItem(UINT nValue)
		{
			m_nValue = nValue;
			GetEditOptions(NULL)->AddConstraint(_T("미설정"), 0);
			GetEditOptions(NULL)->AddConstraint(_T("즉시"), 1);
			GetEditOptions(NULL)->AddConstraint(_T("5초"), 5);
			GetEditOptions(NULL)->AddConstraint(_T("10초"), 10);
			GetEditOptions(NULL)->AddConstraint(_T("15초"), 15);
			GetEditOptions(NULL)->AddConstraint(_T("20초"), 20);
			GetEditOptions(NULL)->AddConstraint(_T("25초"), 25);
			GetEditOptions(NULL)->AddConstraint(_T("30초"), 30);
			GetEditOptions(NULL)->AddConstraint(_T("35초"), 35);
			GetEditOptions(NULL)->AddConstraint(_T("40초"), 40);
			GetEditOptions(NULL)->AddConstraint(_T("45초"), 45);
			GetEditOptions(NULL)->AddConstraint(_T("50초"), 50);
			GetEditOptions(NULL)->AddConstraint(_T("1분"), 60);
			GetEditOptions(NULL)->AddConstraint(_T("1분10초"), 70);
			GetEditOptions(NULL)->AddConstraint(_T("1분20초"), 80);
			GetEditOptions(NULL)->AddConstraint(_T("1분30초"), 90);
			GetEditOptions(NULL)->AddConstraint(_T("2분"), 120);
			GetEditOptions(NULL)->AddConstraint(_T("2분30초"), 150);
			GetEditOptions(NULL)->AddConstraint(_T("3분"), 180);
			GetEditOptions(NULL)->AddConstraint(_T("4분"), 240);
			GetEditOptions(NULL)->AddConstraint(_T("5분"), 300);

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
			if((m_ci.m_nAllianceID > 0 && ((CMyRecord*)GetRecord())->m_nAllianceID > 0) ||
				((CMyRecord*)GetRecord())->m_bIsAllianceHead)
			{
				return;
			}

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

	class CShareTimeRecordItem2 : public CShareTimeRecordItem
	{
	public:
		CShareTimeRecordItem2(UINT nValue) : CShareTimeRecordItem(nValue)
		{
		}

		virtual void OnConstraintChanged(XTP_REPORTRECORDITEM_ARGS* pItemArgs, CXTPGridRecordItemConstraint* pConstraint)
		{
		}
	};

public:
	UINT	m_nShareReportTabIdx;
	int		m_nAllianceID;
	BOOL	m_bIsAllianceHead;
	BOOL	m_bNoShareA;
	BOOL	m_bNoShareB;

	long	m_nOriRcpRateA;
	long	m_nOriShareTimeA;
	long	 m_nTrafficPenalty;
	long	m_nCompany;
	long	m_nShareCode1;

	CString m_strAllianceName;
	CString m_strAllianceSymbol;
public:
	CMyRecord::CMyRecord(long nShareCode1, CString strName, CString strPhone, CString strOfficePhone, CString strChannel, 
		long nRcpRateA, long nRcpRateB, long nShareTimeA, long nShareTimeB, COleDateTime dtInsert, COleDateTime dtLastEdit, 
		CString strEditHistory, long nCompany,BOOL bIntro, int nAllianceID, CString strAllianceName, 
		CString strAllianceSymbol, BOOL bIsAllianceHead, BOOL bNoShareA, BOOL bNoShareB);

	CMyRecord::CMyRecord(COleDateTime dtGenerate,CString sState,long nDeposit,long nBalance,CString sEtc,long nTrafficPenalty);

	void	GetItemMetrics_1(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);

	BOOL GetDirtyFlag();
	BOOL GetShareTimeDirtyFlag();
	long GetShareTimeA();
	BOOL CheckAllianceID(long nAllianceID);
	long GetRcpRate();
};
