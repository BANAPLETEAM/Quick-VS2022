#pragma once
class CXTPGridRecordUniCode : public CXTPGridRecord
{
public:
	CXTPGridRecordUniCode();
	~CXTPGridRecordUniCode();

public:
	void SetReportControl(CXTPGridControl* pReportControl);
	CXTPGridRecordItem* AddItem(class CXTPGridRecordItemUniCode* pItem);
	CXTPGridRecordItem* AddItem(class CXTPGridRecordItemTextUniCode* pItem);

	CXTPGridRecord* Add(CXTPGridRecord* pRecord);

};

