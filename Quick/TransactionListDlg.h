#pragma once
#include "Quick.h"
#include "Explorer.h"

// CTransactionListDlg ��ȭ �����Դϴ�.

class CTransactionListDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CTransactionListDlg)

public:
	CTransactionListDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTransactionListDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TRANSACTIONLIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
