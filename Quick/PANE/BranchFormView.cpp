// BranchDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "BranchFormView.h"
#include "BranchNameDlg.h"

#include "MyReportPaintManager.h"

// CBranchFormView 대화 상자입니다.

IMPLEMENT_DYNCREATE(CBranchFormView, CMyFormView)
CBranchFormView::CBranchFormView()
: CMyFormView(CBranchFormView::IDD)
{
}

CBranchFormView::~CBranchFormView()
{
}

void CBranchFormView::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_TREE_LIST_CTRL, m_ctrlTreeList);
	DDX_Control(pDX, IDC_EDIT_BTN, m_EditBtn);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_RefreshBtn);
	DDX_Control(pDX, IDC_SHARE_CHANEL_BTN, m_ShareChanelBtn);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_SearchEdit);
	DDX_Control(pDX, IDC_STATIC1, m_stc1);
	DDX_Control(pDX, IDC_STATIC2, m_stc2);
	DDX_Control(pDX, IDC_STATIC3, m_stc3);
	DDX_Control(pDX, IDC_STATIC91, m_stc90);
}


BEGIN_MESSAGE_MAP(CBranchFormView, CMyFormView)
	ON_BN_CLICKED(IDC_EDIT_BTN, OnBnClickedEditBtn)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_LIST_CTRL, OnNMDblclkList1)
	ON_WM_SIZE()
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeSearchEdit)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CBranchFormView 메시지 처리기입니다.

void CBranchFormView::OnInitialUpdate()
{
	if(m_bInitialUpdateCalled) return;

	CMyFormView::OnInitialUpdate();

	SetResize(IDC_TREE_LIST_CTRL, sizingRightBottom);

	ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP);
	m_ctrlTreeList.GetReportHeader()->AllowColumnResize(TRUE);
	m_ctrlTreeList.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_ctrlTreeList.GetReportHeader()->AllowColumnSort(TRUE);
	m_ctrlTreeList.GetReportHeader()->AllowColumnRemove(FALSE);
	m_ctrlTreeList.SetPaintManager(new CMyReportPaintManager());
	m_ctrlTreeList.GetPaintManager()->m_strNoItems = "표시할 정보가 없거나, 조건에 해당하는 자료가 존재하지 않음";
	m_ctrlTreeList.SetGridStyle(TRUE, xtpGridSolid);
	m_ctrlTreeList.SetGridColor(RGB(212, 208, 200));
	m_ctrlTreeList.AllowEdit(FALSE);
		
	CXTPGridColumn* pCol0 = m_ctrlTreeList.AddColumn(new CXTPGridColumn(0, _T("회사명"), 140, TRUE));
	CXTPGridColumn* pCol1 = m_ctrlTreeList.AddColumn(new CXTPGridColumn(1, _T("지사명"), 85, TRUE));
	CXTPGridColumn* pCol2 = m_ctrlTreeList.AddColumn(new CXTPGridColumn(2, _T("상황실"), 85, TRUE));
	CXTPGridColumn* pCol3 = m_ctrlTreeList.AddColumn(new CXTPGridColumn(3, _T("대표번호"), 85, TRUE));
	CXTPGridColumn* pCol4 = m_ctrlTreeList.AddColumn(new CXTPGridColumn(4, _T("상황실SMS"), 85, TRUE));
	CXTPGridColumn* pCol5 = m_ctrlTreeList.AddColumn(new CXTPGridColumn(5, _T("지역"), 40, TRUE));
	CXTPGridColumn* pCol6 = m_ctrlTreeList.AddColumn(new CXTPGridColumn(6, _T("오더심볼"), 70, TRUE));

	pCol0->SetTreeColumn(1);	

	pCol0->SetAlignment(DT_LEFT);
	pCol1->SetAlignment(DT_LEFT);
	pCol2->SetAlignment(DT_LEFT);
	pCol3->SetAlignment(DT_LEFT);
	pCol4->SetAlignment(DT_LEFT);
	pCol5->SetAlignment(DT_LEFT);

	m_ctrlTreeList.Populate();

	RefreshList();
}

bool sort_share_company(SHARE_COMPANY_INFO* elem1, SHARE_COMPANY_INFO* elem2)
{ 
	bool bShareLevel = elem1->nShareLevel < elem2->nShareLevel;
	bool bShareCode1 = elem1->nShareCode1 < elem2->nShareCode1;
	bool bRcpIntMode1 = elem1->bRcpIntMode1 > elem2->bRcpIntMode1;
	bool bCompany = elem1->nCompany < elem2->nCompany;

	if(elem1->nShareLevel == elem2->nShareLevel)
	{
		if(elem1->nShareCode1 == elem2->nShareCode1)
		{
			if(m_ci.m_nCompanyCode == elem1->nCompany)
				return true;
			else if(m_ci.m_nCompanyCode == elem2->nCompany)
				return false;
			else
			{
				if(elem1->bRcpIntMode1 == elem2->bRcpIntMode1)
				{
					return bCompany;
				}
				else 
					return bRcpIntMode1;
			}
		}
		else
			return bShareCode1;
	}
	else
		return bShareLevel;
}

void CBranchFormView::RefreshList()
{
	long nCnt = 0;
	CMkRecordset pRs(m_pMkDb); 
	CMkCommand pCmd(m_pMkDb, "select_share_company_to_see_2011_5");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	if(!pRs.Execute(&pCmd)) return;

	m_mapShareCompany.clear();

	for(UINT nItem = 0; nItem < pRs.GetRecordCount(); nItem++)
	{		
		SHARE_COMPANY_INFO *info = new SHARE_COMPANY_INFO;

		long nShareCode2, nShareCode3, nShareCode4, nShareCode5;
		pRs.GetFieldValue("nID", info->nCompany);
		pRs.GetFieldValue("sName", info->strName);
		pRs.GetFieldValue("sBranchName", info->strBranchName);
		pRs.GetFieldValue("sOfficePhone", info->strOfficePhone);
		pRs.GetFieldValue("sCity", info->strCity);
		pRs.GetFieldValue("sTel", info->strTel);
		pRs.GetFieldValue("sClientSymbol", info->strClientSymbol);
		pRs.GetFieldValue("sCity", info->strCity);
		pRs.GetFieldValue("nShareCode1", info->nShareCode1);
		pRs.GetFieldValue("bCorporationTelHidden", info->bCorporationTelHidden);
		pRs.GetFieldValue("bRcpIntMode1", info->bRcpIntMode1);
		pRs.GetFieldValue("nShareCode2", nShareCode2);
		pRs.GetFieldValue("nShareCode3", nShareCode3);
		pRs.GetFieldValue("nShareCode4", nShareCode4);
		pRs.GetFieldValue("nShareCode5", nShareCode5);
		pRs.GetFieldValue("sAuthPhone1", info->strAuthPhone1);
		pRs.GetFieldValue("sAuthPhone2", info->strAuthPhone1);
		pRs.GetFieldValue("sSmsOfficePhone", info->strSMSOfficePhone);
		info->strTel = ::GetDashPhoneNumber(info->strTel);
		info->strOfficePhone = ::GetDashPhoneNumber(info->strOfficePhone);

		info->nShareLevel = ::GetShareLevel(info->nShareCode1, nShareCode2, nShareCode3, nShareCode4, nShareCode5);

		m_mapShareCompany.insert(SHARED_COMPANY_MAP::value_type(info->nCompany, info));
		pRs.MoveNext();
	}

	if(m_mapShareCompany.size() == 0)
		return;

	m_ctrlTreeList.DeleteAllItems();

	CBranchFormRecord * pSMainRecord = NULL;
	long nPreShareCode1 = -1, nShareCode1 = -1;

	typedef vector<SHARE_COMPANY_INFO*> vecShare;
	vecShare vec;

	for(SHARED_COMPANY_MAP::iterator it = m_mapShareCompany.begin(); it != m_mapShareCompany.end(); it++)
	{
		vec.push_back(it->second);
	}

	std::sort(vec.begin(), vec.end(), sort_share_company);
	long nVecItem = 0;

	for(vecShare::iterator it = vec.begin(); it != vec.end(); it++)
	{
		SHARE_COMPANY_INFO *info = vec.at(nVecItem++);

		nShareCode1 = info->nShareCode1;

		if(nPreShareCode1 != nShareCode1)
		{
			pSMainRecord = (CBranchFormRecord*)m_ctrlTreeList.AddRecord(new CBranchFormRecord(info, TRUE));		
			pSMainRecord->SetExpanded(TRUE);
		}
		else
		{
			CXTPGridRecord * pRecord = 
				pSMainRecord->GetChilds()->Add(new CBranchFormRecord(info, FALSE));

			//pSMainRecord->AddSearchData(info);
			pRecord->SetExpanded(TRUE);
		}

		nPreShareCode1 = nShareCode1;
	}

	m_ctrlTreeList.Populate();

	/*

	m_ctrlTreeList.DeleteAllItems();

	long T1 = 0, T2 = 0, T3 = 0, T4 = 0, T5 = 0;
	char buffer[20];


	long nPreShareCode1 = -1;
	long nMainItem = 0;
	CXTPGridRecord * pSMainRecord = NULL;

	//해당 branch수 만큼 page를 추가한다.
	for(UINT nItem = 0; nItem < pRs.GetRecordCount(); nItem++)
	{
		CString strName, strBranchName, strPhone;
		int nCompanyCode;
		CString strShareStartTime, strRcpIntMode;
		CString strClientIntMode, sCity;
		CString strOfficePhone;
		CString strClientSymbol;
		long nShareCode1;
		BOOL bCorporationTelHidden;

		pRs.GetFieldValue("nID", nCompanyCode);
		pRs.GetFieldValue("nShareCode1", nShareCode1);
		pRs.GetFieldValue("sName", strName);
		pRs.GetFieldValue("sBranchName", strBranchName);
		pRs.GetFieldValue("sOfficePhone", strOfficePhone);
		pRs.GetFieldValue("sTel", strPhone);
		pRs.GetFieldValue("sCity", sCity);
		pRs.GetFieldValue("sClientSymbol", strClientSymbol);
		pRs.GetFieldValue("bCorporationTelHidden", bCorporationTelHidden);

		if(m_ci.m_nShareCode1 != nShareCode1)
		{ 
			if(strPhone.GetLength() > 6 && bCorporationTelHidden)
				strPhone = strPhone.Mid(0, strPhone.GetLength() - 4) + "****";
		}

		if(nPreShareCode1 != nShareCode1)
		{
			pSMainRecord = m_ctrlTreeList.AddRecord(new CBranchFormRecord(nCompanyCode, CString(ltoa(++nMainItem, buffer, 10)) + "." + strName,
				strBranchName, GetDashPhoneNumber(strOfficePhone), GetDashPhoneNumber(strPhone), sCity, strClientSymbol, TRUE));

			pSMainRecord->SetExpanded(TRUE);
		}
		else
		{
			CXTPGridRecord * pRecord = 
				pSMainRecord->GetChilds()->Add(new CBranchFormRecord(nCompanyCode, CString(ltoa(++nMainItem, buffer, 10)) + "." + strName,
				strBranchName, GetDashPhoneNumber(strOfficePhone), GetDashPhoneNumber(strPhone), sCity, strClientSymbol, FALSE));
				

			pRecord->SetExpanded(TRUE);
		}

		nPreShareCode1 = nShareCode1;

		pRs.MoveNext();
	}

	m_ctrlTreeList.Populate();

	pRs.Close();
	*/
}

void CBranchFormView::OnBnClickedEditBtn()
{
	if(!POWER_CHECK(1151, "기본정보 수정", TRUE))
		return;

	CXTPGridSelectedRows *pRows = m_ctrlTreeList.GetSelectedRows();

	if(pRows == NULL || pRows->GetCount() == 0) {
		MessageBox("수정할 지사를 선택하시기 바랍니다.", "지사선택", MB_ICONINFORMATION);
		return;
	}

	CBranchFormRecord * pRecord = (CBranchFormRecord*)pRows->GetAt(0)->GetRecord();

	SHARE_COMPANY_INFO *pInfo = pRecord->m_info;

	if(!m_ci.IsChildCompany(pInfo->nCompany))
	{
		MessageBox("공유 회원사의 정보는 수정하실 수 없습니다.", "수정불가", MB_ICONINFORMATION);
		return;
	}

	BOOL bEditCompany = FALSE, bDlgOK = FALSE;
	SHARED_COMPANY_MAP::iterator it = m_mapShareCompany.find(pInfo->nShareCode1);
	// 아래 연락처들은 시스에서 검색시 조회되지 않고 있어서 불필요할것 같아 제외 - by Charko
// 	if(it != m_mapShareCompany.end())
// 	{
// 		if(it->second->strAuthPhone1.GetLength() == 13 && (it->second->strAuthPhone1.Find("010-2481-7733") == 0 || it->second->strAuthPhone1.Find("010-2552-9986") == 0))
// 			bEditCompany = TRUE;
// 		else if(it->second->strAuthPhone2.GetLength() == 13 && it->second->strAuthPhone2.Find("010-2481-7733") == 0)
// 			bEditCompany = TRUE;
// 	}
// 
// 	bEditCompany = TRUE;

	CString strBranchName, strOfficePhone, strClientSymbol, strCompanyName, strCompanyNum, strClientDisplayName, strClientDisplayPhone;
	CXTPGridColumn *pColumn = NULL;

	CBranchNameDlg dlg;
	dlg.m_nCompanyCode = pRecord->m_nCompany;

	if(dlg.DoModal() == IDOK)
	{
		strBranchName = dlg.m_strBranchName;
		strOfficePhone = dlg.m_strOfficePhone;
		strClientSymbol = dlg.m_strClientSymbol;
		strClientDisplayName = dlg.m_strClientDisplayName;
		strClientDisplayPhone = dlg.m_strClientDisplayPhone;
		bDlgOK = TRUE;
	}
/*	}*/
	
	if(bDlgOK)
	{
		CMkCommand pCmd(m_pMkDb, "update_branch_info4");
		pCmd.AddParameter(strBranchName);
		pCmd.AddParameter(strOfficePhone);
		pCmd.AddParameter(strClientSymbol);
		pCmd.AddParameter(strClientDisplayName);
		pCmd.AddParameter(strClientDisplayPhone);
		pCmd.AddParameter(""); //fax사용안함
		pCmd.AddParameter(pInfo->nCompany);

		if(!pCmd.Execute()) return;

		for(int i = 0; i < m_ba.GetCount(); i++) {
			CBranchInfo *pBi = m_ba.GetAt(i);
			if(pBi->nCompanyCode == pInfo->nCompany)
			{
				pBi->strBranchName = strBranchName;
				if(bEditCompany)
				{
					pBi->strName = strCompanyName;
					pBi->strPhone = strCompanyNum;
				}
				break;
			}
		}

		MessageBox("수정되었습니다.\n지사명은 프로그램 재시작시 적용됩니다.", "확인", MB_ICONINFORMATION);
		RefreshList();
	}
}


void CBranchFormView::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CBranchFormView::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnBnClickedEditBtn();
	*pResult = 0;
}
void CBranchFormView::OnSize(UINT nType, int cx, int cy)
{
	CMyFormView::OnSize(nType, cx, cy);


}

void CBranchFormView::OnEnChangeSearchEdit()
{

	CString strSearchWord = "";
	m_SearchEdit.GetWindowText(strSearchWord);

	CXTPGridRecords *pRecords = m_ctrlTreeList.GetRecords();
	long nCount = pRecords->GetCount();

	for(int i=0; i<nCount; i++)
	{
		CBranchFormRecord* pRecord = (CBranchFormRecord*)pRecords->GetAt(i);

		BOOL bFind = FALSE;

		if(pRecord->HasChildren())
		{
			CXTPGridRecords *pChilsRecords = pRecord->GetChilds();

			for(int k=0; k<pChilsRecords->GetCount(); k++)
			{
				CBranchFormRecord *pChildRecord = (CBranchFormRecord*)pChilsRecords->GetAt(k);

				if(pChildRecord->m_info->strName.Find(strSearchWord) >= 0 ||
					pChildRecord->m_info->strBranchName.Find(strSearchWord) >= 0 ||
					pChildRecord->m_info->strTel.Find(strSearchWord) >= 0 ||
					pChildRecord->m_info->strOfficePhone.Find(strSearchWord) >= 0)
				{
					pChildRecord->SetVisible(TRUE);
					bFind = TRUE;
				}
				else 
					pChildRecord->SetVisible(FALSE);
			}
		}

		if(bFind == FALSE)
		{
			if(pRecord->m_info->strName.Find(strSearchWord) >= 0 ||
				pRecord->m_info->strBranchName.Find(strSearchWord) >= 0 ||
				pRecord->m_info->strTel.Find(strSearchWord) >= 0 ||
				pRecord->m_info->strOfficePhone.Find(strSearchWord) >= 0)
			{
				pRecord->SetVisible(TRUE);
			}
			else 
				pRecord->SetVisible(FALSE);
		}
		else
			pRecord->SetVisible(TRUE);
	}

	m_ctrlTreeList.Populate();
	m_ctrlTreeList.ExpandAll();

	/*
	
	CString strText;
	m_SearchEdit.GetWindowText(strText);
	strText.Replace("-", "");

	if(strText.GetLength() == 0)
		return;

	CTreeListItem *pCurItem = m_ctrlTreeList.GetFirstVisibleItem();
	while(pCurItem)
	{
		for(int k = 0; k < 4; k++)
		{
			CString strItem = m_ctrlTreeList.GetItemText(pCurItem, k);
			strItem.Replace("-", "");
			if(strItem.Find(strText) >= 0)
			{
				m_ctrlTreeList.EnsureVisible(pCurItem, 0);
				m_ctrlTreeList.SelectItem(pCurItem, 0);
				return;
			}
		}

		CString strItem = m_ctrlTreeList.GetItemText(pCurItem, 13);
		if(strItem.Find(strText) >= 0)
		{
			m_ctrlTreeList.EnsureVisible(pCurItem, 0);
			m_ctrlTreeList.SelectItem(pCurItem, 0);
			return;
		}		


		pCurItem = m_ctrlTreeList.GetNextItem(pCurItem, TVGN_NEXTVISIBLE);
	}
	*/
}

int CBranchFormView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMyFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS);

	return 0;
}
