#pragma once
#include "afxwin.h"
#include "BranchSel.h"

#define COLOR_YELLOW RGB(0xFF, 0xFF, 0)


typedef struct {
	long nID;
	CString strDong;
} ST_DONG;

typedef map<long, ST_DONG> MAP_DONG;
typedef map<pair<long, long>, long> SAVE_MAP;
extern SAVE_MAP m_mapSave;

class CChargeReportRecord: public CXTPGridRecord
{
public:
	CChargeReportRecord(CString strSido, long nID)
	{
		AddItem(new CXTPGridRecordItemText(strSido));
		m_nID = nID;
		m_nCharge = 0;
		m_bLi = 0;
	}

	CChargeReportRecord(CString strSido, long nID,BOOL bStart, BOOL bLi = FALSE)
	{		
		AddItem(new CXTPGridRecordItemText(strSido));

		if(bStart == FALSE)
		{
			AddItem(new CXTPGridRecordItemText(""));
		}

		m_nID = nID;
		m_nCharge = 0;
		m_bLi = bLi;
	}

private:
	long m_nID;
	long m_nCharge;
	BOOL m_bLi;
public:
	long GetGuID() {return m_nID;}
	BOOL IsHasLi() {return m_bLi;}
};


class CChargeDongReportRecord: public CXTPGridRecord
{
public:	

	class CXTPGridRecordNumber : public CXTPGridRecordItemNumber
	{
	public:
		CXTPGridRecordNumber(long nID): CXTPGridRecordItemNumber(nID)
		{
			m_nID = nID;
			m_nCharge = 0;
			m_bChange = FALSE;
		}

		CString GetCaption(CXTPGridColumn* pColumn)
		{
			return RemoveZero(GetStringFromLong(GetCharge()));
		}

		void OnEditChanged(XTP_REPORTRECORDITEM_ARGS* pItemArgs, LPCTSTR szText)
		{
			long nCharge = atoi(szText);

			if(nCharge >= 1000)
				nCharge = nCharge / 1000;

			SetCharge(nCharge);
			m_bChange = TRUE; 

			CXTPGridRecordItemNumber::OnEditChanged(pItemArgs, szText);
		}

		virtual BOOL OnEditChanging(XTP_REPORTRECORDITEM_ARGS* pItemArgs, CString& rstrNewText)
		{
			int a= 0;
			return CXTPGridRecordItem::OnEditChanging(pItemArgs, rstrNewText);
		}
	
		virtual BOOL OnChar(XTP_REPORTRECORDITEM_ARGS *pItemArgs, UINT nChar)
		{
			return TRUE;
		}
	public:
		BOOL IsChange() {return m_bChange;}
		long GetDongID() {return m_nID;}
		long GetCharge() {return m_nCharge;}
		void SetCharge(long nCharge) {m_nCharge = nCharge;}
		void SetChange(BOOL bChange) {m_bChange = bChange;}

	private:
		long m_nID;
		long m_nCharge;
		BOOL m_bChange;
	};

	CChargeDongReportRecord(long nColItem, MAP_DONG *pMap)
	{	
		for(int i=0; i<nColItem; i++) 
		{
			MAP_DONG::iterator it = pMap->find(i);
			AddItem(new CXTPGridRecordItemText(GetRemoveLastDong(it->second.strDong)));
		}

		m_nID = 0;
	}

	CChargeDongReportRecord(long nID, CString strDong, long nColItem, MAP_DONG *pMap)
	{	
		AddItem(new CXTPGridRecordItemText(strDong));

		for(int i=1; i<nColItem; i++) 
		{
			MAP_DONG::iterator it = pMap->find(i);
			AddItem(new CXTPGridRecordNumber(it->second.nID));
		}

		m_nID = nID;
	}
public:
	long GetStartDongID() {return m_nID;}
	long GetDestDongID(long nItem)
	{
		CXTPGridRecordNumber *pRecordItem = (CXTPGridRecordNumber*)GetItem(nItem);
		return pRecordItem->GetDongID();
	}
	void SetCharge(long nItem, long nCharge)
	{
		((CXTPGridRecordNumber*)GetItem(nItem))->SetCharge(nCharge);
	}

	void SetChange(long nItem, BOOL bChange)
	{
		((CXTPGridRecordNumber*)GetItem(nItem))->SetChange(bChange);
	}

	long GetCharge(long nItem)
	{
		return ((CXTPGridRecordNumber*)GetItem(nItem))->GetCharge();
	}

	BOOL IsChange(long nItem)
	{
		return ((CXTPGridRecordNumber*)GetItem(nItem))->IsChange();
	}

private:
	long m_nID;
public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
};

class CXTPGridChargeControl : public CXTPListCtrl2
{
public:
	CXTPGridChargeControl::CXTPGridChargeControl()
	{
		m_nCol = 0;
	}

	void SetSelectedCol(long  nCol)
	{ 
		m_nCol = nCol;
	}

	long GetSelectedCol()
	{
		return m_nCol;
	}

	void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
	{ 
		long nRow = pDrawArgs->pRow->GetIndex();
		long nCol = pDrawArgs->pColumn->GetIndex();

		pItemMetrics->clrForeground = RGB(0, 0, 0);

		if(nRow == 0 || nCol == 0) 
			pItemMetrics->clrBackground = RGB(220, 220, 255); 

		if(m_nCol == nCol && nCol > 0) 
			pItemMetrics->clrBackground = COLOR_YELLOW;

		if(nRow == 0 || nCol == 0)
			return;

		CChargeDongReportRecord *pRecord = (CChargeDongReportRecord*)pDrawArgs->pRow->GetRecord();

		long nStartID = pRecord->GetStartDongID();
		long nDestID = pRecord->GetDestDongID(nCol);

		if(nStartID == nDestID) 
			pItemMetrics->clrBackground = RGB(200, 255, 200);

		SAVE_MAP::iterator it = m_mapSave.find(make_pair(nStartID, nDestID));

		//if(nRow ==2 && nCol == 1)
		//{ 
		//	int a=0;
		//}

		if(it != m_mapSave.end())
		{
			if(it->second != pRecord->GetCharge(nCol))
				pItemMetrics->clrBackground = RGB(255, 100, 100);
		}
		else 
		{ 
			if(pRecord->IsChange(nCol) && !pItemMetrics->strText.IsEmpty())
				pItemMetrics->clrBackground = RGB(255, 100, 100);
		}
	}

private:
	CWnd *m_pDlg;
	long m_nRow;
	long m_nCol;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

class CChargeDongNewDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeDongNewDlg)

public:
	CChargeDongNewDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChargeDongNewDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHARGE_DONG_NEW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:


	BOOL IsUpdateOk();

	void ChargeTypeNameRefresh();
	virtual BOOL OnInitDialog();
	BOOL MakeStartDestList();
	void ClearDongList();
	void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	void OnReportItemSelChange(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	void RefreshDongData(long nStartID, BOOL bStartLi, long nDestID, BOOL bDestLi);
	void MakeDongList();
	void ReLoadCharge();
	void FillDongData(long nID, BOOL bLi, MAP_DONG *pMap);
	void RefreshDongCharge(long nStartID, BOOL bStartLi, long nDestID, BOOL bDestLi);
	long GetCurPayCompany();
	void SetCharge(long nStartDongID, long nDestDongID, long nCharge);
	long IsChargeChange(BOOL bOnlyCount);
	BOOL SaveReal(long nStartID, long nDestID, long nCharge);
	void ShowListCenter(CXTPGridControl *pControl, CString strExpandCity);
	afx_msg void OnBnClickedCloseButton();
	afx_msg LONG OnChangeBrachCode(WPARAM wParam, LPARAM lParam);
	CXTPGridRecord* GetRecordFromSido(CString strSido, CXTPGridControl *pControl);
	CXTPGridRecord* GetRecordFromGugun(CString strSido, CString strGugun, CXTPGridControl *pControl);
	CXTPGridRecord* GetFirstSelectedRecord(CXTPGridControl *pControl);

	CXTPGridControl m_lstStart;
	CXTPGridControl m_lstDest;
	CXTPGridChargeControl m_lstDong;

	MAP_DONG m_mapStart;
	MAP_DONG m_mapDest;
	CComboBox m_cmbType;
	afx_msg void OnBnClickedSaveButton();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedRefreshButton();

	BOOL m_bSave;
	afx_msg void OnCbnSelchangeTypeCombo();
	afx_msg void OnEnChangeSearchStartEdit();
	afx_msg void OnEnChangeSearchDestEdit();
	CFlatEdit2 m_edtStartSearch;
	CFlatEdit2 m_edtDestSearch;
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	long GetMaxHeightText(CPaintDC *pDc, CString strText);

	afx_msg void OnInsertCharge();
	afx_msg void OnExcel();

	CButton m_chkTwoWay;

	long m_PreGNo;
	long m_PreType;
	long m_PreCarType;

	//아래3개 필요없지만.. 
	long m_nCompany;
	BOOL m_bIntegrated;
	CString m_strCompany;
	CComboBox m_cmbBranch;
	CComboBox m_cmbCarType;
	CComboBox m_cmbDiscountCompany;
	afx_msg void OnCbnSelchangeCarTypeCombo();
	afx_msg void OnCbnEditchangeDisComCombo2();
	afx_msg void OnCbnSelchangeDisComCombo2();
	afx_msg void OnCbnSelchangeCarTypeCombo2();
	CComboBox m_cmbCarType2;
	afx_msg void OnBnClickedSearchGroupBtn();
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnBnClickedDiscountCompanyBtn();
	afx_msg void OnBnClickedDiscountCompanyDelBtn();
	afx_msg void OnCbnSelchangeBranchCombo();
protected:
	virtual void OnCancel();
};
