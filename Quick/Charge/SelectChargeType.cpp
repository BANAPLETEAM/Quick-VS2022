// SelectChargeType.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "quick.h"
#include "SelectChargeType.h"
#include "ChargeContainer.h"
#include "ChargeDongNewDlg.h"


// CSelectChargeType ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSelectChargeType, CMyDialog)
CSelectChargeType::CSelectChargeType(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSelectChargeType::IDD, pParent)
{
	m_pChargeContainer = NULL;
}

CSelectChargeType::~CSelectChargeType()
{
}

void CSelectChargeType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSelectChargeType, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOkBtn)
	ON_BN_CLICKED(IDC_BASIC_OLD_BTN, OnBnClickedBasicOldBtn)
	ON_BN_CLICKED(IDC_DISTANCE_OLD_BTN, OnBnClickedDistanceOldBtn)
	
	//ON_BN_CLICKED(IDC_GU_BASIC_OLD_BTN, &CSelectChargeType::OnBnClickedGuBasicOldBtn)
	ON_BN_CLICKED(IDC_BASIC_NEW_BTN2, &CSelectChargeType::OnBnClickedBasicNewBtn2)
	ON_BN_CLICKED(IDC_BASIC_NEW_BTN, &CSelectChargeType::OnBnClickedBasicNewBtn)
END_MESSAGE_MAP()


// CSelectChargeType �޽��� ó�����Դϴ�.

void CSelectChargeType::OnBnClickedOkBtn()
{
	OnOK();

}

void CSelectChargeType::OnBnClickedBasicOldBtn()
{	
	//if(m_ui.strID == "demo")
	//	m_pChargeContainer->ChargeDongDlg3Show();
	//else
		m_pChargeContainer->ChargeDongDlg3Show();
}


void CSelectChargeType::OnBnClickedDistanceOldBtn()
{
	m_pChargeContainer->ChargeDistanceDlgShow();
}

//
//void CSelectChargeType::OnBnClickedGuBasicOldBtn()
//{
//	m_pChargeContainer->ChargeDlgShow();
//}

void CSelectChargeType::OnBnClickedBasicNewBtn2()
{
	CChargeDongNewDlg *p = new CChargeDongNewDlg;
	p->Create(CChargeDongNewDlg::IDD, this);
	p->ShowWindow(SW_SHOW);
}

void CSelectChargeType::OnBnClickedBasicNewBtn()
{
	CChargeDongNewDlg *p = new CChargeDongNewDlg;
	p->Create(CChargeDongNewDlg::IDD, this);
	p->ShowWindow(SW_SHOW);
}