#pragma once
#include "afxwin.h"

#include <vector>
#include <set>

// CChargeSimpleListDlg 대화 상자입니다.
typedef vector<CString> vecSido2;
typedef set<CString> setSido;


class CChargeSimpleListDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeSimpleListDlg)

public:
	CChargeSimpleListDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChargeSimpleListDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHARGE_LIST_SIMPLE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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


