// SearchDongInsungJibunDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "SearchDongInsungJibunDlg.h"

#define TIMER_EDIT_ABLE 1000

// CSearchDongInsungJibunDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSearchDongInsungJibunDlg, CDialog)

CSearchDongInsungJibunDlg::CSearchDongInsungJibunDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchDongInsungJibunDlg::IDD, pParent)
{
	m_nJibun1 = 0;
	m_nJibun2 = 0;
	m_nDongID = 0;
	m_nRoadID = 0;
	m_nRoadSubID = 0;
	m_strJibun = "";
	m_strRoad = "";
}

CSearchDongInsungJibunDlg::~CSearchDongInsungJibunDlg()
{
}

void CSearchDongInsungJibunDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_Control(pDX, IDC_JIBUN_LIST, m_lstJibun);
	DDX_Control(pDX, IDC_DONG_LIST, m_lstDong);
}


BEGIN_MESSAGE_MAP(CSearchDongInsungJibunDlg, CDialog)
	ON_BN_CLICKED(IDC_SEARCH_BUTTON, &CSearchDongInsungJibunDlg::OnBnClickedSearchButton)
	ON_NOTIFY(NM_DBLCLK, IDC_JIBUN_LIST, OnReportItemJibunDblClick)
	ON_NOTIFY(NM_DBLCLK, IDC_DONG_LIST, OnReportItemDongDblClick)
	ON_WM_TIMER()
END_MESSAGE_MAP()

void CSearchDongInsungJibunDlg::OnReportItemJibunDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	SelectJibun();
}

void CSearchDongInsungJibunDlg::OnReportItemDongDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	SelectDong();
}


// CSearchDongInsungJibunDlg 메시지 처리기입니다.

BOOL CSearchDongInsungJibunDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->wParam == VK_RETURN)
	{
		if(pMsg->message == WM_CHAR) 
		{				
			if(pMsg->hwnd == m_edtSearch.GetSafeHwnd()) 
			{	
				OnBnClickedSearchButton();
			}
			else if(pMsg->hwnd == m_lstJibun.GetSafeHwnd())  
			{	
				SelectJibun();
			}
			else if(pMsg->hwnd == m_lstDong.GetSafeHwnd()) 
			{	
				SelectDong();
			}
			else //CXTPGridInplaceEdit 으로 부터 오는 메세지다
			{
				m_lstJibun.SetFocus(); 
				SelectJibun();
			}

			return TRUE;
		}
	}


	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CSearchDongInsungJibunDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_lstJibun.InsertColumn(0, "시도", LVCFMT_LEFT, 60);
	m_lstJibun.InsertColumn(1, "군구", LVCFMT_LEFT, 60);
	m_lstJibun.InsertColumn(2, "동", LVCFMT_LEFT, 60);
	m_lstJibun.InsertColumn(3, "리(지번)", LVCFMT_LEFT, 60);
	m_lstJibun.SetGridColor(RGB(0xF0, 0xF0, 0xF0));
 
	m_lstJibun.GetColumns()->GetAt(0)->SetEditable(FALSE);
	m_lstJibun.GetColumns()->GetAt(1)->SetEditable(FALSE);
	m_lstJibun.GetColumns()->GetAt(2)->SetEditable(FALSE);
	m_lstJibun.GetColumns()->GetAt(3)->SetEditable(TRUE);
	m_lstJibun.AllowEdit(TRUE);

	m_lstJibun.Populate();

	m_lstDong.InsertColumn(0, "주소", LVCFMT_LEFT, 200);
	m_lstDong.InsertColumn(1, "", LVCFMT_LEFT, 60);
	m_lstDong.SetGridColor(RGB(0xF0, 0xF0, 0xF0));
	m_lstDong.Populate();

	RefreshList(m_strSearch);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSearchDongInsungJibunDlg::RefreshList(CString strSearch)
{
	m_lstJibun.DeleteAllItems();
	m_lstDong.DeleteAllItems();

	CString strSearch1 = "";
	CString strSearch2 = "";
	CString strSearch3 = "";

	if(strSearch.Right(2) != "길") strSearch1 = strSearch + "길"; 
	if(strSearch.Right(2) != "로") strSearch2 = strSearch + "로"; 
	if(strSearch.Right(2) != "번길") strSearch3 = strSearch + "번길"; 

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_dong_pos_search_1");
	cmd.AddParameter(strSearch);
	cmd.AddParameter(strSearch1);
	cmd.AddParameter(strSearch2);
	cmd.AddParameter(strSearch3);
	cmd.AddParameter(m_ci.m_bound.nPosX);
	cmd.AddParameter(m_ci.m_bound.nPosY);

	if(!rs.Execute(&cmd))
		return;

	long nID; long nItem = 0, nRoadID, nRoadSubID;
	CString strSido, strGugun, strDong, strLi;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nID", nID);
		rs.GetFieldValue("sSido", strSido);
		rs.GetFieldValue("sGugun", strGugun);
		rs.GetFieldValue("sDong", strDong);
		rs.GetFieldValue("sLi", strLi);
		rs.GetFieldValue("nRoadID", nRoadID);
		rs.GetFieldValue("nRoadSubID", nRoadSubID);


		m_lstJibun.InsertItem(i, strSido);
		m_lstJibun.SetItemText(i, 1, strGugun); 
		m_lstJibun.SetItemText(i, 2, strDong);
		m_lstJibun.SetItemText(i, 3, strLi);
		m_lstJibun.SetItemLong(i, nID);	
		m_lstJibun.SetItemLong2(i, nRoadID);
		m_lstJibun.SetItemLong3(i, nRoadSubID);

		if(strLi.IsEmpty())
		{
			m_lstDong.InsertItem(nItem, strSido + " " + strGugun + " " + strDong);
			m_lstDong.SetItemText(nItem, 1, "지도보기");
			m_lstDong.SetItemLong(nItem, nID);
			m_lstDong.SetItemLong(nItem, nRoadID);			
			m_lstDong.SetItemLong(nItem++, nRoadSubID);	
			m_lstDong.Populate();
		}

		rs.MoveNext();
	} 

	m_lstJibun.Populate(); 

	SetTimer(TIMER_EDIT_ABLE, 100, NULL);
}

void CSearchDongInsungJibunDlg::OnBnClickedSearchButton()
{
	CString strSearch; m_edtSearch.GetWindowText(strSearch);
	RefreshList(strSearch);
}

void CSearchDongInsungJibunDlg::SelectJibun()
{	
	CXTPGridRecord *pRecord = m_lstJibun.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	m_strJibun = pRecord->GetItem(3)->GetCaption(NULL);
	m_strRoad = pRecord->GetItem(2)->GetCaption(NULL);
	//m_strJibun = ((CXTPGridRecordItemText*)pRecord->GetItem(3))->GetValue();
	m_nDongID = m_lstJibun.GetItemLong(pRecord);
	m_nRoadID = m_lstJibun.GetItemLong2(pRecord);
	m_nRoadSubID = m_lstJibun.GetItemLong3(pRecord); 


	#define LI_OFFSET_START			2000000
	#define LI_OFFSET_END			2100000 // poidatamwe

	if(!m_strJibun.IsEmpty())
	{
		if(m_nDongID > LI_OFFSET_START && m_nDongID < LI_OFFSET_END)
			m_strRoad = pRecord->GetItem(3)->GetCaption(NULL);

		long nFind = m_strJibun.Find("-");
		if(nFind > 0)
		{
			CString strFirst = m_strJibun.Left(nFind);
			CString strSecond = m_strJibun.Mid(nFind + 1, m_strJibun.GetLength() - nFind + 1);

			m_nJibun1 = atoi(strFirst); 
			m_nJibun2 = atoi(strSecond);
		}
		else
		{
			m_nJibun1 = atoi(m_strJibun);
			m_nJibun2 = 0;
		}
	}
	else
	{
		m_nJibun1 = 0;
		m_nJibun2 = 0;
	}

	OnOK();
}

void CSearchDongInsungJibunDlg::SelectDong()
{
	CXTPGridRecord *pRecord = m_lstDong.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	m_nDongID = m_lstDong.GetItemLong(pRecord);
	m_nJibun1 = 0;
	m_nJibun2 = 0;
	m_strJibun = "";

	OnOK();
}

void CSearchDongInsungJibunDlg::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(nIDEvent); 

	if(nIDEvent == TIMER_EDIT_ABLE)
	{		
		if(m_lstJibun.GetRows()->GetCount() > 0)
		{
			CXTPGridRow *pRow = m_lstJibun.GetRows()->GetAt(0);
			XTP_REPORTRECORDITEM_ARGS args(&m_lstJibun, pRow, m_lstJibun.GetColumns()->GetAt(3));
			m_lstJibun.EditItem(&args);
		}
	}

	CDialog::OnTimer(nIDEvent);
}
