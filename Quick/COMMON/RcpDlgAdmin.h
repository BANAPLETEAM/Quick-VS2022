
#pragma once

#include "RcpViewDef.h"

class CRcpDlg;
class CRcpPageInfoForm;
class CRcpPageCTIForm;
class CRcpPageMapForm;
class CRcpPageMemoForm;
class CRcpPageWCountForm;
class CRcpPageRecordFileForm;
class CRcpPageMissingCallForm;


class CRcpDlgAdmin
{
public:
	CRcpDlgAdmin();
	~CRcpDlgAdmin();

public:
	RCP_DLG_MAP m_mapRcpDlg;

	CRcpPageInfoForm* m_pInfoForm;
	CRcpPageCTIForm* m_pCTIForm;
	CRcpPageMapForm* m_pMapForm;
	CRcpPageMemoForm* m_pMemoForm;
	CRcpPageWCountForm* m_pWCountForm;
	CXTPGridSubListControl m_wndSubList;

	CRcpDlg* CreateRcpDlg(CBranchInfo* pBi = NULL, CString strTitle = "½Å±Ô",
		int nItem = -1, int nState = 0, CString strCID = "", BOOL bAddCall = FALSE,
		long nLineID = -1, DWORD dwAnswerTick = 0, long m_nWebID = 0,
		BOOL bScheduleOrder = FALSE, CString strYear = "", long nOperatorID = 0,
		BOOL bNewDlg = FALSE, BOOL bConsign = FALSE);

template<typename T>
	CRcpDlg* CreateRcpDlgSub(CBranchInfo* pBi, CString strTitle, int nItem,
		int nState, CString strCID, BOOL bAddCall, long nLineID,
		DWORD dwAnswerTick, long nWebID, BOOL bScheduleOrder, CString strYear,
		long nOperatorID, BOOL bNewDlg, BOOL bConsign);

	CRcpDlg* OpenRcpDlg(long nTNo);
	CRcpDlg* GetReadyToReuseDlg(UINT nServiceType);
	CRcpDlg* FindRcpDlg(long nTNo);

	CWnd* GetFocusControl();
	void SetFocusControl(CRcpDlg* pDlg, CWnd* pControl);

	void CloseRcpDlg(CRcpDlg* pRcpDlg);
	void MoveNewRcpDlg(CRcpDlg* pRcpDlg, BOOL bForceMoce = FALSE);

	RCP_DLG_MAP* GetRcpDlgMap() { return &m_mapRcpDlg; }
	int GetRcpDlgCount(int nServiceType) { return m_mapRcpDlg.size(); }
	CRcpDlg* IsRcpDlgVisible();
	CRcpDlg* FindRcpDlgFromUniqueChargeID(long nID);

	UINT GetServiceResoure(long nServiceType);

};