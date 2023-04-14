#include "stdafx.h"
#include "SmsDefine.h"

CSmsDefine::CSmsDefine(void)
{
	m_nSmsGeneral = 0;
	m_nSmsAd = 0;
	m_nLms = 0;
	m_nMms = 0;
}

CSmsDefine::~CSmsDefine(void)
{
}

BOOL CSmsDefine::IsLoadSmsAmount()
{
	if(m_nSmsGeneral == 0 || m_nSmsAd == 0 || m_nLms == 0 || m_nMms == 0)
		return FALSE;

	return TRUE;
}

BOOL CSmsDefine::LoadSmsAmount()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_sms_default_charge");
	cmd.AddParameter(0);

	if(!rs.Execute(&cmd))
		return FALSE;

	long nType;
	long nAmount;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nType", nType);
		rs.GetFieldValue("nAmount", nAmount);

		if(nType == 1) m_nSmsGeneral = nAmount;
		else if(nType == 2) m_nSmsAd = nAmount;
		else if(nType == 3) m_nLms = nAmount;
		else if(nType == 4) m_nMms = nAmount;

		rs.MoveNext();
	}

	return TRUE;
}

long CSmsDefine::GetSmsCharge(long nSmsType, BOOL bAdvertise)
{
	if(!IsLoadSmsAmount())
		LoadSmsAmount();

	if(nSmsType == TYPE_SMS && bAdvertise == TRUE)
		return m_nSmsAd;
	if(nSmsType == TYPE_SMS && bAdvertise == FALSE)
		return m_nSmsGeneral;
	if(nSmsType == TYPE_LMS)
		return m_nLms;
	if(nSmsType == TYPE_MMS)
		return m_nMms;

	return 100;
}
