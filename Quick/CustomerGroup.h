
#pragma once

class CCustomerGroup
{
public:
	CCustomerGroup(void);
	~CCustomerGroup(void);
private:
	MAP_CUSTOMER_GROUP m_mapGroup;
	VEC_CUSTOMER_GROUP m_vecGroup;
	ST_CUSTOMER_GROUP_INFOMATION m_stEmptyInfo;
	MAP_CUSTOMER_GROUP m_mapTemp;

public:
	void FillData();
	void FillCharge();
	void Clear();
	
	ST_CUSTOMER_GROUP_INFOMATION *GetGroupData(long nGNo);
	BOOL SetGroupData(long nGNo, ST_CUSTOMER_GROUP_INFOMATION *newST);
	BOOL SetGroupReportData(long nGNo, ST_CUSTOMER_GROUP_INFOMATION *newST, BOOL bInCludeTree = FALSE);
	BOOL SetGroupDataFull(long nGNo, ST_CUSTOMER_GROUP_INFOMATION *newST, BOOL bInCludeTree = FALSE);
	long GetLevel(ST_CUSTOMER_GROUP_INFOMATION *st);
	MAP_CUSTOMER_GROUP *GetGroup() {return &m_mapGroup;};
	VEC_CUSTOMER_GROUP *GetRefreshGroup() {return &m_vecGroup;};

	MAP_CUSTOMER_GROUP *SearchParentAllGroup(long nGNo);
	CUIntArray* SearchParentAllGroup(CString strSearchWord, int nSearchType);
	BOOL CheckGroup(long nFirst, long nSecond);
	void UpdateGroupCount();
	void SetDataNotIncomeMonth(long nGNo, CString strNotIncomeMonth);
	CString GetAllGNoListFromChildGNo(long nChildGNo);
	void GetTopLevelID_PWD(long nChildGNo, CString &strID, CString &strPWD);
	
};
