// AddGroupMemberDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "AddGroupMemberDlg.h"
#include "CustomerPage11.h"


// CAddGroupMemberDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAddGroupMemberDlg, CMyDialog)
CAddGroupMemberDlg::CAddGroupMemberDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAddGroupMemberDlg::IDD, pParent)
	, m_strSearch(_T(""))
	, m_dtStart(COleDateTime::GetCurrentTime())
	, m_dtEnd(COleDateTime::GetCurrentTime())
{
}

CAddGroupMemberDlg::~CAddGroupMemberDlg()
{
}

void CAddGroupMemberDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_SearchEdit);
	DDX_Control(pDX, IDC_MIDWORD_CHECK, m_chkMidSearch);
	DDX_Control(pDX, IDC_START_DTP, m_dtpStart);
	DDX_Control(pDX, IDC_END_DTP, m_dtpEnd);
	DDX_Control(pDX, IDC_TERM_STATIC, m_stcTerm);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);
	DDX_Control(pDX, IDC_SEARCH_COMBO, m_cmbSearch);
	DDX_Control(pDX, IDC_CUSTOMER_LIST, m_lstCustomer);
	DDX_Text(pDX, IDC_SEARCH_EDIT, m_strSearch);
	DDX_DateTimeCtrl(pDX, IDC_START_DTP, m_dtStart);
	DDX_DateTimeCtrl(pDX, IDC_END_DTP, m_dtEnd);
	DDX_Control(pDX, IDC_SEARCH_BTN, m_btnSearch);
}


BEGIN_MESSAGE_MAP(CAddGroupMemberDlg, CMyDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_CUSTOMER_LIST, OnReportItemDblClick)
	ON_BN_CLICKED(IDC_SEARCH_BTN, OnBnClickedSearchBtn)
	ON_CBN_SELCHANGE(IDC_SEARCH_COMBO, OnCbnSelchangeSearchCombo)
	ON_BN_CLICKED(IDC_INCUDE_BTN, OnBnClickedIncudeBtn)
END_MESSAGE_MAP()


void CAddGroupMemberDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CXTPGridSelectedRows *pRows = m_lstCustomer.GetSelectedRows();
	if(pRows == NULL) return;

	long nCNo = m_lstCustomer.GetItemDataLong(pRows->GetAt(0)->GetRecord()->GetIndex());

	CCustomerPage11::OpenCustomerDlgByCNo(nCNo);	
}
// CAddGroupMemberDlg 메시지 처리기입니다.

void CAddGroupMemberDlg::OnBnClickedSearchBtn()
{
	RefreshCustomer();
}

BOOL CAddGroupMemberDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	GetDesktopWindow();
	m_btnDate.InitDateButton(&m_dtpStart, &m_dtpEnd);

	m_cmbSearch.SetCurSel(2);

	m_lstCustomer.SetExtendedStyle(0);
	m_lstCustomer.AddHeader(0,TRUE,"", "고객No", 50 );
	m_lstCustomer.AddHeader(1,TRUE,"", "그룹명", 80 );
	m_lstCustomer.AddHeader(2,TRUE,"", "상호명", 130 );
	m_lstCustomer.AddHeader(3,TRUE,"", "부서", 70 );
	m_lstCustomer.AddHeader(4,TRUE,"", "담당자", 70 );
	m_lstCustomer.AddHeader(5,TRUE,"", "전화1", 80 );
	//m_lstCustomer.AddHeader(6,TRUE,"", "핸드폰", 80 );
	m_lstCustomer.AddHeader(6,TRUE,"", "기준동", 70 );
	m_lstCustomer.AddHeader(7,TRUE,"", "위치정보", 50 );
	
	m_lstCustomer.m_bHeader = TRUE;
	
    m_lstCustomer.Populate();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}



void CAddGroupMemberDlg::ViewSearchEdit()
{
	m_SearchEdit.ShowWindow(SW_SHOW);
	m_chkMidSearch.ShowWindow(SW_SHOW);

	m_dtpStart.ShowWindow(SW_HIDE);
	m_dtpEnd.ShowWindow(SW_HIDE);
	m_stcTerm.ShowWindow(SW_HIDE);
	m_btnDate.ShowWindow(SW_HIDE);
}

void CAddGroupMemberDlg::ViewOrder()
{
	m_SearchEdit.ShowWindow(SW_HIDE);
	m_chkMidSearch.ShowWindow(SW_HIDE);

	m_dtpStart.ShowWindow(SW_SHOW);
	m_dtpEnd.ShowWindow(SW_SHOW);
	m_stcTerm.ShowWindow(SW_SHOW);
	m_btnDate.ShowWindow(SW_SHOW);
}


void CAddGroupMemberDlg::OnCbnSelchangeSearchCombo()
{
	switch(m_cmbSearch.GetCurSel())
	{
	case 0:
		ViewSearchEdit();
		break;
	case 1:
		ViewSearchEdit();
		break;
	case 2:
		ViewSearchEdit();
		break;
	case 3:
		ViewSearchEdit();
		break;
	case 4:
		ViewSearchEdit();
		break;	
	case 5:
		ViewSearchEdit();
		break;	
	case 6:
		ViewOrder();
		break;
	default:
		break;
	}	
}

void CAddGroupMemberDlg::RefreshCustomer()
{
	UpdateData();
	CString strMobile, strTel1, strCompany, strDepart, strName,strDong,strLocation;
	long	nCNo, nGNo,nID,nDisCount, nItem = 0;
	long nPreCNo = -1;
	// 0 전화번호;1고객번호 2 법인명(상호); 3 부서명; 4 담당자; 5 등록일; 6 오더일자
	m_lstCustomer.DeleteAllItem();
	if(m_strSearch.IsEmpty()) 
		return;

	if(m_strSearch.GetLength() == 0 || m_cmbSearch.GetCurSel() == 1 && m_strSearch == "일반")
	{
		MessageBox("검색단어가 없거나 법인명 검색시 일반은 검색이 불가 합니다.");
		return;
	}

	CMkCommand pCmd(m_pMkDb, "search_customer_group_1");
	CMkRecordset pRs(m_pMkDb);
	pCmd.AddParameter(m_cmbSearch.GetCurSel());
	pCmd.AddParameter(::GetCurBranchInfo()->nCustomerTable);    
	pCmd.AddParameter(m_strSearch);
	pCmd.AddParameter(m_chkMidSearch.GetCheck());
	pCmd.AddParameter(m_dtStart);
	pCmd.AddParameter(m_dtEnd);

	if(!pRs.Execute(&pCmd)) return;

	while(!pRs.IsEOF())
	{	
		pRs.GetFieldValue("nCNo", nCNo);
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("sCompany", strCompany);
		pRs.GetFieldValue("sDepart", strDepart);
		pRs.GetFieldValue("sName", strName);
		pRs.GetFieldValue("sTel1", strTel1);
		pRs.GetFieldValue("sMobile", strMobile);
		pRs.GetFieldValue("sDong", strDong);
		pRs.GetFieldValue("sLocation", strLocation);
		pRs.GetFieldValue("nDisCount", nDisCount);
		pRs.GetFieldValue("nGNo", nGNo);

		strTel1 = GetDashPhoneNumber(strTel1);
		strMobile = GetDashPhoneNumber(strMobile);

		if(nCNo == nPreCNo)
			nID = 0;

		m_lstCustomer.MyAddItem(::RemoveZero(::GetStringFromLong(nID))); 
		m_lstCustomer.MyAddItem(m_cg.GetGroupData(nGNo) == NULL? "" : m_cg.GetGroupData(nGNo)->strGroupName);
		m_lstCustomer.MyAddItem(strCompany);
		m_lstCustomer.MyAddItem(strDepart);
		m_lstCustomer.MyAddItem(strName);
		m_lstCustomer.MyAddItem(strTel1);
		//m_lstCustomer.MyAddItem(strMobile);
		m_lstCustomer.MyAddItem(strDong);
		m_lstCustomer.MyAddItem(strLocation);

		m_lstCustomer.InsertItemDataLong(nCNo);
		m_lstCustomer.InsertItemDataLong2(nGNo);
		m_lstCustomer.EndItem();

		nPreCNo = nCNo;

		pRs.MoveNext();
		nItem++;
	}

	pRs.Close();
	m_lstCustomer.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_lstCustomer.Populate();
}

void CAddGroupMemberDlg::OnBnClickedIncudeBtn()
{
	((CCustomerPage11*)m_pParentWnd)->AddGroupMember();
}

BOOL CAddGroupMemberDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if(pMsg->hwnd == m_btnSearch.GetSafeHwnd())
		{
			OnBnClickedSearchBtn();
		}
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}
