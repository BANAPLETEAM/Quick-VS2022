// SearchDongInsungDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "SearchDongInsungDlg.h"
#include "RcpDlg.h"
#include "CustomerDlg.h"
#include "SearchPOIDlg.h"

// CSearchDongInsungDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSearchDongInsungDlg, CDialog)

CSearchDongInsungDlg::CSearchDongInsungDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchDongInsungDlg::IDD, pParent)
{
	m_nOkType = -1;
	m_pDetailPOI = NULL;
	m_nCurNaverID = 0;
}

CSearchDongInsungDlg::~CSearchDongInsungDlg()
{
}

void CSearchDongInsungDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DONG_LIST, m_lstDong);
	DDX_Control(pDX, IDC_CUSTOMER_LIST, m_lstCustomer);
	DDX_Control(pDX, IDC_POI_LIST, m_lstPoi);
}

BEGIN_MESSAGE_MAP(CSearchDongInsungDlg, CDialog)
	ON_MESSAGE(WM_USER + 999, OnRecvWebRecord)
	ON_NOTIFY(NM_DBLCLK, IDC_DONG_LIST, OnReportItemDongDblClick)
	ON_NOTIFY(NM_DBLCLK, IDC_CUSTOMER_LIST, OnReportItemCustomerDblClick)
	ON_NOTIFY(NM_DBLCLK, IDC_POI_LIST, OnReportItemPoiDblClick)
	ON_NOTIFY(NM_CLICK, IDC_POI_LIST, OnReportItemPoiClick)
END_MESSAGE_MAP()

BOOL CSearchDongInsungDlg::OnInitDialog()
{ 
	CDialog::OnInitDialog();

	SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);

	m_lstDong.InsertColumn(0, "시도", LVCFMT_LEFT, 70);
	m_lstDong.InsertColumn(1, "군구", LVCFMT_LEFT, 70);
	m_lstDong.InsertColumn(2, "동", LVCFMT_LEFT, 70);
	m_lstDong.InsertColumn(3, "리", LVCFMT_LEFT, 70);
	m_lstDong.GetPaintManager()->SetColumnStyle(xtpReportColumnFlat); 
	m_lstDong.SetGridColor(RGB(0xF0, 0xF0, 0xF0));
	m_lstDong.Populate();

	m_lstCustomer.InsertColumn(0,"고객명",LVCFMT_LEFT,135);
	m_lstCustomer.InsertColumn(1,"부서명",LVCFMT_LEFT,95);	
	m_lstCustomer.InsertColumn(2,"담당/직위",LVCFMT_LEFT,100);
	m_lstCustomer.InsertColumn(3,"전화번호1",LVCFMT_LEFT,70);
	m_lstCustomer.InsertColumn(4,"전화번호2",LVCFMT_LEFT,70);
	m_lstCustomer.InsertColumn(5,"거래",LVCFMT_LEFT,40);
	m_lstCustomer.InsertColumn(6,"기준동",LVCFMT_LEFT,60);
	m_lstCustomer.InsertColumn(7,"위치",LVCFMT_LEFT,280);
	m_lstCustomer.GetPaintManager()->SetColumnStyle(xtpReportColumnFlat); 
	m_lstCustomer.SetGridColor(RGB(0xF0, 0xF0, 0xF0));
	m_lstCustomer.Populate();

	m_lstCustomer.SetDrawCount(TRUE);

	m_lstPoi.InsertColumn(0, "상호", LVCFMT_LEFT, 120);
	m_lstPoi.InsertColumn(1, "전화번호", LVCFMT_LEFT, 80);
	m_lstPoi.InsertColumn(2, "주소", LVCFMT_LEFT, 170);
	m_lstPoi.InsertColumn(3, "", LVCFMT_LEFT, 50);
	m_lstPoi.GetPaintManager()->SetColumnStyle(xtpReportColumnFlat); 
	m_lstPoi.SetGridColor(RGB(0xF0, 0xF0, 0xF0));
	m_lstPoi.Populate(); 

	//CSearchPOIDlg::m_Naver.ThreadRefresh(m_strSearch, this, CSearchPOIDlg::GetNextNaverUID(), FALSE, 0);
 
	RefreshList(); 
	m_lstDong.SetFocus();
	
	return TRUE;
}

void CSearchDongInsungDlg::RefreshList()
{
	RefreshDongList();
	RefreshCustomerList();
	RefreshPoiList();
}

void CSearchDongInsungDlg::RefreshDongList()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_dong_pos_search");
	cmd.AddParameter(m_strSearch);
	cmd.AddParameter(m_ci.m_bound.nPosX);
	cmd.AddParameter(m_ci.m_bound.nPosY);

	if(!rs.Execute(&cmd))
		return;
  
	long nID;
	CString strSido, strGugun, strDong, strLi;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nID", nID);
		rs.GetFieldValue("sSido", strSido);
		rs.GetFieldValue("sGugun", strGugun);
		rs.GetFieldValue("sDong", strDong);
		rs.GetFieldValue("sLi", strLi);

		m_lstDong.InsertItem(i, strSido);
		m_lstDong.SetItemText(i, 1, strGugun); 
		m_lstDong.SetItemText(i, 2, strDong);
		m_lstDong.SetItemText(i, 3, strLi);
		m_lstDong.SetItemLong(i, nID);	

		rs.MoveNext();
	} 

	m_lstDong.Populate();
}

void CSearchDongInsungDlg::RefreshCustomerList()
{
	UINT nSearchType;
	CString strKeyWord;

	if(!CRcpDlg::MakeSearchQuery(m_strSearch, strKeyWord, &nSearchType)) return;

	CMkCommand cmd(m_pMkDb, "search_customer_2011_10_like_insung");
	CMkRecordset rs(m_pMkDb);

	if(nSearchType == ST_COMPANY) 
		nSearchType++;

	cmd.AddParameter(typeLong, typeInput, sizeof(long), (long)nSearchType);
	cmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCustomerTable);
	cmd.AddParameter(typeString, typeInput, strKeyWord.GetLength(), strKeyWord);
	cmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_ci.m_bSearchFourNumberWithUID);
	cmd.AddParameter(typeBool, typeInput, sizeof(BOOL), 0);

	if(!rs.Execute(&cmd)) return;


	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		ST_CUSTOMER_INFO *pc = new ST_CUSTOMER_INFO;

		COleDateTime dtPRDate;
		CCustomerDlg::GetPcInfo(&rs, pc, dtPRDate, TRUE);

		m_lstCustomer.InsertItem(i, pc->strCompany);
		m_lstCustomer.SetItemText(i, 1, pc->strDepart);
		m_lstCustomer.SetItemText(i, 2, pc->strName);
		m_lstCustomer.SetItemText(i, 3, pc->strMobile);
		m_lstCustomer.SetItemText(i, 4, pc->strTel2);

		CString strTemp = "";
		if(pc->bCredit == 1) strTemp = "신용";
		else if(pc->bCredit == 2) strTemp = "송금";
		else if(pc->bCredit == 3) strTemp = "카드";

		m_lstCustomer.SetItemText(i, 5, strTemp);
		m_lstCustomer.SetItemText(i, 6, pc->strDong);
		m_lstCustomer.SetItemText(i, 7, pc->strLocation);

		m_lstCustomer.SetItemData(i, (DWORD)pc);
		rs.MoveNext();
	}

	m_lstCustomer.Populate();
}

void CSearchDongInsungDlg::RefreshPoiList()
{

}


LONG CSearchDongInsungDlg::OnRecvWebRecord(WPARAM wParam, LPARAM lParam)
{ 
	if(wParam == 0)
	{
		QUERY_INFO *pQI = (QUERY_INFO*)lParam;

		if(pQI->strKeyword == m_strSearch)
		{
			m_lstPoi.Populate();
			m_lstDong.SetFocus();
		}

		delete pQI;
	}
	else
	{
		PORTAR_RESULT_RECORD *pRecord = (PORTAR_RESULT_RECORD*)wParam;

		if(pRecord->QI.nUID == m_nCurNaverID && pRecord->QI.strKeyword == m_strSearch)
		{
			long nItem = m_lstPoi.GetRecords()->GetCount();

			CString strName = pRecord->pSearchPOI->pPOI->GetPlaceName();
			CString strItem = pRecord->pSearchPOI->pPOI->GetRegionName() + " " + pRecord->pSearchPOI->strAddress;

			m_lstPoi.InsertItem(nItem, strName);
			m_lstPoi.SetItemText(nItem, 1, pRecord->pSearchPOI->pPOI->GetPhoneNumber());
			m_lstPoi.SetItemText(nItem, 2, strItem);
			m_lstPoi.SetItemText(nItem, 3, "동선택");
			m_lstPoi.SetItemData(nItem, (DWORD)pRecord->pSearchPOI);
		}
		else
		{
			delete pRecord->pSearchPOI;
		}

		delete pRecord;
	}

	return 0;
}

void CSearchDongInsungDlg::SelectDong()
{
	CXTPGridRecord *pRecord = m_lstDong.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	m_nOkType = 0;
	m_nDongID = m_lstDong.GetItemLong(pRecord);

	OnOK();
}

void CSearchDongInsungDlg::SelectCustomer()
{
	CXTPGridRecord *pRecord = m_lstCustomer.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	ST_CUSTOMER_INFO *pc = (ST_CUSTOMER_INFO*)m_lstCustomer.GetItemData(pRecord);

	m_nOkType = 1;
	m_nCNo = pc->nCNo;
	m_nTelID = pc->nTelID;

	OnOK();
}

void CSearchDongInsungDlg::SelectPoi()
{
	CXTPGridRecord *pRecord = m_lstPoi.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	m_nOkType = 2;

	CSearchPOI *pSearchPoi = (CSearchPOI*)m_lstPoi.GetItemData(pRecord);
	m_pDetailPOI = pSearchPoi->pPOI;
	m_strAddress = pSearchPoi->strAddress;

	OnOK();
}

void CSearchDongInsungDlg::OnReportItemDongDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	SelectDong();
}

void CSearchDongInsungDlg::OnReportItemCustomerDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	SelectCustomer();
}

void CSearchDongInsungDlg::OnReportItemPoiDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	SelectPoi();
}

void CSearchDongInsungDlg::OnReportItemPoiClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify =	(XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	CXTPGridRecord *pRecord = m_lstPoi.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	if(pItemNotify->pColumn->GetIndex() != 3)
		return;

	CSearchPOI *pSearchPoi = (CSearchPOI*)m_lstPoi.GetItemData(pRecord);
	m_pDetailPOI = pSearchPoi->pPOI;

	m_nOkType = 0;
	m_nDongID = pSearchPoi->pPOI->GetDongID();

	OnOK();
}

BOOL CSearchDongInsungDlg::IsLastRowSelect(CXTPGridControl *pControl)
{
	CXTPGridSelectedRows *pRows = pControl->GetSelectedRows();

	if(pRows == NULL) return FALSE;
	if(pRows->GetCount() == 0) return FALSE;

	long nIndex = pRows->GetAt(0)->GetIndex();

	if(pControl->GetRows()->GetCount() - 1 == nIndex)
		return TRUE;
	else 
		return FALSE;
}

BOOL CSearchDongInsungDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{	
		if(pMsg->wParam == VK_DOWN)
		{
			if(pMsg->hwnd == m_lstDong.GetSafeHwnd()) 
			{	
				if(IsLastRowSelect(&m_lstDong))
					m_lstCustomer.SetFocus();
			}
			else if(pMsg->hwnd == m_lstCustomer.GetSafeHwnd()) 
			{	
				if(IsLastRowSelect(&m_lstDong))
					m_lstPoi.SetFocus();
			}

		}
		else if(pMsg->wParam == VK_RETURN)
		{
			if(pMsg->hwnd == m_lstDong.GetSafeHwnd()) 
			{	
				SelectDong();
			}
			else if(pMsg->hwnd == m_lstCustomer.GetSafeHwnd()) 
			{	
				SelectCustomer();
			}
			else if(pMsg->hwnd == m_lstPoi.GetSafeHwnd()) 
			{	
				SelectPoi();
			}
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
