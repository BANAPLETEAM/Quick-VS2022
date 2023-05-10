#pragma once
#include "afxwin.h"


// CAddPhoneDlg 대화 상자입니다.

class CAddPhoneDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddPhoneDlg)

public:
	CAddPhoneDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAddPhoneDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ADD_PHONE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	long m_nTelID;
	long m_nCompany;
	long m_nCNo;
	afx_msg void OnBnClickedSaveBtn();
	afx_msg void OnBnClickedCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	void RefreshPhoneInfo();

	BOOL CheckItem();

	BOOL InsertPhone();
	BOOL UpdatePhone();

	CEdit m_edtID;
	CEdit m_edtPhone;
	CEdit m_edtEnter;
	CEdit m_edtDepart;
	CEdit m_edtManager;
	CEdit m_edtEtc;
	CMyStaticTri m_stcID;
	CMyStaticTri m_stcPhone;
	CMyStaticTri m_stcDepart;
	CMyStaticTri m_stcEtc;
	CMyStaticTri m_stcEnter;
	CMyStaticTri m_stcManager;
};
