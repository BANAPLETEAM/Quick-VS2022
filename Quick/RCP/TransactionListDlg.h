#pragma once
#include "Quick.h"
#include "Explorer.h"

// CTransactionListDlg 대화 상자입니다.

class CTransactionListDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CTransactionListDlg)

public:
	CTransactionListDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTransactionListDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TRANSACTIONLIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedTaxDrawBtn();
	afx_msg void OnBnClickedCertificationRegisterBtn();
	afx_msg void OnBnClickedCancelBtn();

	void BillDraw();
	void TransactionList();
	CExplorer m_Explorer;
	HRESULT GetPostData(CString strKey, LPVARIANT pvPostData);
	
public:
	long m_nBillID;
	CString m_sTNoList;
	long m_nCorporationID;
	int m_nType;
	CButton m_chkPrint;
	BOOL m_bBillView;
	CButton m_btnTaxDraw;
	long m_nCompany;
};
