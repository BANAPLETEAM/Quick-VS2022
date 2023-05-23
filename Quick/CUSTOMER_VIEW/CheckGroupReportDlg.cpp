// CheckGroupReportDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "CheckGroupReportDlg.h"
#include "HelpGroupReportDlg.h"


// CCheckGroupReportDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCheckGroupReportDlg, CMyDialog)
CCheckGroupReportDlg::CCheckGroupReportDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCheckGroupReportDlg::IDD, pParent)
{
	m_strNeedReReportID = "";
}

CCheckGroupReportDlg::~CCheckGroupReportDlg()
{
}

void CCheckGroupReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_lstReport);
	DDX_Control(pDX, IDC_STATIC1, m_stc1);
	DDX_Control(pDX, IDC_STATIC2, m_stc2);
	DDX_Control(pDX, IDC_HELP_BTN, m_btnHelp);
}


BEGIN_MESSAGE_MAP(CCheckGroupReportDlg, CMyDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_HELP_BTN, OnBnClickedHelpBtn)
	ON_BN_CLICKED(IDC_MOVE_BTN, OnBnClickedMoveBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
END_MESSAGE_MAP()




BOOL CCheckGroupReportDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	//*8명의 해당 그룹맴버가 로지메인/로지메인 그룹으로 이동하며
	//DATA날짜이후 재 정산이 필요한 정산내역은 아래와 같습니다(상태에 부분입금 혹은 입금완료)

	char buffer[20];
	CString str1 = "*" + (CString)itoa(m_nMemberCount, buffer, 10) + "명의 해당 그룹맴버가"
		+ m_cg.GetGroupData(m_nDstGNo)->strGroupName + "/" + m_cg.GetGroupData(m_nDstGNo)->strDept + " 그룹으로 이동하며";
	CString str2 = "";

	if(m_dtDate.GetYear() == 2000)
		str2 = "전체날짜이후 재 정산이 필요한 정산내역은 아래와 같습니다(상태에 부분입금 혹은 입금완료)";
	else
		str2 = m_dtDate.Format("%m-%d") + "날짜이후 재 정산이 필요한 정산내역은 아래와 같습니다(상태에 부분입금 혹은 입금완료)";

	m_stc1.SetWindowText(str1);
	m_stc2.SetWindowText(str2);
		
	m_lstReport.InsertColumn(0, "그룹명", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(1, "부서명", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(2, "담당자", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(3, "정산기간", LVCFMT_CENTER, 90);
	m_lstReport.InsertColumn(4, "수금액", LVCFMT_CENTER, 60);
	m_lstReport.InsertColumn(5, "미수금", LVCFMT_CENTER, 60);
	m_lstReport.InsertColumn(6, "상태", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(7, "적요", LVCFMT_LEFT, 200);

	m_lstReport.Populate();
	RefreshList();

	m_btnHelp.LoadBitmaps(IDB_HELP_BTN1, IDB_HELP_BTN2);
	m_btnHelp.SizeToContent(); // Button사이즈에 맞게끔 Bitmap사이즈를 조정합니다

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CCheckGroupReportDlg::RefreshList()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_group_report_check");

	char buffer[10];

	pCmd.AddParameter(m_strGNo);
	pCmd.AddParameter(m_nDstGNo);
	pCmd.AddParameter(m_dtDate);

	if(!pRs.Execute(&pCmd))
		return;

	long nID, nGNo, nBillCollection, nUnCollection, nReportState;
	CString strGroupName, strDept, strName;
	COleDateTime dtReportStart, dtReportEnd;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("nGNo", nGNo);
		pRs.GetFieldValue("nBillCollection", nBillCollection);
		pRs.GetFieldValue("nUnCollection", nUnCollection);
		pRs.GetFieldValue("nReportState", nReportState);
		pRs.GetFieldValue("sGroupName", strGroupName);
		pRs.GetFieldValue("sDept", strDept);
		pRs.GetFieldValue("sName", strName);
		pRs.GetFieldValue("dtReportStart", dtReportStart);
		pRs.GetFieldValue("dtReportEnd", dtReportEnd);

		m_lstReport.InsertItem(i, strGroupName);
		m_lstReport.SetItemText(i, 1, strDept);
		m_lstReport.SetItemText(i, 2, strName);
		m_lstReport.SetItemText(i, 3, dtReportStart.Format("%m-%d") + " ~ " + dtReportEnd.Format("%m-%d"));
		m_lstReport.SetItemText(i, 4, LF->RemoveZero(LF->GetMyNumberFormat(nBillCollection)));
		m_lstReport.SetItemText(i, 5, LF->RemoveZero(LF->GetMyNumberFormat(nUnCollection)));
		m_lstReport.SetItemText(i, 6, GetState(nReportState));
		m_lstReport.SetItemText(i, 7, GetStateEtc(nReportState));
		m_lstReport.SetItemLong(i, nReportState);

		if(nReportState == 0)
			m_strNeedReReportID += (CString)itoa(nID, buffer, 10) + ";";
		
		pRs.MoveNext();
	}	 

	m_lstReport.Populate();
}

CString CCheckGroupReportDlg::GetState(long nReportState)
{
	if(nReportState == 0)
		return "정산완료";
	if(nReportState == 10)
		return "부분입금";
	if(nReportState == 20)
		return "입금완료";

	return "";
}

CString CCheckGroupReportDlg::GetStateEtc(long nReportState)
{
	if(nReportState == 0)
		return "자동재정산";
	if(nReportState == 10)
		return "부분입금으로 인한 자동재장산 불가";
	if(nReportState == 20)
		return "입금완료로 인한 자동재장산 불가";

	return "";
}

void CCheckGroupReportDlg::OnBnClickedButton1()
{
	CMyExcel::ToExcel(&m_lstReport);
}

void CCheckGroupReportDlg::OnBnClickedHelpBtn()
{
	CHelpGroupReportDlg dlg;
	dlg.DoModal();
}

void CCheckGroupReportDlg::OnBnClickedMoveBtn()
{
	OnOK();	
}

void CCheckGroupReportDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}
