#pragma once
#include "afxwin.h"

typedef struct{
	long nCode;
	CString strType;
	long nPenaltyDay;
	long nBlackMarks;
	BOOL bCorp;	
}RiderBlackMarks2010;

class CRiderAdviceRecord2010 : public CXTPGridRecord
{

public:
	class CRiderAdviceComboItem : public CXTPGridRecordItem
	{
	public:
		CRiderAdviceComboItem(UINT nValue)
		{
			m_nValue = nValue;
			//GetEditOptions(NULL)->AddConstraint(_T("무제한"), 9999);
			GetEditOptions(NULL)->AddConstraint(_T("-"), 0);
			GetEditOptions(NULL)->AddConstraint(_T("15일"), 15);
			GetEditOptions(NULL)->AddConstraint(_T("30일"), 30);
			GetEditOptions(NULL)->AddConstraint(_T("60일"), 60);
			GetEditOptions(NULL)->AddConstraint(_T("90일"), 90);
			GetEditOptions(NULL)->AddConstraint(_T("150일"), 150);
			GetEditOptions(NULL)->AddConstraint(_T("180일"), 180);
			GetEditOptions(NULL)->AddConstraint(_T("무제한"), 9999);
			
			GetEditOptions(NULL)->m_bConstraintEdit = FALSE;
			GetEditOptions(NULL)->m_bAllowEdit = FALSE;	
			GetEditOptions(NULL)->AddComboButton(TRUE);
		}

		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			CXTPGridRecordItemConstraint* pConstraint = GetEditOptions(NULL)->FindConstraint(m_nValue);
			//if(pConstraint == NULL || ((CMyRecord*)GetRecord())->m_bNoShareA)
			//{
			//	long nValue = -1;
			//	pConstraint = GetEditOptions(NULL)->FindConstraint(nValue);
			//}
			if(pConstraint == NULL)
				return "";
			//ASSERT(pConstraint);
			return pConstraint->m_strConstraint;
		}

		virtual void OnConstraintChanged(XTP_REPORTRECORDITEM_ARGS* pItemArgs, CXTPGridRecordItemConstraint* pConstraint)
		{
			m_nValue = (long)pConstraint->m_dwData;
		}

		BOOL GetValue()
		{
			return m_nValue;
		}
	protected:
		long m_nValue;

	};

	class CRiderAdviceRecord2010ItemCheck : public CXTPGridRecordItem
	{
	public:
		CRiderAdviceRecord2010ItemCheck(BOOL bCheck)
		{
			HasCheckbox(TRUE);
			SetChecked(bCheck);
		}
	};

	CRiderAdviceRecord2010::CRiderAdviceRecord2010(long nCode, CString strTitle, CString strType, long nPenaltyDay, 
						long nBlackMarks, BOOL bCorp, BOOL bChild, BOOL bCheckCode, CString sCheckEtc,long nApplyPenaltyDay )
	{
		if(bChild)
			AddItem(new CXTPGridRecordItemText(""));
		else
			AddItem(new CXTPGridRecordItemText(strTitle));

		AddItem(new CXTPGridRecordItemText(strType));
		AddItem(new CRiderAdviceRecord2010ItemCheck(bCheckCode));

		CString strPenalty = ""; 

		if(nPenaltyDay == 9999)
			strPenalty = "무제한";
		else if(nPenaltyDay == 0)
			strPenalty = "-";
		else
			strPenalty = LF->GetStringFromLong(nPenaltyDay) + "일";

		if(bCorp)
			strPenalty = "법인콜 " + strPenalty;

		AddItem(new CRiderAdviceComboItem(nApplyPenaltyDay));
		/*
		if(nCode == 7000) //기타
			AddItem(new CRiderAdviceComboItem(9999));
		else
			AddItem(new CXTPGridRecordItemText(sPenalty));
		*/	

		if(nBlackMarks == 0)
			AddItem(new CXTPGridRecordItemText("-"));
		else
			AddItem(new CXTPGridRecordItemText(LF->GetStringFromLong(nBlackMarks) + "점"));

		AddItem(new CXTPGridRecordItemText(sCheckEtc));

		m_nBlackMarks = nBlackMarks;
		m_nPenaltyDay = nPenaltyDay;
		m_bCorp = bCorp;
		m_strType = strType;
		m_nCode = nCode;
		m_strEtc = sCheckEtc;
	}

	BOOL GetChecked()
	{
		return ((CRiderAdviceRecord2010ItemCheck*)GetItem(2))->IsChecked();
	}

	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics) 
	{
		int nCol = pDrawArgs->pColumn->GetItemIndex();
		int nRow = pDrawArgs->pRow->GetIndex();

		if(nCol == 3) //패널티
		{ 
			if(m_nPenaltyDay > 1000) //무제한
				pItemMetrics->clrBackground = RGB(50, 50, 255);
			else if(m_nPenaltyDay > 100)
				pItemMetrics->clrBackground = RGB(100, 100, 255);
			else if(m_nPenaltyDay > 50)
				pItemMetrics->clrBackground = RGB(150, 150, 255);
		}

		if(nCol == 4) //벌점
		{
			if(m_nBlackMarks > 99) 
				pItemMetrics->clrBackground = RGB(255, 50, 50);
			else if(m_nBlackMarks > 49)
				pItemMetrics->clrBackground = RGB(255, 100, 100);
			else if(m_nBlackMarks > 29)
				pItemMetrics->clrBackground = RGB(255, 150, 150);
			else if(m_nBlackMarks > 0)
				pItemMetrics->clrBackground = RGB(255, 200, 200);
		}
	}

	long GetComboValue()
	{
		CRiderAdviceComboItem *pRecordItem = (CRiderAdviceComboItem*)GetItem(3);
		return pRecordItem->GetValue();
	}

public:
	long m_nBlackMarks;
	long m_nPenaltyDay;
	long m_bCorp;
	CString m_strType;
	long m_nCode;
	CString m_strEtc;

};

typedef map<long, RiderBlackMarks2010*>  RiderBlackMarks2010_MAP;

class CRiderAdviceDlg2010 : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderAdviceDlg2010)

public:
	CRiderAdviceDlg2010(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRiderAdviceDlg2010();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RIDER_ADVICE_DLG2010 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	long m_nCompany;
	long m_nRiderCompany;
	long m_nOrderCompany;
	long m_nRNo;

	CString m_strTNo;

	virtual BOOL OnInitDialog();
	void RefreshList();
	RiderBlackMarks2010_MAP m_map;
	afx_msg void OnBnClickedSaveBtn();
	BOOL CheckCount();
	BOOL CheckCountDb(long nCount);
	BOOL Save(BOOL bAll);
	BOOL SaveSub(BOOL bAll, CRiderAdviceRecord2010 *pRecord);
	
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnBnClickedCheckBtn();
	
	CXTPGridControl m_List;
	CFlatEdit2 m_edtTNo;
	afx_msg void OnBnClickedSaveBtn2();
	long m_nModifyID;
	BOOL m_bConfirmTNo;
	afx_msg void OnBnClickedSaveBtn3();
	CButton m_btnSave3;
};
