#pragma once
class CXTPGridRecordItemUniCode : public CXTPGridRecordItem
{
public:
	CXTPGridRecordItemUniCode();
	~CXTPGridRecordItemUniCode();

	void SetControl(CXTPGridControl *pControl)
	{
		m_pControl = pControl;
	}

	void SetRecord(CXTPGridRecord* pReportRecord);
	void ResetMarkupUIElement();
};

