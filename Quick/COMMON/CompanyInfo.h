#pragma once



class CCompanyInfo
{
public:
	CCompanyInfo(void);
	~CCompanyInfo(void);


public:
	MAP_CHILD_COMPANY m_ccm;
	vector<BYTE> m_vecChildCompany;
	ST_BOUNDARY_INFO m_bound;

	CBranchInfo *m_pCargoMainBranch;
	CBranchInfo *m_pQuickMainBranch;

	COleDateTime m_dtPenaltyStart;

	long m_nUseCustomerTable;
	long m_nUsePayTable;
	long m_nUseDOrderTable;
	long m_nAllocateSMSType;
	long m_nFirstPage; 
	long m_nSecondPage; 
	long m_nThirdPage; 
	long m_nMaxChildCompanyCode;
	long m_nRcpTimeColor;
	long m_nType;   // nType이 0이면 퀵 1이면 배달
	long m_nAllianceID;
	long m_nChargeSearchOrder[4];

	int	m_nSMSAllocate;
	int m_nRcpTimeColor1;
	int m_nRcpTimeColor2;
	int m_nRcpTimeColor3;
	int m_nRcpTimeColor4;
	int m_nRcpTimeColor5;
	int m_nCompanyWorking;
	int m_nSlowCharge;
	int m_nStateType;
	int m_nCompanyCode;
	int m_nDefaultCharge;
	int m_nShareCompany;
	int m_nShareStartTime;
	int m_nShareCode1;
	int m_nShareCode2;
	int m_nShareCode3;
	int m_nShareCode4;
	int m_nShareCode5;
	int m_nShareStartTime1;
	int m_nShareStartTime2;
	int m_nShareStartTime3;
	int m_nShareStartTime4;
	int m_nShareStartTime5;
	int m_nSubRegion;
	int m_nPenaltyLevel;
	int m_nAutoHangupElapsedMin;

	BOOL m_bAllocateWithPDA;
	BOOL m_bUseInterCall;
	BOOL m_bCheckMidWord;
	BOOL m_bPreventGroupCancel;
	BOOL m_bHideGroupPhone;
	BOOL m_bPreDeposit;
	BOOL m_bUseCID;
	BOOL m_bRcpIntMode1;
	BOOL m_bRcpIntMode2;
	BOOL m_bRcpIntMode3;
	BOOL m_bRcpIntMode4;
	BOOL m_bRcpIntMode5;
	BOOL m_bClientIntMode1;
	BOOL m_bClientIntMode2;
	BOOL m_bClientIntMode3;
	BOOL m_bClientIntMode4;
	BOOL m_bClientIntMode5;
	BOOL m_bSectionView;
	BOOL m_bUseCidPool;
	BOOL m_bWaitSecondCall;
	BOOL m_bUseSlowOrder;
	BOOL m_bAlwaysIntegrate;
	BOOL m_bCreditAfterDiscount;
	BOOL m_bRcpNoHistory;
	BOOL m_bRcpNoChargeHistory;	
	BOOL m_bCidNonfiexdIntegrationTab;	//###LOGIN에서 추가해야함
	BOOL m_bNoUseCNS;
	BOOL m_bUseShareReport;
	BOOL m_bUseBranchShareReport;
	BOOL m_bSearchFourNumberWithUID;	
	BOOL m_bSingleAllocate;
	BOOL m_bSendOnePage;
	BOOL m_bDisableCreditBtn;
	BOOL m_bUseOrderChangeMent;
	BOOL m_bUseDetailDong;
	BOOL m_bUseRTIDOnSpeedAllocate;
	BOOL m_bCapitalArea;
	BOOL m_bUseSearchPopup;
	BOOL m_bUseDaeriShare;
	BOOL m_bUseCoaliShare;
	BOOL m_bNotUseCNS;
	
	CString m_strUsePrgVersion;
	CString m_strName;
	CString m_strBranchName;
	CString m_strBizNo;
	CString m_strBizType1;
	CString m_strBizType2;
	CString m_strPhone;
	CString m_strOwner;
	CString m_strAddress;
	CString m_strCity;
	CString m_strDDD;
	CString m_strAllocateSMSF; 
	CString m_strSlowMsg;
	CString m_strOfficePhone;
protected:
	MAP_SHARED_COMPANY m_ShareCompanyMap;

public:
	MAP_SHARED_COMPANY &GetMap() { return m_ShareCompanyMap;}
	CString GetName(long nCompany = 0);
	CString GetBranchName(long nCompany = 0);
	CString GetCompanyName(long nCompany = 0);	

	long GetRcpIntMode1(long nCompany = 0);	
	long GetShareCode(long nCompany = 0, long nLevel = 1);
	long GetShareCode1(long nCompany = 0);
	long GetShareCode2(long nCompany = 0);
	long GetShareCode3(long nCompany = 0);
	long GetShareCode4(long nCompany = 0);
	long GetShareCode5(long nCompany = 0);
	CString GetProperName(long nCompany);
	CString GetPhone(long nCompany = 0, BOOL bOfficePhone = FALSE);

	BOOL IsShareCompany(long nCompany);
	BOOL IsChildCompany(long nCompany);
	BOOL IsThisCompany(CString strCompanyName, long nCode = 0, long nShareCode1 = 0);
	BOOL HasShareCompany();
	BOOL IsUseBranchShareReport(long nCompany);
	long GetDefaultCharge();
	BOOL IsCapitalShare();
	BOOL IsRealtimeShareCompany();
	BOOL IsRealtimeShareRider(long nRiderCompany);
	BOOL IsCrossCompany(long nCompany);
	
	MAP_SHARED_COMPANY::iterator GetShareMapBegin() { return m_ShareCompanyMap.begin();}
	MAP_SHARED_COMPANY::iterator GetShareMapEnd() { return m_ShareCompanyMap.end(); }

	BOOL IsCargoMain() { return m_nType == SERVICE_TYPE_CARGO; }
	BOOL HasCargoBranch() { return m_pCargoMainBranch != NULL; }
	BOOL IsCargoOnly() { return m_pCargoMainBranch && !m_pQuickMainBranch; }
	BOOL IsQuickOnly() { return !m_pCargoMainBranch && m_pQuickMainBranch; }

	void CheckFirstMain(CBranchInfo *pBi);

	CString GetShareCompanyName(long nCompany);
	CString GetShareCompanyBranchName(long nCompany);
	CString GetShareCompanyPhone(long nCompany);
	CString GetShareCompanyOfficePhone(long nCompany);
	void GetCNsInfo(long nCompany, long &nCnsSearchType1, long &nCnsSearchType2, long &nCnsSearchPaid);
};
