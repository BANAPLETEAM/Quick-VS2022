#pragma once
#include "afxwin.h"

#include "BranchSel.h"
#include "XTPListCtrl_Branch.h"
// CTransferSmsBetweenShareBalanceDlg 대화 상자입니다.

class  CTransferSmsBetweenShareBalanceDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CTransferSmsBetweenShareBalanceDlg)

public:
	CTransferSmsBetweenShareBalanceDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTransferSmsBetweenShareBalanceDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_TRANSFER_SMS_BETWEEN_SHARE_BALANCE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
public:
	CXTPListCtrl2 m_lstBranch;

	CFlatEdit2 m_edtSearchBranch;

	CFlatEdit2 m_edtMinusShare;
	CFlatEdit2 m_edtPlusSms;
	CFlatEdit2 m_edtMinusSms;
	CFlatEdit2 m_edtPlusShare;

	CFlatEdit2 m_edtPlusSmsCharge;
	CFlatEdit2 m_edtPlusShareBalanceCharge;

	CMyStatic m_stc1;
	CMyStatic m_stc2;
	CMyStatic m_stc3;
	CMyStatic m_stc4;
	CMyStatic m_stc5;
	CMyStatic m_stc6;

	CMyStatic m_stcDraw1;
	CMyStatic m_stcDraw2;

	BOOL m_bDragMode;
	BOOL m_bOnlyOneSite;

	long m_nMinusShareBalance;
	long m_nPlusShareBalance;
	long m_nMinusBasicShareRate;
	long m_nPlusBasicShareRate;
	long m_nMinusSms;
	long m_nPlusSms;
	long m_nMinusShareBalanceCompany;
	long m_nPlusShareBalanceCompany;
	long m_nMinusSmsCompany;
	long m_nPlusSmsCompany;

	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/);
	afx_msg void OnEnChangePlusSmsChargeEdit();
	afx_msg void OnEnChangePlusShareBalanceChargeEdit();
	afx_msg void OnBnClickedTransferToSmsBtn();
	afx_msg void OnBnClickedTransferToShareBalanceBtn();
	afx_msg void OnBnClickedCloseBtn();
	afx_msg void OnBnClickedShowLogBtn();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);

	long GetSelCompany();
	afx_msg void OnToMinusShareBalance();
	afx_msg void OnToPlusSms();
	afx_msg void OnToMinusSms();
	afx_msg void OnToPlusShareBalance();
	afx_msg void OnEnChangeSearchBranchEdit();

	void CheckSmsBalance(UINT flag, long nCompany, BOOL bMsgBox = TRUE);
	void CheckShareBalance(UINT flag, long nCompany, BOOL bMsgBox = TRUE);
	long DrawStcText(CDC *pDC, COLORREF rgbText, CString strDisplay, CRect rc, CFont *font);
	void DrawToSmsCharge(CDC *pDC);
	void DrawToShareBalanceCharge(CDC *pDC);
};
