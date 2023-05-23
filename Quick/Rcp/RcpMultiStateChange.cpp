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
	if(!LF->POWER_CHECK(2009, "��������", TRUE))
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
		CString strTemp; strTemp.Format("%d���� ���� �������� �Ͻðڽ��ϱ�?", nItemCount);

		if(nItemCount > ONE)
		{
			if(MessageBox(NULL, strTemp, "Ȯ��", MB_OKCANCEL) != IDOK)
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
	if(!LF->POWER_CHECK(2002, "�������º���", TRUE))
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
			if(MessageBox(m_pRcpView->GetSafeHwnd(), "��� ���·� �����Ͻðڽ��ϱ�?", "���º���", MB_YESNO | MB_ICONINFORMATION) != IDYES)
				return;
		}
		else if(nState == STATE_OK)
		{
			if(MessageBox(m_pRcpView->GetSafeHwnd(), "���� ���·� �����Ͻðڽ��ϱ�?", "���º���", MB_YESNO | MB_ICONINFORMATION) != IDYES)
				return;
		}
		else if(nState == STATE_ALLOCATED)
		{
			if(MessageBox(m_pRcpView->GetSafeHwnd(), "�������·� �����Ͻðڽ��ϱ�?", "���º���", MB_YESNO | MB_ICONINFORMATION) != IDYES)
				return;
		}
		else if(nState == STATE_FINISH)
		{
			if(MessageBox(m_pRcpView->GetSafeHwnd(), "�Ϸ� �Ͻðڽ��ϱ�?", "���º���", MB_YESNO | MB_ICONINFORMATION) != IDYES)
				return;
		}
		else if(nState == STATE_INQUIRY)
		{
			if(MessageBox(m_pRcpView->GetSafeHwnd(), "���ǻ��·� ���� �Ͻðڽ��ϱ�?", "���º���", MB_YESNO | MB_ICONINFORMATION) != IDYES)
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
			CString strTitle = "[����] " + m_pRcpView->GetItemStart(nItem) + " -> " + m_pRcpView->GetItemDest(nItem);
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

					if(!LF->POWER_CHECK(2009, "��������", TRUE))
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
		strCancel = "[���:������]";
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
		saCancel.Add("[���1:��ȭ����]");
		saCancel.Add("[���2:�ð�����]");
		saCancel.Add("[���3:������̻�]");
		saCancel.Add("[���4:����ũ��ҷ�]");
		saCancel.Add("[���5:��޺Ұ��Ұ�]");
		saCancel.Add("[���6:������]");
		saCancel.Add("[���7:�Ϻ����]");
		saCancel.Add("[���8:������]");
		saCancel.Add("[���9:��������]");
		saCancel.Add("[���10:�������]");
		saCancel.Add("[���:�����Ǽ�]");

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
					strCancel = "[���:" + dlg.m_strEtc + "]";
				else 
					strCancel = "[���:��Ÿ]";

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
		//MessageBox(m_pRcpView->GetSafeHwnd(), "�����Ϸ��� ������ �����ϼ���", "Ȯ��", MB_ICONINFORMATION);
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
			strMsg = "ũ�ν������� ������ ���¸� ���� �����Ͻ� �� �����ϴ�.\n";
			strMsg += "�ش� ȸ���翡�� ��ȭ�ϼż� ó�� �Ͻñ� �ٶ��ϴ�.";
			MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "Ȯ��", MB_ICONINFORMATION);
			return ZERO;
		}
		
		//if(m_pRcpView->GetItemRiderAllocate(nSelItem) == 1 && nChangeState != STATE_WAIT)
		//{
		//	MessageBox(m_pRcpView->GetSafeHwnd(), "�ڵ����� ������ ������ �����Ͻ� �� �����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		//	return ZERO;
		//}

		if(i == ZERO)
		{
			nMainState = nState;
			continue;
		}

		if(nMainState != nState)
		{
			MessageBox(m_pRcpView->GetSafeHwnd(), "���¸� �����Ϸ��� ������ ���°� ��� ��ġ�ؾ� �մϴ�", "Ȯ��", MB_ICONINFORMATION);
			return ZERO;
		}

		if(!CheckChangeItem(nSelItem, nState, nChangeState))
		{
			MessageBox(m_pRcpView->GetSafeHwnd(), "ī����� ���λ��� ������ ���¸� �����Ͻ� �� �����ϴ�\r\n����â���� ī������� ��� �� ���º������ϼ���", "Ȯ��", MB_ICONINFORMATION);
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
			if(nReturn == 1) //�Ǽ� ���� �������� 
				sMsg = "�Ǽ� ���ѿ� �ɷ� �ֽ��ϴ�.\r\n";
			else if(nReturn == 2)
				sMsg = "�ڻ��� �Ǽ����ѿ� �ɷ� �ֽ��ϴ�.\r\n";
			else if(nReturn == 3)
				sMsg = "Ÿ���� �Ǽ����ѿ� �ɷ� �ֽ��ϴ�.\r\n";
			else if(nReturn == 4)
				sMsg = "�ó����� ������ ����ð� �����Դϴ�.\r\n";
			else if(nReturn == 5)
				sMsg = "�ÿܿ��� ������ ����ð� �����Դϴ�.\r\n";
			else if(nReturn == 6)
				sMsg = "�ó����� �Ⱦ��� ����ð� �����Դϴ�.\r\n";
			else if(nReturn == 7)
				sMsg = "�ÿܿ��� �Ⱦ��� ����ð� �����Դϴ�.\r\n";

			sMsg += "�������� �����ðڽ��ϱ�?";

			if(MessageBox(m_pRcpView->GetSafeHwnd(), sMsg, "Ȯ��", MB_YESNO) == IDYES)
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
		MessageBox(m_pRcpView->GetSafeHwnd(), "�ش������ �ܾ��� �����Ͽ� ���������� ������ �� �����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		return FALSE;
	}
	else if(nRet == 2)
	{
		MessageBox(m_pRcpView->GetSafeHwnd(), "�ش������ �ܾ��� �ּҹ������� �ݾ׺��� �����Ͽ�  ���������� ������ �� �����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		return FALSE;
	}

	return TRUE;
}


BOOL CRcpMultiStateChange::OrderRequest(long nTNo, long nState, long nRiderCompany, long nRNo, long nToCompany)
{
	CString sSaveItemMent = "�Ʒ��� ������ ���� �Ͻ� �� �����ϴ�\r\n";

	sSaveItemMent += "[������ �Ϸ�� ��������]\r\n";
	sSaveItemMent += "������û �Ͻðڽ��ϱ�?\r\n"; 

	if(MessageBox(m_pRcpView->GetSafeHwnd(), sSaveItemMent, "Ȯ��", MB_OKCANCEL) != IDOK)
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
			MessageBox(m_pRcpView->GetSafeHwnd(), "�̹� ��û�߿� �ֽ��ϴ�\r\n[���] -> [�Ϸ���� ������û ����]���� Ȯ�� �����ϸ�\r\n�Ϸ��̳� ������ ������ �ڵ����� ó���˴ϴ�\r\n", "Ȯ��", MB_ICONINFORMATION);
			return FALSE;
		}

		if(nRet == ZERO) // ����� �� �� �̻� ���� �ȵǰ� �ϱ����� FALSE�� ����
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

	MessageBox(m_pRcpView->GetSafeHwnd(), strError, "Ȯ��", MB_ICONEXCLAMATION);
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
		LF->MsgBox(IDS_EXPIRED_DATA, "Ȯ��", MB_ICONEXCLAMATION);
		break;
	case 1:
	case 11: //PDA �ƹ��ൿ�� ������
		nRet = STATE_OK_ONLY_MAN;

		if(bRefresh)
			m_pRcpView->AllRefresh();
		break;

	case 10: // ���� bUseSMS �� nAllocType ���� �ٲ� 2�� PDA 1�� SMS 0�� �ƹ��͵� �Ⱦ�
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
			LF->MsgBox("�ش������ ���°� ����Ǿ����ϴ�\r\n������ Ȯ�����ּ���", "Ȯ��", MB_ICONINFORMATION);
			if(bRefresh)
				m_pRcpView->AllRefresh();
			break;
		}
	case 1000:
		{
			LF->MsgBox("�Ϸ簡 ���������� ������� ������ Ÿ��簳�������� �Ұ����մϴ�", "Ȯ��", MB_ICONINFORMATION);
			if(bRefresh)
				m_pRcpView->AllRefresh();
			break;
		}

	default:
		strMsg.Format(IDS_STATE_CHANGED, LF->GetStateString(nRet));
		MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "Ȯ��", MB_ICONEXCLAMATION);
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
			if(MessageBox(NULL, strMsg, "Ȯ��", MB_OKCANCEL) == IDOK)
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
	//�ּ����� Ǯ��
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
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);  //  2007-10-04 �߰� �����α� �ױ�
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
		LF->MsgBox(IDS_EXPIRED_DATA, "Ȯ��", MB_ICONEXCLAMATION);
		break;
	case 1:

		nRet = STATE_CANCELED;
		if(bRefresh)
			m_pRcpView->RefreshList("", "", NULL, FALSE, FALSE);
		break;
	case 100:  // 2007-10-04 �߰� 		
		strMsg = "ũ�ν������� ������ ���� ����Ͻ� �� �����ϴ�.\n";
		strMsg += "�ش� ȸ���翡�� ��ȭ�ϼż� ��� ��û�� �Ͻñ� �ٶ��ϴ�.";
		MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "Ȯ��", MB_ICONINFORMATION);
		break;
	case 300:  // 2007-10-04 �߰� 		
		strMsg = "���� ��������� ��ҵ��� �ʾҽ��ϴ�..\n";
		strMsg += "��������Ʈ�� �����ϼ���";
		MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "Ȯ��", MB_ICONINFORMATION);
		break;
	case 200:  // 2007-10-04 �߰� 		
		strMsg = "��������� ���� ���� �������Դϴ�. \n";
		strMsg += "�ش� ȸ���翡�� ��ȭ�ϼż� ��� ��û�� �Ͻñ� �ٶ��ϴ�.";
		MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "Ȯ��", MB_ICONINFORMATION);
		break;
	default:
		strMsg.Format(IDS_STATE_CHANGED, LF->GetStateString(nRet));
		MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "Ȯ��", MB_ICONEXCLAMATION);
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
		if(MessageBox(NULL, "������ ��簡 �����ϴ�.\r\n�������·� �����Ͻðڽ��ϱ�?", "Ȯ��", MB_OKCANCEL) != IDOK)
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
		LF->MsgBox(IDS_EXPIRED_DATA, "Ȯ��", MB_ICONEXCLAMATION);
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
		MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "Ȯ��", MB_ICONEXCLAMATION);
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
		if(MessageBox(NULL, "������ ��簡 �����ϴ�.\r\n�Ⱦ����·� �����Ͻðڽ��ϱ�?", "Ȯ��", MB_OKCANCEL) != IDOK)
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
		LF->MsgBox(IDS_EXPIRED_DATA, "Ȯ��", MB_ICONEXCLAMATION);
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
		MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "Ȯ��", MB_ICONEXCLAMATION);
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
		LF->MsgBox(IDS_EXPIRED_DATA, "Ȯ��", MB_ICONEXCLAMATION);
		break;
	case 1:
		nRet = STATE_INQUIRY;
		if(bRefresh)
			m_pRcpView->AllRefresh();
		break;
	default:
		strMsg.Format(IDS_STATE_CHANGED, LF->GetStateString(nRet));
		MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "Ȯ��", MB_ICONEXCLAMATION);
		break;
	}

	return nRet;
}


int CRcpMultiStateChange::FinishState(LONG nTNo, LONG nPreState, BOOL bNoQueryMsg, BOOL bRefresh)
{
	if(CheckValidStateChange(nTNo, nPreState, STATE_FINISH) == FALSE)
		return ZERO;

	//if(MessageBox("���� �Ͻðڽ��ϱ�?", "��������", MB_YESNO | MB_ICONINFORMATION) == IDYES	)
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
		LF->MsgBox(IDS_EXPIRED_DATA, "Ȯ��", MB_ICONEXCLAMATION);
		break;
	case 1:
		nRet = STATE_FINISH;
		if(bRefresh)
			m_pRcpView->AllRefresh();
		break;
	default:
		strMsg.Format(IDS_STATE_CHANGED, LF->GetStateString(nRet));
		MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "Ȯ��", MB_ICONEXCLAMATION);
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
		LF->MsgBox(IDS_EXPIRED_DATA, "Ȯ��", MB_ICONEXCLAMATION);
		break;
	case 1:
		nRet = STATE_WAIT;
		if(bRefresh)
			m_pRcpView->AllRefresh();
		break;
	default:
		strMsg.Format(IDS_STATE_CHANGED, LF->GetStateString(nRet));
		MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "Ȯ��", MB_ICONEXCLAMATION);
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
		LF->MsgBox(IDS_EXPIRED_DATA, "Ȯ��", MB_ICONEXCLAMATION);
		break;
	case 1:
		nRet = STATE_OK;
		if(bRefresh)
			m_pRcpView->AllRefresh();
		break;
	default:
		strMsg.Format(IDS_STATE_CHANGED, LF->GetStateString(nRet));
		MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "Ȯ��", MB_ICONEXCLAMATION);
		break;
}
	return nRet;
}

int CRcpMultiStateChange::CancelReserve(LONG nTNo, LONG nPreState)
{
	CString strMsg = "������ �����Ͻðڽ��ϱ�?";
	int nRet = ZERO;
 
	if(MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "��������", MB_YESNO | MB_ICONINFORMATION) == IDYES)
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
			LF->MsgBox(IDS_EXPIRED_DATA, "Ȯ��", MB_ICONEXCLAMATION);
			break;
		case 1:
			nRet = STATE_OK;
			m_pRcpView->AllRefresh();
			break;
		default:
			strMsg.Format(IDS_STATE_CHANGED, LF->GetStateString(nRet));
			MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "Ȯ��", MB_ICONEXCLAMATION);
			break;
		}
	}
	return nRet;
}

int CRcpMultiStateChange::ReserveOrder(LONG nTNo, LONG nPreState, long nReleaseMin, COleDateTime dtReserve, BOOL bChangeRiderForReserve)
{
  	CString strMsg = "���� �Ͻðڽ��ϱ�?";
	int nRet = ZERO;

	if(MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "����", 
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
			LF->MsgBox(IDS_EXPIRED_DATA, "Ȯ��", MB_ICONEXCLAMATION);
			break;
		case 1:
			nRet = STATE_RESERVED;
			m_pRcpView->AllRefresh();
			break;
		default:
			strMsg.Format(IDS_STATE_CHANGED, LF->GetStateString(nRet));
			MessageBox(m_pRcpView->GetSafeHwnd(), strMsg, "Ȯ��", MB_ICONEXCLAMATION);
			break;
		}
	}
	return nRet;
}

void CRcpMultiStateChange::CheckRiderClear(BOOL &bClearRider)
{
	CString strTemp = "������ �������Դϴ�. ��������� �����Ͻðڽ��ϱ�?\r\n\r\n";
	strTemp += "[   ��   ] ��������� ������\r\n";
	strTemp += "[�ƴϿ�] ��������� ���ܵ�\r\n";

	if(MessageBox(m_pRcpView->GetSafeHwnd(), strTemp, "Ȯ��", MB_YESNO) == IDYES)
		bClearRider = TRUE;
	else
		bClearRider = FALSE;
}