#pragma once
class CSmsDefine
{
public:
	CSmsDefine(void);
	~CSmsDefine(void);

private:
	long m_nSmsGeneral; //�Ϲ�SMS�ݾ�
	long m_nSmsAd; //����SMS�ݾ�
	long m_nLms; //LSM�ݾ�
	long m_nMms; //MMS�ݾ�

public:
	BOOL LoadSmsAmount();
	BOOL IsLoadSmsAmount();
	long GetSmsCharge(long nSmsType, BOOL bAdvertise = FALSE);
};

