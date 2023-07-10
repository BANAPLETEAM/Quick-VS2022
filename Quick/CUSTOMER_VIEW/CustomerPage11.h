#pragma once


#include "BtnST.h"

class CAddGroupMemberDlg;
class CCustomerPage11;


class CGroupWorkButton : public CButtonST
{

	//DECLARE_DYNAMIC(CGroupWorkButton)

public:
	CGroupWorkButton();
	virtual ~CGroupWorkButton();

protected:
	DECLARE_MESSAGE_MAP()

	//CRcpDlg *m_pRcpDlg;

public:
	//{{AFX_MSG
	afx_msg LRESULT On_MenuCallback(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMenuGroupTop();
	afx_msg void OnMenuAddGroup();
	afx_msg void OnMenuDeleteGroup();
	afx_msg void OnMenuUpdateGroup();	
	afx_msg void OnMenuMoveGroup();
	//}}AFX_MSG
	CCustomerPage11 *m_pWnd;
	void InitButton();

};


class CCustomerPage11 : public CMyFormView
{
	DECLARE_DYNCREATE(CCustomerPage11)

protected:
	CCustomerPage11();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CCustomerPage11();

public:
	enum { IDD = IDD_CUSTOMER_PAGE11 };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnDeleteCustomer();
	afx_msg void OnAddGroupTop();
	afx_msg void OnAddGroup();
	afx_msg void OnDeleteGroup();
	afx_msg void OnUpdateGroup();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnBnClickedNewChargeDlg();
	afx_msg void OnBnClickedDeleteChargeDlg2();
	afx_msg void OnBnClickedSaveBtn();
	afx_msg void OnBnClickedSearchCustomerBtn();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCbnSelchangeReportSecondDayCombo();
	afx_msg void OnCbnSelchangeReportFirstDayCombo();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedGroupChargeBtn();
	afx_msg void OnBnClickedChargeTypeSearchBtn();
	afx_msg void OnMoveGroup();
	afx_msg void OnBnClickedGroupSettingBtn();
	afx_msg void OnViewExcel();
	afx_msg void OnBnClickedBatchchargeTypeSearchBtn();
	afx_msg void OnBnClickedChargetypenameBatchBtn();

	afx_msg void OnSetReleaseGroupOwner();
	afx_msg void OnSetGroupOwner();

	BOOL FindRecord(CXTPGridRecord *pRecord, CString strSearchWord);
	void AllRecordShow(CXTPGridRecord *pRecord);
	void RefreshList();
	virtual void OnInitialUpdate();
	void ChargeTypeNameRefresh();
	void OnReportItemChange(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	void OnCustomerReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	void RefreshCustomerList();
	void AddGroupMember();
	void CheckCombo();
	void RefreshListCheck();
	void MakeListTree(long nGNo, VEC_CUSTOMER_GROUP::iterator it);
	void ChangeGroupInfo();
	long GetComboData(long nCharge);
	static void OpenCustomerDlgByCNo(long nCNo);

	long m_nGNo;

	CFlatEdit2 m_edtGroupName;
	CFlatEdit2 m_edtDept;
	CFlatEdit2 m_edtName;
	CFlatEdit2 m_edtEMail;
	CFlatEdit2 m_edtID;
	CFlatEdit2 m_edtPwd;
	CFlatEdit2 m_edtMemberTel;
	CFlatEdit2 m_edtRiderDeposit;
	CFlatEdit2 m_edtDetail;
	CFlatEdit2 m_edtPresident;
	CFlatEdit2 m_edtBussinessNo;
	CFlatEdit2 m_edtBussnessStatus;
	CFlatEdit2 m_edtBusinessCategory;
	CFlatEdit2 m_edtCompanyArea;
	CFlatEdit2 m_edtSearchGroupName;
	CFlatEdit2 m_edtDiscount;
	CFlatEdit2 m_edtManagerSearch;

	CButton m_chkCorporationCharge;
	CButton m_chkPartAll;
	CButton m_chkNotShowCash;
	CStatic m_stcGroupNumber;

	CComboBox m_cmbReportFirstDay;
	CComboBox m_cmbReportSecondDay;
	CComboBox m_cmbChargeTypeName;
	CComboBox m_cmbBatchChargeTypeName;

	CXTPListCtrl2 m_lstGroup;
	CCustomerGroupList m_lstCustomer;

	CGroupWorkButton m_btnGroupWork;
	CAddGroupMemberDlg *m_pAddGroupMemberDlg;
	ST_CUSTOMER_GROUP_INFOMATION* GetViewGroupData(ST_CUSTOMER_GROUP_INFOMATION *pData);
	
	CButton m_chkCredit;
	CButton m_chkCashOption;
	CButton m_chkCreditOption;
	CButton m_chkActiveOption;
	CButton m_chkUnActiveOption;
	afx_msg void OnEnChangeManagerSearchEdit();
};


