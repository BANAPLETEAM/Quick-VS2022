#pragma once
#include "afxdtctl.h"


// CWorkTimeDlg 대화 상자입니다.

class CWorkTimeDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CWorkTimeDlg)

public:
	CWorkTimeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CWorkTimeDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_WORK_TIME_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	COleDateTime m_dtStartTime;
	COleDateTime m_dtEndTime;
	afx_msg void OnBnClickedCancel();
};
