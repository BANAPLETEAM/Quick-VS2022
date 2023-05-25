#pragma once

#include "databox.h"
#include "afxwin.h"

class CChargeDongSettingDlg;
class CChargeWorkDlg;
class CChargeDongDlg2;


class CDetailChargeRecord : public CXTPGridRecord
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
		
	};


public:
	CDetailChargeRecord(long nID,BOOL bHasNotDong, int nClass, CString sArea, CString sDong, BOOL bExcel, long nDongID)
	{
		m_bExcel = bExcel;
		m_nID = nID;
		m_bHasNotDong = bHasNotDong;
		m_nClass = nClass;
		m_bDirtyFlag = FALSE;
		m_nDongID = nDongID;
		m_sArea = sArea;
		m_sDong = sDong;
		AddItem(new CXTPGridRecordItemText(sArea));
		AddItem(new CXTPGridRecordItemText(sDong));		


	}
	int GetTypeInfo()
	{
		if(m_nClass == 10 && m_bHasNotDong)
			return 3;
		else if(m_nClass == 10 && m_bHasNotDong == FALSE)
			return 2;
		else if(m_nClass != 10 )
			return 1;
		else
			return 0;
	}

	BOOL GetDirtyFlag() { return m_bDirtyFlag; }
	void SetDirtyFlag() { m_bDirtyFlag = TRUE;}


protected:
	BOOL m_bDirtyFlag;
	BOOL m_bHasNotDong;
	int		m_nClass;
	

public:
	long m_nID;
	BOOL m_bExcel;
	long m_nDongID;
	CString m_sArea;
	CString m_sDong;

	
};


class CDetailDestChargeRecord : public CXTPGridRecord
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
	};
	class CMyXTPGridRecordItemNumber : public CXTPGridRecordItemNumber
	{
	public:
		CMyXTPGridRecordItemNumber(long nCharge): CXTPGridRecordItemNumber(nCharge)
		{

			if(nCharge == 0)
				m_strFormatString = "";
			else
				m_strCaption = LF->GetMyNumberFormat(nCharge);
		}
	};
public:
	CDetailDestChargeRecord(long nID,BOOL bHasNotDong, int nClass, CString sArea,   CString sDong, 
		CString sGeneralMotoCharge, CString sGeneralDaMaCharge, CString sGeneralRaboCharge, CString sCompanyMotoCharge,
		CString sCompanyDaMaCharge, CString sSubWayCharge, BOOL bExcel, long nDongID)
	{
		m_nID = nID;
		m_bHasNotDong = bHasNotDong;
		m_nClass = nClass;
		m_bDirtyFlag = FALSE;
		m_bExcel = bExcel;
		m_nDongID = nDongID;
		m_sArea = sArea;
		m_sDong = sDong;

		m_nGeneralMoto = 0;
		m_nGeneralDama = 0;
		m_nGeneralRabo = 0;
		m_nSpecificMoto = 0;
		m_nSpecificDama = 0;
		m_nSubWay = 0;

		AddItem(new CXTPGridRecordItemText(sArea));
		AddItem(new CXTPGridRecordItemText(sDong));		
		AddItem(new CXTPGridRecordItemText(sGeneralMotoCharge));		
		AddItem(new CXTPGridRecordItemText(sGeneralDaMaCharge));		
		AddItem(new CXTPGridRecordItemText(sGeneralRaboCharge));		
		AddItem(new CXTPGridRecordItemText(sCompanyMotoCharge));		
		AddItem(new CXTPGridRecordItemText(sCompanyDaMaCharge));	
		AddItem(new CXTPGridRecordItemText(sSubWayCharge));	
	}
	int GetTypeInfo()
	{
		if(m_nClass == 10 && m_bHasNotDong)
			return 3;
		else if(m_nClass == 10 && m_bHasNotDong == FALSE)
			return 2;
		else if(m_nClass != 10)
			return 1;
		else
			return 0;
	}
	void SetGeneralMoto(CString str)
	{
		((CXTPGridRecordItemText*)GetItem(2))->SetValue(str == "0" ? "" : str);
		GetItem(2)->SetCaption(str == "0" ? "" : str);
		str.Replace(",", "");
		m_nGeneralMoto = _ttoi(str);
	}
	void SetGeneralDaMa(CString str)
	{
		((CXTPGridRecordItemText*)GetItem(3))->SetValue(str == "0" ? "" : str);
		this->GetItem(3)->SetCaption(str == "0" ? "" : str);
		str.Replace(",", "");
		m_nGeneralDama = _ttoi(str);
	}
	void SetGeneralRabo(CString str)
	{
		((CXTPGridRecordItemText*)GetItem(4))->SetValue(str == "0" ? "" : str);
		this->GetItem(4)->SetCaption(str == "0" ? "" : str);
		str.Replace(",", "");
		m_nGeneralRabo = _ttoi(str);
	}
	void SetSpecificDaMa(CString str)
	{
		((CXTPGridRecordItemText*)GetItem(5))->SetValue(str == "0" ? "" : str);
		this->GetItem(5)->SetCaption(str == "0" ? "" : str);
		str.Replace(",", "");
		m_nSpecificDama = _ttoi(str);
	}		
	void SetSpecificMoto(CString str)
	{
		((CXTPGridRecordItemText*)GetItem(6))->SetValue(str == "0" ? "" : str);
		this->GetItem(6)->SetCaption(str == "0" ? "" : str);
		str.Replace(",", "");
		m_nSpecificMoto = _ttoi(str);
	}
	void SetSpecificSubWay(CString str)
	{
		((CXTPGridRecordItemText*)GetItem(7))->SetValue(str == "0" ? "" : str);
		this->GetItem(7)->SetCaption(str == "0" ? "" : str);
		str.Replace(",", "");
		m_nSubWay = _ttoi(str);
	}		


	BOOL GetDirtyFlag() { return m_bDirtyFlag; }
	void SetDirtyFlag(BOOL bFlag) { m_bDirtyFlag = bFlag;}


protected:
	BOOL m_bDirtyFlag;
	BOOL m_bHasNotDong;
	int		m_nClass;

public:
	long m_nID;
	BOOL m_bExcel;
	long m_nDongID;
	CString m_sArea;
	CString m_sDong;

	long m_nGeneralMoto;
	long m_nGeneralDama;
	long m_nGeneralRabo;
	long m_nSpecificMoto;
	long m_nSpecificDama;
	long m_nSubWay;
	/*
	static BOOL GetValue(XTP_NM_REPORTRECORDITEM* pItemNotify)
	{
	return ((CPropertyItemBool*)pItemNotify->pItem)->GetValue();
	}
	*/
};



class CMyDestReport : public CXTPGridControl
{
public:
	CMyDestReport()
	{
		m_bMotoCharge = FALSE;
		m_bDamaCharge = FALSE;
		m_bTruckCharge = FALSE;
		m_bBonggoCharge= FALSE;
		m_bBonggoCharge= FALSE;

	};   // 표준 생성자입니다.
	virtual ~CMyDestReport(){};
	//int niValue;
	BOOL m_bMotoCharge;
	BOOL m_bDamaCharge;
	BOOL m_bTruckCharge;
	BOOL m_bBonggoCharge;
	BOOL m_bSubWayCharge;

	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{

		CXTPGridRecord *pRecord = pDrawArgs->pRow->GetRecord();
		int nRow = pRecord->GetIndex();
		int nCol = pDrawArgs->pColumn->GetItemIndex();
		if(m_bMotoCharge && nCol == 2)
			pItemMetrics->clrBackground = RGB(235, 235, 255);
		//else
		//	pItemMetrics->clrBackground = RGB(255, 255, 255);

		if(m_bDamaCharge && nCol == 3)
			pItemMetrics->clrBackground = RGB(235, 235, 255);
		//else
		//	pItemMetrics->clrBackground = RGB(255, 255, 255);

		if(m_bBonggoCharge && nCol == 4)
			pItemMetrics->clrBackground = RGB(235, 235, 255);
		//else
		//	pItemMetrics->clrBackground = RGB(255, 255, 255);

		if(m_bTruckCharge && nCol == 5)
			pItemMetrics->clrBackground = RGB(235, 235, 255);

		if(m_bSubWayCharge && nCol == 6)
			pItemMetrics->clrBackground = RGB(235, 235, 255);
		//else
		//	pItemMetrics->clrBackground = RGB(255, 255, 255);
	}

	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	CChargeDongDlg2 *m_pChargeDongDlg;
	void SetChargeDong(CChargeDongDlg2 *pDongDlg){m_pChargeDongDlg = pDongDlg;};
};

typedef map<long,CDetailDestChargeRecord*> DEST_RECORD_MAP;
typedef vector<CDetailDestChargeRecord*> DEST_RECORD_VEC;
//
//class CPaintManager24 : public CMyReportPaintManager
//{
//public:
//
//	void DrawItemCaption(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, 
//		XTP_GRIDRECORDITEM_METRICS* pMetrics)
//	{		
//		int nCol = pDrawArgs->pColumn->GetIndex();
//		int nRow = pDrawArgs->pRow->GetIndex();
//		CString strText = pMetrics->strText; 
//		CRect rc = pDrawArgs->rcItem;
//		CDC *pDC = pDrawArgs->pDC;
//		char buffer[20];
//
//		CDetailDestChargeRecord *pRecord = (CDetailDestChargeRecord*)pDrawArgs->pRow->GetRecord();
//
//		if(pRecord == NULL) return;
//
//		CString sText = pMetrics->strText;
//		
//		if(nCol == 2)
//			sText = itoa(pRecord->m_nGeneralMoto, buffer, 10);
//		else if(nCol == 3)
//			sText = itoa(pRecord->m_nSpecificMoto, buffer, 10);
//		else if(nCol == 4)
//			sText = itoa(pRecord->m_nGeneralDama, buffer, 10);
//		else if(nCol == 5)
//			sText = itoa(pRecord->m_nSpecificDama, buffer, 10);
//
//		pDC->DrawText(sText, rc, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
//	} //DrawItemCaption 끝
//
//};


class CChargeDongDlg2 : public CXTResizeDialog
{
	DECLARE_DYNAMIC(CChargeDongDlg2)

public:
	CChargeDongDlg2(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChargeDongDlg2();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHARGE_DONG_DLG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void InitControl(void);
	int GetType(CDetailChargeRecord *pStartRecord, CDetailDestChargeRecord *pDestRecord);
	virtual BOOL OnInitDialog();
	void SetCharge(long nDestID, int nCol, long nCharge);
	
	
	void ChargeAllDelete();
	void SetAllCharge(long nID, long nCharge);
	void SetAllCharge(long nDestID, long nMotoCharge, long nDamaCharge, long nRaboCharge, long nSpecificMoto, long nSpecificDama, long nSubWayCharge);

	BOOL IsUpdateOk();
	
	BOOL CheckAreaSelect();
	void ChargeTypeNameRefresh();
	void CopyDongDlg();
	void OnViewListPrint();
	void SaveCharge(BOOL bClick);
	void RefreshList();
	void  SetHTypeViewMode(BOOL bTRUE,long nMemCNo, CString sMemName);
	BOOL IsHTypeViewMode();
	long	GetHTypeCNo();
	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnReportStartItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportDestItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportStartItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportDestItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportBeginEdit(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportValueChanged(NMHDR*  pNotifyStruct, LRESULT* /*result*/);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnBnClickedDeleteBtn();
	afx_msg void OnBnClickedEditBtn();
	afx_msg void OnCbnSelchangeDisComCombo();	
	afx_msg void OnBnClickedGeneralDamaCheck();
	afx_msg void OnBnClickedAllDelCheck();
	afx_msg void OnBnClickedDiscountCompanyBtn();
	afx_msg void OnViewExcel();
	afx_msg void OnBnClickedLineBtn();
	afx_msg void OnCbnSelchangeCompanyCombo();
	afx_msg void OnCbnSelchangeChargeTypeCombo();
	afx_msg void OnBnClickedChargeTypeBtn();
	afx_msg void OnBnClickedCopyDongBtn();
	afx_msg void OnBnClickedDiscountCompanyDelBtn();
	afx_msg void OnBnClickedSearchGroupBtn();
	afx_msg void OnBnClickedSameCheckBtn();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedSelectareaMemoryBtn();
	afx_msg void OnBnClickedSameViewBtn();
	afx_msg void OnBnClickedChargeListBtn();
	afx_msg void OnBnClickedSaveBtn();
	afx_msg void OnBnClickedSearchSaveBtn();
	afx_msg void OnBnClickedUserBtn();

	CChargeWorkDlg *m_pChargeWorkDlg;
	CChargeDongSettingDlg *m_pChargeDongSettingDlg;
	CXTPGridRow *m_pPreSelectRow;
	CDataBox m_lstStart;
	CMyDestReport m_lstDest;
	
	DEST_RECORD_MAP m_pDestRecord;
	DEST_RECORD_VEC m_vecDest;

	BOOL m_bIntegrated;
	BOOL m_bCopyDoc;
	long m_nCompany;
	BOOL m_bHTypeViewMode;
	long m_nMemCNo;
	
	int m_nFirstWork;
	CChargeDongDlg2 *m_CopyDongDlg2;
	CComboBox m_StartSidoCombo;
	CComboBox m_DestSidoCombo;
	CComboBox m_StartGugunCombo;
	CComboBox m_DestGugunCombo;
	CComboBox m_cmbCompany;
	CComboBox m_cmbDiscountCompany;
	CComboBox m_ChargeTypeCmb;

	CComboBox m_cmbSearch[4];

	CButton m_chkShuttle;
	CButton m_chkGeneralMoto;
	CButton m_chkGeneralDama;
	CButton m_chkSpecificMoto;
	CButton m_chkSpecificDama;
	CButton m_chkSubWay;
	CButton m_chkAllDel;
	CButton m_chkNotChargeQuery;
	CButton m_btnSameView;
	
	CButton m_DisCountCompanyBtn;
	CButton m_DisCountCompanyDelBtn;
	CButton m_btnChargeList;
	CButton m_LineBtn;
	CButton m_CopyDongDlgBtn;	
	CButton m_btnSelectAreaMemory;
	CButton m_btnSameChekc;
	CButton m_btnChargeType;
	CButton m_btnSave;
	CButton m_btnEdit;
	CButton m_btnDelete;
	
	CButton m_btnText;

	CMyStatic m_stcBranch;
	CMyStatic m_stcChargeType;
	CMyStatic m_stcGroup;
	CMyStatic m_stcRankEx;

	CButton m_btnChargeTypeRank;
	CButton m_btnSearchGroup;
	CComboBox m_cmbHCustomer;
	CButton m_btnSearchHCustomer;

	CMyStatic m_stcSearch1;
	CMyStatic m_stcSearch2;
	CMyStatic m_stcSearch3;


	void FocusUp(CXTPGridControl *pControl);
	void FocusDown(CXTPGridControl *pControl);
	void FocusLeft(CXTPGridControl *pControl);
	void FocusRight(CXTPGridControl *pControl);
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void OnCancel();
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedTwowayCheck();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CButton m_chkGeneralRabo;

	CEdit m_edtCharge11;
	CEdit m_edtCharge12;
	CEdit m_edtCharge13;
	CEdit m_edtCharge14;
	CEdit m_edtCharge15;
	CEdit m_edtCharge16;
	afx_msg void OnBnClickedGeneralRaboCheck();
};
