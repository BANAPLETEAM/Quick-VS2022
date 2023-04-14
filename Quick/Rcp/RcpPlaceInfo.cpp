
#include "StdAfx.h"
#include "resource.h"
#include "RcpPlaceInfo.h"
#include "RcpDlg.h"
#include "SearchPOIDlg.h"
#include "SimpleMapDlg.h"
#include "CustomerDlg.h"
#include "RcpView.h"
#include "RcpDlgSetupDlg.h"
#include "RcpDlgMapDlg.h"
#include "POIDataAddress.h"

#define TEMP_ID	0xFF00
#define CREATE_EDIT(x, y) x = new CEdit(); x->Create(ES_LEFT, CRect(0, 0, 0, 0), m_pRcpDlg, TEMP_ID + y);
#define CREATE_COMBO(x, y) x = new CComboBox(); x->Create(ES_LEFT, CRect(0, 0, 0, 0), m_pRcpDlg, TEMP_ID + y);
#define CREATE_STATIC(x, y) x = new CMarkupStatic(); x->Create("", 0, CRect(0, 0, 0, 0), m_pRcpDlg, TEMP_ID + y);
#define SET_EMPTY_STRING(x) if(x != NULL) {x->SetWindowText("");}
#define TEMP_PLACE	0x1000
 

enum { REPLACE_PHONE_QUERY = 0, REPLACE_PHONE_MOVE = 1, REPLACE_PHONE_DONT_MOVE = 2};


CRcpPlaceInfo::CRcpPlaceInfo(CWnd *pwndParent, long nPlaceType)
{
	m_pRcpDlg = (CRcpDlg*)pwndParent;

	m_nPlaceType = nPlaceType;
	if(m_nPlaceType == PLACE_ORDER)
		m_strPlaceName = "의뢰지";
	else if(m_nPlaceType == PLACE_START)
		m_strPlaceName = "출발지";
	else if(m_nPlaceType == PLACE_DEST)
		m_strPlaceName = "도착지";
	

	if(nPlaceType > PLACE_TYPE_DEST && nPlaceType != PLACE_TYPE_CUSTOMER)
	{
		CREATE_EDIT(m_pedtSearch, 0);
		CREATE_EDIT(m_pedtCompany, 1);
		CREATE_EDIT(m_pedtDepart, 2);
		CREATE_EDIT(m_pedtManager, 3);
		CREATE_STATIC(m_pstcAddress, 4);
		CREATE_EDIT(m_pedtDetail, 5);
		CREATE_EDIT(m_pedtMemo, 6);
		CREATE_EDIT(m_pedtPhone, 7);
		CREATE_EDIT(m_pedtMP, 8);
		CREATE_EDIT(m_pedtCNo, 9);
		CREATE_EDIT(m_pedtDisplayDong, 10);
		//CREATE_COMBO(m_pcmbDelType, 11);
	}
	else
	{
		m_pedtSearch = NULL;
		m_pedtCompany = NULL;
		m_pedtDepart = NULL;
		m_pedtManager = NULL;
		m_pstcAddress = NULL;
		m_pedtDetail = NULL;
		m_pedtMemo = NULL;
		m_pedtPhone = NULL;
		m_pedtMP = NULL;
		m_pedtDisplayDong = NULL;
	}

	m_pPOI = NULL;
	m_pPrePOI = NULL;
	m_bTempCNo = FALSE;
	m_nGNo = 0;
	m_nCustomerID = 0;
	m_nUseCount = 0;
	m_nCNo = 0;
	m_pStartPlace = NULL;
	m_pDestPlace = NULL;
	m_pOrderPlace = NULL;
	m_pcmbDelType = NULL;
	m_pbSkipChangeDelType = NULL;
	m_bCredit = FALSE;
	m_pstcAddressNormal = NULL;

	m_pCustomerDlg = NULL;
	m_bManualDelType = FALSE;
	m_bStartDontAutoCopy = FALSE;
	m_bManualAddCustomer = FALSE;
}

CRcpPlaceInfo::~CRcpPlaceInfo(void)
{
	if(m_nPlaceType > PLACE_TYPE_DEST && m_nPlaceType != PLACE_TYPE_CUSTOMER)
	{
		DELETE_OBJECT(m_pedtSearch);
		DELETE_OBJECT(m_pedtCompany);
		DELETE_OBJECT(m_pedtDepart);
		DELETE_OBJECT(m_pedtManager);
		DELETE_OBJECT(m_pstcAddress);
		DELETE_OBJECT(m_pedtDetail);
		DELETE_OBJECT(m_pedtMemo);
		DELETE_OBJECT(m_pedtPhone);
		DELETE_OBJECT(m_pedtMP);
		DELETE_OBJECT(m_pedtCNo);
		DELETE_OBJECT(m_pedtDisplayDong);
	}

	DELETE_OBJECT(m_pCustomerDlg);
}

void CRcpPlaceInfo::SetControl(CEdit *pedtSearch, CEdit *pedtCNo, CEdit *pedtCompany, CEdit *pedtDepart, 
		CEdit *pedtManager, CMarkupStatic *pstcAddress, CStatic *pstcAddressNormal, CEdit *pedtDetail, 
		CEdit *pedtMemo, CEdit *pedtPhone, CEdit *pedtMP, CEdit *pedtDisplayDong,
		CComboBox *pcmbDelType, CButton *pbtnShowPhoneType, BOOL *pbSkipChangeDelType)
{
	m_pedtSearch = pedtSearch;
	m_pedtCNo = pedtCNo;
	m_pedtCompany = pedtCompany;
	m_pedtDepart = pedtDepart;
	m_pedtManager = pedtManager;
	m_pstcAddress = pstcAddress;
	m_pstcAddressNormal = pstcAddressNormal;
	m_pedtDetail = pedtDetail;
	m_pedtMemo = pedtMemo;
	m_pedtPhone = pedtPhone;
	m_pedtMP = pedtMP;
	m_pedtDisplayDong = pedtDisplayDong;
	m_pcmbDelType = pcmbDelType;
	m_pbSkipChangeDelType = pbSkipChangeDelType;
	m_pbtnShowPhoneType = pbtnShowPhoneType;
}

void CRcpPlaceInfo::SetControl(CEdit *pedtSearch, CMarkupStatic *pstcAddress, CStatic *pstcAddressNormal, CEdit *pedtDetail,
							   CEdit *pedtCompany, CEdit *pedtPhone, CEdit *pedtMP, CEdit *pedtDisplayDong)
{
	m_pedtSearch = pedtSearch;
	m_pstcAddress = pstcAddress;
	m_pstcAddressNormal = pstcAddressNormal;
	m_pedtDetail = pedtDetail;
	m_pedtCNo = NULL;
	m_pedtCompany = pedtCompany;
	m_pedtDepart = NULL;
	m_pedtManager = NULL;
	m_pedtMemo = NULL;
	m_pedtPhone = pedtPhone;
	m_pedtMP = pedtMP;
	m_pedtDisplayDong = pedtDisplayDong;
	m_pcmbDelType = NULL;
	m_pbSkipChangeDelType = NULL;
}

void CRcpPlaceInfo::Clear()
{
	m_bManualDelType = 0;

	SetSearch("");
	SetCNo(0);
	SetGNo(0);
	GetCNoEdit()->SetWindowText("");
	SetCompany("");
	SetDepart("");
	SetManager("");
	SetAddress("");
	SetDetail("");
	SetMemo("");
	SetPhone("");
	SetPhone("", TRUE);
	SetMP("");
	SetPOI(NULL);
	SetDisplayDong("");
	SetDetailPos(0, 0);
	SetCredit(0);
	SetPrePOI(NULL);
	//CheckDelType();
	RefreshCompanyColor();
}

CString CRcpPlaceInfo::GetCustomerTypeString(long nCNo, long nID, CString strUserID)
{
	char buffer[10];

	if(nCNo == 0) return "지명";
	else if(strUserID.GetLength() > 0) return strUserID;
	else if(nID <= 0) return "임시고객";
	else return ltoa(nID, buffer, 10);
}

BOOL CRcpPlaceInfo::MakeSearchQuery(CString strSource, CString &strKeyword, UINT *pnType)
{
	if(IsPhoneNumber(strSource)) 
	{
		if(strSource.GetAt(0) == '-')
		{
			strKeyword = GetNoneDashNumber(strSource);
			*pnType = ST_ID;
		}
		else
		{
			strKeyword = GetNoneDashNumber(strSource);
			if(strKeyword.Left(m_ci.m_strDDD.GetLength()) == m_ci.m_strDDD)
				strKeyword = strKeyword.Right(strKeyword.GetLength() - m_ci.m_strDDD.GetLength());
			*pnType = ST_PHONE;
		}
	}
	else {
		if(strSource.GetAt(0) == '-')
		{
			strSource.Replace("-", "");
			strKeyword = strSource;
			*pnType = ST_ID;
		}
		else if(strSource.GetAt(0) == '~')
		{
			strSource.Replace("~", "");
			strKeyword = strSource;
			*pnType = ST_NAME_DEPART;
		}
		else
		{
			strKeyword = strSource;
			*pnType = ST_COMPANY;
		}
	}

	return TRUE;
}

BOOL CRcpPlaceInfo::SearchCustomerCNo(long nCNo, BOOL bQueryWithoutCustomerDlg, BOOL bAloneItemAutoClosed, 
									long nTelID, BOOL bCopyStart)
{
	if(GetPlaceType() == PLACE_TYPE_CUSTOMER)
	{
		AfxMessageBox("고객은 선택하실 수 없습니다", MB_ICONINFORMATION);
		return FALSE;
	}

	if(bQueryWithoutCustomerDlg) 
	{
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "select_customer_one_2011_13");
		pCmd.AddParameter(nCNo == 0 ? GetCNo() : nCNo);
		pCmd.AddParameter(m_pRcpDlg->m_pBi->nCustomerTable); 
		pCmd.AddParameter(nTelID);

		if(pRs.Execute(&pCmd))
		{
			if(pRs.GetRecordCount() > 0)
			{
				CString strCompany, strDepart, strManager, strPhone, strDisplayDong;
				CString strAddress, strDetail, strMemo, strUserID, strPhone2, strTelSms, strTelTemp, strRiderMemo;
				long nDongID, nPosX, nPosY, nCustomerID, nGNo, nUseCount, nDiscountRange = 0;
				BOOL bHasDetailPos, bCredit, bNotAutoShareOrder, bPopupCustomerDlg, bOnlinePopup;
				long nCancelCount, nMileageBalance, nCustomerGrade, nCustomerColor, nMemoColor, nShowPhoneType, nOnlinePopupCharge;
				long nTempCNo = 0;

				pRs.GetFieldValue("sCompany", strCompany);
				pRs.GetFieldValue("sDepart", strDepart);
				pRs.GetFieldValue("sName", strManager);
				pRs.GetFieldValue("sTel1", strPhone);
				pRs.GetFieldValue("sTel2", strPhone2);
				pRs.GetFieldValue("sTelSms", strTelSms);
				pRs.GetFieldValue("sTelTemp", strTelTemp);
				pRs.GetFieldValue("nDongIDA", nDongID);
				pRs.GetFieldValue("bHasDetailPos", bHasDetailPos);
				pRs.GetFieldValue("nPosXA", nPosX);
				pRs.GetFieldValue("nPosYA", nPosY);
				pRs.GetFieldValue("sAddressA", strAddress);
				pRs.GetFieldValue("sLocationA", strDetail);
				pRs.GetFieldValue("sMemo", strMemo);
				pRs.GetFieldValue("sRiderMemo", strRiderMemo);
				pRs.GetFieldValue("sUserID", strUserID);
				pRs.GetFieldValue("nID", nCustomerID);
				pRs.GetFieldValue("nGNo", nGNo);
				pRs.GetFieldValue("sDong", strDisplayDong);
				pRs.GetFieldValue("bCredit", bCredit);
				pRs.GetFieldValue("nUseCount", nUseCount);
				pRs.GetFieldValue("nCancelCount", nCancelCount);
				pRs.GetFieldValue("nMileageBalance", nMileageBalance);
				pRs.GetFieldValue("nCustomerGrade", nCustomerGrade);
				pRs.GetFieldValue("nCustomerColor", nCustomerColor);
				pRs.GetFieldValue("nMemoColor", nMemoColor);
				pRs.GetFieldValue("nShowPhoneType", nShowPhoneType);
				pRs.GetFieldValue("bPopupCustomerDlg", bPopupCustomerDlg);
				pRs.GetFieldValue("bOnlinePopup", bOnlinePopup);
				pRs.GetFieldValue("nOnlinePopupCharge", nOnlinePopupCharge);
					
				CPOIDataNew::IsPosUsable(nPosX, nPosY);
				
				if(IsTempCNo())
					nTempCNo = GetCNo();
				
				if(m_pRcpDlg->m_pBi->bCallerIDToPhone1 && 
					m_pRcpDlg->m_nInitItem <= ZERO && 
					m_pRcpDlg->m_strCID.IsEmpty() == FALSE)
				{
					if(!m_pRcpDlg->m_pBi->bNotClientPhone1)
						strPhone = m_pRcpDlg->m_strCID; //옵션에서 전화1로 지정을 선택시 무조건 전화1로 넣음
					else
					{
						if(GetPlaceType() == PLACE_TYPE_START || 
							GetPlaceType() == PLACE_TYPE_DEST)
						{
							if(m_pOrderPlace->GetCNo() == nCNo)
								strPhone = m_pRcpDlg->m_strCID;							
						}
						else
							strPhone = m_pRcpDlg->m_strCID;
					}
				}

				if(strPhone.IsEmpty() && 
					m_pRcpDlg->m_nInitItem <= ZERO &&
					::IsThisCompany("이레퀵") == FALSE &&
					GetPlaceType() == PLACE_TYPE_ORDER)
					strPhone = m_pRcpDlg->m_strCID;

				if(strPhone.IsEmpty())
					strPhone = ::GetDashPhoneNumber(strTelTemp);

				if(GetPlaceType() == PLACE_TYPE_ORDER)
					m_pRcpDlg->m_edtSmsPhone.SetWindowText(::GetDashPhoneNumber(strTelSms));
				
				if(strPhone2.IsEmpty() && 
					::GetNoneDashNumber(strPhone) != GetNoneDashNumber(m_pRcpDlg->m_strCID) &&
					GetPlaceType() == PLACE_TYPE_ORDER)
					strPhone2 = ::GetDashPhoneNumber(m_pRcpDlg->m_strCID);

				SetData(nDongID, nPosX, nPosY, strDepart, strManager, strPhone, strDetail, 
					nCNo, nCustomerID, strUserID, nGNo, strMemo, strPhone2, strDisplayDong, 
					strCompany, bHasDetailPos, strAddress, nTelID, bCredit, nUseCount, nCancelCount, nMileageBalance, nShowPhoneType, FALSE);
	
				if(IsOrder())
				{			
					if(::IsThisCompany("사천퀵", m_pRcpDlg->m_pBi->nCompanyCode))
					{		
						m_pRcpDlg->SetGrade(-100);
					}
					else
					{
						m_pRcpDlg->m_edtOrderMemo.SetUserTextColor(nMemoColor);					
						m_pRcpDlg->SetGrade(nCustomerGrade);
					}
					

					BOOL bCreditAfterDis, bCredit, bDiscountApplyOnlyCredit;
					int nDiscount, nDiscountType;
					int nMileageType, nMileageValue, nMileageBalance;
					int nPriceGrade, nUseCount, nCancelCount;
					int nCouponCharge, nCouponType, nAllocGroup;
					long nMemCNo = 0;
					COleDateTime dtRegister, dtLastUse;

					pRs.GetFieldValue("bCreditAfterDiscount", bCreditAfterDis);
					pRs.GetFieldValue("nDiscount", nDiscount);
					pRs.GetFieldValue("nDiscountType", nDiscountType);
					pRs.GetFieldValue("nDiscountRange", nDiscountRange);
					pRs.GetFieldValue("nMileageType", nMileageType);
					pRs.GetFieldValue("nMileageValue", nMileageValue);
					pRs.GetFieldValue("nMileageBalance", nMileageBalance);
					pRs.GetFieldValue("nUseCount", nUseCount);
					pRs.GetFieldValue("nCancelCount", nCancelCount);
					pRs.GetFieldValue("dtRegister", dtRegister);
					pRs.GetFieldValue("dtLastUse", dtLastUse);
					pRs.GetFieldValue("bCredit", bCredit);
					pRs.GetFieldValue("nCouponCharge", nCouponCharge);
					pRs.GetFieldValue("nCouponType", nCouponType);
					pRs.GetFieldValue("nAllocGroup", nAllocGroup);
					pRs.GetFieldValue("nPriceGrade", nPriceGrade);
					pRs.GetFieldValue("nMemCNo", nMemCNo);
					pRs.GetFieldValue("bNotAutoShareOrder", bNotAutoShareOrder);
					pRs.GetFieldValue("bDiscountApplyOnlyCredit", bDiscountApplyOnlyCredit);

					m_pRcpDlg->SetChargeOrCouponInfo(bCredit, nPriceGrade, nCouponCharge, nCouponType); //요기에서 지불방식을 변경하고 밑의 할인타입이 들어가야합니다 choi 20111207

					if(m_pRcpDlg->m_bTodayOrder && m_pRcpDlg->m_nInitItem <= 0)
					{ 

						m_pRcpDlg->SetDiscountType( nGNo,  nDiscountType, nDiscount);
						/*
						if(nDiscount != 0 )
						{
							if(nDiscount > 0)
								m_pRcpDlg->m_nChargeAdd = nDiscount;
							else 
								m_pRcpDlg->m_nChargeDis = nDiscount;
						}
						else
						{
							m_pRcpDlg->m_nChargeAdd = 0;
							m_pRcpDlg->m_nChargeDis = 0;
						}
						m_pRcpDlg->m_nDiscountType = nDiscountType;
						*/
						
						//m_pRcpDlg->SetDiscountInfo(bCreditAfterDis, nDiscount, nDiscountType, nDiscountRange, bDiscountApplyOnlyCredit);						
						m_pRcpDlg->RefreshCharge();
					}

					m_pRcpDlg->SetMileageInfo(nMileageType, nMileageValue, nMileageBalance, m_nCNo, nMemCNo);

					RefreshTelCombo(strPhone, strPhone2);
					m_pRcpDlg->m_CMB_ALLOC_GROUP.pCombo->SetCurSel(nAllocGroup);
					m_pRcpDlg->SetTitleInfo(strCompany +  
									(strDepart.GetLength() > 0 ? "/" + strDepart : "")  + 
									(strManager.GetLength() > 0 ? "/" + strManager : ""));

					m_pRcpDlg->ShowCustomerInnerMemo(strMemo);
 
					if(m_pRcpDlg->m_pBi->bMemoToEtc)
						m_pRcpDlg->AddStringToEtc(strMemo);

					if(m_pRcpDlg->m_pBi->bRiderMemoToEtc)
						m_pRcpDlg->AddStringToEtc(strRiderMemo);

					if(m_pRcpDlg->m_pBi->bAutoShareOrder && bNotAutoShareOrder == TRUE)
						m_pRcpDlg->m_BTN_AUTO_SHARE_ORDER.pButton->SetCheck(FALSE);

					//임시고객인 경우에, 의뢰지가 바뀌면 연동된 출/도 고객이 자동으로 바꿔야함
					if(nTempCNo)
					{
						//Intercustomer 테이블의 임시고객번호를 실제고객번호로 매칭시킨다.
						CMkCommand pCmd(m_pMkDb, "update_intercustomer_cno");
						pCmd.AddParameter(typeLong, typeInput, sizeof(long), nTempCNo);	//TempCNo
						pCmd.AddParameter(typeLong, typeInput, sizeof(long), GetCNo());		//RealCNo
						pCmd.Execute();
	
						if(nTempCNo == m_pStartPlace->GetCNo())
							m_pStartPlace->Copy(this);

						if(nTempCNo == m_pDestPlace->GetCNo())
							m_pDestPlace->Copy(this);
					}
					else if(m_pStartPlace->IsEmpty() && !m_bStartDontAutoCopy)
					{
						if(bCopyStart)
						{
							m_pStartPlace->GetSearchEdit()->SetFocus(); //출발지검색에 주면 자동으로 도착지검색으로간다.
							m_pStartPlace->Copy(this);
						}						
						else
						{
							m_pStartPlace->GetCompanyEdit()->SetFocus();
						}
					}

					m_pRcpDlg->ReLocationAddCustomerBtn();
					m_pRcpDlg->ShowUsageHistory(TRUE);
					m_pRcpDlg->ShowCreditHistory(TRUE);
					m_pRcpDlg->CheckAutoSave();

					if(bOnlinePopup== TRUE && nOnlinePopupCharge > 0)
					{
						CString strTemp;
						strTemp.Format("해당 고객 송금건 %s원 아직 입금되지 않았습니다.", ::GetMyNumberFormat(nOnlinePopupCharge));
						MessageBox(m_pRcpDlg->m_hWnd, strTemp, "확인", MB_ICONINFORMATION);
					}

					if(bPopupCustomerDlg)
						m_pRcpDlg->ShowPlaceCustomerDlgBtn(this);

				}
				else if(m_pRcpDlg->IsStartDestPoi() )
				{
					m_pRcpDlg->GetSectionCharge();
				}
				
				return TRUE;
			}
		}
	}
	else
	{
		char buffer[20];
		return SearchCustomer(ltoa(nCNo == 0 ? GetCNo() : nCNo, buffer, 10), ST_CNO);
	}

	return FALSE;
}

void CRcpPlaceInfo::SetDataOnlyText(CString strName, CString strDisplayDong)
{
	Clear();
	SetCompany(strName);	//SetPhone, SetMP 보다 아래에 있어야함
	SetDisplayDong(strDisplayDong);
}

void CRcpPlaceInfo::SetData(long nDongID, long nPosX, long nPosY, CString strDepart, 
					CString strManager, CString strPhone1, CString strDetail, 
					long nCNo, long nCustomerID, CString strUserID, 
					long nGNo, CString strMemo, CString strPhone2, 
					CString strDisplayDong, CString strCompany,
					BOOL bHasDetailPos, CString strAddress, long nTelID,
					BOOL bCredit,long nUseCount, long nCancelCount, long nMileageBalance, long nShowPhoneType, BOOL bTempCNo, BOOL bEditMode)
{
	strPhone1 = GetDashPhoneNumber(strPhone1);
	strPhone2 = GetDashPhoneNumber(strPhone2);

	/*
	if(strPhone1.IsEmpty())
		strPhone1 = GetDashPhoneNumber(m_pRcpDlg->m_strCID);

	if(strPhone1 == strPhone2)
		strPhone2 = "";
	*/

	SetPhone(strPhone1);
	SetMP(strPhone2);
	SetDepart(strDepart);
	SetManager(strManager);
	SetDetail(strDetail);
	SetCNo(nCNo, bTempCNo, nCustomerID, strUserID, nUseCount, nCancelCount, nMileageBalance);
	SetGNo(nGNo);
	SetMemo(strMemo);
	SetShowPhoneType(nShowPhoneType);
	SetDisplayDong(strDisplayDong);
	SetCompany(strCompany);	//SetPhone, SetMP 보다 아래에 있어야함
	SetCredit(bCredit);
	SetData(nDongID, nPosX, nPosY, bHasDetailPos, strAddress);
	SetTelID(nTelID);
	SetPOI(m_poiNew.GetDongPOI(nDongID));
	CheckDelType();
}


void CRcpPlaceInfo::SetData(long nDongID, long nPosX, long nPosY, BOOL bHasDetailPos, CString strAddress)
{
	CPOIDataNew::IsPosUsable(nPosX, nPosY);
	SetPOI(m_poiNew.GetDongPOI(nDongID));
	SetDetailPos(nPosX, nPosY);

	if(nDongID > 0)	//상세위치인데, 주소정보가 없으면 무효처리한다.
	{
		if(strAddress == m_poiNew.GetDongPOI(nDongID)->GetRegionName(TRUE) || 
			strAddress == m_poiNew.GetDongPOI(nDongID)->GetRegionName())
		{
			strAddress = "";
		}
		
		if(strAddress.IsEmpty())
			bHasDetailPos = FALSE;
	}


	if(m_pPOI)
	{
		if(!bHasDetailPos && strAddress.IsEmpty()) //디비입력시 주소번지까지 입력불가...
		{
			CString strPOIMarkup, strPOINormal;
			CPOIUnit *pPOI = CSearchPOIDlg::SearchAddressResultOnly(m_pMkDb, &m_poiNew,
				GetDetail(), nDongID, strPOIMarkup, strPOINormal);
			if(pPOI)
			{
				if(strPOIMarkup.Find("자동인식") < 0)
				{
					int nPos = strPOIMarkup.Find("</TextBlock>");
					strPOIMarkup.Insert(nPos, "(자동인식)");
					//strPOINormal += "(자동인식)";
				}

				SetAddress(strPOIMarkup, strPOINormal);
				SetDetailPos(pPOI->GetPosX(), pPOI->GetPosY());
			}
			else
			{
				CPOIUnit *pDongPOI = m_poiNew.GetDongPOI(nDongID);
				SetAddress(CSearchPOI::GetMarkupLastPartHilight(pDongPOI), pDongPOI->GetRegionName());
			}
		}
		else if(nPosX > 0 && nPosY > 0 && !strAddress.IsEmpty())
		{
			CString strRegion = m_pPOI->GetRegionName();
			CString strReverseRegion = m_pPOI->GetRegionName(TRUE);

			strAddress.Replace(strRegion, "");
			strAddress.Replace(strReverseRegion, "");
			strRegion.Remove(' ');
			strReverseRegion.Remove(' ');
			strAddress.Replace(strRegion, "");
			strAddress.Replace(strReverseRegion, "");
			strAddress.TrimLeft();
			strAddress = m_pPOI->GetRegionName() + " " + strAddress;
			SetAddress(CSearchPOI::GetMarkupLastPartHilight(strAddress), strAddress);
		}
	}
	else
	{
		SetAddress("");
	}
}

BOOL CRcpPlaceInfo::SetData(long nPosX, long nPosY, BOOL bShowMsg)
{
	if(nPosX > 0 && nPosY > 0)
	{
		long nNewDongID;
		CString strNewAddress;
		if(CPOIDataAddress::GetNearAddress(m_pMkDb, nPosX, nPosY, nNewDongID, strNewAddress))
		{
			CPOIUnit *pPOI = m_poiNew.GetDongPOI(nNewDongID);
			if(pPOI)
			{
				if(bShowMsg)
				{
					CString strMsg;
					strMsg.Format("%s의 주소/위치를 [%s]로 설정하시겠시겠습니까?", 
								m_strPlaceName, strNewAddress);
					if(IDYES != m_pRcpDlg->MessageBox(strMsg, "주소/위치 변경 확인", MB_YESNO | MB_ICONQUESTION))
						return TRUE;
				}

				SetAddress(CSearchPOI::GetMarkupLastPartHilight(strNewAddress), strNewAddress);
				SetPOI(m_poiNew.GetDongPOI(nNewDongID));
				SetDetailPos(nPosX, nPosY);
				return TRUE;
			}
		}
	}
	
	return FALSE;
}

BOOL CRcpPlaceInfo::SearchCustomer(long nData, UINT nSearchType)
{
	char buffer[20];
	return SearchCustomer(ltoa(nData, buffer, 10), nSearchType);
}

BOOL CRcpPlaceInfo::SearchCustomer(CString strData, UINT nSearchType, BOOL bCIDSearch)
{
	CString strKeyword = strData;

	//if(strData.GetLength() == 0)
	//	return FALSE;

	if(nSearchType == ST_AUTO_DETECT)
		if(!MakeSearchQuery(strData, strKeyword, &nSearchType))
			return FALSE;

	if(m_pCustomerDlg == NULL)
	{
		m_pCustomerDlg = new CCustomerDlg;
		m_pCustomerDlg->Create(IDD_CUSTOMER_DLG, m_pRcpDlg);		
	}
	/*else
	{
		CCustomerDlg *pDlg = new CCustomerDlg;
		pDlg->Create(IDD_CUSTOMER_DLG);
		pDlg->m_chkShowDeleteCustomer.SetCheck(m_pCustomerDlg->m_chkShowDeleteCustomer.GetCheck());
		pDlg->m_chkMoveList.SetCheck(m_pCustomerDlg->m_chkMoveList.GetCheck());

		delete m_pCustomerDlg;
		m_pCustomerDlg = pDlg;
	}*/

	CBranchInfo *pBi = GetCurBranchInfo();

	m_pCustomerDlg->m_pParent = this;
	m_pCustomerDlg->m_pRcpDlg = (CRcpDlg*)m_pRcpDlg;
	m_pCustomerDlg->m_bNoneItemAutoCanceled = TRUE;
	m_pCustomerDlg->m_strKeyword = strKeyword;
	m_pCustomerDlg->m_nSearchType = nSearchType; 
	m_pCustomerDlg->m_nBranchCode = m_pRcpDlg ? m_pRcpDlg->m_pBi->nBranchCode : pBi->nBranchCode;
	m_pCustomerDlg->m_strBranchName = m_pRcpDlg ? m_pRcpDlg->m_pBi->strBranchName : pBi->strBranchName;
	m_pCustomerDlg->m_nCompanyCode = m_pRcpDlg ? m_pRcpDlg->m_pBi->nCompanyCode : pBi->nCompanyCode;
	m_pCustomerDlg->m_nDOrderTable = m_pRcpDlg ? m_pRcpDlg->m_pBi->nDOrderTable : pBi->nDOrderTable;
	m_pCustomerDlg->m_nCustomerTable = m_pRcpDlg ? m_pRcpDlg->m_pBi->nCustomerTable : pBi->nCustomerTable;
	m_pCustomerDlg->m_nPayTable = m_pRcpDlg ? m_pRcpDlg->m_pBi->nPayTable : pBi->nPayTable;
	m_pCustomerDlg->m_bGroup = m_pRcpDlg ? m_pRcpDlg->m_pBi->bGroup : pBi->bGroup;
	m_pCustomerDlg->m_nSearchType = nSearchType;
	m_pCustomerDlg->m_nRefreshTelID = GetTelID();
	m_pCustomerDlg->m_bCIDSearch = bCIDSearch;

	if(m_pRcpDlg)
	{
		if(m_bTempCNo || m_pRcpDlg->m_bInternet)
		{
			m_pCustomerDlg->m_nTempCNo = m_nCNo;
			m_pCustomerDlg->m_strTempCompany = GetCompany();
			//m_pCustomerDlg->m_strTempDong = m_strTempDong;
			m_pCustomerDlg->m_strTempTel	= GetPhone();
			m_pCustomerDlg->m_strTempMobile	= GetMP();
			m_pCustomerDlg->m_strTempDepart = GetDepart();
			m_pCustomerDlg->m_strTempName = GetManager();
			m_pCustomerDlg->m_strTempLocation = GetDetail();
		}
		else
		{
			m_pCustomerDlg->m_nTempCNo = 0;
		}
	}
	

	if(nSearchType == ST_COMPANY)
		m_pCustomerDlg->m_strSearchName = strData;
	else if(nSearchType == ST_PHONE)
		m_pCustomerDlg->m_strSearchPhone = strData;
	else if(nSearchType == ST_CNO)
		m_pCustomerDlg->m_nCNo = GetCNo();

	m_pCustomerDlg->m_bNoDelay = TRUE;
	m_pCustomerDlg->InitDialog();
	m_pCustomerDlg->CenterWindow(AfxGetMainWnd());
	m_pCustomerDlg->ShowWindow(!m_pCustomerDlg->m_bCloseDlg);
	return TRUE;
}

void CRcpPlaceInfo::SetCNo(long nCNo, BOOL bTempCNo, long nID, CString strUserID, long nUseCount, long nCancelCount, long nMileageBalance) 
{   
	m_nCNo = nCNo; 
	m_bTempCNo = bTempCNo;
	m_strUserID = strUserID;
	m_nCustomerID = nID;
	m_nUseCount = nUseCount;
	m_nCancelCount = nCancelCount;
	m_nMileageBalance = nMileageBalance;


	if(m_pedtCNo)
		m_pedtCNo->SetWindowText(GetCustomerTypeString(nCNo, m_nCustomerID, strUserID));
}

void CRcpPlaceInfo::RefreshTelCombo(CString strPhone, CString strMobile)
{
/*
	if((m_pRcpDlg->m_nLineID > 0) && (IsNumeric(GetNoneDashNumber(m_pRcpDlg->m_strCID)) == TRUE))//실제전화오면 
	{
		if(GetNoneDashNumber(m_pRcpDlg->m_strCID) == GetNoneDashNumber(strPhone))
			m_pedtMP->SetWindowText(GetDashPhoneNumber(strMobile));
		else
			m_pedtMP->SetWindowText(GetDashPhoneNumber(m_pRcpDlg->m_strCID));
	}
	else
	{
		m_pedtMP->SetWindowText(GetDashPhoneNumber(strMobile));
	}
*/
}


BOOL CRcpPlaceInfo::Copy(CRcpPlaceInfo *p)
{
//	if(p->GetCNo() == 0)
//		return FALSE;

	if(p == this)
		return FALSE;

	if(IsOrder())
		if(!SearchCustomerCNo(p->GetCNo()))
			return FALSE;

	SetSearch(p->GetSearch());
	SetPOI(p->GetPOI());
	SetDetailPos(p->GetDetailPosX(), p->GetDetailPosY());
	SetDepart(p->GetDepart());
	SetManager(p->GetManager());
	SetPhone(p->GetPhone());
	SetDetail(p->GetDetail());
	SetCNo(p->GetCNo(), p->IsTempCNo(), p->GetCustomerID(), p->GetUserID());
	SetGNo(p->GetGNo());
	SetMemo(p->GetMemo());
	SetMP(p->GetMP());
	SetDisplayDong(p->GetDisplayDong());
	SetCompany(p->GetCompany()); //SetPhone, SetMP 보다 아래에 있어야함
	SetAddress(p->GetAddressMarkup(), p->GetAddress());
	SetCredit(p->IsCredit());
	SetTelID(p->GetTelID());
	CheckDelType();

	return TRUE;
}

void CRcpPlaceInfo::Exchange(CRcpPlaceInfo *p)
{
	CRcpPlaceInfo temp(m_pRcpDlg, TEMP_PLACE);
	temp.Copy(this);
	Copy(p);
	p->Copy(&temp);
}

void CRcpPlaceInfo::SetDisplayDong(CString strDisplayDong) 
{ 
	if(m_pPOI)
	{
		CPOIUnit *pDong = m_pPOI->GetDongPOI(FALSE);
		CString strDong, strShortDong, strSido, strGugun;

		if(pDong->IsTopTheDoPOI())
		{
			strSido = pDong->GetGugun1Only(TRUE);
			strGugun = pDong->GetGugun2Only(TRUE);
			strDong = pDong->IsLiPOI() ? pDong->GetLi() : pDong->GetDong();
		}
		else
		{
			strSido = pDong->GetSido();
			strGugun = pDong->GetGugun1Only(TRUE);
			strDong = pDong->IsLiPOI() ? pDong->GetLi() : pDong->GetDong();
			strShortDong = pDong->GetLi() ? pDong->GetLi(TRUE) : pDong->GetDong(TRUE);
		}

		if(strDisplayDong == strDong || 
			strDisplayDong == strShortDong ||
			strDisplayDong == "")
		{
			long nDongID = pDong->GetMainDongID();
			if(nDongID == 3503 ||
			   nDongID == 3831 || 
			   nDongID == 3900 ||
			   nDongID == 4056 ||
			   nDongID == 4162 ||
			   nDongID == 8082 ||
			   nDongID == 8085 ||
			   nDongID == 8086)
			{
				//nDongID == 3500 || 
				//nDongID == 3503 ||

				strDisplayDong = strGugun + strDong;
			}
			else if(pDong->IsLiPOI() || (m_ci.m_strCity != strSido && pDong->GetClass() != PN_SIDO))
				strDisplayDong = strSido + strDong;
			else
				strDisplayDong = strDong;
		}
	}

	CEdit *pedt = GetDisplayDongEdit();
	if(pedt->GetSafeHwnd())
		pedt->SetWindowText(strDisplayDong);
}

void CRcpPlaceInfo::SetCompany(CString strCompany) 
{ 
	/*
	CString strCompany2 = strCompany;
	strCompany2.Remove('-');

	CString strPhone2 = GetPhone();
	strPhone2.Remove('-');

	CString strMP2 = GetMP();
	strMP2.Remove('-');

	if(IsOrder() && (strPhone2.GetLength() > 0 && strCompany2 == strPhone2 ||
		strPhone2.GetLength() > 0 && strCompany2 == strMP2 ||
			strCompany == ""))
		GetCompanyEdit()->SetWindowText("일반");
	else
		GetCompanyEdit()->SetWindowText(strCompany);
*/
	GetCompanyEdit()->SetWindowText(strCompany);
}

BOOL CRcpPlaceInfo::IsPosValid()
{
	if(m_pPOI && m_pPOI->GetPosX() && m_pPOI->GetPosY())
		return TRUE;
	else 
		return FALSE;
}

long CRcpPlaceInfo::GetPosX()
{
	if(m_pPOI)
		return m_nDetailPosX > 0 ? m_nDetailPosX : m_pPOI->GetPosX();
	else 
		return 0;
}

long CRcpPlaceInfo::GetPosY()
{
	if(m_pPOI)
		return m_nDetailPosY > 0 ? m_nDetailPosY : m_pPOI->GetPosY();
	else 
		return 0;
}

void CRcpPlaceInfo::ShowMap(BOOL bFromCustomerDlg)
{
	if(IsPosValid()) 
	{ 
		CRcpDlgMapDlg *pRcpDlgMapDlg = LU->GetRcpDlgMap(m_pRcpDlg);
		pRcpDlgMapDlg->m_bFromCustomerDlg = bFromCustomerDlg;
		CLogiMapNew *pLogiMap = pRcpDlgMapDlg->GetMap();
		pLogiMap->ClearAllLayer();
		pLogiMap->AddPointPOI(TRUE, CString("[" + m_strPlaceName + "]") + GetAddress(), GetPosX(), GetPosY(), GetAddress());
		pRcpDlgMapDlg->ShowWindow(SW_SHOW);
	}
	else
	{
		m_pRcpDlg->MessageBox(m_strPlaceName + "의 위치정보가 없습니다.", "확인", MB_ICONINFORMATION);
	}
}

void CRcpPlaceInfo::SetOtherPlaceInfo(CRcpPlaceInfo *pOrder, CRcpPlaceInfo *pStart, CRcpPlaceInfo *pDest)
{
	m_pOrderPlace = pOrder;
	m_pStartPlace = pStart;
	m_pDestPlace = pDest;
}

BOOL CRcpPlaceInfo::CheckDelType(BOOL bAutoChange)
{
	int nSel = 2;

	if(bAutoChange && m_bManualDelType)
		return m_pcmbDelType->GetCurSel();
	
	if(!bAutoChange)
		m_bManualDelType = TRUE;

	if(m_nPlaceType != TEMP_PLACE && m_nPlaceType != PLACE_TYPE_CUSTOMER)
	{
		if(!m_pOrderPlace->IsNewCus() && (m_pStartPlace->GetPOI() || m_pDestPlace->GetPOI()))
		{
			if(m_pOrderPlace->GetCNo() == m_pStartPlace->GetCNo())
				nSel = 0;
			else if(m_pOrderPlace->GetCNo() == m_pDestPlace->GetCNo())
				nSel = 1;
			else 
				nSel = 2;
		}
		else if(m_pOrderPlace->IsNewCus())
		{
			if(m_bManualAddCustomer)
			{
				/**
				16.11.02 charko - 신규 일때 기본적으로 외부로 두고,
				디테일 좌표가 같을 경우 보내기, 찾아오기로 변경되게 변경.
				**/

				nSel = 2;
				
				if(bAutoChange)
				{				
					if(m_pOrderPlace->GetDetailPosX() == m_pStartPlace->GetDetailPosX() &&
						m_pOrderPlace->GetDetailPosY() == m_pStartPlace->GetDetailPosY() &&
						m_pStartPlace->GetDetailPosX() != 0)
					{
						nSel = 0;

						if(!m_pOrderPlace->GetPhone().IsEmpty() && m_pDestPlace->GetPhone() == m_pOrderPlace->GetPhone())
							m_pDestPlace->SetPhone("");
					}
					else if(m_pOrderPlace->GetDetailPosX() == m_pDestPlace->GetDetailPosX() &&
						m_pOrderPlace->GetDetailPosY() == m_pDestPlace->GetDetailPosY() &&
						m_pDestPlace->GetDetailPosX() != 0)
					{
						nSel = 1;

						if(!m_pOrderPlace->GetPhone().IsEmpty() && m_pStartPlace->GetPhone() == m_pOrderPlace->GetPhone())
							m_pStartPlace->SetPhone("");
					}
				}
				else if(!bAutoChange)
					nSel = m_pcmbDelType->GetCurSel();
				
				if(nSel == 2 && m_pcmbDelType->GetCurSel() == nSel)
				{
					if(m_pStartPlace->IsNewCus())
						m_pStartPlace->SetPhone("");
					if(m_pDestPlace->IsNewCus())
						m_pDestPlace->SetPhone("");
				}
			}
			else
			{
				int nCur = m_pcmbDelType->GetCurSel();

				if(!bAutoChange && nCur == 0 || bAutoChange && m_pStartPlace->IsNewCus() && m_pStartPlace->GetPOI())
					nSel = 0;
				else if(!bAutoChange && nCur == 1 || bAutoChange && m_pDestPlace->IsNewCus() && m_pDestPlace->GetPOI())
					nSel = 1;
			}

			if(nSel == 0)
			{
				m_pStartPlace->SetPhone(m_pOrderPlace->GetPhone().GetLength() == 0 ? m_pStartPlace->GetPhone() : m_pOrderPlace->GetPhone());

				m_pOrderPlace->SetDisplayDong(m_pStartPlace->GetDisplayDong());
				m_pOrderPlace->SetPOI(m_pStartPlace->GetPOI());
				m_pOrderPlace->SetDetailPos(m_pStartPlace->GetDetailPosX(), m_pStartPlace->GetDetailPosY());
				m_pOrderPlace->SetData(m_pStartPlace->GetDetailPosX(), m_pStartPlace->GetDetailPosY());

				if(!m_pOrderPlace->GetPhone().IsEmpty() && m_pDestPlace->GetPhone() == m_pOrderPlace->GetPhone())
					m_pDestPlace->SetPhone("");
			}
			else if(nSel == 1)
			{
				m_pDestPlace->SetPhone(m_pOrderPlace->GetPhone().GetLength() == 0 ? m_pStartPlace->GetPhone() : m_pOrderPlace->GetPhone());

				m_pOrderPlace->SetDisplayDong(m_pDestPlace->GetDisplayDong());
				m_pOrderPlace->SetPOI(m_pDestPlace->GetPOI());
				m_pOrderPlace->SetDetailPos(m_pDestPlace->GetDetailPosX(), m_pDestPlace->GetDetailPosY());
				m_pOrderPlace->SetData(m_pDestPlace->GetDetailPosX(), m_pDestPlace->GetDetailPosY());

				if(!m_pOrderPlace->GetPhone().IsEmpty() && m_pStartPlace->GetPhone() == m_pOrderPlace->GetPhone())
					m_pStartPlace->SetPhone("");
			}
		}

		if(bAutoChange && m_pcmbDelType->GetCurSel() != nSel && *m_pbSkipChangeDelType == FALSE)
		{
			*m_pbSkipChangeDelType = TRUE;
			m_pcmbDelType->SetCurSel(nSel);
			*m_pbSkipChangeDelType = FALSE;
		}
	}

	return nSel;
}

void CRcpPlaceInfo::RefreshCompanyColor()
{
	if(m_nPlaceType <= PLACE_TYPE_DEST)
	{
		//temp_place는 flatedit 상속이 아니라서, delete시에 crash 발생

		CFlatEdit2 *pEdit = ((CFlatEdit2*)m_pedtCompany);

		if(IsCredit())
			pEdit->SetUserTextColor(RGB(255, 0, 0));
		else
			pEdit->SetUserTextColor(RGB(0, 0, 0));

		if(GetGNo() > 0)
			pEdit->SetUserBkColor(RGB(220, 220, 255));
		else
			pEdit->SetUserBkColor(RGB(255, 255, 255));
	}
}




#define GET_DB_STRING(x)	\
	if(m_pcmbDelType->GetCurSel() == DEL_SEND)\
	{\
		if(m_nPlaceType == PLACE_ORDER || \
			m_nPlaceType == PLACE_START)\
		{\
			return m_pOrderPlace->x().GetLength() > 0 ? m_pOrderPlace->x() : m_pStartPlace->x();\
		}\
	}\
	else if(m_pcmbDelType->GetCurSel() == DEL_RECV)\
	{\
		if(m_nPlaceType == PLACE_ORDER ||\
			m_nPlaceType == PLACE_DEST)\
		{\
			return m_pOrderPlace->x().GetLength() > 0 ? m_pOrderPlace->x() : m_pDestPlace->x();\
		}\
	}\
	return x();


#define GET_DB_POI(x)	\
	if(m_pcmbDelType->GetCurSel() == DEL_SEND)\
	{\
		if(m_nPlaceType == PLACE_ORDER || \
			m_nPlaceType == PLACE_START)\
		{\
			return m_pStartPlace->x();\
		}\
	}\
	else if(m_pcmbDelType->GetCurSel() == DEL_RECV)\
	{\
		if(m_nPlaceType == PLACE_ORDER ||\
			m_nPlaceType == PLACE_DEST)\
		{\
			return m_pDestPlace->x();\
		}\
	}\
	return x();



CString CRcpPlaceInfo::GetDBCompany() 
{ 
	GET_DB_STRING(GetCompany)
}

CString CRcpPlaceInfo::GetDBDepart() 
{
	GET_DB_STRING(GetDepart)
}

CString CRcpPlaceInfo::GetDBManager() 
{ 
	GET_DB_STRING(GetManager)
}

CString CRcpPlaceInfo::GetDBDetail() 
{ 
	GET_DB_STRING(GetDetail)
}

CString CRcpPlaceInfo::GetDBMemo() 
{ 
	GET_DB_STRING(GetMemo)
}

CString CRcpPlaceInfo::GetDBPhone() 
{ 
	GET_DB_STRING(GetPhone)
}

CString CRcpPlaceInfo::GetDBMP() 
{ 
	GET_DB_STRING(GetMP)
}

long CRcpPlaceInfo::GetDBPosX() 
{ 
	GET_DB_POI(GetPosX)
}

long CRcpPlaceInfo::GetDBPosY() 
{ 
	GET_DB_POI(GetPosY)
}

CString CRcpPlaceInfo::GetDBDisplayDong()
{
	GET_DB_POI(GetDisplayDong)
}

CString CRcpPlaceInfo::GetDBAddress() 
{ 
	GET_DB_POI(GetAddress)
}

CPOIUnit* CRcpPlaceInfo::GetDBPOI() 
{ 
	GET_DB_POI(GetPOI)
}

BOOL CRcpPlaceInfo::NeedToAddCustomer()
{
	//의뢰지와 동일하지 않은, 신규추가 상태인 경우에
	//동이외에 다른 정보가 있으면 고객으로 추가를 한다. (주소도 추가함)

	if(IsNewCus())
	{
		if(m_pcmbDelType->GetCurSel() == DEL_SEND && m_nPlaceType == PLACE_DEST ||
			m_pcmbDelType->GetCurSel() == DEL_RECV && m_nPlaceType == PLACE_START || 
			m_pcmbDelType->GetCurSel() > DEL_RECV)
		{
			if(GetPOI())
			{
				if(GetPhone().GetLength() > 7 ||
					GetMP().GetLength() > 7)
				{
					return TRUE;
				}
			}
		}
	}

	//전화번호 정보만으로 원하지 않는 고객이 자꾸 생심 choi 20110721
	//프로시져안에서 한번체크함 전화번호 존재할시는 등록안함 없을시만 등록함 choi 20110811 
	
	return FALSE;
}

CRcpPlaceInfo* CRcpPlaceInfo::GetJoinPlace()
{
	if(m_pcmbDelType->GetCurSel() == DEL_SEND)
	{
		if(m_nPlaceType == PLACE_ORDER)
			return m_pStartPlace;
		else if(m_nPlaceType == PLACE_START)
			return m_pOrderPlace;
	}
	else if(m_pcmbDelType->GetCurSel() == DEL_RECV)
	{
		if(m_nPlaceType == PLACE_ORDER)
			return m_pDestPlace;
		else if(m_nPlaceType == PLACE_DEST)
			return m_pOrderPlace;
	}

	return NULL;
}

void CRcpPlaceInfo::OnContextMenuCall(BOOL bPhone2)
{
	CMenu *pMainMenu = new CMenu;
	CMenu *pCallMenu = NULL, *pRemoveMenu = NULL, *pSetNumber1 = NULL, *pSetNumber2 = NULL;

	CPoint pt; 
	GetCursorPos(&pt);

	CString strCID = m_pRcpDlg->m_strCID;
	m_arrMenuPhone.RemoveAll();
	m_bMenuSelectPhone2 = bPhone2;

	CString strCurPhone = GetPhone(bPhone2);

		pMainMenu->DestroyMenu();

	pMainMenu->CreatePopupMenu();

	if(strCurPhone.GetLength() > 0)
	{ 
		pMainMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_PHONE_CUR_CALL, strCurPhone + " 로 전화걸기");
		pMainMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_PHONE_SEND_SMS, strCurPhone + " 로 SMS전송");
		pMainMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_PHONE_ALLOCATE_SEND_SMS, strCurPhone + " 로 배차SMS전송");
		if(GetNoneDashNumber(strCID) != GetNoneDashNumber(strCurPhone))
		{
			pMainMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_PHONE_CUR_CALL, GetDashPhoneNumber(strCID) + " 발신번호로 전화걸기");
			if(IsNewCus() && strCID.GetLength() > 0)
				pMainMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_PHONE_CUR_CALL, GetDashPhoneNumber(strCID) + "발신번호 선택하기");
		}

		if(!IsNewCus())
			pMainMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_PHONE_CUR_REMOVE, strCurPhone + " 삭제하기");

		strCurPhone = GetNoneDashNumber(strCurPhone);
	}

	if(!IsNewCus())
	{
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "select_customertel2");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_pRcpDlg->m_pBi->nCompanyCode);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCNo);
		if(pRs.Execute(&pCmd))
		{
			CString strPhone;
			long nType;
			UINT nID = ID_MENU_PHONE_SELECT;
			BOOL bCheckCIDNumber = FALSE;

			for(int i = 0; i < pRs.GetRecordCount(); i++)
			{
				if(i == 0)
					pMainMenu->AppendMenu(MF_BYCOMMAND | MF_SEPARATOR, 0, "");

				pRs.GetFieldValue("sTel", strPhone);
				pRs.GetFieldValue("nType", nType);

				CString strType;
				if(nType == 1)
					strType = " (직통전화)";
				else if(nType == 2)
					strType = " (휴대전화)";
				
				MENU_PHONE phone;
				phone.strPhone = GetNoneDashNumber(strPhone);
				phone.strDisplay = GetDashPhoneNumber(strPhone) + " " + strType;

				if(phone.strPhone == GetNoneDashNumber(strCID) && strCID.GetLength() > 0)
				{
					phone.strDisplay += nType > 0 ? "(발신번호)" : " (발신번호)";
					bCheckCIDNumber = TRUE;
				}

				m_arrMenuPhone.Add(phone);
				pMainMenu->AppendMenu(MF_BYCOMMAND, nID, phone.strDisplay + " 선택");
				nID++;

				pRs.MoveNext();
			}

			if(!bCheckCIDNumber && strCID.GetLength() > 0)
			{
				MENU_PHONE phone;
				phone.strPhone = GetNoneDashNumber(strCID);
				phone.strDisplay = GetDashPhoneNumber(strCID) + " (발신번호)";
				m_arrMenuPhone.Add(phone);
				pMainMenu->AppendMenu(MF_BYCOMMAND, nID, phone.strDisplay + " 선택");
				nID++;
			}

			if(m_arrMenuPhone.GetCount() > 0)
			{
				pMainMenu->AppendMenu(MF_BYCOMMAND | MF_SEPARATOR, 0, "");

				int nType = MF_BYPOSITION | MF_POPUP;

				pCallMenu = new CMenu;
				pCallMenu->CreatePopupMenu();
				pMainMenu->InsertMenu(pMainMenu->GetMenuItemCount(), nType, (UINT)pCallMenu->m_hMenu, "전화걸기");

				pRemoveMenu = new CMenu;
				pRemoveMenu->CreatePopupMenu();
				pMainMenu->InsertMenu(pMainMenu->GetMenuItemCount(), nType, (UINT)pRemoveMenu->m_hMenu, "전화번호 목록에서 삭제");

				pSetNumber1 = new CMenu;
				pSetNumber1->CreatePopupMenu();
				pMainMenu->InsertMenu(pMainMenu->GetMenuItemCount(), nType, (UINT)pSetNumber1->m_hMenu, "고객DB 전화1로 지정함");

				pSetNumber2 = new CMenu;
				pSetNumber2->CreatePopupMenu();
				pMainMenu->InsertMenu(pMainMenu->GetMenuItemCount(), nType, (UINT)pSetNumber2->m_hMenu, "고객DB 전화2로 지정함");

				for(int i = 0; i < m_arrMenuPhone.GetCount(); i++)
				{
					pCallMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_PHONE_CALL + i, m_arrMenuPhone[i].strDisplay);
					pRemoveMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_PHONE_REMOVE + i, m_arrMenuPhone[i].strDisplay);
					pSetNumber1->AppendMenu(MF_BYCOMMAND, ID_MENU_PHONE_SET_NUMBER1 + i, m_arrMenuPhone[i].strDisplay);
					pSetNumber2->AppendMenu(MF_BYCOMMAND, ID_MENU_PHONE_SET_NUMBER2 + i, m_arrMenuPhone[i].strDisplay);
				}
			}
		}
	}

	if(pMainMenu->GetMenuItemCount() > 0)
		pMainMenu->AppendMenu(MF_BYCOMMAND | MF_SEPARATOR, 0, "");
	pMainMenu->AppendMenu(MF_BYCOMMAND, ID_MENU_PHONE_ETC + 1, "접수창 설정");
	pMainMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, m_pRcpDlg);

	DELETE_OBJECT(pMainMenu);
	DELETE_OBJECT(pCallMenu);
	DELETE_OBJECT(pRemoveMenu);
	DELETE_OBJECT(pSetNumber1);
	DELETE_OBJECT(pSetNumber2);
}

void CRcpPlaceInfo::OnSelectMenuCall(UINT nID)
{
	CRcpView *pView = m_pRcpDlg->m_pRcpView;
	long nCompany = m_pRcpDlg->m_pBi->nCompanyCode;
	BOOL bPhone2 = m_bMenuSelectPhone2;

	if(nID == ID_MENU_PHONE_CUR_CALL) 
		pView->MakeCall(nCompany, GetPhone(bPhone2), CALL_TO_CUSTOMER);
	else if(nID == ID_MENU_PHONE_CUR_REMOVE)
		DeletePhone(GetNoneDashNumber(GetPhone(bPhone2)));
	else if(nID == ID_MENU_PHONE_SEND_SMS)
		SendSms(nCompany, GetNoneDashNumber(GetPhone(bPhone2)));
	else if(nID == ID_MENU_PHONE_ALLOCATE_SEND_SMS)
		SendSms(nCompany, GetNoneDashNumber(GetPhone(bPhone2)), true);
	else if(nID >= ID_MENU_PHONE_SELECT && nID <= ID_MENU_PHONE_SELECT + 100)
		SetPhone(GetDashPhoneNumber(m_arrMenuPhone[nID - ID_MENU_PHONE_SELECT].strPhone), bPhone2);
	else if(nID >= ID_MENU_PHONE_CALL && nID <= ID_MENU_PHONE_CALL + 100)
		pView->MakeCall(nCompany, m_arrMenuPhone[nID - ID_MENU_PHONE_CALL].strPhone, CALL_TO_CUSTOMER);
	else if(nID >= ID_MENU_PHONE_REMOVE && nID <= ID_MENU_PHONE_REMOVE + 100)
		DeletePhone(m_arrMenuPhone[nID - ID_MENU_PHONE_REMOVE].strPhone);
	else if(nID >= ID_MENU_PHONE_SET_NUMBER1 && nID <= ID_MENU_PHONE_SET_NUMBER1 + 100)
		UpdatePhone(m_arrMenuPhone[nID - ID_MENU_PHONE_SET_NUMBER1].strPhone);
	else if(nID >= ID_MENU_PHONE_SET_NUMBER2 && nID <= ID_MENU_PHONE_SET_NUMBER2 + 100)
		UpdatePhone(m_arrMenuPhone[nID - ID_MENU_PHONE_SET_NUMBER2].strPhone, TRUE);
	else if(nID == ID_MENU_PHONE_ETC + 1)
	{
		CRcpDlgSetupDlg dlg;
		if(IDOK == dlg.DoModal())
		{
			SetStartDontAutoCopy(CRcpDlgSetupDlg::m_info.nStartDontAutoCopy);

			BOOL bMenualAddCustomer = CRcpDlgSetupDlg::m_info.nManualAddCustomer;
			SetMenualAddCustomer(bMenualAddCustomer);

			//아래 세개의 클레스는 데이터를 서로 공유			
			if(m_pOrderPlace)
				m_pOrderPlace->m_bManualAddCustomer = bMenualAddCustomer;
			if(m_pStartPlace)
				m_pStartPlace->m_bManualAddCustomer = bMenualAddCustomer;
			if(m_pDestPlace)
				m_pDestPlace->m_bManualAddCustomer = bMenualAddCustomer;
		}
	}
}

void CRcpPlaceInfo::SendSms(long nCompany, CString strPhone, bool bAllocate)
{
	if(strPhone.Left(2) != "01")
	{
		MessageBox(m_pRcpDlg->GetSafeHwnd(), "휴대폰 번호만 전송 하실 수 있습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	LU->GetRcpView()->SendSms(nCompany, strPhone, bAllocate);
}

void CRcpPlaceInfo::DeletePhone(CString strPhone)
{
	if(IDYES == m_pRcpDlg->MessageBox(strPhone + " 번을 DB에서 삭제 하시겠습니까?", "확인", MB_ICONQUESTION | MB_YESNO))
	{
		CMkCommand pCmd(m_pMkDb, "delete_customertel2");
		pCmd.AddParameter(m_pRcpDlg->m_pBi->nCompanyCode);
		pCmd.AddParameter(GetCNo());
		pCmd.AddParameter(strPhone);
		if(pCmd.Execute())
		{
			int nReplacePhoneType = REPLACE_PHONE_QUERY;
			DeletePhoneThisPlace(this, strPhone, nReplacePhoneType);
			DeletePhoneThisPlace(GetJoinPlace(), strPhone, nReplacePhoneType);

			m_pRcpDlg->MessageBox("삭제되었습니다.", "확인", MB_ICONINFORMATION);
		}
	}
}

void CRcpPlaceInfo::DeletePhoneThisPlace(CRcpPlaceInfo *p, CString strPhone, int &nReplacePhoneType)
{
	if(p)
	{
		CString strPhone1 = GetNoneDashNumber(p->GetPhone());
		CString strPhone2 = GetNoneDashNumber(p->GetPhone(TRUE));

		if(strPhone == strPhone1)
		{
			p->SetPhone("");
			if(!p->GetPhone(TRUE).IsEmpty())
			{
				if(nReplacePhoneType == REPLACE_PHONE_QUERY)
				{
					int nRet = m_pRcpDlg->MessageBox("전화1 삭제 후에, 전화2를 전화1로 이동하시겠습니까?", 
									"확인", MB_ICONQUESTION | MB_YESNO);

					nReplacePhoneType = nRet == IDYES ? REPLACE_PHONE_MOVE : REPLACE_PHONE_DONT_MOVE;
				}			

				if(nReplacePhoneType == REPLACE_PHONE_MOVE)
				{
					p->SetPhone(GetDashPhoneNumber(p->GetPhone(TRUE)));
					p->SetPhone("", TRUE);
				}
			}
		}

		if(strPhone == strPhone2)
			p->SetPhone("", TRUE);
	}
}


void CRcpPlaceInfo::UpdatePhone(CString strPhone, BOOL bPhone2)
{
	CString strMsg;
	strMsg.Format("%s 번을 고객DB에서 대표전화번호%s로 설정하시겠습니까?", strPhone, bPhone2 ? "2" : "1");

	if(IDYES == m_pRcpDlg->MessageBox(strMsg, "확인", MB_ICONQUESTION | MB_YESNO))
	{
		CMkCommand pCmd(m_pMkDb, "update_customer_phone");
		pCmd.AddParameter(m_pRcpDlg->m_pBi->nCompanyCode);
		pCmd.AddParameter(GetCNo());
		pCmd.AddParameter(!bPhone2 ? strPhone : "");
		pCmd.AddParameter(bPhone2 ? strPhone : "");
		if(pCmd.Execute())
		{
			SetPhone(GetDashPhoneNumber(strPhone), bPhone2);
			m_pRcpDlg->MessageBox("설정되었습니다.", "확인", MB_ICONINFORMATION);
		}
	}
}

void CRcpPlaceInfo::UpdateJoinedControl(UINT nID)
{
	CRcpPlaceInfo *pPlace = GetJoinPlace();
/*
	if(pPlace && pPlace->IsNewCus() && IsNewCus())
	{
		if(m_pedtCNo->GetDlgCtrlID() == nID)
			UpdateJoinedEditControl(m_pedtCNo, pPlace->GetCNoEdit());
		else if(m_pedtCompany->GetDlgCtrlID() == nID)
			UpdateJoinedEditControl(m_pedtCompany, pPlace->GetCompanyEdit());
		else if(m_pedtDisplayDong->GetDlgCtrlID() == nID)
			UpdateJoinedEditControl(m_pedtDisplayDong, pPlace->GetDisplayDongEdit());
		else if(m_pedtDepart->GetDlgCtrlID() == nID)
			UpdateJoinedEditControl(m_pedtDepart, pPlace->GetDepartEdit());
		else if(m_pedtManager->GetDlgCtrlID() == nID)
			UpdateJoinedEditControl(m_pedtManager, pPlace->GetManagerEdit());
		else if(m_pedtDetail->GetDlgCtrlID() == nID)
			UpdateJoinedEditControl(m_pedtDetail, pPlace->GetDetailEdit());
		else if(m_pedtPhone->GetDlgCtrlID() == nID || m_pedtMP->GetDlgCtrlID() == nID)
		{
			*m_pbSkipChangeDelType = TRUE;
			m_pcmbDelType->SetCurSel(DEL_UNKNOWN);
			*m_pbSkipChangeDelType = FALSE;
		}

	}
*/
}

void CRcpPlaceInfo::UpdateJoinedEditControl(CEdit *pedtSrc, CEdit *pedtDst)
{
	CString strTemp;
	pedtSrc->GetWindowText(strTemp);
	pedtDst->SetWindowText(strTemp);
}

void CRcpPlaceInfo::SaveAddressToOrder(CRcpPlaceInfo *pPlace)
{
	if(pPlace->IsNewCus())
	{
		m_pRcpDlg->MessageBox("신규고객입니다.\n수정불가합니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	if(!GetPOI())
	{
		m_pRcpDlg->MessageBox("위치정보가 없습니다.\n수정불가합니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	CMkCommand pCmd(m_pMkDb, "update_customer_address_info");
	pCmd.AddParameter(pPlace->GetCNo());
	pCmd.AddParameter(GetDisplayDong());
	pCmd.AddParameter(GetDetail());
	pCmd.AddParameter(GetAddress());
	pCmd.AddParameter(GetPOI()->GetDongID());
	pCmd.AddParameter(GetPosX());
	pCmd.AddParameter(GetPosY());

	if(pCmd.Execute())
		m_pRcpDlg->MessageBox("추가되었습니다.", "확인", MB_ICONINFORMATION);
}

void CRcpPlaceInfo::InitDiscountInfo()
{
	m_pRcpDlg->SetDiscountInfoInit();
}

BOOL CRcpPlaceInfo::IsEmpty()
{
	if(GetCNo() == 0 && 
		GetCompany().IsEmpty() &&
		GetDepart().IsEmpty() &&
		GetManager().IsEmpty() &&
		GetAddress().IsEmpty())
	{
		return TRUE;
	}

	return FALSE;
}

void CRcpPlaceInfo::SetAddress(CString strMarkup, CString strNormal) 
{ 
	if(GetAddressStatic())
		GetAddressStatic()->SetMarkupText(strMarkup, strNormal); 

	if(m_pstcAddressNormal)
	{
		strNormal.Replace("  ", " ");
		m_pstcAddressNormal->SetWindowText(strNormal);
	}
}