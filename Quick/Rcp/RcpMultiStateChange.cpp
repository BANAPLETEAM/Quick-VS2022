#include "StdAfx.h"
#include "resource.h"
#include "RcpMultiStateChange.h"
#include "RcpView.h"
#include "MkLock.h"
#include "CancelDlg.h"
#include "SmsDlg.h"
#include "CompleteAfterEditDlg.h"
 
CRcpMultiStateChange::CRcpMultiStateChange(CRcpView *pView)
{
	m_pRcpView = pView;
	m_pList = m_pRcpView->GetReportControl();
	m_bNotUseStateChangeMsgBox = FALSE;
}

CRcpMultiStateChange::~CRcpMultiStateChange(void)
{
}

void CRcpMultiStateChange::ChangeItemStateAllocate(long nTNo, long nRNo, long nRiderCompany)
{
	if(!LF->POWER_CHECK(2009, "개별배차", TRUE))
		return;

	CXTPGridSelectedRows *pRows = m_pList->GetSelectedRows();
	if(pRows == NULL) return;
	if(pRows->GetCount() == ZERO) return;

	long nIndex = pRows->GetAt(ZERO)->GetIndex();
	long nRet = MINUS_ONE;

	if(m_pRcpView->GetItemIsParentOrder(nIndex) == TRUE)
	{
		OrderRecordList &order = m_pRcpView->GetTodayOrder()->GetOrderRecordList();
		OrderRecordList::iterator it;

		BOOL bUpdate = FALSE;

		for(it = order.begin(); it != order.end(); it++)
		{
			if(it->second.nTNoSet == nTNo)
			{
				if(it->second.nState >= 8 && it->second.nState <= 10)
				{
					nRet = Allocate(it->second.nTNo, nRNo, it->second.nState, nRiderCompany, FALSE);

					if(nRet != STATE_OK_ONLY_MAN)
						break;
					else 
						bUpdate = TRUE;
				}
			}
		}

		if(bUpdate == TRUE)
			m_pRcpView->AllRefresh();
	}
	else if(IsChangeItemStateOk(STATE_OK_ONLY_MAN))
	{
		long nItemCount = pRows->GetCount();
		CString strTemp; strTemp.Format("%d건을 동시 개별배차 하시겠습니까?", nItemCount);

		if(nItemCount > ONE)
		{
			if(MessageBox(NULL, strTemp, "확인", MB_OKCANCEL) != IDOK)
				return;
		}

		for(int i=ZERO; i<pRows->GetCount(); i++)
		{
			long nItem = pRows->GetAt(i)->GetIndex();
			long nTNo = m_pRcpView->GetItemTNo(nItem);
			long nPreState = m_pRcpView->GetItemState(nItem);

			nRet = Allocate(nTNo, nRNo, nPreState, nRiderCompany,
								pRows->GetCount() - ONE == i ? TRUE : FALSE);

			if(nRet != STATE_OK_ONLY_MAN)
				break;
		}
	}	
	else
	{
		long nItem = pRows->GetAt(ZERO)->GetIndex();
		long nTNo = m_pRcpView->GetItemTNo(nItem);
		long nPreState = m_pRcpView->GetItemState(nItem);

		nRet = Allocate(nTNo, nRNo, nPreState, nRiderCompany);
	}
}

void CRcpMultiStateChange::ChangeItemState(int nState, BOOL bShare)
{
	if(!LF->POWER_CHECK(2002, "오더상태변경", TRUE))
		return;

	m_bNotUseStateChangeMsgBox = AfxGetApp()->GetProfileInt("RcpPage", "NotUseStateChangeMsgBox", 0);
	
	CString strCancel;
	long nPenaltyMin;
	long nPenaltyCharge;
	long nCancelType;
	BOOL bChangeToWait;

	LU->GetRcpView()->SetRefreshStop();

	if(m_bNotUseStateChangeMsgBox == FALSE)
	{
		if(nState == STATE_WAIT)
		{
			if(MessageBox(m_pRcpView->GetSafeHwnd(), "대기 상태로 변경하시겠습니까?", "상태변경", MB_YESNO | MB_ICONINFORMATION) != IDYES)
				return;
		}
		else if(nState == STATE_OK)
		{
			if(MessageBox(m_pRcpView->GetSafeHwnd(), "접수 상태로 변경하시겠습니까?", "상태변경", MB_YESNO | MB_ICONINFORMATION) != IDYES)
				return;
		}
		else if(nState == STATE_ALLOCATED)
		{
			if(MessageBox(m_pRcpView->GetSafeHwnd(), "배차상태로 변경하시겠습니까?", "상태변경", MB_YESNO | MB_ICONINFORMATION) != IDYES)
				return;
		}
		else if(nState == STATE_FINISH)
		{
			if(MessageBox(m_pRcpView->GetSafeHwnd(), "완료 하시겠습니까?", "상태변경", MB_YESNO | MB_ICONINFORMATION) != IDYES)
				return;
		}
		else if(nState == STATE_INQUIRY)
		{
			if(MessageBox(m_pRcpView->GetSafeHwnd(), "문의상태로 변경 하시겠습니까?", "상태변경", MB_YESNO | MB_ICONINFORMATION) != IDYES)
				return;
		}
		
	}

	if(IsChangeItemStateOk(nState))
	{
		CXTPGridSelectedRows *pRows = m_pList->GetSelectedRows();


		for(int i=ZERO; i<pRows->GetCount(); i++)
		{
			long nItem = pRows->GetAt(i)->GetIndex();
			long nTNo = m_pRcpView->GetItemTNo(nItem);
			long nPreState = m_pRcpView->GetItemState(nItem);
			long nRNo = m_pRcpView->GetItemRNo(nItem);
			long nRiderCompany = m_pRcpView->GetItemRiderCompany(nItem);
			long nOrderCompany = m_pRcpView->GetItemCompany(nItem);
			long nDeposit = m_pRcpView->GetItemDeposit(nItem);
			long nCarType = m_pRcpView->GetItemCarType(nItem);
			CString strPhone = m_pRcpView->GetItemPhone(nItem);
			CString strTitle = "[개별] " + m_pRcpView->GetItemStart(nItem) + " -> " + m_pRcpView->GetItemDest(nItem);
			BOOL bShare = m_pRcpView->GetItemShare(nItem);

			long nRet = ZERO;
			long nRet2 = ZERO;

			switch (nState)
			{
				case STATE_WAIT :
					nRet = CancelAllocateToWait(nTNo, nPreState,  
									i == ZERO ? FALSE : TRUE,  
									pRows->GetCount() - ONE == i ? TRUE : FALSE,
									nRNo);
					break;

				case STATE_OK :
					nRet = CancelAllocate(nTNo, nPreState,  
									i == ZERO ? FALSE : TRUE,  bShare, 
									pRows->GetCount() - ONE == i ? TRUE : FALSE,
									nRNo);
					break;

				case STATE_OK_ONLY_MAN :

					if(!LF->POWER_CHECK(2009, "개별배차", TRUE))
						return;

					LU->OpenAllocateDlg(nTNo, nPreState, strTitle, ZERO, nDeposit, nCarType);
					return;
				break;
					 
				case STATE_ALLOCATED :
					nRet = CompleteState(nOrderCompany, nTNo, nRNo, nPreState, 
									i == ZERO ? FALSE : TRUE,
									pRows->GetCount() - ONE == i ? TRUE : FALSE);
					break;

				case STATE_PICKUP:
					nRet = PickupState(nOrderCompany, nTNo, nRNo, nPreState, 
									i == ZERO ? FALSE : TRUE,
									pRows->GetCount() - ONE == i ? TRUE : FALSE);
					break;

				case STATE_FINISH:
					nRet = FinishState(nTNo, nPreState, 
									i == ZERO ? FALSE : TRUE,
									pRows->GetCount() - ONE == i ? TRUE : FALSE);
					break;
				case STATE_INQUIRY:
					nRet = InquiryState(nTNo, nPreState, 
						i == ZERO ? FALSE : TRUE,
						pRows->GetCount() - ONE == i ? TRUE : FALSE);
					break;

				case STATE_CANCELED:
							
					if(i==ZERO)
					{
						if(FALSE == GetCancelItem(nTNo, nRiderCompany, nOrderCompany, strPhone, 
								strCancel, nCancelType, nPenaltyMin, nPenaltyCharge, bChangeToWait))
						{
							return;
							break;
						}							
					}

					nRet = CancelOrder(nOrderCompany, nTNo, nPreState, 
									strCancel, nCancelType, nPenaltyMin, nPenaltyCharge, bChangeToWait,
									pRows->GetCount() - ONE == i ? TRUE : FALSE,
									nRNo);

					break;

			}			

			if(nRet != nState)
				break;
		} 
	}

	if(nState != STATE_OK_ONLY_MAN)
		LU->GetRcpView()->SetRefreshStart();
}

BOOL CRcpMultiStateChange::GetCancelItem(long nTNo, long nRiderCompany, long nOrderCompany, CString strPhone,
										 CString &strCancel, long &nCancelType, long &nPenaltyMin, long &nPenaltyCharge, BOOL &bCancelWait)
{
	CBranchInfo *pBi = LF->GetBranchInfo(nOrderCompany);
	if(pBi->bCancelReason)
	{
		strCancel = "[취소:즉시취소]";
		nCancelType = 11;
		nPenaltyMin = ZERO;
		nPenaltyCharge = ZERO;
		bCancelWait = FALSE;
		return TRUE;
	}
	else
	{
		CCancelDlg dlg;
		CStringArray saCancel;
		saCancel.Add("[취소1:전화불통]");
		saCancel.Add("[취소2:시간지연]");
		saCancel.Add("[취소3:배달지이상]");
		saCancel.Add("[취소4:물건크기불량]");
		saCancel.Add("[취소5:취급불가불건]");
		saCancel.Add("[취소6:고객없음]");
		saCancel.Add("[취소7:일부취소]");
		saCancel.Add("[취소8:기사부족]");
		saCancel.Add("[취소9:연습오더]");
		saCancel.Add("[취소10:본인취소]");
		saCancel.Add("[취소:배차실수]");

		dlg.m_nTNo = nTNo;
		dlg.m_nCompany = nRiderCompany;
		dlg.m_psaCancel = &saCancel;
		dlg.m_strCustomerPhone = strPhone;
		dlg.m_nOrderCompany = nOrderCompany;
		//dlg.m_strPenaltyCharge.Format("%d", m_pBi->nCancelPenaltyCharge);

		if(dlg.DoModal() == IDOK) 
		{
			if(dlg.m_nCancelType >= 11)
			{
				if(dlg.m_strEtc.GetLength() > ZERO)			
					strCancel = "[취소:" + dlg.m_strEtc + "]";
				else 
					strCancel = "[취소:기타]";

				dlg.m_nCancelType = 11;
			}
			else 
			{
				strCancel = saCancel.GetAt(dlg.m_nCancelType);
			}

			nCancelType = dlg.m_nCancelType;
			nPenaltyMin = dlg.m_bAllocateLimit ? atol(dlg.m_strPenaltyMin) : ZERO;
			nPenaltyCharge = dlg.m_bCancelPenaltyCharge ? atol(dlg.m_strPenaltyCharge) : ZERO;
			bCancelWait = dlg.m_bChangeToWait;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CRcpMultiStateChange::IsChangeItemStateOk(long nChangeState)
{
	CXTPGridSelectedRows *pRows = m_pList->GetSelectedRows();

	if(pRows == NULL)
	{
		LF->MsgBox(IDS_INVALID_ITEM);
		//MessageBox(m_pRcpView->GetSafeHwnd(), "변경하려는 오더를 선택하세요", "확인", MB_ICONINFORMATION);
		return ZERO;
	}

	long nCount = pRows->GetCount();
	long nMainState = ZERO;

	CMkLock lock(&m_csOrder);

	for(int i=ZERO; i<nCount; i++)
	{
		int nSelItem = pRows->GetAt(i)->GetIndex();
		int nState = m_pRcpView->GetItemState(nSelItem);
		
		if(m_pRcpView->GetItemSecondCross(nSelItem))
		{
			CString strMsg;
			strMsg = "크로스배차된 오더의 상태를 직접 변경하실 수 없습니다.\n";
			strMsg += "해당 회원사에게 전화하셔서 처리 하시기 바랍니다.";
			MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "확인", MB_ICONINFORMATION);
			return ZERO;
		}
		
		//if(m_pRcpView->GetItemRiderAllocate(nSelItem) == 1 && nChangeState != STATE_WAIT)
		//{
		//	MessageBox(m_pRcpView->GetSafeHwnd(), "자동배차 상태의 오더를 수정하실 수 없습니다", "확인", MB_ICONINFORMATION);
		//	return ZERO;
		//}

		if(i == ZERO)
		{
			nMainState = nState;
			continue;
		}

		if(nMainState != nState)
		{
			MessageBox(m_pRcpView->GetSafeHwnd(), "상태를 변경하려는 오더의 상태가 모두 일치해야 합니다", "확인", MB_ICONINFORMATION);
			return ZERO;
		}

		if(!CheckChangeItem(nSelItem, nState, nChangeState))
		{
			MessageBox(m_pRcpView->GetSafeHwnd(), "카드결제 승인상태 오더는 상태를 변경하실 수 없습니다\r\n접수창에서 카드결제를 취소 후 상태변경을하세요", "확인", MB_ICONINFORMATION);
			return ZERO;
		}
	}

	return nCount;
}

BOOL CRcpMultiStateChange::CheckChangeItem(long nSelItem, long nPreState, long nState, long nCancelType)
{
	long nCreditCardType = m_pRcpView->GetItemCreditCardType(nSelItem);

	if(nCreditCardType == NICE_CARD_COMPLETE || nCreditCardType == NICE_CARD_COMPLETE_QUICKCALL)
	{
		if(LF->IsCardCheckState(nPreState, nCancelType) == TRUE && LF->IsCardCheckState(nState, nCancelType) == FALSE)
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CRcpMultiStateChange::CheckLockCount(long nRiderCompany, long nRNo)
{
	long nReturn = ZERO;
	CString sMsg = "";

	CMkCommand pCmd(m_pMkDb, "check_ability_allocate_state2");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), nRiderCompany);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), nRNo);

	if(pCmd.Execute())
	{
		parRet->GetValue(nReturn);	

		if(nReturn > ZERO)
		{
			if(nReturn == 1) //건수 제한 상태인지 
				sMsg = "건수 제한에 걸려 있습니다.\r\n";
			else if(nReturn == 2)
				sMsg = "자사콜 건수제한에 걸려 있습니다.\r\n";
			else if(nReturn == 3)
				sMsg = "타사콜 건수제한에 걸려 있습니다.\r\n";
			else if(nReturn == 4)
				sMsg = "시내오더 배차후 경과시간 제한입니다.\r\n";
			else if(nReturn == 5)
				sMsg = "시외오더 배차후 경과시간 제한입니다.\r\n";
			else if(nReturn == 6)
				sMsg = "시내오더 픽업후 경과시간 제한입니다.\r\n";
			else if(nReturn == 7)
				sMsg = "시외오더 픽업후 경과시간 제한입니다.\r\n";

			sMsg += "개별배차 내리시겠습니까?";

			if(MessageBox(m_pRcpView->GetSafeHwnd(), sMsg, "확인", MB_YESNO) == IDYES)
				return TRUE;
			else
				return FALSE; 
		}
	}

	return TRUE;
}


BOOL CRcpMultiStateChange::CheckRiderDeposit(long nRiderCompany, long nRNo, long nTNo)
{
	CMkCommand pCmd(m_pMkDb, "check_rider_deposit_for_allocate_2");

	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeReturn, sizeof(long), ZERO);
	pCmd.AddParameter(nRiderCompany);
	pCmd.AddParameter(nRNo);
	pCmd.AddParameter(nTNo);

	if(!pCmd.Execute()) return FALSE;

	long nRet = ZERO;
	pPar->GetValue(nRet);

	if(nRet == 1)
	{
		MessageBox(m_pRcpView->GetSafeHwnd(), "해당기사님의 잔액이 부족하여 개별배차를 내리실 수 없습니다", "확인", MB_ICONINFORMATION);
		return FALSE;
	}
	else if(nRet == 2)
	{
		MessageBox(m_pRcpView->GetSafeHwnd(), "해당기사님의 잔액이 최소배차가능 금액보다 부족하여  개별배차를 내리실 수 없습니다", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	return TRUE;
}


BOOL CRcpMultiStateChange::OrderRequest(long nTNo, long nState, long nRiderCompany, long nRNo, long nToCompany)
{
	CString sSaveItemMent = "아래의 이유로 수정 하실 수 없습니다\r\n";

	sSaveItemMent += "[정산이 완료된 공유오더]\r\n";
	sSaveItemMent += "수정요청 하시겠습니까?\r\n"; 

	if(MessageBox(m_pRcpView->GetSafeHwnd(), sSaveItemMent, "확인", MB_OKCANCEL) != IDOK)
		return FALSE;

	long nRet;

	CMkCommand pCmd(m_pMkDb, "insert_order_change_request_by_state");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	pCmd.AddParameter(nTNo);
	pCmd.AddParameter(nState);
	pCmd.AddParameter(nRiderCompany);
	pCmd.AddParameter(nRNo);
	pCmd.AddParameter(nToCompany);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.strName);

	if(pCmd.Execute())
	{
		parRet->GetValue(nRet);

		if(nRet == 2)
		{
			MessageBox(m_pRcpView->GetSafeHwnd(), "이미 요청중에 있습니다\r\n[기능] -> [완료오더 수정요청 관리]에서 확인 가능하며\r\n하루이내 응답이 없으면 자동승인 처리됩니다\r\n", "확인", MB_ICONINFORMATION);
			return FALSE;
		}

		if(nRet == ZERO) // 제대로 됨 더 이상 진행 안되게 하기위해 FALSE를 리턴
			return FALSE;
	}
	else 
		return FALSE;

	return TRUE;

}


BOOL CRcpMultiStateChange::CheckValidStateChange(long nTNo, long nPreState, long nState, long nRiderCompany, long nRNo)
{
	return TRUE;
	int nRow = m_pRcpView->m_xList.GetSelectedItem();

	if(m_pRcpView->GetItemTodayOrder(nRow) == TRUE)
		return TRUE; 

	long nPreRiderCompany = m_pRcpView->GetItemRiderCompany(nRow);
	long nPreRNo = m_pRcpView->GetItemRNo(nRow);

	if((m_ci.GetShareCode1(m_pRcpView->GetItemCompany(nRow)) !=
		m_ci.GetShareCode1(nPreRiderCompany)) && nPreRiderCompany != ZERO)
	{
		return OrderRequest(nTNo, nState, nRiderCompany, nRNo, nPreRiderCompany);
	}

	if((m_ci.GetShareCode1(m_pRcpView->GetItemCompany(nRow)) !=
		m_ci.GetShareCode1(nRiderCompany)) && nRiderCompany != ZERO)
	{
		return OrderRequest(nTNo, nState, nRiderCompany, nRNo, nRiderCompany);
	}

	if(CCompleteAfterEditDlg::IsDifferentState(nPreState, nState) == FALSE)
		return OrderRequest(nTNo, nState, nRiderCompany, nRNo, nRiderCompany);

	return TRUE;
}

BOOL CRcpMultiStateChange::CheckRiderLoadIns(long nRiderCompany, long nRNo, long nTNo)
{
	CMkCommand cmd(m_pMkDb, "check_rider_load_ins_allocate");
	cmd.AddParameter(nTNo);
	cmd.AddParameter(nRiderCompany);
	cmd.AddParameter(nRNo);
	CMkParameter *parErrorOut = cmd.AddParameter(typeString, typeOutput, 100, "");

	if(!cmd.Execute())
		return FALSE;

	CString strError;
	parErrorOut->GetValue(strError);

	if(strError.IsEmpty())
		return TRUE;

	MessageBox(m_pRcpView->GetSafeHwnd(), strError, "확인", MB_ICONEXCLAMATION);
	return FALSE;
}

int CRcpMultiStateChange::Allocate(LONG nTNo, LONG nRNo, LONG nPreState, LONG nRiderCompany, BOOL bRefresh)
{
	if(CheckLockCount(nRiderCompany, nRNo) == FALSE)
		return ZERO;

	if(CheckRiderDeposit(nRiderCompany, nRNo, nTNo) == FALSE)
		return ZERO;

	if(CheckRiderLoadIns(nRiderCompany, nRNo, nTNo) == FALSE)
		return ZERO;

	int nRet = ZERO;
	CString strMsg;

	CMkCommand pCmd(m_pMkDb, "change_item_state_allocate_2011_2"); 
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nTNo);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), nRNo);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), nRiderCompany);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), nPreState);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), STATE_OK_ONLY_MAN);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_ui.nWNo);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_ui.nCompany);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), OFFICE_OK_ONLY_MAN);
	pCmd.AddParameter(m_ui.strName);

	pCmd.Execute();

	parRet->GetValue(nRet);					


	switch(nRet)
	{
	case ZERO:
		LF->MsgBox(IDS_EXPIRED_DATA, "확인", MB_ICONEXCLAMATION);
		break;
	case 1:
	case 11: //PDA 아무행동도 안취함
		nRet = STATE_OK_ONLY_MAN;

		if(bRefresh)
			m_pRcpView->AllRefresh();
		break;

	case 10: // 기존 bUseSMS 가 nAllocType 으로 바뀜 2가 PDA 1이 SMS 0이 아무것도 안씀
		{
			CSmsDlg dlg;
			dlg.m_nRCompany = nRiderCompany;
			dlg.m_nRNo = nRNo;
			dlg.m_nTNo = nTNo;

			//if(nRet == 11)
			//	dlg.m_bSendPDA = TRUE;

			dlg.DoModal();


			nRet = STATE_OK_ONLY_MAN;

			if(bRefresh)
				m_pRcpView->AllRefresh();
			break;
		}
	case 100:
		{
			LF->MsgBox("해당오더의 상태가 변경되었습니다\r\n오더를 확인해주세요", "확인", MB_ICONINFORMATION);
			if(bRefresh)
				m_pRcpView->AllRefresh();
			break;
		}
	case 1000:
		{
			LF->MsgBox("하루가 지난오더는 정산상의 이유로 타기사개별배차가 불가능합니다", "확인", MB_ICONINFORMATION);
			if(bRefresh)
				m_pRcpView->AllRefresh();
			break;
		}

	default:
		strMsg.Format(IDS_STATE_CHANGED, LF->GetStateString(nRet));
		MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "확인", MB_ICONEXCLAMATION);
		break;
	}
	return nRet;
}

BOOL CRcpMultiStateChange::CheckEventOrder(long nTNo)
{
	CMkCommand cmd(m_pMkDb, "LuckyOrder_Cancel_Confirm");
	CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	cmd.AddParameter(nTNo); 
	CMkParameter *parOut = cmd.AddParameter(typeString, typeOutput, 1000, "");

	if(cmd.Execute()) {
		long nRet = 0; CString strMsg;
		parRet->GetValue(nRet);
		parOut->GetValue(strMsg);

		if(nRet == 1) {
			if(MessageBox(NULL, strMsg, "확인", MB_OKCANCEL) == IDOK)
				return FALSE;
		}
		else 
			return TRUE;
	}

	return FALSE;
}

int CRcpMultiStateChange::CancelOrder(LONG nCompany, LONG nTNo, LONG nPreState, CString strCancel, int nCancelType, 
						  int nPenaltyMin, int nPenaltyCharge, BOOL bChangeToWait, BOOL bRefresh, long nRNo)
{
	//주석쉽게 풀기
	if(CheckValidStateChange(nTNo, nPreState, STATE_CANCELED) == FALSE)
		return ZERO;

	if(!CheckEventOrder(nTNo))
		return 0;

	BOOL bClearRider = FALSE;

	if(nRNo > 0 && nCancelType != 10)
		CheckRiderClear(bClearRider);

	CBranchInfo *pBranch = LF->GetBranchInfo(nCompany);

	if(pBranch->bNotUseEtcForCancel)
		strCancel = "";

	int nRet = ZERO;
	CString strMsg;
	CMkCommand pCmd(m_pMkDb, "change_item_state_cancel_2011_4");

	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nTNo);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), ZERO);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), nPreState);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), STATE_CANCELED);
	pCmd.AddParameter(typeString, typeInput, strCancel.GetLength(), strCancel);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), nCancelType);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);  //  2007-10-04 추가 오더로그 쌓기
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_ui.nWNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nPenaltyMin);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nPenaltyCharge);
	pCmd.AddParameter(bChangeToWait);
	pCmd.AddParameter(m_ui.strName);
	pCmd.AddParameter(bClearRider);

	if(!pCmd.Execute()) return ZERO;
	parRet->GetValue(nRet);			

	switch(nRet)
	{
	case ZERO:
		LF->MsgBox(IDS_EXPIRED_DATA, "확인", MB_ICONEXCLAMATION);
		break;
	case 1:

		nRet = STATE_CANCELED;
		if(bRefresh)
			m_pRcpView->RefreshList("", "", NULL, FALSE, FALSE);
		break;
	case 100:  // 2007-10-04 추가 		
		strMsg = "크로스배차된 오더를 직접 취소하실 수 없습니다.\n";
		strMsg += "해당 회원사에게 전화하셔서 취소 요청을 하시기 바랍니다.";
		MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "확인", MB_ICONINFORMATION);
		break;
	case 300:  // 2007-10-04 추가 		
		strMsg = "당일 연계오더가 취소되지 않았습니다..\n";
		strMsg += "로지소프트로 문의하세요";
		MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "확인", MB_ICONINFORMATION);
		break;
	case 200:  // 2007-10-04 추가 		
		strMsg = "연계오더로 인해 콜이 수행중입니다. \n";
		strMsg += "해당 회원사에게 전화하셔서 취소 요청을 하시기 바랍니다.";
		MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "확인", MB_ICONINFORMATION);
		break;
	default:
		strMsg.Format(IDS_STATE_CHANGED, LF->GetStateString(nRet));
		MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "확인", MB_ICONEXCLAMATION);
		break;
	}

	return nRet;
}

int CRcpMultiStateChange::CompleteState(LONG nCompany, LONG nTNo, LONG nRNo, LONG nPreState, BOOL bNoQueryMsg, BOOL bRefresh)
{
	if(CheckValidStateChange(nTNo, nPreState, STATE_ALLOCATED) == FALSE)
		return ZERO; 

	if(nRNo == 0)
	{
		if(MessageBox(NULL, "배차된 기사가 없습니다.\r\n배차상태로 변경하시겠습니까?", "확인", MB_OKCANCEL) != IDOK)
			return 0;
	}

	CBranchInfo *pBranch = LF->GetBranchInfo(nCompany);

	CMkCommand pCmd(m_pMkDb, "change_item_state_complete_2011"); 
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nTNo); 
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), pBranch->nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nPreState);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), STATE_ALLOCATED);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nWNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nCompany);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), OFFICE_ALLOCATED); 
	pCmd.AddParameter(m_ui.strName);

	if(!pCmd.Execute()) return ZERO;

	CString strMsg;
	long nRet = 0;
	parRet->GetValue(nRet);					

	switch(nRet)
	{
	case ZERO:
		LF->MsgBox(IDS_EXPIRED_DATA, "확인", MB_ICONEXCLAMATION);
		break;
	case 1:
		nRet = STATE_ALLOCATED;
		if(bRefresh)
			m_pRcpView->AllRefresh();
		break;

	case 10:
		{
			CSmsDlg dlg;
			dlg.m_nRCompany = pBranch->nCompanyCode;
			dlg.m_nRNo = nRNo;
			dlg.m_nTNo = nTNo;
			dlg.DoModal();

			m_pRcpView->AllRefresh();
			nRet = STATE_OK_ONLY_MAN;
			break;
		}

	default:
		strMsg.Format(IDS_STATE_CHANGED, LF->GetStateString(nRet));
		MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "확인", MB_ICONEXCLAMATION);
		break;
	}

	return nRet;
}


int CRcpMultiStateChange::PickupState(LONG nCompany, LONG nTNo, LONG nRNo, LONG nPreState, BOOL bNoQueryMsg, BOOL bRefresh)
{
	if(CheckValidStateChange(nTNo, nPreState, STATE_PICKUP) == FALSE)
		return ZERO;

	if(nRNo == 0)
	{
		if(MessageBox(NULL, "배차된 기사가 없습니다.\r\n픽업상태로 변경하시겠습니까?", "확인", MB_OKCANCEL) != IDOK)
			return 0;
	}

	CBranchInfo *pBranch = LF->GetBranchInfo(nCompany);

	int nRet = ZERO;
	CString strMsg;

	CMkCommand pCmd(m_pMkDb, "change_item_state_pickup_2011");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nTNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), pBranch->nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nPreState);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), STATE_PICKUP);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nWNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), OFFICE_PICKUP);
	pCmd.AddParameter(m_ui.strName);

	if(!pCmd.Execute()) return ZERO;
	parRet->GetValue(nRet);					

	switch(nRet)
	{
	case ZERO:
		LF->MsgBox(IDS_EXPIRED_DATA, "확인", MB_ICONEXCLAMATION);
		break;
	case 1:
		nRet = STATE_PICKUP;
		
		if(bRefresh)
			m_pRcpView->AllRefresh();
		break;

	case 10:
		{
			CSmsDlg dlg;
			dlg.m_nRCompany = pBranch->nCompanyCode;
			dlg.m_nRNo = nRNo;
			dlg.m_nTNo = nTNo;
			dlg.DoModal();

			m_pRcpView->AllRefresh();
			nRet = STATE_OK_ONLY_MAN;
			break;
		}

	default:
		strMsg.Format(IDS_STATE_CHANGED, LF->GetStateString(nRet));
		MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "확인", MB_ICONEXCLAMATION);
		break;
	}

	return nRet;
}

int CRcpMultiStateChange::InquiryState(LONG nTNo, LONG nPreState, BOOL bNoQueryMsg, BOOL bRefresh)
{
	if(CheckValidStateChange(nTNo, nPreState, STATE_INQUIRY) == FALSE)
		return ZERO; 

	CMkCommand pCmd(m_pMkDb, "[change_item_state_InQuiry]");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nTNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), 0);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), nPreState);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), STATE_INQUIRY);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_ui.nCompany);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_ui.nWNo);
	
	if(!pCmd.Execute()) return ZERO;

	long nRet;
	CString strMsg;
	parRet->GetValue(nRet);					
	switch(nRet)
	{
	case ZERO:
		LF->MsgBox(IDS_EXPIRED_DATA, "확인", MB_ICONEXCLAMATION);
		break;
	case 1:
		nRet = STATE_INQUIRY;
		if(bRefresh)
			m_pRcpView->AllRefresh();
		break;
	default:
		strMsg.Format(IDS_STATE_CHANGED, LF->GetStateString(nRet));
		MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "확인", MB_ICONEXCLAMATION);
		break;
	}

	return nRet;
}


int CRcpMultiStateChange::FinishState(LONG nTNo, LONG nPreState, BOOL bNoQueryMsg, BOOL bRefresh)
{
	if(CheckValidStateChange(nTNo, nPreState, STATE_FINISH) == FALSE)
		return ZERO;

	//if(MessageBox("종료 하시겠습니까?", "오더종료", MB_YESNO | MB_ICONINFORMATION) == IDYES	)
	//{
	CMkCommand pCmd(m_pMkDb, "change_item_state_finish_2011_1");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nTNo);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), nPreState);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), STATE_FINISH);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_ui.nWNo);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_ui.nCompany);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), OFFICE_FINISH);
	pCmd.AddParameter(m_ui.strName);

	if(!pCmd.Execute()) return ZERO;

	long nRet;
	CString strMsg;
	parRet->GetValue(nRet);					
	switch(nRet)
	{
	case ZERO:
		LF->MsgBox(IDS_EXPIRED_DATA, "확인", MB_ICONEXCLAMATION);
		break;
	case 1:
		nRet = STATE_FINISH;
		if(bRefresh)
			m_pRcpView->AllRefresh();
		break;
	default:
		strMsg.Format(IDS_STATE_CHANGED, LF->GetStateString(nRet));
		MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "확인", MB_ICONEXCLAMATION);
		break;
	}

	return nRet;
}

int CRcpMultiStateChange::CancelAllocateToWait(LONG nTNo, LONG nPreState, BOOL bNoQueryMsg, BOOL bRefresh, long nRNo)
{
	if(CheckValidStateChange(nTNo, nPreState, STATE_WAIT) == FALSE)
		return ZERO;

	BOOL bClearRider = FALSE;

	if(nRNo > 0)
		CheckRiderClear(bClearRider);
			
	CMkCommand pCmd(m_pMkDb, "change_item_state_wait_2011_1");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nTNo);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), nPreState);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), STATE_WAIT);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), LF->GetCurBranchInfo()->bUserIDSequence);
	pCmd.AddParameter(m_ui.strName);
	pCmd.AddParameter(bClearRider);

	if(!pCmd.Execute()) return FALSE;

	long nRet = 0;
	parRet->GetValue(nRet);			

	CString strMsg;

	switch(nRet)
	{
	case ZERO:
		LF->MsgBox(IDS_EXPIRED_DATA, "확인", MB_ICONEXCLAMATION);
		break;
	case 1:
		nRet = STATE_WAIT;
		if(bRefresh)
			m_pRcpView->AllRefresh();
		break;
	default:
		strMsg.Format(IDS_STATE_CHANGED, LF->GetStateString(nRet));
		MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "확인", MB_ICONEXCLAMATION);
		break;
	}

	return nRet;
}

int CRcpMultiStateChange::CancelAllocate(LONG nTNo, LONG nPreState, BOOL bNoQueryMsg, BOOL bShare, BOOL bRefresh, long nRNo)
{
	if(CheckValidStateChange(nTNo, nPreState, STATE_OK) == FALSE)
		return ZERO;

	BOOL bClearRider = FALSE;

	if(nRNo > 0)
		CheckRiderClear(bClearRider);

	BOOL bUserIDSequence = LF->GetCurBranchInfo()->bUserIDSequence;
	CMkCommand pCmd(m_pMkDb, "change_item_state_allocate_cancel_2011_1");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nTNo);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), ZERO);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), nPreState);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), STATE_OK);
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), bShare);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bUserIDSequence);		
	pCmd.AddParameter(m_ui.strName);
	pCmd.AddParameter(bClearRider);

	if(!pCmd.Execute()) return ZERO;

	long nRet = 0;
	CString strMsg;

	parRet->GetValue(nRet);
	switch(nRet)
	{
	case ZERO:
		LF->MsgBox(IDS_EXPIRED_DATA, "확인", MB_ICONEXCLAMATION);
		break;
	case 1:
		nRet = STATE_OK;
		if(bRefresh)
			m_pRcpView->AllRefresh();
		break;
	default:
		strMsg.Format(IDS_STATE_CHANGED, LF->GetStateString(nRet));
		MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "확인", MB_ICONEXCLAMATION);
		break;
}
	return nRet;
}

int CRcpMultiStateChange::CancelReserve(LONG nTNo, LONG nPreState)
{
	CString strMsg = "예약을 해제하시겠습니까?";
	int nRet = ZERO;
 
	if(MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "예약해제", MB_YESNO | MB_ICONINFORMATION) == IDYES)
	{
		CMkCommand pCmd(m_pMkDb, "change_item_state_reserve_cancel_2011_1");
		CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nTNo);
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), nPreState);
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), STATE_OK);
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_ui.nWNo);
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_ui.nCompany);
		pCmd.AddParameter(m_ui.strName);

		if(!pCmd.Execute()) return ZERO; 
		parRet->GetValue(nRet);					
		switch(nRet)
		{ 
		case ZERO:
			LF->MsgBox(IDS_EXPIRED_DATA, "확인", MB_ICONEXCLAMATION);
			break;
		case 1:
			nRet = STATE_OK;
			m_pRcpView->AllRefresh();
			break;
		default:
			strMsg.Format(IDS_STATE_CHANGED, LF->GetStateString(nRet));
			MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "확인", MB_ICONEXCLAMATION);
			break;
		}
	}
	return nRet;
}

int CRcpMultiStateChange::ReserveOrder(LONG nTNo, LONG nPreState, long nReleaseMin, COleDateTime dtReserve, BOOL bChangeRiderForReserve)
{
  	CString strMsg = "예약 하시겠습니까?";
	int nRet = ZERO;

	if(MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "예약", 
		MB_YESNO | MB_ICONINFORMATION) == IDYES)
	{
		CMkCommand pCmd(m_pMkDb, "change_item_state_reserve_2011_2");

		CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), nTNo);
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), ZERO);
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), nPreState);
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), STATE_RESERVED);
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_ui.nWNo);
		pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_ui.nCompany);
		pCmd.AddParameter(m_ui.strName);
		pCmd.AddParameter(nReleaseMin);
		pCmd.AddParameter(dtReserve);
		pCmd.AddParameter(bChangeRiderForReserve);

		if(!pCmd.Execute()) return ZERO;
		parRet->GetValue(nRet);					
		switch(nRet) 
		{
		case ZERO:
			LF->MsgBox(IDS_EXPIRED_DATA, "확인", MB_ICONEXCLAMATION);
			break;
		case 1:
			nRet = STATE_RESERVED;
			m_pRcpView->AllRefresh();
			break;
		default:
			strMsg.Format(IDS_STATE_CHANGED, LF->GetStateString(nRet));
			MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "확인", MB_ICONEXCLAMATION);
			break;
		}
	}
	return nRet;
}

void CRcpMultiStateChange::CheckRiderClear(BOOL &bClearRider)
{
	CString strTemp = "기사님이 배차중입니다. 기사정보를 삭제하시겠습니까?\r\n\r\n";
	strTemp += "[   예   ] 기사정보를 삭제함\r\n";
	strTemp += "[아니요] 기사정보를 남겨둠\r\n";

	if(MessageBox(m_pRcpView->GetSafeHwnd(), strTemp, "확인", MB_YESNO) == IDYES)
		bClearRider = TRUE;
	else
		bClearRider = FALSE;
}