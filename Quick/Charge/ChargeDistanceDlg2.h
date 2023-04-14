#pragma once

#include "databox.h"
#include "afxwin.h"
#include "BranchSel.h"
#include "MyStatic.h"
#include "MyButton.h"
// CChargeDistanceDlg2 대화 상자입니다.

class CMyResizeDialog;
class CChargeWorkDlg;
class CChargeDongExDlg;

class CDetailDistanceDestChargeRecord2;
class CMyDestReport3;

typedef map<long,CDetailDistanceDestChargeRecord2*> DEST_RECORD_MAP3;
typedef vector<CDetailDistanceDestChargeRecord2*> DEST_RECORD_VEC3;


#define EX_CHARGE_TYPE_LI 0
#define EX_CHARGE_TYPE_LOGI 1
#define EX_CHARGE_TYPE_CUSTOM 2
#define EX_CHARGE_TYPE_ALL 3

#define A_TYPE	0
#define B_TYPE	1
#define C_TYPE	2
#define D_TYPE	3

#define COL_BIKE 2
#define COL_SEDAN 3
#define COL_DAMA 4
#define COL_LABO 5
#define COL_TRUCK 6

class CDetailDistanceChargeRecord2 : public CXTPGridRecord
{
protected:


public:
	CDetailDistanceChargeRecord2(long nID,BOOL bHasNotDong, int nClass, CString sArea,   CString sDong)
	{
		m_nID = nID;
		m_bHasNotDong = bHasNotDong;
		m_nClass = nClass;
		m_bDirtyFlag = FALSE;
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
		else if(m_nClass == 20)
			return -1;
		else
			return 0;
	}

	BOOL GetDirtyFlag() { return m_bDirtyFlag; }
	void SetDirtyFlag() { m_bDirtyFlag = TRUE;}


protected:
	BOOL m_bDirtyFlag;
	BOOL m_bHasNotDong;
	

public:
	long m_nID;	
	int m_nClass;
};



#define  KM_PER 2

class CDetailDistanceDestChargeRecord2 : public CXTPGridRecord
{

public:
	CDetailDistanceDestChargeRecord2(long nID, BOOL bHasNotDong, int nClass, CString sArea, CString sDong)
	{
		m_nID = nID;
		m_bHasNotDong = bHasNotDong;
		m_nClass = nClass;

		AddItem(new CXTPGridRecordItemText(sArea));
		AddItem(new CXTPGridRecordItemText(sDong));		
		AddItem(new CXTPGridRecordItemText(""));		
		AddItem(new CXTPGridRecordItemText(""));		
		AddItem(new CXTPGridRecordItemText(""));		
		AddItem(new CXTPGridRecordItemText(""));		
		AddItem(new CXTPGridRecordItemText(""));		
	}

	void CDetailDistanceDestChargeRecord2::ChangeValue(int car_type, CString caption)
	{
		int col = -1;
		if(car_type == CAR_AUTO) col = COL_BIKE;
		else if(car_type == CAR_SEDAN) col = COL_SEDAN;
		else if(car_type == CAR_DAMA) col = COL_DAMA;
		else if(car_type == CAR_LABO) col = COL_LABO;
		else if(car_type == CAR_TRUCK) col = COL_TRUCK;
		else
			return;

		GetItem(col)->SetCaption(caption);
	}

	void CDetailDistanceDestChargeRecord2::ChangeClear()
	{
		GetItem(COL_BIKE)->SetCaption("");
		GetItem(COL_SEDAN)->SetCaption("");
		GetItem(COL_DAMA)->SetCaption("");
		GetItem(COL_LABO)->SetCaption("");
		GetItem(COL_TRUCK)->SetCaption("");
	}


	int GetTypeInfo()
	{
		if(m_nClass == 10 && m_bHasNotDong)
			return 3;
		else if(m_nClass == 10 && m_bHasNotDong == FALSE)
			return 2;
		else if(m_nClass != 10)
			return 1;
		else if(m_nClass == 20 )
			return -1;
		else
			return 0;
	}	

protected:
	BOOL m_bHasNotDong;

public:
	long m_nID;		
	int		m_nClass;
};


class CMyDestReport3 : public CDataBox
{
public:
	CMyDestReport3()
	{
		
		m_bA = FALSE;
		m_bB = FALSE;
		m_bC = FALSE;
		m_bD = FALSE;
		m_bE = FALSE;
		m_pvecDest = NULL;

	};   // 표준 생성자입니다.
	virtual ~CMyDestReport3(){};
	//int niValue;
	
	BOOL m_bA;
	BOOL m_bB;
	BOOL m_bC;
	BOOL m_bD;
	BOOL m_bE;

	DEST_RECORD_VEC3 * m_pvecDest;
	

	void SetVectorDest(DEST_RECORD_VEC3  &vecDest)
	{
		m_pvecDest = &vecDest;
	}

	virtual void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
	{

		CDetailDistanceDestChargeRecord2 *pRecord = (CDetailDistanceDestChargeRecord2 *)pDrawArgs->pRow->GetRecord();
		int nRow = pRecord->GetIndex();
		int nCol = pDrawArgs->pColumn->GetItemIndex();
		
		if(m_bA && nCol == 2)
			pItemMetrics->clrBackground = RGB(235, 235, 255);	

		if(m_bB && nCol == 3)
			pItemMetrics->clrBackground = RGB(235, 235, 255);

		if(m_bC && nCol == 4)
			pItemMetrics->clrBackground = RGB(235, 235, 255);	

		if(m_bD && nCol == 5)
			pItemMetrics->clrBackground = RGB(235, 235, 255);

		if(m_bE && nCol == 6)
			pItemMetrics->clrBackground = RGB(235, 235, 255);
	}
};


class CChargeDistanceDlg2 : public CMyResizeDialog
{
	DECLARE_DYNAMIC(CChargeDistanceDlg2)

public:
	CChargeDistanceDlg2(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChargeDistanceDlg2();

	// 대화 상자 데이터입니다.
	//enum { IDD = IDD_XTP_CHARGEDISTANCE_DLG };
	enum { IDD = IDD_CHARGE_DISTANCE_DLG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnReportStartItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportDestItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);

	void SetCompany(long nCompany);
	void InitControl(void);
	int GetType(CDetailDistanceChargeRecord2 *pStartRecord, CDetailDistanceDestChargeRecord2 *pDestRecord);
	virtual BOOL OnInitDialog();
	void ChargeAllDelete();
	void SetAllCharge(int dest_id, int car_type, int amount_type);
	BOOL CheckAreaSelect();
	LONG OnChangeBrachCode(WPARAM wParam, LPARAM lParam);

	afx_msg void OnSize(UINT nType, int cx, int cy);

	CChargeWorkDlg *m_pChargeWorkDlg;

	CDataBox  m_lstStart;
	CMyDestReport3 m_lstDest;

	DEST_RECORD_MAP3 m_pDestRecord;
	DEST_RECORD_VEC3 m_vecDest;

	BOOL m_bIntegrated;
	BOOL m_bCopyDoc;
	long m_nCompany;
	//CComboBox m_cmbCompany;
	CString m_sCompany;

	CChargeDistanceDlg2 *m_CopyDongDlg2;
	CComboBox m_StartSidoCombo;
	CComboBox m_DestSidoCombo;
	//afx_msg void OnCbnSelchangeStartSidoCombo();
	//afx_msg void OnCbnSelchangeDestSidoCombo();
	//afx_msg void OnCbnSelchangeStartGugunCombo();
	//afx_msg void OnCbnSelchangeDestGugunCombo();
	CComboBox m_StartGugunCombo;
	CComboBox m_DestGugunCombo;
	CButton m_chkShuttle;
	
	CButton m_chkA;
	CButton m_chkB;
	CButton m_chkC;
	CButton m_chkD;
	CButton m_chkE;

	
	CMyStatic	m_stcABCD;
	CComboBox m_cmbABCDType;
	CFlatMainEdit m_edtMain;
	CFlatSubEdit m_edtSub;
	CBranchMainBtn m_btnMain;
	CBranchSubBtn m_btnSub;
	CBranchSel m_cBranch;
	CMyStatic m_stcEx1;
	CMyStatic m_stcEx2;
	CMyStatic m_stcEx3;
	CMyStatic m_stcBranch;
	
	afx_msg void OnBnClickedDeleteBtn();	
	afx_msg void OnBnClickedGeneralMotoCheck();
	afx_msg void OnBnClickedGeneralDamaCheck();
	afx_msg void OnBnClickedGeneralLaboCheck();
	             
	afx_msg void OnBnClickedGeneralBanCheck();
	afx_msg void OnBnClickedGeneralTruckCheck();
	afx_msg void OnCbnSelchangeCompanyCombo();
	afx_msg void OnBnClickedCopyDongBtn();
	afx_msg void OnBnClickedTypeEditBtn();
	afx_msg void OnBnClickedTypeSettingBtn();
	
	afx_msg void OnBnClickedAllDelCheck();
	CMyButton m_CopyDongDlgBtn;
	CComboBox m_cmbTypeNameCombo2;
	CButton m_chkAllDel;
	CMyButton m_btnTypeSetting;
	CMyButton m_btnTypeSettingTruck;
	void RefreshList();
	void SetTypeRefresh();
	BOOL ChargeLinkUpdate();
	void CarORABCDTypeChangeRefesh();
	
	afx_msg void OnCbnSelchangeAbcdTypeCombo();


	map<int, CString> charge_type_map_;
	afx_msg void OnBnClickedTypeSettingTruckBtn();
	void OpenChargeDistanceTypeDlg(BOOL bTruck);
	int GetAmountType();
};
