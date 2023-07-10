#pragma once
#include "afxwin.h"


// CChargeListSetDlg ��ȭ �����Դϴ�.

class CChargeListSetDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeListSetDlg)

public:
	CChargeListSetDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CChargeListSetDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CHARGE_LIST_SET_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	CComboBox m_cmbChargeList;
	CButton m_btnNewList;
	CButton m_btnDelList;
	CButton m_btnCopyList;
	CButton m_btnNicNameInput;
	CButton m_btnDongInput;
	CButton m_btnDongOutput;
	CEdit m_edtDong;
	CEdit m_edtNickName;
	CEdit m_edtDongDetail;
	CXTPListCtrl2 m_RegisterDongList;
	CXTPListCtrl2 m_DongList;
	CPOIUnit *m_pDongPoi;
	long m_nDongID;

public:
	virtual BOOL OnInitDialog();
	
	afx_msg void OnBnClickedDongInputBtn();
	afx_msg void OnCbnSelchangeChargelistCombo();
	afx_msg void OnBnClickedDongOutBtn();
	afx_msg void OnBnClickedNicknameInputBtn();	
	afx_msg void OnBnClickedChargelistNewBtn();
	afx_msg void OnBnClickedChargelistDelBtn();
	afx_msg void OnBnClickedChargelistCopyBtn();

	void MakeColumn();
	void RefreshLegalDong();
	void ChargeListInputCommbo();

	
	afx_msg void OnBnClickedChargelistRefreshBtn();
};
