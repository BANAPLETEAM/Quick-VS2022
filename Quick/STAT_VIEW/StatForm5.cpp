// StatForm9.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "StatForm5.h"

// CStatForm5

IMPLEMENT_DYNCREATE(CStatForm5, CMyFormView)

CStatForm5::CStatForm5()
: CMyFormView(CStatForm5::IDD)
{ 
}

CStatForm5::~CStatForm5()
{
}

void CStatForm5::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WORK_REPORT, m_wndReport);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);
}

BEGIN_MESSAGE_MAP(CStatForm5, CMyFormView)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CStatForm5 진단입니다.

#ifdef _DEBUG
void CStatForm5::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CStatForm5::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CStatForm5 메시지 처리기입니다.

void CStatForm5::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_btnDate.InitDateButton(&m_FromDT, &m_ToDT);
	m_btnDate.OnMenuWeek();

	SetResize(IDC_WORK_REPORT, sizingRightBottom);

	InitColumn();
}

void CStatForm5::InitColumn()
{
	UpdateData(TRUE);

	int nColumnCount = m_wndReport.GetColumns()->GetCount();
	for(int i=0;i < nColumnCount;i++)
	{
		CXTPGridColumns *pColums = m_wndReport.GetColumns();
		pColums->Remove(pColums->GetAt(0));
	}

	COleDateTimeSpan span = m_dtTo - m_dtFrom;

	CXTPGridColumn *pCol0 = m_wndReport.AddColumn(new CXTPGridColumn(0, "접수자", 80, FALSE));
	m_wndReport.InsertColumn(1, "타입",LVCFMT_LEFT, 40);

	pCol0->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol0->SetTreeColumn(1);

	COleDateTime dtFrom = m_dtFrom;

	for(int i=0; i<span.GetTotalDays(); i++)
	{
		CString strFormat;

		if(i == 0 || dtFrom.GetDay() == 1)		
			strFormat.Format("%d/%d", dtFrom.GetMonth(), dtFrom.GetDay());
		else	
			strFormat.Format("%d", dtFrom.GetDay());

		//if(dtFrom.GetDayOfWeek() == 6) // 금요일
		//	m_wndReport.m_nColor[nFridayCount++] = i + REAL_COUNT_COL;

		dtFrom = dtFrom + COleDateTimeSpan(1, 0, 0, 0);

		m_wndReport.InsertColumn(i+2, strFormat, LVCFMT_RIGHT, 40);
	}

	int a =m_wndReport.GetColumns()->GetCount();

	m_wndReport.InsertColumn(m_wndReport.GetColumns()->GetCount(), "최종합계", LVCFMT_RIGHT, 50);

	m_wndReport.Populate();
}


void CStatForm5::OnBnClickedRefreshBtn()
{
	RefreshList();	    	
}

void CStatForm5::RefreshList()
{
	CMyFormView::RefreshList();

	UpdateData(TRUE);

	m_mapWNo.clear();
	m_wndReport.DeleteAllItems();
	InitColumn();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_dorder_for_nWNo_stat");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);

	if(!pRs.Execute(&pCmd)) return;

	if(pRs.GetRecordCount() == 0) return;

	long nPreOption = 0;
	long nItemCount = 0;

	ST_WNO_DATE st;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nOption", st.nOption);

		if(nPreOption != st.nOption)
		{
			long nSaveOption = st.nOption;

			st.nOption = nPreOption;
			m_mapWNo[nItemCount++] = st;

			st.nOption = nSaveOption;
		}

		pRs.GetFieldValue("dtWorkMonth", st.strWorkDate);
		pRs.GetFieldValue("nWCompany", st.nWCompany);
		pRs.GetFieldValue("nWNo", st.nWNo);
		pRs.GetFieldValue("sWName", st.strWName);

		pRs.GetFieldValue("n1", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][1]);
		pRs.GetFieldValue("n2", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][2]);
		pRs.GetFieldValue("n3", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][3]);
		pRs.GetFieldValue("n4", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][4]);
		pRs.GetFieldValue("n5", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][5]);
		pRs.GetFieldValue("n6", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][6]);
		pRs.GetFieldValue("n7", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][7]);
		pRs.GetFieldValue("n8", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][8]);
		pRs.GetFieldValue("n9", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][9]);
		pRs.GetFieldValue("n10", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][10]);
		pRs.GetFieldValue("n11", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][11]);
		pRs.GetFieldValue("n12", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][12]);
		pRs.GetFieldValue("n13", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][13]);
		pRs.GetFieldValue("n14", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][14]);
		pRs.GetFieldValue("n15", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][15]);
		pRs.GetFieldValue("n16", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][16]);
		pRs.GetFieldValue("n17", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][17]);
		pRs.GetFieldValue("n18", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][18]);
		pRs.GetFieldValue("n19", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][19]);
		pRs.GetFieldValue("n20", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][20]);
		pRs.GetFieldValue("n21", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][21]);
		pRs.GetFieldValue("n22", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][22]);
		pRs.GetFieldValue("n23", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][23]);
		pRs.GetFieldValue("n24", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][24]);
		pRs.GetFieldValue("n25", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][25]);
		pRs.GetFieldValue("n26", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][26]);
		pRs.GetFieldValue("n27", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][27]);
		pRs.GetFieldValue("n28", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][28]);
		pRs.GetFieldValue("n29", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][29]);
		pRs.GetFieldValue("n30", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][30]);
		pRs.GetFieldValue("n31", st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][31]);

		int a = st.nDay[_ttoi(st.strWorkDate.Mid(4, 2))][1];

		nPreOption = st.nOption;

		pRs.MoveNext();
	}

	m_mapWNo[nItemCount++] = st;

	RefreshCount();
}

void CStatForm5::RefreshCount()
{
	long nRow = 0;
	long nCol = 1;
	long nColor = 0;

	char buffer[20];

	int nColumnCount = m_wndReport.GetColumns()->GetCount();

	MAP_WNO::iterator it;
	MAP_WNO::iterator itPre = m_mapWNo.end();

	for(it = m_mapWNo.begin(); it != m_mapWNo.end(); it++)
	{
		COleDateTime dtFrom; m_FromDT.GetTime(dtFrom);

		if(nRow == 0)
			m_wndReport.InsertItem(nRow, it->second.strWName + "(" + CString(itoa(it->second.nWNo, buffer, 10)) + ")");

		if(itPre != m_mapWNo.end())
		{
			if(itPre->second.nWNo == it->second.nWNo &&
				itPre->second.nWCompany == it->second.nWCompany)
			{
				m_wndReport.InsertItem(nRow, "");
			}
			else
			{		
				m_wndReport.InsertItem(nRow, it->second.strWName + "(" + CString(itoa(it->second.nWNo, buffer, 10)) + ")");
				nColor++;
			}
		}

		if(it->second.nOption == 0)
			m_wndReport.SetItemText(nRow, nCol++, "완료");
		else if(it->second.nOption == 1)
			m_wndReport.SetItemText(nRow, nCol++, "취소");
		else if(it->second.nOption == 2)
			m_wndReport.SetItemText(nRow, nCol++, "문의");
		else if(it->second.nOption == 3)
			m_wndReport.SetItemText(nRow, nCol++, "기타");
		else if(it->second.nOption == 4)
			m_wndReport.SetItemText(nRow, nCol++, "합계");
		else
			m_wndReport.SetItemText(nRow, nCol++, "알수업음");

		long nTotal = 0;

		for(int i=nCol; i<nColumnCount-1; i++)
		{
			m_wndReport.SetItemText(nRow, nCol++, itoa(it->second.nDay[dtFrom.GetMonth()][dtFrom.GetDay()], buffer, 10));
			nTotal += it->second.nDay[dtFrom.GetMonth()][dtFrom.GetDay()];
			dtFrom += COleDateTimeSpan(1, 0, 0, 0);
		}

		m_wndReport.SetItemText(nRow, nCol++, itoa(nTotal, buffer, 10));

		if(it->second.nOption == 4)
			m_wndReport.SetItemLong(nRow, 9999);
		else
			m_wndReport.SetItemLong(nRow, nColor);

		nRow++;
		nCol = 1;

		itPre = it;
	}

	m_wndReport.Populate();
}

void CStatForm5::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_wndReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	

}

void CStatForm5::OnViewExcel()
{
	if(!POWER_CHECK(8900, "엑셀변환", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nCompanyCode, 402, m_ui.nWNo, m_wndReport.GetItemCount());  
	CMyExcel::ToExcel(&m_wndReport);
}
