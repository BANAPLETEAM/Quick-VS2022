// VarietyDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderBoardAddDlg.h"



// CRiderBoardAddDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRiderBoardAddDlg, CMyDialog)
CRiderBoardAddDlg::CRiderBoardAddDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRiderBoardAddDlg::IDD, pParent)
{
	m_strTitle = "";
	m_strMemo = "";
	m_bShow = TRUE;
	m_nIndex = 0;
}

CRiderBoardAddDlg::~CRiderBoardAddDlg()
{
}

void CRiderBoardAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TITLE_EDIT, m_strTitle);
	DDX_Text(pDX, IDC_MEMO_EDIT, m_strMemo);
	DDX_Check(pDX, IDC_SHOW_CHECK, m_bShow);
}


BEGIN_MESSAGE_MAP(CRiderBoardAddDlg, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BTN, &CRiderBoardAddDlg::OnBnClickedOkBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, &CRiderBoardAddDlg::OnBnClickedCancelBtn)
END_MESSAGE_MAP()




BOOL CRiderBoardAddDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	if(m_nIndex > 0)
	{
		RefreshDlg();
		return FALSE;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRiderBoardAddDlg::RefreshDlg()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_rider_board_one");
	cmd.AddParameter(m_nIndex);

	if(!rs.Execute(&cmd))
		return;

	if(rs.GetRecordCount() == 0)
		return;

	rs.GetFieldValue("sTitle", m_strTitle);
	rs.GetFieldValue("sMemo", m_strMemo);
	rs.GetFieldValue("bShow", m_bShow);

	UpdateData(FALSE);
}

void CRiderBoardAddDlg::OnBnClickedOkBtn()
{
	UpdateData(TRUE);

	if(m_strTitle.IsEmpty())
	{
		MessageBox("제목을 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(m_strMemo.IsEmpty())
	{
		MessageBox("내용을 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CMkCommand cmd(m_pMkDb, "insert_rider_board");
	cmd.AddParameter(m_nIndex);
	cmd.AddParameter(m_ci.m_nShareCode1);
	cmd.AddParameter(m_strTitle);
	cmd.AddParameter(m_strMemo);
	cmd.AddParameter(m_bShow);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);

	if(cmd.Execute())
	{
		MessageBox("등록/수정되었습니다", "확인", MB_ICONINFORMATION);
		OnOK();
	}
}

void CRiderBoardAddDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}

BOOL CRiderBoardAddDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN)
		{
			long nUID = ::GetDlgCtrlID(pMsg->hwnd);
 
			if(nUID == IDC_TITLE_EDIT)
				GetDlgItem(IDC_MEMO_EDIT)->SetFocus();
			if(nUID == IDC_MEMO_EDIT)
				return CMyDialog::PreTranslateMessage(pMsg);

			return TRUE;
		}
	}
	
	return CMyDialog::PreTranslateMessage(pMsg);
}
