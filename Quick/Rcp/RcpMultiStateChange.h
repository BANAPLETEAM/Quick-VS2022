#pragma once

class CRcpView;
class CMyReportControl;

class CRcpMultiStateChange
{
public:
	CRcpMultiStateChange(CRcpView *pView);
	~CRcpMultiStateChange(void);

	//void ChangeState(CMyReportControl *pList, int nState);

	CRcpView *m_pRcpView;
	CMyReportControl *m_pList;
	CCriticalSection m_csOrder;
	BOOL m_bNotUseStateChangeMsgBox;

	void ChangeItemState(int nState, BOOL bShare = FALSE);
	BOOL IsChangeItemStateOk(long nChangeState);
	BOOL GetCancelItem(long nTNo, long nRiderCompany, long nOrderCompany, CString strPhone,
				CString &strCancel, long &nCancelType, long &nPenaltyMin, long &nPenaltyCharge, BOOL &bCancelWait);

	long GetMultiSelecteCount();
	void ChangeItemStateAllocate(long nTNo, long nRNo, long nRiderCompany);
	BOOL CheckRiderLoadIns(long nRiderCompany, long nRNo, long nTNo);

	BOOL CheckLockCount(long nRiderCompany, long nRNo);
	BOOL CheckRiderDeposit(long nRiderCompany, long nRNo, long nTNo);
	BOOL OrderRequest(long nTNo, long nState, long nRiderCompany = 0, long nRNo = 0, long nToCompany = 0);
	BOOL CheckValidStateChange(long nTNo, long nPreState, long nState, long nRiderCompany = 0, long nRNo = 0);
	BOOL CheckEventOrder(long nTNo);

	int CancelOrder(LONG nCompany, LONG nTNo, LONG nPreState, CString strCancel, int nCancelType, 
		int nPenaltyMin = 0, int nPenaltyCharge = 0, BOOL bChangeToWait = 0, BOOL bRefresh = TRUE,long nRNo = 0);
	int Allocate(LONG nTNo, LONG nRNo, LONG nPreState, LONG nRiderCompany, BOOL bRefresh = TRUE);
	int CancelAllocate(LONG nTNo, LONG nPreState, BOOL bNoQueryMsg = FALSE, BOOL bShare = FALSE, BOOL bRefresh = TRUE, long nRNo = 0);
	int CompleteState(LONG nCompany, LONG nTNo, LONG nRNo, LONG nPreState, BOOL bNoQueryMsg = FALSE, BOOL bRefresh = TRUE);
	int PickupState(LONG nCompany,LONG nTNo, LONG nRNo, LONG nPreState, BOOL bNoQueryMsg = FALSE, BOOL bRefresh = TRUE);
	int FinishState(LONG nTNo, LONG nPreState, BOOL bNoQueryMsg = FALSE, BOOL bRefresh = TRUE);
	int InquiryState(LONG nTNo, LONG nPreState, BOOL bNoQueryMsg, BOOL bRefresh);
	int CancelAllocateToWait(LONG nTNo, LONG nPreState, BOOL bNoQueryMsg = FALSE, BOOL bRefresh = TRUE, long nRNo = 0);
	
	int CancelReserve(LONG nTNo, LONG nPreState);
	int ReserveOrder(LONG nTNo, LONG nPreState, long nReleaseMin, COleDateTime dtReserve, BOOL bChangeRiderForReserve);
	BOOL CheckChangeItem(long nSelItem, long nPreState, long nState, long nCancelType = 0);
	void CheckRiderClear(BOOL &bClearRider);
};
