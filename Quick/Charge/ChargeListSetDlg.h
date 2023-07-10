#pragma once
#include "afxwin.h"


// CChargeListSetDlg 대화 상자입니다.

class CChargeListSetDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeListSetDlg)

public:
	CChargeListSetDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChargeListSetDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHARGE_LIST_SET_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
