// ShareTransferCancelDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareTransferCancelDlg.h"

#include "ShareTranferRequestDlg.h"

// CShareTransferCancelDlg 대화 상자입니다.

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


// CShareTransferCancelDlg 메시지 처리기입니다.

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

	MessageBox("거절되었습니다", "확인", MB_ICONINFORMATION);

	m_pParent->ReFresh();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}

void CShareTransferCancelDlg::OnBnClickedCancel()
{
//	MessageBox("취소되었습니다", "확인", MB_ICONERROR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}
