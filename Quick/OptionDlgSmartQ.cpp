// OptionDlgSmartQ.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "OptionDlgSmartQ.h"
#include "MainOptionDlg2011.h"
#include "SmartCallBoardDlg.h"


// COptionDlgSmartQ

IMPLEMENT_DYNCREATE(COptionDlgSmartQ, CMyFormView)

COptionDlgSmartQ::COptionDlgSmartQ()
	: CMyFormView(COptionDlgSmartQ::IDD)
{

}

COptionDlgSmartQ::~COptionDlgSmartQ()
{
}

void COptionDlgSmartQ::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USE_SMART_QUICK_CHECK, m_chkUseSmartQuick);
	DDX_Control(pDX, IDC_ABLE_SMART_QUICK_CANCEL_CHECK, m_chkAbleSmartQuickCancel);
	DDX_Control(pDX, IDC_SEND_SMARTQ_MENT_EDIT, m_edtSmartQMent);
	DDX_Control(pDX, IDC_SEND_SMARTQ_MENT_CHECK, m_chkSendSmartQMent);
	DDX_Control(pDX, IDC_LENGTH_STATIC, m_stcLength);
	DDX_Control(pDX, IDC_USE_RCP_TIME_CHECK, m_chkUseRcpTimeCheck);
	DDX_Control(pDX, IDC_RCP_TIME_START_COMBO, m_cmbRcpTimeStart);
	DDX_Control(pDX, IDC_RCP_TIME_END_COMBO, m_cmbRcpTimeEnd);
}

BEGIN_MESSAGE_MAP(COptionDlgSmartQ, CMyFormView)
	ON_EN_CHANGE(IDC_SEND_SMARTQ_MENT_EDIT, &COptionDlgSmartQ::OnEnChangeSendSmartqMentEdit)
END_MESSAGE_MAP()


// COptionDlgSmartQ 진단입니다.

#ifdef _DEBUG
void COptionDlgSmartQ::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void COptionDlgSmartQ::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// COptionDlgSmartQ 메시지 처리기입니다.


BOOL COptionDlgSmartQ::Save(long nCompany, BOOL bAll)
{
	UpdateData(TRUE);

	BOOL bUseSmartQuick= m_chkUseSmartQuick.GetCheck();
	BOOL bAbleSmartQuickCancel = m_chkAbleSmartQuickCancel.GetCheck();
	BOOL bSendSmartQMent = m_chkSendSmartQMent.GetCheck();
	CString strSendSmartQMent; m_edtSmartQMent.GetWindowText(strSendSmartQMent);
		
	CMkCommand pCmd(m_pMkDb, "update_option_2011_smartq_2");	//   
	// 인터콜
	pCmd.AddParameter(bAll);	
	pCmd.AddParameter(nCompany);	
	pCmd.AddParameter(bUseSmartQuick);	
	pCmd.AddParameter(bAbleSmartQuickCancel);
	pCmd.AddParameter(bSendSmartQMent);
	pCmd.AddParameter(strSendSmartQMent);
	pCmd.AddParameter(m_chkUseRcpTimeCheck.GetCheck());
	pCmd.AddParameter(m_cmbRcpTimeStart.GetCurSel());
	pCmd.AddParameter(m_cmbRcpTimeEnd.GetCurSel()); 
	//pCmd.AddParameter(m_chkUseEventBoard.GetCheck()); //m_chkUseEventBoard 옵션 > 스마트Q > 사용(체크)
	
	pCmd.AddParameter(m_ui.strID); 	
		

	return pCmd.Execute();
}

void COptionDlgSmartQ::OnEnChangeSendSmartqMentEdit()
{
	if(m_edtSmartQMent.GetWindowTextLength() <= 90)
	{
		m_stcLength.SetWindowText("SMS전송(건당13원)");
	} 
	else
	{
		m_stcLength.SetWindowText("LMS전송(건당30원)");
	}
}
