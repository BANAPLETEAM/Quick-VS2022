#pragma once
#include "afxdtctl.h"

// CDateSelectDlg 대화 상자입니다.

class CDateSelectDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CDateSelectDlg)

public:
	CDateSelectDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDateSelectDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DATE_SELECT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strTitle;
	BOOL m_bAllocate;
	COleDateTime m_dtLastAllocate;

	COleDateTime m_dtDateTime;

	CDateTimeCtrl m_ctpDt;
	CDateTimeCtrl m_ctpTime;
	COleDateTime m_dtDate;
	COleDateTime m_dtTime;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
};
