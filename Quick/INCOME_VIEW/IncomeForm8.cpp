// IncomeForm8.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "IncomeForm8.h"

#include "IncomeForm6.h"
#include "RiderReportDlg.h"
#include "RiderDepositMsgDlg.h"
#include "MakeFixedDepositDlg.h"

// CIncomeForm8

IMPLEMENT_DYNCREATE(CIncomeForm8, CMyFormView)

CIncomeForm8::CIncomeForm8()
	: CMyFormView(CIncomeForm8::IDD)
{
}

CIncomeForm8::~CIncomeForm8()
{
}

void CIncomeForm8::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_REPORT_LIST, m_wndReport);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);
	DDX_Control(pDX, IDC_RNO_EDIT, m_RNoEdit);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_NOT_REPORT_CHECK, m_chkNotReport);
	DDX_Control(pDX, IDC_REPORT_CHECK, m_chkReport);
	DDX_Control(pDX, IDC_INCOME_COMPLETE_CHECK, m_chkIncomeComplete);
	DDX_Control(pDX, IDC_OUTPUT_COMPLETE_CHECK, m_chkOutputComplete);
	DDX_Control(pDX, IDC_GIVE_STATIC, m_stcGive);
	DDX_Control(pDX, IDC_TAKE_STATIC, m_stcTake);
}

BEGIN_MESSAGE_MAP(CIncomeForm8, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_EN_CHANGE(IDC_RNO_EDIT, OnEnChangeRnoEdit)
	ON_BN_CLICKED(IDC_NOT_REPORT_CHECK, OnBnClickedNotReportCheck)
	ON_BN_CLICKED(IDC_REPORT_CHECK, OnBnClickedReportCheck)
	ON_BN_CLICKED(IDC_INCOME_COMPLETE_CHECK, OnBnClickedIncomeCompleteCheck)
	ON_BN_CLICKED(IDC_OUTPUT_COMPLETE_CHECK, OnBnClickedOutputCompleteCheck)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT_LIST, OnDblClickList)
	ON_NOTIFY(NM_CLICK, IDC_REPORT_LIST, OnClickList)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_MAKE_FIXED_DEPOSIT, OnMakeFixedDeposit)
	ON_COMMAND(ID_HALF_INSERT_FIXED_DEPOSIT, OnHalfInsertFixedDeposit)
	ON_COMMAND(ID_DELETE_FIXED_DEPOSIT, OnDeleteFixedDeposit)
	ON_COMMAND(ID_NOT_REPORT, OnNotReport)
	ON_COMMAND(ID_REPORT_COMPLETE, OnReportComplete)
	ON_COMMAND(ID_INCOME_COMPLETE, OnIncomeComplete)
	ON_COMMAND(ID_EXCEL, OnViewExcel)
END_MESSAGE_MAP()


// CIncomeForm8 진단입니다.

#ifdef _DEBUG
void CIncomeForm8::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CIncomeForm8::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CIncomeForm8 메시지 처리기입니다.

void CIncomeForm8::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CIncomeForm8::RefreshList()
{
	CMyFormView::RefreshList();

	m_wndReport.DeleteAllItems();
	UpdateData(TRUE);

	CString sRNo;
	m_RNoEdit.GetWindowText(sRNo);

	CMkRecordset pRs(m_pMkDb); 
	CMkCommand pCmd(m_pMkDb, "select_rider_fixeddeposit_taking_log_5");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);

	if(!pRs.Execute(&pCmd)) return;

	long nID, nRNo, nFixedDeposit, nWNo, nState, nCreditOrderSum, nCompany, nRiderIncomeDay, nTotal;
	CString strRName, strTakeDate, strEtc;
	BOOL bWeeklyDeposit, bSameRiderIncomeDay;
	COleDateTime dtGenerate, dtCreditOrderStart, dtCreditOrderEnd;
	CString strBankName, strBankAccount, strBankAccountOwner, strMemo, strHp;

	char buffer[20];

	for(int i=ZERO; i<pRs.GetRecordCount(); i++)
	{
		ST_DEPOSIT *st = new ST_DEPOSIT;

		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("nFixedDeposit", nFixedDeposit);
		pRs.GetFieldValue("nWNo", nWNo);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("sRName", strRName);
		pRs.GetFieldValue("bWeeklyDeposit", bWeeklyDeposit);
		pRs.GetFieldValue("sTakeDate", strTakeDate);
		pRs.GetFieldValue("dtGenerate", dtGenerate);
		pRs.GetFieldValue("nCreditOrderSum", nCreditOrderSum);
		pRs.GetFieldValue("dtCreditOrderStart", dtCreditOrderStart);
		pRs.GetFieldValue("dtCreditOrderEnd", dtCreditOrderEnd);
		pRs.GetFieldValue("sEtc", strEtc);
		pRs.GetFieldValue("nRiderIncomeDay", nRiderIncomeDay);
		pRs.GetFieldValue("bSameRiderIncomeDay", bSameRiderIncomeDay);
		pRs.GetFieldValue("sBankName", strBankName);
		pRs.GetFieldValue("sBankAccount", strBankAccount);
		pRs.GetFieldValue("sBankAccountOwner", strBankAccountOwner);
		pRs.GetFieldValue("sMemo", strMemo);
		pRs.GetFieldValue("nTotal", nTotal);
		pRs.GetFieldValue("sHp", strHp);

		strHp.Replace("-", "");
	
		COleDateTime dtMainDate(_ttoi(strTakeDate.Left(4)), _ttoi(strTakeDate.Mid(4, 2)), _ttoi(strTakeDate.Right(2)), 0, 0, 0);
		COleDateTime dtCur = COleDateTime::GetCurrentTime();
		dtCur.SetDateTime(dtCur.GetYear(), dtCur.GetMonth(), dtCur.GetDay(), 0, 0, 0);

		COleDateTime dtCompareDate;
		dtCompareDate = LF->GetCompareDate(bWeeklyDeposit, dtMainDate, nRiderIncomeDay, bSameRiderIncomeDay);

		st->nID = nID;
		st->nCompany = nCompany;
		st->nTotal = nTotal;
		st->nState;
		st->dtCreditOrderStart = dtCreditOrderStart;
		st->dtCreditOrderEnd = dtCreditOrderEnd;
		st->dtCompareDate = dtCompareDate;
		st->strBankName = strBankName;
		st->strBankAccount = strBankAccount;
		st->strBankAccountOwner = strBankAccountOwner;
		st->strEtc = strEtc;
		st->strMemo = strMemo;
		st->nRNo = nRNo;
		st->nState = nState;
		st->strRName = strRName;
		st->nFixedDeposit = nFixedDeposit;
		st->strHp = strHp;

		m_wndReport.InsertItem(i, itoa(nRNo, buffer, 10), -1, 0);
		m_wndReport.SetItemText(i, 1, strRName);
		m_wndReport.SetItemText(i, 2, dtCreditOrderStart.Format("%y-%m-%d") + " ~ " + dtCreditOrderEnd.Format("%y-%m-%d"));
		m_wndReport.SetItemText(i, 3, dtCompareDate.Format("%y-%m-%d"));

		CString strState = "";

		if(nState == ZERO)
			strState = "미정산";
		else if(nState == 1)
			strState = "정산완료";
		else if(nState == 2) 
		{
			if(nTotal < ZERO)
				strState = "송금완료";
			else
				strState = "입금완료";
		}

		m_wndReport.SetItemText(i, 4, strState);

		if(nTotal > ZERO)
		{
			m_wndReport.SetItemText(i, 5, LF->GetMyNumberFormat(nTotal));
			m_wndReport.SetItemText(i, 6, "");
		}
		else if(nTotal <= ZERO)
		{
			m_wndReport.SetItemText(i, 5, "");
			m_wndReport.SetItemText(i, 6, LF->GetMyNumberFormat(abs(nTotal)));
		}
		
		m_wndReport.SetItemText(i, 7, strBankAccount);
		m_wndReport.SetItemText(i, 8, strBankName);
		m_wndReport.SetItemText(i, 9, strBankAccountOwner);
		m_wndReport.SetItemText(i, 10, "송금완료");
		m_wndReport.SetItemText(i, 11, "입금완료");
		m_wndReport.SetItemText(i, 12, "SMS");
		m_wndReport.SetItemText(i, 13, "PDA");
		m_wndReport.SetItemText(i, 14, strEtc);
		m_wndReport.SetItemText(i, 15, strMemo);
		m_wndReport.SetItemData(i, (DWORD)st);

		pRs.MoveNext();
	}

	RecordHide();
	//m_wndReport.Populate();

}

void CIncomeForm8::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_DateBtn.InitDateButton(&m_FromDT, &m_ToDT);
	m_DateBtn.OnMenuMonth();

	m_wndReport.InsertColumn(0, "사번", LVCFMT_RIGHT, 40);
	m_wndReport.InsertColumn(1, "기사명", LVCFMT_RIGHT, 60);
	m_wndReport.InsertColumn(2, "정산기간", LVCFMT_CENTER, 150);
	m_wndReport.InsertColumn(3, "입금날짜", LVCFMT_CENTER, 70);
	m_wndReport.InsertColumn(4, "상태", LVCFMT_CENTER, 70);
	m_wndReport.InsertColumn(5, "미지입금", LVCFMT_CENTER, 70);
	m_wndReport.InsertColumn(6, "환불금", LVCFMT_CENTER, 70);
	m_wndReport.InsertColumn(7, "계좌번호", LVCFMT_CENTER, 110);
	m_wndReport.InsertColumn(8, "거래은행", LVCFMT_CENTER, 70);
	m_wndReport.InsertColumn(9, "예금주", LVCFMT_CENTER, 70);
	m_wndReport.InsertColumn(10, "완료", LVCFMT_CENTER, 65);
	m_wndReport.InsertColumn(11, "완료", LVCFMT_CENTER, 65);
	m_wndReport.InsertColumn(12, "전송", LVCFMT_CENTER, 50);
	m_wndReport.InsertColumn(13, "전송", LVCFMT_CENTER, 50);
	m_wndReport.InsertColumn(14, "적요", LVCFMT_CENTER, 250);
	m_wndReport.InsertColumn(15, "메모", LVCFMT_CENTER, 250);

	m_chkNotReport.SetCheck(TRUE);
	m_chkReport.SetCheck(TRUE);
	m_chkIncomeComplete.SetCheck(TRUE);
	m_chkOutputComplete.SetCheck(TRUE);

	m_wndReport.Populate();

	SetResize(IDC_REPORT_LIST, sizingRightBottom);
}

void CIncomeForm8::RecordHide()
{ 
	CString sSearchRNo; m_RNoEdit.GetWindowText(sSearchRNo);
	char buffer[20];
	long nGiveTotal = 0;
	long nTakeTotal = 0;
	
	CXTPGridRecords *pRecords = m_wndReport.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{ 
		CXTPGridRecord* pRecord = pRecords->GetAt(i); 
		ST_DEPOSIT *pDeposit = (ST_DEPOSIT*)m_wndReport.GetItemData(pRecord);

		CString sRNo = itoa(pDeposit->nRNo, buffer, 10);
		long nTotal = pDeposit->nTotal;
		long nState = pDeposit->nState;

		BOOL bVisible = FALSE;
		
 		if((sRNo == sSearchRNo) || (sSearchRNo == ""))
		{
			if((m_chkNotReport.GetCheck()) && (nState == 0))
				bVisible = TRUE;
			else if((m_chkReport.GetCheck()) && (nState == 1))
				bVisible = TRUE;
			else if((m_chkIncomeComplete.GetCheck()) &&
				(nState == 2) &&
				nTotal >= 0)
				bVisible = TRUE;
			else if((m_chkOutputComplete.GetCheck()) &&
				(nState == 2) &&
				nTotal < 0)
				bVisible = TRUE;
			else
				bVisible = FALSE;
		}
		else
			bVisible = FALSE;

		if((bVisible == TRUE) &&(nState != 2))
		{
			if(nTotal > 0)
				nGiveTotal += nTotal;
			else
				nTakeTotal += nTotal;
		}

		pRecord->SetVisible(bVisible);
	}

	m_stcGive.SetWindowText("미지입금 : " + LF->GetMyNumberFormat(nGiveTotal));
	m_stcTake.SetWindowText("환불금 : " + LF->GetMyNumberFormat(abs(nTakeTotal)));

	m_wndReport.Populate();
}

void CIncomeForm8::OnEnChangeRnoEdit()
{
	RecordHide();
}

void CIncomeForm8::OnBnClickedNotReportCheck()
{
	RecordHide();
}

void CIncomeForm8::OnBnClickedReportCheck()
{
	RecordHide();
}

void CIncomeForm8::OnBnClickedIncomeCompleteCheck()
{
	RecordHide();
}

void CIncomeForm8::OnBnClickedOutputCompleteCheck()
{
	RecordHide();
}

void CIncomeForm8::OnDblClickList(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	int nItem = m_wndReport.GetNextItem(-1, LVNI_SELECTED);

	if(nItem >= 0) 
	{ 
		ST_DEPOSIT *pDeposit = (ST_DEPOSIT*)m_wndReport.GetItemData(pItemNotify->pRow->GetRecord());

		CRiderReportDlg dlg;
		dlg.m_nID = pDeposit->nID;
		dlg.m_strRName = pDeposit->strRName;

		if(pDeposit->nState == 2 || pDeposit->nState == 1)
			dlg.m_bComplete = TRUE;

		dlg.m_dtFrom = pDeposit->dtCreditOrderStart;
		dlg.m_dtTo = pDeposit->dtCreditOrderEnd;
 
		dlg.m_bAbleMove = TRUE;
		dlg.m_nRiderCompany = pDeposit->nCompany;
		dlg.m_nRNo = pDeposit->nRNo;
		dlg.m_nFixedDepositCharge = pDeposit->nFixedDeposit;

		if(dlg.DoModal() == IDOK)
			RefreshList();	
	}
}

void CIncomeForm8::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	//m_wndReport.ScreenToClient(&point);
	m_wndReport.GetWindowRect(&rect);

	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(7);
	pRMenu->EnableMenuItem(ID_HALF_INSERT_FIXED_DEPOSIT,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	

}


void CIncomeForm8::OnClickList(NMHDR * pNotifyStruct, LRESULT * result)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	long nRow = pItemNotify->pRow->GetRecord()->GetIndex();
	long nCol = pItemNotify->pColumn->GetItemIndex();

	CXTPGridRecord * pRecord = pItemNotify->pRow->GetRecord();

	ST_DEPOSIT *pDeposit = (ST_DEPOSIT*)m_wndReport.GetItemData(pRecord);

	if(nCol >= 7 && nCol <= 9)
		m_wndReport.SetSelectCol(nRow, nCol);

	if((nCol == 10) || (nCol == 11)) // 송금완료
	{
		if(pDeposit->nState == 0)
		{
			MessageBox("정산창을 이용하여 정산처리 후 시도하세요", "확인", MB_ICONINFORMATION);
			return;
		}
		else if(pDeposit->nState == 1)
		{
			if((pDeposit->nTotal > 0) && (nCol == 10))
			{
				MessageBox("입금완료 버튼을 이용하세요", "확인", MB_ICONINFORMATION);
				return;
			}

			if((pDeposit->nTotal < 0) && (nCol == 11))
			{
				MessageBox("송금완료 버튼을 이용하세요", "확인", MB_ICONINFORMATION);
				return;
			}

			CString str = nCol == 10 ? "송금완료" : "입금완료";

			if(MessageBox(str + " 상태로 변경하시겠습니까?", "확인", MB_ICONINFORMATION | MB_OKCANCEL) != IDOK)
				return;

			if(CompleteIncome(pDeposit->nID))
			{ 				
				pDeposit->nState = 2;
				((CXTPGridRecordItemText*)(pRecord->GetItem(4)))->SetValue(str);
				((CXTPGridRecordItemText*)(pRecord->GetItem(4)))->SetCaption(str);

				m_wndReport.Populate();
				MessageBox("변경되었습니다", "확인", MB_ICONINFORMATION);
			}
		}    
		else if(pDeposit->nState == 2)
		{
			CString str = nCol == 10 ? "송금완료" : "입금완료";

			MessageBox("이미 " + str + "처리 되었습니다", "확인", MB_ICONINFORMATION);
			return;			
		}
	}
	else if((nCol == 12) || (nCol == 13))//SMS전송
	{
		CRiderDepositMsgDlg dlg;
		dlg.m_sMsg = GetSMSMsg(pDeposit); //12 SMS

		if(dlg.DoModal() == IDOK)
		{
			if(nCol == 12)
			{
				LF->SendSmsNew(m_ci.m_nCompanyCode, 777, pDeposit->strHp, m_ci.m_strOfficePhone, dlg.m_sMsg, "기사공지", "", "", TRUE);
			}
			else if(nCol == 13)
			{
				if(LF->SendPDASimple(m_ci.m_nCompanyCode, pDeposit->nCompany, pDeposit->nRNo, dlg.m_sMsg))
				{
					MessageBox("PDA 공지로 전송하였습니다", "확인", MB_ICONINFORMATION);
					return;
				}
			}
		}
	}

    m_wndReport.Populate();
}

CString CIncomeForm8::GetSMSMsg(ST_DEPOSIT *pDeposit)
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_deposit_info_by_incomday_2");

	pCmd.AddParameter(pDeposit->nID);
	pCmd.AddParameter(pDeposit->nCompany);
	pCmd.AddParameter(pDeposit->nRNo);

	if(!pRs.Execute(&pCmd)) return "";

	BOOL bWeeklyDeposit, bSameRiderIncomeDay;
	CString sTakeDate;
	long nRiderIncomeDay;
	long nTakeTotal, nGiveTotal, nTotal;

	pRs.GetFieldValue("bWeeklyDeposit", bWeeklyDeposit);
	pRs.GetFieldValue("bSameRiderIncomeDay", bSameRiderIncomeDay);
	pRs.GetFieldValue("sTakeDate", sTakeDate);
	pRs.GetFieldValue("nRiderIncomeDay", nRiderIncomeDay);
	pRs.GetFieldValue("nTakeTotal", nTakeTotal);
	pRs.GetFieldValue("nGiveTotal", nGiveTotal);
	pRs.GetFieldValue("nTotal", nTotal);

	COleDateTime dtMainDate(atoi(sTakeDate.Left(4)), atoi(sTakeDate.Mid(4,2)), atoi(sTakeDate.Right(2)), 0, 0, 0);

	COleDateTime dtIncomeDate = LF->GetCompareDate(bWeeklyDeposit, dtMainDate, nRiderIncomeDay, bSameRiderIncomeDay);
	CString sMsg = "";

	sMsg.Format("%d월%d일", dtIncomeDate.GetMonth(), dtIncomeDate.GetDay());
	sMsg += "은 지입금 입금일입니다.";


	CString sTotal; sTotal.Format("%d", nTotal);
	CString sTakeTotal; sTakeTotal.Format("%d", nTakeTotal);
	CString sGiveTotal; sGiveTotal.Format("%d", nGiveTotal);

	sMsg += sGiveTotal + "-" +  sTakeTotal;

	if(atoi(sTotal) > 0)
		sMsg += " 최종 " + sTotal + "입금하시길 바랍니다.";
	else if(atoi(sTotal) < 0)
	{
		sTotal.Replace("-", "");
		sMsg += " 최종 " + sTotal + "입금예정입니다.";
	}
	else
		sMsg += " 최종금액 0원입니다.";

	return sMsg;
}

BOOL CIncomeForm8::CompleteIncome(long nID)
{
	CMkCommand pCmd(m_pMkDb, "update_fixed_deposit_state");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nID);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), 2);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);

	if(pCmd.Execute())
	{
		return TRUE;
	}

	return FALSE;
}

void CIncomeForm8::OnMakeFixedDeposit()
{
	CXTPGridRow *pRow = m_wndReport.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	ST_DEPOSIT *pDeposit = (ST_DEPOSIT*)m_wndReport.GetItemData(pRow->GetRecord());
	
	CMakeFixedDepositDlg dlg;
	dlg.m_nRiderCompany = pDeposit->nCompany;
	dlg.m_nRNo = pDeposit->nRNo;
	dlg.m_strRName = pDeposit->strRName;

	if(dlg.DoModal() == IDOK)
		RefreshList();

}


void CIncomeForm8::OnHalfInsertFixedDeposit()
{
	/*
	long index = m_wndReport.GetNextItem(-1, LVNI_SELECTED);

	if(index == -1)
	{
		MessageBox("부분 입금 할 지입금 로그를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	} 

	CHalfInsertFixedDepositDlg dlg;

	if(dlg.DoModal() == IDOK)
	{
		long nID = (long)m_wndReport.GetItemData(index);

		CString sDepositCharge; sDepositCharge = m_wndReport.GetItemText(index, 11);
		sDepositCharge.Replace(",", "");

		if(dlg.m_nCharge > _ttoi(sDepositCharge))
		{
			if(MessageBox("부분 수정 할 금액이 지입금보다 큽니다\r\n   진행하시겠습니까", "확인", MB_OKCANCEL) != IDOK)
				return;
		}

		CMkCommand pCmd(m_pMkDb, "update_fixed_deposit");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), dlg.m_nCharge);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.strName);

		if(pCmd.Execute())
			RefreshList();

	}
	*/
}
void CIncomeForm8::OnDeleteFixedDeposit()
{
	CXTPGridRow *pRow = m_wndReport.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	ST_DEPOSIT *pDeposit = (ST_DEPOSIT*)m_wndReport.GetItemData(pRow->GetRecord());

	CString sDate = ((CXTPGridRecordItemText*)(pRow->GetRecord()->GetItem(3)))->GetCaption(NULL);

	CString str;
	str.Format("정산기산 : %s, 금액 : %d원을 삭제 하시겠습니까?", sDate, pDeposit->nFixedDeposit);

	if(MessageBox(str, "확인", MB_OKCANCEL) == IDOK)
	{
		long nID = pDeposit->nID;

		CMkCommand pCmd(m_pMkDb, "delete_fixed_deposit");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.strName);

		if(pCmd.Execute())
			RefreshList();
	}
}

void CIncomeForm8::OnNotReport()
{
	CXTPGridRow *pRow = m_wndReport.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	ST_DEPOSIT *pDeposit = (ST_DEPOSIT*)m_wndReport.GetItemData(pRow->GetRecord());

	if(pDeposit->nState == 0)
	{
		return;
	}
	else if((pDeposit->nState == 1) || (pDeposit->nState == 2))
	{
		long nID = pDeposit->nID;
		CMkCommand pCmd(m_pMkDb, "update_fixed_deposit_state");

		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), 0);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);

		if(pCmd.Execute())
			RefreshList();	
	}
}
void CIncomeForm8::OnReportComplete()
{
	CXTPGridRow *pRow = m_wndReport.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	ST_DEPOSIT *pDeposit = (ST_DEPOSIT*)m_wndReport.GetItemData(pRow->GetRecord());

	if(pDeposit->nState == 0)
	{
		MessageBox("정산창을 이용하세요!", "확인", MB_ICONINFORMATION);
		return; 
	}
	else if(pDeposit->nState == 2)
	{
		long nID = pDeposit->nFixedDeposit;
		CMkCommand pCmd(m_pMkDb, "update_fixed_deposit_state");

		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), 1);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);

		if(pCmd.Execute())
			RefreshList();	
	}
}
void CIncomeForm8::OnIncomeComplete()
{
	CXTPGridRow *pRow = m_wndReport.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	ST_DEPOSIT *pDeposit = (ST_DEPOSIT*)m_wndReport.GetItemData(pRow->GetRecord());

	if(pDeposit->nState)
	{
		MessageBox("정산먼저 완료하세요", "확인", MB_ICONINFORMATION);
	}
	else if(pDeposit->nState == 1)
	{
		long nID = pDeposit->nID;
		CMkCommand pCmd(m_pMkDb, "update_fixed_deposit_state");

		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), 2);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);

		if(pCmd.Execute())
			RefreshList();
	}
	else if(pDeposit->nState == 2)
	{
		return;
	}
}

void CIncomeForm8::OnViewExcel()
{
	if(!LF->POWER_CHECK(7900, "엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(m_ci.m_nCompanyCode, 505, m_wndReport.GetItemCount());  
	CMyExcel::ToExcel(&m_wndReport);
}

BOOL CIncomeForm8::PreTranslateMessage(MSG* pMsg)
{
	if(GetKeyState(VK_CONTROL) & 0x8000)
	{
		if(pMsg->wParam == 'c' || pMsg->wParam == 'C')
		{
			CPoint pt;
			::GetCursorPos(&pt);

			CRect rcList; m_wndReport.GetWindowRect(&rcList);

			if(!rcList.PtInRect(pt))
				return TRUE;

			if(m_wndReport.GetSelCol() >= 7 && m_wndReport.GetSelCol() <= 9) //은행정보
			{
				CXTPGridRecords *pRecords = m_wndReport.GetRecords();
				CXTPGridRecord* pRecord = pRecords->GetAt(m_wndReport.GetSelRow());

				CString sText = ((CXTPGridRecordItemText*)pRecord->GetItem(m_wndReport.GetSelCol()))->GetCaption(NULL);

				if(::OpenClipboard(m_hWnd))
				{
					::EmptyClipboard();

					HANDLE hData = ::GlobalAlloc(GMEM_MOVEABLE, sText.GetLength()+1);
					LPSTR pData = (LPSTR)::GlobalLock(hData);
					::strcpy(pData, sText);
					::GlobalUnlock(hData);

					::SetClipboardData(CF_TEXT, hData);
					::CloseClipboard();
				}
			}
		}
	}

	return CMyFormView::PreTranslateMessage(pMsg);
}
