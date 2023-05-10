// AddRiderShareInfoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "AddRiderShareInfoDlg.h"
#include "SearchRiderDlg.h"
#include "RiderShareBoardDlg.h"
// CAddRiderShareInfoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAddRiderShareInfoDlg, CMyDialog)

CAddRiderShareInfoDlg::CAddRiderShareInfoDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAddRiderShareInfoDlg::IDD, pParent)
{
	m_nRiderCompany = 0;
	m_nRNo = 0;
	m_strRName = "";
	m_strMsg = "";
}

CAddRiderShareInfoDlg::~CAddRiderShareInfoDlg()
{
}

void CAddRiderShareInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RNO_EDIT, m_edtRNo);
	DDX_Control(pDX, IDC_RIDER_EDIT, m_edtRider);
	DDX_Control(pDX, IDC_ETC_EDIT, m_edtEtc);
}


BEGIN_MESSAGE_MAP(CAddRiderShareInfoDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CAddRiderShareInfoDlg::OnBnClickedSearchBtn)
	ON_BN_CLICKED(IDC_SHOW_RIDER_INFO_BTN, &CAddRiderShareInfoDlg::OnBnClickedShowRiderInfoBtn)
	ON_BN_CLICKED(IDC_OK_BTN, &CAddRiderShareInfoDlg::OnBnClickedOkBtn)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CAddRiderShareInfoDlg 메시지 처리기입니다.

BOOL CAddRiderShareInfoDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	if(m_nRiderCompany > 0 && m_nRNo > 0)
	{
		char buffer[10];
		m_edtRider.SetWindowText(CString(itoa(m_nRNo, buffer, 10)) + "/" + m_strRName);
		SetTimer(1000, 100, NULL);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAddRiderShareInfoDlg::OnBnClickedSearchBtn()
{
	CString strSearch;
	m_edtRNo.GetWindowText(strSearch);

	if(strSearch.GetLength() == 0)
	{
		MessageBox("검색어 (사번, 기사명)을 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CSearchRiderDlg dlg;
	dlg.m_strSearch = strSearch;

	if(dlg.DoModal() == IDOK)
	{
		m_nRiderCompany = dlg.m_nRiderCompany;
		m_nRNo = dlg.m_nRNo;
		m_strRName = dlg.m_strRName;

		char buffer[10];

		if(m_nRiderCompany > 0 && m_nRNo > 0)
			m_edtRider.SetWindowText(CString(itoa(m_nRNo, buffer, 10)) + "/" + m_strRName);

		m_edtEtc.SetFocus();
	}
}

void CAddRiderShareInfoDlg::OnBnClickedShowRiderInfoBtn()
{
	if(m_nRiderCompany > 0 && m_nRNo > 0)
		LU->ShowRiderInfoDlg(m_nRiderCompany, m_nRNo);
	else
	{
		MessageBox("기사를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}
}

void CAddRiderShareInfoDlg::OnBnClickedOkBtn()
{
	if(m_nRiderCompany > 0 && m_nRNo > 0)
	{	
		UpdateData(TRUE);
		m_edtEtc.GetWindowText(m_strMsg);

		if(m_strMsg.GetLength() < 5)
		{
			AfxMessageBox("5자이상으로 입력하여 주세요", MB_ICONINFORMATION);
			return;
		}

		CRiderShareBoardDlg *pDlg = (CRiderShareBoardDlg*)(GetParent());

		if(pDlg != NULL)
		{
			pDlg->AddRiderInfo();
			ShowWindow(SW_HIDE);
		}
	}
	else
	{
		MessageBox("기사를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}
}

BOOL CAddRiderShareInfoDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if(pMsg->hwnd == m_edtRNo.GetSafeHwnd())
			OnBnClickedSearchBtn();

		if(pMsg->hwnd != m_edtEtc.GetSafeHwnd())
			return TRUE;
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CAddRiderShareInfoDlg::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(nIDEvent);
	m_edtEtc.SetFocus();

	CMyDialog::OnTimer(nIDEvent);
}
