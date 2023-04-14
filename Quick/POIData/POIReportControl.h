#pragma once


class CPOIReportControl : public CXTPGridControl
{
public:
	CPOIReportControl(void) {}
	virtual ~CPOIReportControl(void) {}

public:
	BOOL IsVScrollBarVisible() { return m_bVScrollBarVisible; }
};
