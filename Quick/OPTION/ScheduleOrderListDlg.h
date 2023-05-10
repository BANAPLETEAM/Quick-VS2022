#pragma once

class CScheduleOrderListDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CScheduleOrderListDlg)

public:
	CScheduleOrderListDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CScheduleOrderListDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_SCHEDULE_ORDER_LIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

protected:
	CXTPListCtrl2 m_List;
	CXTFlatEdit m_edtSearch;
	CString m_strSearch;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeXtplistctrlCombo();
	afx_msg void OnEnChangeXtplistctrlEdit();
	afx_msg void OnNMDblClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAddBtn();
	afx_msg void OnBnClickedMakeOrderJustBtn();
	afx_msg void OnBnClickedEditOrderBtn();
	afx_msg void OnBnClickedDeleteBtn();

	void RefreshList();
protected:
	virtual void OnOK();
};
