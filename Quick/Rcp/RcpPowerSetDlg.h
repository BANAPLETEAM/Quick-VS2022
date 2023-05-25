#pragma once

#include "MakeRcpPower.h"


class CDetailPowerRecord : public CXTPGridRecord
{
protected:
	
	class CPowerRecordItemCheck : public CXTPGridRecordItem
	{
	public:
		CPowerRecordItemCheck(BOOL bCheck)
		{
			HasCheckbox(TRUE);
			SetChecked(bCheck);
		}
/*
		void OnEditChanged(XTP_REPORTRECORDITEM_ARGS* pItemArgs, LPCTSTR szText)
		{
			if(((CDetailPowerRecord*)GetRecord())->HasChildren())
			{
				CXTPGridRecords *pChildRecords = ((CDetailPowerRecord*)GetRecord())->GetChilds();
				for(int k = 0; k < pChildRecords->GetCount(); k++)
				{
					CXTPGridRecord *pRecord = pChildRecords->GetAt(k);
					((CDetailPowerRecord*)pRecord)->SetEditable(IsChecked());
				}
			}
		}
*/
	};


public:
	CDetailPowerRecord(long nCode, CString strMain, CString strSubMain, CString strTitle, CString strDetail, BOOL bHasPower)
	{
		m_nCode = nCode;
		m_bDirtyFlag = FALSE;
		AddItem(new CXTPGridRecordItemText(strMain));
		AddItem(new CXTPGridRecordItemText(strSubMain));
		AddItem(new CPowerRecordItemCheck(bHasPower));
		AddItem(new CXTPGridRecordItemText(strTitle));
		AddItem(new CXTPGridRecordItemText(strDetail));
	}

	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{
		int nCol = pDrawArgs->pColumn->GetIndex();
		if(nCol == 3)
		{
			if(GetPowerType())
			{
				pItemMetrics->clrBackground = RGB(0, 0, 200);
				pItemMetrics->clrForeground= RGB(255, 255, 255);
			}
			else
			{
				pItemMetrics->clrBackground = RGB(200, 200, 250);
				pItemMetrics->clrForeground = RGB(0, 0, 0);
			}
		}
	}


	BOOL GetDirtyFlag() { return m_bDirtyFlag; }
	void SetDirtyFlag() { m_bDirtyFlag = TRUE;}
	long GetPowerType() { return ((CPowerRecordItemCheck*)GetItem(2))->IsChecked(); }

protected:
	BOOL m_bDirtyFlag;

public:
	long m_nCode;

	/*
	static BOOL GetValue(XTP_NM_REPORTRECORDITEM* pItemNotify)
	{
	return ((CPropertyItemBool*)pItemNotify->pItem)->GetValue();
	}
	*/
};




// CRcpPowerSetDlg 대화 상자입니다.

class CRcpPowerSetDlg : public CXTResizeDialog
{
	DECLARE_DYNAMIC(CRcpPowerSetDlg)

public:
	CRcpPowerSetDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRcpPowerSetDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_RCP_POWER_SET_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOkBtn();
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnEnChangeSearchEdit();

protected:
	CXTPGridControl m_wndReportCtrl;
	CImageList m_ilIcons;
	CFlatEdit2 m_edtSearch;

public:
	afx_msg void OnCustom1Click(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	virtual BOOL OnInitDialog();
	void RefreshList();
	BOOL GetPowerSub(CDetailPowerRecord *pPower, BOOL bLogiSet, CString &strPower, BOOL &bNotHasPower);
	void SavePower(BOOL bLogiSet = FALSE);

	CString m_strMsg;
	long m_nCompany;
	long m_nMNo;
	long m_nRole;

	CString m_strBranchName;
	CString m_strName;

	CStatic m_NameStatic;
	CButton m_PreventCheck;
	BOOL m_bPrevent;

	CMakeRcpPower m_ManagerPower;
};


