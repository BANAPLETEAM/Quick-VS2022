#pragma once

typedef struct  
{
	long	nMileageSpan;
	long	nMileageDamaSpan;
	long	nMileageBonggoSpan;
	long	nMileageTruckSpan;

	long	nMileageSettingCount;
	long	nMileageSettingCountTruck;
	long	nCompany;
	long	nStartAmount[4][30];
	long	nEndAmount[4][30];
	long	nAmount[4][30];
	long	nTermCount[4];
	int		nClass;

}MILEAGE_INFORMATION;

//typedef map<std::pair<long,long>, CUSTOMER_GROUP_INFORMATION*> CUSTOMER_GROUP_MAP;
typedef map<long, MILEAGE_INFORMATION*> MILEAGE_INFORMATION_MAP;


class CMileageInfo
{
public:
	CMileageInfo(void);
	~CMileageInfo(void);
private:
	MILEAGE_INFORMATION_MAP m_MileageMap;
	long GetCarTypeForCharge(long nCarType);
public:
	void FillData();	
	void Clear();
	BOOL m_bFillData;
	
	MILEAGE_INFORMATION *GetMileData(long nCompany);		
	MILEAGE_INFORMATION_MAP  *GetMileMap() {return &m_MileageMap;}	
	void InsertData(long nCompany);
	long GetMileageVal(long nCompany, int nUiCarType, int nPersonMileageType, 
		long nPersonMileage,long nChargeSum, int nRcpCarType);

	// RcpDlg »ç¿ë
	BOOL IsBranchUseMile(long nCompany , int nMilegeType);
	BOOL IsMileageUseSpanCheck(long nCNo , long nSpanMile, long nEditTNo = 0);
	long GetNowMileageBalance(long nCNo,  long nEditTNo);
};
