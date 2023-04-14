#pragma once
#include "afxwin.h"

#define TYPE_MAIN_TEL 0
#define TYPE_OFFICE_TEL 1

#define MAX_SMS_TEL_COUNT 20

typedef struct{
	CString strTel[MAX_SMS_TEL_COUNT];
	CString strEtc[MAX_SMS_TEL_COUNT];
	long nTelType[MAX_SMS_TEL_COUNT];
} ST_SMS_CALL_BACK;

typedef map<long, ST_SMS_CALL_BACK> MAP_SMS_CALL_BACK;

static MAP_SMS_CALL_BACK m_mapSmsCallBack;

class CSmsComboBox : public CComboBox
{
public:
	CSmsComboBox(void);
	~CSmsComboBox(void);

	void InitSmsPhoneNumber(long nCompany, long nSelTelType = -1, long nDropWidth = 0, CString strPhone = "");
	CString GetSmsPhoneNumber();
	void ChangeSelType(long nTelType);
	void SetReadOnly(BOOL bReadOnly);
};

