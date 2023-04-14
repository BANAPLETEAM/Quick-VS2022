// ShareTransferCancelDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareTransferCancelDlg.h"

#include "ShareTranferRequestDlg.h"

// CShareTransferCancelDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CShareTransferCancelDlg, CMyDialog)
CShareTransferCancelDlg::CShareTransferCancelDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CShareTransferCancelDlg::IDD, pParent)
{
	m_nID = 0;
	m_pParent = NULL;
}

CShareTransferCancelDlg::~CShareTransferCancelDlg()
{
}

void CShareTransferCancelDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MEMO_EDIT, m_MemoEdt);
}


BEGIN_MESSAGE_MAP(CShareTransferCancelDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CShareTransferCancelDlg �޽��� ó�����Դϴ�.

void CShareTransferCancelDlg::OnBnClickedOk()
{
	CString strRefuse;
	m_MemoEdt.GetWindowText(strRefuse);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_request_cancel_1");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nID);
	pCmd.AddParameter(typeString, typeInput, strRefuse.GetLength(), strRefuse);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);

	if(!pRs.Execute(&pCmd)) return;

	MessageBox("�����Ǿ����ϴ�", "Ȯ��", MB_ICONINFORMATION);

	m_pParent->ReFresh();
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnOK();
}

void CShareTransferCancelDlg::OnBnClickedCancel()
{
//	MessageBox("��ҵǾ����ϴ�", "Ȯ��", MB_ICONERROR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}
