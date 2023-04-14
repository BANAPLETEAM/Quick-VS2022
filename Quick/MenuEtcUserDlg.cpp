// MenuEtcUserDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "MenuEtcUserDlg.h"



// CMenuEtcUserDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMenuEtcUserDlg, CMyDialog)
CMenuEtcUserDlg::CMenuEtcUserDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CMenuEtcUserDlg::IDD, pParent)
{
}

CMenuEtcUserDlg::~CMenuEtcUserDlg()
{
}

void CMenuEtcUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ETC_TITLE_EDIT1, m_EtcTitleEdt[0]);
	DDX_Control(pDX, IDC_ETC_TITLE_EDIT2, m_EtcTitleEdt[1]);
	DDX_Control(pDX, IDC_ETC_TITLE_EDIT3, m_EtcTitleEdt[2]);
	DDX_Control(pDX, IDC_ETC_TITLE_EDIT4, m_EtcTitleEdt[3]);
	DDX_Control(pDX, IDC_ETC_TITLE_EDIT5, m_EtcTitleEdt[4]);
	DDX_Control(pDX, IDC_ETC_MEMO_EDIT1, m_EtcMemoEdt[0]);
	DDX_Control(pDX, IDC_ETC_MEMO_EDIT2, m_EtcMemoEdt[1]);
	DDX_Control(pDX, IDC_ETC_MEMO_EDIT3, m_EtcMemoEdt[2]);
	DDX_Control(pDX, IDC_ETC_MEMO_EDIT4, m_EtcMemoEdt[3]);
	DDX_Control(pDX, IDC_ETC_MEMO_EDIT5, m_EtcMemoEdt[4]);
	DDX_Control(pDX, IDC_FRONT_CHECK, m_chkFront);
}


BEGIN_MESSAGE_MAP(CMenuEtcUserDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(ID_ALL_OK_BTN, OnBnClickedAllOkBtn)
END_MESSAGE_MAP()


// CMenuEtcUserDlg �޽��� ó�����Դϴ�.

void CMenuEtcUserDlg::OnBnClickedOk()
{
	UpdateData(true);

	if(SaveSetting(m_pBi))
	{
		AfxGetApp()->WriteProfileInt(m_ui.strID + "_Etc", "Front", m_chkFront.GetCheck());
		
		MessageBox("����Ǿ����ϴ�\r\n�� ������ ����˴ϴ�", "Ȯ��", MB_ICONINFORMATION);
		OnOK();
	}
}

BOOL CMenuEtcUserDlg::SaveSetting(CBranchInfo *pBi)
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_etc_menu_user_memo");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), pBi->nCompanyCode);

	for(int i=0; i<5; i++)
	{
		CString sEtcUserTitel;
		CString sEtcUserMemo; 
		m_EtcTitleEdt[i].GetWindowText(sEtcUserTitel);
		m_EtcMemoEdt[i].GetWindowText(sEtcUserMemo);

		if(i == 4) //5��° ����� ���Ǵ� ������Ʈ�� ����
		{			
			AfxGetApp()->WriteProfileString(m_ui.strID + "_Etc", "Title", sEtcUserTitel); //�������� ������Ʈ��
			AfxGetApp()->WriteProfileString(m_ui.strID + "_Etc", "Memo", sEtcUserMemo);
		}
		else
		{
			pCmd.AddParameter(typeString, typeInput, sEtcUserTitel.GetLength(), sEtcUserTitel);
			pCmd.AddParameter(typeString, typeInput, sEtcUserMemo.GetLength(), sEtcUserMemo);
		}
	}

	if(!pRs.Execute(&pCmd)) 
	{
		MessageBox("�ٽ� �õ��� �ּ���", "�������", MB_ICONERROR);
		return FALSE;
	}

	return TRUE;
}

BOOL CMenuEtcUserDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_EtcTitleEdt[0].SetWindowText(m_pBi->sEtcUserTitle1);
	m_EtcTitleEdt[1].SetWindowText(m_pBi->sEtcUserTitle2);
	m_EtcTitleEdt[2].SetWindowText(m_pBi->sEtcUserTitle3);
	m_EtcTitleEdt[3].SetWindowText(m_pBi->sEtcUserTitle4);
	m_EtcMemoEdt[0].SetWindowText(m_pBi->sEtcUserMemo1);
	m_EtcMemoEdt[1].SetWindowText(m_pBi->sEtcUserMemo2);
	m_EtcMemoEdt[2].SetWindowText(m_pBi->sEtcUserMemo3);
	m_EtcMemoEdt[3].SetWindowText(m_pBi->sEtcUserMemo4);

	CString sRegTitle, sRegMemo;

    sRegTitle =	AfxGetApp()->GetProfileString(m_ui.strID + "_Etc", "Title", "");
	sRegMemo =	AfxGetApp()->GetProfileString(m_ui.strID + "_Etc", "Memo", "");

	m_chkFront.SetCheck(AfxGetApp()->GetProfileInt(m_ui.strID + "_Etc", "Front", 0));

	m_EtcTitleEdt[4].SetWindowText(sRegTitle);
	m_EtcMemoEdt[4].SetWindowText(sRegMemo);

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CMenuEtcUserDlg::OnBnClickedAllOkBtn()
{
	BOOL bOk = FALSE;

	for(int i=1; i<m_ba.GetCount(); i++)
	{
		CBranchInfo *pBi = m_ba.GetAt(i);
		bOk = SaveSetting(pBi);

		if(!bOk)
			break;
	}

	if(bOk)
	{
		MessageBox("����Ǿ����ϴ�\r\n�� ������ ����˴ϴ�", "Ȯ��", MB_ICONINFORMATION);
		OnOK();
	}
}
