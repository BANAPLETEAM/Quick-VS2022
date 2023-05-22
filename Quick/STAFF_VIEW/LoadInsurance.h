#pragma once

enum {LOAD_INS_INSERT, LOAD_INS_DELETE, LOAD_INS_SEARCH}; //�˻�����Ÿ�� ���, ����, �˻�
enum {LOAD_INS_CAR_TYPE_BIKE = 1, LOAD_INS_CAR_TYPE_CAR, LOAD_INS_CAR_TYPE_SUBWAY}; //�������, ����, ����ö
enum {LOAD_INS_WORK_STATE_NORMAL = 1, LOAD_INS_WORK_STATE_CANCEL}; // �����ϻ��� ����, ����. ���� ������ 2�� �����´�

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
