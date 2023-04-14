// CorpOrderDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "CorpOrderDlg.h"



// CCorpOrderDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCorpOrderDlg, CMyDialog)
CCorpOrderDlg::CCorpOrderDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCorpOrderDlg::IDD, pParent)
{
}

CCorpOrderDlg::~CCorpOrderDlg()
{
}

void CCorpOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
}


BEGIN_MESSAGE_MAP(CCorpOrderDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST, OnCustomdrawList)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnNMClickList)
END_MESSAGE_MAP()


// CCorpOrderDlg 메시지 처리기입니다.

void CCorpOrderDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CCorpOrderDlg::RefreshList()
{
	m_List.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_corp_order");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
    
	if(!pRs.Execute(&pCmd)) return;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		char buffer[20];
		long nCompany, nTNo, nAgreeState;
		COleDateTime dt1;
		CString sPhone1, sStart, sDest, sCName, sFullName, sReplaceOrder;

		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nTNo", nTNo);
		pRs.GetFieldValue("dt1", dt1);
		pRs.GetFieldValue("sCName", sCName);
		pRs.GetFieldValue("sPhone1", sPhone1);
		pRs.GetFieldValue("sStart", sStart);
		pRs.GetFieldValue("sDest", sDest);
		pRs.GetFieldValue("FullName", sFullName);
		pRs.GetFieldValue("sReplaceOrder", sReplaceOrder);
		pRs.GetFieldValue("nAgreeState", nAgreeState);


		m_List.InsertItem(i, m_ci.GetBranchName(nCompany));
		m_List.SetItemText(i, 1, itoa(nTNo, buffer, 10));
		m_List.SetItemText(i, 2, dt1.Format("%m:%d %H:%M"));
		m_List.SetItemText(i, 3, sCName);
		m_List.SetItemText(i, 4, sPhone1);
		m_List.SetItemText(i, 5, sStart);
		m_List.SetItemText(i, 6, sDest);
		m_List.SetItemText(i, 7, sFullName);
		m_List.SetItemText(i, 8, sReplaceOrder);

		if(nAgreeState == 0)
			m_List.SetItemText(i, 9, "승인대기중");
		else if(nAgreeState == 1)
			m_List.SetItemText(i, 9, "변경요청");
		else if(nAgreeState == 2)
			m_List.SetItemText(i, 9, "변경함(대기중)");
		else // 3인경우
			m_List.SetItemText(i, 9, "승인");
        
		pRs.MoveNext();

	}

}

BOOL CCorpOrderDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 

	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS | LVS_NOSORTHEADER);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES);

	m_List.InsertColumn(0, "발주회사", LVCFMT_LEFT, 90);
	m_List.InsertColumn(1, "오더번호", LVCFMT_LEFT, 80);
	m_List.InsertColumn(2, "접수날짜", LVCFMT_LEFT, 100);
	m_List.InsertColumn(3, "고객명", LVCFMT_LEFT, 70);
	m_List.InsertColumn(4, "고객전화", LVCFMT_LEFT, 80);
	m_List.InsertColumn(5, "출발지", LVCFMT_LEFT, 70);
	m_List.InsertColumn(6, "도착지", LVCFMT_LEFT, 70);
	m_List.InsertColumn(7, "법인소속", LVCFMT_LEFT, 120);
	m_List.InsertColumn(8, "변경요청", LVCFMT_LEFT, 150);
	m_List.InsertColumn(9, "상태", LVCFMT_LEFT,80);

    RefreshList();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CCorpOrderDlg::OnCustomdrawList ( NMHDR* pNMHDR, LRESULT* pResult )
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
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
	{

		COLORREF crText, crBkgnd;
		//
		if(m_List.GetItemText(pLVCD->nmcd.dwItemSpec, pLVCD->iSubItem) == "변경요청")
		{
			crText = RGB(0, 0, 255);

		}
		else
			crText =RGB(0, 0, 0);


		crBkgnd =RGB(255,255,255);

		pLVCD->clrText = crText;
		pLVCD->clrTextBk = crBkgnd;

		// Tell Windows to paint the control itself.
		*pResult = CDRF_DODEFAULT;
	}
}
void CCorpOrderDlg::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	int index= m_List.GetNextItem(-1, LVNI_SELECTED);

	CString sState = m_List.GetItemText(index, 9);

	if(sState != "변경요청")
		return;

	CString sTNo = m_List.GetItemText(index, 1);

	CString msg = "접수번호(" + sTNo + ")를 변경요청 사항에 맞게 수정하셨습니까?";

	if(MessageBox(msg, "확인", MB_OKCANCEL) == IDOK)
	{
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "update_Corp_Order_Change");

		pCmd.AddParameter(typeLong, typeInput, sizeof(long), _ttoi(sTNo));

		if(!pRs.Execute(&pCmd))
			return;
		else
			RefreshList();

	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}
