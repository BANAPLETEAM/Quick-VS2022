#include "StdAfx.h"
#include "SmsComboBox.h"

CSmsComboBox::CSmsComboBox(void)
{
}

CSmsComboBox::~CSmsComboBox(void)
{
}

CString CSmsComboBox::GetSmsPhoneNumber()
{
	CString strText;
	GetWindowText(strText);

	long nFind = strText.Find("(");

	if(nFind >= 0)
		strText = strText.Left(nFind);

	strText.Trim();
	strText.Replace("-", "");

	return strText;
}

void CSmsComboBox::ChangeSelType(long nTelType)
{
	long nCount = GetCount();

	for(int i=0; i<nCount; i++)
	{
		if(GetItemData(i) == nTelType)
		{
			SetCurSel(i);
			break;
		}
	}
}

void CSmsComboBox::SetReadOnly(BOOL bReadOnly)
{
	COMBOBOXINFO info = { sizeof(COMBOBOXINFO) }; 
	GetComboBoxInfo(&info);
	CWnd *pWnd = CWnd::FromHandle(info.hwndItem);

	((CEdit*)pWnd)->SetReadOnly(bReadOnly);
}

void CSmsComboBox::InitSmsPhoneNumber(long nCompany, long nSelTelType, long nDropWidth, CString strPhone)
{
	MAP_SMS_CALL_BACK::iterator it = m_mapSmsCallBack.find(nCompany);

	if(nDropWidth > 0)
		SetDroppedWidth(nDropWidth);

	if(it == m_mapSmsCallBack.end())
	{
		CMkRecordset rs(m_pMkDb);
		CMkCommand cmd(m_pMkDb, "select_sms_call_back_number_1");
		cmd.AddParameter(nCompany);

		if(!rs.Execute(&cmd))
			return;

		long nRecordCount = rs.GetRecordCount();

		if(nRecordCount == 0)
		{
			ST_SMS_CALL_BACK st;
			st.strEtc[0] = "";
			st.strTel[0] = "";
			m_mapSmsCallBack.insert(MAP_SMS_CALL_BACK::value_type(nCompany, st));
		}
		else
		{
			ST_SMS_CALL_BACK st;

			for(int i=0; i<rs.GetRecordCount(); i++)
			{
				rs.GetFieldValue("sTel", st.strTel[i]);
				rs.GetFieldValue("sEtc", st.strEtc[i]);
				rs.GetFieldValue("nTelType", st.nTelType[i]);

				rs.MoveNext();
			}

			m_mapSmsCallBack.insert(MAP_SMS_CALL_BACK::value_type(nCompany, st));
		}

		it = m_mapSmsCallBack.find(nCompany);
	}

	ResetContent();

	BOOL bSelect = FALSE;

	for(int i=0; i<MAX_SMS_TEL_COUNT; i++)
	{
		CString strTel = it->second.strTel[i];
		CString strEtc = it->second.strEtc[i];
		long nTelType = it->second.nTelType[i];

		if(strTel.IsEmpty())
			break;

		InsertString(i, LF->GetDashPhoneNumber(strTel) + " (" + strEtc + ")");
		SetItemData(i, nTelType);

		if(nSelTelType == nTelType)
		{
			SetCurSel(i);
			bSelect = TRUE;
		}
		//pBox->SetItemData(i, )		
	}

	if(GetCount() > 0 && !bSelect)
		SetCurSel(0);

	if(!strPhone.IsEmpty())
		SetWindowText(strPhone);
}