// SimpleSearchDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SimpleSearchDlg.h"



// CSimpleSearchDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSimpleSearchDlg, CMyDialog)
CSimpleSearchDlg::CSimpleSearchDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSimpleSearchDlg::IDD, pParent)	
	, m_sTNo(_T(""))
{
	m_sCompany = "";
	m_sManager = "";
	m_sStart = "";
	m_sDCompany = "";
	m_sRName = "";
	m_sDest = "";
	m_nCompany = 0;
	m_bIntegrated = FALSE;
	m_nTNo = -1;
	m_nState = -1;
	m_sCName = "";
}

CSimpleSearchDlg::~CSimpleSearchDlg()
{

}

void CSimpleSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_SCOMPANY_EDIT, m_edtCompany);
	DDX_Control(pDX, IDC_SMANAGER_EDIT, m_edtManager);
	DDX_Control(pDX, IDC_SSTART_EDIT, m_edtStart);
	DDX_Control(pDX, IDC_SDCOMPANY_EDIT, m_edtDCompany);
	DDX_Control(pDX, IDC_SRIDERNAME_EDIT, m_edtRName);
	DDX_Control(pDX, IDC_SDEST_EDIT, m_edtDest);
	DDX_Control(pDX, IDC_NTNO_EDIT, m_edtNTNO);

	DDX_Control(pDX, IDC_BRANCH_STATIC, m_stcBranch);
	DDX_Control(pDX, IDC_SCOMPANY_STATIC, m_stcCompany);
	DDX_Control(pDX, IDC_SMANAGER_STATIC, m_stcManager);
	DDX_Control(pDX, IDC_SSTART_STATIC, m_stcStart);
	DDX_Control(pDX, IDC_SDCOMPANY_STATIC, m_stcDCompany);
	DDX_Control(pDX, IDC_SRIDER_STATIC, m_stcRName);
	DDX_Control(pDX, IDC_SDEST_STATIC, m_stcDest);
	DDX_Control(pDX, IDC_NTNO_STATIC, m_stcNTNO);

	DDX_Text(pDX, IDC_SCOMPANY_EDIT, m_sCompany);
	DDX_Text(pDX, IDC_SMANAGER_EDIT, m_sManager);
	DDX_Text(pDX, IDC_SSTART_EDIT, m_sStart);
	DDX_Text(pDX, IDC_SDCOMPANY_EDIT, m_sDCompany);
	DDX_Text(pDX, IDC_SRIDERNAME_EDIT, m_sRName);
	DDX_Text(pDX, IDC_SDEST_EDIT, m_sDest);
	DDX_Control(pDX, IDC_COMBO1, m_cmbBranch);
	
	DDX_Text(pDX, IDC_NTNO_EDIT, m_sTNo);
}


BEGIN_MESSAGE_MAP(CSimpleSearchDlg, CMyDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeCombo1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
END_MESSAGE_MAP()


// CSimpleSearchDlg 메시지 처리기입니다.

BOOL CSimpleSearchDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_edtCompany.SetFocus();


	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );//|LVS_EX_CHECKBOXES
	m_List.InsertColumn(0,"접수",LVCFMT_LEFT, 40);
	m_List.InsertColumn(1,"개별",LVCFMT_LEFT, 40);
	m_List.InsertColumn(2,"배차",LVCFMT_LEFT, 40);
	m_List.InsertColumn(3,"완료",LVCFMT_LEFT, 40);
	m_List.InsertColumn(4,"상태",LVCFMT_LEFT, 40);
	m_List.InsertColumn(5,"접수번호",LVCFMT_LEFT, 65);
	m_List.InsertColumn(6,"담당자",LVCFMT_LEFT, 55);
	m_List.InsertColumn(7,"출)고객명",LVCFMT_LEFT, 80);
	m_List.InsertColumn(8,"도)고객명",LVCFMT_LEFT, 80);
	m_List.InsertColumn(9,"출발동",LVCFMT_LEFT, 60);
	m_List.InsertColumn(10,"도착동",LVCFMT_LEFT, 60);
	m_List.InsertColumn(11,"기사명",LVCFMT_LEFT,55);
	m_List.InsertColumn(12,"금액",LVCFMT_RIGHT, 45);
	m_List.InsertColumn(13,"왕복",LVCFMT_LEFT, 40);
	m_List.InsertColumn(14,"차량",LVCFMT_LEFT, 40);
	m_List.InsertColumn(15,"지불",LVCFMT_LEFT, 40);	
	m_List.InsertColumn(16,"접수자",LVCFMT_LEFT, 50);	

	int nCurSel = 0;
	
	for(int i = 0; i < m_ba.GetCount(); i++)
	{
		CBranchInfo *bi = (CBranchInfo*)m_ba.GetAt(i);
		
		m_cmbBranch.InsertString(i,bi->strBranchName);
		m_cmbBranch.SetItemData(i, bi->nCompanyCode);
		if(bi->nCompanyCode == m_nCompany)
			nCurSel = i;
	}
	if(m_bIntegrated)
		m_cmbBranch.SetCurSel(0);
	else
		m_cmbBranch.SetCurSel(nCurSel);

	return TRUE;
}

BOOL CSimpleSearchDlg::PreTranslateMessage(MSG* pMsg)
{	
	if(pMsg->message == WM_KEYDOWN)
	{	
		if(pMsg->wParam == VK_RETURN)		
		{			
			switch(::GetDlgCtrlID(pMsg->hwnd))
			{
				case IDC_SCOMPANY_EDIT:
					RefreshList(1);
					return TRUE;
				
				case IDC_SMANAGER_EDIT:
					RefreshList(2);
					return TRUE;
				
				case IDC_SSTART_EDIT:
					RefreshList(3);
					return TRUE;
				
				case IDC_SDCOMPANY_EDIT:
					RefreshList(4);
					return TRUE;

				case IDC_SRIDERNAME_EDIT:
					RefreshList(5);
					return TRUE;

				case IDC_SDEST_EDIT:
					RefreshList(6);
					return TRUE;
			}
		}
	}
	
	return CMyDialog::PreTranslateMessage(pMsg);
}

void CSimpleSearchDlg::RefreshList(int nSearch)
{
	
	m_List.DeleteAllItems();
	CString sSearch = "";

	UpdateData();

	switch(nSearch)
	{
		case 1:
			sSearch = m_sCompany;
			break;
		case 2:
			sSearch = m_sManager;
			break;
		case 3:
			sSearch = m_sStart;
			break;
		case 4:
			sSearch = m_sDCompany;
			break;
		case 5:
			sSearch = m_sRName;
			break;
		case 6:
			sSearch = m_sDest;
			break;
		case 7:
			sSearch = m_sTNo;
			break;

	}
	if(sSearch.GetLength() <= 0)
	{	
		MessageBox("검색하실 내용을 입력하세요","확인", MB_ICONINFORMATION);
		return;
	}
	CWaitCursor wait;
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_today_orderlist_search");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_bIntegrated);	
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), nSearch);
	pCmd.AddParameter(typeString, typeInput, sSearch.GetLength(), sSearch);	

	if(!pRs.Execute(&pCmd)) return;

	COleDateTime dt0,dt1, dt2,dt3, dtFinal;
	CString sCName = "", sDName = "", sStart = "", sDest = "", sRName = "",sState = "",sManager = "";
	BOOL bDoc = FALSE;
	long nTotal = 0, nKDelivery = 0, nAPay = 0, nWNo = 0, nTNo = 0,nState = 0;
	
	int nCol = 1, nItem = 0;
	const char *szKDelMask[] = {"", "다마", "트럭", "봉고", "대리"};
	const char *szAPayMask[] = {"선불", "착불", "신용", "송금"};
	char buffer[15];

	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("dt0", dt0);
		pRs.GetFieldValue("dt1", dt1);
		pRs.GetFieldValue("dt2", dt2);
		pRs.GetFieldValue("dt3", dt3);
		pRs.GetFieldValue("dtFinal", dtFinal);
		pRs.GetFieldValue("nTNo", nTNo);
		pRs.GetFieldValue("sManager", sManager);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("sCName", sCName);
		pRs.GetFieldValue("sDName", sDName);
		pRs.GetFieldValue("sStart", sStart);
		pRs.GetFieldValue("sDest", sDest);
		pRs.GetFieldValue("sRName", sRName);
		pRs.GetFieldValue("cTotal", nTotal);
		pRs.GetFieldValue("bDoc", bDoc);
		pRs.GetFieldValue("nKDelivery", nKDelivery);
		pRs.GetFieldValue("nAPay", nAPay);
		pRs.GetFieldValue("nWNo", nWNo);		
		
		m_List.InsertItem(nItem, dt1.Format("%H:%M") );
		m_List.SetItemText(nItem, nCol++, dt2.Format("%H:%M"));
		m_List.SetItemText(nItem, nCol++, dt3.Format("%H:%M"));
		m_List.SetItemText(nItem, nCol++, dtFinal.Format("%H:%M"));
		m_List.SetItemText(nItem, nCol++, GetStateString(nState));
		m_List.SetItemText(nItem, nCol++, itoa(nTNo, buffer,10));
		m_List.SetItemText(nItem, nCol++, sManager);
		m_List.SetItemText(nItem, nCol++, sCName);
		m_List.SetItemText(nItem, nCol++, sDName);
		m_List.SetItemText(nItem, nCol++, sStart);
		m_List.SetItemText(nItem, nCol++, sDest);
		m_List.SetItemText(nItem, nCol++, sRName);
		m_List.SetItemText(nItem, nCol++, GetMyNumberFormat((int)nTotal));
		m_List.SetItemText(nItem, nCol++, bDoc ? "왕복" : "편도");
		m_List.SetItemText(nItem, nCol++, szKDelMask[nKDelivery]);		
		m_List.SetItemText(nItem, nCol++, szAPayMask[nAPay]);
		m_List.SetItemText(nItem, nCol++, itoa(nWNo, buffer, 10));

		m_List.SetItemData(nItem,nTNo);

		nItem++;
		nCol = 1;
		pRs.MoveNext();
	}
	
	pRs.Close();
	
}
void CSimpleSearchDlg::OnBnClickedButton1()
{
	OnCancel();
}

void CSimpleSearchDlg::OnCbnSelchangeCombo1()
{
	long nCompany = 0;
	if(m_cmbBranch.GetCount() > 1 && m_cmbBranch.GetCurSel() == 0)
		m_bIntegrated = 1;
	
	m_nCompany = (long)m_cmbBranch.GetItemData(m_cmbBranch.GetCurSel());
	
}

void CSimpleSearchDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0) {	

		m_nTNo = (long)m_List.GetItemData(nItem);
		CString sState = m_List.GetItemText(nItem,3);
		m_sCName = m_List.GetItemText(nItem,6);		

			 if(sState == "접수") m_nState = 10; 			
		else if(sState == "개별") m_nState = 11;			
		else if(sState == "발송") m_nState = 15;			
		else if(sState == "실패") m_nState = 20;			
		else if(sState == "배차") m_nState = 30;			
		else if(sState == "완료") m_nState = 35;			
		else if(sState == "취소") m_nState = 40;			
		else if(sState == "인터넷") m_nState = 2;			
		else if(sState == "현장") m_nState = 3;			
		else if(sState == "이동") m_nState = 5;			
		else if(sState == "대기") m_nState = 8;			
		else if(sState == "예약") m_nState = 9;			
		else if(sState == "공지") m_nState = 1;			
		else m_nState = -1;		

		OnOK();
	}
	*pResult = 0;
}
