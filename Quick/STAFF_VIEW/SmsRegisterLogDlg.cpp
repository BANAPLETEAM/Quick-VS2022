// SmsRegisterLogDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SmsRegisterLogDlg.h"



// CSmsRegisterLogDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSmsRegisterLogDlg, CMyDialog)

CSmsRegisterLogDlg::CSmsRegisterLogDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CSmsRegisterLogDlg::IDD, pParent)
{

}

CSmsRegisterLogDlg::~CSmsRegisterLogDlg()
{
}

void CSmsRegisterLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LOG_LIST, m_lstLogList);
}


BEGIN_MESSAGE_MAP(CSmsRegisterLogDlg, CMyDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


void CSmsRegisterLogDlg::RefreshLogList()
{
	m_lstLogList.DeleteAllItems();

	int nCol = 1;
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_smscallback_doc_log_1");
	cmd.AddParameter(m_nTelNo);
	cmd.AddParameter(m_nCompany);

	if(!rs.Execute(&cmd)) return;

	CString strTel, strEtc;
	long nUse, nState, nCorpType, nTelecomState, nTelType, nIdentityCardState, nCompany;
	CString strContactName, strContactNumber, strUpdateWName;
	COleDateTime dtLog;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		long nCol = 0;

		rs.GetFieldValue("nCompany", nCompany);
		rs.GetFieldValue("sTel", strTel);
		rs.GetFieldValue("sEtc", strEtc);
		rs.GetFieldValue("nUse", nUse);
		rs.GetFieldValue("nState", nState);
		rs.GetFieldValue("nCorpType", nCorpType);
		rs.GetFieldValue("nTelecomState", nTelecomState);
		rs.GetFieldValue("nTelType", nTelType);
		rs.GetFieldValue("nIdentityCardState", nIdentityCardState);
		rs.GetFieldValue("nTelType", nTelType);
		rs.GetFieldValue("sContactName", strContactName);
		rs.GetFieldValue("sContactNumber", strContactNumber);
		rs.GetFieldValue("dtLog", dtLog);
		rs.GetFieldValue("sUpdateWName", strUpdateWName);


		m_lstLogList.InsertItem(i,"");
		m_lstLogList.SetItemText(i, 1, m_ci.GetBranchName(nCompany));		
		m_lstLogList.SetItemText(i, 2, nTelType == 0 ? m_ci.GetPhone(nCompany) : m_ci.GetPhone(nCompany,TRUE));
		m_lstLogList.SetItemText(i, 3, LF->GetDashPhoneNumber(strTel));
		m_lstLogList.SetItemText(i, 4, strEtc);
		m_lstLogList.SetItemText(i, 5, LF->GetSMSTelUse(nUse));
		m_lstLogList.SetItemText(i, 6, LF->GetSMSFileStateType(nState));
		m_lstLogList.SetItemText(i, 7, LF->GetSMSTelCorp(nCorpType));
		m_lstLogList.SetItemText(i, 8, LF->GetSMSFileStateType(nTelecomState, nTelType));
		m_lstLogList.SetItemText(i, 9, LF->GetSMSFileStateType(nIdentityCardState, nTelType));
		m_lstLogList.SetItemText(i, 10, strContactName);
		m_lstLogList.SetItemText(i, 11, strContactNumber);
		m_lstLogList.SetItemText(i, 12, dtLog.Format("%Y-%m-%d %H:%M"));
		m_lstLogList.SetItemText(i, 13, strUpdateWName);

		rs.MoveNext();
	}

	m_lstLogList.Populate();
}

BOOL CSmsRegisterLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_lstLogList.InsertColumn(0, "순번",		LVCFMT_CENTER, 40);
	m_lstLogList.InsertColumn(1, "지사명",	LVCFMT_LEFT, 90);
	m_lstLogList.InsertColumn(2, "대표/상황실", LVCFMT_LEFT, 90);
	m_lstLogList.InsertColumn(3, "발신번호", LVCFMT_LEFT, 98);
	m_lstLogList.InsertColumn(4, "내용",		LVCFMT_LEFT, 65);
	m_lstLogList.InsertColumn(5, "번호사용",		LVCFMT_CENTER, 50);
	m_lstLogList.InsertColumn(6, "진행상태",		LVCFMT_CENTER, 70);
	m_lstLogList.InsertColumn(7, "사업자/개인",	LVCFMT_LEFT, 65);
	m_lstLogList.InsertColumn(8, "통신시설상태",	LVCFMT_CENTER, 70);
	m_lstLogList.InsertColumn(9, "신분증상태",	LVCFMT_CENTER, 70);
	m_lstLogList.InsertColumn(10, "담당자",	LVCFMT_LEFT, 90);
	m_lstLogList.InsertColumn(11, "담당자전화번호",	LVCFMT_LEFT, 110);
	m_lstLogList.InsertColumn(12, "수정일",	LVCFMT_LEFT, 110);
	m_lstLogList.InsertColumn(13, "작업자",	LVCFMT_LEFT, 80);

	m_lstLogList.SetOrderIndexCol(0);

	//m_lstLogList.Populate();

	RefreshLogList();



	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CSmsRegisterLogDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(m_lstLogList.GetSafeHwnd())
	{
		CRect rcForm, rcList;
		GetClientRect(rcForm);
		m_lstLogList.GetWindowRect(rcList);
		ScreenToClient(rcList);

		rcList.right = rcForm.right - 3;
		rcList.bottom = rcForm.bottom - 3;
		m_lstLogList.MoveWindow(rcList);
	}
}
