// OtherRiderTransferDlg1.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "quick.h"
#include "OtherRiderTransferDlg.h"
#include "OtherRiderFindDlg.h"
#include "OtherRiderTransferLogDlg.h"


// COtherRiderTransferDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(COtherRiderTransferDlg, CMyDialog)
COtherRiderTransferDlg::COtherRiderTransferDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(COtherRiderTransferDlg::IDD, pParent)
{
	m_nAbility = 0;
	m_nRiderCompany = 0;
	m_nRNo = 0;

	m_strCompanyName = "";
	m_strBranchName = "";
	m_strRNo = "";
	m_strName = "";
	m_strID = "";
	m_strHp = "";
	m_strSSN = "";

	m_strAbleCharge = "";

	m_strCharge = "";
	m_strEtc = "";

	m_bTransReady = FALSE;

	m_nTransReadyCompany = 0;
}

COtherRiderTransferDlg::~COtherRiderTransferDlg()
{
}

void COtherRiderTransferDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMPANY_NAME_EDT, m_edtCompanyName);
	DDX_Control(pDX, IDC_BRANCH_NAME_EDT, m_edtBranchName);
	DDX_Control(pDX, IDC_RNO_EDT, m_edtRNo);
	DDX_Control(pDX, IDC_NAME_EDT, m_edtName);
	DDX_Control(pDX, IDC_ID_EDT, m_edtID);
	DDX_Control(pDX, IDC_HP_EDT, m_edtHp);
	DDX_Control(pDX, IDC_ABLE_CHARGE_EDT, m_edtAbleCharge);
	DDX_Control(pDX, IDC_BRANCH_COMBO, m_cmbBranch);

	DDX_Control(pDX, IDC_CHARGE_EDT, m_edtCharge);
	DDX_Control(pDX, IDC_ETC_EDT, m_edtEtc);//

	DDX_Text(pDX, IDC_COMPANY_NAME_EDT, m_strCompanyName);
	DDX_Text(pDX, IDC_BRANCH_NAME_EDT, m_strBranchName);
	DDX_Text(pDX, IDC_RNO_EDT, m_strRNo);
	DDX_Text(pDX, IDC_NAME_EDT, m_strName);
	DDX_Text(pDX, IDC_ID_EDT, m_strID);
	DDX_Text(pDX, IDC_HP_EDT, m_strHp);

	DDX_Text(pDX, IDC_ABLE_CHARGE_EDT, m_strAbleCharge);

	DDX_Text(pDX, IDC_CHARGE_EDT, m_strCharge);
	DDX_Text(pDX, IDC_ETC_EDT, m_strEtc);

	DDX_Control(pDX, IDC_STATIC1, m_stc1);
	DDX_Control(pDX, IDC_STATIC2, m_stc2);
	DDX_Control(pDX, IDC_STATIC3, m_stc3);
	DDX_Control(pDX, IDC_STATIC4, m_stc4);
	DDX_Control(pDX, IDC_STATIC5, m_stc5);
	DDX_Control(pDX, IDC_STATIC6, m_stc6);
	DDX_Control(pDX, IDC_STATIC7, m_stc7);
	DDX_Control(pDX, IDC_STATIC8, m_stc8);
	DDX_Control(pDX, IDC_STATIC9, m_stc9);	

	DDX_Control(pDX, IDC_SEARCH_RIDER, m_btnRiderSearch);

	DDX_Control(pDX, IDC_ABLE_BRANCH_EDIT, m_edtAbleBranchName);

}


BEGIN_MESSAGE_MAP(COtherRiderTransferDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SEARCH_RIDER, OnBnClickedSearchRider)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, OnBnClickedSaveButton)
	ON_BN_CLICKED(IDC_CANCEL_BUTTON, OnBnClickedCancelButton)
	ON_CBN_SELCHANGE(IDC_BRANCH_COMBO, OnCbnSelchangeBranchCombo)

	ON_BN_CLICKED(IDC_SHOW_LOG_DLG, &COtherRiderTransferDlg::OnBnClickedShowLogDlg)
END_MESSAGE_MAP()

void COtherRiderTransferDlg::OnCbnSelchangeBranchCombo()
{
	GetBranchBalance();
}

// COtherRiderTransferDlg 메시지 처리기입니다.

BOOL COtherRiderTransferDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow(GetDesktopWindow());

	m_edtCompanyName.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtCompanyName.SetUserOption(RGB(0, 0, 0), RGB(245, 245, 245), "");
	m_edtBranchName.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtBranchName.SetUserOption(RGB(0, 0, 0), RGB(245, 245, 245), "");
	m_edtRNo.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtRNo.SetUserOption(RGB(0, 0, 0), RGB(245, 245, 245), "");
	m_edtName.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtName.SetUserOption(RGB(0, 0, 0), RGB(245, 245, 245), "");
	m_edtID.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtID.SetUserOption(RGB(0, 0, 0), RGB(245, 245, 245), "");
	m_edtHp.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtHp.SetUserOption(RGB(0, 0, 0), RGB(245, 245, 245), "");
	m_edtAbleCharge.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtAbleCharge.SetUserOption(RGB(0, 0, 0), RGB(245, 245, 245), "");

	m_edtHp.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtHp.SetUserOption(RGB(0, 0, 0), RGB(245, 245, 245), "");

	m_stc1.SetBkColor(RGB(230, 255, 230));
	m_stc2.SetBkColor(RGB(230, 255, 230));
	m_stc3.SetBkColor(RGB(230, 255, 230));
	m_stc4.SetBkColor(RGB(230, 255, 230));
	m_stc5.SetBkColor(RGB(230, 255, 230));
	m_stc6.SetBkColor(RGB(230, 255, 230));
	m_stc7.SetBkColor(RGB(230, 230, 255));
	m_stc8.SetBkColor(RGB(230, 230, 255));
	m_stc9.SetBkColor(RGB(230, 230, 255));

	for(int i = 0; i < m_ba.GetCount(); i++)
	{
		CBranchInfo *pBi = m_ba.GetAt(i);

		if(pBi->bRcpIntMode1)// || pBi->bUseBranchShareReport)
		{
			if(pBi->strBranchName != "통합")
			{
				int nIndex = m_cmbBranch.AddString(pBi->strBranchName + "(" + pBi->strPhone + ")");
				m_cmbBranch.SetItemData(nIndex, pBi->nCompanyCode);
			}
		}
	}

	m_cmbBranch.SetCurSel(0);
	GetBranchBalance();

	if(m_nRiderCompany > 0 && m_nRNo > 0)
		RefreshRiderInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void COtherRiderTransferDlg::RefreshRiderInfo()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_rider_info_for_send");
	cmd.AddParameter(m_nRiderCompany);
	cmd.AddParameter(m_nRNo);

	if(!rs.Execute(&cmd))
		return;


	CString strCompanyName, strBranchName, strRName, strID, strHp;

	rs.GetFieldValue("sCompanyName", strCompanyName);
	rs.GetFieldValue("sBranchName", strBranchName);
	rs.GetFieldValue("sRName", strRName);
	rs.GetFieldValue("sID", strID);
	rs.GetFieldValue("sHp", strHp);

	m_edtCompanyName.SetWindowText(strCompanyName);
	m_edtBranchName.SetWindowText(strBranchName);
	m_edtRNo.SetWindowText(LF->GetMyNumberFormat(m_nRNo));
	m_edtName.SetWindowText(strRName);
	m_edtID.SetWindowText(strID);
	m_edtHp.SetWindowText(strHp);

	//m_edt
}

void COtherRiderTransferDlg::OnBnClickedSearchRider()
{
	COtherRiderFindDlg dlg;

	if(dlg.DoModal() == IDOK)
	{
		m_nRiderCompany = dlg.m_nCompany;
		m_nRNo =  dlg.m_nRNo;
		m_strName = dlg.m_strName;

		RefreshRiderInfo();
	}	
}

void COtherRiderTransferDlg::OnBnClickedSaveButton()
{
	if(!LF->POWER_CHECK(1531, "타기사충전"))
		return;

	if((m_nRiderCompany == 0) || (m_nRNo == 0))
	{
		MessageBox("기사님을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}
	
	CString strTransCharge ="";
	m_edtCharge.GetWindowText(strTransCharge);
	strTransCharge.Replace("-", "");

	if(atoi(strTransCharge) > m_nAbility)
	{
		MessageBox("이체 가능금액보다 많이 이체 하실 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	if(atoi(strTransCharge) > 100000)
	{
		MessageBox("10만원이상 이체 하실 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	if(atoi(strTransCharge) <= 0)
	{
		MessageBox("0원이상으로 이체 하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	SendPayLater(atoi(strTransCharge));
}

void COtherRiderTransferDlg::SendPayLater(long nTransCharge)
{	/*
	if(m_nTransReadyCompany <= 0)
	{
		fc.LF->MsgBox("잔액이 차감될 회사가 정해지지 않았습니다", "확인" , MB_ICONINFORMATION);
		return;
	}
	*/

	long nIndex = m_cmbBranch.GetCurSel();
	
	if(nIndex < 0)
		return;

	long nCompany = m_cmbBranch.GetItemData(nIndex);

	CString strMemo; m_edtEtc.GetWindowText(strMemo);

	if(strMemo.IsEmpty())
	{
		MessageBox("이체 사유를 입력하세요", "확인", MB_ICONINFORMATION);
		m_edtEtc.SetFocus();
		return;
	}

	if(MessageBox("타기사 충전을 하시겠습니까?", "확인", MB_OKCANCEL) != IDOK)
	{
		return;
	}

	CMkRecordset rs(m_pMkDb); 
	CMkCommand cmd(m_pMkDb, "send_charge_to_other_rider");

	cmd.AddParameter(m_nRiderCompany);
	cmd.AddParameter(m_nRNo);
	cmd.AddParameter(m_strName);
	cmd.AddParameter(nCompany);
	cmd.AddParameter(nTransCharge);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.strName);
	cmd.AddParameter(strMemo);

	if(!rs.Execute(&cmd))
		return;

	MessageBox("이체 되었습니다.", "이체성공", MB_ICONINFORMATION);
	OnOK();
}

void COtherRiderTransferDlg::OnBnClickedCancelButton()
{
	OnCancel();
}

void COtherRiderTransferDlg::GetBranchBalance()
{
	long nIndex = m_cmbBranch.GetCurSel();

	if(nIndex < 0)
		return;

	long nCompany = (long)m_cmbBranch.GetItemData(nIndex);
	
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_share_balance_simple");

	cmd.AddParameter(nCompany);

	if(rs.Execute(&cmd))
	{
		rs.GetFieldValue("nAbility", m_nAbility);

		m_edtAbleCharge.SetWindowText(LF->GetMyNumberFormat(m_nAbility) + "원");
	}
}

void COtherRiderTransferDlg::OnBnClickedShowLogDlg()
{
	CREATE_AND_SHOW_MODALESS(COtherRiderTransferLogDlg, this);
}
