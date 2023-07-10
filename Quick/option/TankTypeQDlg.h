#pragma once


// CTankTypeQDlg 대화 상자입니다.

#include "afxwin.h"
class  CTankTypeQRecordItemCheck : public CXTPGridRecordItem
{
public:
	CTankTypeQRecordItemCheck(BOOL bCheck)
	{
		HasCheckbox(TRUE);
		SetChecked(bCheck);
	}

};

class CTankTypeQRecordItemCombo : public CXTPGridRecordItem
{
public:
	CTankTypeQRecordItemCombo(UINT nValue)
	{
		m_nValue = nValue;
		GetEditOptions(NULL)->AddConstraint("정상", 0);
		GetEditOptions(NULL)->AddConstraint("20%만보기", 1);
		GetEditOptions(NULL)->AddConstraint("25%만보기", 2);
		GetEditOptions(NULL)->AddConstraint("30%만보기", 3);
		GetEditOptions(NULL)->AddConstraint("40%만보기", 4);
		GetEditOptions(NULL)->AddConstraint("50%만보기", 5);
		GetEditOptions(NULL)->AddConstraint("66%만보기", 6);
		GetEditOptions(NULL)->AddConstraint("75%만보기", 7);
		GetEditOptions(NULL)->AddConstraint("80%만보기", 8);
		GetEditOptions(NULL)->AddConstraint("90%만보기", 9);
		GetEditOptions(NULL)->m_bConstraintEdit = FALSE;
		GetEditOptions(NULL)->m_bAllowEdit = TRUE;
		GetEditOptions(NULL)->m_bExpandOnSelect = TRUE;
		GetEditOptions(NULL)->AddComboButton(TRUE);
	}

	CString GetCaption(CXTPGridColumn* /*pColumn*/)
	{
		CXTPGridRecordItemConstraint* pConstraint = GetEditOptions(NULL)->FindConstraint(m_nValue);
		if (pConstraint == NULL)
		{
			long nValue = 0;
			pConstraint = GetEditOptions(NULL)->FindConstraint(nValue);
		}

		ASSERT(pConstraint);
		return pConstraint->m_strConstraint;
	}

	virtual void OnConstraintChanged(XTP_GRIDRECORDITEM_ARGS* pItemArgs, CXTPGridRecordItemConstraint* pConstraint)
	{
		m_nValue = (long)pConstraint->m_dwData;
	}

	BOOL GetValue()
	{
		return m_nValue;
	}

	void SetValue(int nValue)
	{
		m_nValue = nValue;

		SetGroupPriority(nValue);
		SetSortPriority(GetGroupPriority());
	}

protected:
	long m_nValue;
};

class CTankTypeQRecord : public CXTPGridRecord
{
public:
	CTankTypeQRecord(CString num, CString branch_name, BOOL show_tank, int tank_type, BOOL show_part_not_apply, BOOL show_part_apply,
		BOOL call_count, BOOL rider_calc, BOOL rider_count, BOOL branch_calc) 
	{
		AddItem(new CXTPGridRecordItemText(num));
		AddItem(new CXTPGridRecordItemText(branch_name));
		AddItem(new CTankTypeQRecordItemCheck(show_tank));
		AddItem(new CTankTypeQRecordItemCombo(tank_type));
		AddItem(new CTankTypeQRecordItemCheck(show_part_not_apply));
		AddItem(new CTankTypeQRecordItemCheck(show_part_apply));
		AddItem(new CTankTypeQRecordItemCheck(call_count));
		AddItem(new CTankTypeQRecordItemCheck(rider_calc));
		AddItem(new CTankTypeQRecordItemCheck(rider_count));
		AddItem(new CTankTypeQRecordItemCheck(branch_calc));
	}
};

class CTankTypeQDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CTankTypeQDlg)

public:
	CTankTypeQDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTankTypeQDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TANKVIEW_Q_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedApplyBtn();	
	afx_msg void OnReportCheckItem(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportClickItem(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	virtual BOOL OnInitDialog();
	void SetInitColumn(int nShowPartApply, BOOL &bCallCount, BOOL &bRiderCalculate, 
		BOOL &bRiderCount, BOOL &bBranchCalculate);
	CXTPListCtrl2 m_List;
	void RefreshList();
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnBnClickedRateAllBtn();
	CComboBox m_cmbRate;
	CComboBox m_cmbCheck;
	afx_msg void OnBnClickedCheckAllBtn();
	afx_msg void OnBnClickedCheckNotallBtn();
	void SetCheckFunction(BOOL bCheck);
	afx_msg void OnBnClickedButton1();

	long m_nCompany;
	long m_nServer;
};
