// RiderDepositEditHistoryDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderDepositEditHistoryDlg.h"

#include "MyReportPaintManager.h"


// CRiderDepositEditHistoryDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRiderDepositEditHistoryDlg, CMyDialog)
CRiderDepositEditHistoryDlg::CRiderDepositEditHistoryDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRiderDepositEditHistoryDlg::IDD, pParent)
{
}

CRiderDepositEditHistoryDlg::~CRiderDepositEditHistoryDlg()
{
}

void CRiderDepositEditHistoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_Report);
}


BEGIN_MESSAGE_MAP(CRiderDepositEditHistoryDlg, CMyDialog)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CRiderDepositEditHistoryDlg 메시지 처리기입니다.

void CRiderDepositEditHistoryDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}

void CRiderDepositEditHistoryDlg::OnBnClickedOk()
{
	RefreshList();	
}

BOOL CRiderDepositEditHistoryDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CXTPGridColumn *pCol10 = m_Report.AddColumn(new CXTPGridColumn(0, "순번", 40, FALSE));
	CXTPGridColumn *pCol11 = m_Report.AddColumn(new CXTPGridColumn(1, "접수자", 90, FALSE));
	CXTPGridColumn *pCol12 = m_Report.AddColumn(new CXTPGridColumn(2, "기사명", 90, FALSE));
	CXTPGridColumn *pCol13 = m_Report.AddColumn(new CXTPGridColumn(3, "수정시간", 90, FALSE));
	CXTPGridColumn *pCol14 = m_Report.AddColumn(new CXTPGridColumn(4, "변경내역", 100, FALSE));
	CXTPGridColumn *pCol15 = m_Report.AddColumn(new CXTPGridColumn(5, "변경전", 130, FALSE));
	CXTPGridColumn *pCol16 = m_Report.AddColumn(new CXTPGridColumn(6, "변경후", 130, FALSE));

	pCol10->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol10->SetTreeColumn(1);
	pCol10->SetAlignment(DT_RIGHT);	
	pCol11->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol11->SetAlignment(DT_RIGHT);
	pCol12->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol12->SetAlignment(DT_CENTER);
	pCol13->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol13->SetAlignment(DT_RIGHT);
	pCol14->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol14->SetAlignment(DT_CENTER);
	pCol15->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol15->SetAlignment(DT_CENTER);
	pCol16->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol16->SetAlignment(DT_CENTER);

	m_Report.GetReportHeader()->AllowColumnRemove(FALSE);
	m_Report.GetReportHeader()->AllowColumnResize(TRUE);
	m_Report.GetReportHeader()->AllowColumnSort(FALSE);
	m_Report.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_Report.SetPaintManager(new CMyReportPaintManager());
	m_Report.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
	m_Report.AllowEdit(FALSE);
	m_Report.FocusSubItems(TRUE);
	m_Report.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_Report.SetGridColor(RGB(180, 180, 200));
	m_Report.SetTreeIndent(30);

	m_Report.Populate();

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRiderDepositEditHistoryDlg::RefreshList()
{
	m_Report.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_deposit_edit_history_1");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRiderCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRNo);

	if(!pRs.Execute(&pCmd)) return;

	//	2007-01-06 18:13:07.583		10	0	10	15990707	15990808	역삼동	삼성동	[취소5:한잔 더]	9000	1000	
	COleDateTime dtLog;

	if(pRs.GetRecordCount() == 1)
		return;

	for(int i=0 ; i<pRs.GetRecordCount(); i++)
	{
		DEPOSIT_EDIT_HISTORY EditHistory;

		pRs.GetFieldValue("dtGenerate", EditHistory.dtEdit);
		pRs.GetFieldValue("nRiderCompany", EditHistory.nRiderCompany);
		pRs.GetFieldValue("nRNo", EditHistory.nRNo);
		pRs.GetFieldValue("sRName", EditHistory.sRName);
		pRs.GetFieldValue("nDepositType", EditHistory.nDepositType);

		pRs.GetFieldValue("nDepositAllocateType", EditHistory.nDepositAllocateType);
		pRs.GetFieldValue("sMyCallRateType", EditHistory.sMyCallRateType);
		pRs.GetFieldValue("sOtherCallRateType", EditHistory.sOtherCallRateType);
		pRs.GetFieldValue("nFixedDeposit", EditHistory.nFixedDeposit);
		pRs.GetFieldValue("nPayMentDay", EditHistory.nPayMentDay);
		pRs.GetFieldValue("nWNo", EditHistory.nWNo);
		pRs.GetFieldValue("sWName", EditHistory.sWName);

		//근무유형, 입금방식, 지입금, 자사콜, 타사콜, 납일일

		
		int nItem = 0;

		EditHistory.item[nItem++] = GetDepositType(EditHistory.nDepositType);
		EditHistory.item[nItem++] = EditHistory.nDepositAllocateType == 0 ? "선입금" : "후입금";
		EditHistory.item[nItem++] = LF->GetMyNumberFormat(EditHistory.nFixedDeposit);
		EditHistory.item[nItem++] = EditHistory.sMyCallRateType;
		EditHistory.item[nItem++] = EditHistory.sOtherCallRateType;
		EditHistory.item[nItem++] = GetPayMentDay(EditHistory.nDepositType, EditHistory.nPayMentDay);

		m_EditHistoryMap[i] = EditHistory;

		pRs.MoveNext();
	}

	CompareMap();
}

void CRiderDepositEditHistoryDlg::CompareMap()
{
	CString sTitle[] = {"근무유형", "입금방식", "지입금", "자사콜", "타사콜", "납일일"};

	map<long, DEPOSIT_EDIT_HISTORY>::iterator pos;

	CXTPGridRecord *pMainRecord = NULL;
	CXTPGridRecord *pSubMainRecord = NULL;

	int nItem = 0;

	for(pos = m_EditHistoryMap.begin(); pos != m_EditHistoryMap.end(); pos++)
	{
		bool bTreeHead = TRUE;

		map<long, DEPOSIT_EDIT_HISTORY>::iterator pos1 = pos;
		pos1++;

		if(pos1 == m_EditHistoryMap.end())
			break;

		BOOL bDifferent = FALSE;


		for(int i=0; i<MAX_STRING_COUNT; i++)
		{
			if(pos->second.item[i] != pos1->second.item[i])
			{
				bDifferent = TRUE;
				break;
			}			
		}	

		if(bDifferent == FALSE)
			continue;

		for(int i=0; i<MAX_STRING_COUNT; i++)
		{
			if(i == 0)
			{
				pMainRecord = m_Report.AddRecord(new CRiderDepositRecord(nItem++, pos->second.dtEdit, pos->second.nRNo, pos->second.sRName,
					pos->second.nWNo, pos->second.sWName, sTitle[i], pos->second.item[i], pos1->second.item[i], TRUE));
			}
			else 
			{
				pMainRecord->GetChilds()->Add(new CRiderDepositRecord(0, pos->second.dtEdit, pos->second.nRNo, pos->second.sWName,
				pos->second.nWNo, pos->second.sWName, sTitle[i], pos->second.item[i], pos1->second.item[i], FALSE));

				pMainRecord->SetExpanded(TRUE);
			}
		}	

		m_Report.AddRecord(new CRiderDepositRecord(""));
	}

	m_Report.Populate();
}

CString CRiderDepositEditHistoryDlg::GetDepositType(long nDepositType)
{
	if(nDepositType == 20)
		return "월비";
	if(nDepositType == 30)
		return "주비";
	if(nDepositType == 40)
		return "일비";
	if(nDepositType == 50)
		return "프로제";

	return "알수없음";
}

CString CRiderDepositEditHistoryDlg::GetPayMentDay(long nDepositType, long nPayMentDay)
{
	char buffer[10];
	
    if(nDepositType == 20) // 월비
		return (CString)itoa(nPayMentDay, buffer, 10) + "일";

	if(nDepositType == 30) //주비
	{
		char *dayofweek[] = {"일", "월", "화", "수", "목", "금", "토", "평균"};
		return dayofweek[nPayMentDay];
	}

	return "";

}
