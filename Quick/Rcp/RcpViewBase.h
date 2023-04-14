#pragma once

#include "RcpViewDef.h"
#include "MyReportControl.h"
#include "PPTooltip.h"

class CRcpPageInfoForm;
class CRcpPageCTIForm;
class CRcpPageMapForm;
class CRcpPageMemoForm;
class CRcpPageWCountForm;
class CRcpDlg;
class CRcpPageRecordFileForm;
class CRcpPageMissingCallForm;


// CRcpViewBase 뷰입니다.

class CRcpViewBase : public CMyFormView
{
	DECLARE_DYNCREATE(CRcpViewBase)

protected:
	CRcpViewBase();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CRcpViewBase();
	virtual void OnInitialUpdate();
	virtual void MoveClient();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LONG OnCloseRcpDlg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnReportColumnRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()

protected:
	int m_nSavedFormHegiht;
	long m_nFormHeight;

	CPtrArray m_arrSavedHideWnd;
	RCP_DLG_MAP m_mapRcpDlg;
	BOOL m_bDialogMode;
	CXTPGridSubListControl m_wndSubList;
	CImageList m_listIcons;
	CPPToolTip m_tooltip;
	CXTPPopupControl m_wndPopupControl;
	CCriticalSection m_csOrder;

	void AddMapForm(BOOL bActive = FALSE);
	void InitForm();
	void LoadListFont(BOOL bRedraw);
	void RefreshStateColor();
	void LoadReportState();
	void SaveReportState(CString &strSave, long &nSize);
	void OnShowFieldChooser();
	void MoveNewRcpDlg(CRcpDlg *pRcpDlg, BOOL bForceMoce = FALSE);

public:
	CBranchInfo *m_pBi;
	CMyReportControl m_xList;
	CRcpPageInfoForm *m_pInfoForm;
	CRcpPageCTIForm *m_pCTIForm;
	CRcpPageMapForm *m_pMapForm;
	CRcpPageMemoForm *m_pMemoForm;
	CRcpPageWCountForm *m_pWCountForm;
	CRcpPageRecordFileForm *m_pRecordFileForm;
	CRcpPageMissingCallForm *m_pMissingCallForm;
	CRcpFormTabControl m_wndTabControl;


	RCP_DLG_MAP* GetRcpDlgMap() {return &m_mapRcpDlg;}
	int GetRcpDlgCount(int nServiceType) { return m_mapRcpDlg.size(); }
	CRcpDlg* IsRcpDlgVisible();
	CRcpDlg* FindRcpDlgFromUniqueChargeID(long nID);
	CRcpDlg* FindRcpDlg(long nTNo);
	CRcpDlg* GetReadyToReuseDlg(UINT nServiceType);
	CRcpDlg* OpenRcpDlg(long nTNo);
	CWnd* GetFocusControl();
	void SetFocusControl(CRcpDlg *pDlg, CWnd* pControl);
	void ShowAllControl(BOOL bShow, CWnd *pwndExcept = NULL);

	void ChangeFormHeight(long nTop) { m_nFormHeight = nTop; MoveClient();}
	void IncFormHeight() { m_nFormHeight+=10; MoveClient();}
	void DecFormHeight() { m_nFormHeight-=10; MoveClient();}
	void SetFormHeightBig() { m_nFormHeight = TAB_FORM_HEIGHT_BIG; MoveClient();}
	void SetFormHeightNormal() { m_nFormHeight = TAB_FORM_HEIGHT; MoveClient();}
	void SetFormHeightMax();
	void SetFormHeightRestore();
	BOOL IsDialogMode() { return m_bDialogMode; }

	CRcpDlg* CreateRcpDlg(CBranchInfo *pBi = NULL, CString strTitle = "신규", 
		int nItem = -1, int nState = 0, CString strCID = "", BOOL bAddCall = FALSE,
		long nLineID = -1, DWORD dwAnswerTick = 0,long m_nWebID= 0,
		BOOL bScheduleOrder = FALSE, CString strYear = "",long nOperatorID = 0,
		BOOL bNewDlg = FALSE,BOOL bConsign = FALSE);

	template<typename T> 
	CRcpDlg* CreateRcpDlgSub(CBranchInfo *pBi, CString strTitle, int nItem, 
		int nState, CString strCID, BOOL bAddCall, long nLineID, 
		DWORD dwAnswerTick,long nWebID, BOOL bScheduleOrder, CString strYear,
		long nOperatorID, BOOL bNewDlg,BOOL bConsign);


	UINT GetServiceResoure(long nServiceType);
};


