// SaveMentDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "SaveMentDlg.h"


// CSaveMentDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSaveMentDlg, CDialog)

CSaveMentDlg::CSaveMentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveMentDlg::IDD, pParent)
{

}

CSaveMentDlg::~CSaveMentDlg()
{
}

void CSaveMentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MENT_LIST, m_lstMent);
	DDX_Control(pDX, IDC_CUSTOMER_CHECK, m_chkCustomer);
	DDX_Control(pDX, IDC_RIDER_CHK, m_chkRider);
	DDX_Control(pDX, IDC_SMS_EDIT, m_edtMent);
}


BEGIN_MESSAGE_MAP(CSaveMentDlg, CDialog)
	ON_NOTIFY(XTP_NM_GRID_SELCHANGED, IDC_MENT_LIST, OnReportItemChange)
	ON_BN_CLICKED(IDC_CUSTOMER_CHECK, &CSaveMentDlg::OnBnClickedCustomerCheck)
	ON_BN_CLICKED(IDC_RIDER_CHK, &CSaveMentDlg::OnBnClickedRiderChk)
	ON_BN_CLICKED(IDC_ADD_BTN, &CSaveMentDlg::OnBnClickedAddBtn)
	ON_BN_CLICKED(IDC_UPDATE_BTN, &CSaveMentDlg::OnBnClickedUpdateBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CSaveMentDlg::OnBnClickedCloseBtn)
	ON_COMMAND(ID_DELETE, OnDelete)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CSaveMentDlg 메시지 처리기입니다.

BOOL CSaveMentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_chkCustomer.SetCheck(TRUE);

	m_lstMent.InsertColumn(0, "멘트", LVCFMT_LEFT, 250);
	m_lstMent.Populate();

	::FillStateMent();
	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSaveMentDlg::OnBnClickedCustomerCheck()
{
	if(m_chkCustomer.GetCheck())
		m_chkRider.SetCheck(FALSE);
	else
		m_chkRider.SetCheck(TRUE);

	RefreshList();
}

void CSaveMentDlg::OnBnClickedRiderChk()
{
	if(m_chkRider.GetCheck())
		m_chkCustomer.SetCheck(FALSE);
	else
		m_chkCustomer.SetCheck(TRUE);

	RefreshList();
}

void CSaveMentDlg::RefreshList()
{
	m_lstMent.DeleteAllItems();
	long nType = m_chkRider.GetCheck() ? ZERO : ONE;

	long nCount = ZERO;

	MAP_STATE_MENT::iterator it;

	for(it = m_mapStateMent.begin(); it != m_mapStateMent.end(); it++)
	{
		if(nType == it->second.nType)
		{
			m_lstMent.InsertItem(nCount, it->second.strMent);
			m_lstMent.SetItemLong(nCount++, it->second.nID);
		}
	}

	m_lstMent.Populate();
	OnReportItemChange(NULL, NULL);
}

void CSaveMentDlg::OnBnClickedAddBtn()
{
	CString strMent; m_edtMent.GetWindowText(strMent);

	if(strMent.GetLength() < 5)
	{
		MessageBox("5자 이상으로 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CMkCommand pCmd(m_pMkDb, "insert_order_state_ment");
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(m_chkRider.GetCheck() == TRUE ? 0 : 1);
	pCmd.AddParameter(strMent);

	if(pCmd.Execute())
	{
		MessageBox("추가되었습니다", "확인", MB_ICONINFORMATION);
		::FillStateMent();
		RefreshList();
	}
}

void CSaveMentDlg::OnBnClickedUpdateBtn()
{
	CXTPGridRecord *pRecord = m_lstMent.GetFirstSelectedRecord();

	if(pRecord == NULL)
	{
		MessageBox("수정하실 멘트를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CString strMent; m_edtMent.GetWindowText(strMent);

	if(strMent.GetLength() < 5)
	{
		MessageBox("5자 이상으로 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}
	
	long nID = m_lstMent.GetItemLong(pRecord);

	if(nID < ONE)
	{
		MessageBox("수정 불가능한 멘트입니다. 멘트를 추가하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CMkCommand pCmd(m_pMkDb, "update_order_state_ment");
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(nID);
	pCmd.AddParameter(strMent);

	if(pCmd.Execute())
	{
		MessageBox("수정되었습니다", "확인", MB_ICONINFORMATION);
		m_edtMent.SetWindowText("");
		::FillStateMent();
		RefreshList();
	}
}

void CSaveMentDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}

void CSaveMentDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rc;
	m_lstMent.GetWindowRect(&rc);

	if(!rc.PtInRect(point))
		return;

	BCMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU_1);
	BCMenu *pRMenu = (BCMenu*)rMenu.GetSubMenu(2);
	pRMenu->SetMenuDrawMode(TRUE);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}


void CSaveMentDlg::OnDelete()
{
	CXTPGridRecord *pRecord = m_lstMent.GetFirstSelectedRecord();

	if(pRecord == NULL)
	{
		MessageBox("삭제하실 멘트를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	long nID = m_lstMent.GetItemLong(pRecord);

	CMkCommand pCmd(m_pMkDb, "delete_order_state_ment");
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(nID);

	if(pCmd.Execute())
	{
		MessageBox("삭제되었습니다", "확인", MB_ICONINFORMATION);
		m_edtMent.SetWindowText("");
		::FillStateMent();
		RefreshList();
	}
}

void CSaveMentDlg::OnReportItemChange(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	CXTPGridRecord *pRecord = m_lstMent.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	m_edtMent.SetWindowText(m_lstMent.GetItemText(pRecord, ZERO));		
} 