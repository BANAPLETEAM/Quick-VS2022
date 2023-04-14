// OptionDlgPersonalInfo.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "quick.h"
#include "OptionDlgPersonalInfo.h"
#include "POIDataNew.h"
#include "SearchRegionDlg.h"
#include "MainOptionDlg2011.h"
#include "LogiUtil.h"
#include "MakePOIData.h"

// COptionDlgPersonalInfo

IMPLEMENT_DYNCREATE(COptionDlgPersonalInfo, CMyFormView)

COptionDlgPersonalInfo::COptionDlgPersonalInfo()
	: CMyFormView(COptionDlgPersonalInfo::IDD)
{
	m_strMainName = "";
	m_strMainBizNo = "";
	m_strMainOwner = "";
	m_strMainOwnerSSN = "";
	m_strMainTel = "";
	m_strMainHp = "";
	m_strMainEMail = "";
	m_nMainHomeDongID = 0;
	m_strMainHomeAddress = "";
	m_nMainCompanyDongID = 0;
	m_strMainCompanyAddress = "";
	m_strMainManager = "";
	m_strMainBank = "";
	m_strMainBankAccount = "";
	m_strMainAccountOwner = "";
	m_strMainFax = "";
	m_strMainHomePage = "";
	m_strMainHomeZipCode = "";
	m_strMainCompanyZipCode = "";
	m_nMainPostalReceiveType = 1;

	m_nHomeDongID = 0;
	m_nCompanyDongID = 0;
}

COptionDlgPersonalInfo::~COptionDlgPersonalInfo()
{
}

void COptionDlgPersonalInfo::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INFO_STATIC, m_stcInfo);
	DDX_Control(pDX, IDC_INFO_STATIC7, m_stcInfo2);
	DDX_Control(pDX, IDC_INFO_STATIC8, m_stcInfo3);
	DDX_Control(pDX, IDC_NAME_EDIT, m_edtName);
	DDX_Control(pDX, IDC_OWNER_EDIT, m_edtOwner);
	DDX_Control(pDX, IDC_TEL_EDIT, m_edtTel);
	DDX_Control(pDX, IDC_HP_EDIT, m_edtHp);
	DDX_Control(pDX, IDC_BIZ_NO_EDIT, m_edtBizNo);
	DDX_Control(pDX, IDC_OWNER_SSN_EDIT, m_edtOwnerSSN);
	DDX_Control(pDX, IDC_EMAIL_EDIT, m_edtEMail);
	DDX_Control(pDX, IDC_HOME_DONG_EDIT, m_edtHomeDong);
	DDX_Control(pDX, IDC_HOME_DONG_STATIC, m_stcHomeDong);
	DDX_Control(pDX, IDC_HOME_ADDRESS_EDIT, m_edtHomeAddress);
	DDX_Control(pDX, IDC_COMPANY_DONG_EDIT, m_edtCompanyDong);
	DDX_Control(pDX, IDC_COMPANY_DONG_STATIC, m_stcCompanyDong);
	DDX_Control(pDX, IDC_COMPANY_ADDRESS_EDIT, m_edtCompanyAddress);
	DDX_Control(pDX, IDC_CARD_CONTRACT_EDIT, m_edtCardContract);
	DDX_Control(pDX, IDC_MID_EDIT, m_edtMID);
	DDX_Control(pDX, IDC_USE_CARD_PAY_CHECK, m_chkUseCardPay);
	DDX_Control(pDX, IDC_MANAGER_EDIT, m_edtManager);
	DDX_Control(pDX, IDC_BANK_EDIT, m_edtBank);
	DDX_Control(pDX, IDC_BANK_ACCOUNT_EDIT, m_edtBankAccount);
	DDX_Control(pDX, IDC_ACCOUNT_OWNER_EDIT, m_edtAccountOwner);
	DDX_Control(pDX, IDC_FAX_EDIT, m_edtFax);
	DDX_Control(pDX, IDC_HOME_PAGE_EDIT, m_edtHomePage);
	DDX_Control(pDX, IDC_HOME_ZIP_CODE_EDIT, m_edtHomeZipCode);
	DDX_Control(pDX, IDC_COMPANY_ZIP_CODE_EDIT, m_edtCompanyZipCode);
	DDX_Control(pDX, IDC_HOME_CHECK, m_chkHome);
	DDX_Control(pDX, IDC_COMPANY_CHECK, m_chkCompany);
	DDX_Control(pDX, IDC_NOT_APPLY_WITH_HOLDING_CHECK, m_chkNotApplyWithHolding);
	DDX_Control(pDX, IDC_WON_CUT_CHECK, m_chkWonCut);

	DDX_Text(pDX, IDC_NAME_EDIT, m_strName);
	DDX_Text(pDX, IDC_OWNER_EDIT, m_strOwner);
	DDX_Text(pDX, IDC_TEL_EDIT, m_strTel);
	DDX_Text(pDX, IDC_HP_EDIT, m_strHp);
	DDX_Text(pDX, IDC_BIZ_NO_EDIT, m_strBizNo);
	DDX_Text(pDX, IDC_OWNER_SSN_EDIT, m_strOwnerSSN);
	DDX_Text(pDX, IDC_EMAIL_EDIT, m_strEMail);
	DDX_Text(pDX, IDC_HOME_DONG_EDIT, m_strHomeDong);
	DDX_Text(pDX, IDC_HOME_ADDRESS_EDIT, m_strHomeAddress);
	DDX_Text(pDX, IDC_COMPANY_DONG_EDIT, m_strCompanyDong);
	DDX_Text(pDX, IDC_COMPANY_ADDRESS_EDIT, m_strCompanyAddress);
	DDX_Text(pDX, IDC_CARD_CONTRACT_EDIT, m_strCardContract);
	DDX_Text(pDX, IDC_MID_EDIT, m_strMID);
	DDX_Text(pDX, IDC_MANAGER_EDIT, m_strManager);
	DDX_Text(pDX, IDC_BANK_EDIT, m_strBank);
	DDX_Text(pDX, IDC_BANK_ACCOUNT_EDIT, m_strBankAccount);
	DDX_Text(pDX, IDC_ACCOUNT_OWNER_EDIT, m_strAccountOwner);
	DDX_Text(pDX, IDC_FAX_EDIT, m_strFax);
	DDX_Text(pDX, IDC_HOME_PAGE_EDIT, m_strHomePage);
	DDX_Text(pDX, IDC_HOME_ZIP_CODE_EDIT, m_strHomeZipCode);
	DDX_Text(pDX, IDC_COMPANY_ZIP_CODE_EDIT, m_strCompanyZipCode);
	DDX_Check(pDX, IDC_NOT_APPLY_WITH_HOLDING_CHECK, m_bNotApplyWithHolding);
	DDX_Check(pDX, IDC_WON_CUT_CHECK, m_bWonCut);


	DDX_Control(pDX, IDC_FEE_TYPE_COMBO, m_cmbFeeType);
	DDX_Control(pDX, IDC_GENERAL_STATIC, m_stcGeneral);
	DDX_Control(pDX, IDC_CARD_STATIC, m_stcCard);
}

BEGIN_MESSAGE_MAP(COptionDlgPersonalInfo, CMyFormView)
	ON_BN_CLICKED(IDC_USE_CARD_PAY_CHECK, &COptionDlgPersonalInfo::OnBnClickedUseCardPayCheck)
	ON_BN_CLICKED(IDC_HOME_CHECK, &COptionDlgPersonalInfo::OnBnClickedHomeCheck)
	ON_BN_CLICKED(IDC_COMPANY_CHECK, &COptionDlgPersonalInfo::OnBnClickedCompanyCheck)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_DELETE_BTN, &COptionDlgPersonalInfo::OnBnClickedDeleteBtn)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// COptionDlgPersonalInfo 진단입니다.

#ifdef _DEBUG
void COptionDlgPersonalInfo::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void COptionDlgPersonalInfo::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void COptionDlgPersonalInfo::RefreshData(CMkRecordset *pRs)
{
	ChangeControl();

	CMainOptionDlg2* pDlg = (CMainOptionDlg2*)GetParent()->GetParent();
	long nCompanyCode = pDlg->GetSelCompanyCode();

	BOOL bUseCardPay;
	long nCardContract, nFeeType; 

	m_nHomeDongID = 0;
	m_nCompanyDongID = 0;

	pRs->GetFieldValue("sName", m_strName);
	pRs->GetFieldValue("sBizNo", m_strBizNo);
	pRs->GetFieldValue("sOwner", m_strOwner);
	pRs->GetFieldValue("sOwnerSSN", m_strOwnerSSN);
	pRs->GetFieldValue("sTel", m_strTel);
	pRs->GetFieldValue("sHp", m_strHp);
	pRs->GetFieldValue("sEMail", m_strEMail);
	pRs->GetFieldValue("nHomeDongID", m_nHomeDongID);
	pRs->GetFieldValue("sHomeAddress", m_strHomeAddress);
	pRs->GetFieldValue("nCompanyDongID", m_nCompanyDongID);
	pRs->GetFieldValue("sCompanyAddress", m_strCompanyAddress);
	pRs->GetFieldValue("bUseCardPay", bUseCardPay);
	pRs->GetFieldValue("nCardContract", nCardContract);
	pRs->GetFieldValue("sMID", m_strMID);
	pRs->GetFieldValue("sManager", m_strManager);
	pRs->GetFieldValue("sBank", m_strBank);
	pRs->GetFieldValue("sBankAccount", m_strBankAccount);
	pRs->GetFieldValue("sAccountOwner", m_strAccountOwner);
	pRs->GetFieldValue("sFax", m_strFax); 
	pRs->GetFieldValue("nPostalReceiveType", m_nPostalReceiveType); 
	pRs->GetFieldValue("sHomePage", m_strHomePage);
	pRs->GetFieldValue("sHomeZipCode", m_strHomeZipCode); 
	pRs->GetFieldValue("sCompanyZipCode", m_strCompanyZipCode);
	pRs->GetFieldValue("nFeeType", nFeeType);
	pRs->GetFieldValue("bNotApplyWithHolding", m_bNotApplyWithHolding);
	pRs->GetFieldValue("nWonCut", m_bWonCut);
						
	//if(m_ci.m_bRcpIntMode1)
	if(m_ci.GetRcpIntMode1(nCompanyCode))
	{
		m_strMainName = m_strName;
		m_strMainBizNo = m_strBizNo;
		m_strMainOwner = m_strOwner;
		m_strMainOwnerSSN = m_strOwnerSSN;
		m_strMainTel = m_strTel;
		m_strMainHp = m_strHp;
		m_strMainEMail = m_strEMail;
		m_nMainHomeDongID = m_nHomeDongID;
		m_strMainHomeAddress = m_strCompanyAddress;
		m_nMainCompanyDongID = m_nCompanyDongID;
		m_strMainCompanyAddress = m_strCompanyAddress;
		m_strMainManager = m_strManager;
		m_strMainBank = m_strBank;
		m_strMainBankAccount = m_strBankAccount;
		m_strMainAccountOwner = m_strAccountOwner;
		m_strMainFax = m_strFax;
		m_strMainHomePage = m_strHomePage;
		m_strMainHomeZipCode = m_strHomeZipCode;
		m_strMainCompanyZipCode = m_strCompanyZipCode;
		m_nMainPostalReceiveType = m_nPostalReceiveType;
	}
	else
	{
		m_strName = m_strMainName;
		m_strBizNo = m_strMainBizNo;
		m_strOwner = m_strMainOwner;
		m_strOwnerSSN = m_strMainOwnerSSN;
		m_strTel = m_strMainTel;
		m_strHp = m_strMainHp;
		m_strEMail = m_strMainEMail;
		m_nHomeDongID = m_nMainHomeDongID;
		m_strHomeAddress = m_strMainHomeAddress;
		m_nCompanyDongID = m_nMainCompanyDongID;
		m_strCompanyAddress = m_strMainCompanyAddress;
		m_strManager = m_strMainManager;
		m_strBank = m_strMainBank;
		m_strBankAccount = m_strMainBankAccount;
		m_strAccountOwner = m_strMainAccountOwner;
		m_strFax = m_strMainFax;
		m_strHomePage = m_strMainHomePage;
		m_strHomeZipCode = m_strMainHomeZipCode;
		m_strCompanyZipCode = m_strMainCompanyZipCode;
		m_nPostalReceiveType = m_nMainPostalReceiveType;
	}
	
	UpdateData(FALSE);

	m_chkUseCardPay.SetCheck(bUseCardPay);

	
	if(nCardContract == 0 || m_strMID.IsEmpty())
		m_edtCardContract.SetWindowText("미계약");
	else if(nCardContract == 1)
		m_edtCardContract.SetWindowText("카드사 승인대기중");
	else if(nCardContract == 2)
		m_edtCardContract.SetWindowText("정상");

	if(m_nPostalReceiveType == 0)
	{
		m_chkHome.SetCheck(TRUE);
		m_chkCompany.SetCheck(FALSE);
	}
	else
	{
		m_chkHome.SetCheck(FALSE);
		m_chkCompany.SetCheck(TRUE);
	}

	m_cmbFeeType.SetCurSel(nFeeType);

	DisplayDongInfo();
}

void COptionDlgPersonalInfo::DisplayDongInfo()
{
	CString strTemp;

	if(m_nHomeDongID > 0)
	{
		CPOIUnit *pPoi = m_poiNew.GetDongPOI(m_nHomeDongID);

		if(pPoi)
		{
			strTemp = pPoi->GetFullName(FALSE);
			m_stcHomeDong.SetMarkupText(CSearchPOI::GetMarkupLastPartHilight(strTemp, FALSE), strTemp);
		}
	}
	else
	{
		CString strTemp;
		strTemp = "<TextBlock FontFamily='Tahoma' HorizontalAlignment='Left' VerticalAlignment='Center'><Run Foreground='red' FontWeight='Bold'>[동 선택]</Run> <Run Foreground='black' FontWeight='Bold'>클릭하세요</Run></TextBlock>";
		m_stcHomeDong.SetMarkupText(strTemp);
	} 
 
	if(m_nCompanyDongID > 0)
	{
		CPOIUnit *pPoi = m_poiNew.GetDongPOI(m_nCompanyDongID);

		if(pPoi)
		{
			strTemp = pPoi->GetFullName(FALSE);
			m_stcCompanyDong.SetMarkupText(CSearchPOI::GetMarkupLastPartHilight(strTemp, FALSE), strTemp);
		}
	}
	else
	{
		m_edtCompanyDong.SetWindowText("");

		CString strTemp;
		strTemp = "<TextBlock FontFamily='Tahoma' HorizontalAlignment='Left' VerticalAlignment='Center'><Run Foreground='red' FontWeight='Bold'>[동 선택]</Run> <Run Foreground='black' FontWeight='Bold'>클릭하세요</Run></TextBlock>";
		m_stcCompanyDong.SetMarkupText(strTemp);
	}
}

BOOL COptionDlgPersonalInfo::PreTranslateMessage(MSG* pMsg)
{
	long uID = 0;

	if(pMsg->message == WM_LBUTTONDOWN)
	{
		uID = ::GetDlgCtrlID(pMsg->hwnd);

		if(::GetDlgCtrlID(pMsg->hwnd) == IDC_HOME_DONG_STATIC)
		{
			SearchRegion(IDC_HOME_DONG_STATIC);
			return TRUE;
		}
		else if(::GetDlgCtrlID(pMsg->hwnd) == IDC_COMPANY_DONG_STATIC)
		{
			SearchRegion(IDC_COMPANY_DONG_STATIC);
			return TRUE;
		}
	}

	if(pMsg->message == WM_KEYDOWN && pMsg->wParam != VK_RETURN)
	{
		uID = ::GetDlgCtrlID(pMsg->hwnd);

		switch(::GetDlgCtrlID(pMsg->hwnd)) 
		{
		case IDC_HOME_ADDRESS_EDIT:
			{ 
				if(m_nHomeDongID == 0)
				{
					SearchRegion(IDC_HOME_DONG_STATIC);
					return TRUE;
				}

				break;					
			}

		case IDC_COMPANY_ADDRESS_EDIT:
			{
				if(m_nCompanyDongID == 0)
				{
					SearchRegion(IDC_COMPANY_DONG_STATIC);
					return TRUE;
				}

				break;
			}
		}

	}

	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		uID = ::GetDlgCtrlID(pMsg->hwnd);

		switch(::GetDlgCtrlID(pMsg->hwnd)) 
		{
		case IDC_NAME_EDIT: 
			{
				m_edtBizNo.SetFocus();
				break;
			}
		case IDC_BIZ_NO_EDIT:
			{
				m_edtOwner.SetFocus();
				break;
			}
		case IDC_OWNER_EDIT:
			{
				m_edtOwnerSSN.SetFocus();
				break;
			}
		case IDC_OWNER_SSN_EDIT:
			{
				m_edtTel.SetFocus();
				break;
			}
		case IDC_TEL_EDIT:
			{
				m_edtHp.SetFocus();
				break;
			}
		case IDC_HP_EDIT:
			{
				m_edtManager.SetFocus();
				break;
			}
		case IDC_MANAGER_EDIT:
			{
				m_edtEMail.SetFocus();
				break;
			}
		case IDC_EMAIL_EDIT:
			{
				m_edtBank.SetFocus();
				break;
			}		
		case IDC_BANK_EDIT:
			{
				m_edtBankAccount.SetFocus();
				break;
			}
		case IDC_BANK_ACCOUNT_EDIT:
			{
				m_edtAccountOwner.SetFocus();
				break;
			}
		case IDC_ACCOUNT_OWNER_EDIT:
			{
				m_edtFax.SetFocus();
				break;
			}
		case IDC_FAX_EDIT:
			{
				m_edtHomePage.SetFocus();
				break;
			}
		case IDC_HOME_PAGE_EDIT:
			{
				if(SearchRegion(IDC_HOME_DONG_STATIC))
					m_edtHomeAddress.SetFocus();
				break;
			}	
	
		case IDC_HOME_ADDRESS_EDIT:
			{ 
				m_edtHomeZipCode.SetFocus();
				break;					
			}
		case IDC_HOME_ZIP_CODE_EDIT:
			{
				if(SearchRegion(IDC_COMPANY_DONG_STATIC))
					m_edtCompanyAddress.SetFocus();
				break;					
			}

		case IDC_COMPANY_ADDRESS_EDIT:
			{
				m_edtCompanyZipCode.SetFocus();
				break;
			}
		case IDC_COMPANY_ZIP_CODE_EDIT:
			{
				m_chkUseCardPay.SetFocus();
				break;
			}
		}

		return TRUE;
	}

	return CMyFormView::PreTranslateMessage(pMsg);
}

BOOL COptionDlgPersonalInfo::SearchRegion(long nFlag)
{
	CSearchRegionDlg dlg;
	dlg.m_bReturnLiID = TRUE;
	dlg.m_strSearch = "";

	if(dlg.DoModal() == IDOK)
	{
		if(nFlag == IDC_HOME_DONG_STATIC)
		{
			m_nHomeDongID = dlg.m_nDongID;
			m_edtHomeAddress.SetFocus();
		}
		else if(nFlag == IDC_COMPANY_DONG_STATIC)
		{
			m_nCompanyDongID = dlg.m_nDongID;
			m_edtCompanyAddress.SetFocus();
		}
		
		DisplayDongInfo();
		return TRUE;
	}

	return FALSE;
}

BOOL COptionDlgPersonalInfo::Save(long nCompany, BOOL bAll)
{
	UpdateData(TRUE);

	if(m_strBizNo.IsEmpty())
	{
		MessageBox("사업자번호를 입력하세요", "확인", MB_ICONINFORMATION);
		return FALSE;;
	}

	if(m_strOwner.IsEmpty())
	{
		MessageBox("대표자명 입력하세요", "확인", MB_ICONINFORMATION);
		return FALSE;;
	}

	if(m_strOwnerSSN.IsEmpty())
	{
		MessageBox("대표자명을 생년월일을 입력하세요", "확인", MB_ICONINFORMATION);
		return FALSE;;
	}

	if(m_strTel.IsEmpty())
	{
		MessageBox("연락처(유선)을 입력하세요", "확인", MB_ICONINFORMATION);
		return FALSE;;
	}

	if(m_strHp.IsEmpty())
	{
		MessageBox("전화번호(핸드폰)을 입력하세요", "확인", MB_ICONINFORMATION);
		return FALSE;;
	}

	if(m_strManager.IsEmpty())
	{
		MessageBox("담당자를 입력하세요", "확인", MB_ICONINFORMATION);
		return FALSE;;
	}

	if(m_strEMail.IsEmpty())
	{
		MessageBox("이메일을 입력하세요", "확인", MB_ICONINFORMATION);
		return FALSE;;
	}

	if(m_strBank.IsEmpty())
	{
		MessageBox("정산은행을 입력하세요", "확인", MB_ICONINFORMATION);
		return FALSE;;
	}

	if(m_strBankAccount.IsEmpty())
	{
		MessageBox("정산계좌번호를 입력하세요", "확인", MB_ICONINFORMATION);
		return FALSE;;
	}

	if(m_strAccountOwner.IsEmpty())
	{
		MessageBox("예금주를 입력하세요", "확인", MB_ICONINFORMATION);
		return FALSE;;
	}

	if(m_strCompanyAddress.IsEmpty())
	{
		MessageBox("사업장주소를 입력하세요", "확인", MB_ICONINFORMATION);
		return FALSE;;
	}

	if(m_strHomePage.IsEmpty())
	{
		MessageBox("홈페이지를 입력하세요", "확인", MB_ICONINFORMATION);
		return FALSE;;
	}


	CMkCommand cmd(m_pMkDb, "update_option_2011_personal_info_2");

	cmd.AddParameter(bAll);
	cmd.AddParameter(nCompany);
	cmd.AddParameter(m_ui.strID); 

	cmd.AddParameter(m_strName);
	cmd.AddParameter(m_strBizNo);
	cmd.AddParameter(m_strOwner);
	cmd.AddParameter(m_strOwnerSSN);
	cmd.AddParameter(::GetNoneDashNumber(m_strTel));
	cmd.AddParameter(::GetNoneDashNumber(m_strHp));
	cmd.AddParameter(m_strEMail);
	cmd.AddParameter(m_nHomeDongID);
	cmd.AddParameter(m_strHomeAddress);
	cmd.AddParameter(m_nCompanyDongID);
	cmd.AddParameter(m_strCompanyAddress);
	cmd.AddParameter(m_chkUseCardPay.GetCheck());
	cmd.AddParameter(m_strManager);
	cmd.AddParameter(m_strBank);
	cmd.AddParameter(m_strBankAccount);
	cmd.AddParameter(m_strAccountOwner);
	cmd.AddParameter(m_strFax);
	cmd.AddParameter(m_chkCompany.GetCheck());
	cmd.AddParameter(m_strHomePage);
	cmd.AddParameter(m_strHomeZipCode);
	cmd.AddParameter(m_strCompanyZipCode);
	cmd.AddParameter(m_nHomeDongID ? m_poiNew.GetPOI(m_nHomeDongID)->GetRegionName() : "");
	cmd.AddParameter(m_nCompanyDongID ? m_poiNew.GetPOI(m_nCompanyDongID)->GetRegionName() : "");
	cmd.AddParameter(m_cmbFeeType.GetCurSel());
	cmd.AddParameter(m_bNotApplyWithHolding);
	cmd.AddParameter(m_bWonCut);

	return cmd.Execute();

}
void COptionDlgPersonalInfo::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	SetOptiobView(TRUE);

	//LU->PoiLoad();

	if(!m_poiNew.IsDataLoadOK())
	{
		CMakePOIData poi(&m_poiNew, m_pMkDb, m_ci.m_strCity, m_ci.m_bCapitalArea, FALSE, TRUE);
		poi.AutoLoad(TRUE);
	}

	CMainOptionDlg2* pDlg = (CMainOptionDlg2*)GetParent()->GetParent();

	CRect rtSTATIC_OPTION; 
	pDlg->GetDlgItem(IDC_STATIC_OPTION)->GetWindowRect(rtSTATIC_OPTION);

	this->SetWindowPos(&CWnd::wndTop,0,0,200,200,SWP_NOMOVE);
	CSize sizeTotal;

	sizeTotal.cx = 150;
	sizeTotal.cy = 550;
	SetScrollSizes(MM_TEXT, sizeTotal);

	m_edtHomeDong.SetMyFont("맑은 고딕", 16, FW_NORMAL);
	m_edtHomeDong.SetUserOption(RGB(0, 0, 255), RGB(200, 255, 155), "동입력");
	m_edtCompanyDong.SetMyFont("맑은 고딕", 16, FW_NORMAL);
	m_edtCompanyDong.SetUserOption(RGB(0, 0, 255), RGB(200, 255, 155), "동입력");

	m_edtBizNo.SetEditMask("000-00-00000", LITERAL_BIZ_NO_NUMBER);
	m_edtBizNo.SetPromptChar(' ');
	//m_edtOwnerSSN.SetEditMask("000000-0000000", LITERAL_SSN_NUMBER);
	//m_edtOwnerSSN.SetPromptChar(' ');
	m_edtHomeZipCode.SetEditMask("000-000", LITERAL_ZIP_CODE_NUMBER);
	m_edtHomeZipCode.SetPromptChar(' ');
 	m_edtCompanyZipCode.SetEditMask("000-000", LITERAL_ZIP_CODE_NUMBER);
	m_edtCompanyZipCode.SetPromptChar(' ');

	m_edtHomeAddress.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "동이하 주소를 입력하세요");
	m_edtCompanyAddress.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "동이하 주소를 입력하세요");

	m_stcInfo.SetFont(m_FontManager.GetFont("맑은 고딕", 16, FW_BOLD));
	m_stcInfo2.SetFont(m_FontManager.GetFont("맑은 고딕", 16, FW_BOLD));
	m_stcInfo3.SetFont(m_FontManager.GetFont("맑은 고딕", 16, FW_BOLD));

	m_stcCard.GetWindowRect(m_rcCard); ScreenToClient(m_rcCard);
}

void COptionDlgPersonalInfo::OnBnClickedUseCardPayCheck()
{
}

void COptionDlgPersonalInfo::OnBnClickedHomeCheck()
{
	m_chkCompany.SetCheck(!m_chkHome.GetCheck());
}

void COptionDlgPersonalInfo::OnBnClickedCompanyCheck()
{
	m_chkHome.SetCheck(!m_chkCompany.GetCheck());
}

void COptionDlgPersonalInfo::OnSize(UINT nType, int cx, int cy)
{
	return;
	CMyFormView::OnSize(nType, cx, cy);
}

void COptionDlgPersonalInfo::OnBnClickedDeleteBtn()
{
	if(MessageBox("체크지사의 카드결제 내역을 모두 삭제하시겠습니까?", "확인", MB_OKCANCEL) != IDOK)
		return;

	CMainOptionDlg2* pDlg = (CMainOptionDlg2*)GetParent()->GetParent();
	long nCompanyCode = pDlg->GetSelCompanyCode();

	CStringArray strCompanyArray;
	long nCount = pDlg->m_lstBranch.GetCheckCount(strCompanyArray);


	for(int i = 0; i < strCompanyArray.GetCount(); i++)
	{
		long nCompany = atoi(strCompanyArray.GetAt(i));

		CMkCommand cmd(m_pMkDb, "delete_all_card_save_info");
		cmd.AddParameter(nCompany);
		cmd.AddParameter(m_ui.nCompany);
		cmd.AddParameter(m_ui.nWNo);
		cmd.AddParameter(m_ui.strName);

		if(cmd.Execute())
		{			
		}
	}

	MessageBox("삭제되었습니다", "확인", MB_ICONINFORMATION);
}

void COptionDlgPersonalInfo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CMyFormView::OnPaint()을(를) 호출하지 마십시오.
}

void COptionDlgPersonalInfo::ChangeControl()
{
	CMyFormView::OnVScroll(SB_TOP, 0, NULL);

	CMainOptionDlg2* pDlg = (CMainOptionDlg2*)GetParent()->GetParent();
	long nCompany = pDlg->GetSelCompanyCode(); 

	BOOL bMainCompany = GetBranchInfo(nCompany)->bRcpIntMode1;

	CRect rcTop, rcBottom, rcCard;

	m_stcGeneral.GetWindowRect(rcTop); ScreenToClient(rcTop);
	//m_edtCompanyAddress.GetWindowRect(rcBottom); ScreenToClient(rcBottom);
	GetDlgItem(IDC_BOTTOM_STATIC)->GetWindowRect(rcBottom); ScreenToClient(rcBottom);
	m_stcCard.GetWindowRect(rcCard); ScreenToClient(rcCard);

	rcTop.bottom = rcBottom.bottom;
	rcTop.right = rcBottom.right;

	CWnd *pWnd = GetWindow(GW_CHILD);
	while(pWnd != NULL && pWnd->GetSafeHwnd() && pWnd->GetDlgCtrlID() != 0)
	{
		//pWnd->ShowWindow(TRUE);  

		if(bMainCompany)
		{
			if(m_rcCard.top != rcCard.top) 
			{
				long nHeight = 370;
				MoveControl(pWnd, nHeight); 
			}			
		}
		else
		{
			if(m_rcCard.top == rcCard.top)
			{
				long nHeight = -370;
				MoveControl(pWnd, nHeight);
			}
		}

		pWnd = pWnd->GetWindow(GW_HWNDNEXT);

	}

	Invalidate(TRUE);
}

void COptionDlgPersonalInfo::MoveControl(CWnd *pWnd, long nHeight)
{
	CRect rc;
	pWnd->GetWindowRect(rc); ScreenToClient(rc);

	long nControlHeight = rc.Height();

	rc.top += nHeight;
	rc.bottom = rc.top + nControlHeight;

	pWnd->MoveWindow(rc);
}