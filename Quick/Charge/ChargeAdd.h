#pragma once

typedef struct  
{
	COleDateTime dtFrom;
	COleDateTime dtTo;
	long nMotoCharge;
	long nDamaCharge;
	long nLaboCharge;
	long nBonggoCharge;
	long nTruckCharge;
}ADDCHARGE;

typedef vector<ADDCHARGE*> VEC_CHARGE_INFO;
typedef map<long, VEC_CHARGE_INFO*> MAP_DAY_CHARGE_INFO;

typedef vector<MAP_DAY_CHARGE_INFO*> VEC_DAY_CHARGE_INFO;
typedef map<long,VEC_DAY_CHARGE_INFO* > MAP_CO_DAY_CHARGE_INFO;

typedef map<COleDateTime, CString> MAP_HOLIDAY;


class CChargeAdd
{
public:
	CChargeAdd(void);
	virtual ~CChargeAdd(void);
protected:	
	VEC_CHARGE_INFO* GetCompanyDayChargeVector(long nCompany, long nDayType	 );
	MAP_HOLIDAY m_mapHoliday;
public:
	BOOL IsMapCompany(long nCompany);
	BOOL IsMapCompanyDay(long nCompany, long nDayType);
	void LoadChargeAddData(long nCompany, BOOL bIntegrated);
	long GetChargeAdd(long nCompany,int  nDay,int nCar,long  nCharge, COleDateTime dtOrderInputTime);
	void LoadHolidayInfo();
	BOOL IsHoliday(COleDateTime dtDate);
	
	MAP_CO_DAY_CHARGE_INFO m_mapCoDayChargeInfo;


};
