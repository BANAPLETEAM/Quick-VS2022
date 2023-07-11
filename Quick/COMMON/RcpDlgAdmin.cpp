#include "stdafx.h"
#include "Quick.h"
#include "RcpDlgAdmin.h"
#include "RcpDlg.h"
#include "RcpView.h"
#include "RcpPageCTIForm.h"
#include "RcpPageMemoForm.h"
#include "RcpPageMapForm.h"
#include "RcpPageInfoForm.h"
#include "MyReportPaintManager.h"
#include "SetRcpPageDlg.h"
#include "MkLock.h"
#include "MakePOIData.h"
#include "CustomerData.h"
#include "RcpPageRecordFileForm.h"
#include "RcpPageMissingCallForm.h"
#include "RcpInsungDlg.h"
#include "RcpPageWCountForm.h"

CRcpDlgAdmin::CRcpDlgAdmin()
{
	m_pInfoForm = NULL;
	m_pCTIForm = NULL;
	m_pMapForm = NULL;
	m_pMemoForm = NULL;
}

CRcpDlgAdmin::~CRcpDlgAdmin()
{
	m_mapRcpDlg.clear();
}

CRcpDlg* CRcpDlgAdmin::CreateRcpDlg(CBranchInfo* pBi, CString strTitle, int nItem,
	int nState, CString strCID, BOOL bAddCall, long nLineID,
	DWORD dwAnswerTick, long nWebID, BOOL bScheduleOrder, CString strYear,
	long nOperatorID, BOOL bNewDlg, BOOL bConsign)
{
	if (!pBi) pBi = LF->GetCurBranchInfo();


	if (!LF->IsUseNewDlg())
		return CreateRcpDlgSub<CRcpDlg>(pBi, strTitle, nItem, nState, strCID, bAddCall, nLineID,
			dwAnswerTick, nWebID, bScheduleOrder, strYear,
			nOperatorID, bNewDlg, bConsign);
	else
		return CreateRcpDlgSub<CRcpInsungDlg>(pBi, strTitle, nItem, nState, strCID, bAddCall, nLineID,
			dwAnswerTick, nWebID, bScheduleOrder, strYear,
			nOperatorID, bNewDlg, bConsign);
}

CWnd* CRcpDlgAdmin::GetFocusControl()
{
	RCP_DLG_MAP::iterator it;
	for (it = m_mapRcpDlg.begin(); it != m_mapRcpDlg.end(); it++)
	{
		if (it->first->m_pFocusControl)
			return it->first->m_pFocusControl;
	}
	return NULL;
}

void CRcpDlgAdmin::SetFocusControl(CRcpDlg* pDlg, CWnd* pControl)
{
	RCP_DLG_MAP::iterator it;
	for (it = m_mapRcpDlg.begin(); it != m_mapRcpDlg.end(); it++)
	{
		if (it->first->GetSafeHwnd() == pDlg->GetSafeHwnd())
			it->first->m_pFocusControl = pControl;
		else
			it->first->m_pFocusControl = NULL;
	}
}

template<typename T> CRcpDlg*
CRcpDlgAdmin::CreateRcpDlgSub(CBranchInfo* pBi, CString strTitle, int nItem,
	int nState, CString strCID, BOOL bAddCall, long nLineID,
	DWORD dwAnswerTick, long nWebID, BOOL bScheduleOrder, CString strYear,
	long nOperatorID, BOOL bNewDlg, BOOL bConsign)
{
	BOOL bReuseMode = FALSE;

	T* pRcpDlg = NULL;
	CWnd* pFocusControl = GetFocusControl();

	if (nItem > 0 && bNewDlg == FALSE)
	{
		pRcpDlg = (T*)OpenRcpDlg(nItem);
		if (pRcpDlg) {
			MoveNewRcpDlg(pRcpDlg, TRUE);
			return (T*)pRcpDlg;
		}
	}

	pRcpDlg = (T*)GetReadyToReuseDlg(!LF->IsUseNewDlg());
	if (pRcpDlg)
		bReuseMode = TRUE;

	if (!bReuseMode)
		pRcpDlg = new T;

	pRcpDlg->m_bCopyDlg = bNewDlg;
	pRcpDlg->m_nInitItem = nItem;	//nItem >= 0 이면 수정, -1 이면 신규모드(디폴트 -1임)
	pRcpDlg->m_strCID = strCID;
	pRcpDlg->m_nPreState = nState;
	pRcpDlg->m_nLineID = nLineID;
	pRcpDlg->m_dwAnswerTick = dwAnswerTick;
	pRcpDlg->m_bScheduleOrder = bScheduleOrder;
	pRcpDlg->m_strYear = strYear;
	pRcpDlg->m_nOperatorID = nOperatorID;
	pRcpDlg->m_bConsignLink = bConsign;
	if (!pBi)
		pRcpDlg->m_pBi = LF->GetCurBranchInfo();
	else
		pRcpDlg->m_pBi = pBi;

	pRcpDlg->m_bAddCall = bAddCall;
	pRcpDlg->m_pRcpView = LU->GetRcpView();
	pRcpDlg->m_nWebID = nWebID;

	if (!bReuseMode)
	{
		if (!LU->GetRcpView()->RcpCreate(pRcpDlg, GetServiceResoure(!LF->IsUseNewDlg())))
		{
			AfxMessageBox("메인 접수창 생성 실패");
			return NULL;
		}

		MoveNewRcpDlg(pRcpDlg);
		m_mapRcpDlg.insert(RCP_DLG_MAP::value_type(pRcpDlg, pRcpDlg));
	}
	else
	{
		pRcpDlg->OnInitialUpdate();
	}


	if (!pRcpDlg->m_strExtraTitle.IsEmpty())
	{
		strTitle += " " + pRcpDlg->m_strExtraTitle;
	}

	if (strCID.GetLength() > 0)
		m_pCTIForm->QueueWorkingMode();

	pRcpDlg->SetTitleInfo(strTitle);
	pRcpDlg->ShowWindow(pRcpDlg->IsIconic() ? SW_RESTORE : SW_SHOW);

	if (LF->GetBranchInfo(m_ui.nCompany)->bPopupFocus && pFocusControl)
		pFocusControl->SetFocus();

	return (T*)pRcpDlg;
}

CRcpDlg* CRcpDlgAdmin::OpenRcpDlg(long nTNo)
{
	if ((long)m_mapRcpDlg.size() == ZERO)
		return NULL;

	RCP_DLG_MAP::iterator it;
	for (it = m_mapRcpDlg.begin(); it != m_mapRcpDlg.end(); it++)
	{
		if (it->first->m_nInitItem == nTNo)
		{
			it->first->InitData();
			it->first->InitControlAfterGetData();
			return it->first;
		}
	}
	return NULL;
}

CRcpDlg* CRcpDlgAdmin::GetReadyToReuseDlg(UINT nServiceType)
{
	RCP_DLG_MAP::iterator it;
	for (it = m_mapRcpDlg.begin(); it != m_mapRcpDlg.end(); it++)
	{
		if (it->first->m_bReadyToReuse && !it->first->IsInsungDlg() == nServiceType)
			return it->first;
	}
	return NULL;
}

CRcpDlg* CRcpDlgAdmin::FindRcpDlg(long nTNo)
{
	RCP_DLG_MAP::iterator it;
	for (it = m_mapRcpDlg.begin(); it != m_mapRcpDlg.end(); it++)
	{
		if (it->first->m_nInitItem == nTNo)
			return it->first;
	}
	return NULL;
}

void CRcpDlgAdmin::CloseRcpDlg(CRcpDlg* pRcpDlg)
{
	if (GetRcpDlgCount(pRcpDlg->m_pBi->nServiceType) <= 2)
	{
		pRcpDlg->ShowWindow(SW_HIDE);
		pRcpDlg->Construct(FALSE);
		pRcpDlg->UpdateData(FALSE);
		pRcpDlg->m_bReadyToReuse = TRUE;
	}
	else
	{
		m_mapRcpDlg.erase(pRcpDlg);
		delete pRcpDlg;
		pRcpDlg = NULL;
	}
}

void CRcpDlgAdmin::MoveNewRcpDlg(CRcpDlg* pRcpDlg, BOOL bForceMoce)
{
	CRect rcDlg, rcSrcDlg;

	if (GetRcpDlgCount(pRcpDlg->m_pBi->nServiceType) > 0 && bForceMoce == FALSE)
	{
		RCP_DLG_MAP::reverse_iterator it = m_mapRcpDlg.rbegin();
		it->first->GetWindowRect(rcSrcDlg);
		rcSrcDlg.OffsetRect(-25, 20);

		pRcpDlg->GetWindowRect(rcDlg);
		rcDlg.OffsetRect(rcSrcDlg.left - rcDlg.left, rcSrcDlg.top - rcDlg.top);

	}
	else
	{
		CRect rcView;
		LU->GetRcpView()->GetWindowRect(rcView);
		pRcpDlg->GetWindowRect(rcDlg);
		pRcpDlg->ScreenToClient(rcDlg);
		rcDlg.OffsetRect(rcView.right - rcDlg.Width() - 40, rcView.top + 40);
		pRcpDlg->MoveWindow(rcDlg);
	}

	pRcpDlg->MoveWindow(rcDlg);
}

CRcpDlg* CRcpDlgAdmin::IsRcpDlgVisible()
{
	try {
		RCP_DLG_MAP::iterator it;
		for (it = m_mapRcpDlg.begin(); it != m_mapRcpDlg.end(); it++)
		{
			if (it->first->IsWindowVisible())
				return it->first;
		}
	}
	catch (...) {
		return NULL;
	}

	return NULL;
}

CRcpDlg* CRcpDlgAdmin::FindRcpDlgFromUniqueChargeID(long nID)
{
	RCP_DLG_MAP::iterator it;
	for (it = m_mapRcpDlg.begin(); it != m_mapRcpDlg.end(); it++)
	{
		if (it->first->m_nQueryChargeUniqueID == nID)
			return it->first;
	}
	return NULL;
}

UINT CRcpDlgAdmin::GetServiceResoure(long nServiceType)
{
	if (nServiceType == 1)
		return IDD_RCP_DLG;
	else
		return IDD_RCP_INSUNG_DLG;
	/*
	if(nServiceType == SERVICE_TYPE_CARGO)
		return IDD_RCP_CARGO_DLG;
	else
		return IDD_RCP_DLG;
		*/
}