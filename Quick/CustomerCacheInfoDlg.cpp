// CustomerCacheInfoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "CustomerCacheInfoDlg.h"
#include "CustomerData.h"


// CCustomerCacheInfoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCustomerCacheInfoDlg, CMyDialog)

CCustomerCacheInfoDlg::CCustomerCacheInfoDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCustomerCacheInfoDlg::IDD, pParent)
{

}

CCustomerCacheInfoDlg::~CCustomerCacheInfoDlg()
{
}

void CCustomerCacheInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCustomerCacheInfoDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REMAKE_BTN, &CCustomerCacheInfoDlg::OnBnClickedRemakeBtn)
END_MESSAGE_MAP()


// CCustomerCacheInfoDlg 메시지 처리기입니다.

BOOL CCustomerCacheInfoDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	
	m_cus.SetCompanyCode(m_ci.m_nUseCustomerTable, m_ba.GetCount() < 2 ? FALSE : TRUE);
	GetDlgItem(IDC_INFO_STATIC)->SetWindowText(m_cus.GetInfo());

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CCustomerCacheInfoDlg::OnBnClickedRemakeBtn()
{
	m_cus.ClearFileData();
	if(m_cus.IsDataLoadOK())
		MessageBox("프로그램 재시작 바랍니다.", "확인", MB_ICONINFORMATION);
	else
		MessageBox("고객데이터를 초기화 하였습니다.\n접수화면으로 진행 하시기 바랍니다.", "확인", MB_ICONINFORMATION);

}
