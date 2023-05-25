#pragma once


#define WM_CLOSE_MSG_CONN_LIST_DLG	WM_USER + 681
enum { REQUEST_CANCEL = 0, REQUEST_RCP = 1};

#include "DateButton.h"
#include "MyReportControl.h"
#include "FlatEdit2.h"
#include "DalsuRichEdit.h"

class CNewConnListRecord : public CXTPGridRecord
{
public:
	CNewConnListRecord(COleDateTime dtLog, 
			long nCompany,
			long nWNo,
			CString strName, 
			CString strCompany, 
			long nCompany2,
			long nWNo2, 
			CString strName2, 
			CString strCompany2, 
			CString strMsg,
			int nClientType,
			int nClientType2);

	long m_nType;
	long m_nTCompany;
	long m_nTWNo;
	CString m_strTCompany;
	CString m_strTName;
	CString m_strMsg;
	COleDateTime m_dtLog;
	int m_nTClientType;

	static long m_nMyCompany;
	static long m_nMyWNo;

protected:
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);

};

class CMsgNoteDlg;
class CMessageRecord;
// CNewConnListDlg 대화 상자입니다.

class CNewConnListDlg : public CMyResizeDialog
{
	DECLARE_DYNAMIC(CNewConnListDlg)

public:
	CNewConnListDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CNewConnListDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_NEW_CONN_LIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()


public:
	void UpdateUser(long nShareCode1, long nCompany, long nMNo, 
		CString strCompany, CString strBranch, CString strName, 
		COleDateTime dtTime, int nStatus, int nClientType, BOOL bExpand = FALSE,
		BOOL bAlreadyExistSkip = FALSE);

	void UpdateUserInfo(CMessageRecord *pRecord, long nShareCode1, long nCompany, long nMNo, 
		CString strCompany, CString strBranch, CString strName, 
		COleDateTime dtTime, int nStatus, int nClientType);

	void UpdateUserStatus(long nCompany, long nMNo, int nClientType, int nStatus);
	CXTPGridRecord* InsertSite(long nShareCode1, CString strSiteName, int nClientType = 0);

	void InsertUser(CXTPGridRecord *pInserted, 
		long nShareCode1, long nCompany, long nMNo, 
		CString strCompany, CString strBranch, CString strName, 
		COleDateTime dtTime, int nStatus, int nClientType);

	void RefreshConnList(BOOL bBackground = FALSE);
	void RefreshRequestCompanyList();
	void RefreshReport();
	void ClearExistFlag();
	void CheckExistFlagForDeleting();
	void SearchUser(CString strKeyword);
	void DirectSendMsg();
	void RefreshHistory();
	BOOL GetMsgDatabase();
	void RefreshAllStaffList();
	BOOL InsertNoteMsg(long nCompany, long nMNo, CString strSend, 
			CString strCompany, CString strName);
	CMsgNoteDlg* ShowNoteMsgDlg(long nCompany, long nMNo, long nClientType, 
		CString strCompanyName, CString strName, CString strTitle = "", CString strDescript = "",
		CMsgNoteDlg *pMsgDlgInstance = NULL);
	void ReportFilter();
	void SendBulkMsg(BOOL bInstanceMsg, int nSendType);
	CWnd* GetParentWnd() { return m_pParentWnd; }

	static int staticRefreshProc(CNewConnListDlg *app)
	{ return app->RefreshProc((LPVOID)app); }

	UINT RefreshProc(LPVOID lParam);
	void FindAfterShowMsgDlg(long nCompany, long nMNo, CString strMsg = "");
	void RefreshHistoryRich(long nCompany, long nMNo, long nClientType);
	void SendMsgForGroupChating(long nCompany, long nMNo, CString strName, char *szMsg);


public:
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnReportItemHistoryClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnReportItemHistoryDblClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnBnClickedPowerBtn();
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnBnClickedShowIntercallCheck();
	afx_msg void OnBnClickedMyCompanyCheck();
	afx_msg void OnBnClickedRefreshHistoryBtn();
	afx_msg void OnCbnSelchangeShowTypeCombo();
	afx_msg void OnEnChangeSearchHistoryEdit();
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnBnClickedSendMsgBtn();
	afx_msg void OnBnClickedSendNoteMsgBtn();
	afx_msg void OnCbnSelchangeMainCombo();
	afx_msg void OnBnClickedSendSelectBtn();
	afx_msg void OnBnClickedSendSearchBtn();
	afx_msg void OnBnClickedShowOnlyOnlineCheck();

public:
	BOOL m_bRequestMode;
	long m_nRequestType;
	long m_nRequestTNo;
	long m_nRequestCompany;
	BOOL m_bQueryChargeMode;
	char m_szQueryCharge[1024];
	BOOL m_bCloseMode;
	long m_nFindCompany;
	long m_nFindRNo;
	BOOL m_bRcpCopyData;
	char *m_pszRcpCopyData;
	CMkDatabase *m_pMsgDb;

	long m_nMyCompany;
	long m_nMyWNo;
	long m_nMyShareCode1;
	CString m_strMyName;
	CString m_strMyCompanyName;
	CString m_strMyBranchName;

protected:
	CXTPGridControl m_wndReportCtrl;
	CWnd *m_pParentWnd;
	CImageList m_ilIcons;
	CFlatEdit2 m_SearchEdit;
	CButton m_PowerBtn;
	CButton m_chkShowIntercall;
	CButton m_chkMyCompany;
	CComboBox m_cmbShowType;
	CFlatEdit2 m_edtSearchHistory;
	CDateTimeCtrl m_dtpFrom;
	CDateTimeCtrl m_dtpTo;
	CDateButton m_btnDate;
	CMyReportControl m_lstHistory;
	CMyReportControl m_lstHistory2;
	BOOL m_bFirstRefresh;
	CDalsuRichEdit m_edtHistoryRich;

	CFlatEdit2 m_edtBranch;
	CButton m_btnOpenBranch;
	CFlatEdit2 m_edtSend;
	CButton m_chkShowOnlyOnline;

	HANDLE m_hExitHandle;
	HANDLE m_hThreadDiedHandle;
	CCriticalSection m_csList;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

