// AuthLogDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "AuthLogDlg.h"



// CAuthLogDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAuthLogDlg, CMyDialog)
CAuthLogDlg::CAuthLogDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAuthLogDlg::IDD, pParent)
	, m_From(COleDateTime::GetCurrentTime())
	, m_To(COleDateTime::GetCurrentTime())
{
}

CAuthLogDlg::~CAuthLogDlg()
{
	DeleteObject(m_WhiteBrush);
}

void CAuthLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_From);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_To);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_RefreshBtn);
}


BEGIN_MESSAGE_MAP(CAuthLogDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST, OnCustomdrawList)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CAuthLogDlg 메시지 처리기입니다.

BOOL CAuthLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_WhiteBrush = CreateSolidBrush(RGB(255,255,255));

	m_dtFrom.SetFormat("yyyy-MM-dd HH:00");
	m_dtTo.SetFormat("yyyy-MM-dd HH:00");

	m_DateBtn.InitDateButton((CDateTimeCtrl*)&m_dtFrom, (CDateTimeCtrl*)&m_dtTo);
	m_DateBtn.OnMenuToday();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 

	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS | LVS_NOSORTHEADER);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES);

	m_List.InsertColumn(0, "생성시점", LVCFMT_LEFT, 100);
	m_List.InsertColumn(1, "PC번호", LVCFMT_LEFT, 60);
	m_List.InsertColumn(2, "타입", LVCFMT_LEFT, 50);
	m_List.InsertColumn(3, "작업자", LVCFMT_LEFT, 80);
	m_List.InsertColumn(4, "소속회사", LVCFMT_LEFT, 80);
	m_List.InsertColumn(5, "적요", LVCFMT_LEFT, 350);
	
	m_List.Populate();
	Refresh();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAuthLogDlg::Refresh()
{
	m_List.DeleteAllItems();
	UpdateData(true);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_auth_log");

	int nReturn = 0;

	pCmd.AddParameter(typeInt, typeInput, sizeof(long), m_ui.nWNo);
	pCmd.AddParameter(typeInt, typeInput, sizeof(long), m_ui.nCompany);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_From);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_To);

	CMkParameter *pPar = pCmd.AddParameter(typeInt, typeOutput, sizeof(long), nReturn);

	if(!pRs.Execute(&pCmd)) return;

	pPar->GetValue(nReturn);

	if(nReturn == 100)
	{
		MessageBox("통합권한이 없습니다", "확인", MB_ICONERROR);
		OnCancel();
	}
	else if(nReturn == 1000)
	{
		MessageBox("관리자 아닙니다", "확인", MB_ICONERROR);
		OnCancel();
	}

	COleDateTime dtWork;
	int nType, nClientNo, nCompany;
	CString sWNo, sEtc;

	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("dtWork", dtWork);
		pRs.GetFieldValue("nType", nType);
		pRs.GetFieldValue("nClientNo", nClientNo);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("sWNo", sWNo);
		pRs.GetFieldValue("sEtc", sEtc);

		m_List.InsertItem(i, dtWork.Format("%y-%m-%d %H:%M:%S"));

		CString sClientNo;
		sClientNo.Format("%d", nClientNo);

		m_List.SetItemText(i, 1, sClientNo);
		m_List.SetItemText(i, 2, ReturnType(nType));
		m_List.SetItemText(i, 3, sWNo);
		m_List.SetItemText(i, 4, m_ci.GetName(nCompany));
		m_List.SetItemText(i, 5, sEtc);

		pRs.MoveNext();
		m_List.Populate();
	}
}


void CAuthLogDlg::OnCustomdrawList ( NMHDR* pNMHDR, LRESULT* pResult )
{

	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
	//CListCtrl plist = reinterpret_cast<CListCtrl*>pNMHDR;


	// Take the default processing unless we set this to something else below.
	*pResult = 0;

	// First thing - check the draw stage. If it's the control's prepaint
	// stage, then tell Windows we want messages for every item.

	if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		// This is the notification message for an item.  We'll request
		// notifications before each subitem's prepaint stage.

		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
	{
		// This is the prepaint stage for a subitem. Here's where we set the
		// item's text and background colors. Our return value will tell 
		// Windows to draw the subitem itself, but it will use the new colors
		// we set here.
		// The text color will cycle through red, green, and light blue.
		// The background color will be light blue for column 0, red for
		// column 1, and black for column 2.

		COLORREF crText, crBkgnd;
		if(m_List.GetItemText((int)pLVCD->nmcd.dwItemSpec, 2) == "신규")
			crBkgnd = RGB(255,255,230);
		else if(m_List.GetItemText((int)pLVCD->nmcd.dwItemSpec, 2) == "수정")
			crBkgnd = RGB(230,255,255);
		else
			crBkgnd =RGB(255,230,255);


		crText =RGB(0,0,0);


		// Store the colors back in the NMLVCUSTOMDRAW struct.
		pLVCD->clrText = crText;
		pLVCD->clrTextBk = crBkgnd;

		// Tell Windows to paint the control itself.
		*pResult = CDRF_DODEFAULT;
	}
}

void CAuthLogDlg::OnBnClickedRefreshBtn()
{
	Refresh();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

CString CAuthLogDlg::ReturnType(int nType)
{
	if(nType == 0)
		return "신규";
	else if(nType == 1)
		return "수정";
	else
		return "삭제";

}
void CAuthLogDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	GetClientRect(&rect);

	dc.SelectStockObject(NULL_PEN);
	dc.Rectangle(&rect);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CMyDialog::OnPaint()을(를) 호출하지 마십시오.
}

HBRUSH CAuthLogDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMyDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		hbr = m_WhiteBrush;  
	}

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
