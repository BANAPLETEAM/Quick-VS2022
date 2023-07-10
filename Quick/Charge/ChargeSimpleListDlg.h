#pragma once
#include "afxwin.h"

#include <vector>
#include <set>

// CChargeSimpleListDlg ��ȭ �����Դϴ�.
typedef vector<CString> vecSido2;
typedef set<CString> setSido;


class CChargeSimpleListDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeSimpleListDlg)

public:
	CChargeSimpleListDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CChargeSimpleListDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CHARGE_LIST_SIMPLE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

	
	
	CButton m_btnDongInput;
	CButton m_btnDongOutput;
	CEdit m_edtDong;
	//CEdit m_edtNickName;
	CEdit m_edtDongDetail;
	CXTPListCtrl2 m_RegisterDongList;
	CXTPListCtrl2 m_DongList;
	
	setSido m_setSido;
	setSido m_setSaveSido;
	
	long m_nDongID;
	

public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedDongInputBtn();
	afx_msg void OnBnClickedDongOutBtn();
	afx_msg void OnBnClickedSaveBtn();
	void RefreshSaveList();
	void RefreshList();
	void Compare(CStringArray &sArr);
	
	long m_nCompany;
	BOOL m_bChargeDongDlg3;

	
};


