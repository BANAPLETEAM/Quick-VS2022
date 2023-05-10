// ShareReportRateDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareReportRateDlg.h"

#include "ShareReportRateDlg1.h"
#include "ShareReportRateDlg2.h"
#include "ShareReportRateDlg3.h"
#include "ShareReportRateDlg6.h"



// CShareReportRateDlg 대화 상자입니다.





//CShareReportRateTabControl
void CShareReportRateTabControl::OnItemClick(CXTPTabManagerItem* pItem)
{
	CXTPTabControl::OnItemClick( pItem);
	HWND hWnd = pItem->GetHandle();
}

IMPLEMENT_DYNAMIC(CShareReportRateDlg, CMyDialog)
CShareReportRateDlg::CShareReportRateDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CShareReportRateDlg::IDD, pParent)
{
	m_bExitPrg = FALSE;
	m_bInitializing = FALSE;
}

CShareReportRateDlg::~CShareReportRateDlg()
{
}

void CShareReportRateDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	//	DDX_Control(pDX, IDC_REPORT, m_wndReport);
	DDX_Control(pDX, IDC_BALANCE_EDIT, m_BalanceEdit);
	DDX_Control(pDX, IDC_BASIC_RATE_EDIT, m_BasicRateEdit);
	DDX_Control(pDX, IDC_ACCOUNT_EDIT, m_AccountEdit);
	DDX_Control(pDX, IDC_ACCOUNT_EDIT2, m_AccountEdit2);
	DDX_Control(pDX, IDC_HELP_STATIC, m_HelpStatic);
	DDX_Control(pDX, IDC_YESTERDAY_EDIT, m_YesterdayEdit);
	DDX_Control(pDX, IDC_GLOBAL_SHARE_TIME_EDIT, m_GlobalShareTimeEdt);
	DDX_Control(pDX, IDC_NO_SHOW_CHECK, m_chkNoShowShareReport);

	DDX_Control(pDX, IDC_TEST_BTN, m_btnTest);
}


BEGIN_MESSAGE_MAP(CShareReportRateDlg, CMyDialog)
	ON_WM_CREATE()
	ON_NOTIFY(XTP_NM_GRID_HYPERLINK, IDC_REPORT, OnReportHyperlinkClick)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_TIMER()
	ON_STN_CLICKED(IDC_STATIC_OPTION, OnStnClickedStaticOption)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	
	ON_BN_CLICKED(IDC_INTRO_MY_COMPANY_BTN, OnBnClickedIntroMyCompanyBtn)
	ON_BN_CLICKED(IDC_EXIT_PRG_BTN, OnBnClickedExitPrgBtn)
	ON_BN_CLICKED(IDC_NO_SHOW_CHECK, &CShareReportRateDlg::OnBnClickedNoShowCheck)
	ON_BN_CLICKED(IDC_TEST_BTN, &CShareReportRateDlg::OnBnClickedTestBtn)
END_MESSAGE_MAP()


CMyRecord::CMyRecord(long nShareCode1, CString strName, CString strPhone, CString strOfficePhone, CString strChannel, 
					long nRcpRateA, long nRcpRateB, long nShareTimeA, long nShareTimeB, 
					COleDateTime dtInsert, COleDateTime dtLastEdit, CString strEditHistory, long nCompany, BOOL bIntro,
					int nAllianceID, CString strAllianceName, CString strAllianceSymbol, 
					BOOL bIsAllianceHead, BOOL bNoShareA, BOOL bNoShareB)
{
	m_nShareReportTabIdx = 0;
	m_nShareCode1 = nShareCode1;
	m_nCompany = nCompany;
	m_nAllianceID = nAllianceID;
	m_strAllianceName = strAllianceName;
	m_strAllianceSymbol = strAllianceSymbol;
	m_bIsAllianceHead = bIsAllianceHead;
	m_bNoShareA = bNoShareA;
	m_bNoShareB = bNoShareB;
	m_nOriRcpRateA = nRcpRateA;
	m_nOriShareTimeA = nShareTimeA;


	AddItem(new CXTPGridRecordItemText(strName));
	AddItem(new CXTPGridRecordItemText(strPhone));
	AddItem(new CXTPGridRecordItemText(strOfficePhone));
	AddItem(new CXTPGridRecordItemText(strChannel));

	CRcpRateRecordItem *pRcpRateA = (CRcpRateRecordItem*)AddItem(new CRcpRateRecordItem(nRcpRateA));
	if(bIsAllianceHead)
		pRcpRateA->SetEditable(FALSE);
	
	//AddItem(new CProcessRateRecordItem(20 - nRcpRateA));
	AddItem(new CRcpRateRecordItem2(nRcpRateB));
	AddItem(new CShareTimeRecordItem(nShareTimeA));
	AddItem(new CShareTimeRecordItem2(nShareTimeB));
	AddItem(new CMyDateRecordItem(dtInsert));
	AddItem(new CMyDateRecordItem(dtLastEdit));
	CXTPGridRecordItem *pItem = AddItem(new CXTPGridRecordItemText(strEditHistory));
	pItem->AddHyperlink(new CXTPGridHyperlink(0, 0xFFFF));
	pItem = AddItem(new CXTPGridRecordItemText("이체"));
	pItem->AddHyperlink(new CXTPGridHyperlink(0, 0xFFFF));
	pItem = AddItem(new CXTPGridRecordItemText("청구"));
	pItem->AddHyperlink(new CXTPGridHyperlink(0, 0xFFFF));
	//pItem = AddItem(new CXTPGridRecordItemText("소개"));
	//pItem->AddHyperlink(new CXTPGridHyperlink(0, 0xFFFF));

}


void CMyRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	if(1 == m_nShareReportTabIdx)
	{
		GetItemMetrics_1( pDrawArgs,  pItemMetrics);
		return;
	}

	if(((CRcpRateRecordItem*)GetItem(4))->GetValue() == 0 || 
		m_bNoShareA == TRUE ||
		m_bNoShareB == TRUE)
	{
		if(!pDrawArgs->pRow->GetRecord()->HasChildren())
		{
			static CFont m_fontStriked;

			if (!m_fontStriked.GetSafeHandle())
			{
				LOGFONT lf;
				pDrawArgs->pControl->GetPaintManager()->m_fontText.GetLogFont(&lf);
				lf.lfStrikeOut = TRUE;

				m_fontStriked.CreateFontIndirect(&lf);
			}

			pItemMetrics->clrForeground = RGB(128, 128, 128);
			pItemMetrics->pFont = &m_fontStriked;
		}
	}

	int nCol = pDrawArgs->pColumn->GetIndex();
	if(nCol == 4)
	{
		long nRcpRateA = ((CRcpRateRecordItem*)GetItem(4))->GetValue();
		long nRcpRateB = ((CRcpRateRecordItem2*)GetItem(6))->GetValue();

		if(nRcpRateA != nRcpRateB || nRcpRateA == 5 || nRcpRateB == 5)
			pItemMetrics->clrBackground = RGB(255, 200, 200);
		else
			pItemMetrics->clrBackground = RGB(200, 200, 255);
	}
	else if(nCol == 7)
	{
		long nShareTimeA = ((CShareTimeRecordItem*)GetItem(7))->GetValue();
		long nShareTimeB = ((CShareTimeRecordItem*)GetItem(8))->GetValue();

		if(nShareTimeA <= 0 || nShareTimeB <= 0)
			pItemMetrics->clrBackground = RGB(255, 200, 200);
		else if(nShareTimeA >= nShareTimeB)
			pItemMetrics->clrBackground = RGB(100, 255, 100);
		else 
			pItemMetrics->clrBackground = RGB(210, 255, 210);
	}
	else if(nCol == 8)
	{
		long nShareTimeA = ((CShareTimeRecordItem*)GetItem(7))->GetValue();
		long nShareTimeB = ((CShareTimeRecordItem*)GetItem(8))->GetValue();

		if(nShareTimeA <= 0 || nShareTimeB <= 0)
			pItemMetrics->clrBackground = RGB(255, 200, 200);
		else if(nShareTimeA <= nShareTimeB)
			pItemMetrics->clrBackground = RGB(100, 255, 100);
		else 
			pItemMetrics->clrBackground = RGB(210, 255, 210);

	}
	else if(nCol == 0)
	{
		pItemMetrics->clrBackground = RGB(200, 255, 200);
	}
}

// CShareReportRateDlg 메시지 처리기입니다.


BOOL CShareReportRateDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	if(m_ci.m_nCompanyCode == 10)
		m_btnTest.ShowWindow(TRUE);

	if(m_bInitializing)
	{
		m_chkNoShowShareReport.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EXIT_PRG_BTN)->ShowWindow(SW_SHOW);
	}
	m_chkNoShowShareReport.SetCheck(AfxGetApp()->GetProfileInt("Quick", "NoShowShareReport", 0));

	m_GlobalShareTimeEdt.SetLimitText(3);
	m_AccountEdit2.SetWindowText("(주)무브먼트소프트");

	CRect rtSTATIC_OPTION;
	this->GetDlgItem(IDC_STATIC_OPTION)->GetWindowRect(rtSTATIC_OPTION);
	this->ScreenToClient(rtSTATIC_OPTION);
	this->GetDlgItem(IDC_STATIC_OPTION)->ShowWindow(SW_HIDE);

	LU->CreateFormViewTabControl(this, &m_wndTabControl, rtSTATIC_OPTION);

	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CShareReportRateDlg1), "정산비율설정", 0);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CShareReportRateDlg2), "입출금내역", 0);
	LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CShareReportRateDlg3), "공동정산내역", 0);
	if(m_ui.nCompany == 10 || (m_ui.nCompany >= 6550  && m_ui.nCompany <= 6590)  )
		LU->AddView(this, &m_wndTabControl, RUNTIME_CLASS(CShareReportRateDlg6), "탁송연계", 0);


	((CShareReportRateDlg1*)GetTabItem(0))->RefreshList();

	static bool IsCheck = true;

	if(IsCheck == true)
		SetTimer(100, 100, NULL);

	IsCheck = false;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

int CShareReportRateDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMyDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}


void CShareReportRateDlg::OnReportHyperlinkClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
	if(!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	// if click on Hyperlink in Item
	if (pItemNotify->nHyperlink >= 0)
	{
		int nRow = pItemNotify->pRow->GetIndex();
		int nCol = pItemNotify->pColumn->GetItemIndex();

		//서브창 표시해서 변경내역 뿌려줘야 한다.

	}
}

void CShareReportRateDlg::OnCancel()
{
	//CMyDialog::OnCancel();
	OnOK();
}

CWnd* CShareReportRateDlg::GetTabItem(CString sCaption)
{
	CXTPTabPaintManager* pXTPTabPaintManager =  m_wndTabControl.GetPaintManager();
	int nTabCount = m_wndTabControl.GetItemCount();
	for(int nTab = 0;nTab < nTabCount;nTab++)
	{
		CXTPTabManagerItem* pXTPTabManagerItem =  m_wndTabControl.GetItem(nTab);
		if(sCaption ==  pXTPTabManagerItem->GetCaption() )
		{
			CWnd* pWnd =  FromHandle(pXTPTabManagerItem->GetHandle());
			return pWnd;
		}
	}

	return NULL;
}

CWnd* CShareReportRateDlg::GetTabItem(int nTab)
{
	CXTPTabPaintManager* pXTPTabPaintManager =  m_wndTabControl.GetPaintManager();
	int nTabCount = m_wndTabControl.GetItemCount();
	if(nTab >= nTabCount) return NULL;

	CXTPTabManagerItem* pXTPTabManagerItem =  m_wndTabControl.GetItem(nTab);

	CWnd* pWnd =  FromHandle(pXTPTabManagerItem->GetHandle());
	return pWnd;
}

void CShareReportRateDlg::OnBnClickedOk()
{
	if(((CShareReportRateDlg1*)GetTabItem(0))->CheckValidate())
		OnOK();
}

BOOL CShareReportRateDlg::IsRequest(int nCompany)
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_transfer_request");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCompany);

	if(!pRs.Execute(&pCmd)) return false;

	if(pRs.GetRecordCount() > 0)
		return true;
	else
		return false;

}

void CShareReportRateDlg::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == 100)
	{
		if(this->IsWindowVisible())
		{
			KillTimer(100);
			OpenRequestBox1();
		}
	}
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CMyDialog::OnTimer(nIDEvent);
}

void CShareReportRateDlg::OpenRequestBox1()
{
	if(IsRequest(m_ci.m_nCompanyCode))
	{
		CShareTranferRequestDlg dlg(this);
		CString sBalance, sMinBalance;
		m_BalanceEdit.GetWindowText(sBalance);
		m_BasicRateEdit.GetWindowText(sMinBalance);
		sBalance.Replace(",", "");
		sBalance.Replace("원", "");
		sMinBalance.Replace(",", "");
		sMinBalance.Replace("원", "");

		int nAbilityMoney = _ttoi(sBalance) - _ttoi(sMinBalance);

		dlg.m_nAbilityMoney = nAbilityMoney;
		dlg.m_pShareReportRateDlg1 = (CShareReportRateDlg1*)GetTabItem(0);
		dlg.m_sSql = "select_transfer_request_1";
	
		dlg.DoModal();		
	}
}

void CShareReportRateDlg::OnStnClickedStaticOption()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CShareReportRateDlg::OnBnClickedButton1()
{
	CString sGlobalShareTime;
	m_GlobalShareTimeEdt.GetWindowText(sGlobalShareTime);

	if((_ttoi(sGlobalShareTime) < 60 || _ttoi(sGlobalShareTime) > 600) && _ttoi(sGlobalShareTime) != 0)
	{
		MessageBox("60~600초 사이로 입력해 주세요", "확인", MB_ICONERROR);
		return;
	}

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_global_share_time");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), _ttoi(sGlobalShareTime));

	if(!pRs.Execute(&pCmd)) return;

	MessageBox("수정되었습니다", "확인",MB_ICONINFORMATION);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CShareReportRateDlg::OnBnClickedIntroMyCompanyBtn()
{
	/*
	CCompanyIntroDlg dlg;

	dlg.m_nIntroCompany = m_ci.m_nCompanyCode;
	dlg.m_nWriteMode = TRUE;
	dlg.DoModal();
	*/
}

void CShareReportRateDlg::OnBnClickedExitPrgBtn()
{
	m_bExitPrg = TRUE;
	OnOK();
}

BOOL CShareReportRateDlg::IsNoShow()
{
	return AfxGetApp()->GetProfileInt("Quick", "NoShowShareReport", 0);
}

void CShareReportRateDlg::OnBnClickedNoShowCheck()
{
	AfxGetApp()->WriteProfileInt("Quick", "NoShowShareReport", m_chkNoShowShareReport.GetCheck());
}

void CShareReportRateDlg::OnBnClickedTestBtn()
{
	/*
	CMkCommand pCmd(m_pMkDb, "test_yu_proc");
	pCmd.AddParameter(0);

	if(pCmd.Execute())
	{
		MessageBox("프로시져 실행 성공함", "확인", MB_ICONINFORMATION);
		return;
	}
	*/
}
