// AddCustomerDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "AddCustomerDlg.h"
#include "RcpPlaceInfo.h"
#include "POIDataNew.h"
#include "CustomerDlg.h"
#include "SearchPOIDlg.h"
#include "CustomerData.h"

// CAddCustomerDlg 대화 상자입니다.insert_new_customerTel

IMPLEMENT_DYNAMIC(CAddCustomerDlg, CMyDialog)
CAddCustomerDlg::CAddCustomerDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CAddCustomerDlg::IDD, pParent) 
, m_strFax(_T(""))
{ 
	m_pCustomerDlg = NULL;
	m_bCredit = FALSE;
	m_hBrush1 = CreateSolidBrush(RGB(220,220,220));

	m_nPosX = 0;
	m_nPosY = 0;
	m_nDongID = 0;
	m_nCNo = 0;
	m_nTempCNo = 0;
	m_bInternet = FALSE;

	m_pPlace = new CRcpPlaceInfo(this, PLACE_TYPE_CUSTOMER);
}

CAddCustomerDlg::~CAddCustomerDlg()
{
	DeleteObject(m_hBrush1);
	LU->DestorySearchPoiDlg();
	DELETE_OBJECT(m_pPlace);
}

void CAddCustomerDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);

	//DDX_Text(pDX, IDC_CNO_EDIT, m_strID);
	DDX_Text(pDX, IDC_USER_ID_EDIT, m_strUserID);
	DDX_Text(pDX, IDC_COMPANY_EDIT, m_strCompany);
	DDX_Text(pDX, IDC_TEL_EDIT, m_strTel);
	DDX_Text(pDX, IDC_DISPLAY_DONG_EDIT, m_strDisplayDong);
	DDX_Text(pDX, IDC_LOCATE_EDIT, m_strLocation);
	DDX_Text(pDX, IDC_DEPART_EDIT, m_strDepart);
	DDX_Text(pDX, IDC_SNAME_EDIT, m_strName);
	DDX_Text(pDX, IDC_MEMO_EDIT, m_strMemo);
	DDX_Text(pDX, IDC_MOBILE_EDIT, m_strMobile);
	DDX_Text(pDX, IDC_ADDR_DONG_EDIT, m_strAddrDong);
	DDX_Check(pDX, IDC_CREDIT_CHECK, m_bCredit);
	DDX_Text(pDX, IDC_RIDER_MEMO_EDIT, m_strRiderMemo);

	DDX_Control(pDX, IDC_LOCATE_EDIT, m_edtLocate);
	//DDX_Control(pDX, IDC_CNO_EDIT, m_edtCNo);
	DDX_Control(pDX, IDC_USER_ID_EDIT, m_edtUserID);
	DDX_Control(pDX, IDC_COMPANY_EDIT, m_edtCompany);
	DDX_Control(pDX, IDC_DEPART_EDIT, m_edtDepart);
	DDX_Control(pDX, IDC_DISPLAY_DONG_EDIT, m_edtDisplayDong);
	DDX_Control(pDX, IDC_SNAME_EDIT, m_edtName);
	DDX_Control(pDX, IDC_TEL_EDIT, m_edtTel);
	DDX_Control(pDX, IDC_CREDIT_CHECK, m_chkCredit);
	DDX_Control(pDX, IDC_MEMO_EDIT, m_edtMemo);
	DDX_Control(pDX, IDC_MOBILE_EDIT, m_edtMobile);
	DDX_Control(pDX, IDC_LOCATE_STATIC, m_stcLocate);
	DDX_Control(pDX, IDC_CUSTOMER_NO_STATIC, m_stcCNo);
	DDX_Control(pDX, IDC_COMPANY_STATIC, m_stcCompany);
	DDX_Control(pDX, IDC_BASEDONG_STATIC, m_stcBaseDong);
	DDX_Control(pDX, IDC_DEPART_STATIC, m_stcDepart);
	DDX_Control(pDX, IDC_TEL_STATIC, m_stcTel);
	DDX_Control(pDX, IDC_MANAGER_STATIC, m_stcManager);
	DDX_Control(pDX, IDC_MOBILE_STATIC, m_stcMobile);
	DDX_Control(pDX, IDC_MEMO_STATIC, m_stcMemo);
	DDX_Control(pDX, IDC_ALLOC_GROUP_STATIC, m_stcAllocGroup);
	DDX_Control(pDX, IDC_ALLOC_GROUP_COMBO, m_cmbAllocGroup);
	//	DDX_Control(pDX, IDC_MAP_STATIC, m_stcMap);
	DDX_Control(pDX, IDC_RIDER_MEMO_STATIC, m_stcRiderMemo);
	DDX_Control(pDX, IDC_ADDRESS_STATIC, m_stcAddress);
	DDX_Control(pDX, IDC_RIDER_MEMO_EDIT, m_edtRiderMemo);
	DDX_Control(pDX, IDC_ADDR_DONG_EDIT, m_edtAddrDong);

	DDX_Control(pDX, IDC_OK_BTN, m_btnOK);
	DDX_Control(pDX, IDC_CANCEL_BTN, m_btnCancel);
	DDX_Control(pDX, IDC_ADDRESS_DISPLAY_STATIC, m_stcAddressDisplay);
	DDX_Control(pDX, IDC_STATIC1, m_stcHelp);
	DDX_Control(pDX, IDC_FAX_EDIT_EDIT, m_edtFax);
	DDX_Text(pDX, IDC_FAX_EDIT_EDIT, m_strFax);
	DDX_Control(pDX, IDC_FAX_STATIC, m_stcFax);
}


BEGIN_MESSAGE_MAP(CAddCustomerDlg, CMyDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOkBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_EN_CHANGE(IDC_ADDR_DONG_EDIT, OnEnChangeAddrDongEdit)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SHOW_MAP_BTN, &CAddCustomerDlg::OnBnClickedShowMapBtn)
	ON_EN_SETFOCUS(IDC_ADDR_DONG_EDIT, &CAddCustomerDlg::OnEnSetfocusAddrDongEdit)
	ON_WM_SHOWWINDOW()
	ON_EN_KILLFOCUS(IDC_ADDR_DONG_EDIT, &CAddCustomerDlg::OnEnKillfocusAddrDongEdit)
	ON_EN_SETFOCUS(IDC_TEL_EDIT, &CAddCustomerDlg::OnEnSetfocusTelEdit)
	ON_EN_CHANGE(IDC_TEL_EDIT, &CAddCustomerDlg::OnEnChangeTelEdit)
END_MESSAGE_MAP()


// CAddCustomerDlg 메시지 처리기입니다.


BOOL CAddCustomerDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	LU->MakeAllocateGroupCombo(&m_cmbAllocGroup);

	m_pPlace->SetControl(&m_edtAddrDong, &m_stcAddressDisplay, NULL, &m_edtLocate,
						&m_edtCompany, &m_edtTel, &m_edtMobile, &m_edtDisplayDong);

	//	for(int i = 0; i < m_cmbAllocGroup.GetCount(); i++)
	//		m_cmbAllocGroup.SetItemData(i, i);
	//m_edtCNo.SetWindowText("N/A");

	m_cmbAllocGroup.SetCurSel(0);

	for(int i =0; i < m_ba.GetCount(); i++)
	{
		CBranchInfo *pBi = (CBranchInfo *)m_ba.GetAt(i);
		if(pBi->nCompanyCode == m_nCustomerTable && pBi->bUserIDSequence)
		{
			m_strUserID = NowUserID(m_nCustomerTable);
			m_edtUserID.SetWindowText(m_strUserID);
		}
	}

	CenterWindow();
	m_edtUserID.SetFocus();
	
	SetTimer(0, 100, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CAddCustomerDlg::OnBnClickedOk()
{
	CString strTel;

	UpdateData(TRUE);

	if(m_strCompany.GetLength() < 1)
	{
		MessageBox("상호를 입력 하여주시기 바랍니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	CPOIUnit *pPoi = m_pPlace->GetPOI();
		
	if(pPoi == NULL)
	{
		MessageBox("기준동 주소가 정확하지 않습니다.", "확인", MB_ICONINFORMATION);
		return;
	}


	//remove some dash
	strTel = LF->GetNoneDashNumber(m_strTel);

	if(!LF->IsPhoneNumber(strTel))
	{
		MessageBox("전화번호에 숫자/대쉬 이외의 문자는 사용하실수 없습니다.",
			"확인", MB_ICONINFORMATION);
		return;
	}

	/*
	if(strTel.GetLength() < 7)
	{
		MessageBox("전화번호를 확인하세요",
			"확인", MB_ICONINFORMATION);
		m_edtTel.SetFocus();
		return;
	}
	*/


	if(m_strAddrDong.GetLength() < 1)
	{
		MessageBox("동(주소)을 입력 하여주시기 바랍니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	CString strCouponCharge, strTeam, strTempUserID = "", strMsg = "";
	m_nAllocGroup = (long)m_cmbAllocGroup.GetItemData(m_cmbAllocGroup.GetCurSel());

	for(int i =0; i < m_ba.GetCount(); i++)
	{
		CBranchInfo *pBi = (CBranchInfo *)m_ba.GetAt(i);
		if(pBi->nCompanyCode == m_nCustomerTable && pBi->bUserIDSequence)
		{
			if(m_strUserID.GetLength() > 0 && atol(m_strUserID) > 0)
			{
				strTempUserID = NowUserID(m_nCustomerTable);
				if(strTempUserID != m_strUserID)
				{
					strMsg.Format("%s 의 고객번호는 등록되어 사용중입니다. 지금 %s번호가 신고객번호 입니다.\r\n\r\n 사용하시려면예를 선택하세요",
						m_strUserID, strTempUserID);
					if(MessageBox(strMsg, "확인", MB_ICONINFORMATION | MB_YESNO) == IDYES)
					{
						m_strUserID = strTempUserID;
						break;
					}
					else
						return;

				}
			}
			else
			
	break;
		}
	}


 	m_stcAddressDisplay.GetNormalText(m_strAddressDetail);
	//m_strAddressDetail.Replace(pPoi->GetFullName(), "");
	//m_strAddressDetail.TrimLeft();

	long nPosX = m_pPlace->GetPosX();
	long nPosY = m_pPlace->GetPosY();

	if(nPosX == 0 || nPosY == 0)
	{
		nPosX = pPoi->GetPosX();
		nPosY = pPoi->GetPosY();
	}

	CWaitCursor wait; 
	CMkCommand pCmd(m_pMkDb, "insert_new_customer_new6");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(long));	//return
	pCmd.AddParameter(m_strUserID);
	pCmd.AddParameter(m_nCustomerTable);
	pCmd.AddParameter(m_strCompany);
	pCmd.AddParameter(m_strDepart);
	pCmd.AddParameter(m_strName);
	pCmd.AddParameter(strTel);
	pCmd.AddParameter(m_strDisplayDong);
	pCmd.AddParameter(m_strLocation);
	pCmd.AddParameter(m_bCredit);
	pCmd.AddParameter(0);
	pCmd.AddParameter((strTeam == "일반") ? 0 : atol(strTeam));
	pCmd.AddParameter((int)m_cmbAllocGroup.GetItemData(m_cmbAllocGroup.GetCurSel()));
	pCmd.AddParameter(m_strMobile);
	pCmd.AddParameter(atol(strCouponCharge));
	pCmd.AddParameter(m_strMemo);

	pCmd.AddParameter(m_strRiderMemo);
	pCmd.AddParameter("");
	pCmd.AddParameter(m_strAddressDetail);
	pCmd.AddParameter((long)pPoi->GetDongID());
	pCmd.AddParameter(nPosX);
	pCmd.AddParameter(nPosY);
	pCmd.AddParameter(1); //m_nSendStateChangeSMS
	pCmd.AddParameter(0);
	pCmd.AddParameter(0);
	pCmd.AddParameter(m_strFax);

	pCmd.AddParameter(m_bInternet);
	pCmd.AddParameter(m_nTempCNo);

	//프로시져 실행
	if(pCmd.Execute()){
		m_nCNo = parRet->GetLong();

		if(m_nCNo > 0) { 
			m_cus.GetNewCustomer();

			if(m_pCustomerDlg)
				m_pCustomerDlg->InsertCustomerOk();
			else
			{
				MessageBox("추가되었습니다.", "확인", MB_ICONEXCLAMATION);
				OnOK();
			}					
			//
		}
		else 
		{
			MessageBox("데이터(고객) 추가를 실패하였습니다.", "확인", MB_ICONEXCLAMATION);
		}
	}
}

CString CAddCustomerDlg::NowUserID(long nCompany)
{
	CString sTempUserID;
	CMkCommand pCmd(m_pMkDb, "select_customer_userid_sequence");	
	pCmd.AddParameter(nCompany);
	CMkParameter *parRet = pCmd.AddParameter(typeString, typeOutput, sizeof(10),0);	
	if(pCmd.Execute()){
		parRet->GetValue(sTempUserID);
		return sTempUserID;

	}
	return "";
}

BOOL CAddCustomerDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{	
		if(pMsg->hwnd == m_edtCNo.GetSafeHwnd()) {
			m_edtCompany.SetFocus();
			return TRUE;
		}
		if(pMsg->hwnd == m_edtCompany.GetSafeHwnd()) {
			m_edtDepart.SetFocus();
			m_edtDepart.SetSel(0xFFFF);
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtDepart.GetSafeHwnd()) {
			m_edtName.SetFocus();
			m_edtName.SetSel(0xFFFF);
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtName.GetSafeHwnd()) {
			m_edtTel.SetFocus();
			m_edtTel.SetSel(0xFFFF);
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtTel.GetSafeHwnd()) {
			m_edtMobile.SetFocus();
			m_edtMobile.SetSel(0xFFFF);
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtMobile.GetSafeHwnd()) {
			m_edtMemo.SetFocus();
			m_edtMemo.SetSel(0xFFFF);
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtMemo.GetSafeHwnd()) {
			m_edtFax.SetFocus();
			m_edtFax.SetSel(0xFFFF);
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtFax.GetSafeHwnd()) {
			m_edtRiderMemo.SetFocus();
			m_edtRiderMemo.SetSel(0xFFFF);
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtRiderMemo.GetSafeHwnd()) {
			m_edtLocate.SetFocus();
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtLocate.GetSafeHwnd()) {
			m_edtAddrDong.SetFocus();
			return TRUE;
		}
		else if(pMsg->hwnd == m_edtAddrDong.GetSafeHwnd()) 
		{
			LU->OnAutoSelectEvent(TYPE_AUTO, TRUE, 0, FALSE);

			if(m_pPlace->GetPOI())
			{
				SetDisplayAddrEdt();
				//CString strText; m_edtAddrDong.GetWindowText(strText);
				//m_edtDisplayDong.SetWindowText(strText);
				//m_edtDisplayDong.SetFocus();
			}

			return TRUE;
		}
		else if(pMsg->hwnd == m_edtDisplayDong.GetSafeHwnd()) {
			m_btnOK.SetFocus();
			return TRUE;
		}
		else if(pMsg->hwnd == m_btnOK.GetSafeHwnd()) {
			OnBnClickedOk();
			return TRUE;
		}
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}


HBRUSH CAddCustomerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMyDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(pWnd->GetSafeHwnd() == this->GetSafeHwnd())
		return m_hBrush1;

	if(pWnd->GetDlgCtrlID() == IDC_COUPON_CHECK ||
		pWnd->GetDlgCtrlID() == IDC_MIDWORD_CHECK) {
			pDC->SetBkMode(TRANSPARENT);
			hbr = m_hBrush1;
		}
	else if(pWnd->GetDlgCtrlID() == IDC_ALLOC_GROUP_COMBO)
	{
		if(pWnd->IsWindowEnabled())
		{
			CComboBox *pCombo = (CComboBox*)pWnd;
			if(pCombo->GetCurSel() > 0)
			{
				pDC->SetTextColor(RGB(0, 0, 0));
				pDC->SetBkColor(RGB(150, 255, 150));
			}
			else {
				pDC->SetTextColor(RGB(100, 100, 100));
				pDC->SetBkColor(RGB(255, 255, 255));
			}
		}
	}
	else if(nCtlColor == CTLCOLOR_STATIC) {
		switch(pWnd->GetDlgCtrlID())
		{
		default:
			pDC->SetBkMode(TRANSPARENT);
			hbr = m_hBrush1;
			break;
		}
	}

	return hbr;
}

void CAddCustomerDlg::OnBnClickedOkBtn()
{
	OnBnClickedOk();
}

void CAddCustomerDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}

void CAddCustomerDlg::OnEnChangeAddrDongEdit()
{
	SearchDong(FALSE);
}  

void CAddCustomerDlg::OnTimer(UINT nIDEvent)
{
	if(m_nSearchPoiDlg != IDD_ADD_CUSTOMER_DLG)
			return;

		//if(GetFocus() != this) 
		//		return;


	CSearchPOIDlg *pDlg = LU->GetSearchPOIDlg();
	if(pDlg)
	{
		if(pDlg->IsWindowVisible() &&
			GetForegroundWindow() != pDlg &&
			//GetActiveWindow() != pDlg &&
			!pDlg->m_chkAlwaysShow.GetCheck())
		{ 
			CWnd *pWnd = GetFocus();
			if(pWnd->GetSafeHwnd() != NULL)			
			{
				if(pWnd != (CWnd*)&m_edtAddrDong)
				{
					LU->HideSearchPOIDlg();
				}
				else if(pWnd == (CWnd*)&m_edtAddrDong && m_edtAddrDong.GetWindowTextLength() == 0)
				{
					LU->HideSearchPOIDlg();				
				}
			}
		}
	}

	CMyDialog::OnTimer(nIDEvent);
}

void CAddCustomerDlg::SetDisplayAddrEdt()
{
	CPOIUnit *pUnit = m_pPlace->GetPOI();
	
	if(pUnit != NULL)
	{
		m_nDongID = pUnit->GetDongID();
		m_nPosX = m_pPlace->GetDetailPosX();
		m_nPosY = m_pPlace->GetDetailPosY();

		if(m_nPosX == 0 || m_nPosY == 0)
		{
			m_nPosX = pUnit->GetPosX();
			m_nPosY = pUnit->GetPosY();
		}
	}
}

void CAddCustomerDlg::OnBnClickedShowMapBtn()
{
	m_pPlace->ShowMap();
}

void CAddCustomerDlg::OnEnSetfocusAddrDongEdit()
{
	//SearchDong(TRUE);
}

void CAddCustomerDlg::SearchDong(BOOL bFocus)
{
	m_nSearchPoiDlg = IDD_ADD_CUSTOMER_DLG;

	if(LU->GetSearchPOIDlg())
	{
		if(bFocus == TRUE && LU->GetSearchPOIDlg()->m_bClosedByUser)
			return;
	}

	CString strDong; m_edtAddrDong.GetWindowText(strDong);
	//LU->ShowSearchPOIDlg(strDong, m_pPlace, m_pCustomerDlg->m_nCustomerTable, m_pCustomerDlg, &m_edtAddrDong, &m_edtDisplayDong);
	LU->ShowSearchPOIDlg(strDong, m_pPlace, LF->GetCurBranchInfo()->nCompanyCode, GetParent(), &m_edtAddrDong, &m_edtDisplayDong, FALSE);

	if(m_pCustomerDlg)
		m_pCustomerDlg->m_bDirty = TRUE; 
}

void CAddCustomerDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CMyDialog::OnShowWindow(bShow, nStatus);

	//m_bShowDlg = bShow;
}

void CAddCustomerDlg::OnEnKillfocusAddrDongEdit()
{
}

void CAddCustomerDlg::OnEnSetfocusTelEdit()
{
	//CString strTel = "";
	//m_edtTel.GetWindowText(strTel);
	////CCustomerDlg *pDlg = (CCustomerDlg *)GetParent();
	//LU->ShowSearchPOIDlg(strTel, m_pCustomerDlg->m_pPlace, m_pCustomerDlg->m_nCustomerTable, m_pCustomerDlg, &m_edtFax, &m_edtMobile);
	//
	////LU->ShowSearchPOIDlg(strCompany, pDlg->m_pPlace, pDlg->m_nCustomerTable, pDlg, &this->, &m_edtDisplayDong);
	
}

void CAddCustomerDlg::OnEnChangeTelEdit()
{
	//CString strTel = "";
	//m_edtTel.GetWindowText(strTel);
	////CCustomerDlg *pDlg = (CCustomerDlg *)GetParent();
	//LU->ShowSearchPOIDlg(strTel, m_pCustomerDlg->m_pPlace, m_pCustomerDlg->m_nCustomerTable, m_pCustomerDlg, &m_edtFax, &m_edtMobile);
}
