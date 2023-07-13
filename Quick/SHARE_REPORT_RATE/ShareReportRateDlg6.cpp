// ShareReportRateDlg6.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareReportRateDlg6.h"
#include "MyReportPaintManager.h"
#include "ConsignSettingDlg.h"

// CShareReportRateDlg6

#define NEW_APPLY 0
#define  APPLY_RATE 1
#define  MODIFY_RATE 2

IMPLEMENT_DYNCREATE(CShareReportRateDlg6, CMyFormView)

CShareReportRateDlg6::CShareReportRateDlg6()
	: CMyFormView(CShareReportRateDlg6::IDD)
{
	COleDateTimeSpan span(30, 0,0,0);
	
}

CShareReportRateDlg6::~CShareReportRateDlg6()
{

}

void CShareReportRateDlg6::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST,m_lstReport);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_Control(pDX, IDC_SETTING_REPORT,m_SettingReport);
	
	
}

BEGIN_MESSAGE_MAP(CShareReportRateDlg6, CMyFormView)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_WM_MOUSEACTIVATE()
	ON_NOTIFY(NM_DBLCLK, IDC_SETTING_REPORT, OnReportLogItemClick)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CShareReportRateDlg6::OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_LINK_BTN, &CShareReportRateDlg6::OnBnClickedLinkBtn)
	ON_BN_CLICKED(IDC_LINK_MODIFY_BTN, &CShareReportRateDlg6::OnBnClickedLinkModifyBtn)
	ON_BN_CLICKED(IDC_REJECT_BTN, &CShareReportRateDlg6::OnBnClickedRejectBtn)
	ON_BN_CLICKED(IDC_ACCEPT_BTN, &CShareReportRateDlg6::OnBnClickedAcceptBtn)
END_MESSAGE_MAP()


// CShareReportRateDlg6 �����Դϴ�.

#ifdef _DEBUG
void CShareReportRateDlg6::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CShareReportRateDlg6::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CShareReportRateDlg6 �޽��� ó�����Դϴ�.

void CShareReportRateDlg6::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();


	CXTPGridColumn* pCol0  = m_lstReport.AddColumn(new CXTPGridColumn(0, "����", 50, FALSE));
	m_lstReport.AddColumn(new CXTPGridColumn(1, "����", 45, FALSE));
	m_lstReport.AddColumn(new CXTPGridColumn(2, "ȸ���", 100, FALSE));
	m_lstReport.AddColumn(new CXTPGridColumn(3, "��Ȳ��", 90, FALSE));
	m_lstReport.AddColumn(new CXTPGridColumn(4, "��ǥ��ȣ", 90, FALSE));
	m_lstReport.AddColumn(new CXTPGridColumn(5, "��ǥ", 60, FALSE));

	pCol0->SetTreeColumn(TRUE);

	m_lstReport.GetReportHeader()->AllowColumnResize(TRUE);
	m_lstReport.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_lstReport.GetReportHeader()->AllowColumnSort(TRUE);
	m_lstReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_lstReport.SetPaintManager(new CMyReportPaintManager());
	m_lstReport.GetPaintManager()->m_strNoItems = "ǥ���� ������ ���ų�, ���ǿ� �ش��ϴ� �ڷᰡ �������� ����";
	m_lstReport.SetGridStyle(TRUE, xtpGridSolid);
	m_lstReport.SetGridColor(RGB(212, 208, 200));
	m_lstReport.AllowEdit(FALSE);

	m_lstReport.Populate();

	int nCol = 0;
	
	m_SettingReport.InsertColumn(nCol++, "����",DT_LEFT,50, FALSE, TRUE);
	m_SettingReport.InsertColumn(nCol++, "����",	DT_LEFT,40, FALSE, FALSE);
	m_SettingReport.InsertColumn(nCol++, "ȸ���",DT_LEFT,90, FALSE, FALSE);
	m_SettingReport.InsertColumn(nCol++, "������",	DT_CENTER,45, FALSE, FALSE);
	m_SettingReport.InsertColumn(nCol++, "����",DT_LEFT,55, FALSE, FALSE);
	m_SettingReport.InsertColumn(nCol++, "������",DT_LEFT,60, FALSE, FALSE);
	m_SettingReport.InsertColumn(nCol++, "������",DT_CENTER,45, FALSE, FALSE);
	m_SettingReport.InsertColumn(nCol++, "������",DT_CENTER,45, FALSE, FALSE);
	m_SettingReport.InsertColumn(nCol++, "����",DT_CENTER,60, FALSE, FALSE);	
	m_SettingReport.InsertColumn(nCol++, "����������",DT_LEFT, 90, FALSE, FALSE);	
	m_SettingReport.InsertColumn(nCol++, "��������",DT_LEFT, 70, FALSE, FALSE);
	m_SettingReport.InitControl();
	m_SettingReport.GetReportHeader()->AllowColumnResize(FALSE);
	m_SettingReport.GetReportHeader()->AllowColumnSort(FALSE);
	m_SettingReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_SettingReport.Populate();

	CompanyRefreshList(); // ����� ȸ�縮��Ʈ
	LinkRefreshList(); // ��ϵ� ����Ʈ	

	
}

void CShareReportRateDlg6::OnContextMenu(CWnd* pWnd, CPoint point)
{
	//CRect rect;
	////m_List.GetWindowRect(&rect);
	//if(!rect.PtInRect(point)) return;

	//CMenu rMenu;
	//rMenu.LoadMenu(IDR_CONTEXT_MENU);
	//CMenu *pRMenu=rMenu.GetSubMenu(2);
	//pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CShareReportRateDlg6::OnViewExcel()
{
	if(!LF->POWER_CHECK(1900, "������ȯ", TRUE))
		return;

	//LF->AddSecurityLog(m_ci.m_nCompanyCode, 1204, m_List.GetItemCount());  
	//CMyExcel::ToExcel(m_List);
}


int CShareReportRateDlg6::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	return 0;
	return CMyFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CShareReportRateDlg6::OnBnClickedRefreshBtn()
{
	LinkRefreshList();
}




void CShareReportRateDlg6::InitRegionGroup()
{
	int nCol = 0;


	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_region_group");
	pCmd.AddParameter(0);

	if(!pRs.Execute(&pCmd)) return;

	CString sCity, sCitySum;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("sCity", sCity);
		pRs.GetFieldValue("sCitySum", sCitySum);	

		m_gpMap2[sCity] = sCitySum;
		pRs.MoveNext();
	}

	pRs.Close();
}


BOOL CShareReportRateDlg6::IsTransCheckMode()
{

	if(m_ui.nCompany == 10 || (m_ui.nCompany >= 6550  && m_ui.nCompany <= 6590)  )
		return TRUE;
	else
		return FALSE;
}

void CShareReportRateDlg6::CompanyRefreshList()
{

	InitRegionGroup();

	m_map2.clear();
	m_lstReport.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_other_region_branch_2011");

	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(IsTransCheckMode());

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
			it = m_map2.find(sMainCity);

			if(it == m_map2.end())
			{
				m_map2[sMainCity] = m_lstReport.AddRecord(new CORBRecord(sMainCity));		

				it = m_map2.find(sMainCity);
			}

			pRegionTopRecord = it->second;
			pRegionTopRecord->SetExpanded(TRUE);

			pCityTopRecord = pRegionTopRecord->GetChilds()->Add(new CORBRecord(TRUE, sCity, sName, sOfficePhone, sTel, sOWner, nShareCode1));

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



CString CShareReportRateDlg6::GetGroupRegion(CString sCity)
{
	GROUP_MAP::iterator it;

	for(it = m_gpMap2.begin(); it != m_gpMap2.end(); it++)
	{
		if(it->second.Find(sCity) >= 0)
			return it->first;
	}

	return "��Ÿ";	
}



void CShareReportRateDlg6::LinkRefreshList()
{

	if( m_SettingReport.GetRecords()->GetCount() > 0)
	{
		m_SettingReport.DeleteAllItem();
		m_vecConsignCompany.clear();
	}


	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_consign_setting_company_list2011_1");
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	if(pRs.Execute(&pCmd))
	{
		long nOtherCompany, nNowRate, nID, nState, nMyAccept,nOtherCompanyCNo, 
			nModifyRequestCompany, nModifyRate ;		
		BOOL  bTodayDelete = 0, bReserve = FALSE;

		COleDateTime dtAcceptApply, dtInitDay, dtReserve;
		CString sTreeCity,sCity, sRquestCompanyName = "", sRequestRate = "", sApplyReserveDate = "",
			sEtc = "",sOtherCompanyName= "", sNowRate = "", sAcceptApplyDate = "", sReserve= "", 
			sConSignLink = "", sModifyRate = "", sDtInitDay = "", sDtReserve = "", sApplyModify = "";
		for(int i = 0; i < pRs.GetRecordCount(); i++ )
		{
			pRs.GetFieldValue("nMyAccept", nMyAccept);			
			pRs.GetFieldValue("sCity", sCity);			
			pRs.GetFieldValue("nOtherCompany", nOtherCompany);
			pRs.GetFieldValue("sOtherCompanyName", sOtherCompanyName);
			pRs.GetFieldValue("nOtherCompanyCNo", nOtherCompanyCNo);			
			pRs.GetFieldValue("nNowRate", nNowRate);
			pRs.GetFieldValue("dtInitDay", dtInitDay);			
			pRs.GetFieldValue("dtAcceptApply", dtAcceptApply);		
			pRs.GetFieldValue("nID", nID);
		/*	pRs.GetFieldValue("bTodayDelete", bTodayDelete);			
			pRs.GetFieldValue("dtTodayDelete", dtTodayDelete);	*/		
			pRs.GetFieldValue("nState", nState);
			pRs.GetFieldValue("nModifyRequestCompany", nModifyRequestCompany);
			pRs.GetFieldValue("bReserve", bReserve);
			pRs.GetFieldValue("dtReserve", dtReserve);
			pRs.GetFieldValue("nModifyRate", nModifyRate);
			
			sTreeCity = GetGroupRegion(sCity);
		
			if(nMyAccept)
				sConSignLink = "Ź��->My";
			else
				sConSignLink = "My->Ź��";
			
			if(nModifyRate > 0 && nModifyRequestCompany)
				sModifyRate.Format("%d%%", nModifyRate);
			else if(nModifyRate == 0 && ( nState == NEW_APPLY || nState == MODIFY_RATE ) )
				sModifyRate.Format("%d%%", 0);
			else
				sModifyRate = "";

			if(nNowRate > 0)
				sNowRate.Format("%d%%", nNowRate);
			else if(nNowRate == 0 && ( nState == APPLY_RATE || nState == MODIFY_RATE) )
				sNowRate.Format("%d%%", 0);
			else
				sNowRate = "";
			
			sAcceptApplyDate = (dtAcceptApply.m_status != COleDateTime::null) ?
				dtAcceptApply.Format("%y-%m-%d %H:%M") : "";
			sDtInitDay = (dtInitDay.m_status != COleDateTime::null) ?
				dtInitDay.Format("%y-%m-%d") : "";
			sDtReserve = (dtReserve.m_status != COleDateTime::null) ?
				dtReserve.Format("%m-%d") : "";

			if(nModifyRequestCompany == 0)
				sApplyModify = "";
			else if(nModifyRequestCompany == m_ci.m_nShareCode1)
				sApplyModify = "My";
			else
				sApplyModify = "Other";
			
		
			CMyXTPGridRecord *pParentRecord = GetParentSettingRecord(sTreeCity);		
			pParentRecord->SetExpanded(TRUE);
			CMyXTPGridRecord *pRecord =  (CMyXTPGridRecord *)pParentRecord->GetChilds()->Add(new CMyXTPGridRecord);

			pRecord->MySubAddItem("");
			pRecord->MySubAddItem(sCity);
			pRecord->MySubAddItem(sOtherCompanyName);		
			pRecord->MySubAddItem( sNowRate);

			pRecord->MySubAddItem(CConsignSettingDlg::GetLogType(nState));		
			pRecord->MySubAddItem(bReserve && (nState == NEW_APPLY || nState == MODIFY_RATE )	? 
													sDtReserve : "");	
			pRecord->MySubAddItem(sApplyModify);		
			pRecord->MySubAddItem(sModifyRate);		
			pRecord->MySubAddItem(sConSignLink );		
			
			pRecord->MySubAddItem(sAcceptApplyDate);				
			pRecord->MySubAddItem(sDtInitDay);	
			pRecord->SetItemDataLong(nOtherCompany );				
			pRecord->SetItemDataLong2(nID);
			pRecord->SetItemDataLong3(nMyAccept);
			pRecord->SetItemDataLong4(nModifyRequestCompany);

			pRecord->SetItemDataInt(nState);		

			//pRecord->SetExpanded(TRUE);
			if(pRecord->GetItemDataLong3() == 0)
				m_vecConsignCompany.push_back(pRecord);						

			pRs.MoveNext();
		}
		pRs.Close();	
	}


	CXTPGridColumn *pCol = m_SettingReport.GetColumns()->GetAt(0);
	if(pCol )
		pCol->SetTreeColumn(TRUE);
	m_SettingReport.Populate();
}

CMyXTPGridRecord* CShareReportRateDlg6::GetParentSettingRecord(CString sCity)
{
	if(m_SettingReport.GetRecords()->GetCount() <= 0)
		return InitSettingRegionGroup(sCity);

	for(int i =0; i < m_SettingReport.GetRecords()->GetCount(); i++)
	{
		CMyXTPGridRecord* pRecord = (CMyXTPGridRecord*)m_SettingReport.GetRecords()->GetAt(i);
		if( pRecord->GetItemDataString() == sCity)
			return pRecord;
	}

	return InitSettingRegionGroup(sCity);
}

CMyXTPGridRecord*  CShareReportRateDlg6::InitSettingRegionGroup(CString sCity)
{
	int nCol = 0;


	m_SettingReport.MyAddItem(nCol++,sCity, "����",	50, FALSE, DT_LEFT);
	m_SettingReport.MyAddItem(nCol++,"", "����",		40, FALSE, DT_LEFT);
	m_SettingReport.MyAddItem(nCol++,"", "ȸ���",		80, FALSE, DT_LEFT);
	m_SettingReport.MyAddItem(nCol++,"", "����",		80, FALSE, DT_LEFT);
	m_SettingReport.MyAddItem(nCol++,"", "������",		90, FALSE, DT_LEFT);
	m_SettingReport.MyAddItem(nCol++,"", "������",		50, FALSE, DT_LEFT);
	m_SettingReport.MyAddItem(nCol++,"", "����",		50, FALSE, DT_LEFT);
	m_SettingReport.MyAddItem(nCol++,"", "����",		80, FALSE, DT_LEFT);	
	m_SettingReport.MyAddItem(nCol++,"", "����������",  90, FALSE, DT_LEFT);		
	m_SettingReport.MyAddItem(nCol++,"", "����������",	90, FALSE, DT_LEFT);
	CMyXTPGridRecord  *pRecord = 
	m_SettingReport.MyAddItem(nCol++,"", "�������",		80, FALSE, DT_LEFT);	
	//m_mapCitySeing[sCity] = pRecord;
	m_SettingReport.InsertItemDataString(sCity);	
	m_SettingReport.EndItem();



	return pRecord;
}


BOOL CShareReportRateDlg6::GeneralCheckData()
{
	if(m_lstReport.GetSelectedRows()->GetCount() <=0 )
	{
		MessageBox("�����Ͻ� ȸ�縦 �����Ͽ� �ּ���", "Ȯ��" , MB_ICONINFORMATION);
		return FALSE;
	}


	CXTPGridRow *pRow = m_lstReport.GetSelectedRows()->GetAt(0);
	if( pRow->GetChilds()->GetCount() > 0 )
	{
		MessageBox("�����Ͻ� ���� ���ú��ٴ�  ȸ�縦 �����Ͽ� �ּ���", "Ȯ��" , MB_ICONINFORMATION);
		return FALSE;
	}
	return TRUE;
}

BOOL CShareReportRateDlg6::CheckData()
{


	try
	{
		if( m_lstReport.GetSelectedRows()->GetCount() <=0 )
			throw("������ ȸ�縦 �����Ͽ� �ּ���!");

		CString sErrMsg = "";

		for(int i = 0; i < m_lstReport.GetSelectedRows()->GetCount(); i++)
		{
			CXTPGridRow* pRow = m_lstReport.GetSelectedRows()->GetAt(i);
			if( pRow->GetTreeDepth() <= 0)
				continue;

			CORBRecord *pRecord =  (CORBRecord *)pRow->GetRecord();
			if ( IsConsignService(pRecord->m_nShareCode) )
			{
				sErrMsg.Format("������ ȸ���� %s�� �̹� �����Ǿ� �ֽ��ϴ�.",	pRecord->GetItem(2)->GetCaption(NULL) );						
				MessageBox( sErrMsg, 	"Ȯ��",  MB_ICONINFORMATION  ) ;
				return FALSE;;
			}
		}
		return TRUE;

	}	
	catch (char * e)
	{
		MessageBox(e, "Ȯ��", MB_ICONINFORMATION);
	}
	catch (CString  str)
	{
		MessageBox(str, "Ȯ��", MB_ICONINFORMATION);
	}
	return FALSE;

}

void CShareReportRateDlg6::OnBnClickedLinkBtn()
{
	if(! CheckData())
		return;

	if( !GeneralCheckData() ) 	return;

	CXTPGridRow *pRow = m_lstReport.GetSelectedRows()->GetAt(0);
	CORBRecord *pRecord = (CORBRecord *) pRow->GetRecord();	

	if(pRecord->m_nShareCode == m_ci.GetShareCode1() )
	{
		MessageBox("�ڻ翡 ����Ź����  �� �� �����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
		return;
	}



	CConsignSettingDlg dlg;
	dlg.m_bNew = TRUE;
	dlg.m_nShareCode1 = m_ci.GetShareCode1();
	dlg.m_nOtherCompany = pRecord->m_nShareCode;
	dlg.m_sOtherCity = pRecord->m_sCity;
	if( dlg.DoModal() == IDOK)
		LinkRefreshList();

}

BOOL CShareReportRateDlg6::IsConsignService(long nShareCode)
{
	CONSIGNCOMPANY_VEC::iterator it;

	if(	m_vecConsignCompany.size() <= 0 )
		return FALSE;

	for(it = m_vecConsignCompany.begin(); it != m_vecConsignCompany.end(); ++ it)
	{
		if( nShareCode ==  (*it)->GetItemDataLong() )
			return TRUE;
	}
	return FALSE;
}

void CShareReportRateDlg6::OnReportLogItemClick(NMHDR * pNotifyStruct, LRESULT * result)
{

	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;


	//int nRow = pItemNotify->pRow->GetIndex();
	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	if(m_SettingReport.GetSelectedCount() <= 0)
		return;

	OnBnClickedLinkModifyBtn();
}
void CShareReportRateDlg6::OnBnClickedLinkModifyBtn()
{
	if(m_SettingReport.GetSelectedRows()->GetCount() <=0 )
	{
		MessageBox( "�����Ͻ� ȸ�縦 �����Ͽ� �ּ���", "Ȯ��" , MB_ICONINFORMATION);
		return ;
	}

	CXTPGridRow *pRow = m_SettingReport.GetSelectedRows()->GetAt(0);
	CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *) pRow->GetRecord();	

	if(pRecord->GetItemDataLong() <= 0 )
	{
		MessageBox( "�����Ͻ� ȸ�縦 �����Ͽ� �ּ���", "Ȯ��" , MB_ICONINFORMATION);
		return ;
	}
	
	CXTPGridRow *pAreaRow = m_lstReport.GetSelectedRows()->GetAt(0);
	CORBRecord *pAreaRecord = (CORBRecord *) pAreaRow->GetRecord();	

	if(pAreaRecord->m_nShareCode == m_ci.GetShareCode1() )
	{
		MessageBox("�ڻ翡 ����Ź����  �� �� �����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
		return;
	}


	CConsignSettingDlg dlg;
	dlg.m_nShareCode1 = m_ci.GetShareCode1();
	dlg.m_bNew = FALSE;
	dlg.m_nOtherCompany = pRecord->GetItemDataLong();
	dlg.m_nShareCode1 = m_ci.GetShareCode1();
	dlg.m_nModifyID = pRecord->GetItemDataLong2();
	
	if( dlg.DoModal() == IDOK)
		LinkRefreshList();

}

void CShareReportRateDlg6::OnBnClickedRejectBtn()
{
	try{

		if(m_SettingReport.GetSelectedCount()<= 0	)
			throw "�ź��� �׸��� �������ּ���";

		CMyXTPGridRecord *pRecord = m_SettingReport.GetSelectedRecord(0);
		long nModifynRequestCompany = pRecord->GetItemDataLong4();
		long nState = pRecord->GetItemDataInt();

		if( !(nState == NEW_APPLY || nState == MODIFY_RATE )  )
			throw "�ź��Ͻ� �׸��� �ƴմϴ�. ";

		if( nModifynRequestCompany ==  m_ci.m_nShareCode1  )
			throw "�ڻ簡 ����(��û)�Ͻ� �׸��̿� �źΰ� �ȵǸ� ������ư�� ���� �����Ͽ� �ּ���.";

		long nOtherCompany = pRecord->GetItemDataLong();
		long nID = pRecord->GetItemDataLong2();

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "delete_consignment_reject_company2011" );
		pCmd.AddParameter( m_ci.GetShareCode1());
		pCmd.AddParameter(nOtherCompany);				
		pCmd.AddParameter(m_ui.strName);
		pCmd.AddParameter(m_ui.nCompany);
		pCmd.AddParameter(m_ui.nWNo);
		pCmd.AddParameter(nID);
	
		CMkParameter *pParOUTPUT = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
		if(!pCmd.Execute()) return;	

		int nOUTPUT = 0;
		pParOUTPUT->GetValue(nOUTPUT);

		if(nOUTPUT == 100 )
			throw "�ش�õ��� ����Ǿ� �ִ� ��ü�� �ֽ��ϴ�. ";
		if(nOUTPUT == 300 )
			throw " �ź���  ��û�� �ƴմϴ�.";
		if(nOUTPUT == 400 )
			throw " ��û�� ȸ��� �ź��� ȸ�簡 �����մϴ�.  ";
		/*if(nOUTPUT == 500 )
		throw "������ �����ܾ��� �����ϴ�. �����Ͻð� �����ϼ��� ";
		if(nOUTPUT == 600 )
		throw " ����ȸ���� ������� �����ϴ�.  ";*/


		

		MessageBox("�ش� ���� �ź��Ͽ����ϴ�", "Ȯ��" , MB_ICONINFORMATION);
		
		LinkRefreshList();
	}
	catch(char *e)
	{
		MessageBox(e , "Ȯ��" , MB_ICONINFORMATION);
	}
	catch(CString s)
	{
		MessageBox(s, "Ȯ��" , MB_ICONINFORMATION);
	}
	

}

void CShareReportRateDlg6::OnBnClickedAcceptBtn()
{
	try{

		if(m_SettingReport.GetSelectedCount()<= 0	)
			throw "�ź��� �׸��� �������ּ���";

		CMyXTPGridRecord *pRecord = m_SettingReport.GetSelectedRecord(0);
		long nModifynRequestCompany = pRecord->GetItemDataLong4();
		long nState = pRecord->GetItemDataInt();

		if( !(nState == NEW_APPLY || nState == MODIFY_RATE )  )
			throw "�����Ͻ� �׸��� �ƴմϴ�. ";

		if( nModifynRequestCompany ==  m_ci.m_nShareCode1  )
			throw "�ڻ簡 ����(��û)�Ͻ� �׸��̿� ������ �ȵǸ� ������ư�� ���� �����Ͽ� �ּ���.";

		long nOtherCompany = pRecord->GetItemDataLong();
		long nID = pRecord->GetItemDataLong2();

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "delete_consignment_accpt_company2011" );
		pCmd.AddParameter( m_ci.GetShareCode1());
		pCmd.AddParameter(nOtherCompany);				
		pCmd.AddParameter(m_ui.strName);
		pCmd.AddParameter(m_ui.nCompany);
		pCmd.AddParameter(m_ui.nWNo);
		pCmd.AddParameter(nID);

		CMkParameter *pParOUTPUT = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
		if(!pCmd.Execute()) return;	

		int nOUTPUT = 0;
		pParOUTPUT->GetValue(nOUTPUT);

		if(nOUTPUT == 100 )
			throw "�ش�õ��� ����Ǿ� �ִ� ��ü�� �ֽ��ϴ�. ";
		if(nOUTPUT == 300 )
			throw " ������ ��û�� �ƴմϴ�.";
		if(nOUTPUT == 400 )
			throw " ��û�� ȸ���� ������ �ƴ϶� ���Ұ��� ";
		/*if(nOUTPUT == 500 )
		throw "������ �����ܾ��� �����ϴ�. �����Ͻð� �����ϼ��� ";
		if(nOUTPUT == 600 )
		throw " ����ȸ���� ������� �����ϴ�.  ";*/




		MessageBox("�ش� ���� �����Ͽ����ϴ�", "Ȯ��" , MB_ICONINFORMATION);

		LinkRefreshList();
	}
	catch(char *e)
	{
		MessageBox(e , "Ȯ��" , MB_ICONINFORMATION);
	}
	catch(CString s)
	{
		MessageBox(s, "Ȯ��" , MB_ICONINFORMATION);
	}

}
