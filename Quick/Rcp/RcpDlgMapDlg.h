#pragma once


// CRcpDlgMapDlg ��ȭ �����Դϴ�.

#include "SimpleMapDlg.h"

class CRcpDlg;

class CRcpDlgMapDlg : public CSimpleMapDlg
{
	DECLARE_DYNAMIC(CRcpDlgMapDlg)

public:
	CRcpDlgMapDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRcpDlgMapDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RCP_DLG_MAP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedRcpcloseCheck();
	afx_msg void OnBnClickedSetOrderAddressBtn();
	afx_msg void OnBnClickedSetStartAddressBtn();
	afx_msg void OnBnClickedSetDestAddressBtn();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

	CRcpDlg *m_pRcpDlg;
	CButton m_chkRcpClose;
public:
	BOOL m_bFromCustomerDlg;
	void SetParentRcpDlg(CRcpDlg *pRcpDlg) { m_pRcpDlg = pRcpDlg; }
	void SetPlaceAddress(CRcpPlaceInfo *pPlace);

};
