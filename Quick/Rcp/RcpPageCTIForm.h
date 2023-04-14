#pragma once

#include "MyCall.h"
#include "OpStatePaintManager.h"
#include "PPTooltip.h"

#define COL_CUSTOMER_INFO	5

typedef struct
{
	CString strCName;
	CString strID; //nID
	CString strDong;
	CString strDepart;
	CString strManager;
	CString strInfo;
	CString strDesc;
}  PHONE_CUSTOMER_STRUCT;

//typedef map<CString, PHONE_CUSTOMER_STRUCt> PHONE_CUSTOMER_MAP;
typedef map<CString, PHONE_CUSTOMER_STRUCT> PHONE_CUSTOMER_MAP;
typedef map<CString, pair<CString, COleDateTime>> LAST_ANSWER_OP_MAP;
typedef map<CString, int> RECORDFILENAME_INSERTID_MAP;
//typedef map<CString, pair<CString, DWORD>> ALL_BARO_SMS_MAP;

typedef struct {
	CString strDID;
	CString strKeyPhoneID;
	COleDateTime dtFirstTime;
	COleDateTime dtLastTime;
	CString strPhone;
	CString strBranch;
	int nState;
	CString strOperator;
	CString strCustomer;
	COleDateTime dtAnswer;
	BOOL bAnswer;
	BOOL bNoRing;
} CALL_LIST_INFO;

typedef struct {
	CString strPhone;
	CString strKeyPhoneID;
	CString strDID;
	CString strOperator;
	CString strCallingLine;
} CALL_LIST_SELECTED_ITEM;

class CRcpPage;
class CRcpPageCTIForm;
class CCallListRecord;
class CMkDatabase;
class COPStatePaintManagerEx;

typedef map <CCallListRecord*, CString> CALL_LIST_MAP;

class CRingInfoStatic : public CMarkupStatic
{
public:
	CRingInfoStatic()
	{
		m_clrBackNomal = RGB(255, 255, 255);
		m_clrBackReverse = RGB(255, 200, 200);
		m_bReverse = FALSE;
	};
public:
	afx_msg void OnPaint()
	{
		CPaintDC dcPaint(this);
		CXTPBufferDC dcBuffer(dcPaint);

		CXTPClientRect rc(this);
		if(m_bReverse)
			dcBuffer.FillSolidRect(rc, m_clrBackReverse);
		else
			dcBuffer.FillSolidRect(rc, m_clrBackNomal);

		if (m_pUIElement)
		{
			CXTPMarkupDrawingContext dc(dcBuffer);
			m_pUIElement->Measure(&dc, rc.Size());
			m_pUIElement->Arrange(rc);
			m_pUIElement->Render(&dc);
		}
	}
	void SetReverse() { m_bReverse = !m_bReverse; }
	void RemoveReverse() { m_bReverse = FALSE; }

	COLORREF m_clrBackNomal;
	COLORREF m_clrBackReverse;
	BOOL m_bReverse;
};

// CRcpPageCTIForm 폼 뷰입니다.

class CRcpPageCTIForm : public CMyFormView
{
	DECLARE_DYNCREATE(CRcpPageCTIForm)

protected:
	CRcpPageCTIForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CRcpPageCTIForm();

public:
	enum { IDD = IDD_RCP_PAGE_CTI_FORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result);

	DECLARE_MESSAGE_MAP()
public:
	CALL_LIST_MAP m_map;
	virtual void OnInitialUpdate();

	BOOL OnSaveReportState();
	BOOL OnLoadReportState();

	afx_msg void OnBnClickedHangUpBtn();
	afx_msg void OnBnClickedEnableCheck();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedUpBtn();
	afx_msg void OnBnClickedDnBtn();
	afx_msg void OnBnClickedConnectBtn();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedAutoAnswerBtn();
	afx_msg void OnBnClickedMakeCallBtn();
	afx_msg void OnReportColumnRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnOPReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnOPReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedSetupBtn();
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnEnSetfocusSearchEdit();
	afx_msg void OnBnClickedRefreshStopCheck();
	afx_msg void OnViewExcel();
	afx_msg void OnOpReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg LRESULT OnMyCallMessage(WPARAM wParam, LPARAM lParam);

	static BOOL LoadTelClientInfo(CString& strIP, CString& strKeyPhoneID);
	static CString GetPhoneCustomer(CString strPhone);
	static PHONE_CUSTOMER_MAP m_mapPhoneCustomer;
	static CCriticalSection m_csPhoneCustomer;

	CString GetPhoneState(int nType, BOOL bOutBoundCall = FALSE);

	void PopupColumnSelect();

	void SetCallList(int nType,const char* szPhoneNumber,const char* szKeyPhoneID,const char* szDID,
		const char* szOperator, const char* szCustomer, 
		COleDateTime dtCur = COleDateTime::GetCurrentTime(), 
		BOOL bRedraw = TRUE);
	void SetOPState(int nType,const char* szPhoneNumber,const char* szKeyPhoneID,const char* szDID,
		const char* szOperator,CString strCustomer, 
		COleDateTime dtCur = COleDateTime::GetCurrentTime(), 
		BOOL bRedraw = TRUE);

	CCallListRecord* FindCallListItem(int nType, CString szPhoneNumber, COleDateTime dtCur = COleDateTime::GetCurrentTime());
	CCallListRecord* FindCallListItemWithKeyPhoneID(CString strKeyPhoneID, CString strPhoneNumber, COleDateTime dtCur);
	void SocketConnected();
	void SocketDisConnected();
	void EnsureVisibleFirstRow();
	void MakeOPList(BOOL bReDraw = TRUE);
	void AddPhoneCustomer(CString strPhone, CString strCustomer, BOOL bLastRefresh = FALSE);
	BOOL SetInfoToReport(CString strPhone, PHONE_CUSTOMER_STRUCT *stInfo, long nRow);
	BOOL IsMyPreAnswerCustomer(CString strID, CString strPhone);
	BOOL LoadCTIInfo(CString strUserID = "");
	void FilterList(CString strPhone, BOOL bRedraw = FALSE);
	void SearchRecvCID(CString strPhone);
	void ClearRecvCIDFilter();
	void PopupRcpDlg(const char* szPhoneNumber,const char* szKeyPhoneID,const char* szDID);
	BOOL RefreshOK(BOOL bFromSearch = FALSE);
	void SetLastRefresh();
	BOOL IsLastRefreshInOneSec();
	void DisplayRingInfo(long nRing, long nAnswer, long nMissingCallCount, long nMissingCallPerMin);
	void CheckAutoTransfer();
	BOOL AmIbusy();
	void MakeCall(int nCompany, CString strPhone, CString strCallingLine = "", CString strDID = "");
	void GetPreCallInfoLog(BOOL bCallFromInit = FALSE);
	void AddLastAnswerOP(CString strPhoneNumber, CString strOperator, COleDateTime dtCur);
	CString GetLastAnswerOP(CString strPhoneNumber, COleDateTime dtCur);
	void CheckAutoBlocking();

	static int staticAutoBlockingProc(CRcpPageCTIForm *app)
	{ return app->AutoBlockingProc((LPVOID)app); }

	UINT AutoBlockingProc(LPVOID lParam);
	void OnContextMenu(CWnd* pWnd, CPoint point);
	void RefreshState(CString strMsg = "");
	void AddBlockingPhone(CString strPhone);
	void RefreshRingInfo();
	CCallListRecord* FindCallListHasBranchInfo(CString strPhoneNumber);
	void AutoHangUp();
	void SaveReportState(CString &strSave, long &nSize);
	void LoadReportState();
	BOOL SetRecordData(CCallListRecord *pRecord, CString szPhoneNumber);
	afx_msg void OnReportColumnChangeChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/);

public:
	CCriticalSection m_csCallList;
	CCriticalSection m_csOPState;
	CCriticalSection m_csMap;
	CCriticalSection m_csState;

	CString m_strIP;
	CString m_strKeyPhoneID;
	CString m_strLastFilterPhone;
	CString m_strRecvCID;

	CMyCall m_call;
	CMyCall m_callSUB;		//고객정보를 얻기위한 SUB CALL 객체
	BOOL m_bInitialized;

	CFlatEdit2 m_edtState;
	CButton m_btnHangUp;
	CFlatEdit2 m_edtSearch;
	CFlatEdit2 m_edtMakeCall;
	BOOL m_bColumnInsert;

	CWnd *m_pwndParent;
	CXTPGridControl m_wndReport;
	CXTPGridControl m_wndOPReport;
	COPStatePaintManager *m_pOPPaintManager;
	COPStatePaintManagerEx *m_pOPPaintManagerEx;
	CString m_strTelserverKey;
	BOOL m_bConnected;

	HCURSOR m_hcArrow;
	HCURSOR m_hcVertical;
	BOOL m_bChangeCursor; // 화면이동 변수들
	BOOL m_bMoveControl;
	CButton m_chkRefreshStop;
	DWORD m_dwRefreshStop;
	DWORD m_dwLastRefresh;	

	CString m_strAutoTransfer;
	CString m_strAutoTransfer2;

	CRingInfoStatic m_stcRingInfo;
	CCriticalSection m_csRinginfo;
	CXTPGridRecord *m_pLastAutoTransferRecord;
	DWORD m_dwLastAutoTransferTick;
	COleDateTime m_dtLastRefresh;
	BOOL m_bMouseButtonDown;
	LAST_ANSWER_OP_MAP m_mapLastAnswerOP;
	BOOL m_bAutoBlockingThreadAlive;

	HANDLE m_hAutoBlockingHandle;
	HANDLE m_hExitHandle;
	HANDLE m_hThreadDiedHandle;
	CStringList m_lstBlocking;
	CButton m_btnMakeCallHotKey;
	CStringArray m_saHotNumberList;

	CString m_strIP2;
	BOOL m_bUseCTI;
	BOOL m_bHotCID;
	BOOL m_bAutoBlocking;
	BOOL m_bAutoTransfer;
	CALL_LIST_SELECTED_ITEM m_selected;
	CString m_strRingInfo;
	CMkDatabase *m_pMainDb;
	CMkDatabase *m_pLogDb;
	BOOL m_bEnableDBRefresh;
	CWnd *m_pMainFrame;

	CButton m_btnCIDNumber;
	CFlatEdit2 m_edtQueueState;
	CButton m_btnQueuePause;

	BOOL m_bIPPBX;
	BOOL m_bQueueRcpPopup;

	long m_nRcpPopupSecond;
	DWORD m_dwRingInfoTick;
	BOOL m_bSoundPlay;
	BOOL m_bRingColor;
	BOOL m_bRingMusic;
	CString m_strRingMusicPath;

	int m_nRingCount;
	DWORD m_dwDeviceID;
	void OnOpenMusic();
	BOOL OnPlayMusic();
	BOOL OnStopMusic();

	BOOL GetQueueRcpPopup(){ return m_bQueueRcpPopup;};

	void QueueRecvModeSecond();
	void ThreadQueueRecvMode();
	static UINT WINAPI _ThreadQueueRecvMode(LPVOID pParam);

	BOOL m_bThreadQueue;
	void QueueWorkingMode();
	HANDLE m_threadHandle;

	void AddRecordFileNameInsertID(CString strKeyPhoneID, CString strPhoneNumber, int nInsertID);
	long GetRecordFileNameInsertID(CString strPhoneNumber);
	void RemoveRecordFileNameInsertID(CString strPhoneNumber);

	afx_msg void OnBnClickedQueuePausedBtn();
	afx_msg void OnBnClickedCIDBtn();

	CBranchInfo *m_pBiCID;
	void SelectCID(CBranchInfo *pBi);

	void RefreshQueueState();
	void MoveTopControl();
	void MoveOffsetControl(CWnd *pWnd, int nOffset);

	RECORDFILENAME_INSERTID_MAP m_mapRecordFileID;

	long m_nOPStateWidth;
	OP_STATE_MAP* GetOPStateMap();
	void AddOpRecord(CString strTemp, CXTPGridRecord *pRecord, OP_STATE_INFO *pInfo);
	void OpReportItemClickEvent(int nEventType, CString strKeyPhoneID);
	CPPToolTip m_tooltip;

	BOOL m_bNotCalllistPickup;

	/*static CCriticalSection m_csAllbaroSMS;
	static ALL_BARO_SMS_MAP m_mapAllbaroSMS;
	void AddAllbaroSMS(CString strPhone, CString strKeyPhone);
	void RemoveAllbaroSMS(CString strPhone);
	BOOL SendAllbaroSMS();*/

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnBnClickedMakeCallUserBtn();
	afx_msg void OnBnClickedMakeCallHotKey1Btn();
	afx_msg void OnBnClickedMakeCallHotKey2Btn();
	afx_msg void OnBnClickedMakeCallHotKey3Btn();
	afx_msg void OnBnClickedMakeCallHotKey4Btn();
	afx_msg void OnBnClickedMakeCallHotKey3Btn2();
	afx_msg void OnBnClickedMakeCallHotKey5Btn();
	afx_msg void OnBnClickedMakeCallHotKeyBtn();
	afx_msg void OnMenuHotNumber(UINT nID);
	afx_msg void OnMenuCallList(UINT nID);
	afx_msg void OnMenuOPList(UINT nID);
};



AFX_INLINE void CRcpPageCTIForm::SetLastRefresh()
{
	m_dwLastRefresh = GetTickCount();
}

AFX_INLINE BOOL CRcpPageCTIForm::IsLastRefreshInOneSec()
{
	return (GetTickCount() - m_dwLastRefresh) < 1000;
}