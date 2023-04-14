// DepositJobLogDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "DepositJobLogDlg.h"



// CDepositJobLogDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDepositJobLogDlg, CMyDialog)
CDepositJobLogDlg::CDepositJobLogDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CDepositJobLogDlg::IDD, pParent)
{
	m_nScheduleID = 0 ;
	m_strDisplayName = "";
}

CDepositJobLogDlg::~CDepositJobLogDlg()
{
}

void CDepositJobLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_HELP, m_stcHelp);
	DDX_Control(pDX, IDC_LOG_LIST, m_lstLog);
}


BEGIN_MESSAGE_MAP(CDepositJobLogDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_JOB_BTN, OnBnClickedRefreshJobBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, OnBnClickedCloseBtn)
END_MESSAGE_MAP()


// CDepositJobLogDlg 메시지 처리기입니다.

BOOL CDepositJobLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow();
	m_stcHelp.SetWindowText("작업명 : " + m_strDisplayName);

	m_lstLog.InsertColumn(0, "작업시간", LVCFMT_LEFT, 150);
	m_lstLog.InsertColumn(1, "작업자", LVCFMT_LEFT, 80);
	m_lstLog.InsertColumn(2, "적용기사", LVCFMT_LEFT, 70);
	m_lstLog.InsertColumn(3, "성공여부", LVCFMT_CENTER, 60);

	m_lstLog.Populate();

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDepositJobLogDlg::OnBnClickedRefreshJobBtn()
{
	RefreshList();
}

void CDepositJobLogDlg::RefreshList()
{
	m_lstLog.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_schedule_log");

	pCmd.AddParameter(m_nScheduleID);

	if(!pRs.Execute(&pCmd)) return;

	char buffer[10];
	COleDateTime dtPlay;
	long nApplyRider;
	CString sWName;
	BOOL bSuccess;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("dtPlay", dtPlay);
		pRs.GetFieldValue("nApplyRider", nApplyRider);
		pRs.GetFieldValue("sWName", sWName);
		pRs.GetFieldValue("bSuccess", bSuccess);

		m_lstLog.InsertItem(i, dtPlay.Format(dtPlay.Format("%y-%m-%d %H:%M:%S")));
		m_lstLog.SetItemText(i, 1, sWName);
		m_lstLog.SetItemText(i, 2, (CString)itoa(nApplyRider, buffer, 10) + "명");
		m_lstLog.SetItemText(i, 3, bSuccess == TRUE ? "성공" : "실패");

		pRs.MoveNext();
	}

	m_lstLog.Populate();
}


void CDepositJobLogDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}
