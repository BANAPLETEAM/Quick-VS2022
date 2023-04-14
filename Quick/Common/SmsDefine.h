#pragma once
class CSmsDefine
{
public:
	CSmsDefine(void);
	~CSmsDefine(void);

private:
	long m_nSmsGeneral; //일반SMS금액
	long m_nSmsAd; //광고SMS금액
	long m_nLms; //LSM금액
	long m_nMms; //MMS금액

public:
	BOOL LoadSmsAmount();
	BOOL IsLoadSmsAmount();
	long GetSmsCharge(long nSmsType, BOOL bAdvertise = FALSE);
};

