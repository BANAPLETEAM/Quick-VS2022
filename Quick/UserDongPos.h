#pragma once


class CPOIInfo
{
public:
	
	int		nDepth;
	long	nPOIID;	
	CString sName;
	CString sAllName;
	BOOL	bFactPOI;
	long	nDongID;
	int		nDongDepth;
	CPOIInfo *pParent;

};

class CDepthInfo
{
private:
	long nDongID[10];
	int nDongGuSiClass[10];
	int nCount;
public:
	void CDeptInfo()
	{
		nCount = 0;
		
	}

	
	void Insert(long nDongID_, long nDongGuSiClass_)
	{
		if(nCount > 10 )
			return;

		nDongID[nCount] = nDongID_;
		
		nDongGuSiClass[nCount] = nDongGuSiClass_;
		nCount++;
	}
	long GetDeptDongID(int nDepth)
	{
		return nDongID[nDepth];
	}
	CString GetDeptDongID_str(int nDepth)
	{
		CString s;
		s.Format("%ld", 	nDongID[nDepth]);
		return s;
	}
	long GetDeptDongGuSi(int nDepth)
	{
		return nDongGuSiClass[nDepth];
	}

	void Clear()
	{
		for(int i = 0; i < nCount; i++)
		{
			nDongID[i] = 0;
			nDongGuSiClass[i] = 0;
		}
		nCount = 0;

		
	}
	int GetDepthCount()
	{
		return nCount;
	}
};

class CDepthInfoValue  
{

	CString sStart[20];
	CString sDest[20];
	int nUnionCount;
	int nType[20];
public:
	CDepthInfoValue()
	{
		nUnionCount = 0;
		
	}
	
	void insert(int nStart, int nDest, int nStartType, int nDestType)
	{
		char buffer[10];
		sStart[nUnionCount]	 = ltoa(nStart, buffer,10);
		sDest[nUnionCount] = ltoa(nDest, buffer,10);
		if(nStartType == 3 && nDestType == 3)
			nType[nUnionCount] = 8;
		else if(nStartType == 3 && nDestType == 2)
			nType[nUnionCount] = 7;
		else if(nStartType == 3 && nDestType == 1)
			nType[nUnionCount] = 6;
		else if(nStartType == 2 && nDestType == 3)
			nType[nUnionCount] = 5;
		else if(nStartType == 1 && nDestType == 3)
			nType[nUnionCount] = 4;
		else if(nStartType == 2 && nDestType == 2)
			nType[nUnionCount] = 3;
		else if(nStartType == 2 && nDestType == 1)
			nType[nUnionCount] = 2;
		else if(nStartType == 1 && nDestType == 2)
			nType[nUnionCount] = 1;
		else if(nStartType == 1 && nDestType == 1)
			nType[nUnionCount] = 0;

		nUnionCount++;
	}
	void Clear()
	{
		for(int i =0; i < 20; i++)
		{
			sStart[i] = "";
			sDest[i] = "";
			nType[i] = 0;
		}
	}

};

typedef map<long, long> USER_DONGPOS_MATCH_MAP;  //  <nDongID, nID>
typedef map<long, USER_DONGPOS_MATCH_MAP*> COMPANY_USER_DONGPOS_MATCH_MAP;  // < nCompany , USER_DONGPOS_MATCH_MAP>


typedef map<long, CPOIInfo*> USER_DONGPOS_MAP;  // < nID, CPOIInfo> -> <nDongID, CPOIInfo>
//typedef map<long, CPOIInfo*> DONGPOS_MAP;  // < nDongID, CPOIInfo> 
typedef map<long, USER_DONGPOS_MAP*> COMPANY_USER_DONGPOS_MAP; // < nCompany, USER_DONGPOS_MAP>
//typedef map<long, DONGPOS_MAP*> COMPANY_DONGPOS_MAP; // < nCompany, USER_DONGPOS_MAP>

class CUserDongPos
{
public:
	CUserDongPos(void);
	~CUserDongPos(void);
private:
	COMPANY_USER_DONGPOS_MAP m_mapCoInUserDongPos;
	COMPANY_USER_DONGPOS_MATCH_MAP m_mapCoInUserDongPosMatch;
	//COMPANY_DONGPOS_MAP m_mapCoInDongPos;


public:
	void FillData(long nCompany);	
	
	void Clear(long nCompany, BOOL bPOIInfoDataDelete=FALSE);
	void ClearMatch(long nCompany);
	CDepthInfo m_DIStart;
	CDepthInfo m_DIDest;
	CDepthInfoValue m_DeptInfoValue;
	
	
	USER_DONGPOS_MAP * GetUserDongPos(long nCompany);		
	USER_DONGPOS_MATCH_MAP * GetUserDongPosMatch(long nCompany);
	void SetUserDong(long nCompany,USER_DONGPOS_MAP *pMap);
	void SetUserDongMatch(long nCompany,USER_DONGPOS_MATCH_MAP *pMap);
	
	//long CUserDongPos::GetUserCharge(long nCompany, long nStartID, long nDestID);

	void GetParentDepthInfo(long nCompany, long nStartID, long nDestID, CString &sStartList, CString &sDestList);
private:
	void GetParentDepthInfoChild(CPOIInfo *pPOIInfo, BOOL bStart);
	long GetDongIDMatch(long nCompany, long nDongID);
	//USER_DONGPOS_MAP  *GetUserDongPosData() {return &m_MileageMap;}	
	//void InsertData(long nCompany);
	

};
