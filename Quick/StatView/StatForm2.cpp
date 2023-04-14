// Report4.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "StatForm2.h"

#include "POIData.h"

// CStatForm2 대화 상자입니다.



IMPLEMENT_DYNCREATE(CStatForm2, CMyFormView)
CStatForm2::CStatForm2()
	: CMyFormView(CStatForm2::IDD)
{
}

CStatForm2::~CStatForm2()
{
}

void CStatForm2::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_RefreshBtn);
}


BEGIN_MESSAGE_MAP(CStatForm2, CMyFormView)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_FROM, OnDtnDatetimechangeDatetimepickerFrom)
END_MESSAGE_MAP()


// CStatForm2 메시지 처리기입니다.

void CStatForm2::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();


	m_DateBtn.InitDateButton(&m_FromDT, &m_ToDT);
	m_DateBtn.OnMenuWeek();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 

	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS | LVS_NOSORTHEADER);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES);

	m_List.InsertColumn(0,"시간대",LVCFMT_LEFT,60);
	m_List.InsertColumn(1,"총건수",LVCFMT_RIGHT,100);
	m_List.InsertColumn(2,"접수",LVCFMT_RIGHT,55);
	m_List.InsertColumn(3,"완료",LVCFMT_RIGHT,55);
	m_List.InsertColumn(4,"취소",LVCFMT_RIGHT,55);
	m_List.InsertColumn(5,"출근수",LVCFMT_RIGHT,55);
	m_List.InsertColumn(6,"접속수",LVCFMT_RIGHT,55);
	m_List.InsertColumn(7,"총건수",LVCFMT_RIGHT,100);
	m_List.InsertColumn(8,"접수",LVCFMT_RIGHT,70);
	m_List.InsertColumn(9,"완료",LVCFMT_RIGHT,55);
	m_List.InsertColumn(10,"취소",LVCFMT_RIGHT,55);
	m_List.InsertColumn(11,"출근수",LVCFMT_RIGHT,55);
	m_List.InsertColumn(12,"접속수",LVCFMT_RIGHT,55);
	m_List.InsertColumn(13,"콜증감율",LVCFMT_RIGHT,70);

	SetResize(IDC_LIST1, sizingRightBottom);
	m_List.Populate();

}


typedef struct {
	long nCount;
	long nCount2;
	long nLastCount;
	long nLastCount2;
} COUNT_INFO;


void CStatForm2::RefreshList()
{
	CMyFormView::RefreshList();

	UpdateData(TRUE);
	m_List.DeleteAllItems();

	m_dtFrom.SetDateTime(m_dtFrom.GetYear(), m_dtFrom.GetMonth(), m_dtFrom.GetDay(), 9, 0, 0);


	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_hour_call_rider_compare");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), GetCurBranchInfo()->nDOrderTable);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);

	if(m_ui.strID.MakeLower() == "mksong" ||
		m_ui.strID.MakeLower() == "mksong2" ||
		m_ui.strID.MakeLower() == "mksong3" ||
		m_ui.strID.MakeLower() == "mksong4" ||
		m_ui.strID.MakeLower() == "mksong5" ||
		m_ui.strID.MakeLower() == "mksong6" ||
		m_ui.strID.MakeLower() == "mksong7") {
		pCmd.AddParameter(typeBool, typeInput, sizeof(int), 1);
	}
	else {
		pCmd.AddParameter(typeBool, typeInput, sizeof(int), 0);
	}

	if(!pRs.Execute(&pCmd)) return;

	int nItem = 0;
	COleDateTime dtToday = COleDateTime::GetCurrentTime();

	m_List.InsertItem(nItem, "비교");
	m_List.SetItemText(nItem, 1, m_dtFrom.Format("%m-%d(%a)"));
	m_List.SetItemText(nItem, 7, "금일");
	m_List.SetItemText(nItem++, 8, dtToday.Format("%m-%d(%a)"));

	COUNT_INFO ciTotal, ciRcp, ciComplete, ciCancel, ciLogin, ciConnRider;
	long nMatchCount = 0;
	char buffer[10];
	COleDateTime dtTime;

	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("dtTime", dtTime);
		pRs.GetFieldValue("nTotalCount", ciTotal.nCount);
		pRs.GetFieldValue("nCallStateRcp", ciRcp.nCount);
		pRs.GetFieldValue("nCallStateComplete", ciComplete.nCount);
		pRs.GetFieldValue("nCallStateCancel", ciCancel.nCount);
		pRs.GetFieldValue("nLoginRider", ciLogin.nCount);
		pRs.GetFieldValue("nConnectingRider", ciConnRider.nCount);
		pRs.GetFieldValue("nTotalCount2", ciTotal.nCount2);
		pRs.GetFieldValue("nCallStateRcp2", ciRcp.nCount2);
		pRs.GetFieldValue("nCallStateComplete2", ciComplete.nCount2);
		pRs.GetFieldValue("nCallStateCancel2", ciCancel.nCount2);
		pRs.GetFieldValue("nLoginRider2", ciLogin.nCount2);
		pRs.GetFieldValue("nConnectingRider2", ciConnRider.nCount2);

//		ciTotal.nSum += ciTotal.nCount;
//		ciRcp.nSum += ciRcp.nCount;
//		ciComplete.nSum += ciComplete.nCount;
//		ciCancel.nSum += ciCancel.nCount;
//		ciLogin.nSum += ciLogin.nCount;
//		ciConnRider.nSum += ciConnRider.nCount;

//		ciTotal.fGapPercent += (double)((ciTotal.nCount2 - ciTotal.nPreCount2) - (ciTotal.nCount - ciTotal.nPreCount) * 100.0 / max(ciTotal.nCount, 1);
//		ciRcp.fGapPercent += (double)(ciRcp.nCount2 - ciRcp.nCount) * 100.0 / max(ciRcp.nCount, 1);
//		ciComplete.fGapPercent += (double)(ciComplete.nCount2 - ciComplete.nCount) * 100.0 / max(ciComplete.nCount, 1);
//		ciCancel.fGapPercent += (double)(ciCancel.nCount2 - ciCancel.nCount) * 100.0 / max(ciCancel.nCount, 1);
//		ciLogin.fGapPercent += (double)(ciLogin.nCount2 - ciLogin.nCount) * 100.0 / max(ciLogin.nCount, 1);
//		ciConnRider.fGapPercent += (double)(ciConnRider.nCount2 - ciConnRider.nCount) * 100.0 / max(ciConnRider.nCount, 1);

		m_List.InsertItem(nItem, dtTime.Format("%H:%M"));		
		m_List.SetItemText(nItem, 1, ltoa(ciTotal.nCount, buffer, 10));
		m_List.SetItemText(nItem, 2, ltoa(ciRcp.nCount, buffer, 10));			
		m_List.SetItemText(nItem, 3, ltoa(ciComplete.nCount, buffer, 10));		
		m_List.SetItemText(nItem, 4, ltoa(ciCancel.nCount, buffer, 10));		
		m_List.SetItemText(nItem, 5, ltoa(ciLogin.nCount, buffer, 10));
		m_List.SetItemText(nItem, 6, ltoa(ciConnRider.nCount, buffer, 10));


		//아직까지 존재하는 것 
		if(ciTotal.nCount2 > -1)
		{
			nMatchCount++;						

			m_List.SetItemData(nItem, 1);
			m_List.SetItemText(nItem, 7, ltoa(ciTotal.nCount2, buffer, 10));
			m_List.SetItemText(nItem, 8, ltoa(ciRcp.nCount2, buffer, 10));			
			m_List.SetItemText(nItem, 9, ltoa(ciComplete.nCount2, buffer, 10));		
			m_List.SetItemText(nItem, 10, ltoa(ciCancel.nCount2, buffer, 10));		
			m_List.SetItemText(nItem, 11, ltoa(ciLogin.nCount2, buffer, 10));
			m_List.SetItemText(nItem, 12, ltoa(ciConnRider.nCount2, buffer, 10));

			CString strRate;
			strRate.Format("%0.1f%%", (double)(ciTotal.nCount2 - ciTotal.nCount) * 100 / max(ciTotal.nCount, 1));
			m_List.SetItemText(nItem++, 13, strRate);


			ciTotal.nLastCount = ciTotal.nCount;
			ciRcp.nLastCount = ciRcp.nCount;
			ciComplete.nLastCount = ciComplete.nCount;
			ciCancel.nLastCount = ciCancel.nCount;
			ciLogin.nLastCount = ciLogin.nCount;
			ciConnRider.nLastCount = ciConnRider.nCount;

			ciTotal.nLastCount2 = ciTotal.nCount2;
			ciRcp.nLastCount2 = ciRcp.nCount2;
			ciComplete.nLastCount2 = ciComplete.nCount2;
			ciCancel.nLastCount2 = ciCancel.nCount2;
			ciLogin.nLastCount2 = ciLogin.nCount2;
			ciConnRider.nLastCount2 = ciConnRider.nCount2;
		}
		else
		{
			long nTotal =0, nRcp =0, nComplete =0, nCancel = 0, nLogin = 0, nConnRider = 0;			
			nTotal =(!ciTotal.nLastCount) ? 0 : 
					(long)(ciTotal.nCount * (1 + (ciTotal.nLastCount2 - ciTotal.nLastCount) / (double)ciTotal.nLastCount));				
			nRcp =	(!ciRcp.nLastCount) ? 0 : 
					(long)(ciRcp.nCount * (1 + (ciRcp.nLastCount2 - ciRcp.nLastCount) / (double)ciRcp.nLastCount));
			nComplete = (!ciComplete.nLastCount) ? 0:
					(long)(ciComplete.nCount * (1 + (ciComplete.nLastCount2 - ciComplete.nLastCount) / (double)ciComplete.nLastCount  ));
			nCancel =(long) (nTotal - nComplete);
			nLogin =(!ciLogin.nLastCount) ? 0:
					(long)(ciLogin.nCount * (1 + (ciLogin.nLastCount2 - ciLogin.nLastCount) / (double)ciLogin.nLastCount));				
			nConnRider =(!ciConnRider.nLastCount) ? 0 :
					(long)(ciConnRider.nCount  *  (1 + (ciConnRider.nLastCount2 - ciConnRider.nLastCount) / (double)ciConnRider.nLastCount));
				
			// 0으로 나누는 버그수정
	
		/*	long nTotal = ciTotal.nCount * (1 + (ciTotal.nLastCount2 - ciTotal.nLastCount) / (long)ciTotal.nLastCount);
			long nRcp = ciRcp.nCount * (1 + (ciRcp.nLastCount2 - ciRcp.nLastCount) / (double)ciRcp.nLastCount);
			long nComplete = ciComplete.nCount * (1 + (ciComplete.nLastCount2 - ciComplete.nLastCount) / (double)ciComplete.nLastCount   );
			long nCancel = nTotal - nComplete;
			long nLogin = ciLogin.nCount * (1 + (ciLogin.nLastCount2 - ciLogin.nLastCount) / (double)ciLogin.nLastCount);
			long nConnRider = ciConnRider.nCount  *  (1 + (ciConnRider.nLastCount2 - ciConnRider.nLastCount) / (double)ciConnRider.nLastCount);*/

			m_List.SetItemData(nItem, 0);
			m_List.SetItemText(nItem, 7, ltoa(nTotal, buffer, 10));
			m_List.SetItemText(nItem, 8, ltoa(nRcp, buffer, 10));			
			m_List.SetItemText(nItem, 9, ltoa(nComplete, buffer, 10));		
			m_List.SetItemText(nItem, 10, ltoa(nCancel, buffer, 10));		
			m_List.SetItemText(nItem, 11, ltoa(nLogin, buffer, 10));
			m_List.SetItemText(nItem, 12, ltoa(nConnRider, buffer, 10));
			m_List.SetItemText(nItem++, 13, "<-예측");
		}

		pRs.MoveNext();
		
	}
	m_List.Populate();
}

//void CStatForm2::RefreshList()
//{
//	CMyFormView::RefreshList();
//
//	//CWaitCursor wait;
//	UpdateData(TRUE);
//
//	int _nCallStateRcp = 0;
//	int _nCallStateComplete = 0;
//	int _nCallStateCancel = 0;
//	int _nLoginRider = 0;
//	int _nConnectingRider = 0;
//
//	int _nCallStateRcp2 = 0;
//	int _nCallStateComplete2 = 0;
//	int _nCallStateCancel2 = 0;
//	int _nLoginRider2 = 0;
//	int _nConnectingRider2 = 0;
//
//
//	m_List.m_nPredItem = -1;
//	m_List.DeleteAllItems();
//
//	
//	CMkRecordset pRs(m_pMkDb);
//	CMkCommand pCmd(m_pMkDb, "select_hour_call_rider_compare_1");
//	pCmd.AddParameter(typeLong, typeInput, sizeof(int), GetCurBranchInfo()->nDOrderTable);
//	pCmd.AddParameter(typeBool, typeInput, sizeof(int), GetCurBranchInfo()->bIntegrated);
//	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
//	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);
//
//	if(m_ui.strID.MakeLower() == "mksong" ||
//		m_ui.strID.MakeLower() == "mksong2" ||
//		m_ui.strID.MakeLower() == "mksong3" ||
//		m_ui.strID.MakeLower() == "mksong4" ||
//		m_ui.strID.MakeLower() == "mksong5" ||
//		m_ui.strID.MakeLower() == "mksong6" ||
//		m_ui.strID.MakeLower() == "mksong7") {
//		pCmd.AddParameter(typeBool, typeInput, sizeof(int), 1);
//	}
//	else {
//		pCmd.AddParameter(typeBool, typeInput, sizeof(int), 0);
//	}
//
//	if(!pRs.Execute(&pCmd)) return;
//
//	int nItem = 0;
//	m_List.InsertItem(nItem, "비교");
//	m_List.SetItemText(nItem, 1, m_dtFrom.Format("%Y-%m-%d"));
//	m_List.SetItemText(nItem, 7, "금일");
//	nItem++;
//
//	CString sLastHHMM = "";
//	int		nLastCnt  = 0;
//	long	nLastTotalCount, nLastCallStateRcp, nLastCallStateComplete, nLastCallStateCancel, nLastLoginRider, nLastConnectingRider;
//	nLastCnt  = nLastTotalCount = nLastCallStateRcp = nLastCallStateComplete = nLastCallStateCancel = nLastLoginRider = nLastConnectingRider = 0;
//
//	COleDateTime dtTime;
//	long nTotalCount, nCallStateRcp, nCallStateComplete, nCallStateCancel, nLoginRider, nConnectingRider;
//	long nTotalCount2, nCallStateRcp2, nCallStateComplete2, nCallStateCancel2, nLoginRider2, nConnectingRider2;
//	char buffer[10];
//
//	while(!pRs.IsEOF())
//	{
//		pRs.GetFieldValue("dtTime", dtTime);
//		pRs.GetFieldValue("nTotalCount", nTotalCount);
//		pRs.GetFieldValue("nCallStateRcp", nCallStateRcp);
//		pRs.GetFieldValue("nCallStateComplete", nCallStateComplete);
//		pRs.GetFieldValue("nCallStateCancel", nCallStateCancel);
//		pRs.GetFieldValue("nLoginRider", nLoginRider);
//		pRs.GetFieldValue("nConnectingRider", nConnectingRider);
//		pRs.GetFieldValue("nTotalCount2", nTotalCount2);
//		pRs.GetFieldValue("nCallStateRcp2", nCallStateRcp2);
//		pRs.GetFieldValue("nCallStateComplete2", nCallStateComplete2);
//		pRs.GetFieldValue("nCallStateCancel2", nCallStateCancel2);
//		pRs.GetFieldValue("nLoginRider2", nLoginRider2);
//		pRs.GetFieldValue("nConnectingRider2", nConnectingRider2);
//		
//		nLastCnt++;		
//		if(m_List.m_nPredItem == -1 && nTotalCount2 == -1) m_List.m_nPredItem = nItem - 1;
//
//		if(nTotalCount2 > -1)
//		{
//			_nCallStateRcp		+= nCallStateRcp;
//			_nCallStateRcp2		+= nCallStateRcp2;
//
//			_nCallStateComplete += nCallStateComplete;
//			_nCallStateComplete2 += nCallStateComplete2;
//
//			_nCallStateCancel	+= nCallStateCancel;
//			_nCallStateCancel2	+= nCallStateCancel2;
//
//			_nLoginRider += nLoginRider;
//			_nLoginRider2 += nLoginRider2;
//
//			_nConnectingRider += _nConnectingRider;
//			_nConnectingRider2 += _nConnectingRider2;
//		}
//
///*
//		else
//		{
//			nCallStateRcp2 = nCallStateComplete2 = nCallStateCancel2 = 0;
//			if(_nCallStateRcp2 > 0)
//			{
//				nCallStateRcp2			=	nCallStateRcp * ((_nCallStateRcp2*1.0)/_nCallStateRcp);
//				nCallStateComplete2		=	nCallStateComplete * ((_nCallStateRcp2*1.0)/_nCallStateRcp);
//				nCallStateCancel2		=	nCallStateCancel * ((_nCallStateRcp2*1.0)/_nCallStateRcp);
//				nLoginRider2			=	nLoginRider * ((_nCallStateRcp2*1.0)/_nCallStateRcp);
//				nConnectingRider2		=	nConnectingRider * ((_nCallStateRcp2*1.0)/_nCallStateRcp);
//			}			
//		}
//*/
//		
//		if( dtTime.Format("%H:%M") != sLastHHMM  )
//		{
//			if( !sLastHHMM.IsEmpty() )
//			{
///*
//				nTotalCount = nLastTotalCount/nLastCnt;
//				nCallStateRcp = nLastCallStateRcp/nLastCnt; 
//				nCallStateComplete = nLastCallStateComplete/nLastCnt;
//				nCallStateCancel = nLastCallStateCancel/nLastCnt;
//				nLoginRider = nLastLoginRider/nLastCnt;
//				nConnectingRider = nLastConnectingRider/nLastCnt;
//*/
//
//				m_List.InsertItem(nItem, dtTime.Format("%H:%M"));		
//				m_List.SetItemText(nItem, 1, ltoa(nLastTotalCount/nLastCnt, buffer, 10));
//				m_List.SetItemText(nItem, 2, ltoa(nLastCallStateRcp/nLastCnt, buffer, 10));			
//				m_List.SetItemText(nItem, 3, ltoa(nLastCallStateComplete/nLastCnt, buffer, 10));		
//				m_List.SetItemText(nItem, 4, ltoa(nLastCallStateCancel/nLastCnt, buffer, 10));		
//				m_List.SetItemText(nItem, 5, ltoa(nLastLoginRider/nLastCnt, buffer, 10));
//				m_List.SetItemText(nItem, 6, ltoa(nLastConnectingRider/nLastCnt, buffer, 10));
//
//				if(nTotalCount2 < 0)
//				{
//					
//				/*	
//					if(_nCallStateRcp2 > 0)	nCallStateRcp2				=	atoi(m_List.GetItemText(nItem-1, 8)) * _nCallStateRcp/_nCallStateRcp2;
//					if(_nCallStateComplete2 > 0)	nCallStateComplete2		=	atoi(m_List.GetItemText(nItem-1, 9)) * _nCallStateComplete/_nCallStateComplete2;
//					if(_nCallStateCancel2 > 0)	nCallStateCancel2		=	atoi(m_List.GetItemText(nItem-1, 10)) * _nCallStateCancel/_nCallStateCancel2;
//					if(_nLoginRider2 > 0)	nLoginRider2			=	nLoginRider * _nLoginRider/_nLoginRider2;
//					if(_nConnectingRider2 > 0)	nConnectingRider2		=	nConnectingRider*_nConnectingRider/_nConnectingRider2;
//				*/	
//					if(_nCallStateRcp2 > 0)	nCallStateRcp2				=	atoi(m_List.GetItemText(nItem, 2)) * _nCallStateRcp2/_nCallStateRcp;
//					if(_nCallStateComplete2 > 0)	nCallStateComplete2		=	atoi(m_List.GetItemText(nItem, 3)) * _nCallStateComplete2/_nCallStateComplete;
//					if(_nCallStateCancel2 > 0)	nCallStateCancel2		=	atoi(m_List.GetItemText(nItem-1, 10)) * _nCallStateCancel2/_nCallStateCancel;
//					if(_nLoginRider2 > 0)	nLoginRider2			=	nLoginRider * _nLoginRider2/_nLoginRider;
//					if(_nConnectingRider2 > 0)	nConnectingRider2	=	nConnectingRider*_nConnectingRider2/_nConnectingRider;
//					if(_nCallStateComplete2 > 0)nTotalCount2		=   atoi(m_List.GetItemText(nItem, 1)) * _nCallStateComplete2/_nCallStateComplete;
//					nCallStateCancel2 = nTotalCount2	-	(nCallStateRcp2 + nCallStateComplete2 ) ;
//				}
//				m_List.SetItemText(nItem, 7, ltoa(nTotalCount2, buffer, 10));
//				m_List.SetItemText(nItem, 8, ltoa(nCallStateRcp2, buffer, 10));
//				m_List.SetItemText(nItem, 9, ltoa(nCallStateComplete2, buffer, 10));
//				m_List.SetItemText(nItem, 10, ltoa(nCallStateCancel2, buffer, 10));
//				m_List.SetItemText(nItem, 11, ltoa(nLoginRider2, buffer, 10));
//				m_List.SetItemText(nItem, 12, ltoa(nConnectingRider2, buffer, 10));
//				nItem++;
//			}
//
//			sLastHHMM = dtTime.Format("%H:%M");
//			nLastTotalCount = nTotalCount;
//			nLastCallStateRcp = nCallStateRcp; 
//			nLastCallStateComplete = nCallStateComplete;
//			nLastCallStateCancel = nCallStateCancel;
//			nLastLoginRider = nLoginRider;
//			nLastConnectingRider = nConnectingRider;
//			nLastCnt  =  0;
//		}
//		else
//		{
//			sLastHHMM = dtTime.Format("%H:%M");
//			nLastTotalCount += nTotalCount;
//			nLastCallStateRcp += nCallStateRcp; 
//			nLastCallStateComplete += nCallStateComplete;
//			nLastCallStateCancel += nCallStateCancel;
//			nLastLoginRider += nLoginRider;
//			nLastConnectingRider += nConnectingRider;
//		}
//		pRs.MoveNext();
//	}
//
//	if( nLastCnt > 0 )
//	{
//
//		nTotalCount = nLastTotalCount/nLastCnt;
//		nCallStateRcp = nLastCallStateRcp/nLastCnt; 
//		nCallStateComplete = nLastCallStateComplete/nLastCnt;
//		nCallStateCancel = nLastCallStateCancel/nLastCnt;
//		nLoginRider = nLastLoginRider/nLastCnt;
//		nConnectingRider = nLastConnectingRider/nLastCnt;
//
//		m_List.InsertItem(nItem, dtTime.Format("%H:%M"));		
//		m_List.SetItemText(nItem, 1, ltoa(nTotalCount, buffer, 10));
//		m_List.SetItemText(nItem, 2, ltoa(nCallStateRcp, buffer, 10));			
//		m_List.SetItemText(nItem, 3, ltoa(nCallStateComplete, buffer, 10));		
//		m_List.SetItemText(nItem, 4, ltoa(nCallStateCancel, buffer, 10));		
//		m_List.SetItemText(nItem, 5, ltoa(nLoginRider, buffer, 10));
//		m_List.SetItemText(nItem, 6, ltoa(nConnectingRider, buffer, 10));
//
//		if(_nCallStateRcp2 > 0)
//		{
//
//			if(_nCallStateRcp > 0)	nCallStateRcp2			=	nCallStateRcp * ((_nCallStateRcp2*1.0)/_nCallStateRcp);
//			if(_nCallStateComplete > 0)	nCallStateComplete2		=	nCallStateComplete * ((_nCallStateComplete2*1.0)/_nCallStateComplete);
//			if(_nCallStateCancel > 0)	nCallStateCancel2		=	nCallStateCancel * ((_nCallStateCancel2*1.0)/_nCallStateCancel);
//			if(_nLoginRider > 0)	nLoginRider2			=	nLoginRider * ((_nLoginRider2*1.0)/_nLoginRider);
//			if(_nConnectingRider > 0)	nConnectingRider2		=	nConnectingRider * ((_nConnectingRider2*1.0)/_nConnectingRider);
///*
//			nCallStateRcp2			=	nCallStateRcp * ((_nCallStateRcp2*1.0)/_nCallStateRcp);
//			nCallStateComplete2		=	nCallStateComplete * ((_nCallStateRcp2*1.0)/_nCallStateRcp);
//			nCallStateCancel2		=	nCallStateCancel * ((_nCallStateRcp2*1.0)/_nCallStateRcp);
//			nLoginRider2			=	nLoginRider * ((_nCallStateRcp2*1.0)/_nCallStateRcp);
//			nConnectingRider2		=	nConnectingRider * ((_nCallStateRcp2*1.0)/_nCallStateRcp);
//*/
//		}
//		nTotalCount2				=	nCallStateRcp2 + nCallStateComplete2 + nCallStateCancel2;
//
//		m_List.SetItemText(nItem, 7, ltoa(nTotalCount2, buffer, 10));
//		m_List.SetItemText(nItem, 8, ltoa(nCallStateRcp2, buffer, 10));
//		m_List.SetItemText(nItem, 9, ltoa(nCallStateComplete2, buffer, 10));
//		m_List.SetItemText(nItem, 10, ltoa(nCallStateCancel2, buffer, 10));
//		m_List.SetItemText(nItem, 11, ltoa(nLoginRider2, buffer, 10));
//		m_List.SetItemText(nItem, 12, ltoa(nConnectingRider2, buffer, 10));
//	}
//
//
//
//}

void CStatForm2::OnBnClickedRefreshBtn()
{
	RefreshList();
}


void CStatForm2::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CStatForm2::OnViewExcel()
{
	if(!POWER_CHECK(8900, "엑셀변환", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nDOrderTable, 605, m_List.GetItemCount());  
	CMyExcel::ToExcel(&m_List);
}


void CStatForm2::OnDtnDatetimechangeDatetimepickerFrom(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	
	COleDateTime dtFrom, dtTo;
	m_FromDT.GetTime(dtFrom);
	dtFrom = dtFrom + COleDateTimeSpan(1, 0, 0, 0);
	m_ToDT.SetTime(dtFrom);

	*pResult = 0;
}
