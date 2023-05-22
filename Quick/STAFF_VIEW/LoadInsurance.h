#pragma once

enum {LOAD_INS_INSERT, LOAD_INS_DELETE, LOAD_INS_SEARCH}; //검색쿼리타입 등록, 삭제, 검색
enum {LOAD_INS_CAR_TYPE_BIKE = 1, LOAD_INS_CAR_TYPE_CAR, LOAD_INS_CAR_TYPE_SUBWAY}; //오토바이, 차량, 지하철
enum {LOAD_INS_WORK_STATE_NORMAL = 1, LOAD_INS_WORK_STATE_CANCEL}; // 보험등록상태 재직, 해지. 당일 해지시 2로 내려온다

class CLoadInsurance
{
public:
	CString m_strUrl;
	CString m_strEtc;
	long m_nType;

	CLoadInsuranceData *m_stLoadInsurance;
	CLoadInsurance(long nType, CLoadInsuranceData *st, CString strEtc); 
	~CLoadInsurance(void);
	BOOL Open();
	BOOL ParseXmlInsertDelete(char *sz);
	BOOL ParseXmlSearch(char *sz);
	
	void UTF8Conv(LPCTSTR lpsz);
	CString ConvertReceivedDataToString(CByteArray & data);

	static void CheckRiderStateChange(ST_RIDER_INFO *stRider, long bAdminTable, CString strSSN, long nCarType, CString strCarNo);
	static CString GetInsCarTypeString(long nCarType);
	static long GetCarTypeForLoadIns(long nCarType);
	static BOOL IsAbleCarType(long nCarType);
	static BOOL IsForceLoadInsuranceRegister(long nCompany);

};
