#pragma once

#include "VirtualRecord.h"

class CMyReportControl : public CXTPGridControl
{
	DECLARE_DYNAMIC(CMyReportControl)

public:
	CMyReportControl();
	virtual ~CMyReportControl();

protected:
	DECLARE_MESSAGE_MAP()

public:
	int GetSelectedItem()
	{
		POSITION pos = GetSelectedRows()->GetFirstSelectedRowPosition();

		if(pos)
			return GetSelectedRows()->GetNextSelectedRow(pos)->GetIndex();
		else
			return -1;
	}
	CXTPGridSelectedRows* GetXListSelectedRows()
	{
		return GetSelectedRows();
	}

	CVirtualRecord* GetXListSelectedRecord()
	{
		return (CVirtualRecord*)(GetSelectedRows()->GetAt(0)->GetRecord());
	}


	void LoadListInfo();
	void SaveListInfo();

	int m_nHWidth[MAX_COLUMN];
	int m_nHOrder[MAX_COLUMN];
	UINT m_nColumnCount;


	void GetSortCol(int *nCol, BOOL *bAsc);

	void ShowRiderInfo(BOOL bShow);
	void DrawRiderInfo(CDC *pDC);
	void DrawInfoBox(CDC *pDC, CRect rc, BOOL bGreen = FALSE);
	void PrintLine(CDC *pDC, CRect &rc, CString strTitle, CString strText, 
				BOOL bNextSeparator = FALSE, COLORREF clrText = RGB(0, 0, 0));
	void PrintDualLine(CDC *pDC, CRect &rc, CString strTitle, CString strText, 
				BOOL bNextSeparator = FALSE, COLORREF clrText = RGB(0, 0, 0));

	void ShowCustomerInfo(BOOL bShow);
	void DrawCustomerInfo(CDC *pDC);
	void ShowShareOrder(BOOL bShow);
	void DrawShareOrder(CDC *pDC);

	void SetSelectedColor(COLORREF clrSelected);
	virtual void OnDraw(CDC* pDC);

protected:
	BOOL m_bShowRiderInfo;
	BOOL m_bShowCustomerInfo;
	BOOL m_bShowShareOrder;

public:
	CString m_strCompany;
	CString m_strBranch;
	CString m_strCompanyPhone;
	CString m_strOfficePhone;
	CString m_strRName;
	CString m_strDeviceID;
	CString m_strDeviceType;
	CString m_strDeviceVer;
	CString m_strPhone;
	CString m_strHomePhone;
	CString m_strEnterDate;
	CString m_strDepositType;
	CString m_strTodayIncome;
	CString m_strBalance;
	CString m_strTodayCharge;
	CString m_strWorkState;
	CString m_strCountLimit;
	CString m_strTimeLimit;
	CString m_strInsInfo;
	CString m_strInsExpDate;
	CString m_strHistory;
	CString m_strCurBranch;
	CString m_strRecvCID;

	BOOL m_bConfirmCall;
};


