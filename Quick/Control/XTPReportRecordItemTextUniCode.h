#pragma once
class CXTPGridRecordItemTextUniCode :public  CXTPGridRecordItemText
{
public:
	CXTPGridRecordItemTextUniCode();
	CXTPGridRecordItemTextUniCode(CString strDummy) :CXTPGridRecordItemText(strDummy)
	{
	}

	~CXTPGridRecordItemTextUniCode();

	void SetControl(CXTPGridControl *pControl)
	{
		m_pControl = pControl;
	}
		
	void SetRecord(CXTPGridRecord* pReportRecord);
	void ResetMarkupUIElement();
};

