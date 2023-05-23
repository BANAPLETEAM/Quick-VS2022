// CardVerifyDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "CardVerifyDlg.h"
#include ".\cardverifydlg.h"
#include "BCCardFunc.h"
#include "CardPayLogDlg.h"

// CCardVerifyDlg 대화 상자입니다.
CMkDatabase* CCardVerifyDlg::m_pMkCard = NULL;

IMPLEMENT_DYNAMIC(CCardVerifyDlg, CMyDialog)
CCardVerifyDlg::CCardVerifyDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CCardVerifyDlg::IDD, pParent)
{
	m_pParent = pParent; //rcpdlg;
	m_nCardType = 0;
	m_nOKCardCharge = 0;
	m_bAcceptCanceled = FALSE;

	m_nTNo = 0;
	m_nRiderCompany = 0;
	m_nRNo = 0;

	m_nPreProcess = -1;

	m_pMkCard = NULL;
	m_pBi = NULL;
	m_bAgreeCardSave = FALSE;
}

CCardVerifyDlg::~CCardVerifyDlg()
{
	if(m_pMkCard)
	{
		delete m_pMkCard;
		m_pMkCard = NULL;
	}
}

void CCardVerifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CARD_TYPE_COMBO, m_cmbCardType);
	DDX_Control(pDX, IDC_PHONE_EDIT, m_edtPhone);
	DDX_Control(pDX, IDC_CARD_NUMBER_EDIT, m_edtCardNumber);
	DDX_Control(pDX, IDC_CUSTOMER_EDIT, m_edtCustomer);
	DDX_Control(pDX, IDC_BALANCE_EDIT, m_edtBalance);
	DDX_Control(pDX, IDC_CARD_CHARGE_EDIT, m_edtCardCharge);
	DDX_Control(pDX, IDC_CARD_CHARGE_EDIT2, m_edtCardCharge2);
	DDX_Control(pDX, IDC_ACCEPT_BTN, m_btnAccept);
	DDX_Control(pDX, IDC_REQUEST_CANCEL_BTN, m_btnRequestCancel);

	DDX_CBIndex(pDX, IDC_CARD_TYPE_COMBO, m_nCardType);
	DDX_Text(pDX, IDC_PHONE_EDIT, m_strPhone);
	DDX_Text(pDX, IDC_CARD_NUMBER_EDIT, m_strCardNumber);
	DDX_Text(pDX, IDC_CUSTOMER_EDIT, m_strCustomer);
	DDX_Text(pDX, IDC_BALANCE_EDIT, m_strBalance);
	DDX_Text(pDX, IDC_CARD_CHARGE_EDIT, m_strCardCharge);
	DDX_Control(pDX, IDC_TRAN_EDIT, m_edtTran);
	DDX_Control(pDX, IDC_MONTH_COMBO, m_cmbMonth);
	DDX_Control(pDX, IDC_YEAR_COMBO, m_cmbYear);
	DDX_Control(pDX, IDC_BILL_KEY_COMBO, m_cmbBillKey);
	DDX_Control(pDX, IDC_CARD_NUMBER_EDIT2, m_edtCardNumber2);
	DDX_Control(pDX, IDC_ACCEPT_BTN2, m_btnAccept2);
	DDX_Control(pDX, IDC_SEND_SMS_CHECK, m_chkSendSms);
	DDX_Control(pDX, IDC_E_MAIL_EDIT, m_edtEMail); 
	DDX_Control(pDX, IDC_FEE_TYPE_COMBO, m_cmbFeeType);
	DDX_Control(pDX, IDC_FEE_TYPE_COMBO2, m_cmbFeeType2);
	DDX_Control(pDX, IDC_AGREE_CARD_SAVE_CHECK, m_chkAgreeCardSave);
}


BEGIN_MESSAGE_MAP(CCardVerifyDlg, CMyDialog)
	ON_BN_CLICKED(IDC_VERIFY_BTN, OnBnClickedVerifyBtn)
	ON_BN_CLICKED(IDC_ACCEPT_BTN, OnBnClickedAcceptBtn)
	ON_BN_CLICKED(IDC_REQUEST_CANCEL_BTN, OnBnClickedRequestCancelBtn)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_VERIFY_BTN2, OnBnClickedVerifyBtn2)
	ON_BN_CLICKED(IDC_ACCEPT_BTN2, &CCardVerifyDlg::OnBnClickedAcceptBtn2)
	ON_CBN_SELCHANGE(IDC_BILL_KEY_COMBO, &CCardVerifyDlg::OnCbnSelchangeBillKeyCombo)
	ON_BN_CLICKED(IDC_DELETE_CARD_BTN, &CCardVerifyDlg::OnBnClickedDeleteCardBtn)
	ON_BN_CLICKED(IDC_SHOW_HISTORY_BTN, &CCardVerifyDlg::OnBnClickedShowHistoryBtn)
	ON_BN_CLICKED(IDC_SEND_SMS_CHECK, &CCardVerifyDlg::OnBnClickedSendSmsCheck)
	ON_CBN_SELCHANGE(IDC_FEE_TYPE_COMBO, &CCardVerifyDlg::OnCbnSelchangeFeeTypeCombo)
	ON_CBN_SELCHANGE(IDC_FEE_TYPE_COMBO2, &CCardVerifyDlg::OnCbnSelchangeFeeTypeCombo2)	
	ON_BN_CLICKED(IDC_AGREE_CARD_SAVE_CHECK, &CCardVerifyDlg::OnBnClickedAgreeCardSaveCheck)
END_MESSAGE_MAP()


BOOL CCardVerifyDlg::GetCardSocket(const char* szIP, UINT uPort)
{
	if(m_pMkCard != NULL)
	{
		delete m_pMkCard;
		m_pMkCard = NULL;
	}

	if(m_pMkCard == NULL)
	{
		m_pMkCard = new CMkDatabase(g_bana_log);
		BYTE nXorKey = (m_pMkCard->GetXorKey() + 3) % 128;
		BYTE des_key_new[] = {29,44,2,83,32,98,10,8};
		BYTE nXoredKey[8];

		for(int i = 0; i < 8; i++)
			nXoredKey[i] = des_key_new[i] ^ ((nXorKey + i) % 128);
		m_pMkCard->SetServerKey(nXoredKey);

		CBranchInfo *ci = LF->GetBranchInfo(m_ci.m_nCompanyCode);

		MSG_LOGIN_INFO info;
		ZeroMemory(&info, sizeof(MSG_LOGIN_INFO));
		info.nCompany = m_ci.m_nCompanyCode;
		info.nWNo = m_ui.nWNo;
		info.nShareCode1 = ci->nShareCode1;
		info.nShareCode2 = ci->nShareCode2;
		info.nShareCode3 = ci->nShareCode3;
		info.nShareCode4 = ci->nShareCode4;
		info.nShareCode5 = ci->nShareCode5;
		info.nShareCode6 = 0;
		info.nShareCode7 = 0;
		info.nShareCode8 = 0;
		info.nShareCode9 = 0;
		info.nShareCode10 = 0;
		info.nMsgGroupCode = 0;
		strcpy(info.szCompanyName, ci->strName);
		strcpy(info.szBranchName, ci->strBranchName);
		strcpy(info.szUserName, m_ui.strName);
		info.bIdle = 0;
		info.bManager =0;
		info.nDisplayType = 0;

		m_pMkCard->SetParentWnd(NULL);
		m_pMkCard->AsyncSelect(0);

		m_pMkCard->SetLoginInfo(&info);
		return m_pMkCard->Open(szIP, uPort, TRUE);
	}
	else
	{
		BOOL bRet = m_pMkCard->GetSocket()->IsConnected();
		if(FALSE == bRet) m_pMkCard->ConnectServer();
		return  bRet;
	}
}

void CCardVerifyDlg::MoveDialog()
{ 
	if(!m_pParent)
		return;

	CRect rcParent, rcDlg;
	m_pParent->GetWindowRect(rcParent); 
	GetWindowRect(rcDlg); 

	long nWidth = rcDlg.Width();	
	long nHeight = rcDlg.Height();

	rcDlg.left = rcParent.left + 397;  
	rcDlg.right =rcDlg.left + nWidth;   
	rcDlg.top = rcParent.top + 151; 
	rcDlg.bottom = rcDlg.top + nHeight;

	MoveWindow(rcDlg);
}

BOOL CCardVerifyDlg::GetAgreeCardSave()
{
	CMkCommand cmd(m_pMkDb, "select_agree_card_save");
	CMkParameter *pRet = cmd.AddParameter(typeLong, typeReturn, 0);
	cmd.AddParameter(m_nCNo);

	if(!cmd.Execute())
		return TRUE;

	long nRet; pRet->GetValue(nRet);

	return nRet;
}

void CCardVerifyDlg::SetAgreeCardSave(BOOL bAgree, long nCNo)
{
	CMkCommand cmd(m_pMkDb, "update_agree_card_save");
	cmd.AddParameter(nCNo);
	cmd.AddParameter(bAgree);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);

	cmd.Execute();
}

BOOL CCardVerifyDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_chkAgreeCardSave.SetCheck(GetAgreeCardSave());
	MoveDialog();
	InitCombo();

	m_chkSendSms.SetCheck(AfxGetApp()->GetProfileInt("CCardVerifyDlg", "m_chkSendSms", 0));

	m_stCardInfo.nTNo = m_nTNo;

	LF->GetCardPayType(m_stCardInfo, FALSE);

	m_strTransactionNumber = m_strOKTranNumber;
	m_strOrderPhone = m_strPhone;

	if(m_strOrderPhone.Left(1) != "0" && m_strOrderPhone.GetLength() > 0)
		m_strOrderPhone = m_ci.m_strDDD + m_strOrderPhone;
	m_strOrderPhone.Remove('-');

	m_edtPhone.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "기명고객전용");
	//m_edtCardNumber.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "무기명인경우입력");

	m_edtCardNumber.SetEditMask("0000-0000-0000-0000", LITERAL_CARD_NUMBER);
	m_edtCardNumber.SetPromptChar(' ');

	m_edtCardNumber.SetFont(m_FontManager.GetFont("맑은 고딕", 20, FW_BOLD));
	m_edtPhone.SetMyFont("맑은 고딕", 20, FW_BOLD);
	m_edtCustomer.SetMyFont("맑은 고딕", 20, FW_BOLD);
	m_edtCardCharge.SetMyFont("맑은 고딕", 20, FW_BOLD);
	m_edtCardCharge2.SetMyFont("맑은 고딕", 20, FW_BOLD); 
	m_edtBalance.SetMyFont("맑은 고딕", 20, FW_BOLD);
	m_edtCardNumber2.SetMyFont("맑은 고딕", 22, FW_BOLD);
	m_edtCardNumber2.SetUserOption(RGB(255, 0, 0), RGB(255, 255, 255));

	m_cmbCardType.SetCurSel(0);

	if(m_stCardInfo.nCardProcess == NICE_CARD_COMPLETE ||
		m_stCardInfo.nCardProcess == NICE_CARD_COMPLETE_QUICKCALL)
	{
		m_cmbFeeType.SetCurSel(m_stCardInfo.nFeeType);
		m_cmbFeeType2.SetCurSel(m_stCardInfo.nFeeType);

		m_btnAccept.EnableWindow(FALSE);
		m_btnAccept2.EnableWindow(FALSE);
		m_btnRequestCancel.EnableWindow(TRUE);
		m_edtCardNumber.EnableWindow(FALSE);
		m_cmbMonth.EnableWindow(FALSE);
		m_cmbYear.EnableWindow(FALSE);
		m_cmbFeeType.EnableWindow(FALSE);
		m_cmbFeeType2.EnableWindow(FALSE);

		m_edtCardCharge.SetWindowText(LF->GetMyNumberFormat(m_stCardInfo.nCharge));
		m_edtCardCharge2.SetWindowText(LF->GetMyNumberFormat(m_stCardInfo.nCharge));
	}
	else 
	{
		m_cmbFeeType.SetCurSel(m_pBi->nFeeType);
		m_cmbFeeType2.SetCurSel(m_pBi->nFeeType);

		InitCombo();
		m_btnAccept.EnableWindow(TRUE);
		m_btnRequestCancel.EnableWindow(FALSE);		
		RefreshResultCharge(TRUE);
		RefreshResultCharge(FALSE);
	}

	if(m_chkAgreeCardSave.GetCheck())
		InitUseageCardHistory();
	

	m_edtEMail.SetWindowText(m_strEMail);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CCardVerifyDlg::InitCombo()
{
	m_cmbYear.ResetContent();
	m_cmbMonth.ResetContent();

	COleDateTime dtCur = COleDateTime::GetCurrentTime();

	long nYear = dtCur.GetYear();

	for(int i=0; i<12; i++)
	{
		CString strYear; 
		strYear.Format("%d", nYear++);
		m_cmbYear.InsertString(i, strYear.Right(2));
		CString srtMonth; srtMonth.Format("%02d", i+1);
		m_cmbMonth.InsertString(i, srtMonth);
	}

	m_cmbYear.SetCurSel(0);
	m_cmbMonth.SetCurSel(0);
}

void CCardVerifyDlg::GetValidDate(CString &strMM, CString &strYY)
{
	m_cmbMonth.GetWindowText(strMM); 
	m_cmbYear.GetWindowText(strYY);
	//m_cmbMonth.GetLBText(m_cmbMonth.GetCurSel(), strMM);
	//m_cmbYear.GetLBText(m_cmbYear.GetCurSel(), strYY);
}

BOOL CCardVerifyDlg::VerifyCustomer(BOOL bShowMsg)
{
	/*
	CString strError, strPhone;

	m_edtPhone.GetWindowText(strPhone);

	if(strPhone.Left(1) != "0" && strPhone.GetLength() > 0)
		strPhone = m_ci.m_strDDD + strPhone;
	strPhone.Remove('-');

	m_edtCardNumber.GetWindowText(m_strCardNumber);
	m_strCardNumber.Remove('-');

	if(0 == GetBCCardNumber(m_strServerType, m_strBCHeadBranchCode, strPhone, m_strCardNumber, m_strCustomer, m_strBalance, strError))
	{
		m_strCustomer.Trim();
		m_strBalance.Format("%d", atol(m_strBalance));
		m_edtCardNumber.SetWindowText(::GetMyCardNumber(m_strCardNumber));
		m_edtCustomer.SetWindowText(m_strCustomer);
		m_edtBalance.SetWindowText(LF->GetMyNumberFormat(m_strBalance));
		m_btnAccept.EnableWindow();

		if(bShowMsg)
		{
			CString strMsg;
			strMsg.Format("결제가능한 카드입니다.[잔액:%s]", LF->GetMyNumberFormat(m_strBalance));
			MessageBox(strMsg, "확인", MB_ICONINFORMATION);
		}
		return TRUE;
	}
	else
	{
		if(strError.Find("회원정보") >= 0)
		{
			m_edtCustomer.SetWindowText("무기명(카드번호입력요망)");
			if(bShowMsg)
				MessageBox("해당 전화번호로 등록된 고객이 없습니다.\n카드번호를 입력해주시기 바랍니다.", 
				"카드번호입력요망", MB_ICONEXCLAMATION);
		}
		else
		{
			m_edtCustomer.SetWindowText("");
			if(bShowMsg)
				MessageBox(strError, "카드조회중 오류발생", MB_ICONEXCLAMATION);
		}
		m_edtBalance.SetWindowText("");
		m_edtCardNumber.SetWindowText(LITERAL_CARD_NUMBER);
		m_btnAccept.EnableWindow(FALSE);
	}
*/
	return FALSE;
}

void CCardVerifyDlg::OnBnClickedVerifyBtn()		//전화번호조회
{
	VerifyCustomer();
}


BOOL CCardVerifyDlg::VerifyCardNumber(BOOL bShowMsg)
{
	/*
	CString strError, strCardNumber, strPhone;

	m_edtPhone.GetWindowText(strPhone);

	if(strPhone.Left(1) != "0" && strPhone.GetLength() > 0)
		strPhone = m_ci.m_strDDD + strPhone;
	strPhone.Remove('-');

	m_edtCardNumber.GetWindowText(strCardNumber);
	strCardNumber.Remove('-');

	if(m_strOrderPhone.GetLength() < 9 && strPhone.GetLength() < 9)
		strPhone = "0215990707";

	CString strTransactionNumber;
	int nRet = BCCardRequestOK(m_strServerType, m_strBCHeadBranchCode, 
		strPhone.IsEmpty() ? m_strOrderPhone : strPhone, strCardNumber, 
		"1599070707", "0","", strTransactionNumber, m_strBalance, strError);

	if(nRet == 0 || nRet == 75)
	{
		m_btnAccept.EnableWindow();
		m_strBalance.Format("%d", atol(m_strBalance));
		m_edtBalance.SetWindowText(LF->GetMyNumberFormat(m_strBalance));

		if(bShowMsg)
		{
			CString strMsg;
			strMsg.Format("결제가능한 카드입니다.[잔액:%s]", LF->GetMyNumberFormat(m_strBalance));
			MessageBox(strMsg, "확인", MB_ICONINFORMATION);
		}

		return TRUE;
	}
	else
	{
		m_edtBalance.SetWindowText("");
		m_btnAccept.EnableWindow(FALSE);

		if(bShowMsg)
		{
			if(strError.Find("회원정보") >= 0)
			{
				MessageBox("카드번호가 정상적이지 않습니다", "확인", MB_ICONINFORMATION);
			}
			else
				MessageBox(strError, "조회중 오류발생", MB_ICONEXCLAMATION);
		}
	}
	*/

	return FALSE;
}

void CCardVerifyDlg::OnBnClickedVerifyBtn2()		//카드번호조회
{
	VerifyCardNumber();
}

void CCardVerifyDlg::DeleteBillkeyCombo()
{
	for(int i=0; i<m_cmbBillKey.GetCount(); i++)
	{
		ST_BILL_KEY *st = (ST_BILL_KEY*)m_cmbBillKey.GetItemData(i);

		if(st)
		{
			delete st;
			st = NULL;
		}
	}

	m_cmbBillKey.ResetContent();
}

void CCardVerifyDlg::InitUseageCardHistory()
{
	DeleteBillkeyCombo();
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_billkey_cards_for_rcp");
	cmd.AddParameter(m_nTNo);

	if(!rs.Execute(&cmd)) 
		return;

	long nItem = 0;

	m_cmbBillKey.InsertString(nItem, "");
	m_cmbBillKey.SetItemData(nItem++, NULL);

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		ST_BILL_KEY *st = new ST_BILL_KEY;

		rs.GetFieldValue("nCardID", st->nID);
		rs.GetFieldValue("sCardCompanyName", st->strCardCompanyName);
		rs.GetFieldValue("sCard4Digits", st->strCard4Digits);

		CString strTemp = st->strCardCompanyName;
		strTemp.Trim(); strTemp.Replace("[", ""); strTemp.Replace("]", "");

		m_cmbBillKey.InsertString(nItem, strTemp + " " + st->strCard4Digits);
		m_cmbBillKey.SetItemData(nItem++, (DWORD_PTR)st);

		rs.MoveNext();
	}

	if(rs.GetRecordCount() > 0)
	{ 
		m_cmbBillKey.SetCurSel(0);
		OnCbnSelchangeBillKeyCombo();
	}
}

BOOL CCardVerifyDlg::CheckCardPayOk(CString &strErrorMsg)
{
	CMkCommand cmd(m_pMkDb, "check_card_pay_type");
	CMkParameter *parRet = cmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	cmd.AddParameter(m_nTNo);
	CMkParameter *pParProcess = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *pParMsg = cmd.AddParameter(typeString, typeOutput, 200, "");

	if(!cmd.Execute())
	{
		strErrorMsg = "오더 정보 요청에 실패했습니다";
		return FALSE;
	}

	long nRet; parRet->GetValue(nRet);
	pParProcess->GetValue(m_nPreProcess);
	pParMsg->GetValue(strErrorMsg);

	return nRet;
}

void CCardVerifyDlg::SaveEMail()
{
	return;
	CString strEMail;
	m_edtEMail.GetWindowText(strEMail);

	CMkCommand cmd(m_pMkDb, "update_customer_email");
	cmd.AddParameter(m_nCNo);
	cmd.AddParameter(strEMail);

	cmd.Execute();
}

void CCardVerifyDlg::OnBnClickedAcceptBtn()
{
	if(!LF->POWER_CHECK(1890, "카드결제", TRUE))
		return;

	UpdateData(TRUE);

	CString strMM, strYY, strMsg;
	CString strErrorMsg;

	if(!GetCardSocket(m_stCardInfo.strCardServerAddr, m_stCardInfo.uCardServerPort))
	{
		MessageBox("카드서버 접속실패\r\n다시 시도해주세요", "확인", MB_ICONERROR);
		return;
	}

	if(!CheckCardPayOk(strErrorMsg))
	{
		MessageBox(strErrorMsg, "확인", MB_ICONINFORMATION);
		return;
	}

	if(!UpdateFeeTypeForCard(TRUE))
	{
		MessageBox("결제를 위한 오더정보 업데이트에 실해했습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	SaveEMail();

	GetValidDate(strMM, strYY);
	BOOL bResult = LF->SendNiceCardPay(m_pMkCard, 1, m_nTNo, 0, m_strCardNumber, strMM, strYY, LF->GetStringFromLong(m_ui.nCompany), LF->GetStringFromLong(m_ui.nWNo), strMsg, m_chkSendSms.GetCheck());


	if(bResult)
	{
		InsertCardLog(TRUE);
		MessageBox("성공적으로 카드 결제가 이루어 졌습니다", "확인", MB_ICONINFORMATION);
		m_bAgreeCardSave = m_chkAgreeCardSave.GetCheck();
		OnOK();
	}
	else
	{
		if(!strMsg.IsEmpty())
			MessageBox(strMsg, "확인", MB_ICONERROR);
	}
}

void CCardVerifyDlg::OnBnClickedRequestCancelBtn()
{
	if(!LF->POWER_CHECK(1891, "카드취소", TRUE))
		return;

	if(m_stCardInfo.nCardProcess != NICE_CARD_COMPLETE &&
		m_stCardInfo.nCardProcess != NICE_CARD_COMPLETE_QUICKCALL)
	{	
		MessageBox("해당 오더에 대한 결제내역이 존재하지 않습니다.",	
			"확인", MB_ICONINFORMATION);
		return;
	}

	CString strMsg;

	if(!GetCardSocket(m_stCardInfo.strCardServerAddr, m_stCardInfo.uCardServerPort))
	{
		MessageBox("카드서버 접속실패\r\n다시 시도해주세요", "확인", MB_ICONERROR);
		return;
	}

	BOOL bResult = LF->SendNiceCardPay(m_pMkCard, 0, m_nTNo, 0, m_strCardNumber, "", "", LF->GetStringFromLong(m_ui.nCompany), LF->GetStringFromLong(m_ui.nWNo), strMsg, m_chkSendSms.GetCheck());

	if(bResult)
	{
		InsertCardLog(FALSE);
		MessageBox("카드가 취소되었습니다", "확인", MB_ICONINFORMATION);
		OnOK();
	}
	else
	{
		if(!strMsg.IsEmpty())
			MessageBox(strMsg, "확인", MB_ICONERROR);
	}
}

void CCardVerifyDlg::OnBnClickedCancel()
{
	OnCancel();
}

void CCardVerifyDlg::OnOK()
{
	CMyDialog::OnOK();
}

void CCardVerifyDlg::OnCancel()
{
	if(m_nPreProcess > -1) //결제를 시도했던오더의 카드 진행상태를 이전 상태로 돌려준다
	{
		CMkCommand cmd(m_pMkDb, "update_card_state_pre");
		cmd.AddParameter(m_nTNo);
		cmd.AddParameter(m_nPreProcess);

		cmd.Execute();
	}

	CMyDialog::OnCancel();
}

BOOL CCardVerifyDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN) 
	{
		if(pMsg->wParam == VK_RETURN)
		{
			COMBOBOXINFO info_month = { sizeof(COMBOBOXINFO) };
			COMBOBOXINFO info_year = { sizeof(COMBOBOXINFO) };
			m_cmbMonth.GetComboBoxInfo(&info_month);
			m_cmbYear.GetComboBoxInfo(&info_year);

			if(IDC_CARD_NUMBER_EDIT == ::GetDlgCtrlID(pMsg->hwnd))
			{
				CWnd *pWnd = CWnd::FromHandle(info_month.hwndItem);
				pWnd->SetFocus();
				return TRUE;
			}
			else if(info_month.hwndItem == pMsg->hwnd)
			{
				CWnd *pWnd = CWnd::FromHandle(info_year.hwndItem);
				pWnd->SetFocus();
				return TRUE;
			}
			else if(info_year.hwndItem == pMsg->hwnd)
			{
				m_btnAccept.SetFocus();
				return TRUE;
			}
			else if(m_btnAccept.GetSafeHwnd() == pMsg->hwnd)
			{
				//카드Open부분에서 에러남
				//Sleep(500);
				//OnBnClickedAcceptBtn();
				return TRUE;
			}

			return TRUE;
		}
		else if(pMsg->wParam == VK_F9)
		{
			if(GetKeyState(VK_SHIFT) & 0x8000)
			{
				m_edtTran.ShowWindow(SW_SHOW);
				return FALSE;
			}
		}
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CCardVerifyDlg::OnBnClickedAcceptBtn2()
{
	if(!LF->POWER_CHECK(1890, "카드결제", TRUE))
		return;

	UpdateData(TRUE);

	CString strMsg;
	CString strErrorMsg;

	if(!GetCardSocket(m_stCardInfo.strCardServerAddr, m_stCardInfo.uCardServerPort))
	{
		MessageBox("카드서버 접속실패\r\n다시 시도해주세요", "확인", MB_ICONERROR);
		return;
	}

	if(!CheckCardPayOk(strErrorMsg))
	{
		MessageBox(strErrorMsg, "확인", MB_ICONINFORMATION);
		return;
	}

	long nBillKey =  GetBillKey();

	if(nBillKey <= ZERO)
	{
		MessageBox("카드결제 정보가 있는 항목을 선택해 주세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CString str4Digits = GetBill4Digits();

	if(nBillKey <= 0)
	{
		MessageBox("기존 이용했던 내역이 올바르지 않습니다\r\n신규 카드 결제를 이용하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	/*
	CString strTemp;
	strTemp.Format("고객님에게 카드 뒷 4자리를 확인하세요\r\n[%s]가 맞습니까?\r\n\r\n[예]클릭시 결제가 진행됩니다", str4Digits);

	if(MessageBox(strTemp, "확인", MB_OKCANCEL) != IDOK)
	return;
	*/

	if(MessageBox("[예]를 클릭시 결제가 진행됩니다", "확인", MB_OKCANCEL) != IDOK)
		return;

	if(!UpdateFeeTypeForCard(FALSE))
	{
		MessageBox("결제를 위한 오더정보 업데이트에 실해했습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	SaveEMail();

	BOOL bResult = LF->SendNiceCardPay(m_pMkCard, 1, m_nTNo, GetBillKey(), str4Digits, "", "", LF->GetStringFromLong(m_ui.nCompany), LF->GetStringFromLong(m_ui.nWNo), strMsg, m_chkSendSms.GetCheck());

	if(bResult)
	{
		InsertCardLog(TRUE);
		MessageBox("성공적으로 카드 결제가 이루어 졌습니다", "확인", MB_ICONINFORMATION);

		m_bAgreeCardSave = m_chkAgreeCardSave.GetCheck();
		OnOK();
	}
	else
	{
		if(!strMsg.IsEmpty())
			MessageBox(strMsg, "확인", MB_ICONERROR);
	}
}

long CCardVerifyDlg::GetBillKey()
{
	long nIndex = m_cmbBillKey.GetCurSel();

	if(nIndex >= 0)
	{
		ST_BILL_KEY *st = (ST_BILL_KEY*)m_cmbBillKey.GetItemData(nIndex);

		if(st == NULL)
			return 0;

		return st->nID;
	}

	return 0;
}

CString CCardVerifyDlg::GetBill4Digits()
{
	long nIndex = m_cmbBillKey.GetCurSel();

	if(nIndex >= 0)
	{
		ST_BILL_KEY *st = (ST_BILL_KEY*)m_cmbBillKey.GetItemData(nIndex);
		return st->strCard4Digits;
	}

	return "";
}

void CCardVerifyDlg::OnCbnSelchangeBillKeyCombo()
{
	long nIndex = m_cmbBillKey.GetCurSel();

	if(nIndex >= 0)
	{
		ST_BILL_KEY *st = (ST_BILL_KEY*)m_cmbBillKey.GetItemData(nIndex);

		if(st == NULL)
			m_edtCardNumber2.SetWindowText("");
		else
			m_edtCardNumber2.SetWindowText(st->strCard4Digits);
	}
}

void CCardVerifyDlg::InsertCardLog(BOOL bPay)
{
	CString strCharge; m_edtCardCharge.GetWindowText(strCharge);
	strCharge.Replace(",", "");

	CMkCommand cmd(m_pMkDb, "insert_order_log_for_card");
	cmd.AddParameter(m_nTNo);
	cmd.AddParameter(bPay);
	cmd.AddParameter(atoi(strCharge)); 
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);

	if(m_ui.nWNo == 0)
	{
		if(m_ci.m_bRcpIntMode1)
			cmd.AddParameter("관리자_본사");
		else
			cmd.AddParameter("관리자_" + m_ci.GetBranchName());
	}
	else
		cmd.AddParameter(m_ui.strName);

	cmd.Execute();
}

void CCardVerifyDlg::OnBnClickedDeleteCardBtn()
{
	long nIndex = m_cmbBillKey.GetCurSel();

	if(nIndex < 1)
	{
		MessageBox("삭제하려는 카드를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	ST_BILL_KEY *st = (ST_BILL_KEY*)m_cmbBillKey.GetItemData(nIndex);

	if(MessageBox("카드번호 [" + st->strCard4Digits + "]를 삭제하시겠습니까?", "확인", MB_ICONINFORMATION) != IDOK)
		return;

	CMkCommand cmd(m_pMkDb, "delete_billkey");
	cmd.AddParameter(st->nID);

	if(cmd.Execute())
		InitUseageCardHistory();

}

void CCardVerifyDlg::OnBnClickedShowHistoryBtn()
{
	CCardPayLogDlg dlg;
	dlg.m_nTNo = m_nTNo;
	dlg.DoModal();
}

void CCardVerifyDlg::OnBnClickedSendSmsCheck()
{
	AfxGetApp()->WriteProfileInt("CCardVerifyDlg", "m_chkSendSms", m_chkSendSms.GetCheck());
}

void CCardVerifyDlg::OnCbnSelchangeFeeTypeCombo()
{
	RefreshResultCharge(TRUE);
}

void CCardVerifyDlg::OnCbnSelchangeFeeTypeCombo2()
{
	RefreshResultCharge(FALSE);
}

void CCardVerifyDlg::RefreshResultCharge(BOOL bUp)
{
	CComboBox *pBox = bUp == TRUE ? &m_cmbFeeType : &m_cmbFeeType2;

	CMkCommand cmd(m_pMkDb, "select_card_pay_charge_info_choi_1");
	cmd.AddParameter(m_nTNo);
	cmd.AddParameter(pBox->GetCurSel());
	CMkParameter *parChargeAmt = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *parServiceAmt = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *parSupplyAmt = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *parGoodVat = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if(!cmd.Execute())
		return;

	long nChargeAmt, nServiceAmt, nSupplyAmt, nGoodsVat;

	parChargeAmt->GetValue(nChargeAmt);
	parServiceAmt->GetValue(nServiceAmt);
	parSupplyAmt->GetValue(nSupplyAmt);
	parGoodVat->GetValue(nGoodsVat);


	CEdit *pEdit = bUp == TRUE ? &m_edtCardCharge : &m_edtCardCharge2;

	pEdit->SetWindowText(LF->GetMyNumberFormat(nChargeAmt));
}


BOOL CCardVerifyDlg::UpdateFeeTypeForCard(BOOL bUp)
{
	CComboBox *pBox = bUp == TRUE ? &m_cmbFeeType : &m_cmbFeeType2;

	CMkCommand cmd(m_pMkDb, "update_fee_type_for_card");
	cmd.AddParameter(m_nTNo);
	cmd.AddParameter(pBox->GetCurSel());

	return cmd.Execute();
}

void CCardVerifyDlg::OnBnClickedAgreeCardSaveCheck()
{
	SetAgreeCardSave(m_chkAgreeCardSave.GetCheck(), m_nCNo);
}
