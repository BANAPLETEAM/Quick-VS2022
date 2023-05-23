// TransferRiderDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "TransferRiderDlg.h"


// CTransferRiderDlg 대화 상자입니다.

#define WM_GET_ALLOCATE_RIDER WM_USER + 100

IMPLEMENT_DYNAMIC(CTransferRiderDlg, CMyDialog)

CTransferRiderDlg::CTransferRiderDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CTransferRiderDlg::IDD, pParent)
{
	m_nRiderCompany = 0;
	m_nRNo = 0;
	m_strRiderName = "";
}

CTransferRiderDlg::~CTransferRiderDlg()
{
}

void CTransferRiderDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RNO_EDIT, m_edtRNo);
	DDX_Control(pDX, IDC_RNAME_EDIT, m_edtRName);
	DDX_Control(pDX, IDC_COMPANY_EDIT, m_edtCompany);
	DDX_Control(pDX, IDC_ETC_EDIT, m_edtEtc);
	DDX_Control(pDX, IDC_REPORT_LIST, m_lstReport);
	DDX_Control(pDX, IDC_CHARGE_EDIT, m_edtCharge);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_btnRefresh);
	DDX_Control(pDX, IDC_CLOSE_BTN, m_btnClose);
}


BEGIN_MESSAGE_MAP(CTransferRiderDlg, CMyDialog)
	ON_BN_CLICKED(IDC_TRANS_BUTTON, &CTransferRiderDlg::OnBnClickedTransButton)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CTransferRiderDlg::OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_SEARCH_RIDER_BTN, &CTransferRiderDlg::OnBnClickedSearchRiderBtn)
	ON_MESSAGE(WM_GET_ALLOCATE_RIDER, OnGetAllocateRider)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CTransferRiderDlg::OnBnClickedCloseBtn)
END_MESSAGE_MAP()


// CTransferRiderDlg 메시지 처리기입니다.

void CTransferRiderDlg::OnBnClickedTransButton()
{
	if(m_nRiderCompany <= ZERO ||
		m_nRNo <= ZERO)
	{
		MessageBox("기사님을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CString strCharge; m_edtCharge.GetWindowText(strCharge);
	strCharge.Replace(",", "");

	if(_ttoi(strCharge) <= ZERO) 
	{
		MessageBox("요청하실 금액을 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CString strTemp;
	strTemp.Format("%d번 %s기사님에게 %s원을 이체요청 하시겠습니까?", m_nRNo, m_strRiderName, LF->GetMyNumberFormat(_ttoi(strCharge)));

	if(MessageBox(strTemp, "확인", MB_OKCANCEL) != IDOK)
		return;

	CString strEtc; m_edtEtc.GetWindowText(strEtc);

	CMkCommand pCmd(m_pMkDb, "update_share_report_want_transfer_for_rider");
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(m_ui.strName);
	pCmd.AddParameter(_ttoi(strCharge));
	pCmd.AddParameter(strEtc);
	pCmd.AddParameter(m_nRiderCompany);
	pCmd.AddParameter(m_nRiderCompany);
	pCmd.AddParameter(m_nRNo);
	pCmd.AddParameter(m_strRiderName);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.strName);

	if(!pCmd.Execute())
		return;

	MessageBox("청구 요청 하였습니다", "확인", MB_ICONINFORMATION);
	RefreshList();	
}

BOOL CTransferRiderDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	LF->MakeModaless();
	CenterWindow();

	m_lstReport.InsertColumn(0, "요청날짜", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(1, "요청업체", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(2, "사유", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(3, "진행상태", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(4, "요청금액", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(5, "입금날짜", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(6, "받은금액", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(7, "받은메모", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(8, "이체적요", LVCFMT_LEFT, 150);
	m_lstReport.Populate();


	RefreshList();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CTransferRiderDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CTransferRiderDlg::RefreshList()
{
	m_lstReport.DeleteAllItems();

    CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_transfer_my_request_for_rider");

    pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);

	if(!pRs.Execute(&pCmd)) return;

	CString sMemo, sReceiveMessage, strFormat, strTransferEtc, strToCompany;
	long nID, nToCompany, nRequestCharge, nReceiveCharge, nState;
    COleDateTime dtRequest, dtReceive;

	for(int i = 0 ; i < pRs.GetRecordCount(); i++)
	{ 
        pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("nToCompany", nToCompany);
		pRs.GetFieldValue("sMemo", sMemo);
		pRs.GetFieldValue("dtRequest", dtRequest);
		pRs.GetFieldValue("nRequestCharge", nRequestCharge);
		pRs.GetFieldValue("dtReceive", dtReceive);
		pRs.GetFieldValue("nReceiveCharge", nReceiveCharge);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("sReceiveMessage", sReceiveMessage);
		pRs.GetFieldValue("sTransferEtc", strTransferEtc);
		pRs.GetFieldValue("sToCompany", strToCompany);


		m_lstReport.InsertItem(i, dtRequest.Format("%m-%d %H:%M"));
		m_lstReport.SetItemText(i, 1, strToCompany);
		m_lstReport.SetItemText(i, 2, sMemo);
		m_lstReport.SetItemText(i, 3, ReturnType(nState));
		m_lstReport.SetItemText(i, 4, LF->GetMyNumberFormat(nRequestCharge));

		if(nState == 2 || nState == 4) //정상종료 
		{
			m_lstReport.SetItemText(i, 5, dtReceive.Format("%m-%d %H:%M"));
			m_lstReport.SetItemText(i, 6, LF->GetMyNumberFormat(nReceiveCharge));
		}
		else
		{
			m_lstReport.SetItemText(i, 5, "");
			m_lstReport.SetItemText(i, 6, "");
		}

		m_lstReport.SetItemText(i, 7, sReceiveMessage);
		m_lstReport.SetItemText(i, 8, strTransferEtc);

		pRs.MoveNext();
	}

	m_lstReport.Populate();
}

void CTransferRiderDlg::OnBnClickedSearchRiderBtn()
{
	LU->OpenOtherAllocateDlg(0, 0, 0, 0, FALSE, this);
}

LONG CTransferRiderDlg::OnGetAllocateRider(WPARAM wParam, LPARAM lParam)
{	
	ST_RIDER_WORK_STATE_INFO *pInfo = (ST_RIDER_WORK_STATE_INFO*)wParam;

	m_nRiderCompany = pInfo->nCompany;
	m_nRNo = pInfo->nRNo;
	m_strRiderName = pInfo->strName;
	m_strCompanyName = pInfo->strCompanyName;

	delete pInfo;
	pInfo = NULL;

	char buffer[10];

	m_edtRNo.SetWindowText(CString(itoa(m_nRNo, buffer, 10)));
	m_edtCompany.SetWindowText(m_strCompanyName);
	m_edtRName.SetWindowText(m_strRiderName);	

	return 0;
}

CString CTransferRiderDlg::ReturnType(int nType)
{
	if(nType == 1)
		return "입금대기중";
	else if(nType == 2)
		return "입금완료";
	else if(nType == 4) //사용자거절
		return "거절";
	else
		return "일주일경과"; //3이 일주일이 경과하여 자동 취소 됨
}
void CTransferRiderDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(!m_lstReport.GetSafeHwnd())
		return;

	/*
	CRect rcDlg, rcList, rcRefreshBtn, rcCloseBtn;
	GetClientRect(rcDlg);

	m_btnRefresh.GetWindowRect(rcRefreshBtn);
	m_btnClose.GetWindowRect(rcCloseBtn);
	ScreenToClient(rcRefreshBtn);
	ScreenToClient(rcCloseBtn);



	m_lstReport.GetWindowRect(rcList);
	ScreenToClient(rcList);

	rcList.right = rcDlg.right - 1;
	rcList.bottom = rcDlg.bottom - 1; 

	m_lstReport.MoveWindow(rcList);
	*/
}

BOOL CTransferRiderDlg::PreTranslateMessage(MSG* pMsg)
{
	

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CTransferRiderDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}
