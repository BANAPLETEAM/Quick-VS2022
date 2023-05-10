#pragma once
#include "afxcmn.h"
//#include "ShareReportTransferDlg.h"
//#include "ShareTransferCancelDlg.h"
//#include "ShareTransferRequestDetailDlg.h"

class CShareReportRateDlg1;
class CBranchReportTransferDlg;

#define ONE_WEEK_AFTER 100


// CShareTranferRequestDlg ��ȭ �����Դϴ�.

class CShareTranferRequestDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CShareTranferRequestDlg)

public:
	CShareTranferRequestDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CShareTranferRequestDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SHARE_TRANSFER_REQUEST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_nWeek;
	int m_nAbilityMoney;
	CListCtrl m_List;
	CString m_sSql;
	CString ReturnString(int nInt);

	CShareReportRateDlg1 * m_pShareReportRateDlg1;
	CBranchReportTransferDlg * m_pBranchReportTransferDlg;

	void ReFresh();
	void FinishRequest(int nReceive, CString sMemo);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawList ( NMHDR* pNMHDR, LRESULT* pResult );
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
};
