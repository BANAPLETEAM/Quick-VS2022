// RiderTraceMapDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "RiderTraceMapDlg.h"
#include "MyMkMessenger.h"
#include "RiderMapNormalForm.h"

// CRiderTraceMapDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRiderTraceMapDlg, CMyDialog)

CRiderTraceMapDlg::CRiderTraceMapDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRiderTraceMapDlg::IDD, pParent)
{
	m_nCompany = 0;
	m_nRNo = 0;
}

CRiderTraceMapDlg::~CRiderTraceMapDlg()
{
	if(LU->GetMessenger())
		LU->GetMessenger()->DeleteRiderPosWnd(this);
}

void CRiderTraceMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RIDER_MAP_CTRL, m_wndMap);
	DDX_Control(pDX, IDC_ORDER_LIST, m_lstOrder);
}


BEGIN_MESSAGE_MAP(CRiderTraceMapDlg, CMyDialog)
	ON_WM_SIZE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CRiderTraceMapDlg 메시지 처리기입니다.
BOOL CRiderTraceMapDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CBitmap bitmap;
	CImageList imageList;
	bitmap.LoadBitmap(IDB_LIST);
	imageList.Create(16,18,ILC_COLOR24 | ILC_MASK,1,1); 
	imageList.Add(&bitmap,RGB(0, 255, 255));
	m_lstOrder.SetImageList(&imageList,LVSIL_SMALL);
	m_lstOrder.GetPaintManager()->m_strNoItems = "";
	m_lstOrder.InsertColumn(0, "시간",LVCFMT_LEFT, 55);
	m_lstOrder.InsertColumn(1, "의뢰인",LVCFMT_LEFT, 67);
	m_lstOrder.InsertColumn(2, "출발지",LVCFMT_LEFT, 63);
	m_lstOrder.InsertColumn(3, "도착지",LVCFMT_LEFT, 63);
	m_lstOrder.InsertColumn(4, "요금",LVCFMT_RIGHT, 50);
	m_lstOrder.EnableToolTips(FALSE);
	m_lstOrder.ShowWindow(FALSE);

	m_wndMap.SetRcpView(LU->GetRcpView());

	m_wndMap.CreateWait();
	m_wndMap.SetMapLevel(AfxGetApp()->GetProfileInt("RiderTraceMapDlg", "MapLevel", 8));

	LU->GetMessenger()->AddRecvRiderPosWnd(this);
	LU->GetMessenger()->SetRecvRiderPosMsg(TRUE);

	MoveRider();
	OnSize(0xFF, 0, 0);

	UpdateOrderStatic(); 
	
	return TRUE;
}

void CRiderTraceMapDlg::RefreshList()
{
	m_lstOrder.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_have_order");
	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(m_nRNo);
	if(pRs.Execute(&pCmd))
	{
		for(int i = 0; i < pRs.GetRecordCount(); i++)
		{
			long nCompany, nState, nCharge;
			COleDateTime dtState;
			CString strCName, strStart, strDest;

			pRs.GetFieldValue("nCompany", nCompany);
			pRs.GetFieldValue("nState", nState);
			pRs.GetFieldValue("dtState", dtState);
			pRs.GetFieldValue("sOName", strCName);
			pRs.GetFieldValue("sSDong", strStart);
			pRs.GetFieldValue("sDDong", strDest);
			pRs.GetFieldValue("nChargeSum", nCharge);

			if(!m_ci.IsChildCompany(nCompany))
				strCName = "타사오더";

			CRiderMapNormalForm::AddRiderHaveOrderToList(&m_lstOrder, i, dtState, nState, strCName, strStart, strDest, nCharge);

			pRs.MoveNext();
		}
	}
}

void CRiderTraceMapDlg::UpdateOrderStatic()
{
	RefreshList();

	CXTPGridRecords *pRecords = m_lstOrder.GetRecords();

	long nCount = pRecords->GetCount();

	long nDisplayCount = min(nCount, DISPLAY_ORDER_COUNT);

	for(int i=0; i<nDisplayCount; i++)
	{ 
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		//밑에꺼부터 0번임
		CXUIStaticText *pText = &m_wndMap.m_uistcOrder[nDisplayCount - i - 1];
		CXUIImage *pImage = &m_wndMap.m_uiimageOrder[nDisplayCount - i - 1];

		long nState = m_lstOrder.GetItemLong(pRecord);
		long nCharge = m_lstOrder.GetItemLong2(pRecord);

		CString strTemp; 
		strTemp.Format(" (%s)%s  %s  %s->%s %s", pRecord->GetItem(0)->GetCaption(NULL), 
			LF->GetStateString(nState),
			pRecord->GetItem(1)->GetCaption(NULL), 
			pRecord->GetItem(2)->GetCaption(NULL), 
			pRecord->GetItem(3)->GetCaption(NULL), 
			pRecord->GetItem(4)->GetCaption(NULL));

		pText->SetCaption(strTemp); 
		pText->SetVisible(TRUE); 
		pImage->SetVisible(TRUE);	
	}

	for(int i=nDisplayCount; i<DISPLAY_ORDER_COUNT; i++ ) 
	{  
		long nIndex = i;  
		CXUIStaticText *pText = &m_wndMap.m_uistcOrder[nIndex];
		CXUIImage *pImage = &m_wndMap.m_uiimageOrder[nIndex];

		pText->SetVisible(0);
		pImage->SetVisible(0);
	}
}

void CRiderTraceMapDlg::MoveRider()
{
	if(m_nCompany > 0)
		m_wndMap.SetTraceRider(m_nCompany, m_nRNo);
}

void CRiderTraceMapDlg::OnSize(UINT nType, int cx, int cy)
{
	if(nType != 0xFF)
		CMyDialog::OnSize(nType, cx, cy);

	if(m_wndMap.GetSafeHwnd())
	{
		CRect rc;
		GetClientRect(rc);
		m_wndMap.MoveWindow(rc);
	}
}


void CRiderTraceMapDlg::OnClose()
{
	AfxGetApp()->WriteProfileInt("RiderTraceMapDlg", "MapLevel", m_wndMap.GetMapLevel());
	CMyDialog::OnClose();
}

