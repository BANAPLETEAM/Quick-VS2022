// ChargeDongNewDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ChargeDongNewDlg.h"
#include "ChargeInsertDlg.h"
#include "ChargePaintManager.h"
#include "SearchGroupDlg.h"
#include "VarietyDlg.h"

// CChargeDongNewDlg 대화 상자입니다.
SAVE_MAP m_mapSave;

IMPLEMENT_DYNAMIC(CChargeDongNewDlg, CMyDialog)

CChargeDongNewDlg::CChargeDongNewDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CChargeDongNewDlg::IDD, pParent)
{	
	m_bSave = FALSE;
}

CChargeDongNewDlg::~CChargeDongNewDlg()
{
}

void CChargeDongNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_START_LIST, m_lstStart);
	DDX_Control(pDX, IDC_DEST_LIST, m_lstDest);
	DDX_Control(pDX, IDC_DONG_LIST, m_lstDong);
	DDX_Control(pDX, IDC_TYPE_COMBO, m_cmbType);

	DDX_Control(pDX, IDC_START_SEARCH_EDIT, m_edtStartSearch);
	DDX_Control(pDX, IDC_DEST_SEARCH_EDIT, m_edtDestSearch);

	DDX_Control(pDX, IDC_TWO_WAY_CHECK, m_chkTwoWay);
	DDX_Control(pDX, IDC_BRANCH_COMBO, m_cmbBranch);
	DDX_Control(pDX, IDC_CAR_TYPE_COMBO, m_cmbCarType);
	DDX_Control(pDX, IDC_DIS_COM_COMBO2, m_cmbDiscountCompany);
	DDX_Control(pDX, IDC_CAR_TYPE_COMBO2, m_cmbCarType2);
}


BEGIN_MESSAGE_MAP(CChargeDongNewDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON, &CChargeDongNewDlg::OnBnClickedCloseButton)
	ON_NOTIFY(NM_CLICK, IDC_START_LIST, OnReportItemClick)
	ON_NOTIFY(NM_CLICK, IDC_DEST_LIST, OnReportItemClick)
	ON_MESSAGE(WM_CHANGE_BRANCH_CODE, OnChangeBrachCode)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &CChargeDongNewDlg::OnBnClickedSaveButton)
	ON_NOTIFY(XTP_NM_GRID_SELCHANGED, IDC_DONG_LIST, OnReportItemSelChange)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_REFRESH_BUTTON, &CChargeDongNewDlg::OnBnClickedRefreshButton)
	ON_CBN_SELCHANGE(IDC_TYPE_COMBO, &CChargeDongNewDlg::OnCbnSelchangeTypeCombo)
	ON_EN_CHANGE(IDC_START_SEARCH_EDIT, &CChargeDongNewDlg::OnEnChangeSearchStartEdit)
	ON_EN_CHANGE(IDC_DEST_SEARCH_EDIT, &CChargeDongNewDlg::OnEnChangeSearchDestEdit)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_INSERT_CHARGE, OnInsertCharge)
	ON_COMMAND(ID_EXCEL, OnExcel)
	ON_CBN_SELCHANGE(IDC_CAR_TYPE_COMBO, &CChargeDongNewDlg::OnCbnSelchangeCarTypeCombo)
	ON_CBN_EDITCHANGE(IDC_DIS_COM_COMBO2, &CChargeDongNewDlg::OnCbnEditchangeDisComCombo2)
	ON_CBN_SELCHANGE(IDC_DIS_COM_COMBO2, &CChargeDongNewDlg::OnCbnSelchangeDisComCombo2)
	ON_CBN_SELCHANGE(IDC_CAR_TYPE_COMBO2, &CChargeDongNewDlg::OnCbnSelchangeCarTypeCombo2)
	ON_BN_CLICKED(IDC_SEARCH_GROUP_BTN, &CChargeDongNewDlg::OnBnClickedSearchGroupBtn)
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CChargeDongNewDlg::OnBnClickedSearchBtn)
	ON_BN_CLICKED(IDC_DISCOUNT_COMPANY_BTN, &CChargeDongNewDlg::OnBnClickedDiscountCompanyBtn)
	ON_BN_CLICKED(IDC_DISCOUNT_COMPANY_DEL_BTN, &CChargeDongNewDlg::OnBnClickedDiscountCompanyDelBtn)
	ON_CBN_SELCHANGE(IDC_BRANCH_COMBO, &CChargeDongNewDlg::OnCbnSelchangeBranchCombo)
END_MESSAGE_MAP()


// CChargeDongNewDlg 메시지 처리기입니다.

BOOL CChargeDongNewDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	for(int i = 0; i < m_ba.GetCount(); i++)
	{
		CBranchInfo *pBi = m_ba.GetAt(i);
		int nIndex = m_cmbBranch.AddString(pBi->strBranchName + "(" + pBi->strPhone + ")");
		m_cmbBranch.SetItemData(nIndex, (DWORD_PTR)pBi);
	}

	m_cmbBranch.SetCurSel(0);
	m_cmbType.SetCurSel(0);
	m_cmbCarType.SetCurSel(0);
	m_cmbCarType2.SetCurSel(0);

	m_edtStartSearch.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtStartSearch.SetUserOption(RGB(0, 0, 255), RGB(255, 255, 255), "출착지");

	m_edtDestSearch.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtDestSearch.SetUserOption(RGB(0, 0, 255), RGB(255, 255, 255), "도착지");

	m_cmbType.SetCurSel(0);

	CXTPGridColumn* pStartColumn = m_lstStart.AddColumn(new CXTPGridColumn(0, _T("출발지"), 180, FALSE));
	pStartColumn->SetTreeColumn(1);	 

	CXTPGridColumn* pDestColumn = m_lstDest.AddColumn(new CXTPGridColumn(0, _T("도착지"), 180, FALSE));
	pDestColumn->SetTreeColumn(1);	
	//pDestColumn = m_lstDest.AddColumn(new CXTPGridColumn(1, _T("요금"), 50, FALSE));
	//pDestColumn->SetEditable(TRUE);

	m_lstStart.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);	
	m_lstStart.SetTreeIndent(30);
	m_lstStart.SetGridColor(RGB(222, 222, 222));
	m_lstStart.GetPaintManager()->m_strNoItems = "";
	m_lstStart.GetReportHeader()->AllowColumnRemove(FALSE);
	m_lstStart.GetReportHeader()->AllowColumnSort(FALSE);
	m_lstStart.GetReportHeader()->AllowColumnResize(FALSE);
	m_lstStart.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_lstStart.Populate();


	m_lstDest.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);	
	m_lstDest.SetTreeIndent(30);
	m_lstDest.SetGridColor(RGB(222, 222, 222));
	m_lstDest.GetPaintManager()->m_strNoItems = "";
	m_lstDest.GetReportHeader()->AllowColumnRemove(FALSE);
	m_lstDest.GetReportHeader()->AllowColumnSort(FALSE);
	m_lstDest.GetReportHeader()->AllowColumnResize(FALSE);
	m_lstDest.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_lstDest.Populate();

	CChargePaintManager *pManager = new CChargePaintManager();

	static LOGFONT chargefont = {20,0,0,0,FW_NORMAL,0,0,0,HANGUL_CHARSET,0,0,0,0,"맑은 고딕"};

	m_lstDong.SetPaintManager(pManager);
	m_lstDong.GetReportHeader()->AllowColumnResize(TRUE); 
	m_lstDong.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_lstDong.GetReportHeader()->AllowColumnSort(FALSE);
	m_lstDong.GetReportHeader()->AllowColumnRemove(FALSE);
	m_lstDong.SetTreeIndent(30); 
	m_lstDong.SetGridColor(RGB(222, 222, 222));
	m_lstDong.GetPaintManager()->m_strNoItems = "";  
	m_lstDong.GetPaintManager()->SetTextFont(chargefont);
	m_lstDong.ShowHeader(FALSE);
	m_lstDong.SetGridStyle(TRUE, xtpGridSolid);	

	CXTPGridPaintManager *pPaint = (CXTPGridPaintManager*)m_lstDong.GetPaintManager();
	pPaint->m_clrSelectedRow.SetCustomValue(COLOR_YELLOW);
	pPaint->m_clrSelectedRowText.SetCustomValue(RGB(0, 0, 0));
	pPaint->m_clrHighlight.SetCustomValue(COLOR_YELLOW);
	pPaint->m_clrHighlightText.SetCustomValue(RGB(0, 0, 0));

	m_lstDong.Populate();

	ChargeTypeNameRefresh();

	MakeStartDestList();

	OnReportItemClick(NULL, NULL);

	//if(fc.isha)

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CChargeDongNewDlg::MakeStartDestList()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_dong_pos_for_sido_1");
	cmd.AddParameter(0);
	CMkParameter *parCity = cmd.AddParameter(typeString, typeOutput, 100, m_ci.m_strCity);

	if(!rs.Execute(&cmd))
		return FALSE;

	if(rs.GetRecordCount() == 0)
		return FALSE;

	CString strSido, strGugun, strExpandCity;
	long nID, nSido;

	parCity->GetValue(strExpandCity);

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("sSido", strSido);
		rs.GetFieldValue("nSido", nSido);
		m_lstStart.AddRecord(new CChargeReportRecord(strSido, nSido));
		m_lstDest.AddRecord(new CChargeReportRecord(strSido, nSido));

		rs.MoveNext();
	}

	CMkRecordset rs2(m_pMkDb);
	CMkCommand cmd2(m_pMkDb, "select_dong_pos_for_gugun");
	cmd2.AddParameter(0);

	if(!rs2.Execute(&cmd2))
		return FALSE; 

	for(int j=0; j<rs2.GetRecordCount(); j++)
	{ 
		rs2.GetFieldValue("sSido", strSido);
		rs2.GetFieldValue("sGugun", strGugun);
		rs2.GetFieldValue("nID", nID);

		CXTPGridRecord *pRecord = GetRecordFromSido(strSido, &m_lstStart);

		if(pRecord) 
		{
			CXTPGridRecord *pRecord1 = pRecord->GetChilds()->Add(new CChargeReportRecord(strGugun, nID, TRUE));

			if(strExpandCity == strSido)
				pRecord->SetExpanded(TRUE);
		}

		pRecord = GetRecordFromSido(strSido, &m_lstDest);

		if(pRecord)
		{
			CXTPGridRecord *pRecord1 = pRecord->GetChilds()->Add(new CChargeReportRecord(strGugun, nID, TRUE));

			if(strExpandCity == strSido)
				pRecord->SetExpanded(TRUE);
		}		

		rs2.MoveNext();
	} 

	CMkRecordset rs3(m_pMkDb);
	CMkCommand cmd3(m_pMkDb, "select_dong_pos_for_li");
	cmd3.AddParameter(0);

	if(!rs3.Execute(&cmd3))
		return FALSE; 

	CString strDong;

	for(int k=0; k<rs3.GetRecordCount(); k++)
	{ 
		rs3.GetFieldValue("sSido", strSido);
		rs3.GetFieldValue("sGugun", strGugun);
		rs3.GetFieldValue("sDong", strDong);
		rs3.GetFieldValue("nID", nID);

		CXTPGridRecord *pRecord = GetRecordFromGugun(strSido, strGugun, &m_lstStart);

		if(pRecord) 
		{
			CXTPGridRecord *pRecord1 = pRecord->GetChilds()->Add(new CChargeReportRecord(strDong, nID, TRUE, TRUE));

			//if(strExpandCity == strSido)
			//	pRecord->SetExpanded(TRUE);
		}

		pRecord = GetRecordFromGugun(strSido, strGugun, &m_lstDest);

		if(pRecord) 
		{
			CXTPGridRecord *pRecord1 = pRecord->GetChilds()->Add(new CChargeReportRecord(strDong, nID, TRUE, TRUE));

			//if(strExpandCity == strSido)
			//	pRecord->SetExpanded(TRUE);
		}

		rs3.MoveNext();
	}


	m_lstStart.Populate();
	m_lstDest.Populate();

	ShowListCenter(&m_lstStart, strExpandCity);
	ShowListCenter(&m_lstDest, strExpandCity);

	return TRUE;
}

void CChargeDongNewDlg::ShowListCenter(CXTPGridControl *pControl, CString strExpandCity)
{
	CXTPGridRows *pRows = pControl->GetRows();

	long nCount = pRows->GetCount();

	for(int i=0; i<nCount; i++)
	{
		CXTPGridRow *pRow = pRows->GetAt(i);

		if(pRow->GetRecord()->GetItem(0)->GetCaption(NULL) == strExpandCity)
		{
			pControl->EnsureVisible(pRow);
			pControl->GetSelectedRows()->Select(pRow);
			pControl->SetFocusedRow(pRow);
			pControl->Populate();
			return;
		}
	}
}



CXTPGridRecord* CChargeDongNewDlg::GetRecordFromSido(CString strSido, CXTPGridControl *pControl)
{
	CXTPGridRecords *pRecords = pControl->GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString strTemp = pRecord->GetItem(0)->GetCaption(NULL);

		if(strSido == strTemp)
			return pRecord;
	}

	return NULL;
}

CXTPGridRecord* CChargeDongNewDlg::GetRecordFromGugun(CString strSido, CString strGugun, CXTPGridControl *pControl)
{
	CXTPGridRecords *pRecords = pControl->GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		CString strTemp = pRecord->GetItem(0)->GetCaption(NULL);

		if(strSido == strTemp)
		{
			if(pRecord->HasChildren()) 
			{
				CXTPGridRecords *pRecords1 = pRecord->GetChilds();;

				for(int j=0; j<pRecords1->GetCount(); j++)
				{
					CXTPGridRecord *pRecord1 = pRecords1->GetAt(j);
					strTemp = pRecord1->GetItem(0)->GetCaption(NULL);

					if(strGugun == strTemp)
						return pRecord1;
				}
			}
		}
	}

	return NULL;
}

CXTPGridRecord* CChargeDongNewDlg::GetFirstSelectedRecord(CXTPGridControl *pControl)
{
	CXTPGridSelectedRows *pRows = pControl->GetSelectedRows();

	if(pRows == NULL)
		return NULL;

	if(pRows->GetCount() == 0)
		return NULL;

	return pRows->GetAt(0)->GetRecord();
}

void CChargeDongNewDlg::OnReportItemSelChange(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	/*
	CPoint pt = pItemNotify->pt;


	CPoint point;
	GetCursorPos(&point);
	CXTPGridRow *pRow = m_lstDong.HitTest(point);
	//pRow->HitTest()

	//m_nSelCol = pItemNotify->pColumn->GetIndex();
	//m_nSelRow = pItemNotify->pRow->GetIndex();
	//m_nSelCol = pItemNotify->pColumn->GetIndex();
	*/
}

void CChargeDongNewDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	//if (!pItemNotify->pRow || !pItemNotify->pColumn)
	//	return; 
 
	if(m_bSave == FALSE)
	{
		if(IsChargeChange(TRUE) == -1)
		{ 
			//MessageBox("요금 링크를 사용하는 업체는 요금을 수정 하실수 없습니다", "확인", MB_ICONINFORMATION);
		}
		else if(IsChargeChange(TRUE) > 0)
		{
			long nRet = MessageBox("저장되지 않은 항목이 있습니다\r\n저장하시겠습니까?", "확인", MB_OKCANCEL);

			if(nRet == IDOK) 
				IsChargeChange(FALSE);
		}
	}

	CChargeReportRecord *pStartRecord = (CChargeReportRecord*)GetFirstSelectedRecord(&m_lstStart);
	CChargeReportRecord *pDestRecord = (CChargeReportRecord*)GetFirstSelectedRecord(&m_lstDest);

	if(pStartRecord == NULL || pDestRecord == NULL)
		return;

	long nStartID = pStartRecord->GetGuID();
	long nDestID = pDestRecord->GetGuID();

	BOOL bStartLi = pStartRecord->IsHasLi();
	BOOL bDestLi = pDestRecord->IsHasLi();

	if(nStartID == 0 || nDestID == 0) 
		return;

	RefreshDongData(nStartID, bStartLi, nDestID, bDestLi);

	m_bSave = FALSE;
}

void CChargeDongNewDlg::RefreshDongData(long nStartID, BOOL bStartLi, long nDestID, BOOL bDestLi)
{
	ClearDongList();
	FillDongData(nStartID, bStartLi, &m_mapStart);
	FillDongData(nDestID, bDestLi, &m_mapDest);
	MakeDongList();
	RefreshDongCharge(nStartID, bStartLi, nDestID, bDestLi);
}

void CChargeDongNewDlg::FillDongData(long nID, BOOL bLi, MAP_DONG *pMap)
{
	pMap->clear();

	if(pMap == &m_mapDest)
	{
		ST_DONG st; st.nID = 0; st.strDong = "";
		pMap->insert(MAP_DONG::value_type(pMap->size(), st));
	}

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_dong_from_gu_1");
	cmd.AddParameter(nID);
	cmd.AddParameter(bLi);

	if(!rs.Execute(&cmd))
		return;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		ST_DONG st;
		rs.GetFieldValue("nID", st.nID);
		rs.GetFieldValue("sDong", st.strDong);

		pMap->insert(MAP_DONG::value_type(pMap->size(), st));
		rs.MoveNext();
	}
}



BOOL CChargeDongNewDlg::IsUpdateOk()
{
	CBranchInfo *p = (CBranchInfo*)m_cmbBranch.GetItemData(m_cmbBranch.GetCurSel());

	if(p->nCompanyCode == p->nPayTable)
		return TRUE;

	if(p->nPayTable == m_ui.nCompany)
		return TRUE;

	//MessageBox("요금 링크를 사용하는 업체는 요금을 수정 하실수 없습니다", "확인", MB_ICONINFORMATION);
	return FALSE;
}


long CChargeDongNewDlg::GetCurPayCompany()
{
	long nIndex = m_cmbBranch.GetCurSel();
	CBranchInfo *p = (CBranchInfo*)m_cmbBranch.GetItemData(nIndex);
	return p->nPayTable;
}

void CChargeDongNewDlg::RefreshDongCharge(long nStartID, BOOL bStartLi, long nDestID, BOOL bDestLi)
{
	long nCustomerCharge = m_cmbDiscountCompany.GetCurSel();
	long nGNo = (long)m_cmbDiscountCompany.GetItemData(nCustomerCharge);

	CMkRecordset rs(m_pMkDb); 
	//CMkCommand cmd(m_pMkDb, "select_charge_for_gu_2"); 
	CMkCommand cmd(m_pMkDb, "select_charge_for_gu_q3");
	cmd.AddParameter(GetCurPayCompany()); //지사선택하는걸로 바꿔야함
	cmd.AddParameter(nStartID);
	cmd.AddParameter(bStartLi);
	cmd.AddParameter(nDestID);
	cmd.AddParameter(bDestLi);
	cmd.AddParameter(nGNo);
	cmd.AddParameter(m_cmbType.GetCurSel());
	cmd.AddParameter(m_cmbCarType.GetCurSel());


	if(!rs.Execute(&cmd))
		return;

	m_PreGNo = nGNo;
	m_PreType = m_cmbType.GetCurSel();
	m_PreCarType= m_cmbCarType.GetCurSel();

	long nStartDongID, nDestDongID, nCharge;

	m_mapSave.clear();

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nStartID", nStartDongID);
		rs.GetFieldValue("nDestID", nDestDongID);
		rs.GetFieldValue("nCharge", nCharge);

		nCharge = nCharge / 1000;

		SetCharge(nStartDongID, nDestDongID, nCharge);

		m_mapSave.insert(SAVE_MAP::value_type(make_pair(nStartDongID, nDestDongID), nCharge));

		rs.MoveNext();
	}

	m_lstDong.Populate();
}

void CChargeDongNewDlg::SetCharge(long nStartDongID, long nDestDongID, long nCharge)
{
	CXTPGridRecords *pRecords = m_lstDong.GetRecords();

	long nRowCount = pRecords->GetCount();
	long nColumnCount = m_lstDong.GetColumns()->GetCount();

	//Row에 출발지, Col에 도착지

	for(int i=0; i<nRowCount; i++)
	{
		CChargeDongReportRecord *pRecord = (CChargeDongReportRecord*)pRecords->GetAt(i);

		if(pRecord->GetStartDongID() == nStartDongID)
		{
			for(int j=1; j<nColumnCount; j++)
			{
				if(pRecord->GetDestDongID(j) == nDestDongID)
				{
					pRecord->SetCharge(j, nCharge);
					return;
				}
			}
		}		
	}
}

void CChargeDongNewDlg::ClearDongList()
{
	m_lstDong.GetRecords()->RemoveAll();
	m_lstDong.GetColumns()->Clear();
}

long CChargeDongNewDlg::GetMaxHeightText(CPaintDC *pDc, CString strText)
{
	long nY = 0;
	CStringW strTextW(strText);

	for(int i=0; i<strTextW.GetLength(); i++)
	{
		CStringW strW = strTextW.Mid(i, 1);

		CSize szSize = pDc->GetTextExtent(CString(strW)); 

		nY += szSize.cy - 1;
	} 

	return nY;
}

void CChargeDongNewDlg::MakeDongList()
{ 
	long nColItem = 0; 
	long nItem = 0;
	long nFirstRowHeight = 10;
 
	m_lstDong.SetSelectedCol(0); 
	CPaintDC dc(&m_lstDong);   
	CFont *pOldfont = dc.SelectObject(m_FontManager.GetFont("맑은 고딕", 20, FW_BOLD));
   
	for(MAP_DONG::iterator it = m_mapDest.begin(); it != m_mapDest.end(); it++)
	{  
		CString strDong = ::GetRemoveLastDong(it->second.strDong); 

		CSize szSize = dc.GetTextExtent(strDong); 
		CStringW strW(strDong);
 
		CXTPGridColumn *pCol = m_lstDong.AddColumn(new CXTPGridColumn(nColItem++, strDong, 55, FALSE));

		nFirstRowHeight = max(nFirstRowHeight, GetMaxHeightText(&dc, strDong));

		//nFirstRowHeight = max(nFirstRowHeight, szSize.cy * strW.GetLength());

		if(nItem == 0)
		{
			pCol->SetWidth(55); 
			pCol->GetEditOptions()->m_bAllowEdit = FALSE;
			pCol->GetEditOptions()->m_dwEditStyle = ES_NUMBER;
		}
		else
		{
			pCol->SetWidth(ROW_COL_SIZE);
			pCol->GetEditOptions()->m_bAllowEdit = TRUE;
			pCol->SetAlignment(DT_RIGHT);
		} 

		nItem++;
	}  

	CChargePaintManager *pPaintManager = (CChargePaintManager*)m_lstDong.GetPaintManager();
	pPaintManager->SetFirstRowHeight(nFirstRowHeight);

	m_lstDong.AddRecord(new CChargeDongReportRecord(nColItem, &m_mapDest));

	m_lstDong.SetFreezeColumnsCount(1);
	m_lstDong.AllowEdit(TRUE);
	m_lstDong.Populate();

	long nColCount = m_lstDong.GetColumns()->GetCount();
	long nMaxCol = 10; 

	for(MAP_DONG::iterator it = m_mapStart.begin(); it != m_mapStart.end(); it++)
	{
		CString strDong = ::GetRemoveLastDong(it->second.strDong);
		CSize szSize = dc.GetTextExtent(strDong);

		nMaxCol = max(nMaxCol, szSize.cx);
		m_lstDong.AddRecord(new CChargeDongReportRecord(it->second.nID, strDong, nColItem, &m_mapDest));
	}

	CXTPGridColumn *pCol = m_lstDong.GetColumns()->GetAt(0);
	pCol->SetWidth(nMaxCol);

	m_lstDong.Populate();

	dc.SelectObject(pOldfont);
}

void CChargeDongNewDlg::OnBnClickedCloseButton()
{
	OnCancel();
}

void CChargeDongNewDlg::OnBnClickedSaveButton()
{
	if(!::POWER_CHECK(1101, "요금수정/삭제", TRUE)) 
		return;

	long nSaveCount = IsChargeChange(TRUE);

	if(nSaveCount > 0)
	{
		IsChargeChange(FALSE);
		MessageBox("저장되었습니다", "확인", MB_ICONINFORMATION);
		OnReportItemClick(NULL, NULL);
	}
	else if(nSaveCount == 0)
	{
		MessageBox("변경된 요금이 없습니다", "확인", MB_ICONINFORMATION);
	}
	else if(nSaveCount == -1)
	{
		MessageBox("요금 링크를 사용하는 업체는 요금을 수정 하실수 없습니다", "확인", MB_ICONINFORMATION);
	}

		
}

BOOL CChargeDongNewDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_LBUTTONUP)
	{ 
		CPoint pt;
		CRect rcClient;
		m_lstDong.GetWindowRect(&rcClient); 
		GetCursorPos(&pt);

		if(rcClient.PtInRect(pt))
		{
			//ScreenToClient(&pt);
			pt -= rcClient.TopLeft(); 
			CXTPGridRow *pRow = m_lstDong.HitTest(pt);

			if(pRow)  
			{ 
				CXTPGridRecordItem *pItem = pRow->HitTest(pt);

				long nIndex = pItem->GetIndex();
				m_lstDong.SetSelectedCol(nIndex); 
				CChargeDongReportRecord *pRecord = ((CChargeDongReportRecord*)pRow->GetRecord());
				//pRecord->SetCharge(nIndex, 0);

				if(pRow->GetRecord()->GetIndex() == 0)
					return TRUE;			
			}
		} 
	}
	
	return CMyDialog::PreTranslateMessage(pMsg);
}

void CChargeDongNewDlg::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(nIDEvent);
	ReLoadCharge();

	CMyDialog::OnTimer(nIDEvent);
} 

void CChargeDongNewDlg::ReLoadCharge()
{

	/*
	CChargeDongReportRecord *pRecord1 = (CChargeDongReportRecord*)m_lstDong.GetRecords()->GetAt(1);
	pRecord1->SetCharge(1, 200000);
	pRecord1->GetItem(1)->SetCaption(fc.GetStringFromLong(200000));
	m_lstDong.Populate();
	return; 

	for(LONG_MAP::iterator it = m_map.begin(); it != m_map.end(); it++)
	{
	ST_LONG st = it->second;

	CChargeDongReportRecord *pRecord1 = (CChargeDongReportRecord*)m_lstDong.GetRecords()->GetAt(st.nRow);

	if(pRecord1->GetCharge(st.nCol) == 0)
	{
	pRecord1->SetCharge(st.nCol, st.nCharge);
	pRecord1->SetChange(st.nCol, FALSE); 
	pRecord1->GetItem(st.nCol)->SetCaption(fc.GetStringFromLong(st.nCharge));
	}
	}

	m_map.clear();
	*/
}

void CChargeDongNewDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(!m_lstStart.GetSafeHwnd()) return;
	if(!m_lstDest.GetSafeHwnd()) return;
	if(!m_lstDong.GetSafeHwnd()) return;

	CRect rcStart, rcDest, rcDong;

	m_lstStart.GetWindowRect(rcStart);
	m_lstDest.GetWindowRect(rcDest);
	m_lstDong.GetWindowRect(rcDong);
	ScreenToClient(rcStart);
	ScreenToClient(rcDest);
	ScreenToClient(rcDong);

	rcStart.bottom = rcDest.bottom = rcDong.bottom = cy - 5;
	rcDong.right = cx - 5;

	m_lstStart.MoveWindow(rcStart);
	m_lstDest.MoveWindow(rcDest);
	m_lstDong.MoveWindow(rcDong);
}

long CChargeDongNewDlg::IsChargeChange(BOOL bOnlyCount)
{
	CXTPGridRecords *pRecords = (CXTPGridRecords*)m_lstDong.GetRecords();

	long nType = m_cmbType.GetCurSel();
	long nChangeCount = 0;
	long nRowCount= pRecords->GetCount();
	long nColCount = m_lstDong.GetColumns()->GetCount();
	BOOL bTwoWay = m_chkTwoWay.GetCheck();

	if(bOnlyCount)
	{
		if(!IsUpdateOk())
			return -1;
	}

	for(int i=1; i<nRowCount; i++)
	{
		CChargeDongReportRecord *pRecord = (CChargeDongReportRecord*)pRecords->GetAt(i);

		long nStartID = pRecord->GetStartDongID();

		for(int j=1; j<nColCount; j++)
		{
			if(pRecord->IsChange(j))
			{
				long nDestID = pRecord->GetDestDongID(j);

				if(!bOnlyCount)					
				{
					if(!SaveReal(nStartID, nDestID, pRecord->GetCharge(j)))
					{
						MessageBox("요금 저장중에 오류가 발생했습니다\r\n다시 시도해 주세요", "확인", MB_ICONINFORMATION);
						return 0;
					}
				}

				nChangeCount++;
			}
		}
	}

	if(!bOnlyCount)
		m_bSave = TRUE;

	return nChangeCount;
}

BOOL CChargeDongNewDlg::SaveReal(long nStartID, long nDestID, long nCharge)
{
	long nCustomerCharge = m_cmbDiscountCompany.GetCurSel();
	long nGNo = (long)m_cmbDiscountCompany.GetItemData(nCustomerCharge);

	CMkCommand cmd(m_pMkDb, "update_charge_dong_new_q4");
	cmd.AddParameter(GetCurPayCompany());
	cmd.AddParameter(nStartID);
	cmd.AddParameter(nDestID);
	cmd.AddParameter(nCharge * 1000);
	cmd.AddParameter(m_PreGNo);
	cmd.AddParameter(m_PreType);
	cmd.AddParameter(m_PreCarType);
	cmd.AddParameter(m_chkTwoWay.GetCheck());
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);

	return cmd.Execute();
}

LONG CChargeDongNewDlg::OnChangeBrachCode(WPARAM wParam, LPARAM lParam)
{	
	OnReportItemClick(NULL, NULL);

	return 0;
}

void CChargeDongNewDlg::OnBnClickedRefreshButton()
{
	OnReportItemClick(NULL, NULL);
}

void CChargeDongNewDlg::OnCbnSelchangeTypeCombo()
{
	OnReportItemClick(NULL, NULL);
}

void CChargeDongNewDlg::OnEnChangeSearchStartEdit()
{
	CString strSearch; m_edtStartSearch.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstDong.GetRecords();

	if(pRecords->GetCount() <= 1)
		return;

	for(int i=1; i<pRecords->GetCount(); i++) 
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		CString strItem = pRecord->GetItem(0)->GetCaption(NULL);

		pRecord->SetVisible(strItem.Find(strSearch) >= ZERO ? TRUE : FALSE);
	}

	m_lstDong.Populate();
}

void CChargeDongNewDlg::OnEnChangeSearchDestEdit()
{
	CString strSearch; m_edtDestSearch.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstDong.GetRecords();

	if(pRecords->GetCount() < 1)
		return;

	CXTPGridColumns *pColumns = m_lstDong.GetColumns();

	CXTPGridRecord *pRecord = pRecords->GetAt(ZERO);

	for(int i=1; i<pColumns->GetCount(); i++)
	{
		CString strItem = pRecord->GetItem(i)->GetCaption(NULL);

		pColumns->GetAt(i)->SetVisible(strItem.Find(strSearch) >= ZERO ? TRUE : FALSE);
	}

	m_lstDong.Populate();
}

void CChargeDongNewDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstDong.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU_1);
	CMenu *pRMenu=rMenu.GetSubMenu(5);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x,point.y,this);
}

void CChargeDongNewDlg::OnInsertCharge()
{
	CXTPGridRecord *pRecord = m_lstDong.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	long nCol = m_lstDong.GetSelectedCol();
	long nRow = pRecord->GetIndex();

	if(nCol < 1) return;
	if(nRow < 0) return;

	CChargeInsertDlg dlg;
	dlg.m_plstDong = &m_lstDong;
	dlg.m_nCol = nCol;

	if(dlg.DoModal() == IDOK)
	{
		CXTPGridSelectedRows *pRows= m_lstDong.GetSelectedRows();

		for(int i=0; i<pRows->GetCount(); i++)
		{ 
			CChargeDongReportRecord *pRecord = (CChargeDongReportRecord*)pRows->GetAt(i)->GetRecord();
			pRecord->SetCharge(nCol, atoi(dlg.m_strCharge));
			pRecord->SetChange(nCol, TRUE);
		}
	}
}

void CChargeDongNewDlg::OnExcel()
{
	if(!POWER_CHECK(1900, "엑셀변환", TRUE))
		return;
	
	::AddSecurityLog(m_ci.m_nCompanyCode, 801, m_lstDong.GetRecords()->GetCount());
	CMyExcel::ToExcel(&m_lstDong);
}

void CChargeDongNewDlg::ChargeTypeNameRefresh()
{
	m_cmbDiscountCompany.ResetContent();

	m_cmbDiscountCompany.InsertString(0, "기본요금");
	m_cmbDiscountCompany.SetItemData(0, 0);

	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "select_charge_discount_company2");	
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), GetCurPayCompany());		

	long nID = 0;
	int  i = 1;
	CString sChargeName = "";

	if(pRs2.Execute(&pCmd2))
	{
		while(!pRs2.IsEOF())
		{	
			pRs2.GetFieldValue("nID", nID);
			pRs2.GetFieldValue("sChargeName", sChargeName);

			m_cmbDiscountCompany.InsertString(i, sChargeName);
			m_cmbDiscountCompany.SetItemData(i++, (DWORD_PTR)nID);
			pRs2.MoveNext();
		}
		pRs2.Close();
	}

	m_cmbDiscountCompany.SetCurSel(0);
}

void CChargeDongNewDlg::OnCbnSelchangeCarTypeCombo()
{
	m_cmbCarType2.SetCurSel(m_cmbCarType.GetCurSel());
	OnReportItemClick(NULL, NULL);
}

void CChargeDongNewDlg::OnCbnEditchangeDisComCombo2()
{
}

void CChargeDongNewDlg::OnCbnSelchangeDisComCombo2()
{
	OnReportItemClick(NULL, NULL);
}

void CChargeDongNewDlg::OnCbnSelchangeCarTypeCombo2()
{
	m_cmbCarType.SetCurSel(m_cmbCarType2.GetCurSel());
	OnReportItemClick(NULL, NULL);
}

void CChargeDongNewDlg::OnBnClickedSearchGroupBtn()
{
	CSearchGroupDlg dlg;
	dlg.m_nDataType = SG_DISCOUNT_COMPANY;
	dlg.m_nCompany = m_nCompany;

	if(dlg.DoModal() == IDOK)
	{
		for(int i = 0; i < m_cmbDiscountCompany.GetCount(); i++)
		{
			long nGNo = (long)m_cmbDiscountCompany.GetItemData(i);
			if(dlg.m_nChargeID == nGNo)
			{
				m_cmbDiscountCompany.SetCurSel(i);				
				break;
			}
		}
	}
}

void CChargeDongNewDlg::OnBnClickedSearchBtn()
{
	CPoint pt;
	GetCursorPos(&pt); 
	BCMenu *pMenu = new BCMenu;
	pMenu->CreatePopupMenu();

	pMenu->AppendMenu(MF_BYCOMMAND, IDC_SEARCH_GROUP_BTN, "그룹검색");
	pMenu->AppendMenu(MF_SEPARATOR, (UINT)-1, (LPCTSTR)NULL);
	pMenu->AppendMenu(MF_BYCOMMAND, IDC_DISCOUNT_COMPANY_BTN, "요금제등록");	
	pMenu->AppendMenu(MF_BYCOMMAND, IDC_DISCOUNT_COMPANY_DEL_BTN, "요금제삭제");
	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);

	delete pMenu;
	pMenu = NULL;
}

void CChargeDongNewDlg::OnBnClickedDiscountCompanyBtn()
{
	if(!POWER_CHECK(1101, "요금수정/삭제", TRUE))
		return;

	CString sChargeName = "";
	CVarietyDlg dlg;
	dlg.m_sTitleDlg = "신규요금명을 적으세요";
	if(dlg.DoModal() == IDOK)
	{

		sChargeName = dlg.m_sValue;
		if(sChargeName.GetLength() == 0)
			return;

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "insert_chargetype_name");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCurBranchInfo()->nPayTable);
		pCmd.AddParameter(typeString, typeInput, sChargeName.GetLength(), sChargeName);
		pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);
		CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

		if(!pRs.Execute(&pCmd)) return;
		long nReturnValue = 0;
		pPar->GetValue(nReturnValue);

		if(nReturnValue < 0)
			MessageBox("기존의 등록할 이름과 일치합니다.", "확인", MB_ICONINFORMATION);
		else
		{
			MessageBox("요금제가 신규로 생성되었습니다.","확인", MB_ICONINFORMATION);
			m_cg.FillCharge();
		}

	}
	else
		return;


	ChargeTypeNameRefresh();
	CString sTypeName = "";
	for(int i = 0; i < m_cmbDiscountCompany.GetCount(); i++)
	{
		m_cmbDiscountCompany.GetLBText(i,sTypeName);
		if(sTypeName == sChargeName)
		{
			m_cmbDiscountCompany.SetCurSel(i);
			return;
		}
	}
}

void CChargeDongNewDlg::OnBnClickedDiscountCompanyDelBtn()
{
	if(!POWER_CHECK(1101, "요금수정/삭제", TRUE))
		return;

	if(m_cmbDiscountCompany.GetCount() <= 0 )
		return;
	if(m_cmbDiscountCompany.GetCurSel() == 0 )
	{
		MessageBox("기본요금은 삭제하실수 없습니다", "확인",  MB_ICONINFORMATION);
		return;
	}
	if(m_cmbDiscountCompany.GetCurSel() < 0 )
	{
		MessageBox("요금제가 선택되지 않았습니다", "확인",  MB_ICONINFORMATION);
		return;
	}

	CString strChargeTypeName = "", sTemp = "";

	int nCur = m_cmbDiscountCompany.GetCurSel();
	m_cmbDiscountCompany.GetLBText(nCur,strChargeTypeName);
	long nChargeTypeID = (long)m_cmbDiscountCompany.GetItemData(nCur);
	sTemp = strChargeTypeName + " 의 해당요금제를 삭제하시겠습니까?\n\r\n\r 요금제가 삭제되면 법인등록된 요금제도 삭제됩니다.\n\r\n\r 삭제하시려면 예(Y)를 눌러주세요";
	if(MessageBox(sTemp,"확인", MB_ICONINFORMATION| MB_YESNO) == IDYES)
	{

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "delete_chargetype_name2");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCurBranchInfo()->nPayTable);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nChargeTypeID);

		CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

		if(!pRs.Execute(&pCmd)) return;
		long nReturnValue = 0;
		pPar->GetValue(nReturnValue);

		if(nReturnValue < 0)
			MessageBox("삭제할 해당요금이 서버에 없습니다.", "확인", MB_ICONINFORMATION);
		else
		{
			MessageBox("요금제가 삭제 되었습니다.","확인", MB_ICONINFORMATION);			
			ChargeTypeNameRefresh();
		}

	}
	m_cmbDiscountCompany.SetCurSel(0);
}

void CChargeDongNewDlg::OnCbnSelchangeBranchCombo()
{
	OnReportItemClick(NULL, NULL);
}

void CChargeDongNewDlg::OnCancel()
{
	CMyDialog::OnCancel();
	delete this;
}

BOOL CXTPGridChargeControl::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_CHAR) //CXTPGridInplaceEdit 으로 부터 오는 메세지다
	{
		if(pMsg->wParam == VK_RETURN ||
			pMsg->wParam == VK_TAB)
		{
			CXTPGridRow *pRow = GetSelectedRows()->GetAt(0);
			long nCol = GetSelectedCol();

			if(pRow != NULL)
			{
				CXTPGridRow *pNextRows = pRow;
				long nNextCol = nCol;

				if(pMsg->wParam == VK_RETURN) 
				{
					long nRow = pRow->GetIndex() + 1;

					if(nRow >= GetRows()->GetCount())
						return CXTPListCtrl2::PreTranslateMessage(pMsg);
 
					pNextRows = GetRows()->GetAt(nRow);
				}
				else //VK_TAB
				{
					nNextCol = nCol + 1;

					if(nNextCol >= GetColumns()->GetCount())
						return CXTPListCtrl2::PreTranslateMessage(pMsg);
				}

				SetSelectedCol(nNextCol);
				XTP_REPORTRECORDITEM_ARGS args(this, pNextRows, GetColumns()->GetAt(nNextCol));
				EditItem(&args);
				return TRUE;
			}
		}
	}

	return CXTPListCtrl2::PreTranslateMessage(pMsg);
}

BOOL CChargeDongReportRecord::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CXTPGridRecord::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
