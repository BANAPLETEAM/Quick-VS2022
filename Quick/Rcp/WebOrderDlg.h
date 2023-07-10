#pragma once


// CWebOrderDlg 대화 상자입니다.

class CWebOrderDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CWebOrderDlg)

public:
	CWebOrderDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CWebOrderDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_WEBORDER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	CDateButton m_DateBtn;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRefreshBtn();
	COleDateTime m_dtFrom;
	COleDateTime  m_dtTo;
	CDateTimeCtrl m_From;
	CDateTimeCtrl  m_To;
	void RefreshList();
	CXTPListCtrl2 m_List;
	CEdit m_edtEtc;
	
	CButton m_chkAll;
	afx_msg void OnBnClickedDateBtn();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedReceiptBtn();
	

	void ChangItemState(int nType);
	afx_msg void OnBnClickedReBtn();
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnBnClickedProcessBtn();
	afx_msg void OnBnClickedEndBtn();
	long m_nWebID;
	afx_msg void OnBnClickedEtcModifyBtn();
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * result);
	
};
