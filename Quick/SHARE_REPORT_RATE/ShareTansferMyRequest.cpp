// ShareTansferMyRequest.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareTansferMyRequest.h"
#include "ShareReportMyRequestDetailDlg.h"


// CShareTansferMyRequest 대화 상자입니다.

IMPLEMENT_DYNAMIC(CShareTansferMyRequest, CMyDialog)
CShareTansferMyRequest::CShareTansferMyRequest(CWnd* pParent /*=NULL*/)
	: CMyDialog(CShareTansferMyRequest::IDD, pParent)
	, m_dtFromValue(COleDateTime::GetCurrentTime())
	, m_dtToValue(COleDateTime::GetCurrentTime())
{
}

CShareTansferMyRequest::~CShareTansferMyRequest()
{
}

void CShareTansferMyRequest::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtFromValue);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtToValue);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
}


BEGIN_MESSAGE_MAP(CShareTansferMyRequest, CMyDialog)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST, OnCustomdrawList)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnNMDblclkList)
END_MESSAGE_MAP()


// CShareTansferMyRequest 메시지 처리기입니다.

BOOL CShareTansferMyRequest::OnInitDialog()
{
	CMyDialog::OnInitDialog();


	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 

	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS | LVS_NOSORTHEADER);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES);

	m_List.InsertColumn(0, "순번", LVCFMT_LEFT , 40);
	m_List.InsertColumn(1, "요청회사", LVCFMT_LEFT  , 90);
	m_List.InsertColumn(2, "사유", LVCFMT_LEFT  , 150);
	m_List.InsertColumn(3, "상태", LVCFMT_LEFT  , 70);
	m_List.InsertColumn(4, "요청일", LVCFMT_LEFT  , 80);
	m_List.InsertColumn(5, "요청금액", LVCFMT_LEFT  , 70);
	m_List.InsertColumn(6, "입금날짜", LVCFMT_LEFT  , 80);
	m_List.InsertColumn(7, "입금금액", LVCFMT_LEFT  , 70);
	m_List.InsertColumn(8, "받은메세지", LVCFMT_LEFT  , 150);

	m_dtFrom.SetFormat("yyyy-MM-dd HH:00");
	m_dtTo.SetFormat("yyyy-MM-dd HH:00");

	m_DateBtn.InitDateButton((CDateTimeCtrl*)&m_dtFrom, (CDateTimeCtrl*)&m_dtTo);
	m_DateBtn.OnMenuToday();

	Refresh();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CShareTansferMyRequest::Refresh()
{
	UpdateData(true);
	m_List.DeleteAllItems();

    CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_transfer_my_request");

    pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFromValue);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtToValue);

	if(!pRs.Execute(&pCmd)) return;

	CString sMemo, sReceiveMessage, strFormat;
	long nID, nToCompany, nRequestCharge, nReceiveCharge, nState;
    COleDateTime dtRequest, dtReceive;

	for(int i = 0 ; i < pRs.GetRecordCount(); i++)
	{ 
        pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("nToCompany", nToCompany);
		pRs.GetFieldValue("sMemo", sMemo);
		pRs.GetFieldValue("dtRequest", dtRequest);
		pRs.GetFieldValue("nRequestCharge", nRequestCharge);
		pRs.GetFieldValue("dtReceive", dtReceive);
		pRs.GetFieldValue("nReceiveCharge", nReceiveCharge);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("sReceiveMessage", sReceiveMessage);

		strFormat.Format("%d", i);
		m_List.InsertItem(i,strFormat);
		m_List.SetItemText(i, 1, m_ci.GetName(nToCompany));
		m_List.SetItemText(i, 2, sMemo);
		m_List.SetItemText(i, 3, ReturnType(nState));
		m_List.SetItemText(i, 4, dtRequest.Format("%m-%d %H:%M"));

		strFormat.Format("%d원", nRequestCharge);
		m_List.SetItemText(i, 5, strFormat);

		if(nState == 2 || nState == 4) //정상종료 
		{
			m_List.SetItemText(i, 6, dtReceive.Format("%m-%d %H:%M"));

			strFormat.Format("%d원", nReceiveCharge);
			m_List.SetItemText(i, 7, strFormat);
		}
		else
		{
			m_List.SetItemText(i, 6, "");
			m_List.SetItemText(i, 7, "");
		}

		m_List.SetItemText(i, 8, sReceiveMessage);

		pRs.MoveNext();
	}
}

CString CShareTansferMyRequest::ReturnType(int ntype)
{
    if(ntype == 1)
		return "입금대기중";
	else if(ntype == 2)
		return "입금완료";
	else if(ntype == 4) //사용자거절
		return "거절";
	else
		return "일주일경과"; //3이 일주일이 경과하여 자동 취소 됨
}


void CShareTansferMyRequest::OnCustomdrawList ( NMHDR* pNMHDR, LRESULT* pResult )
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
		//
		if(m_List.GetItemText(pLVCD->nmcd.dwItemSpec, 3) == "입금대기중")
			crBkgnd = RGB(245,245,220);
		else if(m_List.GetItemText(pLVCD->nmcd.dwItemSpec, 3) == "일주일경과"
				|| m_List.GetItemText(pLVCD->nmcd.dwItemSpec, 3) == "거절")
			crBkgnd = RGB(245,220,245);
		else
			crBkgnd = RGB(220,245,245);


		crText =RGB(0,0,0);

		pLVCD->clrText = crText;
		pLVCD->clrTextBk = crBkgnd;

		// Tell Windows to paint the control itself.
		*pResult = CDRF_DODEFAULT;
	}
}


void CShareTansferMyRequest::OnBnClickedRefreshBtn()
{
	Refresh();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CShareTansferMyRequest::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	int index = m_List.GetNextItem(-1, LVNI_SELECTED);

	if(index == -1) return;

	CShareReportMyRequestDetailDlg pDlg;

	CString SeDate, ReDate, SeMoney, ReMoney, SeMemo, ReMemo;

	SeDate = m_List.GetItemText(index, 4);
	SeMoney = m_List.GetItemText(index, 5);
	SeMemo= m_List.GetItemText(index, 2);

	ReDate = m_List.GetItemText(index, 6);
	ReMoney = m_List.GetItemText(index, 7);
	ReMemo = m_List.GetItemText(index, 8);

	pDlg.m_SeDate = SeDate;
	pDlg.m_SeMoney = SeMoney;
	pDlg.m_SeMemo = SeMemo;
	pDlg.m_ReDate = ReDate;
	pDlg.m_ReMoney = ReMoney;
	pDlg.m_ReMemo = ReMemo;

	pDlg.DoModal();

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}
