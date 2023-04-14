// DbTestDlg.h : 헤더 파일
//

#pragma once

#include "DataBox.h"

#define  MAX_SUB_COUNT 5
#define  MAX_MAIN_COUNT 3
#define EVERY_DAY_CHECK 2
// CDbTestDlg 대화 상자

#include "BranchSel.h"
#include "XTPListCtrl_Branch.h"

class CXTPGridRecordItemTextOption : public CXTPGridRecordItemText
{
public:
	CXTPGridRecordItemTextOption(CString sValue)
	{
		this->SetValue(sValue);
		this->SetCaption(sValue);
		
	}

	virtual void OnEditChanged(
		XTP_REPORTRECORDITEM_ARGS* pItemArgs, 
		LPCTSTR szText
		)
	{
		if(pItemArgs->pItem && pItemArgs->pItem->GetIndex() >= 1 &&  pItemArgs->pItem->GetIndex()  <= 3)
		{
			SetValue(szText);
			SetCaption(szText);
		}
		
	}


};


class CMyCallRiderRecord : public CMyXTPGridRecord
{


	long m_nID;
	long m_nClass;
	BOOL m_bDirtyFlag;
	


public:
	CMyCallRiderRecord(CString sType ,long nStartValue,long  nEndValue,
			long  nAmount, long  nAmountA, long  nAmountB, long  nAmountC,
			long  nClass, long nID,BOOL bCount, BOOL bAverage, BOOL bMax )
	{
		AddItem(new CXTPGridRecordItemTextOption(sType)  );		
		AddItem(new CXTPGridRecordItemTextOption(nStartValue <= 0 ? "" : GetMyNumberFormat(nStartValue) ));
		AddItem(new CXTPGridRecordItemTextOption(nEndValue <= 0 ? "" : GetMyNumberFormat(nEndValue) ));
		AddItem(new CXTPGridRecordItemTextOption(nAmount <= 0 ? "" : GetMyNumberFormat(nAmount) ));		
		
	
		m_nClass = nClass;
		m_bDirtyFlag = FALSE;
		m_nID = nID;
	}
	
	CString GetItemValue(int nCol)
	{
		if(nCol >= 0 && nCol <= 3)
			return ((CXTPGridRecordItemText*)GetItem(nCol))->GetValue();
		else
			return "";


	}
	void SetItemValue(int nCol, CString sValue)
	{
		((CXTPGridRecordItemText*)GetItem(nCol))->SetValue(sValue);
		((CXTPGridRecordItemText*)GetItem(nCol))->SetCaption(sValue);
	}

};

class CMyCallDepositDlg : public CMyDialog
{
// 생성
public:
	CMyCallDepositDlg(CWnd* pParent = NULL);	// 표준 생성자
	virtual ~CMyCallDepositDlg();
// 대화 상자 데이터
	enum { IDD = IDD_MYCALL_DEPOSIT_DLG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원


// 구현
protected:
	HICON m_hIcon;
	BOOL m_bInitData;
	// 메시지 맵 함수를 생성했습니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()

public:
	void InitControl();
	//BOOL IsTypeData(CMyCallRiderRecord *pRecord);
	//void DeleteExceptionList();
	BOOL IsTermBlank(CMyCallRiderRecord *pRecord);
	BOOL ExceptionCheckCharge();
	CString EmptyNulllValue(CString sValue);
	//afx_msg void OnBnClickedTestBtn();
	
	
	
	CDataBox m_ChargeList;

	CComboBox m_cmbBranch;

	
	
	long m_nCompany;
	CBranchSel m_cBranch;
	CFlatMainEdit m_edtMain;
	CFlatSubEdit m_edtSub;
	CBranchMainBtn m_btnMain; 
	CBranchSubBtn m_btnSub;
	CXTPListCtrl_Branch m_lstBranch;
	
	LONG OnChangeBrachCode(WPARAM wParam, LPARAM lParam);
	void RefreshList();
	BOOL Save(long nCompany, BOOL bAll);
	BOOL ExceptionColumnString(CString sRow,  int nCol , CString sValue );
	BOOL ExceptionRowString(CMyCallRiderRecord *pRecord,    CString &sPreEndValue  );

	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnBnClickedAllDelBtn();
	afx_msg void OnBnClickedRowDelBtn();
	afx_msg void OnBnClickedBranchAllBtn2();
	//afx_msg void OnBnClickedRowAddBtn();
	
	
	
	afx_msg void OnBnClickedBranchBtn2();
	//afx_msg void OnBnClickedExpireCheck();
	//afx_msg void OnBnClickedMileDayRadio();
	//afx_msg void OnBnClickedMileMonthRadio();
};

