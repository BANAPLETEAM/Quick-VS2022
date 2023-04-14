#pragma once

#include "CallPassFunc.h"

class CInsungCallPassInfo;

class CInsungCallPass : public CCallPassFunc
{
public:
	CInsungCallPass(void);
	~CInsungCallPass(void);

	BOOL CallPass(CMkDatabase *pMkDb, CInsungCallPassInfo &info);
	void ToInsungCarType(int &nCarType);

};

class CInsungCallPassInfo 
{
public:
	CInsungCallPassInfo()
	{
		nPayType = 0;
		nCarType = 0;
		nWayType = 0;
		nCharge = 0;
		nTransCharge = 0;
	}

	CString strCID;
	CString strSCompany;
	CString strSDepart;
	CString strSManager;
	CString strSPhone;
	CString strSDong;
	CString strSDetail;
	CString strDCompany;
	CString strDDepart;
	CString strDManager;
	CString strDPhone;
	CString strDDong;
	CString strDDetail;
	CString strEtc;
	int nPayType;
	int nCarType;
	int nWayType;
	int nCharge;
	int nTransCharge;
};
