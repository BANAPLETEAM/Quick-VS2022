#pragma once
#include "afxwin.h"
#include "DataBox.h"

// CChargeListDlg 대화 상자입니다.

class CChargeListDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeListDlg)

public:
	CChargeListDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChargeListDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHARGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAllChargeBtn();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeSearchChargeEdit();
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);	
	afx_msg void OnBnClickedChargeNameModifyBtn();
	afx_msg void OnBnClickedChargeNameNewBtn();
	afx_msg void OnBnClickedChargeTypenameInputBtn();
	afx_msg void OnBnClickedChargeTypenameDelBtn();
	afx_msg void OnEnChangeSearchGroupEdit();
	afx_msg void OnBnClickedModifyChargeBtn();
	afx_msg void OnBnClickedExcelBtn();
	afx_msg void OnBnClickedChargeWindowBtn();
	afx_msg void OnBnClickedChargeDeleteBtn();

	virtual BOOL OnInitDialog();
	void RefreshList();
	void ChargeGroupModify(int nRow);
	void RegisterGroupView();
	void RegisterChargeView();
	void AllGroupRefresh();

	CDataBox m_lstGroupList;
	CDataBox m_lstChargeList;
	CDataBox m_lstAllGroupList;
	CDataBox m_lstRegisterChargeList;

	CFlatEdit2 m_edtSearchChargeWord;
	CFlatEdit2 m_edtSearchGroup;

	CComboBox m_cmbType;

	CButton m_chkRegisterView;
	CButton m_chkTwoWay;

	long m_nCompany;
};
