// SendOtherRiderMsgDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "SendOtherRiderMsgDlg.h"


// CSendOtherRiderMsgDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSendOtherRiderMsgDlg, CMyDialog)

CSendOtherRiderMsgDlg::CSendOtherRiderMsgDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSendOtherRiderMsgDlg::IDD, pParent)
{
	m_nRiderCompany = 0;
	m_nRNo = 0;
}

CSendOtherRiderMsgDlg::~CSendOtherRiderMsgDlg()
{
}

void CSendOtherRiderMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG_EDIT, m_edtMsg);
}
 

BEGIN_MESSAGE_MAP(CSendOtherRiderMsgDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SEND_BTN, OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
END_MESSAGE_MAP()

void CSendOtherRiderMsgDlg::OnBnClickedSendBtn()
{
	CString strMsg;
	m_edtMsg.GetWindowText(strMsg);

	if(strMsg.IsEmpty())
	{
		MessageBox("전송하실 메시지를 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "edit_rider_msg10"); 
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), 0);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nRiderCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nRNo);
	pCmd.AddParameter(typeString, typeInput, strMsg.GetLength(), strMsg);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nWNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), 0);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), 1);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), 1);
	pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);

	if(!pCmd.Execute()) 
		return;

	MessageBox("전송 되었습니다", "확안", MB_ICONINFORMATION);
	OnOK();
}

void CSendOtherRiderMsgDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}

BOOL CSendOtherRiderMsgDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	return TRUE;
}
