#pragma once

//
//#include "CustomerPage8_1.h"


// CAddGroupMemberDlg 대화 상자입니다.

class CAddGroupMemberDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAddGroupMemberDlg)

public:
	CAddGroupMemberDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAddGroupMemberDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ADD_GROUP_MEMBER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedIncudeBtn();
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnCbnSelchangeSearchCombo();
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void ViewSearchEdit();
	void ViewOrder();
	void RefreshCustomer();

	CustomerList m_lstCustomer;
	CStatic m_stcTerm;

	CFlatEdit2 m_SearchEdit;
	CButton m_chkMidSearch;
	CButton m_btnSearch;

	COleDateTime m_dtStart;
	COleDateTime m_dtEnd;

	CDateTimeCtrl m_dtpStart;
	CDateTimeCtrl m_dtpEnd;

	CDateButton m_btnDate;
	CComboBox m_cmbSearch;

	CString m_strSearch;
	
};
