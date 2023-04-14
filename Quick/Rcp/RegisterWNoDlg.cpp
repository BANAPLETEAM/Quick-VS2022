// RegisterWNoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RegisterWNoDlg.h"



// CRegisterWNoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRegisterWNoDlg, CMyDialog)
CRegisterWNoDlg::CRegisterWNoDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRegisterWNoDlg::IDD, pParent)
{
}

CRegisterWNoDlg::~CRegisterWNoDlg()
{
}

void CRegisterWNoDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_Stc1);
	DDX_Control(pDX, IDC_STATIC2, m_Stc2);
	DDX_Control(pDX, IDC_REPORT_LIST, m_wndReport);
}


BEGIN_MESSAGE_MAP(CRegisterWNoDlg, CMyDialog)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_REGISTER1, OnRegister1)
	ON_COMMAND(ID_REGISTER2, OnRegister2)
	ON_BN_CLICKED(IDC_REFRESH, OnBnClickedRefresh)
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOkBtn)
END_MESSAGE_MAP()


// CRegisterWNoDlg 메시지 처리기입니다.

void CRegisterWNoDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	//m_wndReport.ScreenToClient(&point);
	m_wndReport.GetWindowRect(&rect);

	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(8);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CRegisterWNoDlg::OnRegister1()
{
	long nIndex = m_wndReport.GetNextItem(-1, LVNI_SELECTED);

	long nCompany = m_wndReport.GetItemLong(nIndex);
	CString sRNo = m_wndReport.GetItemText(nIndex, 0);
	CString sName = m_wndReport.GetItemText(nIndex, 1);

	AfxGetApp()->WriteProfileInt("Messanger", "nFindCompany", nCompany);
	AfxGetApp()->WriteProfileInt("Messanger", "nFindRNo", _ttoi(sRNo));
	AfxGetApp()->WriteProfileString("Messanger", "sFindName", sName);

	CString str;
	str.Format("%s번 %s",sRNo, sName);
	m_Stc1.SetWindowText(str);
}

void CRegisterWNoDlg::OnRegister2()
{
	long nIndex = m_wndReport.GetNextItem(-1, LVNI_SELECTED);

	long nCompany = m_wndReport.GetItemLong(nIndex);
	CString sRNo = m_wndReport.GetItemText(nIndex, 0);
	CString sName = m_wndReport.GetItemText(nIndex, 1);

	AfxGetApp()->WriteProfileInt("Messanger", "nFindCompany2", nCompany);
	AfxGetApp()->WriteProfileInt("Messanger", "nFindRNo2", _ttoi(sRNo));
	AfxGetApp()->WriteProfileString("Messanger", "sFindName2", sName);

	CString str;
	str.Format("%s번 %s", sRNo, sName);
	m_Stc2.SetWindowText(str);

	long a =  AfxGetApp()->GetProfileInt("Messanger", "nFindCompany2", 0);
}
BOOL CRegisterWNoDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_wndReport.InsertColumn(0, "사번", LVCFMT_LEFT, 50);
	m_wndReport.InsertColumn(1, "이름", LVCFMT_LEFT, 60);

	m_wndReport.Populate();

	RefreshList();

	AfxGetApp()->GetProfileInt("Messanger", "nFindCompany", 0);
	AfxGetApp()->GetProfileInt("Messanger", "nFindCompany2", 0);

	long nFindCompany = AfxGetApp()->GetProfileInt("Messanger", "nFindCompany", 0);
	long nFindCompany2 = AfxGetApp()->GetProfileInt("Messanger", "nFindCompany2", 0);
	long nFindRNo= AfxGetApp()->GetProfileInt("Messanger", "nFindRNo", 0);
	long nFindRNo2 = AfxGetApp()->GetProfileInt("Messanger", "nFindRNo2", 0);
	CString sName = AfxGetApp()->GetProfileString("Messanger", "sFindName", "");
	CString sName2 = AfxGetApp()->GetProfileString("Messanger", "sFindName2", "");

	CString str1;
	CString str2;

	if(nFindCompany == 0)
		str1 = "등록안됨";
	else
		str1.Format("%d번 %s", nFindRNo, sName);

	m_Stc1.SetWindowText(str1);

	if(nFindCompany == 2)
		str2 = "등록안됨";
	else
		str2.Format("%d번 %s", nFindRNo2, sName2);

	m_Stc2.SetWindowText(str2);
	
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRegisterWNoDlg::RefreshList()
{
	m_wndReport.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_wno");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_bRcpIntMode1 == TRUE ? 1 : 0 );

	if(!pRs.Execute(&pCmd)) return;

	long nCompany, nMNo;
	CString sName;
	char buffer[20];

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("lCode", nCompany);
		pRs.GetFieldValue("nMNo", nMNo);
		pRs.GetFieldValue("sName", sName);

		m_wndReport.InsertItem(i, itoa(nMNo, buffer, 10));
		m_wndReport.SetItemText(i, 1, sName);
		m_wndReport.SetItemLong(i, nCompany);

		pRs.MoveNext();
	} 

	m_wndReport.Populate();

}

void CRegisterWNoDlg::OnBnClickedRefresh()
{
	RefreshList();
}

void CRegisterWNoDlg::OnBnClickedOkBtn()
{
	OnOK();
}
