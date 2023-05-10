// OtherRegionBranchDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "OtherRegionBranchDlg.h"
#include "MyReportPaintManager.h"

// COtherRegionBranchDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(COtherRegionBranchDlg, CMyDialog)

COtherRegionBranchDlg::COtherRegionBranchDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(COtherRegionBranchDlg::IDD, pParent)
{

}

COtherRegionBranchDlg::~COtherRegionBranchDlg()
{
}

void COtherRegionBranchDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST, m_lstReport);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
}


BEGIN_MESSAGE_MAP(COtherRegionBranchDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &COtherRegionBranchDlg::OnBnClickedRefreshBtn)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &COtherRegionBranchDlg::OnEnChangeSearchEdit)
END_MESSAGE_MAP()


// COtherRegionBranchDlg 메시지 처리기입니다.

BOOL COtherRegionBranchDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	CenterWindow();

	CXTPGridColumn* pCol0  = m_lstReport.AddColumn(new CXTPGridColumn(0, "지역", 60, FALSE));
	m_lstReport.AddColumn(new CXTPGridColumn(1, "도시", 50, FALSE));
	m_lstReport.AddColumn(new CXTPGridColumn(2, "회사명", 100, FALSE));
	m_lstReport.AddColumn(new CXTPGridColumn(3, "상황실", 90, FALSE));
	m_lstReport.AddColumn(new CXTPGridColumn(4, "대표번호", 90, FALSE));
	m_lstReport.AddColumn(new CXTPGridColumn(5, "대표", 60, FALSE));

	pCol0->SetTreeColumn(TRUE);

	m_lstReport.GetReportHeader()->AllowColumnResize(TRUE);
	m_lstReport.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_lstReport.GetReportHeader()->AllowColumnSort(TRUE);
	m_lstReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_lstReport.SetPaintManager(new CMyReportPaintManager());
	m_lstReport.GetPaintManager()->m_strNoItems = "표시할 정보가 없거나, 조건에 해당하는 자료가 존재하지 않음";
	m_lstReport.SetGridStyle(TRUE, xtpGridSolid);
	m_lstReport.SetGridColor(RGB(212, 208, 200));
	m_lstReport.AllowEdit(FALSE);

	m_lstReport.Populate();
	InitRegionGroup();
	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void COtherRegionBranchDlg::InitRegionGroup()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_region_group");
	pCmd.AddParameter(0);

	if(!pRs.Execute(&pCmd)) return;

	CString sCity, sCitySum;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("sCity", sCity);
		pRs.GetFieldValue("sCitySum", sCitySum);

		m_gpMap[sCity] = sCitySum;

		pRs.MoveNext();
	}
	
}

void COtherRegionBranchDlg::OnBnClickedRefreshBtn()
{
	RefreshList();	
	OnEnChangeSearchEdit();
}

void COtherRegionBranchDlg::RefreshList()
{
	m_map.clear();
	m_lstReport.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_other_region_branch");

	pCmd.AddParameter(m_ci.m_strCity);

	if(!pRs.Execute(&pCmd)) return;

	long nPreShareCode1 = 0, nShareCode1 = 0;
	CString sName, sBranchName, sOfficePhone, sTel, sCity, sOWner;

	CXTPGridRecord *pRegionTopRecord = NULL;
	CXTPGridRecord *pCityTopRecord = NULL;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("sBranchName", sBranchName);
		pRs.GetFieldValue("sName", sName);
		pRs.GetFieldValue("sOfficePhone", sOfficePhone);
		pRs.GetFieldValue("sTel", sTel);
		pRs.GetFieldValue("sCity", sCity);
		pRs.GetFieldValue("nShareCode1", nShareCode1);
		pRs.GetFieldValue("sOWner", sOWner);
 
		pRs.MoveNext();

		if(nShareCode1 != nPreShareCode1)
		{
			CString sMainCity = GetGroupRegion(sCity);

			CITY_MAP::iterator it;
			it = m_map.find(sMainCity);

			if(it == m_map.end())
			{
				m_map[sMainCity] = m_lstReport.AddRecord(new CORBRecord(sMainCity));
				it = m_map.find(sMainCity);
			}
			
			pRegionTopRecord = it->second;
			pRegionTopRecord->SetExpanded(TRUE);

			pCityTopRecord = pRegionTopRecord->GetChilds()->Add(new CORBRecord(TRUE, sCity, sName, sOfficePhone, sTel, sOWner,nShareCode1));
			pCityTopRecord->SetExpanded(TRUE);

			nPreShareCode1 = nShareCode1;
			continue;
		}

		CXTPGridRecord *pCityBottomRecord = pCityTopRecord->GetChilds()->Add(new CORBRecord(FALSE, sName, sBranchName, sOfficePhone, sTel, sCity, nShareCode1));
		((CORBRecord*)pCityTopRecord)->AddSearchData(sName, sBranchName, sOfficePhone, sTel, sCity);
		pCityBottomRecord->SetExpanded(TRUE);
	}

	m_lstReport.Populate();
}

CString COtherRegionBranchDlg::GetGroupRegion(CString sCity)
{
	GROUP_MAP::iterator it;

	for(it = m_gpMap.begin(); it != m_gpMap.end(); it++)
	{
		if(it->second.Find(sCity) >= 0)
			return it->first;
	}

	return "기타";	
}

void COtherRegionBranchDlg::OnEnChangeSearchEdit()
{
	CString sSearch;
	m_edtSearch.GetWindowText(sSearch);

	CXTPGridRecords *pTopRecords = m_lstReport.GetRecords();

	for(int i=0; i<pTopRecords->GetCount(); i++)
	{
		CXTPGridRecord *pSecondRecord = pTopRecords->GetAt(i);
		CXTPGridRecords *pSecondChildRecords = pSecondRecord->GetChilds();

		for(int j=0; j<pSecondChildRecords->GetCount(); j++)
		{
			CORBRecord *pThirdRecord = (CORBRecord*)pSecondChildRecords->GetAt(j);

			if(pThirdRecord->m_sSearchData.Find(sSearch) >= 0)
				pThirdRecord->SetVisible(TRUE);
			else
				pThirdRecord->SetVisible(FALSE);
		}
	}

	m_lstReport.Populate();
}

