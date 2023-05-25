// MessageRecord.h: interface for the CMessageRecord class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGERECORD_H__AFFF918D_1624_41E5_8902_81B1F0C749BA__INCLUDED_)
#define AFX_MESSAGERECORD_H__AFFF918D_1624_41E5_8902_81B1F0C749BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


enum {
	MSG_STATUS_NORMAL = 0,
	MSG_STATUS_IDLE = 1,
	MSG_STATUS_PROTECTED = 2
};


enum {
	COL_BRANCH = 0,
	COL_MNO,
	COL_NAME_MSG,
	COL_STATUS
};


//////////////////////////////////////////////////////////////////////////
// This class is your main custom Record class which you'll manipulate with.
// It contains any kind of specific methods like different types of constructors,
// any additional custom data as class members, any data manipulation methods.
class CMessageRecord : public CXTPGridRecord
{
public:
	
	class CMessageRecordItemDateTime : public CXTPGridRecordItemDateTime
	{
	public:
		CMessageRecordItemDateTime(COleDateTime dtDateTime)
			: CXTPGridRecordItemDateTime(dtDateTime)
		{
			m_strFormatString = _T("%H:%M");
		}

		CString GetCaption(CXTPGridColumn* pColumn)
		{
			if(COleDateTime::GetCurrentTime() - COleDateTimeSpan(2, 0, 0, 0) < GetValue())
				return CXTPGridRecordItemDateTime::GetCaption(pColumn);
			else
				return "-";
		}
	};


	class CStatusRecordItem : public CXTPGridRecordItem
	{
	public:
		CStatusRecordItem(int nStatus)
		{
			m_nStatus = nStatus;
		}

		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			switch(m_nStatus)
			{
			case MSG_STATUS_IDLE:
				return "비움";
			case MSG_STATUS_PROTECTED:
				return "오프";
			default:
				return "";
			}
		}

		void SetStatus(int nStatus)
		{
			switch(nStatus)
			{
			case MSG_STATUS_IDLE:
				((CMessageRecord*)GetRecord())->GetItem(0)->SetIconIndex(2);
				break;
			case MSG_STATUS_PROTECTED:
				((CMessageRecord*)GetRecord())->GetItem(0)->SetIconIndex(3);
				break;
			default:
				((CMessageRecord*)GetRecord())->GetItem(0)->SetIconIndex(0);
				break;
			}

			m_nStatus = nStatus;
		}

	protected:
		int m_nStatus;
	};



public:


	// Construct record object from detailed values on each field
	CMessageRecord(long nShareCode1, long nCompany, long nMNo, 
		CString strCompany, CString strBranch, CString strName, 
		COleDateTime dtTime, BOOL bIdle, int nClientType);

	// Clean up internal objects
	virtual ~CMessageRecord();

	// Overridden callback method, where we can customize any drawing item metrics.
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);

	BOOL CheckUser(long nCompany, long nMNo, long nClientType = 0)
	{
		return (m_nCompany == nCompany) && (m_nMNo == nMNo) && (m_nClientType == nClientType);
	}

	void ClearExistFlag() { m_bExistFlag = FALSE;}
	void SetExistFlag() { m_bExistFlag = TRUE;}
	BOOL GetExistFlag() { return m_bExistFlag;} 

	void SetStatus(long nStatus)
	{ 
		((CStatusRecordItem*)GetItem(COL_STATUS))->SetStatus(nStatus);
		m_nStatus = nStatus;
	}

	long GetStatus()
	{ return m_nStatus; }


public:
	long m_nShareCode1;
	long m_nCompany;
	long m_nMNo;
	long m_nClientType;
	CString m_strCompanyName;
	CString m_strBranchName;
	CString m_strName;
	int m_nStatus;
	BOOL m_bExistFlag;

};


class CMessageTitleRecord : public CXTPGridRecord
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
			long nChildCount = ((CMessageTitleRecord*)GetRecord())->GetChilds()->GetCount();
			strFormat.Format("%d명",nChildCount);
			return strFormat;
		}

	};



	// Construct record object from detailed values on each field
	CMessageTitleRecord(long nShareCode1, CString strCompany, int nClientType);

	// Clean up internal objects
	virtual ~CMessageTitleRecord();

	// Overridden callback method, where we can customize any drawing item metrics.
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);

	BOOL CheckShareCode(long nShareCode1, long nClientType = 0)
	{
		return (m_nShareCode1 == nShareCode1) && (m_nClientType == nClientType);
	}

public:
	long m_nShareCode1;
	long m_nClientType;
	CString m_strCompanyName;
};





#endif // !defined(AFX_MESSAGERECORD_H__AFFF918D_1624_41E5_8902_81B1F0C749BA__INCLUDED_)
