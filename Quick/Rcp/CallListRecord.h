#pragma once

#include "RcpPageCTIForm.h"

#define CALLRECORD()	((CCallListRecord*)GetRecord())

class CCallListRecord : public CXTPGridRecord
{
protected:

	class CCallListStartDateTimeItem : public CXTPGridRecordItemDateTime
	{
	public:
		CCallListStartDateTimeItem(COleDateTime dtDateTime)
			: CXTPGridRecordItemDateTime(dtDateTime)
		{
			m_strFormatString = _T("%H:%M:%S");
		}
		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			return CALLRECORD()->m_dtFirstTime.Format(m_strFormatString);
		}
	};

	class CCallListPhoneItem : public CXTPGridRecordItemText
	{
	public:
		CCallListPhoneItem(CString strDummy):CXTPGridRecordItemText(strDummy)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			if(CALLRECORD()->m_bShowLastPhoneNumber)
				return GetDashPhoneNumber(CALLRECORD()->m_strPhone);
			else
				return CALLRECORD()->m_strPhone.Left(CALLRECORD()->m_strPhone.GetLength() - 2) + "**";
		}
	};


	class CCallListStateItem : public CXTPGridRecordItem
	{
	public:

		CCallListStateItem(UINT nState)
		{
			GetEditOptions(NULL)->AddConstraint(_T("통화"), 0);
			GetEditOptions(NULL)->AddConstraint(_T("끊음"), 1);
			GetEditOptions(NULL)->AddConstraint(_T("링"), 2);
			GetEditOptions(NULL)->AddConstraint(_T("콜벨"), 3);
			GetEditOptions(NULL)->AddConstraint(_T("착신"), 4);
			GetEditOptions(NULL)->AddConstraint(_T("걸기"), 5);
			GetEditOptions(NULL)->AddConstraint(_T("ARS"), 6);
			GetEditOptions(NULL)->AddConstraint(_T("ⓒ통화"), 100);
			GetEditOptions(NULL)->AddConstraint(_T("ⓒ끊음"), 101);
			GetEditOptions(NULL)->m_bConstraintEdit = FALSE;
			GetEditOptions(NULL)->m_bAllowEdit = FALSE;		
		}

		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			long nConstraint = CALLRECORD()->m_nState;
			if(nConstraint <= 1 && CALLRECORD()->m_bOutBoundCall)
				nConstraint = nConstraint + 100;

			CXTPGridRecordItemConstraint* pConstraint = 
				GetEditOptions(NULL)->FindConstraint(nConstraint);
			if(!pConstraint)
				return "N/A";
			else 
				return pConstraint->m_strConstraint;
		}

	};

	class CCallListEndDateTimeItem : public CXTPGridRecordItemDateTime
	{
	public:
		CCallListEndDateTimeItem(COleDateTime dtDateTime)
			: CXTPGridRecordItemDateTime(dtDateTime)
		{
			m_strFormatString = _T("%H:%M:%S");
		}
		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			return CALLRECORD()->m_dtLastTime.Format(m_strFormatString);
		}
	};

	class COperatorRecordItem : public CXTPGridRecordItemText
	{
	public:
		COperatorRecordItem(CString strDummy):CXTPGridRecordItemText(strDummy)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			return CALLRECORD()->m_strOperator.GetLength() > 1 ? CALLRECORD()->m_strOperator : 
			CALLRECORD()->m_strKeyPhoneID;
		}
	};

	class CCustomerNameRecordItem : public CXTPGridRecordItemText
	{
	public:
		CCustomerNameRecordItem(CString strDummy):CXTPGridRecordItemText(strDummy)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			//TRACE("%s(고객)\r\n", ((CCallListRecord*)GetRecord())->m_strCustomerName);
			//g_bana_log->Print("%s(고객)", ((CCallListRecord*)GetRecord())->m_strCustomerName);
			return CALLRECORD()->m_strCustomerName; 
		}
	};

	class CCustomerIDRecordItem : public CXTPGridRecordItemText
	{
	public:
		CCustomerIDRecordItem(CString strDummy):CXTPGridRecordItemText(strDummy)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			return CALLRECORD()->m_strCustomerID;
		}
	};


	class CCustomerManagerRecordItem : public CXTPGridRecordItemText
	{
	public:
		CCustomerManagerRecordItem(CString strDummy):CXTPGridRecordItemText(strDummy)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			return CALLRECORD()->m_strCustomerManager;
		}
	};

	class CCustomerDongRecordItem : public CXTPGridRecordItemText
	{
	public:
		CCustomerDongRecordItem(CString strDummy):CXTPGridRecordItemText(strDummy)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			return CALLRECORD()->m_strCustomerDong;
		}
	};

	class CCustomerInfoRecordItem : public CXTPGridRecordItemText
	{
	public:
		CCustomerInfoRecordItem(CString strDummy):CXTPGridRecordItemText(strDummy)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			return CALLRECORD()->m_strCustomerInfo;
		}
	};

	class CCustomerDescRecordItem : public CXTPGridRecordItemText
	{
	public:
		CCustomerDescRecordItem(CString strDummy):CXTPGridRecordItemText(strDummy)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			return CALLRECORD()->m_strCustomerDesc;
		}
	};

	class CLastAnswerRecordItem : public CXTPGridRecordItemText
	{
	public:
		CLastAnswerRecordItem(CString strDummy):CXTPGridRecordItemText(strDummy)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			return CALLRECORD()->m_strLastAnswer;
		}
	};



	class CBranchRecordItem : public CXTPGridRecordItemText
	{
	public:
		CBranchRecordItem(CString strDummy):CXTPGridRecordItemText(strDummy)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			if(CALLRECORD()->m_strBranch.GetLength() > 0)
				return CALLRECORD()->m_strBranch;
				//return CALLRECORD()->m_strBranch + "(" + CALLRECORD()->m_strDID + ")";
			else
				return "-";
		}
	};

	class CEtcRecordItem : public CXTPGridRecordItemText
	{
	public:
		CEtcRecordItem(CString strDummy):CXTPGridRecordItemText(strDummy)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			return CALLRECORD()->m_strEtc;
		}
	};


	class CRingTimeRecordItem : public CXTPGridRecordItemText
	{
	public:
		CRingTimeRecordItem(CString strDummy):CXTPGridRecordItemText(strDummy)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			if(!CALLRECORD()->m_bRing)
				return "-";

			if(CALLRECORD()->m_bAnswer)
			{
				return CCallListRecord::GetMyElapsedTimeFormat(
					CALLRECORD()->m_dtFirstTime, CALLRECORD()->m_dtAnswer);
			}
			else if(CALLRECORD()->m_nState == PH_RING ||
					CALLRECORD()->m_nState == PH_ARS_ANSWER)
			{
				//링울리고 1분이상 지나면, HANG_UP 신호가 빠진것으로 간주함
				CString strElapsed = CCallListRecord::GetMyElapsedTimeFormat(
					CALLRECORD()->m_dtFirstTime, COleDateTime::GetCurrentTime());

				if(strElapsed.Find("분") >= 0)
				{
					CALLRECORD()->m_nState = PH_HANG_UP;
					CALLRECORD()->m_dtLastTime = CALLRECORD()->m_dtFirstTime + COleDateTimeSpan(0, 0, 1, 0);
				}

				return strElapsed;
			}
			else
			{
				return CCallListRecord::GetMyElapsedTimeFormat(
					CALLRECORD()->m_dtFirstTime, CALLRECORD()->m_dtLastTime);
			}
		}
	};

	class CAnswerTimeRecordItem : public CXTPGridRecordItemText
	{
	public:
		CAnswerTimeRecordItem(CString strDummy):CXTPGridRecordItemText(strDummy)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			if(CALLRECORD()->m_nState == PH_HANG_UP && CALLRECORD()->m_bRing)
			{
				COleDateTimeSpan span = CALLRECORD()->m_dtLastTime - CALLRECORD()->m_dtAnswer;

				if(!CALLRECORD()->m_bAnswer || 
					CALLRECORD()->m_bAnswer && (!CALLRECORD()->m_bIPPBX && span.GetTotalSeconds() <= 5))
				{
					CALLRECORD()->m_bMissing = TRUE;
					return "못받음";
				}
			}

			if(!CALLRECORD()->m_bAnswer && !CALLRECORD()->m_bOutBoundCall)
			{
				return "-";
			}
			else if(CALLRECORD()->m_nState == PH_ANSWER)
			{
				COleDateTimeSpan span = COleDateTime::GetCurrentTime() - CALLRECORD()->m_dtAnswer;
				int nSec = abs((int)span.GetTotalSeconds());
				if(nSec > 3600)
				{
					CALLRECORD()->m_nState = PH_HANG_UP;
					CALLRECORD()->m_dtLastTime = CALLRECORD()->m_dtAnswer + COleDateTimeSpan(0, 1, 0, 0);
				}

				return CCallListRecord::GetMyElapsedTimeFormat(
					CALLRECORD()->m_dtAnswer, COleDateTime::GetCurrentTime());
			}
			else if(CALLRECORD()->m_nState == PH_OUT_BOUND_CALL)
			{
				COleDateTimeSpan span = COleDateTime::GetCurrentTime() - CALLRECORD()->m_dtFirstTime;
				int nSec = abs((int)span.GetTotalSeconds());
				if(nSec > 3600)
				{
					CALLRECORD()->m_nState = PH_HANG_UP;
					CALLRECORD()->m_dtLastTime = CALLRECORD()->m_dtFirstTime + COleDateTimeSpan(0, 1, 0, 0);
				}

				return CCallListRecord::GetMyElapsedTimeFormat(
					CALLRECORD()->m_dtFirstTime, COleDateTime::GetCurrentTime());
			}
			else if(CALLRECORD()->m_bOutBoundCall)
			{
				return CCallListRecord::GetMyElapsedTimeFormat(
				CALLRECORD()->m_dtFirstTime, CALLRECORD()->m_dtLastTime);
			}
			else
			{
				return CCallListRecord::GetMyElapsedTimeFormat(
				CALLRECORD()->m_dtAnswer, CALLRECORD()->m_dtLastTime);
			}
		}
	};

public:
	static CString GetMyElapsedTimeFormat(COleDateTime dtStart, COleDateTime dtEnd, BOOL bRemoveSec = FALSE)
	{
		COleDateTimeSpan span = dtEnd - dtStart;
		int nSec = (int)span.GetTotalSeconds();
		int nAbsSec = abs(nSec);
		CString strTime;

		if(bRemoveSec)
		{
			if(nAbsSec <= 30)
				strTime = "";
			else if(nAbsSec < 60)
				strTime.Format("%d초", nSec);
			else
				strTime.Format("%d분", nSec / 60);
		}
		else
		{
			if(nAbsSec <= 1)
				strTime = "-";
			else if(nAbsSec < 60)
				strTime.Format("%d초", nSec);
			else if(nAbsSec < 600)
				strTime.Format("%d분%d", nSec / 60, nAbsSec % 60);
			else 
				strTime.Format("%d분", nSec / 60);
		}

		return strTime;
	}

	static CString GetMyElapsedTimeFormatEx(COleDateTime dtStart, COleDateTime dtEnd, BOOL bRemoveSec = FALSE)
	{
		COleDateTimeSpan span = dtEnd - dtStart;
		int nSec = (int)span.GetTotalSeconds();
		int nAbsSec = abs(nSec);
		CString strTime;

		if(bRemoveSec)
		{
			if(nAbsSec <= 30)
				strTime = "";
			else if(nAbsSec < 60)
				strTime.Format("%d초", nAbsSec);
			else if(nAbsSec < 3600)
				strTime.Format("%d' %d\"", nAbsSec / 60, nAbsSec % 60);
			else
				strTime.Format("%dH", nAbsSec / 3600);
		}
		else
		{
			if(nAbsSec <= 1)
				strTime = "-";
			else if(nAbsSec < 60)
				strTime.Format("%d초", nAbsSec);
			else if(nAbsSec < 3600)
				strTime.Format("%d' %d\"", nAbsSec / 60, nAbsSec % 60);
			else 
				strTime.Format("%dH", nAbsSec / 3600);
		}

		return strTime;
	}

	static int GetMyElapsedSecond(COleDateTime dtStart, COleDateTime dtEnd)
	{
		COleDateTimeSpan span = dtEnd - dtStart;
		int nSec = (int)span.GetTotalSeconds();
		return abs(nSec);
	}

	CCallListRecord(COleDateTime dtCur)
	{
		m_dtFirstTime = dtCur;
		m_dtLastTime = m_dtFirstTime;
		m_dtAnswer = m_dtFirstTime;
		m_nState = PH_HANG_UP;
		m_bAnswer = FALSE;
		m_bRing = FALSE;
		m_bMissing = FALSE;
		m_nCompany = 0;
		m_bOutBoundCall = FALSE;
		m_bIPPBX = FALSE;

		//CRcpPageCTIForm에서 CCustomerRecordItem의 컬럼번호를 참조하기 때문에
		//컬럼 위치가 변경되면, 헤더파일의 #define COL_CUSTOMER_INFO 수정해줘야함

		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CCallListStartDateTimeItem(m_dtFirstTime));
		AddItem(new CCallListPhoneItem(""));
		AddItem(new CCallListStateItem(0));
		AddItem(new COperatorRecordItem(""));
		AddItem(new CCustomerNameRecordItem(""));
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CCustomerManagerRecordItem(""));
		AddItem(new CCustomerDongRecordItem(""));

		AddItem(new CBranchRecordItem(""));
		AddItem(new CCallListEndDateTimeItem(m_dtLastTime));
		AddItem(new CCustomerIDRecordItem(""));
		AddItem(new CLastAnswerRecordItem(""));
		AddItem(new CRingTimeRecordItem(""));
		AddItem(new CAnswerTimeRecordItem(""));
		AddItem(new CEtcRecordItem(""));
		AddItem(new CXTPGridRecordItemText("재생"));
		AddItem(new CXTPGridRecordItemText("다운"));
	}
 
	virtual void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
	{
		if(pDrawArgs->pColumn == NULL ||
			pDrawArgs->pRow == NULL)
			return; 

		if(pDrawArgs->pColumn->GetItemIndex() == ZERO)
			pItemMetrics->strText.Format("%d", (pDrawArgs->pControl->GetRecords()->GetCount() - pDrawArgs->pRow->GetIndex()));

		switch(m_nState)
		{
		case PH_ANSWER:
			pItemMetrics->clrBackground = RGB(220, 255, 220);
			pItemMetrics->clrForeground= RGB(0, 0, 0);
			break;
		
		case PH_OUT_BOUND_CALL:
			pItemMetrics->clrBackground = RGB(200, 200, 255);
			pItemMetrics->clrForeground= RGB(0, 0, 0);
			break;


		case PH_RING:
		case PH_ARS_ANSWER:
			pItemMetrics->clrBackground = RGB(255, 255, 200);
			pItemMetrics->clrForeground= RGB(0, 0, 0);
			break;

		default:
			if(m_bMissing)
			{
				pItemMetrics->clrBackground = RGB(255, 220, 220);
				pItemMetrics->clrForeground= RGB(0, 0, 0);
			}
			else
			{
				pItemMetrics->clrBackground = RGB(255, 255, 255);
				pItemMetrics->clrForeground= RGB(0, 0, 0);
			}
			break;
		}
	}

public:
	CString m_strDID;
	CString m_strKeyPhoneID;
	COleDateTime m_dtFirstTime;
	COleDateTime m_dtLastTime;
	CString m_strPhone;
	CString m_strBranch;
	int m_nState;
	CString m_strOperator;
	CString m_strCustomerName;			
	CString m_strCustomerID;
	CString m_strCustomerDepart;
	CString m_strCustomerManager;
	CString m_strCustomerInfo;
	CString m_strCustomerDong;
	CString m_strCustomerDesc;
	COleDateTime m_dtAnswer;
	BOOL m_bAnswer;
	BOOL m_bOutBoundCall;
	BOOL m_bRing;
	BOOL m_bMissing;
	BOOL m_bShowLastPhoneNumber;
	long m_nCompany;
	CString m_strCallingLine;
	CString m_strCompanyPhone;
	CString m_strEtc;
	CString m_strLastAnswer;
	BOOL m_bIPPBX;
};