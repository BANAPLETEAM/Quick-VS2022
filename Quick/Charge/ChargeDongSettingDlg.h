#pragma once

#include "afxwin.h"

class CChargeDongDlg2;


class CChargeDongSettingDlg :  public CXTResizeDialog
{
	DECLARE_DYNAMIC(CChargeDongSettingDlg)

public:
	CChargeDongSettingDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChargeDongSettingDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHARGE_SETTING_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	CXTPListCtrl2 m_lstSectionName;
	CXTPListCtrl2 m_lstStart;
	CXTPListCtrl2 m_lstDest;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void RefreshSection();

	afx_msg void OnBnClickedStartBillBtn();
	afx_msg void OnReportSectionNameItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedBonggoCheck();
	afx_msg void OnBnClickedTruckCheck();
	afx_msg void OnBnClickedStartdestDelBtn();
	afx_msg void OnBnClickedDestBillBtn();
	afx_msg void OnBnClickedStartListDelBtn();
	afx_msg void OnBnClickedDestListDelBtn();
	afx_msg void OnBnClickedSaveBtn();
	afx_msg void OnBnClickedSaveBtn2();	
	afx_msg void OnBnClickedMotoCheck();
	afx_msg void OnBnClickedSaveAmountBtn();	
	afx_msg void OnBnClickedDamaCheck();
	afx_msg void OnBnClickedStartdestBrinngBtn();
	afx_msg void OnBnClickedStartdestSaveBtn();	
	afx_msg void OnBnClickedNewAreaBtn();
	afx_msg void OnBnClickedDeleteAreaBtn();
	afx_msg void OnBnClickedServerRefrshBtn();
	afx_msg void OnBnClickedSetChargeDongBtn();	
	afx_msg void OnBnClickedSearchGroupBtn();
	afx_msg void OnBnClickedSearchGroupRefreshBtn();
	afx_msg void OnBnClickedStartBillBtnServer();
	afx_msg void OnBnClickedDestBillBtnServer();
	afx_msg void OnBnClickedStartListDelBtnServer();
	afx_msg void OnBnClickedDestListDelBtnServer();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClose();
	afx_msg void OnCbnSelchangeCompanyCombo();

	void RefreshRegisterStartArea(long nChargeAreID);
	void RefreshRegisterDestArea(long nChargeAreID);
	void GetDestDongID(BOOL bServer);
	void GetStartDongID(BOOL bServer);	
	void DelDestList(BOOL bServer);
	void DelStartList(BOOL bServer);
	void SaveStartList();
	void SaveDestList();
	void AllStartDestDelList();
	void ChargeTypeNameRefresh();
	int GetType(int nStartType, int nDestType);

	CChargeDongDlg2 * m_pChargeDongDlg;	

	long m_nMoto;
	long m_nDama;
	long m_nBonggo;
	long m_nTruck;
	long m_nCompany;

	CButton m_chkMoto;
	CButton m_chkDama;
	CButton m_chkBonggo;
	CButton m_chkTruck;	

	CFlatEdit2 m_edtMoto;
	CFlatEdit2 m_edtDama;
	CFlatEdit2 m_edtBonggo;
	CFlatEdit2 m_edtTruck;	

	CComboBox m_cmbDiscountCompany;
	CComboBox m_cmbChargeType;
	CComboBox m_cmbCompany;

	CButton m_btnServerRefreshSection;
	CButton m_btnNewArea;
	CButton m_btnDeleteArea;
	CButton m_btnStartSave;
	CButton m_btnDestSave;
	CButton m_btnSaveAmount;
	CButton m_btnStartBillServerSave;
	CButton m_btnStartListDelServerSave;
	CButton m_btnDestBillServerSave;
	CButton m_btnDestListDelServerSave;
	CButton m_btnStartDestServerSave;
	CButton m_chkShuttle;
};
