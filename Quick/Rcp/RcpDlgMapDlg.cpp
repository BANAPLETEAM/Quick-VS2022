// D:\LOGISOFT\Quick2011\Rcp\RcpDlgMapDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "RcpDlgMapDlg.h"
#include "RcpDlg.h"
#include "RcpPlaceInfo.h"


// CRcpDlgMapDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRcpDlgMapDlg, CSimpleMapDlg)

CRcpDlgMapDlg::CRcpDlgMapDlg(CWnd* pParent /*=NULL*/)
	: CSimpleMapDlg(CRcpDlgMapDlg::IDD, pParent)
{
	m_pRcpDlg = NULL;
	m_bFromCustomerDlg = FALSE;
}

CRcpDlgMapDlg::~CRcpDlgMapDlg()
{
}

void CRcpDlgMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CSimpleMapDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RCPCLOSE_CHECK, m_chkRcpClose);

}


BEGIN_MESSAGE_MAP(CRcpDlgMapDlg, CSimpleMapDlg)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_RCPCLOSE_CHECK, &CRcpDlgMapDlg::OnBnClickedRcpcloseCheck)
	ON_BN_CLICKED(IDC_SET_ORDER_ADDRESS_BTN, &CRcpDlgMapDlg::OnBnClickedSetOrderAddressBtn)
	ON_BN_CLICKED(IDC_SET_START_ADDRESS_BTN, &CRcpDlgMapDlg::OnBnClickedSetStartAddressBtn)
	ON_BN_CLICKED(IDC_SET_DEST_ADDRESS_BTN, &CRcpDlgMapDlg::OnBnClickedSetDestAddressBtn)
END_MESSAGE_MAP()


// CRcpDlgMapDlg �޽��� ó�����Դϴ�.

BOOL CRcpDlgMapDlg::OnInitDialog()
{
	CSimpleMapDlg::OnInitDialog();

	m_chkRcpClose.SetCheck(AfxGetApp()->GetProfileInt("RcpDlgMapDlg", "RcpCloseSameClose", 0));
	OnSize(0xFF, 0, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CRcpDlgMapDlg::OnBnClickedRcpcloseCheck()
{
	AfxGetApp()->WriteProfileInt("RcpDlgMapDlg", "RcpCloseSameClose", 
		((CButton*)GetDlgItem(IDC_RCPCLOSE_CHECK))->GetCheck());
}

void CRcpDlgMapDlg::OnBnClickedSetOrderAddressBtn()
{
	if(m_bFromCustomerDlg)
	{
		MessageBox("����â���� ����Ȯ�� �� ������ �ּ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	if(m_pRcpDlg)
		SetPlaceAddress(m_pRcpDlg->m_pOrder);
}

void CRcpDlgMapDlg::OnBnClickedSetStartAddressBtn()
{
	if(m_bFromCustomerDlg)
	{
		MessageBox("����â���� ����Ȯ�� �� ������ �ּ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	if(m_pRcpDlg)
		SetPlaceAddress(m_pRcpDlg->m_pStart);
}

void CRcpDlgMapDlg::OnBnClickedSetDestAddressBtn()
{
	if(m_bFromCustomerDlg)
	{
		MessageBox("����â���� ����Ȯ�� �� ������ �ּ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	if(m_pRcpDlg)
		SetPlaceAddress(m_pRcpDlg->m_pDest);
}

void CRcpDlgMapDlg::SetPlaceAddress(CRcpPlaceInfo *pPlace)
{
	long nPosX, nPosY;
	m_wndMap.GetCenterPos(nPosX, nPosY);
	if(!pPlace->SetData(nPosX, nPosY, TRUE))
		MessageBox("�ּҸ� �ε� ���� ���߽��ϴ�.", "����", MB_ICONINFORMATION);
	else 
		ShowWindow(SW_HIDE);
}

void CRcpDlgMapDlg::OnSize(UINT nType, int cx, int cy)
{
	if(nType != 0xFF)
		CMyDialog::OnSize(nType, cx, cy);

	if(m_wndMap.GetSafeHwnd())
	{
/*
		CRect rc;
		static int nTop = 0;
		if(nTop == 0)
		{
			m_wndMap.GetWindowRect(rc);
			ScreenToClient(rc);
			nTop = rc.top;
		}
*/
		CRect rc;
		GetClientRect(rc);
		rc.top = 32;
		m_wndMap.MoveWindow(rc);
	}
}