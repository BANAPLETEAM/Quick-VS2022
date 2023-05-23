// RcpMapSetupDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RcpMapSetupDlg.h"


#define LOAD_FROM_REG(y, x) info.x = AfxGetApp()->GetProfileInt("RcpMapSetup", #x, y);
#define SAVE_TO_REG(x) AfxGetApp()->WriteProfileInt("RcpMapSetup", #x, info.x);
#define SET_CHECK(x, y)  ((CButton*)GetDlgItem(x))->SetCheck(m_info.y);
#define SET_COMBO(x, y)  ((CComboBox*)GetDlgItem(x))->SetCurSel(m_info.y);
#define GET_CHECK(x, y)  m_info.y = ((CButton*)GetDlgItem(x))->GetCheck();
#define GET_COMBO(x, y)  m_info.y = ((CComboBox*)GetDlgItem(x))->GetCurSel();

// CRcpMapSetupDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRcpMapSetupDlg, CMyDialog)

CRcpMapSetupDlg::CRcpMapSetupDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRcpMapSetupDlg::IDD, pParent)
{
}

CRcpMapSetupDlg::~CRcpMapSetupDlg()
{ 
} 

void CRcpMapSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRcpMapSetupDlg, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOk)
END_MESSAGE_MAP()


// CRcpMapSetupDlg 메시지 처리기입니다.

BOOL CRcpMapSetupDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	LF->LoadFromReg(m_info);
	StructToResource();
	
	return TRUE;
}

void CRcpMapSetupDlg::StructToResource()
{
	SET_CHECK(IDC_RCP_MOVE_MAP_BTN, nRcpMoveMap)
	SET_CHECK(IDC_RCP_DLG_MOVE_MAP_CHECK, nRcpDlgMoveMap)
	SET_CHECK(IDC_NOT_CREATE_MAP_FORM_CHECK, nNotCreateMapForm)
	SET_CHECK(IDC_JOIN_WITH_CID_CHECK, nJoinWithCID)
}

void CRcpMapSetupDlg::ResourceToStruct()
{
	GET_CHECK(IDC_RCP_MOVE_MAP_BTN, nRcpMoveMap)
	GET_CHECK(IDC_RCP_DLG_MOVE_MAP_CHECK, nRcpDlgMoveMap)
	GET_CHECK(IDC_NOT_CREATE_MAP_FORM_CHECK, nNotCreateMapForm)
	GET_CHECK(IDC_JOIN_WITH_CID_CHECK, nJoinWithCID)
}


void CRcpMapSetupDlg::OnBnClickedOk()
{
	ResourceToStruct();
	LF->SaveToReg(m_info);
	OnOK();
}