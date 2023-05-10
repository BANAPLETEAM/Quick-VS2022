// CusSmsDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "CusSmsDlg.h"



// CCusSmsDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCusSmsDlg, CMyDialog)
CCusSmsDlg::CCusSmsDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCusSmsDlg::IDD, pParent)
{
	m_nRiderShotage = FALSE;
}

CCusSmsDlg::~CCusSmsDlg()
{
}

void CCusSmsDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PHONE_EDIT, m_PhoneEdt);
	DDX_Control(pDX, IDC_MEMO_EDIT, m_TextEdt);
	DDX_Text(pDX, IDC_PHONE_EDIT, m_strPhone);
	DDX_Text(pDX, IDC_MEMO_EDIT, m_strText);
	DDX_Control(pDX, IDC_LEN_STATIC, m_LenStatic);
	DDX_Control(pDX, IDC_BRANCH_STATIC, m_BranchStatic);
}


BEGIN_MESSAGE_MAP(CCusSmsDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_EN_CHANGE(IDC_MEMO_EDIT, OnEnChangeMemoEdit)
END_MESSAGE_MAP()


// CCusSmsDlg 메시지 처리기입니다.

void CCusSmsDlg::OnBnClickedOk()
{
	UpdateData();
	OnOK();
}

BOOL CCusSmsDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CString strBranch;
	strBranch.Format("%s(%s)지사의 설정", m_ci.GetBranchName(m_nCompany),  
			m_ci.GetPhone(m_nCompany));

	m_BranchStatic.SetWindowText(strBranch);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_cus_cancel_sms_ment2");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);

	if(pRs.Execute(&pCmd))
	{
		CString strPhone, strText,sRiderShotageSMS,sRiderShotageCallBack;

		if(!pRs.IsEOF())
		{
			pRs.GetFieldValue("sCusCancelSMS", strText);
			pRs.GetFieldValue("sCusCancelCallBack", strPhone);
			pRs.GetFieldValue("sRiderShotageSMS", sRiderShotageSMS);
			pRs.GetFieldValue("sRiderShotageCallBack", sRiderShotageCallBack);

		}
		if(m_nRiderShotage)
		{
			m_PhoneEdt.SetWindowText(sRiderShotageCallBack);
			m_TextEdt.SetWindowText(sRiderShotageSMS);
		}
		else
		{
			m_PhoneEdt.SetWindowText(strPhone);
			m_TextEdt.SetWindowText(strText);
		}
	}

	UpdateTextCount();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CCusSmsDlg::OnEnChangeMemoEdit()
{
	UpdateTextCount();
}

void CCusSmsDlg::UpdateTextCount()
{
	CString strText;
	m_TextEdt.GetWindowText(strText);
	int nLen = strText.GetLength();
	strText.Format("%d/80", nLen);
	m_LenStatic.SetWindowText(strText);
}


