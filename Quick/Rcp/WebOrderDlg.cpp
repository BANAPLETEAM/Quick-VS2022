// WebOrderDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "WebOrderDlg.h"
#include "RcpView.h"



// CWebOrderDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CWebOrderDlg, CMyDialog)
CWebOrderDlg::CWebOrderDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CWebOrderDlg::IDD, pParent)
{
	m_nWebID = 0;
}

CWebOrderDlg::~CWebOrderDlg()
{
}

void CWebOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_From);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_To);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_ALL_CHECK, m_chkAll);
	DDX_Control(pDX, IDC_CUSTOM1, m_List);
	DDX_Control(pDX, IDC_ETC_EDIT, m_edtEtc);
	
}


BEGIN_MESSAGE_MAP(CWebOrderDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_DATE_BTN, OnBnClickedDateBtn)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RECEIPT_BTN, OnBnClickedReceiptBtn)
	
	ON_BN_CLICKED(IDC_RE_BTN, OnBnClickedReBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_BN_CLICKED(IDC_PROCESS_BTN, OnBnClickedProcessBtn)
	ON_BN_CLICKED(IDC_END_BTN, OnBnClickedEndBtn)
	ON_BN_CLICKED(IDC_ETC_MODIFY_BTN, OnBnClickedEtcModifyBtn)
	ON_NOTIFY(NM_CLICK, IDC_CUSTOM1, OnReportItemClick)
	
END_MESSAGE_MAP()


// CWebOrderDlg 메시지 처리기입니다.

BOOL CWebOrderDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_From.SetFormat("yyyy-MM-dd HH:00");
	m_To.SetFormat("yyyy-MM-dd HH:00");

	m_DateBtn.InitDateButton((CDateTimeCtrl*)&m_From, (CDateTimeCtrl*)&m_To);
	m_DateBtn.OnMenuToday();

	m_List.InsertColumn(0, "회사명", DT_LEFT, 85);
	m_List.InsertColumn(1, "접수일시", DT_LEFT, 75);
	m_List.InsertColumn(2, "경과(분)", DT_LEFT, 45);
	m_List.InsertColumn(3, "고객명", DT_LEFT, 75);
	m_List.InsertColumn(4, "전화번호", DT_LEFT, 70);
	m_List.InsertColumn(5, "상태", DT_LEFT, 50);
	m_List.InsertColumn(6, "오더번호", DT_RIGHT, 60);
	m_List.InsertColumn(7, "작업자", DT_LEFT, 65);
	m_List.InsertColumn(8, "처리일시", DT_LEFT, 60);
	m_List.Populate();

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CWebOrderDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CWebOrderDlg::RefreshList()
{
	m_List.DeleteAllItems();
	UpdateData();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "web_select_simple_order");
	pCmd.AddParameter(typeInt, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeInt, typeInput, sizeof(long), LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkAll.GetCheck());	

	if(!pRs.Execute(&pCmd)) return;

	long nID, nCompany, nType, nTNo,nProcess = 0;
	CString sCName,sTel, sWName, sEtc,sType, sBranchName = "";
	COleDateTime dt0, dtProcess, dtFinal;

	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("dt0", dt0);
		pRs.GetFieldValue("dtFinal", dtFinal);
		pRs.GetFieldValue("sCName", sCName);
		pRs.GetFieldValue("sTel", sTel);
		pRs.GetFieldValue("sWName", sWName);
		pRs.GetFieldValue("sEtc", sEtc);
		pRs.GetFieldValue("nType", nType);
		pRs.GetFieldValue("dtProcess", dtProcess);
		pRs.GetFieldValue("nProcess", nProcess);
		pRs.GetFieldValue("sBranchName", sBranchName);		
		pRs.GetFieldValue("nTNo", nTNo);		

		switch(nType)
		{
		case 8: sType = "문의"; break;
		case 11: sType = "진행"; break;
		case 40: sType = "취소"; break;
		case 35: sType = "오더완료"; break;
		default: sType = "N/A"; break;
		}
		
		COleDateTimeSpan span = COleDateTime::GetCurrentTime() - dt0;
		m_List.InsertItem(i, sBranchName);
		m_List.SetItemText(i, 1, dt0.Format("%m-%d %H:%M"));
		m_List.SetItemText(i, 2, (long)span.GetTotalMinutes());
		m_List.SetItemText(i, 3, sCName);
		m_List.SetItemText(i, 4, LF->GetDashPhoneNumber(sTel));
		m_List.SetItemText(i, 5, sType);
		m_List.SetItemText(i, 6, nTNo);
		m_List.SetItemText(i, 7, sWName);
		m_List.SetItemText(i, 8, dtProcess.Format("%m-%d %H:%M"));
		m_List.SetItemLong(i, nID);
		m_List.SetItemLong2(i, nCompany);
		m_List.SetItemDataText(i, sEtc);
		pRs.MoveNext();
	}
	m_List.Populate();


}
void CWebOrderDlg::OnBnClickedDateBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CWebOrderDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}

void CWebOrderDlg::OnBnClickedReceiptBtn()
{
	if(m_List.GetSelectedRows()->GetCount() == 0)
	{
		MessageBox("접수할 아이템을 선택하세요","확인", MB_ICONINFORMATION);
		return;
	}

	long nOutput = 0;
	CXTPGridRecord *pRecord = m_List.GetFirstSelectedRecord();
	
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "web_select_simple_order_state");
	pCmd.AddParameter(typeInt, typeInput, sizeof(long), m_List.GetItemLong(pRecord));  //web아이디
	pCmd.AddParameter(typeInt, typeInput, sizeof(long), m_List.GetItemLong2(pRecord));  // 회사 nCompany
	pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);  //접수자
	CMkParameter *pPar = pCmd.AddParameter(typeInt, typeOutput, sizeof(long), 0);  // 상태
	
	pCmd.Execute();
	pPar->GetValue(nOutput);
	if(nOutput != 8)
	{
		MessageBox("접수할 아이템이 상태가 바뀌었습니다. ","확인", MB_ICONINFORMATION);
		return;
	}

	CBranchInfo *pBi = NULL;
	if(m_ba.GetCount() > 1)
	{
		for(int i = 0; i < m_ba.GetCount(); i++)
		{
			pBi = (CBranchInfo*)m_ba.GetAt(i);

			if(pBi->bIntegrated )
				continue;		

			if(pBi->nCompanyCode  == m_List.GetItemLong2(pRecord))
				break;		

		}
	}
	else
	{
		pBi = m_ba.GetAt(0);
	}

	long nLineGroup = 0;
	CString strLineGroup = "";
	pBi->strLineGroup.Replace(",","");
	strLineGroup = pBi->strLineGroup;
	nLineGroup = atol(strLineGroup);

	m_nWebID = m_List.GetItemLong(pRecord);

	CString strPhone = pRecord->GetItem(4)->GetCaption(NULL);
	strPhone.Replace("-","");

	LU->GetRcpView()->CreateRcpDlg(pBi,strPhone,
		-1,0, strPhone, FALSE, nLineGroup,0, m_List.GetItemLong(pRecord));
}

void CWebOrderDlg::OnBnClickedEtcModifyBtn()
{
	if(m_List.GetItemCount() <= 0)
		return;

	CString strEtc;
	m_edtEtc.GetWindowText(strEtc);
	CXTPGridRecord *pRecord = (CXTPGridRecord*)m_List.GetFirstSelectedRecord();
	long nID = m_List.GetItemLong(pRecord);

	CMkCommand pCmd(m_pMkDb, "web_update_simple_order_etc");
	pCmd.AddParameter(typeInt, typeInput, sizeof(long), nID);  //web아이디	
	pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);  //접수자
	pCmd.AddParameter(typeString, typeInput, strEtc.GetLength(), strEtc);  // 상태
	pCmd.Execute();

	m_List.SetItemDataText(pRecord, strEtc);
	MessageBox("수정되었습니다.", "확인",MB_ICONINFORMATION);
}


void CWebOrderDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * result)
{
	if(m_List.GetItemCount() <= 0)
		return;

	CXTPGridRecord *pRecord = (CXTPGridRecord*)m_List.GetFirstSelectedRecord();
	m_edtEtc.SetWindowText(m_List.GetItemDataText(pRecord));



}

void CWebOrderDlg::ChangItemState(int nType)
{
	if(m_List.GetItemCount() <= 0)
		return;

	for(int i = 0; i < m_List.GetSelectedRows()->GetCount(); i++)
	{
		CXTPGridRow *pRow = (CXTPGridRow *)m_List.GetSelectedRows()->GetAt(i);
		CXTPGridRecord *pRecord = (CXTPGridRecord*)pRow->GetRecord();

		//CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "web_update_simple_order");
		pCmd.AddParameter(typeInt, typeInput, sizeof(long), m_List.GetItemLong(pRecord));  //web아이디	
		pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);  //접수자
		pCmd.AddParameter(typeInt, typeInput, sizeof(long), nType);  // 상태
		pCmd.Execute();


		
	}

	RefreshList();


}

void CWebOrderDlg::OnBnClickedReBtn()
{
	ChangItemState(1);
}

void CWebOrderDlg::OnBnClickedProcessBtn()
{
	ChangItemState(2);
}

void CWebOrderDlg::OnBnClickedEndBtn()
{
	ChangItemState(3);
}

void CWebOrderDlg::OnBnClickedCancelBtn()
{
	ChangItemState(4);
}

