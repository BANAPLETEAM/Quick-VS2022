#pragma once

#include "NewMsgDlg.h"
// CQueryChargeDlg 대화 상자입니다.

class CQueryChargeDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CQueryChargeDlg)

public:
	CQueryChargeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CQueryChargeDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_QUERY_CHARGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CEdit m_edtCharge;
	CEdit m_edtEtc;

	long m_nMNo;
    CString m_strCharge;
	CString m_strEtc;

	CString m_strCustomer;
	CString m_strStart;
	CString m_strStartDong;
	CString m_strDest;
	CString m_strDestDong;

	BOOL m_bChargeSave;
	CNewMsgDlg *m_pNewMsgDlg;
	CString m_strUniqueID;
	CString m_strOP;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCancel();
	void SaveLocation();
};
