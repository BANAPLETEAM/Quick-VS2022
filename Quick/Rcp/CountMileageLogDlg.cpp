// CountMileageLogDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "CountMileageLogDlg.h"
#include "CountMileageLogSubDlg.h"

// CCountMileageLogDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCountMileageLogDlg, CMyDialog)

CCountMileageLogDlg::CCountMileageLogDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCountMileageLogDlg::IDD, pParent)
{
	m_nCompany = 0;
	m_nCNo = 0;
	m_bFirst = TRUE;
}

CCountMileageLogDlg::~CCountMileageLogDlg()
{
	DeleteMapInfo();
}

void CCountMileageLogDlg::DeleteMapInfo()
{
	MAP_COUNT_MILE::iterator it;

	for(it = m_mapPhone.begin(); it != m_mapPhone.end(); it++)
	{
		ST_COUNT_MILE *st = it->second;

		if(st)
		{
			delete st;
			st = NULL;
		}
	}

	for(it = m_mapInternet.begin(); it != m_mapInternet.end(); it++)
	{
		ST_COUNT_MILE *st = it->second;

		if(st)
		{
			delete st;
			st = NULL;
		}
	}

	m_mapPhone.clear();
	m_mapInternet.clear();
}

void CCountMileageLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MILEAGE_LOG_LIST, m_List);
	DDX_Control(pDX, IDC_HELP_STATIC, m_stcHelp);
}


BEGIN_MESSAGE_MAP(CCountMileageLogDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CCountMileageLogDlg::OnBnClickedRefreshBtn)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CCountMileageLogDlg 메시지 처리기입니다.

void CCountMileageLogDlg::PreInitDialog()
{
	CMyDialog::PreInitDialog();
}

BOOL CCountMileageLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CRect rtSTATIC_OPTION;
	this->GetDlgItem(IDC_STATIC_OPTION)->GetWindowRect(rtSTATIC_OPTION);
	this->ScreenToClient(rtSTATIC_OPTION);
	this->GetDlgItem(IDC_STATIC_OPTION)->ShowWindow(SW_HIDE);

	LU->CreateFormViewTabControl(this, &m_wndTabControl, rtSTATIC_OPTION);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CCountMileageLogSubDlg), "전화접수", 0);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CCountMileageLogSubDlg), "인터넷접수", 0);

	m_List.InsertColumn(0, "날짜", LVCFMT_LEFT, 45);
	m_List.InsertColumn(1, "금액", LVCFMT_LEFT, 50);
	m_List.InsertColumn(2, "적요", LVCFMT_LEFT, 120);
	m_List.Populate();

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CCountMileageLogDlg::RefreshList()
{
	RefreshCharge();
	RefreshMap();
}

void CCountMileageLogDlg::RefreshCharge()
{
	m_List.DeleteAllItems(); 

	CCountMileageLogSubDlg*	pCMPhoneDlg	 = (CCountMileageLogSubDlg*)GetTabItem(0);
	CCountMileageLogSubDlg*	pCMInternetDlg = (CCountMileageLogSubDlg*)GetTabItem(1);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_count_mileage_charge_log");
	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(m_nCNo);
	CMkParameter *pBalance = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *pCMCount = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *pCMCharge = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *pCMCountInternet = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *pCMChargeInternet= pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if(!pRs.Execute(&pCmd)) return;

	long nBalance; pBalance->GetValue(nBalance);
	
	pCMCount->GetValue(pCMPhoneDlg->m_nCMCount);
	pCMCharge->GetValue(pCMPhoneDlg->m_nCMCharge);
	pCMCountInternet->GetValue(pCMInternetDlg->m_nCMCount);
	pCMChargeInternet->GetValue(pCMInternetDlg->m_nCMCharge);

	CString sTemp = ""; sTemp.Format("현재잔액은 %s원 입니다.", LF->GetMyNumberFormat(nBalance));
	this->SetWindowText(sTemp);
	sTemp = ""; sTemp.Format("전화접수오더 %d건에 %s원, 인터콜접수오더 %d건에 %s원 적용중입니다", 
		pCMPhoneDlg->m_nCMCount, LF->GetMyNumberFormat(pCMPhoneDlg->m_nCMCharge), 
		pCMInternetDlg->m_nCMCount, LF->GetMyNumberFormat(pCMInternetDlg->m_nCMCharge));
	m_stcHelp.SetWindowText(sTemp);

	COleDateTime dtLog;
	long nSpanMileage;
	CString sEtc;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("dtLog", dtLog);
		pRs.GetFieldValue("nSpanMileage", nSpanMileage);
		pRs.GetFieldValue("sEtc", sEtc);

		m_List.InsertItem(i, dtLog.Format("%m-%d"));
		m_List.SetItemText(i, 1, LF->GetMyNumberFormat(nSpanMileage));
		m_List.SetItemText(i, 2, sEtc);

		pRs.MoveNext();
	}

	m_List.Populate();
}

void CCountMileageLogDlg::RefreshMap()
{
	DeleteMapInfo();

	CCountMileageLogSubDlg*	pCMPhoneDlg	 = (CCountMileageLogSubDlg*)GetTabItem(0);
	CCountMileageLogSubDlg*	pCMInternetDlg = (CCountMileageLogSubDlg*)GetTabItem(1);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_count_mileage_count");

	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(m_nCNo);

	if(!pRs.Execute(&pCmd)) return;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		BOOL bInternet;

		ST_COUNT_MILE *st = new ST_COUNT_MILE;
		pRs.GetFieldValue("nTNo", st->nTNo);
		pRs.GetFieldValue("dt1", st->dt1);
		pRs.GetFieldValue("bInternet", bInternet);

		if(bInternet)
			m_mapInternet.insert(MAP_COUNT_MILE::value_type(std::make_pair(m_mapInternet.size(), st)));
		else
			m_mapPhone.insert(MAP_COUNT_MILE::value_type(std::make_pair(m_mapPhone.size(), st)));

		pRs.MoveNext();
	}

	pCMPhoneDlg->SetCountMileMap(&m_mapPhone);
	pCMInternetDlg->SetCountMileMap(&m_mapInternet);

	if(m_bFirst)
	{
		MoveControl();
		m_bFirst = FALSE;
	}

}

void CCountMileageLogDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}

CWnd* CCountMileageLogDlg::GetTabItem(int nTab)
{
	CXTPTabPaintManager* pXTPTabPaintManager =  m_wndTabControl.GetPaintManager();
	int nTabCount = m_wndTabControl.GetItemCount();
	if(nTab >= nTabCount) return NULL;

	CXTPTabManagerItem* pXTPTabManagerItem =  m_wndTabControl.GetItem(nTab);

	CWnd* pWnd =  FromHandle(pXTPTabManagerItem->GetHandle());
	return pWnd;
}

void CCountMileageLogDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	MoveControl();
}

void CCountMileageLogDlg::MoveControl()
{
	if(m_List.GetSafeHwnd() == NULL) return;
	if(m_wndTabControl.GetSafeHwnd() == NULL) return;
 
	CCountMileageLogSubDlg*	pCMPhoneDlg	 = (CCountMileageLogSubDlg*)GetTabItem(0);
	CCountMileageLogSubDlg*	pCMInternetDlg = (CCountMileageLogSubDlg*)GetTabItem(1);

	if(pCMPhoneDlg == NULL) return;
	if(pCMInternetDlg == NULL) return;

	CRect rcClient, rcList, rcTab; 

	this->GetWindowRect(rcClient);
	m_List.GetWindowRect(rcList);
	m_wndTabControl.GetWindowRect(rcTab);

	ScreenToClient(rcClient);
	ScreenToClient(rcList);
	ScreenToClient(rcTab); 

	rcList.bottom = rcClient.bottom - 10;
	m_List.MoveWindow(rcList); 

	rcTab.bottom = rcClient.bottom - 10;
	rcTab.right = rcClient.right - 3; 
	m_wndTabControl.MoveWindow(rcTab);
	 
	pCMPhoneDlg->MoveControl();
	pCMInternetDlg->MoveControl();	 

}