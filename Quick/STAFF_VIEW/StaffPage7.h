#pragma once


//#include "MyListCtrl7.h"


// CStaffPage7 대화 상자입니다.

class CStaffPage7 : public CMyFormView
{
	DECLARE_DYNCREATE(CStaffPage7)

public:
	enum ColumnsName
	{
		kStaffNumber = 0,
		kDepart,
		kIdentify,
		kName,
		kWorkStop,
		kStopWarningRecommand,
		kWorkMonth,
		kColumsNameTotal
	};

public:
	CStaffPage7();
	virtual ~CStaffPage7();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_STAFF_PAGE7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

	//////////////////////////////////////////////
	
public:
	int m_nCompanyCode;	
	BOOL m_bIntegrated;

public:
	void ModifyPopup(int nItem);
	void ModifyPopup(CXTPListCtrlRecord2* pRecord);

	void SetCompanyCode(int nCompanyCode) { m_nCompanyCode = nCompanyCode; }
	void SetIntegrated(BOOL bIntegrated) { m_bIntegrated = bIntegrated; }
	void InitControl();
	void RefreshList();
	
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnViewExcel();
	afx_msg void OnWorkStop();
	afx_msg void OnWorkOk();
	afx_msg void OnMenuMsg();
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnBnClickedModifyBtn();
	afx_msg void OnEnChangeEditName();
	afx_msg void OnLvnDeleteitemList1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

public :
	int m_nANo;
	int m_nItem;

	CFlatEdit2 m_RiderEdit;
	CString m_strRider;
	CXTPListCtrl2 m_List;
	CXTPGridColumn* m_columnData[kColumsNameTotal];
	CMyStatic m_Static;
	CButton m_btnSearch;
	CButton m_btnModify;
	CButton m_btnRiderMove;
	
	afx_msg void OnBnClickedRiderMoveButton();
};
