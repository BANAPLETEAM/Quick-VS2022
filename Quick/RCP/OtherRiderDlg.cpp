// OtherRiderDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "OtherRiderDlg.h"
#include "RcpView.h"
#include "RcpDlg.h"
#include "RcpMultiStateChange.h"
#include "CustomMyAfxMessgagebox.h"
// COtherRiderDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(COtherRiderDlg, CMyDialog)
COtherRiderDlg::COtherRiderDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(COtherRiderDlg::IDD, pParent)
{
}

COtherRiderDlg::~COtherRiderDlg()
{
}

void COtherRiderDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MNO_EDIT, m_edtMNo);
	DDX_Control(pDX, IDC_FIND_BTN, m_btnFind);
	DDX_Control(pDX, IDC_ALLOCATE_BTN, m_btnAllocate);
	DDX_Control(pDX, IDC_COLSE_BTN, m_btnClose);
	DDX_Control(pDX, IDC_REPORT_LIST, m_lstReport);
}


BEGIN_MESSAGE_MAP(COtherRiderDlg, CMyDialog)
	ON_BN_CLICKED(IDC_FIND_BTN, OnBnClickedFindBtn)
	ON_BN_CLICKED(IDC_ALLOCATE_BTN, OnBnClickedAllocateBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT_LIST, OnReportItemDblClick)
	ON_BN_CLICKED(IDC_COLSE_BTN, OnBnClickedColseBtn)
END_MESSAGE_MAP()


// COtherRiderDlg 메시지 처리기입니다.

void COtherRiderDlg::OnBnClickedFindBtn()
{	
	m_lstReport.DeleteAllItems();

	CString sRNo; m_edtMNo.GetWindowText(sRNo);

	if(sRNo == "0" || sRNo == "")
	{
		MessageBox("다시 입력해 주세요" , "확인", MB_ICONINFORMATION);
		return;
	}

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_other_allocate_rider_5");
	CMkParameter *pDeposit = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nShareCode1);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nShareCode2);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nShareCode3);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nShareCode4);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nShareCode5);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nTNo);
	pCmd.AddParameter(sRNo);

	if(!pRs.Execute(&pCmd)) return;

	if(pRs.GetRecordCount() == 0) return;

	long nCompany, nRNo, nRiderBalance, nDepositType, nWorkState;
	long nShareCode2, nShareCode3, nShareCode4, nShareCode5;
	CString sName, strCompanyName;
	char buffer[20]; 

	long nOrderDeposit = 0; pDeposit->GetValue(nOrderDeposit);

	/*
	if(nOrderDeposit > 20000)
	{
		MessageBox("입금액 2만원 이상은 배차할수 없습니다", "확인", MB_ICONINFORMATION);
		OnCancel();
	}
	*/

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sName", sName);
		pRs.GetFieldValue("nRiderBalance", nRiderBalance);
		pRs.GetFieldValue("nDepositType", nDepositType);
		pRs.GetFieldValue("nWorkState", nWorkState);
		pRs.GetFieldValue("sCompanyName", strCompanyName);

		pRs.GetFieldValue("nShareCode2", nShareCode2);
		pRs.GetFieldValue("nShareCode3", nShareCode3);
		pRs.GetFieldValue("nShareCode4", nShareCode4);
		pRs.GetFieldValue("nShareCode5", nShareCode5);

		m_lstReport.InsertItem(i, m_ci.GetName(nCompany));
		m_lstReport.SetItemText(i, 1, itoa(nRNo, buffer, 10));
		m_lstReport.SetItemText(i, 2, sName);

		CString strFormat = "";
		if(m_ci.m_nShareCode2 == nShareCode2 && nShareCode2 != 0)
			strFormat += "②";
		if(m_ci.m_nShareCode3 == nShareCode3 && nShareCode3 != 0)
			strFormat += "③";
		if(m_ci.m_nShareCode4 == nShareCode4 && nShareCode4 != 0)
			strFormat += "④";
		if(m_ci.m_nShareCode5 == nShareCode5 && nShareCode5 != 0)
			strFormat += "⑤";			

		m_lstReport.SetItemText(i, 3, strFormat);
		m_lstReport.SetItemText(i, 4, strCompanyName);
		//m_lstReport.SetItemText(i, 4, GetEtc(nOrderDeposit, nRiderBalance, nDepositType, m_nCompany, nCompany, nWorkState));
		m_lstReport.SetItemLong(i, nCompany);

		pRs.MoveNext();
	}

	m_lstReport.Populate();

	CXTPGridRows *pRows = m_lstReport.GetRows();
	CXTPGridRow *pRow = pRows->GetAt(0);
	
	m_lstReport.GetSelectedRows()->Select(pRow);

}

CString COtherRiderDlg::GetEtc(long nOrderDeposit, long nRiderBalance, long nDepositType, long nOCompany, long nRCompany, long nWorkState)
{
    if((nOrderDeposit > nRiderBalance) && nOrderDeposit == 10)
		return "잔액부족";
 
	if(nWorkState != 0)
		return "업무중지";

	BOOL bAlince = FALSE;

	for(int i = 1; i <= 5; i++)
	{
		if((m_ci.GetShareCode(nOCompany, i) == m_ci.GetShareCode(nRCompany, i)) &&
			m_ci.GetShareCode(nOCompany, i) != 0 && m_ci.GetShareCode(nRCompany, i) != 0)
		{
			bAlince = TRUE;
			break;
		}
	}

	if(!bAlince)
		return "공유안함";

	return "";
}


BOOL COtherRiderDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow();

	m_lstReport.InsertColumn(0, "기사회사명", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(1, "사번", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(2, "이름", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(3, "차수", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(4, "회사명", LVCFMT_LEFT, 0);

	m_lstReport.Populate();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void COtherRiderDlg::OnBnClickedAllocateBtn()
{ 
	long index = m_lstReport.GetNextItem(-1, LVNI_SELECTED);

	if(index == -1) return;


	m_nRiderCompany = m_lstReport.GetItemLong(index);
	m_nRNo = _ttoi(m_lstReport.GetItemText(index, 1));
	CString sRName = m_lstReport.GetItemText(index, 2);
	CString strCompanyName = m_lstReport.GetItemText(index, 4);

	if(m_bToRcpView == TRUE) 
	{
		if(!m_ci.IsChildCompany(m_nRiderCompany))
		{
			if(m_nState == STATE_RESERVED)
			{
				CCustomMyAfxMessgagebox dlg;
				long nRet = dlg.DoModal();

				if(dlg.m_nType == 0)
				{
					if(LU->IsOtherShareBalanceOk(m_nDeposit, m_nRiderCompany) == FALSE)
					{
						MessageBox("기사님 소속사의 공동금액잔액이 부족하여 개별배차를 내리실 수 없습니다.", "확인", MB_ICONINFORMATION);
						return;
					}
					m_pRcpView->GetStateChange()->Allocate(m_nTNo, m_nRNo, m_nState, m_nRiderCompany);
				}
				else if(dlg.m_nType == 1)
				{
					if(LU->UpdateRiderInfoForReserveOrder(m_nTNo, m_nRiderCompany, m_nRNo) == FALSE)
					{
						MessageBox("기사님 소속사의 공동금액잔액이 부족하여 개별배차를 내리실 수 없습니다.", "확인", MB_ICONINFORMATION);
						return;
					}
					m_pRcpView->AllRefresh();
				}
			}
			else
			{
				if(LU->IsOtherShareBalanceOk(m_nDeposit, m_nRiderCompany) == FALSE)
				{
					MessageBox("기사님 소속사의 공동금액잔액이 부족하여 개별배차를 내리실 수 없습니다.", "확인", MB_ICONINFORMATION);
					return;
				}

				m_pRcpView->GetStateChange()->Allocate(m_nTNo, m_nRNo, m_nState, m_nRiderCompany);
			}
		}
	}
	else if(m_pParent != NULL)
	{
		ST_RIDER_WORK_STATE_INFO *pInfo = new ST_RIDER_WORK_STATE_INFO;
		pInfo->nCompany = m_nRiderCompany;
		pInfo->nRNo = m_nRNo;
		pInfo->strName = sRName;
		pInfo->strCompanyName = strCompanyName;
		pInfo->strPhone = LF->GetRiderPhone(pInfo->nCompany, pInfo->nRNo);
		m_pParent->SendMessage(WM_GET_ALLOCATE_RIDER, (WPARAM)pInfo, (LPARAM)FALSE);
	}

	OnOK();
}

void COtherRiderDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	OnBnClickedAllocateBtn();
}

BOOL COtherRiderDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN) 
		{
			if(pMsg->hwnd == m_edtMNo.GetSafeHwnd())
				OnBnClickedFindBtn();

			return TRUE;
		}

	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void COtherRiderDlg::OnBnClickedColseBtn()
{
	OnCancel();
}
