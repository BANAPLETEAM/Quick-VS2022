#pragma once


#define ID_MENU_PHONE_CUR_CALL		0xE000
#define ID_MENU_PHONE_CUR_REMOVE	0xE001
#define ID_MENU_PHONE_SELECT		0xE100
#define ID_MENU_PHONE_CALL			0xE200
#define ID_MENU_PHONE_REMOVE		0xE300
#define ID_MENU_PHONE_ETC			0xE400	
#define ID_MENU_PHONE_SET_NUMBER1	0xE500	
#define ID_MENU_PHONE_SET_NUMBER2	0xE600
#define ID_MENU_PHONE_SEND_SMS		0xE700
#define ID_MENU_PHONE_ALLOCATE_SEND_SMS	0xE800

typedef struct {
	CString strPhone;
	CString strDisplay;
} MENU_PHONE;

typedef CArray<MENU_PHONE, MENU_PHONE> MENU_PHONE_ARRAY;


class CRcpDlg;
class CPOIUnit;
class CCustomerDlg;

class CRcpPlaceInfo
{
public:
	CRcpPlaceInfo(CWnd *pwndParent, long nPlaceType);
	~CRcpPlaceInfo(void);

	void SetControl(CEdit *pedtSearch, CMarkupStatic *pstcAddress, CStatic *pstcAddressNormal, CEdit *pedtDetail,
							   CEdit *pedtCompany, CEdit *pedtPhone, CEdit *pedtMP, CEdit *pedtDisplayDong);
	void SetControl(CEdit *pedtSearch, CEdit *pedtCNo, CEdit *pedtCompany, CEdit *pedtDepart, 
				CEdit *pedtManager, CMarkupStatic *pedtAddress, CStatic *pstcAddressNormal, CEdit *pedtDetail, 
				CEdit *pedtMemo, CEdit *pedtPhone, CEdit *pedtMP, 
				CEdit *pedtDisplayDong, CComboBox *pcmbDelType, CButton *pbtnShowPhoneType, BOOL *pbSkipChangeDelType);

	BOOL MakeSearchQuery(CString strSource, CString &strKeyword, UINT *pnType);
	BOOL SearchCustomerCNo(long nCNo = 0, BOOL bQueryWithoutCustomerDlg = TRUE, BOOL bAloneItemAutoClosed = TRUE, 
							long nTelID = 0, BOOL bCopyStart = TRUE);
	BOOL SearchCustomer(CString strData, UINT nSearchType = ST_AUTO_DETECT, BOOL bCIDSearch = FALSE);
	BOOL SearchCustomer(long nData, UINT nSearchType = ST_AUTO_DETECT);

public:
	CEdit* GetSearchEdit();
	CEdit* GetCNoEdit();
	CEdit* GetCompanyEdit();
	CEdit* GetDepartEdit();
	CEdit* GetManagerEdit();
	CMarkupStatic* GetAddressStatic();
	CEdit* GetDetailEdit();
	CEdit* GetMemoEdit();
	CEdit* GetMPEdit();
	CEdit* GetPhoneEdit(BOOL bPhone2 = FALSE);
	CEdit* GetDisplayDongEdit();
	CButton* GetShowPhoneTypeCheck();

	CString GetSearch();
	long GetCNo();
	long GetGNo();
	CString GetCompany();
	CString GetDepart();
	CString GetManager();
	CString GetAddress();
	CString GetAddressMarkup();
	CString GetDetail();
	CString GetMemo();
	CString GetPhone(BOOL bPhone2 = FALSE);
	CString GetMP();
	long GetShowPhoneType();
	CPOIUnit *GetPOI();
	CPOIUnit *GetPrePOI();
	long GetCustomerID();
	CString GetUserID();
	BOOL IsTempCNo();
	long GetDetailPosX();
	long GetDetailPosY();
	CString GetDisplayDong();
	long GetPosX();
	long GetPosY();
	BOOL IsPosValid();
	BOOL IsCredit();
	BOOL IsNewCus();
	long GetUseCount();
	long GetCancelCount();
	long GetMileageBalance();

	BOOL NeedToAddCustomer();
	BOOL IsEmpty();

	CString GetDBCompany();
	CString GetDBDepart();
	CString GetDBManager();
	CString GetDBAddress();
	CString GetDBDetail();
	CString GetDBMemo();
	CString GetDBPhone();
	CString GetDBMP();
	CPOIUnit *GetDBPOI();
	CString GetDBDisplayDong();
	long GetDBPosX();
	long GetDBPosY();
	long GetTelID();

	void SetPrePoiFromNowPoi();
	void SetSearch(CString strSearch);
	void SetCNo(long nCNo, BOOL bTempCNo = FALSE, long nID = 0, CString strUserID = "", long nUseCount = 0, long nCancelCount = 0, long nMileageBalance = 0);
	void SetGNo(long nGNo);
	void SetCompany(CString strCompany);
	void SetDepart(CString strDepart);
	void SetManager(CString strManager);
	void SetAddress(CString strMarkup, CString strNormal = "");
	void SetDetail(CString strDetail);
	void SetMemo(CString strMemo);
	void SetPhone(CString strPhone, BOOL bPhone2 = FALSE);
	void SetMP(CString strMP);
	void SetDetailPos(long nPosX, long nPosY);
	void SetPOI(CPOIUnit *pPOI);
	void SetPrePOI(CPOIUnit *pPOI);
	void SetCredit(BOOL bCredit);
	void SetTelID(long nTelID);
	void SetShowPhoneType(long nShowPhoneType);

	void SetData(long nDongID, long nPosX, long nPosY, BOOL bHasDetailPos, CString strAddress);
	void SetData(long nDongID, long nPosX, long nPosY, CString strDepart, 
		CString strManager, CString strPhone, CString strDetail, 
		long nCNo, long nCustomerID, CString strUserID, 
		long nGNo, CString strMemo, CString strMobile, 
		CString strDisplayDong, CString strCompany,
		BOOL bHasDetailPos, CString strAddress, long nTelID, 
		BOOL bCredit, long nUseCount, long nCancelCount, long nMileageBalance, long nShowPhoneType, BOOL bTempCNo = FALSE, BOOL bEditMode = FALSE);
	BOOL SetData(long nPosX, long nPosY, BOOL bShowMsg = FALSE);
	void SetDataOnlyText(CString strName, CString strDisplayDong);

	void SetDisplayDong(CString strDisplayDong = "");
	void Clear();
	BOOL IsOrder() { return m_nPlaceType == PLACE_ORDER; }
	CString GetCustomerTypeString(long nCNo, long nID, CString strUserID);
	int GetPlaceType();
	CString GetPlaceName();
	void RefreshTelCombo(CString strPhone, CString strMobile);

	BOOL Copy(CRcpPlaceInfo *pSrc);
	void Exchange(CRcpPlaceInfo *pSrc);
	void ShowMap(BOOL bFromCustomerDlg = FALSE);
	void SetOtherPlaceInfo(CRcpPlaceInfo *pOrder, CRcpPlaceInfo *pStart, CRcpPlaceInfo *pDest);
	BOOL CheckDelType(BOOL bAutoChange = TRUE);
	void RefreshCompanyColor();
	BOOL GetRouteDistance2(BOOL bShowMap, BOOL bViaApply,BOOL bChargeCalculate, int  nModifyPoiConfirmCharge);
	void OnContextMenuCall(BOOL bPhone2 = FALSE);
	void OnSelectMenuCall(UINT nID);
	void SendSms(long nCompany, CString strPhone, bool bAllocate = false);
	void DeletePhone(CString strPhone);
	void UpdatePhone(CString strPhone, BOOL bPhone2 = FALSE);
	CRcpPlaceInfo* GetJoinPlace();
	void DeletePhoneThisPlace(CRcpPlaceInfo *pPlace, CString strPhone, int &nReplacePhoneType);
	void Setup();
	void UpdateJoinedControl(UINT nID);
	void UpdateJoinedEditControl(CEdit *pedtSrc, CEdit *pedtDst);
	void SaveAddressToOrder(CRcpPlaceInfo *pPlace);
	void InitDiscountInfo();
	CCustomerDlg *GetCustomerDlg(){return m_pCustomerDlg;};
	void SetStartDontAutoCopy(BOOL bDontAutoCopy) 
	{ 
		m_bStartDontAutoCopy = bDontAutoCopy; 
	}
	void SetMenualAddCustomer(BOOL bMenualAddCustomer)
	{
		m_bManualAddCustomer = bMenualAddCustomer;
	}

protected:
	CCustomerDlg *m_pCustomerDlg;
	long m_nDetailPosX;
	long m_nDetailPosY;
	BOOL m_bTempCNo;
	long m_nCNo;
	long m_nGNo;
	long m_nTelID;
	CPOIUnit *m_pPOI;
	CPOIUnit *m_pPrePOI;  // 기존POI
	CEdit *m_pedtSearch;
	CEdit *m_pedtCNo;
	CEdit *m_pedtCompany;
	CEdit *m_pedtDepart;
	CEdit *m_pedtManager;
	CMarkupStatic *m_pstcAddress;
	CStatic *m_pstcAddressNormal;
	CEdit *m_pedtDetail;
	CEdit *m_pedtMemo;
	CEdit *m_pedtPhone;
	CEdit *m_pedtMP;
	CEdit *m_pedtDisplayDong;
	CButton *m_pbtnShowPhoneType;
	CRcpDlg *m_pRcpDlg;
	CString m_strUserID;
	long m_nCustomerID;
	long m_nUseCount;
	long m_nCancelCount;
	long m_nMileageBalance;
	CString m_strDisplayDong;
	CString m_strPlaceName;
	CRcpPlaceInfo *m_pOrderPlace;	
	CRcpPlaceInfo *m_pStartPlace;	
	CRcpPlaceInfo *m_pDestPlace;
	CComboBox *m_pcmbDelType;
	BOOL *m_pbSkipChangeDelType;
	BOOL m_bCredit;
	BOOL m_bManualDelType;
	MENU_PHONE_ARRAY m_arrMenuPhone;
	BOOL m_bMenuSelectPhone2;
	BOOL m_bStartDontAutoCopy;
	BOOL m_bManualAddCustomer; //161121 자동고객저장 무시 옵션(외부, 구분안됨) by Charko

public:
	long m_nPlaceType;
};



#define GET_WINDOW_TEXT_RETURN(x) CString strTemp; x->GetWindowText(strTemp); return strTemp; 

AFX_INLINE CEdit* CRcpPlaceInfo::GetSearchEdit() { return m_pedtSearch;}
AFX_INLINE CEdit* CRcpPlaceInfo::GetCNoEdit() { return m_pedtCNo;}
AFX_INLINE CEdit* CRcpPlaceInfo::GetCompanyEdit() { return m_pedtCompany;}
AFX_INLINE CEdit* CRcpPlaceInfo::GetDepartEdit() { return m_pedtDepart;}
AFX_INLINE CEdit* CRcpPlaceInfo::GetManagerEdit() { return m_pedtManager;}
AFX_INLINE CMarkupStatic* CRcpPlaceInfo::GetAddressStatic() { return m_pstcAddress;}
AFX_INLINE CEdit* CRcpPlaceInfo::GetDetailEdit() { return m_pedtDetail;}
AFX_INLINE CEdit* CRcpPlaceInfo::GetMemoEdit() { return m_pedtMemo;}
AFX_INLINE CEdit* CRcpPlaceInfo::GetPhoneEdit(BOOL bPhone2) { return bPhone2 ? m_pedtMP : m_pedtPhone;}
AFX_INLINE CEdit* CRcpPlaceInfo::GetMPEdit() { return m_pedtMP;}
AFX_INLINE CEdit* CRcpPlaceInfo::GetDisplayDongEdit() { return m_pedtDisplayDong;}
AFX_INLINE CButton* CRcpPlaceInfo::GetShowPhoneTypeCheck() { return m_pbtnShowPhoneType;}

AFX_INLINE CString CRcpPlaceInfo::GetSearch() { GET_WINDOW_TEXT_RETURN(GetSearchEdit()) }
AFX_INLINE long CRcpPlaceInfo::GetCNo() { return m_nCNo;}
AFX_INLINE long CRcpPlaceInfo::GetGNo() { return m_nGNo;}
AFX_INLINE CString CRcpPlaceInfo::GetCompany() { GET_WINDOW_TEXT_RETURN(GetCompanyEdit()) }
AFX_INLINE CString CRcpPlaceInfo::GetDepart() { GET_WINDOW_TEXT_RETURN(GetDepartEdit()) }
AFX_INLINE CString CRcpPlaceInfo::GetManager() { GET_WINDOW_TEXT_RETURN(GetManagerEdit()) }
AFX_INLINE CString CRcpPlaceInfo::GetDetail() { GET_WINDOW_TEXT_RETURN(GetDetailEdit()) } 
AFX_INLINE CString CRcpPlaceInfo::GetMemo() { if(GetMemoEdit()) {GET_WINDOW_TEXT_RETURN(GetMemoEdit())} else return ""; }
AFX_INLINE CString CRcpPlaceInfo::GetPhone(BOOL bPhone2) { {GET_WINDOW_TEXT_RETURN(GetPhoneEdit(bPhone2))} }
AFX_INLINE CString CRcpPlaceInfo::GetMP() { GET_WINDOW_TEXT_RETURN(GetMPEdit()) }
AFX_INLINE long CRcpPlaceInfo::GetShowPhoneType() {return m_pbtnShowPhoneType->GetCheck() ? 1 : 0; }

AFX_INLINE long CRcpPlaceInfo::GetDetailPosX() { return m_nDetailPosX;}
AFX_INLINE long CRcpPlaceInfo::GetDetailPosY() { return m_nDetailPosY;}
AFX_INLINE CString CRcpPlaceInfo::GetDisplayDong() { GET_WINDOW_TEXT_RETURN(GetDisplayDongEdit()) }
AFX_INLINE CString CRcpPlaceInfo::GetAddress() { return GetAddressStatic()->GetNormalText();}
AFX_INLINE CString CRcpPlaceInfo::GetAddressMarkup() { return GetAddressStatic()->GetMarkupText();}
AFX_INLINE BOOL CRcpPlaceInfo::IsCredit() { return m_bCredit; }
AFX_INLINE long CRcpPlaceInfo::GetTelID() { return m_nTelID; }

AFX_INLINE void CRcpPlaceInfo::SetSearch(CString strSearch) { GetSearchEdit()->SetWindowText(strSearch);}
AFX_INLINE void CRcpPlaceInfo::SetGNo(long nGNo) { m_nGNo = nGNo; RefreshCompanyColor(); }
AFX_INLINE void CRcpPlaceInfo::SetDepart(CString strDepart) { GetDepartEdit()->SetWindowText(strDepart);}
AFX_INLINE void CRcpPlaceInfo::SetManager(CString strManager) { GetManagerEdit()->SetWindowText(strManager);}
AFX_INLINE void CRcpPlaceInfo::SetDetail(CString strDetail) { GetDetailEdit()->SetWindowText(strDetail);}
AFX_INLINE void CRcpPlaceInfo::SetMemo(CString strMemo) { if(GetMemoEdit()) GetMemoEdit()->SetWindowText(strMemo);}
AFX_INLINE void CRcpPlaceInfo::SetPhone(CString strPhone, BOOL bPhone2) { GetPhoneEdit(bPhone2)->SetWindowText(LF->GetDashPhoneNumber(strPhone));}
AFX_INLINE void CRcpPlaceInfo::SetMP(CString strMP) { GetMPEdit()->SetWindowText(LF->GetDashPhoneNumber(strMP)); }
AFX_INLINE void CRcpPlaceInfo::SetDetailPos(long nPosX, long nPosY) { m_nDetailPosX = nPosX; m_nDetailPosY = nPosY;}
AFX_INLINE void CRcpPlaceInfo::SetPOI(CPOIUnit *pPOI) {  m_pPOI = pPOI;  }
AFX_INLINE void CRcpPlaceInfo::SetPrePOI(CPOIUnit *pPOI) { m_pPrePOI = pPOI; }
AFX_INLINE void CRcpPlaceInfo::SetPrePoiFromNowPoi() { m_pPrePOI = m_pPOI; }
AFX_INLINE void CRcpPlaceInfo::SetCredit(BOOL bCredit) { m_bCredit = bCredit; RefreshCompanyColor();}
AFX_INLINE void CRcpPlaceInfo::SetTelID(long nTelID) { m_nTelID = nTelID; }
AFX_INLINE void CRcpPlaceInfo::SetShowPhoneType(long nShowPhoneType) {GetShowPhoneTypeCheck()->SetCheck(nShowPhoneType == 1 ? TRUE : FALSE); }

AFX_INLINE int CRcpPlaceInfo::GetPlaceType() { return m_nPlaceType; }
AFX_INLINE CString CRcpPlaceInfo::GetPlaceName() { return m_strPlaceName; }
AFX_INLINE CPOIUnit* CRcpPlaceInfo::GetPOI() { return m_pPOI; }
AFX_INLINE CPOIUnit* CRcpPlaceInfo::GetPrePOI() { return m_pPrePOI; }
AFX_INLINE long CRcpPlaceInfo::GetCustomerID() { return m_nCustomerID; }
AFX_INLINE CString CRcpPlaceInfo::GetUserID() { return m_strUserID; }
AFX_INLINE BOOL CRcpPlaceInfo::IsTempCNo() { return m_bTempCNo; }
AFX_INLINE BOOL CRcpPlaceInfo::IsNewCus() { return GetCNo() <= 0; }
AFX_INLINE long CRcpPlaceInfo::GetUseCount() { return m_nUseCount; }
AFX_INLINE long CRcpPlaceInfo::GetCancelCount() { return m_nCancelCount; }
AFX_INLINE long CRcpPlaceInfo::GetMileageBalance() { return m_nMileageBalance; }

