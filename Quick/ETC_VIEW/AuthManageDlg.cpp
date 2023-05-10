// AuthManage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "AuthManageDlg.h"




// CAuthManage 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAuthManageDlg, CMyDialog)
CAuthManageDlg::CAuthManageDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAuthManageDlg::IDD, pParent)
{
}

CAuthManageDlg::~CAuthManageDlg()
{
	DeleteObject(m_WhiteBrush);
}

void CAuthManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_AUTH_STRETCH_BTN, m_AuthStretchBtn);
	DDX_Control(pDX, IDC_AUTH_DELETE, m_AuthDeleteBtn);
}


BEGIN_MESSAGE_MAP(CAuthManageDlg, CMyDialog)
	ON_BN_CLICKED(IDC_AUTH_STRETCH_BTN, OnBnClickedAuthStretchBtn)
	ON_BN_CLICKED(IDC_AUTH_DELETE, OnBnClickedAuthDelete)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST, OnCustomdrawList)
END_MESSAGE_MAP()


// CAuthManage 메시지 처리기입니다.

void CAuthManageDlg::Refresh()
{
	m_List.DeleteAllItems();

	int nRcpType = 10;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_auth_manage");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);

	CMkParameter *pPar = pCmd.AddParameter(typeInt, typeOutput, sizeof(int), 0);

	if(!pRs.Execute(&pCmd)) return;

	pPar->GetValue(nRcpType);

	if(nRcpType == 100)
	{
		MessageBox("통합권한이 없습니다", "확인", MB_ICONERROR);
		OnCancel();
	}
	else if(nRcpType == 1000)
	{
		MessageBox("관리자가 아닙니다", "확인", MB_ICONERROR);
		OnCancel();
	}

	long nCompany, nClientNo, nID, nExpiration;
	CString strHostName, strID, strPhone, strExtIp;
	COleDateTime dtFirstAuth, dtLastAuth, dtExpiration;

	for(int i = 0 ; i < pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nClientNo", nClientNo);
		pRs.GetFieldValue("sHostName", strHostName);
		pRs.GetFieldValue("sID", strID);
		pRs.GetFieldValue("sPhone", strPhone);
		pRs.GetFieldValue("sExtIp", strExtIp);
		pRs.GetFieldValue("dtFirstAuth", dtFirstAuth);
		pRs.GetFieldValue("dtLastAuth", dtLastAuth);
		pRs.GetFieldValue("dtExpiration", dtExpiration);
		pRs.GetFieldValue("nExpiration", nExpiration);
		pRs.GetFieldValue("nID", nID);

		m_List.InsertItem(i,m_ci.GetBranchName(nCompany));

		CString sClientNo;
		sClientNo.Format("%d", nClientNo);
		m_List.SetItemText(i, 1, sClientNo);
		m_List.SetItemText(i, 2, strHostName);
		m_List.SetItemText(i, 3, strID);
		m_List.SetItemText(i, 4, strPhone);
		m_List.SetItemText(i, 5, strExtIp);
		m_List.SetItemText(i, 6, dtFirstAuth.Format("%y-%m-%d %H:%M"));
		m_List.SetItemText(i, 7, dtLastAuth.Format("%y-%m-%d %H:%M"));
		m_List.SetItemText(i, 8, dtExpiration.Format("%y-%m-%d %H:%M"));

		sClientNo.Format("%d일", nExpiration);
		m_List.SetItemText(i, 9, sClientNo);

		sClientNo.Format("%d", nID);
		m_List.SetItemText(i, 10, sClientNo);
		m_List.SetItemLong(i, nID);

		pRs.MoveNext();
		m_List.Populate();
	}
}

BOOL CAuthManageDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_WhiteBrush = CreateSolidBrush(RGB(255,255,255));

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 

	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS | LVS_NOSORTHEADER);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES);

	m_List.InsertColumn(0, "회사명", LVCFMT_LEFT, 80);
	m_List.InsertColumn(1, "PC번호", LVCFMT_LEFT, 50);
	m_List.InsertColumn(2, "호스트네임", LVCFMT_LEFT, 80);
	m_List.InsertColumn(3, "아이디", LVCFMT_LEFT, 80);
	m_List.InsertColumn(4, "인증폰", LVCFMT_LEFT, 90);
	m_List.InsertColumn(5, "IP", LVCFMT_LEFT, 95);
	m_List.InsertColumn(6, "첫인증", LVCFMT_LEFT, 95);
	m_List.InsertColumn(7, "마지막인증", LVCFMT_LEFT, 95);
	m_List.InsertColumn(8, "인증만료", LVCFMT_LEFT, 95);
	m_List.InsertColumn(9, "남은기간", LVCFMT_LEFT, 60);
	m_List.InsertColumn(10, "nID", LVCFMT_LEFT, 0);

	Refresh();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAuthManageDlg::OnBnClickedAuthStretchBtn()
{
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	if(pRows == NULL || pRows->GetCount() < 1) 
	{	
		MessageBox("연장 할 피시를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	//POSITION pos =;// = m_List.GetFirstSelectedItemPosition();
	//index = m_List.GetNextSelectedItem(pos);
	int nFirst = 1, nCount = 0;
	
	CString strMessage;	
	
	for(int i=0; i<pRows->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();
		//index = m_List.GetNextSelectedItem(pos);
		//if(index == -1 )
		//	continue;

		int nID = m_List.GetItemLong(pRecord);
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "update_stretch_AuthDate");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);

		if(!pRs.Execute(&pCmd)) return;
		nCount++;
		pRs.Close();		
		
	}
	if(nCount > 0 )
	{
		strMessage.Format("피시 %d 대의 연장기간이 현재로부터 두달 연장되었습니다", nCount);	
		MessageBox(strMessage, "연장처리", MB_ICONINFORMATION);
		Refresh();	
	}
	
	

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CAuthManageDlg::OnBnClickedAuthDelete()
{

	int index = m_List.GetNextItem(-1, LVNI_SELECTED);

	if(index == -1) 
	{	
		MessageBox("삭제 할 피시를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CString strPc;
	CString strMessage;
	strPc = m_List.GetItemText(index,1);

	strMessage.Format("피시번호 %s번의 인증이 삭제됩니다  \n\n             삭제하시겠습니까?", strPc);

	if(MessageBox(strMessage, "확인", MB_OKCANCEL) == IDOK)
	{
		int nID = _ttoi(m_List.GetItemText(index, 10));

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "delete_Auth");

		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), _ttoi(strPc));
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), _ttoi(m_List.GetItemText(index, 10)));

		if(!pRs.Execute(&pCmd)) return;

		pRs.Close();

		Refresh();	
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CAuthManageDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	GetClientRect(&rect);

	dc.SelectStockObject(NULL_PEN);
	dc.Rectangle(rect);
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CMyDialog::OnPaint()을(를) 호출하지 마십시오.
}

HBRUSH CAuthManageDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CAuthManageDlg::OnCustomdrawList ( NMHDR* pNMHDR, LRESULT* pResult )
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

		crText = RGB(0, 0, 0);

		CString sDay = m_List.GetItemText((int)pLVCD->nmcd.dwItemSpec, 9);
		sDay.Replace("일", "");
		
	
		if(_ttoi(sDay) < 2 )
			crBkgnd =RGB(255, 0, 0);
		else if(_ttoi(sDay) < 7 )
			crBkgnd =RGB(255, 200, 200);
		else 
			crBkgnd =RGB(255, 255, 255);
		/*
		if ( 0 == pLVCD->iSubItem )
		{
		crText = RGB(255,255,255);
		crBkgnd = RGB(255,0,0);
		}
		else if ( 1 == pLVCD->iSubItem )
		{
		crText = RGB(255,255,255);
		crBkgnd = RGB(0,255,0);
		}
		else
		{
		crText = RGB(255,255,255);
		crBkgnd = RGB(0,0,255);
		}
		*/
		// Store the colors back in the NMLVCUSTOMDRAW struct.
		pLVCD->clrText = crText;
		pLVCD->clrTextBk = crBkgnd;

		// Tell Windows to paint the control itself.
		*pResult = CDRF_DODEFAULT;
	}
}