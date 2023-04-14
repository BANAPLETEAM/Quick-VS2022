#pragma once

#include "databox.h"
#include "MyReportPaintManager.h"
#include "UserDongPos.h"
#include "ChargeDongButton.h"

class CChargeWorkDlg;
class CChargeDongSettingDlg;

typedef map<long,CMyXTPGridRecord*> DEST_MAP;
typedef vector<CPOIInfo*> POI_INFO_VEC;

class CChargeDongUDlg : public CXTResizeDialog
{
	DECLARE_DYNAMIC(CChargeDongUDlg)

public:
	CChargeDongUDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChargeDongUDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHARGE_DONG_UDLG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDeleteBtn();
	afx_msg void OnBnClickedEditBtn();
	afx_msg void OnCbnSelchangeDisComCombo();	
	afx_msg void OnBnClickedGeneralMotoCheck();
	afx_msg void OnBnClickedGeneralDamaCheck();
	afx_msg void OnBnClickedSpecificMotoCheck();
	afx_msg void OnBnClickedSpecificDamaCheck();
	afx_msg void OnBnClickedAllDelCheck();
	afx_msg void OnBnClickedLineBtn();
	afx_msg void OnBnClickedChargeTypeBtn();
	afx_msg void OnBnClickedCopyDongBtn();
	afx_msg void OnBnClickedSearchGroupBtn();	
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedSelectareaMemoryBtn();
	afx_msg void OnBnClickedChargeListBtn();
	afx_msg void OnLvnBegindragData(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);	
	afx_msg void OnReportNewStartItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	//afx_msg void OnReportSelChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportValueChanged(NMHDR*  pNotifyStruct, LRESULT* /*result*/);
	afx_msg void OnReportBeginEdit(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	//afx_msg void OnReportRequestEdit(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportPREVIEWKEYDOWN(NMHDR* pNMHDR, LRESULT* pResult);	
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnBnClickedSearchSaveBtn();
	afx_msg void OnReportStartItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedDiscountCompanyBtn();
	afx_msg void OnCbnSelchangeCompanyCombo();
	afx_msg void OnCbnSelchangeChargeTypeCombo();
	afx_msg void OnBnClickedDiscountCompanyDelBtn();	
	afx_msg void OnDelBottomPoiCharge();
	afx_msg void OnDelBottomBothPoiCharge();
	afx_msg LONG OnInItDataLoad(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnUserDongPosLoad(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnUserDongPosSave(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnUserDongPosPasteDest(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedUserDongposBtn();
	
	virtual BOOL OnInitDialog();	
	void ChargeTypeNameRefresh();	
	void OnViewListPrint();
	void SaveCharge(BOOL bClick);	
	void LoadDong2(BOOL bUser =FALSE);
	void ChildUnSelect(CXTPGridRow* pRow );
	int InsertFind(CXTPGridRecords* pRecords, CString strWord );	
	void OnLButtonUp(UINT nFlags, CPoint point);
	void GetChild(CMyXTPGridRecord *pRecord, int nDepth);
	void ChildInput(CMyXTPGridRecord* pDelRecord,CMyXTPGridRecord* pNewRecord );
	void UserDongSave(BOOL bServerSave);
	BOOL CheckAreaSelect();
	CString CastString(long nValue);
	void ChildPoiDeleteCharge(CMyXTPGridRecord *pReocrd, BOOL bShuttle);
	void NewRefreshList();
	void NewChargeGeneralAllDelete();	
	void NewSetAllCharge(long nDestID, long nMotoCharge, long nDamaCharge, long nSpecificMoto, long nSpecificDama);	
	void UserDongPosLoad();
	void CopyDongDlg();
	void CopyDestBtn();
	long ServerDataInput(int j, CString sName, CString sAllName, CString sFactPOI, 
		CString sDepth, CString sDongID, CString sPOIID );
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void ChildCount(CMyXTPGridRecord *pReocrd,long &nCount);


	POI_INFO_VEC m_Vec;
	BOOL m_bDragMode;	
	CImageList* m_pDragImage;
	CChargeWorkDlg *m_pChargeWorkDlg;
	CChargeDongSettingDlg *m_pChargeDongSettingDlg;
	CXTPGridRow *m_pPreSelectRow;	
	CDataBox m_lstSet;
	CDataBox  m_lstSetDest;
	DEST_MAP m_mapDest;
	CChargeDongButton m_UserDongButton;
	
	BOOL m_bIntegrated;
	BOOL m_bCopyDoc;
	long m_nCompany;	
	//int m_nFirstWork; 양쪽ㅅ트리 열어서 작업
	CChargeDongUDlg *m_CopyDongDlg2;
	CComboBox m_StartSidoCombo;
	CComboBox m_DestSidoCombo;
	CComboBox m_StartGugunCombo;
	CComboBox m_DestGugunCombo;
	CComboBox m_cmbCompany;
	CComboBox m_cmbDiscountCompany;
	CComboBox m_ChargeTypeCmb;
	CComboBox m_cmbSearch[4];
	CEdit m_ChargeEdit;
	CButton m_chkShuttle;
	CButton m_chkGeneralMoto;
	CButton m_chkGeneralDama;
	CButton m_chkSpecificMoto;
	CButton m_chkSpecificDama;
	CButton m_chkAllDel;
	CButton m_chkNotChargeQuery;
	//CButton m_btnSameView;	
	CButton m_DisCountCompanyBtn;
	CButton m_DisCountCompanyDelBtn;
	CButton m_btnChargeList;
	CButton m_LineBtn;
	CButton m_CopyDongDlgBtn;	
	CButton m_btnSelectAreaMemory;
	CButton m_btnSameChekc;
	CButton m_btnChargeType;
	
	CButton m_btnEdit;
	CButton m_btnDelete;
	CMyStatic m_stcServerLoad;
	CMyStatic m_stcServerSave;

	
	

	
	
};
