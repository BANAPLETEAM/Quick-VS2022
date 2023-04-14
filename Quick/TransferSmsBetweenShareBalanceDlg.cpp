// TranferSmsBetweenShareBalanceDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "resource.h"
#include "TransferSmsBetweenShareBalanceDlg.h"
#include "TransferSBSLogDlg.h"
// CTransferSmsBetweenShareBalanceDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTransferSmsBetweenShareBalanceDlg, CMyDialog)

CTransferSmsBetweenShareBalanceDlg::CTransferSmsBetweenShareBalanceDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CTransferSmsBetweenShareBalanceDlg::IDD, pParent)
{
	m_nMinusShareBalance = 0;
	m_nPlusShareBalance = 0;
	m_nMinusBasicShareRate = 0;
	m_nPlusBasicShareRate = 0;
	m_nMinusSms = 0;
	m_nPlusSms = 0;
	m_nMinusShareBalanceCompany = 0;
	m_nPlusShareBalanceCompany = 0;
	m_nMinusSmsCompany = 0;
	m_nPlusSmsCompany = 0;
	m_bOnlyOneSite = FALSE;
}

CTransferSmsBetweenShareBalanceDlg::~CTransferSmsBetweenShareBalanceDlg()
{
}

void CTransferSmsBetweenShareBalanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BRANCH_LIST, m_lstBranch);

	DDX_Control(pDX, IDC_MINUS_SHARE_EDIT, m_edtMinusShare);
	DDX_Control(pDX, IDC_PLUS_SMS_EDIT, m_edtPlusSms);
	DDX_Control(pDX, IDC_MINUS_SMS_EDIT, m_edtMinusSms);
	DDX_Control(pDX, IDC_PLUS_SHARE_EDIT, m_edtPlusShare);

	DDX_Control(pDX, IDC_STATIC1, m_stc1);
	DDX_Control(pDX, IDC_STATIC2, m_stc2);
	DDX_Control(pDX, IDC_STATIC3, m_stc3);
	DDX_Control(pDX, IDC_STATIC4, m_stc4);
	DDX_Control(pDX, IDC_STATIC5, m_stc5);
	DDX_Control(pDX, IDC_STATIC6, m_stc6);

	DDX_Control(pDX, IDC_PLUS_SMS_CHARGE_EDIT, m_edtPlusSmsCharge);
	DDX_Control(pDX, IDC_PLUS_SHARE_BALANCE_CHARGE_EDIT, m_edtPlusShareBalanceCharge);

	DDX_Control(pDX, IDC_DRAW_STATIC1, m_stcDraw1);
	DDX_Control(pDX, IDC_DRAW_STATIC2, m_stcDraw2);
	DDX_Control(pDX, IDC_SEARCH_BRANCH_EDT, m_edtSearchBranch);	
}


BEGIN_MESSAGE_MAP(CTransferSmsBetweenShareBalanceDlg, CMyDialog)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_BRANCH_LIST, OnReportBeginDrag)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()

	ON_WM_CONTEXTMENU()

	ON_COMMAND(ID_TO_MINUS_SHARE_BALANCE, OnToMinusShareBalance)
	ON_COMMAND(ID_TO_PLUS_SMS, OnToPlusSms)
	ON_COMMAND(ID_TO_MINUS_SMS, OnToMinusSms)
	ON_COMMAND(ID_TO_PLUS_SHARE_BALANCE, OnToPlusShareBalance)

	ON_EN_CHANGE(IDC_PLUS_SMS_CHARGE_EDIT, OnEnChangePlusSmsChargeEdit)
	ON_EN_CHANGE(IDC_PLUS_SHARE_BALANCE_CHARGE_EDIT, OnEnChangePlusShareBalanceChargeEdit)
	ON_EN_CHANGE(IDC_SEARCH_BRANCH_EDT, OnEnChangeSearchBranchEdit)

	ON_BN_CLICKED(IDC_TRANSFER_TO_SMS_BTN, OnBnClickedTransferToSmsBtn)
	ON_BN_CLICKED(IDC_TRANSFER_TO_SHARE_BALANCE_BTN, OnBnClickedTransferToShareBalanceBtn)
	ON_BN_CLICKED(IDC_SHOW_LOG_BTN, OnBnClickedShowLogBtn)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON, OnBnClickedCloseBtn)	

	ON_NOTIFY(NM_RCLICK, IDC_REPORT_LIST, OnReportItemRClick)
END_MESSAGE_MAP()

void CTransferSmsBetweenShareBalanceDlg::OnEnChangeSearchBranchEdit()
{
	
}

BOOL CTransferSmsBetweenShareBalanceDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_stc1.SetBkColor(RGB(255, 230 , 230), TRUE);
	m_stc4.SetBkColor(RGB(255, 230 , 230), TRUE);

	m_stc3.SetBkColor(RGB(230, 255 , 230), TRUE);
	m_stc6.SetBkColor(RGB(230, 255 , 230), TRUE);

	m_stc2.SetBkColor(RGB(230, 230 , 255), TRUE);
	m_stc5.SetBkColor(RGB(230, 230 , 255), TRUE);


	m_edtMinusShare.SetMyFont("맑은 고딕", 17, FW_BOLD);
	m_edtMinusShare.SetUserOption(RGB(0, 0, 0), RGB(245, 200, 200), "드래그하세요", TRUE);
	m_edtPlusSms.SetMyFont("맑은 고딕", 17, FW_BOLD);
	m_edtPlusSms.SetUserOption(RGB(0, 0, 0), RGB(200, 200, 245), "드래그하세요", TRUE);
	m_edtMinusSms.SetMyFont("맑은 고딕", 17, FW_BOLD);
	m_edtMinusSms.SetUserOption(RGB(0, 0, 0), RGB(245, 200, 200), "드래그하세요", TRUE);
	m_edtPlusShare.SetMyFont("맑은 고딕", 17, FW_BOLD);
	m_edtPlusShare.SetUserOption(RGB(0, 0, 0), RGB(200, 200, 245), "드래그하세요", TRUE);

	m_edtPlusSmsCharge.SetMyFont("맑은 고딕", 17, FW_BOLD);
	m_edtPlusSmsCharge.SetUserOption(RGB(0, 0, 0), RGB(100, 100, 100), "금 액", TRUE);
	m_edtPlusShareBalanceCharge.SetMyFont("맑은 고딕", 17, FW_BOLD);
	m_edtPlusShareBalanceCharge.SetUserOption(RGB(0, 0, 0), RGB(100, 100, 100), "금 액", TRUE);

	m_lstBranch.InsertColumn(0, "지사명", LVCFMT_LEFT, 150);
	m_lstBranch.Populate();

	long nItem = 0;
	for(int i = 0; i < m_ba.GetCount(); i++)
	{
		CBranchInfo *pBi = m_ba.GetAt(i);

		if(pBi->bIntegrated)
			continue;

		m_lstBranch.InsertItem(nItem, pBi->strBranchName);
		m_lstBranch.SetItemLong(nItem++, pBi->nCompanyCode);
	}

	m_lstBranch.Populate();

	if(m_bOnlyOneSite)
	{
		CheckShareBalance(IDC_MINUS_SHARE_EDIT, m_ci.m_nCompanyCode, FALSE);
		CheckSmsBalance(IDC_PLUS_SMS_EDIT, m_ci.m_nCompanyCode, FALSE);
		CheckSmsBalance(IDC_MINUS_SMS_EDIT, m_ci.m_nCompanyCode, FALSE);
		CheckShareBalance(IDC_PLUS_SHARE_EDIT, m_ci.m_nCompanyCode, FALSE);
	}

	return TRUE; 
}

void CTransferSmsBetweenShareBalanceDlg::OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/)
{
	m_bDragMode = TRUE;
	::SetCursor(AfxGetApp()->LoadCursor(IDC_MOVEHOLD));
	SetCapture();
}

long CTransferSmsBetweenShareBalanceDlg::GetSelCompany()
{
	CXTPGridRecord *pRecord = m_lstBranch.GetFirstSelectedRecord();
	
	if(pRecord == NULL)
		return 0;

	return m_lstBranch.GetItemLong(pRecord);
}

void CTransferSmsBetweenShareBalanceDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(TRUE == m_bDragMode)
	{
		CRect rcMinusShare, rcPlusSms, rcMinusSms, rcPlusShare;
		CRect rcMinusShare1, rcPlusSms1, rcMinusSms1, rcPlusShare1;

		m_edtMinusShare.GetWindowRect(&rcMinusShare);
		m_edtPlusSms.GetWindowRect(&rcPlusSms);
		m_edtMinusSms.GetWindowRect(&rcMinusSms);
		m_edtPlusShare.GetWindowRect(&rcPlusShare);
		m_stc1.GetWindowRect(&rcMinusShare1);
		m_stc2.GetWindowRect(&rcPlusSms1);
		m_stc4.GetWindowRect(&rcMinusSms1);
		m_stc5.GetWindowRect(&rcPlusShare1);

		ScreenToClient(rcMinusShare);
		ScreenToClient(rcPlusSms);
		ScreenToClient(rcMinusSms);
		ScreenToClient(rcPlusShare);
		ScreenToClient(rcMinusShare1);
		ScreenToClient(rcPlusSms1);
		ScreenToClient(rcMinusSms1);
		ScreenToClient(rcPlusShare1);

		long nCompany = GetSelCompany();

		if(rcMinusShare.PtInRect(point) ||
			rcMinusShare1.PtInRect(point))
			CheckShareBalance(IDC_MINUS_SHARE_EDIT, nCompany);
		else if(rcPlusSms.PtInRect(point) ||
			rcPlusSms1.PtInRect(point))
			CheckSmsBalance(IDC_PLUS_SMS_EDIT, nCompany);
		else if(rcMinusSms.PtInRect(point) ||
			rcMinusSms1.PtInRect(point) )
			CheckSmsBalance(IDC_MINUS_SMS_EDIT, nCompany);
		else if(rcPlusShare.PtInRect(point) ||
			rcPlusShare1.PtInRect(point))
			CheckShareBalance(IDC_PLUS_SHARE_EDIT, nCompany);
	}

	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	::ReleaseCapture();
	m_bDragMode  = FALSE;  //순서에 주의 할것

	CMyDialog::OnLButtonUp(nFlags, point);
}

void CTransferSmsBetweenShareBalanceDlg::CheckShareBalance(UINT flag, long nCompany, BOOL bMsgBox)
{
	CFlatEdit2 *pEdit = (CFlatEdit2*)GetDlgItem(flag);

	CMkCommand cmd(m_pMkDb, "select_share_balance_ok");
	CMkParameter *pPar = cmd.AddParameter(typeLong, typeReturn, sizeof(long));
	cmd.AddParameter(nCompany);
	CMkParameter *pParBalance = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *pParBasicRate = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if(!cmd.Execute()) return;

	long nRet; pPar->GetValue(nRet);

	if(nRet == 0)
	{
		if(bMsgBox)
			MessageBox("본사 혹은 지점간정산을 사용하지 않는 업체입니다", "확인", MB_ICONINFORMATION);

		return;
	}

	if(flag == IDC_MINUS_SHARE_EDIT)
	{
		pParBalance->GetValue(m_nMinusShareBalance);
		pParBasicRate->GetValue(m_nMinusBasicShareRate);
		m_nMinusShareBalanceCompany = nCompany;
		OnEnChangePlusSmsChargeEdit();
	}
	else
	{
		pParBalance->GetValue(m_nPlusShareBalance);
		pParBasicRate->GetValue(m_nPlusBasicShareRate);
		m_nPlusShareBalanceCompany = nCompany;
		OnEnChangePlusShareBalanceChargeEdit();
	}

	CBranchInfo *pBi = ::GetBranchInfo(nCompany);
	if(pBi != NULL) 
	{ 
		long nRcpColor = pBi->nRcpColor;

		if(nRcpColor == pBi->nRcpTextColor)
			nRcpColor = RGB(255, 255, 255); 
 
		pEdit->SetWindowText(pBi->strBranchName);
		pEdit->SetUserOption(pBi->nRcpTextColor, nRcpColor, "드래그하세요", TRUE);
		pEdit->Invalidate();
		//pEdit->RedrawWindow();
	}
}

void CTransferSmsBetweenShareBalanceDlg::CheckSmsBalance(UINT flag, long nCompany, BOOL bMsgBox)
{
	CFlatEdit2 *pEdit = (CFlatEdit2*)GetDlgItem(flag);

	CMkCommand cmd(m_pMkDb, "select_sms_balance_ok");
	CMkParameter *pPar = cmd.AddParameter(typeLong, typeReturn, sizeof(long));
	cmd.AddParameter(nCompany);
	CMkParameter *pParOut = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if(!cmd.Execute()) return;

	long nRet; pPar->GetValue(nRet);

	if(nRet == 0)
	{
		if(bMsgBox)
			MessageBox("SMS선입금 방식을 사용하지 않는 업체입니다", "확인", MB_ICONINFORMATION);

		return;
	}

	if(flag == IDC_MINUS_SMS_EDIT) 
	{
		pParOut->GetValue(m_nMinusSms);
		m_nMinusSmsCompany = nCompany;
		OnEnChangePlusShareBalanceChargeEdit();
	}
	else
	{
		pParOut->GetValue(m_nPlusSms);
		m_nPlusSmsCompany = nCompany;
		OnEnChangePlusSmsChargeEdit();
	}

	CBranchInfo *pBi = ::GetBranchInfo(nCompany);
	if(pBi != NULL)
	{
		long nRcpColor = pBi->nRcpColor; 

		if(nRcpColor == pBi->nRcpTextColor)
			nRcpColor = RGB(255, 255, 255); 
	
		pEdit->SetWindowText(pBi->strBranchName);
		pEdit->SetUserOption(pBi->nRcpTextColor, nRcpColor, "드래그하세요", TRUE);
	}
}

void CTransferSmsBetweenShareBalanceDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if(TRUE == m_bDragMode)
	{
		::SetCursor(AfxGetApp()->LoadCursor(IDC_MOVEHOLD));
	}

	CMyDialog::OnMouseMove(nFlags, point);
}

void CTransferSmsBetweenShareBalanceDlg::OnEnChangePlusSmsChargeEdit()
{
	CRect rc;   
	m_stcDraw1.GetWindowRect(rc);
	ScreenToClient(rc); 

	InvalidateRect(rc);
}

void CTransferSmsBetweenShareBalanceDlg::OnEnChangePlusShareBalanceChargeEdit()
{
	CRect rc;  
	m_stcDraw2.GetWindowRect(rc);
	ScreenToClient(rc); 

	InvalidateRect(rc);
}


void CTransferSmsBetweenShareBalanceDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	LF->FillBackground(&dc, this); 
	DrawToSmsCharge(&dc);
	DrawToShareBalanceCharge(&dc);
}


void CTransferSmsBetweenShareBalanceDlg::DrawToSmsCharge(CDC *pDC)
{
	CRect rc, rcTemp;     
	m_stcDraw1.GetWindowRect(rc);
	ScreenToClient(rc);   
	rcTemp = rc;   

	CString strCharge; m_edtPlusSmsCharge.GetWindowText(strCharge);
	long  nCharge = atoi(strCharge);

	pDC->FillSolidRect(rc, RGB(0, 0, 0)); 
	rc.DeflateRect(1, 1, 1, 1);
	pDC->FillSolidRect(rc, RGB(255, 255, 255));

	long nLeft = 0;
	long nMainLeft = 0;

	

	rcTemp.top += 3; rcTemp.left += 5;
	nLeft = DrawStcText(pDC, RGB(0, 0, 0), "이체전 : ", rcTemp, m_FontManager.GetFont("맑은 고딕", 23, FW_BOLD));
	rcTemp.top += 4; rcTemp.left += nLeft + 10; nMainLeft = rcTemp.left;

	if(m_nMinusShareBalanceCompany > 0)
	{
		//nLeft = DrawStcText(pDC, RGB(255, 0, 0), "[" + CI()->GetBranchInfo(m_nMinusShareBalanceCompany)->strBranchName + "]", rcTemp, m_fontSmall);
		nLeft = DrawStcText(pDC, RGB(255, 0, 0), "[" + m_ci.GetBranchName(m_nMinusShareBalanceCompany) + "]", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
		rcTemp.left += nLeft + 2; 
		nLeft = DrawStcText(pDC, RGB(0, 0, 0), "지사의 공유정산잔액 ", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
		rcTemp.left += nLeft + 2; 
		nLeft = DrawStcText(pDC, RGB(0, 0, 255), ::GetMyNumberFormat(m_nMinusShareBalance) +"원", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
	}
	else
		DrawStcText(pDC, RGB(0, 0, 0), "[공유정산금 (-)]로 드래그하세요", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));

	rcTemp.top += 18; rcTemp.left = nMainLeft;

	if(m_nPlusSmsCompany > 0)
	{
		//nLeft = DrawStcText(pDC, RGB(255, 0, 0), "[" + CI()->GetBranchInfo(m_nPlusSmsCompany)->strBranchName + "]", rcTemp, m_fontSmall);
		nLeft = DrawStcText(pDC, RGB(255, 0, 0), "[" + m_ci.GetBranchName(m_nPlusSmsCompany) + "]", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
		rcTemp.left += nLeft + 2; 
		nLeft = DrawStcText(pDC, RGB(0, 0, 0), "지사의 SMS잔액 ", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
		rcTemp.left += nLeft + 2; 
		nLeft = DrawStcText(pDC, RGB(0, 255, 0), ::GetMyNumberFormat(m_nPlusSms) +"원", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
	}
	else
		DrawStcText(pDC, RGB(0, 0, 0), "[SMS잔액 (+)]로 드래그하세요", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));


	rcTemp = rc;
	rcTemp.top = rcTemp.top + 45;rcTemp.left += 5; 

	nLeft = DrawStcText(pDC, RGB(0, 0, 0), "이체후 : ", rcTemp, m_FontManager.GetFont("맑은 고딕", 23, FW_BOLD));
	rcTemp.top += 4; rcTemp.left += nLeft + 10; nMainLeft = rcTemp.left;

	if(m_nMinusShareBalanceCompany > 0)
	{
		nLeft = DrawStcText(pDC, RGB(255, 0, 0), "[" + m_ci.GetShareCompanyBranchName(m_nMinusShareBalanceCompany)+ "]", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
		rcTemp.left += nLeft + 2; 
		nLeft = DrawStcText(pDC, RGB(0, 0, 0), "지사의 공동정산잔액 ", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
		rcTemp.left += nLeft + 2; 
		nLeft = DrawStcText(pDC, RGB(0, 0, 255), ::GetMyNumberFormat(m_nMinusShareBalance - nCharge) +"원", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
	}
	else
		DrawStcText(pDC, RGB(0, 0, 0), "---------------------------------------------", rcTemp, m_FontManager.GetFont("맑은 고딕", 23, FW_BOLD));

	rcTemp.top += 18; rcTemp.left = nMainLeft;

	if(m_nPlusSmsCompany > 0)
	{
		nLeft = DrawStcText(pDC, RGB(255, 0, 0), "[" + m_ci.GetShareCompanyBranchName(m_nPlusSmsCompany) + "]", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
		rcTemp.left += nLeft + 2; 
		nLeft = DrawStcText(pDC, RGB(0, 0, 0), "지사의 SMS잔액 ", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
		rcTemp.left += nLeft + 2; 
		nLeft = DrawStcText(pDC, RGB(0, 255, 0), ::GetMyNumberFormat(m_nPlusSms + nCharge) +"원", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
	}
	else
		DrawStcText(pDC, RGB(0, 0, 0), "---------------------------------------------", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
};


void CTransferSmsBetweenShareBalanceDlg::DrawToShareBalanceCharge(CDC *pDC)
{
	CRect rc, rcTemp;   
	m_stcDraw2.GetWindowRect(rc);
	ScreenToClient(rc);  
	rcTemp = rc;    

	CString strCharge; m_edtPlusShareBalanceCharge.GetWindowText(strCharge);
	long  nCharge = atoi(strCharge);

	pDC->FillSolidRect(rc, RGB(0, 0, 0)); 
	rc.DeflateRect(1, 1, 1, 1);
	pDC->FillSolidRect(rc, RGB(255, 255, 255));

	long nLeft = 0;
	long nMainLeft = 0;

	rcTemp.top += 3; rcTemp.left += 5;
	nLeft = DrawStcText(pDC, RGB(0, 0, 0), "이체전 : ", rcTemp, m_FontManager.GetFont("맑은 고딕", 23, FW_BOLD));
	rcTemp.top += 4; rcTemp.left += nLeft + 10; nMainLeft = rcTemp.left;

	if(m_nMinusSmsCompany > 0)
	{
		nLeft = DrawStcText(pDC, RGB(255, 0, 0), "[" + m_ci.GetShareCompanyBranchName(m_nMinusSmsCompany) + "]", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
		rcTemp.left += nLeft + 2; 
		nLeft = DrawStcText(pDC, RGB(0, 0, 0), "지사의 SMS잔액 ", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
		rcTemp.left += nLeft + 2; 
		nLeft = DrawStcText(pDC, RGB(0, 255, 0), ::GetMyNumberFormat(m_nMinusSms) +"원", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
	}
	else
		DrawStcText(pDC, RGB(0, 0, 0), "[SMS잔액 (-)]로 드래그하세요", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));

	rcTemp.top += 18; rcTemp.left = nMainLeft;

	if(m_nPlusShareBalanceCompany > 0)
	{
		nLeft = DrawStcText(pDC, RGB(255, 0, 0), "[" + m_ci.GetShareCompanyBranchName(m_nPlusShareBalanceCompany) + "]", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
		rcTemp.left += nLeft + 2; 
		nLeft = DrawStcText(pDC, RGB(0, 0, 0), "지사의 공유정산잔액 ", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
		rcTemp.left += nLeft + 2; 
		nLeft = DrawStcText(pDC, RGB(0, 0, 255), ::GetMyNumberFormat(m_nPlusShareBalance) +"원", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
	}
	else
		DrawStcText(pDC, RGB(0, 0, 0), "[공유정산금 (+)]로 드래그하세요", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));


	rcTemp = rc;
	rcTemp.top = rcTemp.top + 45;rcTemp.left += 5;

	nLeft = DrawStcText(pDC, RGB(0, 0, 0), "이체후 : ", rcTemp, m_FontManager.GetFont("맑은 고딕", 23, FW_BOLD));
	rcTemp.top += 4; rcTemp.left += nLeft + 10; nMainLeft = rcTemp.left;

	if(m_nMinusSmsCompany > 0) 
	{
		nLeft = DrawStcText(pDC, RGB(255, 0, 0), "[" + m_ci.GetShareCompanyBranchName(m_nMinusSmsCompany) + "]", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
		rcTemp.left += nLeft + 2; 
		nLeft = DrawStcText(pDC, RGB(0, 0, 0), "지사의 SMS잔액 ", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
		rcTemp.left += nLeft + 2; 
		nLeft = DrawStcText(pDC, RGB(0, 255, 0), ::GetMyNumberFormat(m_nMinusSms - nCharge) +"원", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
	}
	else
		DrawStcText(pDC, RGB(0, 0, 0), "---------------------------------------------", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));

	rcTemp.top += 18; rcTemp.left = nMainLeft;

	if(m_nPlusShareBalanceCompany > 0)
	{
		nLeft = DrawStcText(pDC, RGB(255, 0, 0), "[" + m_ci.GetShareCompanyBranchName(m_nPlusShareBalanceCompany) + "]", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
		rcTemp.left += nLeft + 2; 
		nLeft = DrawStcText(pDC, RGB(0, 0, 0), "지사의 공동정산잔액 ", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
		rcTemp.left += nLeft + 2; 
		nLeft = DrawStcText(pDC, RGB(0, 0, 255), ::GetMyNumberFormat(m_nPlusShareBalance + nCharge) +"원", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
	}
	else
		DrawStcText(pDC, RGB(0, 0, 0), "---------------------------------------------", rcTemp, m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
};


long CTransferSmsBetweenShareBalanceDlg::DrawStcText(CDC *pDC, COLORREF rgbText, CString strDisplay, CRect rc, CFont *font)
{
	CFont* pOldFont = pDC->SelectObject(font);
	pDC->SetTextColor(rgbText);  
	pDC->DrawText(strDisplay, rc, DT_LEFT);

	CSize szSize = pDC->GetTextExtent(strDisplay);
	pDC->SelectObject(pOldFont);

	return szSize.cx;
}

void CTransferSmsBetweenShareBalanceDlg::OnToMinusShareBalance()
{
	CheckShareBalance(IDC_MINUS_SHARE_EDIT, m_nMinusShareBalanceCompany);
}

void CTransferSmsBetweenShareBalanceDlg::OnToPlusSms()
{
	CheckSmsBalance(IDC_PLUS_SMS_EDIT, m_nPlusSms);
}

void CTransferSmsBetweenShareBalanceDlg::OnToMinusSms()
{
	CheckSmsBalance(IDC_MINUS_SMS_EDIT, m_nMinusSms);
}

void CTransferSmsBetweenShareBalanceDlg::OnToPlusShareBalance()
{
	CheckShareBalance(IDC_PLUS_SHARE_EDIT, m_nPlusShareBalanceCompany);
}

void CTransferSmsBetweenShareBalanceDlg::OnBnClickedShowLogBtn()
{
	CTransferSBSLogDlg dlg;
	dlg.DoModal();
}

void CTransferSmsBetweenShareBalanceDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}

void CTransferSmsBetweenShareBalanceDlg::OnBnClickedTransferToSmsBtn()
{ 
	if(m_nMinusShareBalanceCompany <= 0) {MessageBox("공유정산금을 차감시킬 지사를 선택하세요", "확인", MB_ICONINFORMATION); return;}
	if(m_nPlusSmsCompany <= 0) {MessageBox("SMS정산금을 충전시킬 지사를 선택하세요", "확인", MB_ICONINFORMATION); return;}

	CString strCharge; m_edtPlusSmsCharge.GetWindowText(strCharge);
	long nCharge = atoi(strCharge);

	if(nCharge <= 0) {MessageBox("이체할 금액을 0원 이상으로 입력하세요.", "확인", MB_ICONINFORMATION); return;}

	if(m_nMinusShareBalance - m_nMinusBasicShareRate - nCharge < 0)
	{MessageBox("이체가능 공유정산금이 부족합니다", "확인", MB_ICONINFORMATION); return;}

	CMkCommand cmd(m_pMkDb, "transfer_share_balance_to_sms4");
	cmd.AddParameter(m_nMinusShareBalanceCompany);
	cmd.AddParameter(m_nPlusSmsCompany);
	cmd.AddParameter(nCharge);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);
	CMkParameter *pPar = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);	
	if(cmd.Execute())
	{
		int nOUTPUT = 0;
		pPar->GetValue(nOUTPUT);
		if(nOUTPUT == 100) {MessageBox("공유정산금보다 차감시킬 금액이 더큽니다. ", "확인", MB_ICONINFORMATION); return;}
		if(nOUTPUT == 200) {MessageBox("차감시킬 금액이 0이하 입니다.", "확인", MB_ICONINFORMATION); return;}
		if(nOUTPUT == 300) {MessageBox("입금하실 회사의 SMS타입이 후입금입니다. ", "확인", MB_ICONINFORMATION); return;}
		if(nOUTPUT == 400) {MessageBox("공유정산금이 0원이하인 지사가 있습니다. ", "확인", MB_ICONINFORMATION); return;}

		MessageBox("이동 되었습니다.", "확인", MB_ICONINFORMATION);
		CheckShareBalance(IDC_MINUS_SHARE_EDIT, m_nMinusShareBalanceCompany, FALSE);
		CheckSmsBalance(IDC_PLUS_SMS_EDIT, m_nPlusSmsCompany, FALSE);
		CheckSmsBalance(IDC_MINUS_SMS_EDIT, m_nMinusSmsCompany, FALSE);
		CheckShareBalance(IDC_PLUS_SHARE_EDIT, m_nPlusShareBalanceCompany, FALSE);
	}
}

void CTransferSmsBetweenShareBalanceDlg::OnBnClickedTransferToShareBalanceBtn()
{
	if(m_nMinusSmsCompany <= 0) {MessageBox("SMS정산금을 차감시킬 지사를 선택하세요", "확인", MB_ICONINFORMATION); return;}
	if(m_nPlusShareBalanceCompany <= 0) {MessageBox("공유정산금을 충전시킬 지사를 선택하세요", "확인", MB_ICONINFORMATION); return;}

	CString strCharge; m_edtPlusShareBalanceCharge.GetWindowText(strCharge);
	long nCharge = atoi(strCharge);

	if(nCharge <= 0) {MessageBox("이체할 금액을 0원 이상으로 입력하세요.", "확인", MB_ICONINFORMATION); return;}

	if(m_nMinusSms - nCharge < 0)
	{MessageBox("이체가능 SMS잔액이 부족합니다", "확인", MB_ICONINFORMATION); return;}

	CMkCommand cmd(m_pMkDb, "transfer_sms_to_share_balance3");
	cmd.AddParameter(m_nMinusSmsCompany);
	cmd.AddParameter(m_nPlusShareBalanceCompany);
	cmd.AddParameter(nCharge);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);
	CMkParameter *pPar = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);	
	if(cmd.Execute())
	{
		int nOUTPUT = 0;
		pPar->GetValue(nOUTPUT);
		if(nOUTPUT == 100) {MessageBox("SMS 잔액보다 차감시킬 금액이 더큽니다. ", "확인", MB_ICONINFORMATION); return;}
		if(nOUTPUT == 200) {MessageBox("차감시킬 금액이 0이하 입니다.", "확인", MB_ICONINFORMATION); return;}
		if(nOUTPUT == 300) {MessageBox("차감하실 회사의 SMS타입이 후입금입니다. ", "확인", MB_ICONINFORMATION); return;}


		MessageBox("이동 되었습니다.", "확인", MB_ICONINFORMATION);
		CheckShareBalance(IDC_MINUS_SHARE_EDIT, m_nMinusShareBalanceCompany, FALSE);
		CheckSmsBalance(IDC_PLUS_SMS_EDIT, m_nPlusSmsCompany, FALSE);
		CheckSmsBalance(IDC_MINUS_SMS_EDIT, m_nMinusSmsCompany, FALSE);
		CheckShareBalance(IDC_PLUS_SHARE_EDIT, m_nPlusShareBalanceCompany, FALSE);
	}
}

void CTransferSmsBetweenShareBalanceDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstBranch.GetWindowRect(&rect); 
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU_1);
	CMenu *pRMenu=rMenu.GetSubMenu(9);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CTransferSmsBetweenShareBalanceDlg::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_lstBranch, pt);
}