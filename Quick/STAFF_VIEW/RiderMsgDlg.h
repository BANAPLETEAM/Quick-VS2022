#pragma once


#include "MakeBranchCombo.h"
#include "MyCheckBtn.h"
#include "afxwin.h"

// CRiderMsgDlg 대화 상자입니다.

typedef struct {
	long nCompany;
	long nRNo;
} MSG_RIDER_INFO;

typedef CArray<MSG_RIDER_INFO*, MSG_RIDER_INFO*>	CMsgRiderInfo;


class CRiderMsgDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderMsgDlg)
public:
	enum COL_HISTORY
	{
		COL_DATE,
		COL_RECIVE,
		COL_MESSAGE,
		COL_WNO,
		COL_WNAME,
		COL_DT_READ,
		COL_MESSAGE_ID,
		COL_NO,
		COL_DT_DELETE
	};

	enum COL_USER_HISTORY
	{
		COL_USER_HISITORY_DATE,
		COL_USER_HISITORY_MESSAGE,
		COL_USER_HISITORY_RIDER_COMANY_NAME,
		COL_USER_HISITORY_RNO,
		COL_USER_HISITORY_RNAME,
		COL_USER_HISITORY_DT_READ,
		COL_USER_HISITORY_MESSAGE_ID,
		COL_USER_HISITORY_NO
	};

public:
	CRiderMsgDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRiderMsgDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_RIDER_MSG_DLG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSendBtn();
	afx_msg void OnBnClickedNewBtn();
	afx_msg void OnEnChangeMsgEdit();
	afx_msg void OnBnClickedSendBothBtn();
	afx_msg void OnBnClickedSendVRAccountBtn();
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnBnClickedDeleteSelBtn();
	afx_msg void OnBnClickedDeleteAllBtn();
	afx_msg void OnBnClickedCancelBtn2();
	afx_msg void OnBnClickedDeleteChk();
	afx_msg void OnBnClickedEditBtn();
	afx_msg void OnBnClickedAllCompanyBtn();
	afx_msg void OnCbnSelchangeDeleteCombo();
	afx_msg void OnCbnSelchangeBranchCombo();
	afx_msg void OnReportItemChange(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemMsgClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnCurrentUSerHistoryReportItemMsgClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedAllianceMsgBtn();
	afx_msg void OnBnClickedOpenBrnachBtn();
	afx_msg void OnBnClickedWorkingCheck();
	afx_msg void OnBnClickedNotWorkingCheck();

	void FilterRider();
	void FilterListControl(int nCompany, int nRNo);
	void RefreshRiderList();
	void RefreshHistory(long nCompany, long nRNo);
	void RefreshWorkerHistory();
	void RefreshSelectCount();
	BOOL SendVRAcoountMsg(int nItem);
	BOOL SendPDAMsg(int nItem, BOOL bWholeAlliance = FALSE);
	BOOL SendRiderSMS(int nItem);
	BOOL IsAllRider();
	void SetCompanyCode(long nCompanyCode) { m_nCompanyCode = nCompanyCode; }
	void SetIntegrated(BOOL bIntegrated) { m_bIntegrated = bIntegrated; }
	LONG OnChangeBrachAllCode(WPARAM wParam, LPARAM lParam);

	CMsgRiderInfo m_paSelected;

	CMakeBranchCombo m_cBranchCombo;
	CMainBranchCombo m_cmbMain;
	
	CXTPListCtrl2 m_lstRider;
	CXTPListCtrl2 m_lstHistory;
	CXTPListCtrl2 m_lstCurrentUserHistory;

	CFlatEdit2 m_edtSearch;	
	CFlatEdit2 m_edtMsg;
	CFlatEdit2 m_edtBranch;

	CButton m_btnDeleteSel;
	CButton m_btnDeleteAll;
	CButton m_btnNew;
	CButton m_btnSend;
	CButton m_btnSendBoth;
	CButton m_btnCancel;
	CButton m_btnEdit;
	CButton m_btnSendVRAccount;
	CButton m_btnOpenBranch;
	CButton m_chkWorkibg;
	CButton m_chkNotWorkibg;
	CButton m_chkDelete;

	CMyStatic m_stcHistory;
	CMyStatic m_stcHistory2;
	CMyStatic m_stcSearch;
	CMyStatic m_stcSearch2;
	CMyStatic m_stcAutoDelete;
	CMyStatic m_stcMultiSelect;
	CMyStatic m_stcSendType;
	CMyStatic m_stcCount;
	CMyStatic m_stcSelectCount;
	CMyStatic m_stcInfo;
	CMyStatic m_stcMsg;
	CMyStatic m_stcOldMsg;

	CComboBox m_cmbRider;
	CComboBox m_cmbDelete;
	CComboBox m_cmbSMS;
	CComboBox m_cmbBranch;

public:
	long m_nCompanyCode;
	long m_nSend;
	long m_nRNo;

	BOOL m_bIntegrated;
	BOOL m_bStart;

	CString m_strMsg;
	CString m_strOldMsg;
	CString m_strSearch;

	COleDateTime m_dtLast;
protected:
	virtual void OnOK();

public:
	afx_msg void OnBnClickedSendAllBtn();
	CButton m_btnSendAll;
	afx_msg void OnBnClickedSendDownUrlBtn();
};


//#pragma once
//
//#include "MyStatic.h"
//#include "MyButton.h"
//#include "FlatEdit.h"
//#include "MyDialog.h"
//
//// CRiderMsgDlg 대화 상자입니다.
//
//typedef struct {
//	long nCompany;
//	long nRNo;
//} MSG_RIDER_INFO;
//
//typedef CArray<MSG_RIDER_INFO*, MSG_RIDER_INFO*>	CMsgRiderInfo;
//
//class CRiderMsgDlg : public CMyDialog
//{
//	DECLARE_DYNAMIC(CRiderMsgDlg)
//
//public:
//	CRiderMsgDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
//	virtual ~CRiderMsgDlg();
//
//// 대화 상자 데이터입니다.
//	enum { IDD = IDD_RIDER_MSG_DLG };
//
//protected:
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
//
//	DECLARE_MESSAGE_MAP()
//public:
//	afx_msg void OnBnClickedOk();
//	virtual BOOL OnInitDialog();
//
//	CMyStatic m_stcMsg;
//	CMyStatic m_stcOldMsg;
//	CMyStatic m_stcHistory;
//	CMyStatic m_stcSearch;
//	CMyStatic m_stcCount;
//	CMyStatic m_stcSelectCount;
//	CEdit m_edtMsg;
//	CFlatEdit m_edtSearch;
//
//	CString m_strMsg;
//	CString m_strOldMsg;
//	COleDateTime m_dtLast;
//	int m_nSend, m_nRNo;
//	CString m_strSearch;
//
//	CListCtrl m_lstRider;
//	CListCtrl m_lstHistory;
//	CUIntArray m_uaSelected;
//
//	CMyButton m_btnSend;
//	CMyButton m_btnNew;
//	CMyButton m_btnSendBoth;
//	CMyButton m_btnCancel;
//	CMyButton m_btnEdit;
//
//	CMyButton m_btnDeleteSel;
//	CMyButton m_btnDeleteAll;


//	CMyButton m_btnSendVRAccount;
//
//	CMsgRiderInfo m_paSelected;
//
//protected:
//	long m_nCompanyCode;
//	BOOL m_bIntegrated;
//	BOOL m_bStart;
//
//public:
//	void SetCompanyCode(long nCompanyCode) 
//	{ m_nCompanyCode = nCompanyCode; }
//	void SetIntegrated(BOOL bIntegrated) 
//	{ m_bIntegrated = bIntegrated; }
//
//	afx_msg void OnCbnSelchangeRiderCombo();
//protected:
//	virtual void OnOK();
//
//public:
//	afx_msg void OnBnClickedCancel();
//
//	void RefreshRiderList();
//	afx_msg void OnBnClickedSendBtn();
//	afx_msg void OnLvnItemchangedRiderList(NMHDR *pNMHDR, LRESULT *pResult);
//
//	void RefreshHistory(long nCompany, long nRNo);
//	afx_msg void OnBnClickedNewBtn();
//	afx_msg void OnLvnItemchangedHistoryList(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnEnChangeMsgEdit();
//	afx_msg void OnBnClickedSendBothBtn();
//	afx_msg void OnEnChangeSearchEdit();
//
//	BOOL SendPDAMsg(int nItem);
//	BOOL SendRiderSMS(int nItem);
//	BOOL SendVRAcoountMsg(int nItem);
//	afx_msg void OnTimer(UINT nIDEvent);
//
//	void RefreshSelectCount();
//	afx_msg void OnBnClickedCancelBtn2();
//	afx_msg void OnBnClickedDeleteSelBtn();
//	afx_msg void OnBnClickedDeleteAllBtn2();
//	afx_msg void OnBnClickedSendVraccountBtn();
//	afx_msg void OnBnClickedSendVRAccountBtn();
//	afx_msg void OnLvnDeleteallitemsHistoryList(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnNMClickHistoryList(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnBnClickedDeleteAllBtn();
//	afx_msg void OnBnClickedEditBtn();
//
//};
