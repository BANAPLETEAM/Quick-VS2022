#pragma once
#include "afxwin.h"


class CChargeListRecord : public CXTPGridRecord
{
public:
	CChargeListRecord(CString group_name, CString dept, CString charge_name, int gno, int gno_key)
	{
		AddItem(new CXTPGridRecordItemText(group_name));
		AddItem(new CXTPGridRecordItemText(dept));
		AddItem(new CXTPGridRecordItemText(charge_name));

		gno_ = gno;
		gno_key_ = gno_key;
	}

	int GetGNo() { return gno_; }
	int GetGNoKey() { return gno_key_; }

	int gno_ = 0;
	int gno_key_ = 0;
};

// CChargeListDlg ��ȭ �����Դϴ�.

class CChargeListDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeListDlg)

public:
	CChargeListDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CChargeListDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CHARGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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

	CXTPListCtrl2 m_lstGroupList;
	CXTPListCtrl2 m_lstChargeList;
	CXTPListCtrl2 m_lstAllGroupList;
	CXTPListCtrl2 m_lstRegisterChargeList;

	CFlatEdit2 m_edtSearchChargeWord;
	CFlatEdit2 m_edtSearchGroup;

	CComboBox m_cmbType;

	CButton m_chkRegisterView;
	CButton m_chkTwoWay;

	long m_nCompany;
};
