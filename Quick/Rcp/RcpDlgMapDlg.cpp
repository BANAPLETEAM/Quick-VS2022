// D:\LOGISOFT\Quick2011\Rcp\RcpDlgMapDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "RcpDlgMapDlg.h"
#include "RcpDlg.h"
#include "RcpPlaceInfo.h"


// CRcpDlgMapDlg 대화 상자입니다.

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


// CRcpDlgMapDlg 메시지 처리기입니다.

BOOL CRcpDlgMapDlg::OnInitDialog()
{
	CSimpleMapDlg::OnInitDialog();

	m_chkRcpClose.SetCheck(AfxGetApp()->GetProfileInt("RcpDlgMapDlg", "RcpCloseSameClose", 0));
	OnSize(0xFF, 0, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
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
		MessageBox("오더창에서 지도확인 후 수정해 주세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(m_pRcpDlg)
		SetPlaceAddress(m_pRcpDlg->m_pOrder);
}

void CRcpDlgMapDlg::OnBnClickedSetStartAddressBtn()
{
	if(m_bFromCustomerDlg)
	{
		MessageBox("오더창에서 지도확인 후 수정해 주세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(m_pRcpDlg)
		SetPlaceAddress(m_pRcpDlg->m_pStart);
}

void CRcpDlgMapDlg::OnBnClickedSetDestAddressBtn()
{
	if(m_bFromCustomerDlg)
	{
		MessageBox("오더창에서 지도확인 후 수정해 주세요", "확인", MB_ICONINFORMATION);
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
		MessageBox("주소를 로드 하지 못했습니다.", "실패", MB_ICONINFORMATION);
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