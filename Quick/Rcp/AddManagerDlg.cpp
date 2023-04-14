// AddManagerDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "AddManagerDlg.h"


// CAddManagerDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAddManagerDlg, CMyDialog)

CAddManagerDlg::CAddManagerDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAddManagerDlg::IDD, pParent)
{
	m_nCompany = ZERO;
	m_nCNo = ZERO;
}

CAddManagerDlg::~CAddManagerDlg()
{
}

void CAddManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MANAGER_EDIT, m_edtManager);
	DDX_Control(pDX, IDC_DEPART_EDIT, m_edtDepart);
	DDX_Control(pDX, IDC_TEL_EDIT, m_edtTel);
	DDX_Control(pDX, IDC_TEL_EDIT2, m_edtTel2);
	DDX_Control(pDX, IDC_TEL_EDIT4, m_edtTel3);
	DDX_Control(pDX, IDC_TEL_EDIT5, m_edtTel4);

	DDX_Text(pDX, IDC_MANAGER_EDIT, m_strManager);
	DDX_Text(pDX, IDC_DEPART_EDIT, m_strDepart);
	DDX_Text(pDX, IDC_TEL_EDIT, m_strTel);
	DDX_Text(pDX, IDC_TEL_EDIT2, m_strTel2);
	DDX_Text(pDX, IDC_TEL_EDIT4, m_strTel3);
	DDX_Text(pDX, IDC_TEL_EDIT5, m_strTel4);
	DDX_Control(pDX, IDOK, m_btnOK);
}


BEGIN_MESSAGE_MAP(CAddManagerDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &CAddManagerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAddManagerDlg::OnBnClickedCancel)
	ON_BN_CLICKED(ID_ERASE_BTN, &CAddManagerDlg::OnBnClickedEraseBtn)
END_MESSAGE_MAP()


// CAddManagerDlg 메시지 처리기입니다.

void CAddManagerDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	CMkCommand pCmd(m_pMkDb, "insert_customer_phone_with_manager_2");
	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	//pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(::GetBranchInfo(m_nCompany)->nCustomerTable);
	pCmd.AddParameter(m_nCNo);
	pCmd.AddParameter(::GetNoneDashNumberRemoveDDD(m_strDepart));
	pCmd.AddParameter(::GetNoneDashNumberRemoveDDD(m_strManager));
	pCmd.AddParameter(::GetNoneDashNumberRemoveDDD(m_strTel));
	pCmd.AddParameter(::GetNoneDashNumberRemoveDDD(m_strTel2));
	pCmd.AddParameter(::GetNoneDashNumberRemoveDDD(m_strTel3));
	pCmd.AddParameter(::GetNoneDashNumberRemoveDDD(m_strTel4));

	if(!pCmd.Execute()) return;

	/*
	pPar->GetValue(m_nTelID);

	if(m_nTelID == ZERO)
	{
		MessageBox("다시 시도해 주세요", "확인", MB_ICONINFORMATION);
		return;		
	}
	*/

	OnOK();
}

void CAddManagerDlg::OnBnClickedCancel()
{	
	OnCancel();
}

BOOL CAddManagerDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_edtManager.SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CAddManagerDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if(pMsg->hwnd == m_edtManager.GetSafeHwnd()) {
			m_edtDepart.SetFocus();
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtDepart.GetSafeHwnd()) {
			m_edtTel.SetFocus();
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtTel.GetSafeHwnd()) {
			m_edtTel2.SetFocus();
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtTel2.GetSafeHwnd()) {
			m_edtTel3.SetFocus();
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtTel3.GetSafeHwnd()) {
			m_edtTel4.SetFocus();
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtTel4.GetSafeHwnd()) {
			m_btnOK.SetFocus();
			return TRUE;
		}
		else if(pMsg->hwnd == m_btnOK.GetSafeHwnd()) {
			OnBnClickedOk();
			return TRUE;
		}

		return TRUE;
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CAddManagerDlg::OnBnClickedEraseBtn()
{
	m_strManager = "";
	m_strDepart = "";
	m_strTel = "";
	m_strTel2 = "";
	m_strTel3 = "";
	m_strTel4 = "";

	UpdateData(FALSE);
}
