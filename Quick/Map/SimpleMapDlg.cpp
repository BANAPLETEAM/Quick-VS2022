// SimpleMapDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "SimpleMapDlg.h"

#define  MAP_TOP 25
// CSimpleMapDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSimpleMapDlg, CMyDialog)

CSimpleMapDlg::CSimpleMapDlg(UINT nID, CWnd* pParent /*=NULL*/)
	: CMyDialog(nID, pParent)
{
	m_nIDTemplate = nID;
	m_pParent = pParent;
	m_bAutoDelete = TRUE;
	m_bSendPOISelect = FALSE;
	m_bStartPlace = FALSE;
}

CSimpleMapDlg::~CSimpleMapDlg()
{
}

void CSimpleMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TALMAP_CTRL, m_wndMap);
}


BEGIN_MESSAGE_MAP(CSimpleMapDlg, CMyDialog)
	ON_WM_SIZE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


BEGIN_EVENTSINK_MAP(CSimpleMapDlg, CMyDialog)
	//ON_EVENT(CSimpleMapDlg, IDC_TALMAP_CTRL, 1, OnCreateMap, VTS_I4)
	ON_EVENT(CSimpleMapDlg, IDC_TALMAP_CTRL, 43, OnPOIClick, VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4)
END_EVENTSINK_MAP()



// CSimpleMapDlg �޽��� ó�����Դϴ�.
BOOL CSimpleMapDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_wndMap.CreateWait();
	CenterWindow(GetDesktopWindow());
	OnSize(0xFF, 0, 0);

	return FALSE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CSimpleMapDlg::CreateDlg(BOOL bAutoDelete)
{
	m_bAutoDelete = bAutoDelete;
	Create(m_nIDTemplate, m_pParent);
}

void CSimpleMapDlg::OnSize(UINT nType, int cx, int cy)
{
	if(nType != 0xFF)
		CMyDialog::OnSize(nType, cx, cy);

	if(m_wndMap.GetSafeHwnd())
	{
		CRect rc;
		GetClientRect(rc);
		m_wndMap.MoveWindow(rc);
	}
}

void CSimpleMapDlg::OnClose()
{
	if(m_bAutoDelete)
	{
		CMyDialog::OnClose();
		delete this;
	}
	else
	{
		ShowWindow(SW_HIDE);
	}
}

void CSimpleMapDlg::OnPOIClick(LPDISPATCH POI, long nFlag, long X, long Y)
{
	if(!m_bSendPOISelect)
		return;

	CXPOIItem poi;
	poi.AttachDispatch(POI, FALSE);

	CXPopupMenu menu = m_wndMap.app.GetPopupMenu();
	menu.Create();

	CString strText;
	strText.Format("�ش� POI�� %s�� ������", m_bStartPlace ? "�����" : "������");
	menu.AppendString(1000, strText, strText, "", 0);

	CXPoint point = m_wndMap.uiman.ClientToScreen(X, Y);
	CXPopupMenuItem mitem = menu.TrackPopupMenu(0, point.GetX(), point.GetY());
	if(mitem.m_lpDispatch != NULL)
	{
		switch(mitem.GetID())
		{
		case 1000:
			m_pParent->PostMessage(WM_SELECT_POI_ON_MAP, poi.GetData(), 0);
			break;
		}
	}
}

