// AfterReportDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "AfterReportDlg.h"


// CAfterReportDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAfterReportDlg, CMyDialog)
CAfterReportDlg::CAfterReportDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAfterReportDlg::IDD, pParent)
{
}

CAfterReportDlg::~CAfterReportDlg()
{
}

void CAfterReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_Report);
}


BEGIN_MESSAGE_MAP(CAfterReportDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(ID_REFRESH_BTN, OnBnClickedRefreshBtn)
END_MESSAGE_MAP()


// CAfterReportDlg 메시지 처리기입니다.

void CAfterReportDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}

void CAfterReportDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}

BOOL CAfterReportDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	CenterWindow();

	this->SetWindowText(m_cg.GetGroupData(m_nGNo)->strGroupName + "/" + m_cg.GetGroupData(m_nGNo)->strDept);

	//m_Report.InsertColumn(0, "일자", LVCFMT_LEFT, 120);

	CXTPGridColumn* pCol0 = m_Report.AddColumn(new CXTPGridColumn(0, _T("그룹명"), 150));

	m_Report.InsertColumn(1, "일자", LVCFMT_LEFT, 80);
	m_Report.InsertColumn(2, "현금", LVCFMT_LEFT, 95);
	m_Report.InsertColumn(3, "신용", LVCFMT_LEFT, 95);
	m_Report.InsertColumn(4, "송금", LVCFMT_LEFT, 95);
	m_Report.InsertColumn(5, "탁송", LVCFMT_LEFT, 95);
	m_Report.InsertColumn(6, "합계(외+송/외+송+탁)", LVCFMT_LEFT, 120);

	m_Report.GetPaintManager()->m_strNoItems = "차후 일별 사용내역이 없습니다";
	m_Report.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	m_Report.SetGridColor(RGB(255, 255, 255));

	pCol0->SetTreeColumn(1);	
	m_Report.SetTreeIndent(10);

	m_Report.Populate();
	RefreshList();



	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAfterReportDlg::RefreshList()
{
	m_Report.DeleteAllItems();

	long nRet = 0;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_after_report_by_group");
	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeReturn, sizeof(long), 0);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nGNo);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_bAll);

	if(!pRs.Execute(&pCmd)) return;

	pPar->GetValue(nRet);

	if(nRet == 10)
	{
		MessageBox("마지막 정산일이 없습니다", "확인", MB_ICONINFORMATION);
		OnOK();
	}

	CString sDate;
	long nCashCount, nCashCharge, nCreditCount, nCreditCharge, nOnlineCount, nOnlineCharge, nTransCount, nTransCharge;
	CString sFormat; 
	long nGNo = 0, nPrenGNo = 0;

	CXTPGridRecord *pTopRecord;
	CXTPGridRecord *pBottomRecord;


	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nOGNo", nGNo);

		if(nGNo != nPrenGNo)
		{
			pTopRecord = m_Report.AddRecord(new CAfterReportRecord(nGNo));
			pTopRecord->SetExpanded(TRUE);;
		}		

		pRs.GetFieldValue("sDate", sDate);
		pRs.GetFieldValue("nCashCount", nCashCount);
		pRs.GetFieldValue("nCashCharge", nCashCharge);
		pRs.GetFieldValue("nCreditCount", nCreditCount);
		pRs.GetFieldValue("nCreditCharge", nCreditCharge);
		pRs.GetFieldValue("nOnlineCount", nOnlineCount);
		pRs.GetFieldValue("nOnlineCharge", nOnlineCharge);
		pRs.GetFieldValue("nTransCount", nTransCount);
		pRs.GetFieldValue("nTransCharge", nTransCharge);

		pBottomRecord = pTopRecord->GetChilds()->Add(new CAfterReportRecord(nGNo, sDate, nCashCount, nCashCharge, nCreditCount, nCreditCharge,
								nOnlineCount, nOnlineCharge, nTransCount, nTransCharge));
		pBottomRecord->SetExpanded(TRUE);

		nPrenGNo = nGNo;

		pRs.MoveNext();
	}

	m_Report.Populate();

}
