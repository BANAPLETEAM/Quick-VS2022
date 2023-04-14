// MentAddDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MentAddDlg.h"

#include "SpecialCharDlg.h"
#include "MentDlg.h"

// CMentAddDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMentAddDlg, CMyDialog)
CMentAddDlg::CMentAddDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CMentAddDlg::IDD, pParent)
{
	m_pSpecialCharDlg = NULL;
	m_strID = "";
}

CMentAddDlg::~CMentAddDlg()
{
}

void CMentAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TITLE_EDT, m_edtTitle);
	DDX_Control(pDX, IDC_MEMO_EDT, m_edtMemo);
	DDX_Control(pDX, IDC_CHAR_COUNT_STC, m_stcCharCount);
	DDX_Control(pDX, IDC_MENT_ADD_BTN, m_btnMentAdd);
	DDX_Control(pDX, IDC_CLOSE_BTN, m_btnClose);
	DDX_Control(pDX, IDC_SPECIAL_CHAR_BTN, m_btnSpecialChar);
	DDX_Control(pDX, IDC_COPY_EDT, m_edtCopy);
	DDX_Control(pDX, IDC_CLOSE_BTN1, m_btnClose1);
}


BEGIN_MESSAGE_MAP(CMentAddDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SPECIAL_CHAR_BTN, OnBnClickedSpecialCharBtn)
	ON_BN_CLICKED(IDC_CLOSE, OnBnClickedClose)
	ON_BN_CLICKED(IDC_MENT_ADD_BTN, OnBnClickedMentAddBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, OnBnClickedCloseBtn)
	ON_EN_SETFOCUS(IDC_TITLE_EDT, OnEnSetfocusTitleEdt)
	ON_EN_SETFOCUS(IDC_MEMO_EDT, OnEnSetfocusMemoEdt)
	ON_WM_LBUTTONDOWN()
	ON_EN_CHANGE(IDC_MEMO_EDT, OnEnChangeMemoEdt)
END_MESSAGE_MAP()


// CMentAddDlg 메시지 처리기입니다.

void CMentAddDlg::OnBnClickedSpecialCharBtn()
{
	if(m_pSpecialCharDlg == NULL)
	{
		m_pSpecialCharDlg = new CSpecialCharDlg();
		m_pSpecialCharDlg->m_pParent = this;
		m_pSpecialCharDlg->Create(IDD_SPECIAL_CHAR_DLG, NULL);
		m_pSpecialCharDlg->ShowWindow(SW_SHOW);
	}

	if(m_bTitle)
		m_edtTitle.SetFocus();
	else
		m_edtMemo.SetFocus();}

void CMentAddDlg::OnBnClickedClose()
{
	OnCancel();
}

void CMentAddDlg::OnBnClickedMentAddBtn()
{
	UpdateData(true);

	m_edtTitle.GetWindowText(m_strTitle);
	m_edtMemo.GetWindowText(m_strMemo);

	if(m_strTitle.GetLength() <= 0)
	{
		MessageBox("타이틀을 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}
	if(m_strMemo.GetLength() <= 0)
	{
		MessageBox("내용을 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(m_strID == "")
	{
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb,"insert_ment_1");

		pCmd.AddParameter(m_ui.nCompany);
		pCmd.AddParameter(160);   //nType가 160으로 들어가면 기존에 있던것 이외에 직접 타이틀을 만들어서 추가
		pCmd.AddParameter(m_strTitle);
		pCmd.AddParameter(m_strMemo);

		if(!pRs.Execute(&pCmd) ) return;

		MessageBox("정상적으로 추가되었습니다", "확인", MB_ICONINFORMATION);
		m_edtTitle.SetWindowText("");
		m_edtMemo.SetWindowText("");
		m_stcCharCount.SetWindowText("글자수");

		pRs.Close();
	}
	else
	{
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb,"update_ment");

		pCmd.AddParameter(_ttoi(m_strID));
		pCmd.AddParameter(m_strTitle);
		pCmd.AddParameter( m_strMemo);

		if(!pRs.Execute(&pCmd) ) return;

		MessageBox("편집되었습니다", "확인", MB_ICONINFORMATION);
		m_edtTitle.SetWindowText("");
		m_edtMemo.SetWindowText("");
		m_stcCharCount.SetWindowText("글자수");

		pRs.Close();
		OnBnClickedCloseBtn();
	}


	m_pParent->RefreshList();
}

void CMentAddDlg::OnBnClickedCloseBtn()
{
	if(m_pSpecialCharDlg != NULL)
	{
		m_pSpecialCharDlg->Close();
		delete m_pSpecialCharDlg;
		m_pSpecialCharDlg = NULL;
	}

	OnCancel();
}

void CMentAddDlg::OnEnSetfocusTitleEdt()
{
	if(m_pSpecialCharDlg != NULL)
	{
		m_pSpecialCharDlg->m_rdoTitle.SetCheck(BST_CHECKED);
		m_pSpecialCharDlg->m_rdoMemo.SetCheck(false);
	}
}

void CMentAddDlg::OnEnSetfocusMemoEdt()
{
	if(m_pSpecialCharDlg != NULL)
	{
		m_pSpecialCharDlg->m_rdoMemo.SetCheck(BST_CHECKED);
		m_pSpecialCharDlg->m_rdoTitle.SetCheck(false);
	}
}

void CMentAddDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

	if(m_pSpecialCharDlg != NULL)
	{
		CRect rect;
		GetClientRect(rect);
		m_pSpecialCharDlg->PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x + rect.Width() , point.y));
		m_pSpecialCharDlg->SetFocus();
	}

	CMyDialog::OnLButtonDown(nFlags, point);
}

void CMentAddDlg::OnEnChangeMemoEdt()
{
	CString str;
	m_edtMemo.GetWindowText(str);

	str.Format("글자수 : %d/80",str.GetLength());

	m_stcCharCount.SetWindowText(str);
}
