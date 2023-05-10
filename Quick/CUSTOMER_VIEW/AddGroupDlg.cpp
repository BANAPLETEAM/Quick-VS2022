// AddGroupDlg2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "AddGroupDlg.h"
#include "SearchGroupDlg.h"


// CAddGroupDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAddGroupDlg, CMyDialog)
CAddGroupDlg::CAddGroupDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(IDD_ADD_GROUP_DLG, pParent)
, m_strGroupName(_T(""))
, m_bCredit(FALSE)
, m_strDiscount(_T(""))
, m_strAbleUseCharge(_T(""))
{
	m_nGNo = 0;
	m_strManagerHP = "";

	m_bDirtyDiscount = FALSE;
	m_nDirtyDiscount = 0;
	m_bDirtyTaxApply = FALSE;
	m_nDirtyTaxApply = 0;
}

CAddGroupDlg::~CAddGroupDlg()
{
}

void CAddGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GROUP_NAME_EDIT, m_strGroupName);
	DDX_Text(pDX, IDC_ID_EDIT, m_strID);
	DDX_Text(pDX, IDC_DEPT_EDIT, m_strDept);
	DDX_Text(pDX, IDC_PWD_EDIT, m_strPwd);
	DDX_Text(pDX, IDC_NAME_EDIT, m_strName);
	DDX_Text(pDX, IDC_MANAGER_HP_EDIT, m_strManagerHP);	
	DDX_Text(pDX, IDC_EMAIL_EDIT, m_strEmail);
	DDX_Text(pDX, IDC_MEMBER_TEL_EDIT, m_strMemberTel);
	DDX_Control(pDX, IDC_COPORATION_CHARGE_CHECK, m_chkCoporationCharge);
	DDX_Text(pDX, IDC_RIDER_DEPOSIT_EDIT, m_strRiderDeposit);
	DDX_Text(pDX, IDC_DETAIL_ETC_EDIT, m_strDetaileEtc);
	DDX_Text(pDX, IDC_PRESIDENT_EDIT, m_strPresident);
	DDX_Text(pDX, IDC_BUSINEESS_NO_EDIT, m_strBussinessNo);
	DDX_Text(pDX, IDC_BUSINESS_STATUS_EDIT, m_strBusinessStatus);
	DDX_Text(pDX, IDC_BUSINESS_CATEGORY_EDIT, m_strBussinessCategroy);
	DDX_Text(pDX, IDC_COMPANY_AREA_EDIT, m_strArea);
	DDX_Control(pDX, IDC_CHARGE_TYPE_COMBO, m_cmbChargeType);
	DDX_Control(pDX, IDC_REPORT_FIRST_DAY_COMBO, m_cmbReportFirstDay);
	DDX_Control(pDX, IDC_REPORT_SECOND_DAY_COMBO, m_cmbReportSecondDay);
	DDX_Control(pDX, IDC_CREDIT_CHK, m_chkCredit);
	DDX_Check(pDX, IDC_CREDIT_CHK, m_bCredit);
	
	DDX_Text(pDX, IDC_DISCOUNT_EDIT, m_strDiscount);
	DDX_Control(pDX, IDC_LENGTH_STATIC, m_stcLengthStatic);

	DDX_Control(pDX, IDC_DISCOUNT_EDIT, m_edtDiscount);
	DDX_Control(pDX, IDC_ADD_TAX_APPLY_TYPE_COMBO2, m_cmbAddTaxApplyType);


	DDX_Control(pDX, IDC_AUTO_CHARGE_CREATE_CHECK, m_chkAutoChargeCreate);
	
	DDX_Control(pDX, IDC_CASH_APPLY_CHECK, m_chkCashApply);
	DDX_Control(pDX, IDC_CREDIT_APPLY_CHECK, m_chkCreditApply);
	DDX_Control(pDX, IDC_ONLINE_APPLY_CHECK, m_chkOnlineApply);
	DDX_Control(pDX, IDC_TRANS_APPLY_CHECK, m_chkTransApply);

	DDX_CBIndex(pDX, IDC_ADD_TAX_APPLY_TYPE_COMBO2, m_nAddTaxApplyType);
	DDX_Check(pDX, IDC_CASH_APPLY_CHECK, m_bCashApply);
	DDX_Check(pDX, IDC_CREDIT_APPLY_CHECK, m_bCreditApply);
	DDX_Check(pDX, IDC_ONLINE_APPLY_CHECK, m_bOnlineApply);
	DDX_Check(pDX, IDC_TRANS_APPLY_CHECK, m_bTransApply);
	DDX_Control(pDX, IDC_NOT_SHOW_CASH_CHECK, m_chkNotShowCash);
	DDX_Control(pDX, IDC_ABLE_USE_CHARGE_COMBO, m_cmbAbleUseCharge);
	DDX_Control(pDX, IDC_INIT_DAY_COMBO, m_cmbInitDay);
	DDX_Control(pDX, IDC_INTERCALL_NOTVIEW_AMOUNT_COMBO, m_cmbInterCallNotViewAmount);
	DDX_Control(pDX, IDC_DIRECT_DISCOUNT_COMBO, m_cmbDirectDiscount);
	DDX_Control(pDX, IDC_DIRECT_DISCOUNT_EDIT, m_edtDirectDiscount);
	DDX_Control(pDX, IDC_DIRECT_DISCOUNT_RANGE_EDIT, m_edtDirectDiscouintRange);
	DDX_Control(pDX, IDC_MANAGER_IS_ORDERINPUT_CHECK, m_chkManagerIsOrderInput);
	DDX_Text(pDX, IDC_DIRECT_DISCOUNT_EDIT, m_strDirectDiscount);
	DDX_Text(pDX, IDC_DIRECT_DISCOUNT_RANGE_EDIT, m_strDirectDiscountRange);	
	DDX_CBString(pDX, IDC_ABLE_USE_CHARGE_COMBO, m_strAbleUseCharge);

	DDX_Control(pDX, IDC_AUTO_CALCULATE_COMBO, m_cmbAutoCalculate);
	DDX_Control(pDX, IDC_TAX_TYPE_COMBO, m_cmbTaxType);

	DDX_Control(pDX, IDC_DT_PAYMENT_COMBO, m_cmbPayMentAdd);
	DDX_Control(pDX, IDC_DT_BILL_COLLECTION_COMBO, m_cmbBillCollectionAdd);

	DDX_Control(pDX, IDC_GNO_ALL_CHECK, m_chkGNoAll);
	DDX_Control(pDX, IDC_GNO_PERSON_CHECK, m_chkGNoPerson);
	DDX_Control(pDX, IDC_GNO_MULTI_CHECK, m_chkGNoMulti);
	DDX_Control(pDX, IDC_GROUP_REPORT_COUNT_STATIC, m_stcGNoReportCount);
	DDX_Control(pDX, IDC_GNO_INIT_BTN, m_btnGNoInit);
	DDX_Control(pDX, IDC_GNO_ADD_BTN, m_btnGNoAdd);
	DDX_Control(pDX, IDC_GNO_DEL_BTN, m_btnGNoDel);
	DDX_Control(pDX, IDC_GNO_FULLL_BTN, m_btnGNoFull);
	DDX_Control(pDX, IDC_GNO_LIST, m_lstGNo);
	DDX_Control(pDX, IDC_INTERCALL_GROUP_OWNER_CHECK, m_chkIntercallGroupOwner);
	
}


BEGIN_MESSAGE_MAP(CAddGroupDlg, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOkBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_BN_CLICKED(IDC_COPORATION_CHARGE_CHECK, OnBnClickedCoporationChargeCheck)
	ON_CBN_SELCHANGE(IDC_REPORT_SECOND_DAY_COMBO, OnCbnSelchangeReportSecondDayCombo)
	ON_CBN_SELCHANGE(IDC_REPORT_FIRST_DAY_COMBO, OnCbnSelchangeReportFirstDayCombo)
	ON_BN_CLICKED(IDC_SEARCH_CHARGE_LIST_BTN, OnBnClickedSearchChargeListBtn)
	ON_BN_CLICKED(IDC_AUTO_CHARGE_CREATE_CHECK, &CAddGroupDlg::OnBnClickedAutoChargeCreateCheck)
	ON_CBN_SELCHANGE(IDC_AUTO_CALCULATE_COMBO, &CAddGroupDlg::OnCbnSelchangeAutoCalculateCombo)
	ON_BN_CLICKED(IDC_GNO_INIT_BTN, &CAddGroupDlg::OnBnClickedGnoInitBtn)
	ON_BN_CLICKED(IDC_GNO_ADD_BTN, &CAddGroupDlg::OnBnClickedGnoAddBtn)
	ON_BN_CLICKED(IDC_GNO_ALL_CHECK, &CAddGroupDlg::OnBnClickedGnoAllCheck)
	ON_BN_CLICKED(IDC_GNO_DEL_BTN, &CAddGroupDlg::OnBnClickedGnoDelBtn)
	ON_BN_CLICKED(IDC_GNO_FULLL_BTN, &CAddGroupDlg::OnBnClickedGnoFulllBtn)
	ON_BN_CLICKED(IDC_GNO_PERSON_CHECK, &CAddGroupDlg::OnBnClickedGnoPersonCheck)
	ON_BN_CLICKED(IDC_GNO_MULTI_CHECK, &CAddGroupDlg::OnBnClickedGnoMultiCheck)
END_MESSAGE_MAP()


// CAddGroupDlg 메시지 처리기입니다.

BOOL CAddGroupDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	ChargeTypeNameRefresh();

	m_cmbReportFirstDay.SetCurSel(0);
	m_cmbReportSecondDay.SetCurSel(0);
	
	m_cmbInterCallNotViewAmount.SetCurSel(0);
	m_cmbAbleUseCharge.SetCurSel(0);
	m_cmbInitDay.SetCurSel(0);
	m_cmbDirectDiscount.SetCurSel(0);

	

	m_lstGNo.InsertColumn(0, "회사", DT_LEFT, 80, FALSE, FALSE );
	m_lstGNo.InsertColumn(1, "부서", DT_LEFT, 80, FALSE, FALSE );
	m_lstGNo.m_bHeader = TRUE;
	m_lstGNo.Populate();

	for(int i = 0; i < 32; i++)  // PayMentAdd 초기화
	{
		if(i == 0)
		{
			m_cmbPayMentAdd.InsertString(i, "정산일당일");
			m_cmbBillCollectionAdd.InsertString(i, "정산일당일");
		}
		else
		{
			CString strTemp = "";
			strTemp.Format("+ %d일",i);
			m_cmbPayMentAdd.InsertString(i, strTemp);
			m_cmbBillCollectionAdd.InsertString(i, strTemp);
		}
	}
	m_cmbPayMentAdd.SetCurSel(0);  // PayMentAdd 초기화 후에 있어야 함.
	m_cmbBillCollectionAdd.SetCurSel(0);


	if(m_bAdd == FALSE)  //수정
	{

		SetWindowText("그룹 수정");
		m_chkAutoChargeCreate.ShowWindow(SW_HIDE);
		LoadGroup();
	}
	else		// 신규
	{
		this->SetWindowText("그룹 추가");
		m_chkAutoChargeCreate.SetCheck(TRUE);
		if(m_nGNo> 0)
		{
			LoadGroup();
			GetDlgItem(IDC_GROUP_NAME_EDIT)->SetWindowText(m_cg.GetGroupData(m_nGNo)->strGroupName);

			GetDlgItem(IDC_ID_EDIT)->SetWindowText("");
			GetDlgItem(IDC_PWD_EDIT)->SetWindowText("");
		}
		else
		{
			m_cmbReportFirstDay.SetCurSel(1);
			m_cmbAddTaxApplyType.SetCurSel(0);
			m_cmbAutoCalculate.SetCurSel(0);
			m_cmbTaxType.SetCurSel(0);
			m_cmbPayMentAdd.SetCurSel(0);
			m_cmbBillCollectionAdd.SetCurSel(0);
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAddGroupDlg::LoadGroup()
{
	UpdateData();
	m_cg.GetGroupData(m_nGNo)->strName;

	CString strGNoList = "", strTemp = ""; int nCurPos = 0;
	
	char buffer[10];
	CStringArray sArr;
	
	ST_CUSTOMER_GROUP_INFOMATION *pGroup = m_cg.GetGroupData(m_nGNo);
 
	m_strGroupName = pGroup->strGroupName;
	m_strDept = pGroup->strDept;
	m_strName = pGroup->strName;
	m_strMemberTel = GetDashPhoneNumber(pGroup->strMemberTel);
	m_strManagerHP = GetDashPhoneNumber(pGroup->strManagerHP);
	m_strID = pGroup->strID;
	m_strPwd = pGroup->strPassword;
	m_strEmail = pGroup->strEmail;
	m_strDetaileEtc = pGroup->strDetail;
	m_strRiderDeposit = ltoa(pGroup->nDepositRate, buffer,10);	

	m_chkCoporationCharge.SetCheck(pGroup->nCharge > 0 ? TRUE : FALSE);

	m_strPresident = pGroup->strPresident;
	m_strBusinessStatus = pGroup->strBusinessStatus;
	m_strBussinessCategroy = pGroup->strBusinessCategory;
	m_strBussinessNo = pGroup->strBusinessNo;
	m_strArea = pGroup->strArea;		

	m_nAddTaxApplyType = pGroup->nAddTaxApplyType;
	m_bCashApply = pGroup->bCashApply;
	m_bCreditApply = pGroup->bCreditApply;
	m_bOnlineApply = pGroup->bOnlineApply;
	m_bTransApply = pGroup->bTransApply;
	m_strDiscount = GetMyNumberFormat(pGroup->nDiscount);

	if(pGroup->nDirectDiscountType >0)
	{
		m_cmbDirectDiscount.SetCurSel(pGroup->nDirectDiscountType);
		m_strDirectDiscount = GetMyNumberFormat(pGroup->nDirectDiscount);
		m_strDirectDiscountRange = GetMyNumberFormat(pGroup->nDirectDiscountRange);
	}
	else
	{
		m_cmbDirectDiscount.SetCurSel(0);
		m_strDirectDiscount = GetMyNumberFormat(0);
		m_strDirectDiscountRange = GetMyNumberFormat(0);
	}

	m_cmbAutoCalculate.SetCurSel(pGroup->nAutoCalculate);
	m_cmbTaxType.SetCurSel(pGroup->nElectronicTaxType);

	strGNoList = pGroup->strGNoList;
	if(strGNoList.GetLength() > 3 && m_cmbAutoCalculate.GetCurSel() > 0)
	{
		GetParseToken(strGNoList, ",", sArr);	
		int i = 0;
		for(i = 0; i < sArr.GetCount(); i++)
		{
			long nTempGNo = 0; CString strTempName , strTempDept;
			nTempGNo = atol(sArr.GetAt(i));

			strTempName = m_cg.GetGroupData(nTempGNo)->strGroupName;
			strTempDept = m_cg.GetGroupData(nTempGNo)->strDept;

			m_lstGNo.MyAddItem(0, strTempName, "", 80,FALSE, DT_LEFT);
			m_lstGNo.MyAddItem(1, strTempDept, "", 60,FALSE, DT_LEFT);
			m_lstGNo.InsertItemDataLong(nTempGNo);
			m_lstGNo.EndItem();
		}	

		m_lstGNo.Populate();

		m_stcGNoReportCount.SetWindowText("지점수: " +GetMyNumberFormat(i+1));

		switch(pGroup->nGNoListType)
		{
		case 1:
			m_chkGNoAll.SetCheck(TRUE);
			break;
		case 2:
			m_chkGNoPerson.SetCheck(TRUE);
			break;
		case 3:
			m_chkGNoMulti.SetCheck(TRUE);
			break;

		}
		ShowAutoCalculateControl(TRUE);
	}
	

	strTemp = ::GetMyNumberFormat(pGroup->nAbleUseCharge);
	m_strAbleUseCharge = strTemp;
	m_cmbAbleUseCharge.SetWindowText(m_strAbleUseCharge);
	m_cmbInitDay.SetCurSel(max(pGroup->nInitDay - 1, 0));
	m_chkManagerIsOrderInput.SetCheck(pGroup->bManagerIsOrderInput);

	m_cmbReportFirstDay.SetCurSel(pGroup->nReportFirstDay);
	m_cmbReportSecondDay.SetCurSel(pGroup->nReportSecondDay);

	m_bCredit = pGroup->nCredit ==0 ? FALSE : TRUE;
	m_chkCredit.SetCheck(m_bCredit);
	m_edtDiscount.SetWindowText(itoa(pGroup->nDiscount, buffer,10));
	m_chkNotShowCash.SetCheck(pGroup->bNotShowCash);
	m_cmbInterCallNotViewAmount.SetCurSel(pGroup->nInterCallNotViewAmount);

	m_cmbBillCollectionAdd.SetCurSel(pGroup->nBillCollectionAdd<= 0 ? 0 : pGroup->nBillCollectionAdd);
	m_cmbPayMentAdd.SetCurSel(pGroup->nPayMentAdd <= 0 ? 0 : pGroup->nPayMentAdd);
	m_chkIntercallGroupOwner.SetCheck(pGroup->bIntercallGroupOwner);
											  
	
	GetChargeType();
	UpdateData(FALSE);

	m_cmbAbleUseCharge.SetWindowText(m_strAbleUseCharge);
}

void CAddGroupDlg::GetParseToken(CString strList, CString sToken, CStringArray &sArr)
{
	CString strWord ="", strRestList = strList;
	int nCurPos = 0;
	
	strWord = strList.Tokenize(",", nCurPos);
	if(strWord.GetLength() <= 0) return;
	
	sArr.Add(strWord);	
	while(strWord != "")
	{
		strWord = strList.Tokenize(",", nCurPos);
		if(strWord.GetLength() > 0)
			sArr.Add(strWord);	
	}

}

void CAddGroupDlg::GetChargeType()
{
	for(int i=0; i<m_cmbChargeType.GetCount(); i++)
	{
		long nCharge = (long)m_cmbChargeType.GetItemData(i);

		if(nCharge == m_cg.GetGroupData(m_nGNo)->nCharge)
		{
			m_cmbChargeType.SetCurSel(i);
			return;
		}
	}

	m_cmbChargeType.SetWindowText("");
	return;
}

void CAddGroupDlg::OnBnClickedOkBtn()
{
	if(m_chkAutoChargeCreate.GetCheck() && m_chkCoporationCharge.GetCheck())
	{
		MessageBox("법인요금 자동생성과 법인요금지정 체크가 되어있습니다 ", "확인", MB_ICONINFORMATION);
		return;
	}
	CString sChargeTypeName = ""; m_cmbChargeType.GetWindowText(sChargeTypeName);
	if(m_chkAutoChargeCreate.GetCheck() && sChargeTypeName.GetLength()<= 0  )
	{
		MessageBox("법인요금 명을 넣어주세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(m_bAdd == FALSE)
		EditGroup();
	else
		AddNewGroup();	
}

BOOL CAddGroupDlg::UniqueCheckTypeName()
{
	long nCompany = 0;
	if(m_nGNo > 0)
		nCompany = m_cg.GetGroupData(m_nGNo)->nCompany;
	else
		nCompany = GetCurBranchInfo()->nCompanyCode;

	CString sTypeChargeName = "";
	m_cmbChargeType.GetWindowText(sTypeChargeName);


	CMkCommand pCmd2(m_pMkDb, "select_typename_unique_check");		
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), nCompany);		
	pCmd2.AddParameter(sTypeChargeName);	
	CMkParameter *pPar = pCmd2.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	if(!pCmd2.Execute()) return FALSE;

	int nReturnType = 0;
	pPar->GetValue(nReturnType);

	if(nReturnType == 100 )
	{
		MessageBox("동일한 법인요금이 있습니다.  기존법인과 같거나 하위부서이면 기존요금제를 사용하세요! ", 
			"확인", MB_ICONINFORMATION);
		return FALSE;
	}
	else if(nReturnType == 200)
	{
		return TRUE;
	}
	return FALSE;
}

void CAddGroupDlg::AddNewGroup()
{
	UpdateData(TRUE);

	if((m_cmbReportFirstDay.GetCurSel() == 0) && (m_cmbReportSecondDay.GetCurSel() == 0))
	{
		if(MessageBox("정산일이 없습니까?\r\n정산일이 없을경우 자동정산이 이루어지지 않습니다", "확인", MB_ICONINFORMATION | MB_OKCANCEL) != IDOK)
		{
			return;
		}		
	}

	long nDepositRate, nDirectDiscountType = 0, nDirectDiscount =0, nDirectDiscountRange = 0;

	if(!::IsStringDigit(m_strRiderDeposit) && m_strRiderDeposit.GetLength() > 0)
	{
		MessageBox("기사입금액에 숫자를 넣어주세요", "확인", MB_ICONINFORMATION);
		return;
	}
	else if(m_strRiderDeposit.GetLength() == 0)
		m_strRiderDeposit = "0";

	if(m_chkAutoChargeCreate.GetCheck() && !UniqueCheckTypeName() )
		return;

	m_strMemberTel = m_strMemberTel.GetLength() > 0 ? GetNoneDashNumber(m_strMemberTel) : m_strMemberTel;
	m_strManagerHP = GetNoneDashNumber(m_strManagerHP);
	nDepositRate = m_strRiderDeposit.GetLength() > 0 ? atol(m_strRiderDeposit) : 0;
	//m_sBussinessNo = m_sBussinessNo.GetLength() > 0 ? GetNoneDashNumber(m_sBussinessNo) : m_sBussinessNo;	

	long nCompany = 0;

	if(m_cmbDirectDiscount.GetCurSel() > 0)
	{
		nDirectDiscountType = m_cmbDirectDiscount.GetCurSel();
		nDirectDiscount = GetMyUnNumberFormat(m_strDirectDiscount);
		nDirectDiscountRange = GetMyUnNumberFormat(m_strDirectDiscountRange);
	}
	else
	{
		nDirectDiscountType = 0;
		nDirectDiscount = 0;
		nDirectDiscountRange = 0;
	}
	
	if(m_nGNo > 0)
	{
		nCompany = m_cg.GetGroupData(m_nGNo)->nCompany;
		m_cg.GetGroupData(m_nGNo)->nDirectDiscountType = nDirectDiscountType;
		m_cg.GetGroupData(m_nGNo)->nDirectDiscount = nDirectDiscount;
		m_cg.GetGroupData(m_nGNo)->nDirectDiscountRange = nDirectDiscountRange;		
	}
	else
	{
		nCompany = GetCurBranchInfo()->nCompanyCode;
	}

	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "insert_group_2011_9");	
	
	pCmd2.AddParameter(nCompany);		
	pCmd2.AddParameter(m_strGroupName);	
	pCmd2.AddParameter(m_strDept);
	pCmd2.AddParameter(m_strName);
	pCmd2.AddParameter(m_strMemberTel);
	pCmd2.AddParameter(m_strManagerHP);	
	pCmd2.AddParameter(m_strID);
	pCmd2.AddParameter(m_strPwd);
	pCmd2.AddParameter(m_strEmail);
	pCmd2.AddParameter(m_chkCoporationCharge.GetCheck());
	pCmd2.AddParameter((long)m_cmbChargeType.GetItemData(m_cmbChargeType.GetCurSel()));
	pCmd2.AddParameter(nDepositRate);		
	pCmd2.AddParameter(m_strDetaileEtc);
	pCmd2.AddParameter(m_strPresident);
	pCmd2.AddParameter(m_strBusinessStatus);
	pCmd2.AddParameter(m_strBussinessCategroy);
	pCmd2.AddParameter(m_strArea);
	pCmd2.AddParameter(m_strBussinessNo);
	pCmd2.AddParameter(m_cmbReportFirstDay.GetCurSel());
	pCmd2.AddParameter(m_cmbReportSecondDay.GetCurSel());
	pCmd2.AddParameter(m_chkCredit.GetCheck());
	pCmd2.AddParameter(atol(m_strDiscount));
	pCmd2.AddParameter(m_nAddTaxApplyType);


	pCmd2.AddParameter(m_bCashApply);
	pCmd2.AddParameter(m_bCreditApply);
	pCmd2.AddParameter(m_bOnlineApply);
	pCmd2.AddParameter(m_bTransApply);
	pCmd2.AddParameter(m_chkNotShowCash.GetCheck());
	pCmd2.AddParameter(m_cmbInitDay.GetCurSel() + 1);
	pCmd2.AddParameter(atoi(m_strAbleUseCharge));
	pCmd2.AddParameter(m_nGNo);		
	pCmd2.AddParameter(m_chkAutoChargeCreate.GetCheck());	
	pCmd2.AddParameter(m_cmbInterCallNotViewAmount.GetCurSel());	
	pCmd2.AddParameter(nDirectDiscount);	
	pCmd2.AddParameter(nDirectDiscountType);	
	pCmd2.AddParameter(nDirectDiscountRange);	
	pCmd2.AddParameter(m_chkManagerIsOrderInput.GetCheck());	
	pCmd2.AddParameter(m_cmbAutoCalculate.GetCurSel());	
	pCmd2.AddParameter(m_cmbTaxType.GetCurSel());	
	pCmd2.AddParameter(m_cmbBillCollectionAdd.GetCurSel());	
	pCmd2.AddParameter(m_cmbPayMentAdd.GetCurSel());	
	pCmd2.AddParameter(GNoListString());	
	pCmd2.AddParameter(GetListTypeCheck());	
	pCmd2.AddParameter(m_chkIntercallGroupOwner.GetCheck() );	

	CMkParameter *pPar = pCmd2.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if(!pCmd2.Execute())
	{
		MessageBox("입력이 실패되었습니다.", "확인", MB_ICONINFORMATION);		
		return;
	}

	long nNewGNo; pPar->GetValue(nNewGNo);

	MakeGrouopReport(nNewGNo, m_cmbReportFirstDay.GetCurSel(), m_cmbReportSecondDay.GetCurSel());

	if(m_chkAutoChargeCreate.GetCheck())
		m_cg.FillCharge();
	
	m_cg.FillData();

	OnOK();
}

void CAddGroupDlg::MakeGrouopReport(long nGNo, long nFirstDay, long nSecondDay)
{
	if((nFirstDay == 0) && (nSecondDay == 0))
		return;

	CMkCommand pCmd(m_pMkDb, "make_group_report_six_month");
	pCmd.AddParameter(nGNo);
	pCmd.AddParameter(nFirstDay);
	pCmd.AddParameter(nSecondDay);

	pCmd.Execute();
}

void CAddGroupDlg::EditGroup()
{
	try
	{
		UpdateData();
		long nDepositRate;
		long nOldDiscount = 0, nOldTaxApplyType = -1;

		if(m_chkAutoChargeCreate.GetCheck() && !UniqueCheckTypeName() )
			return;

		if(!::IsStringDigit(m_strRiderDeposit) && m_strRiderDeposit.GetLength() > 0)
			throw("기사입금액에 숫자를 넣어주세요");
		else if(m_strRiderDeposit.GetLength() == 0)
			m_strRiderDeposit = "0";

		m_strMemberTel = m_strMemberTel.GetLength() > 0 ? GetNoneDashNumber(m_strMemberTel) : m_strMemberTel;
		nDepositRate = m_strRiderDeposit.GetLength() > 0 ? atol(m_strRiderDeposit) : 0;
		m_strManagerHP = GetNoneDashNumber(m_strManagerHP);
		ST_CUSTOMER_GROUP_INFOMATION * pData = m_cg.GetGroupData(m_nGNo);

		if(pData == NULL) return;

		m_strDiscount.Replace(",", "");
		nOldDiscount = pData->nDiscount;
		nOldTaxApplyType = pData->nAddTaxApplyType;

		pData->strGroupName = m_strGroupName;
		pData->strDept = m_strDept;
		pData->strName = m_strName;
		pData->strMemberTel = m_strMemberTel;
		pData->strManagerHP = m_strManagerHP;
		pData->strID = m_strID;
		pData->strPassword = m_strPwd;
		pData->strEmail = m_strEmail;
		pData->nCharge = m_chkCoporationCharge.GetCheck() == TRUE ? (long)m_cmbChargeType.GetItemData(m_cmbChargeType.GetCurSel()) : 0;
		if(m_chkCoporationCharge.GetCheck() == TRUE)
			m_cmbChargeType.GetLBText(m_cmbChargeType.GetCurSel(), pData->strChargeName);
		else
			pData->strChargeName = "";

		pData->nDepositRate = nDepositRate;
		pData->strDetail = m_strDetaileEtc;
		pData->strPresident = m_strPresident;
		pData->strBusinessStatus = m_strBusinessStatus;
		pData->strBusinessCategory = m_strBussinessCategroy;
		pData->strArea = m_strArea;
		pData->strBusinessNo = m_strBussinessNo;
		pData->nReportFirstDay = m_cmbReportFirstDay.GetCurSel();
		pData->nReportSecondDay = m_cmbReportSecondDay.GetCurSel();
		pData->nCredit = m_chkCredit.GetCheck();
		
		pData->nDiscount = atol(m_strDiscount);
		pData->nAddTaxApplyType = m_nAddTaxApplyType;
		pData->bCashApply = m_bCashApply;
		pData->bCreditApply = m_bCreditApply;
		pData->bOnlineApply = m_bOnlineApply;
		pData->bTransApply = m_bTransApply;
		pData->bNotShowCash = m_chkNotShowCash.GetCheck();
		pData->nInitDay = m_cmbInitDay.GetCurSel() + 1;
		pData->nAbleUseCharge = atoi(m_strAbleUseCharge);
		pData->nInterCallNotViewAmount = m_cmbInterCallNotViewAmount.GetCurSel();
		pData->bManagerIsOrderInput = m_chkManagerIsOrderInput.GetCheck();
		if(m_cmbDirectDiscount.GetCurSel() > 0)
		{
			pData->nDirectDiscountType = m_cmbDirectDiscount.GetCurSel();
			pData->nDirectDiscount = GetMyUnNumberFormat(m_strDirectDiscount);
			pData->nDirectDiscountRange = GetMyUnNumberFormat(m_strDirectDiscountRange);
		}
		else
		{
			pData->nDirectDiscountType = 0;
			pData->nDirectDiscount = 0;
			pData->nDirectDiscountRange = 0;
		}
		pData->nAutoCalculate = m_cmbAutoCalculate.GetCurSel();
		pData->nElectronicTaxType = m_cmbTaxType.GetCurSel();

		pData->nBillCollectionAdd = m_cmbBillCollectionAdd.GetCurSel();
		pData->nPayMentAdd = m_cmbPayMentAdd.GetCurSel();
		pData->strGNoList = GNoListString();
		pData->nGNoListType = GetListTypeCheck();	
		pData->bIntercallGroupOwner = m_chkIntercallGroupOwner.GetCheck();
		
		if(m_cg.SetGroupDataFull(m_nGNo, pData, pData->nLevel == 0 ? TRUE : FALSE))
			MessageBox("수정되었습니다.", "확인", MB_ICONINFORMATION);

		// 정산생성 창에서 할인율과 부가세 변경이 바뀔시 수정한것을 참조
		if(pData->nDiscount != nOldDiscount)
		{
			m_bDirtyDiscount = TRUE;
			m_nDirtyDiscount = pData->nDirectDiscount;
		}
		if(pData->nAddTaxApplyType != nOldTaxApplyType)
		{
			m_bDirtyTaxApply = TRUE;
			m_nDirtyTaxApply = pData->nAddTaxApplyType;
		}
		

		OnOK();
	}
	catch (char* e)
	{
		MessageBox(e, "확인", MB_ICONINFORMATION);
		return;
	}
}

BOOL CAddGroupDlg::PreTranslateMessage(MSG* pMsg)
{
	switch(::GetDlgCtrlID(pMsg->hwnd))
	{
	case IDC_GROUP_NAME_EDIT:
		if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
			GetDlgItem(IDC_DEPT_EDIT)->SetFocus();
		else if(pMsg->message == WM_KEYDOWN)
		{
			::LengthCheck(this->GetSafeHwnd(), IDC_GROUP_NAME_EDIT, IDC_LENGTH_STATIC, 30, "그룹명");
		}			
		else if(pMsg->message == WM_KEYUP)
		{
			if(m_bAdd)
			{
				CString sChargeTypeName = ""; 
				((CEdit*)GetDlgItem(IDC_GROUP_NAME_EDIT))->GetWindowText(sChargeTypeName);

				m_cmbChargeType.SetWindowText(sChargeTypeName);
			}
		}

		break;

	case IDC_DEPT_EDIT:
		if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
			GetDlgItem(IDC_NAME_EDIT)->SetFocus();
		else if(pMsg->message == WM_KEYDOWN)
			::LengthCheck(this->GetSafeHwnd(), IDC_DEPT_EDIT, IDC_LENGTH_STATIC, 50, "부서명");
		break;

	case IDC_NAME_EDIT:
		if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
			GetDlgItem(IDC_MEMBER_TEL_EDIT)->SetFocus();
		else if(pMsg->message == WM_KEYDOWN)
			::LengthCheck(this->GetSafeHwnd(), IDC_NAME_EDIT, IDC_LENGTH_STATIC, 15, "담당자이름");
		break;

	case IDC_MEMBER_TEL_EDIT:
		if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
			GetDlgItem(IDC_ID_EDIT)->SetFocus();
		else if(pMsg->message == WM_KEYDOWN)
			::LengthCheck(this->GetSafeHwnd(), IDC_MEMBER_TEL_EDIT, IDC_LENGTH_STATIC, 17, "대표번호");
		break;

	case IDC_ID_EDIT:
		if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
			GetDlgItem(IDC_PWD_EDIT)->SetFocus();
		else if(pMsg->message == WM_KEYDOWN)
			::LengthCheck(this->GetSafeHwnd(), IDC_ID_EDIT, IDC_LENGTH_STATIC, 15, "아이디");
		break;

	case IDC_PWD_EDIT:
		if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
			GetDlgItem(IDC_EMAIL_EDIT)->SetFocus();
		else if(pMsg->message == WM_KEYDOWN)
			::LengthCheck(this->GetSafeHwnd(), IDC_PWD_EDIT, IDC_LENGTH_STATIC, 15, "패스워드");
		break;

	case IDC_EMAIL_EDIT:
		if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
			GetDlgItem(IDC_COPORATION_CHARGE_CHECK)->SetFocus();
		else if(pMsg->message == WM_KEYDOWN)
			::LengthCheck(this->GetSafeHwnd(), IDC_EMAIL_EDIT, IDC_LENGTH_STATIC, 50, "이메일");
		break;

	case IDC_RIDER_DEPOSIT_EDIT:
		if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
			GetDlgItem(IDC_DETAIL_ETC_EDIT)->SetFocus();
		else if(pMsg->message == WM_KEYDOWN)
			::LengthCheck(this->GetSafeHwnd(), IDC_RIDER_DEPOSIT_EDIT, IDC_LENGTH_STATIC, 3, "기사입금비율");
		break;

	case IDC_DETAIL_ETC_EDIT:
		if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		{
			//GetDlgItem(IDC_PRESIDENT_EDIT)->SetFocus();
		}
		else if(pMsg->message == WM_KEYDOWN)
			::LengthCheck(this->GetSafeHwnd(), IDC_DETAIL_ETC_EDIT, IDC_LENGTH_STATIC, 500, "비고");
		break;

	case IDC_PRESIDENT_EDIT:
		if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
			GetDlgItem(IDC_BUSINESS_STATUS_EDIT)->SetFocus();
		else if(pMsg->message == WM_KEYDOWN)
			::LengthCheck(this->GetSafeHwnd(), IDC_PRESIDENT_EDIT, IDC_LENGTH_STATIC, 10, "대표자");
		break;

	case IDC_BUSINESS_STATUS_EDIT:
		if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
			GetDlgItem(IDC_BUSINEESS_NO_EDIT)->SetFocus();
		else if(pMsg->message == WM_KEYDOWN)
			::LengthCheck(this->GetSafeHwnd(), IDC_BUSINESS_STATUS_EDIT, IDC_LENGTH_STATIC, 20, "업태");
		break;
	case IDC_BUSINEESS_NO_EDIT:
		if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
			GetDlgItem(IDC_BUSINESS_CATEGORY_EDIT)->SetFocus();
		else if(pMsg->message == WM_KEYDOWN)
			::LengthCheck(this->GetSafeHwnd(), IDC_BUSINEESS_NO_EDIT, IDC_LENGTH_STATIC, 10, "사업자번호");
		break;
	case IDC_BUSINESS_CATEGORY_EDIT:
		if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
			GetDlgItem(IDC_COMPANY_AREA_EDIT)->SetFocus();
		else if(pMsg->message == WM_KEYDOWN)
			::LengthCheck(this->GetSafeHwnd(), IDC_BUSINESS_CATEGORY_EDIT, IDC_LENGTH_STATIC, 20, "업종");
		break;
	case IDC_COMPANY_AREA_EDIT:
		if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
			GetDlgItem(IDC_OK_BTN)->SetFocus();
		else if(pMsg->message == WM_KEYDOWN)
			::LengthCheck(this->GetSafeHwnd(), IDC_COMPANY_AREA_EDIT, IDC_LENGTH_STATIC, 100, "사업장주소");

		break;			
	default:
		if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
			pMsg->wParam = NULL;
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CAddGroupDlg::OnOK()
{

	CMyDialog::OnOK();
}

void CAddGroupDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}

void CAddGroupDlg::ChargeTypeNameRefresh()
{
	MAP_CHARGE_TYPE_NAME::iterator it;
	long nItem = 0;

	for(it = m_mapChargeType.begin(); it != m_mapChargeType.end(); it++)
	{
		m_cmbChargeType.InsertString(nItem, it->second.strChargeName);
		m_cmbChargeType.SetItemData(nItem++, it->first);
	}
}

void CAddGroupDlg::OnBnClickedCoporationChargeCheck()
{
	if(m_chkCoporationCharge.GetCheck() == FALSE)
		m_cmbChargeType.SetWindowText("");
	else
		m_chkAutoChargeCreate.SetCheck(FALSE);

}

void CAddGroupDlg::OnCbnSelchangeReportSecondDayCombo()
{
	CheckCombo();
}

void CAddGroupDlg::CheckCombo()
{
	long nFirstSel = m_cmbReportFirstDay.GetCurSel();
	long nSecondSel = m_cmbReportSecondDay.GetCurSel();

	if((nSecondSel < nFirstSel) &&
		nSecondSel != 0)
	{
		MessageBox("첫번째 정산일의 날짜가 두번째 정산일 날짜보다 큽니다", "확인", MB_ICONINFORMATION);
		m_cmbReportSecondDay.SetCurSel(0);
		return;
	}

	if((nSecondSel == nFirstSel) &&
		nFirstSel != 0)
	{
		MessageBox("첫번째 정산일과 두번째 정산일의 날짜가 같습니다", "확인", MB_ICONINFORMATION);
		m_cmbReportSecondDay.SetCurSel(0);
		return;
	}

	if(nFirstSel == 0 && nSecondSel > 0) 
	{
		MessageBox("첫번째 정산일로 설정해주세요", "확인", MB_ICONINFORMATION);
		m_cmbReportFirstDay.SetCurSel(m_cmbReportSecondDay.GetCurSel());
		m_cmbReportSecondDay.SetCurSel(0);
		return;
	}
}

void CAddGroupDlg::OnCbnSelchangeReportFirstDayCombo()
{
	CheckCombo();
}

void CAddGroupDlg::OnBnClickedSearchChargeListBtn()
{
	CSearchGroupDlg dlg;
	dlg.m_nCompany = GetCurBranchInfo()->nPayTable;
	dlg.m_nDataType = SG_DISCOUNT_COMPANY;
	if(dlg.DoModal() == IDOK)
	{
		CString sChargeName = dlg.m_strChargeName;
		long nChargeID = dlg.m_nChargeID;

		for(int i = 0; i < m_cmbChargeType.GetCount(); i++)
		{
			long nCmbChargeTypeID = (long)m_cmbChargeType.GetItemData(i);
			if(nCmbChargeTypeID == nChargeID)
			{
				m_cmbChargeType.SetCurSel(i);
				return;
			}
		}
	}
}

void CAddGroupDlg::OnBnClickedAutoChargeCreateCheck()
{
	if( m_chkAutoChargeCreate.GetCheck() )
	{
		m_chkCoporationCharge.SetCheck(FALSE);
	}
}

void CAddGroupDlg::OnCbnSelchangeAutoCalculateCombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	
	if(m_cmbAutoCalculate.GetCurSel() > 0)
	{
		ShowAutoCalculateControl(TRUE);		
	}
	else
	{
		ShowAutoCalculateControl(FALSE);		
	}
}

void CAddGroupDlg::ShowAutoCalculateControl(BOOL bShow)
{
	long nResult;
	nResult = (bShow) ? SW_SHOW : SW_HIDE;

	m_chkGNoAll.EnableWindow(nResult);
	m_chkGNoPerson.EnableWindow(nResult);
	//m_chkGNoMulti.EnableWindow(nResult);
	

	m_btnGNoInit.EnableWindow(nResult);
	m_btnGNoAdd.EnableWindow(nResult);
	m_btnGNoDel.EnableWindow(nResult);
	m_btnGNoFull.EnableWindow(nResult);

}
void CAddGroupDlg::OnBnClickedGnoInitBtn()
{
	GNoListAllUnCheck();
	GNoListInit();
	m_stcGNoReportCount.SetWindowText("지점수: 0");
}

void CAddGroupDlg::OnBnClickedGnoAddBtn()
{

	CString strSearchGroup = "";
	long nSelectGNo = 0;
	strSearchGroup = m_cg.GetGroupData(m_nGNo)->strGroupName;

	CSearchGroupDlg dlg;
	dlg.m_nCompany = GetCurBranchInfo()->nCompanyCode;
	dlg.m_nDataType = SG_GROUP;
	dlg.m_strSearch = strSearchGroup.GetLength() > 0 ? strSearchGroup : "";
	dlg.m_nAutoSearch = TRUE;
	if(dlg.DoModal() != IDOK) return;

	nSelectGNo = dlg.m_nGNo;

	if(nSelectGNo != m_nGNo && nSelectGNo > 0 && m_lstGNo.GetRecords()->GetCount() <= 0)
	{
		if( MessageBox("해당지사와 정산지사가 상이 합니다 그래도 진행하시겠습니까?", "확인",  MB_YESNO) == IDNO)
			return;
	}

	if(nSelectGNo > 0)
	{
		GNoListAdd(nSelectGNo);
	}

	if(GNoListInputAllSame() )
		m_chkGNoAll.SetCheck(TRUE);
	else if(m_lstGNo.GetRecords()->GetCount() > 1)
		m_chkGNoMulti.SetCheck(TRUE);
	

	int nCount = m_lstGNo.GetRecords()->GetCount();
	m_stcGNoReportCount.SetWindowText("지점수: " +GetMyNumberFormat(nCount));
	
}



void CAddGroupDlg::OnBnClickedGnoAllCheck()
{
	if(m_nGNo <= 0)
		return;

	GNoListStateCheck(0);
	GNoListAll();

	
}
void CAddGroupDlg::OnBnClickedGnoPersonCheck()
{
	if(m_nGNo <= 0)
		return;


	GNoListStateCheck(1);
	GNoListInit();
	GNoListPerson(m_nGNo);
	m_stcGNoReportCount.SetWindowText("지점수: 1");
	m_lstGNo.Populate();
}



void CAddGroupDlg::OnBnClickedGnoDelBtn()
{

	if(m_nGNo <= 0)
		return;

	if( m_lstGNo.GetRecords()->GetCount() <= 0 )
	{
		MsgBox("삭제할 리스트가 없습니다. ");
		return;

	}

	if(m_lstGNo.GetSelectedRows()->GetCount() <= 0) return;

	for(int i = 0; i < m_lstGNo.GetSelectedRows()->GetCount(); i++)
	{
		CMyXTPGridRecord *pRecord = m_lstGNo.GetSelectedRowsGetAtGetRecord(i);
		pRecord->Delete();

	}

	if(m_lstGNo.GetRecords()->GetCount() == 0) 
	{		
		m_chkGNoAll.SetCheck(FALSE);
		m_chkGNoMulti.SetCheck(FALSE);
		m_chkGNoPerson.SetCheck(FALSE);		
	}
	else if(m_lstGNo.GetRecords()->GetCount() == 1) 
	{	
		m_chkGNoAll.SetCheck(FALSE);
		m_chkGNoMulti.SetCheck(FALSE);
		m_chkGNoPerson.SetCheck(TRUE);
	}
	else
	{
		m_chkGNoAll.SetCheck(FALSE);
		m_chkGNoMulti.SetCheck(TRUE);
		m_chkGNoPerson.SetCheck(FALSE);

	}

	m_lstGNo.Populate();
	int nCount = m_lstGNo.GetRecords()->GetCount();
	m_stcGNoReportCount.SetWindowText("지점수: " + GetMyNumberFormat(nCount));
}

void CAddGroupDlg::OnBnClickedGnoFulllBtn()
{
	OnBnClickedGnoAllCheck();
	m_chkGNoAll.SetCheck(TRUE);

}
CString CAddGroupDlg::GNoListString()
{
	CString strGNoList = "",strTemp = "";
	for(int i = 0; i < m_lstGNo.GetRecords()->GetCount(); i++)
	{
		strTemp.Format("%d," , m_lstGNo.GetRecordsGetAt(i)->GetItemDataLong());
		strGNoList += strTemp;
	}

	if(strGNoList.Right(1).Compare(",") == 0)
		strGNoList = strGNoList.Mid(0,strGNoList.GetLength() - 1 );

	return strGNoList;

}

int CAddGroupDlg::GetListTypeCheck()
{
	if(m_chkGNoAll.GetCheck()) return 1;
	else if(m_chkGNoPerson.GetCheck()) return 2;
	else if(m_chkGNoMulti.GetCheck()) return 3;

	return 0;
}

BOOL CAddGroupDlg::GNoListInputAllSame() 
{

	CString strGNoList = "",strTemp = "";
	CString strLoadGNoList = "";
	long nTempGNo = 0;
	map<long,long> mapGNo;
	map<long,long>::iterator it;
	for(int i = 0; i < m_lstGNo.GetRecords()->GetCount(); i++)
	{
		nTempGNo = m_lstGNo.GetRecordsGetAt(i)->GetItemDataLong();
		if(nTempGNo > 0)
			mapGNo[nTempGNo] = nTempGNo;
		
	}

	
	

	strLoadGNoList = m_cg.GetAllGNoListFromChildGNo(m_nGNo);
	CStringArray sArr;
	GetParseToken( strLoadGNoList, ",", sArr);

	if(sArr .GetCount() <= 0 ) return FALSE;

	for(int i = sArr.GetCount() -1; i >= 0; i--)
	{
		strTemp = sArr.GetAt(i);
		nTempGNo = atol(strTemp);
		it = mapGNo.find(nTempGNo);
		if(it != mapGNo.end())
		{
			sArr.RemoveAt(i);
		}
	}

	if(sArr.GetCount() == 0) return TRUE;

	return FALSE;

}
void CAddGroupDlg::GNoListInit()
{
	

	if(m_lstGNo.GetSelectedRows()->GetCount() <= 0) return;

	m_lstGNo.DeleteAllItem();
	m_lstGNo.Populate();

}
void CAddGroupDlg::GNoListPerson(long nGNo)
{
	GNoListInit();

	
	CString strTempName = "", strTempDept = "";
	strTempName = m_cg.GetGroupData(nGNo)->strGroupName;
	strTempDept = m_cg.GetGroupData(nGNo)->strDept;

	m_lstGNo.MyAddItem(0, strTempName, "", 80,FALSE, DT_LEFT);
	m_lstGNo.MyAddItem(1, strTempDept, "", 60,FALSE, DT_LEFT);
	m_lstGNo.InsertItemDataLong(nGNo);
	m_lstGNo.EndItem();

	
}	

void CAddGroupDlg::GNoListAdd(long nGNo)
{
	
	int nSame = 0;
	for(int i =0; i < m_lstGNo.GetRecords()->GetCount(); i++)
	{
		if( m_lstGNo.GetItemDataLong(i) == nGNo)
			nSame++;
	}

	if(nSame > 0) return;

	CString strTempName = "", strTempDept = "";
	strTempName = m_cg.GetGroupData(nGNo)->strGroupName;
	strTempDept = m_cg.GetGroupData(nGNo)->strDept;

	m_lstGNo.MyAddItem(0, strTempName, "", 80,FALSE, DT_LEFT);
	m_lstGNo.MyAddItem(1, strTempDept, "", 60,FALSE, DT_LEFT);
	m_lstGNo.InsertItemDataLong(nGNo);
	m_lstGNo.EndItem();

	m_lstGNo.Populate();
}	






void CAddGroupDlg::GNoListAll()
{
	GNoListInit();

	if( m_cg.GetGroupData(m_nGNo)->nParentGNo  > 0)
	{
		MsgBox("해당 고객사가 본사가 아닙니다.  본사(고객)에서 작업해주세요");
		return;

	}

	CString strGNoList = "";
	strGNoList = m_cg.GetAllGNoListFromChildGNo(m_nGNo);
	if(strGNoList.GetLength() <= 0)
	{
		MsgBox("해당 고객사의 고객이 올바로 만들어지지 않은것 같습니다. 로지소프트로 문의주세요");

		return;
	}

	CStringArray sArr;
	GetParseToken(strGNoList, ",", sArr);	

	for(int i = 0; i < sArr.GetCount(); i++)
	{
		long nTempGNo = 0; CString strTempName , strTempDept;
		nTempGNo = atol(sArr.GetAt(i));

		strTempName = m_cg.GetGroupData(nTempGNo)->strGroupName;
		strTempDept = m_cg.GetGroupData(nTempGNo)->strDept;

		m_lstGNo.MyAddItem(0, strTempName, "", 80,FALSE, DT_LEFT);
		m_lstGNo.MyAddItem(1, strTempDept, "", 60,FALSE, DT_LEFT);
		m_lstGNo.InsertItemDataLong(nTempGNo);
		m_lstGNo.EndItem();
	}	
	m_stcGNoReportCount.SetWindowText("지점수: " + GetMyNumberFormat(sArr.GetCount()));
	m_lstGNo.Populate();

}
void CAddGroupDlg::GNoListStateCheck(int nType)
{
	if(m_chkGNoAll.GetCheck() && nType == 0)
	{
		m_chkGNoMulti.SetCheck(!m_chkGNoAll.GetCheck());
		m_chkGNoPerson.SetCheck(!m_chkGNoAll.GetCheck());
	}
	else  if(m_chkGNoPerson.GetCheck() && nType == 1)
	{
		m_chkGNoAll.SetCheck(!m_chkGNoPerson.GetCheck());
		m_chkGNoMulti.SetCheck(!m_chkGNoPerson.GetCheck());
	}
	else if(m_chkGNoMulti.GetCheck() && nType == 2)
	{
		m_chkGNoAll.SetCheck(!m_chkGNoMulti.GetCheck());
		m_chkGNoPerson.SetCheck(!m_chkGNoMulti.GetCheck());
	}
}
void CAddGroupDlg::GNoListAllUnCheck()
{
	m_chkGNoAll.SetCheck(FALSE);
	m_chkGNoMulti.SetCheck(FALSE);
	m_chkGNoPerson.SetCheck(FALSE);
}



void CAddGroupDlg::OnBnClickedGnoMultiCheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
