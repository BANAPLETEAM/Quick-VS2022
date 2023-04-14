#pragma once

// CSMSStateDlg 대화 상자입니다.

class CSMSStateDlg : public CMyDialog
{
	DECLARE_DYNCREATE(CSMSStateDlg)

public:
	CSMSStateDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSMSStateDlg();
	// 재정의


	// 대화 상자 데이터입니다.
	enum { IDD = IDD_SMSSTATE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	void RefreshList();

	CString GetSMSStateString(long nCount);
	DECLARE_MESSAGE_MAP()

public:
	CListCtrl m_List;
	CStatic m_dtChange;
	afx_msg void OnBnClickedSelectBtn();
	COleDateTime GetSelectTime();
	COleDateTime m_dtCur;
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
