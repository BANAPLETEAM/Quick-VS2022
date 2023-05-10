// ShareTranferRequestDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareTranferRequestDlg.h"

#include "ShareReportRateDlg1.h"
#include "BranchReportTransferDlg.h"

#include "ShareReportTransferDlg.h"
#include "ShareTransferCancelDlg.h"
#include "ShareTransferRequestDetailDlg.h"

#include "LogiUtil.h"


// CShareTranferRequestDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CShareTranferRequestDlg, CMyDialog)
CShareTranferRequestDlg::CShareTranferRequestDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CShareTranferRequestDlg::IDD, pParent)
{
	m_nAbilityMoney = 0;
	m_pShareReportRateDlg1 = NULL;
	m_pBranchReportTransferDlg = NULL;
	m_nWeek = 1000;
	m_sSql = "";
}

CShareTranferRequestDlg::~CShareTranferRequestDlg()
{
}

void CShareTranferRequestDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
}


BEGIN_MESSAGE_MAP(CShareTranferRequestDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnNMDblclkList)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST, OnCustomdrawList)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnNMClickList)
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCRBUTTONDOWN()
END_MESSAGE_MAP()


// CShareTranferRequestDlg 메시지 처리기입니다.

void CShareTranferRequestDlg::OnBnClickedRefreshBtn()
{
	ReFresh();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CShareTranferRequestDlg::ReFresh()
{ 
	m_nAbilityMoney = LU->GetShareBalance(m_ci.m_nCompanyCode);
	m_List.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, m_sSql);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), m_nWeek);

	if(!pRs.Execute(&pCmd)) return;

	pPar->GetValue(m_nWeek);

	long nID, nCompany, nRequestCharge,  nGiveRider;
	COleDateTime dtRequest;
	CString sMemo;

	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("dtRequest", dtRequest);
		pRs.GetFieldValue("nRequestCharge", nRequestCharge);
		pRs.GetFieldValue("sMemo", sMemo);
		pRs.GetFieldValue("nGiveRider", nGiveRider); //1이면 이체와 동시에 기사에게 선입금 충전됨

		m_List.InsertItem(i, m_ci.GetName(nCompany));
		m_List.SetItemText(i, 1, dtRequest.Format("%m-%d %H:%M"));
		m_List.SetItemText(i, 2, ReturnString(nRequestCharge));
		m_List.SetItemText(i, 3, sMemo);
		m_List.SetItemText(i, 4, nGiveRider == 1 ? "충전" : "");
		m_List.SetItemText(i, 5, "이체");
		m_List.SetItemText(i, 6, "거절");

		CString str;

		str.Format("%d", nID);
		m_List.SetItemText(i, 7, str);
		str.Format("%d", nCompany);
		m_List.SetItemText(i, 8, str);

		pRs.MoveNext();
	}
}

CString CShareTranferRequestDlg::ReturnString(int nInt)
{
	CString str;
	str.Format("%d", nInt);

	if(str.GetLength() > 3)
	{
		str = str.Left(str.GetLength() - 3) + "," + str.Right(3);
	}

	str += "원";

	return str;
}

BOOL CShareTranferRequestDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 

	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS | LVS_NOSORTHEADER);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES);

	m_List.InsertColumn(0, "회사명", LVCFMT_LEFT, 80);
	m_List.InsertColumn(1, "요청일", LVCFMT_LEFT, 100);
	m_List.InsertColumn(2, "금액", LVCFMT_LEFT, 70);
	m_List.InsertColumn(3, "사유", LVCFMT_LEFT, 150);
	m_List.InsertColumn(4, "기사충전", LVCFMT_LEFT, 60);
	m_List.InsertColumn(5, "이체", LVCFMT_LEFT, 40);
	m_List.InsertColumn(6, "거절", LVCFMT_LEFT, 40);
	m_List.InsertColumn(7, "아이디", LVCFMT_LEFT, 0);
	m_List.InsertColumn(8, "nCompany", LVCFMT_LEFT, 0);

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	ReFresh();


	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(10, 10));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CShareTranferRequestDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	int index = m_List.GetNextItem(-1, LVNI_SELECTED);

	if(index == -1)
		return;

	CString sCompany = m_List.GetItemText(index, 0);
	CString sDate = m_List.GetItemText(index, 1);
	CString sCharge = m_List.GetItemText(index, 2);
	CString sMemo = m_List.GetItemText(index, 3);

	CShareTransferRequestDetailDlg pDlg;
	pDlg.m_sCompany = sCompany;
	pDlg.m_sDate = sDate;
	pDlg.m_sCharge = sCharge;
	pDlg.m_sMemo = sMemo;

	pDlg.DoModal();

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CShareTranferRequestDlg::OnCustomdrawList ( NMHDR* pNMHDR, LRESULT* pResult )
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
		crText = RGB(0,0,0);
		crBkgnd = RGB(255,255,255);

		if(m_List.GetItemText((long)pLVCD->nmcd.dwItemSpec, (long)pLVCD->iSubItem) == "이체" 
			|| m_List.GetItemText((long)pLVCD->nmcd.dwItemSpec, (long)pLVCD->iSubItem) == "거절" )
		{
			crText = RGB(0,0,255);
		}

		pLVCD->clrText = crText;
		pLVCD->clrTextBk = crBkgnd;

		// Tell Windows to paint the control itself.
		*pResult = CDRF_DODEFAULT;
	}
}

void CShareTranferRequestDlg::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMITEMACTIVATE * pNMIA = (NMITEMACTIVATE*) pNMHDR;

	int index = m_List.GetNextItem(-1, LVNI_SELECTED);

	if(index == -1) return;
	
	if(	pNMIA->iSubItem == 5)
	{
		if(m_ui.nRole != 0)
		{
			MessageBox("관리자 아이디로 로그인하여 이체를하세요", "확인", MB_ICONINFORMATION);
			return;
		}

        CShareReportTransferDlg pDlg;

		CString str = m_List.GetItemText(pNMIA->iItem, 8);

		pDlg.m_nToCompany = _ttoi(str);
		pDlg.m_nAbilityMoney = m_nAbilityMoney;
		
		str = m_List.GetItemText(pNMIA->iItem, 2);
		str.Replace("원", "");
		str.Replace(",", "");

		pDlg.m_sMoneyR = str;

		CString memo = m_List.GetItemText(pNMIA->iItem, 3);
		pDlg.m_sMemoR = memo;

		pDlg.m_pShareTransferRequestDlg = this;
	//	pDlg.m_pShareReportRateDlg1 = m_pShareReportRateDlg1;
	//	pDlg.InitRequest();

		if(pDlg.DoModal() == IDOK)
		{
			if(m_pShareReportRateDlg1 != NULL)
				m_pShareReportRateDlg1->RefreshMoney();
			else if (m_pBranchReportTransferDlg != NULL)
				m_pBranchReportTransferDlg->RefreshMoney();
		}
	}

	if(	pNMIA->iSubItem == 6)
	{
		if(m_ui.nRole != 0)
		{
			MessageBox("관리자 아이디로 로그인하여 청구를하세요", "확인", MB_ICONINFORMATION);
			return;
		}

		CString str = m_List.GetItemText(pNMIA->iItem, 7);

		CShareTransferCancelDlg pDlg;
		pDlg.m_pParent = this;
		pDlg.m_nID = _ttoi(str);
		pDlg.DoModal();
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}

void CShareTranferRequestDlg::FinishRequest(int nReceive, CString sMemo)
{
	
	int index = m_List.GetNextItem(-1, LVNI_SELECTED);
	CString sID = m_List.GetItemText(index, 7);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_transfer_request_1");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), _ttoi(sID));
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nReceive);
	pCmd.AddParameter(typeString, typeInput, sMemo.GetLength(), sMemo);

	CString sFillCharge = m_List.GetItemText(index, 4);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), sFillCharge == "충전" ? 1 : 0);

    pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
	pCmd.AddParameter(typeLong, typeInput, m_ui.strName.GetLength(), m_ui.strName);

	if(!pRs.Execute(&pCmd)) return;

	ReFresh();
}


BOOL CShareTranferRequestDlg::PreCreateWindow(CREATESTRUCT& cs)
{
	//cs.style |= WS_CLIPCHILDREN|WS_CLIPSIBLINGS;

	return CMyDialog::PreCreateWindow(cs);
}

BOOL CShareTranferRequestDlg::PreTranslateMessage(MSG* pMsg)
{
	if((pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)  && m_nWeek == ONE_WEEK_AFTER)
	{
		MessageBox("15일이 경과한 이체 요청 내역이 있습니다", "확인", MB_ICONERROR);
		ReFresh();
		return true;
	}
		
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CShareTranferRequestDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	if(nHitTest == HTCLOSE && m_nWeek == ONE_WEEK_AFTER)
	{
		MessageBox("15일이 경과한 이체 요청 내역이 있습니다", "확인", MB_ICONERROR);		
		ReFresh();
	}
	else
		CMyDialog::OnNcLButtonDown(nHitTest, point);
}

void CShareTranferRequestDlg::OnNcRButtonDown(UINT nHitTest, CPoint point)
{
	if(m_nWeek == ONE_WEEK_AFTER)
		return;
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CMyDialog::OnNcRButtonDown(nHitTest, point);
}
