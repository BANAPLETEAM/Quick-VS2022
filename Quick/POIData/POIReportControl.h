#pragma once

#include "XTPReportControlUniCode.h"

class CPOIReportControl : public CXTPReportControlUniCode
{
public:
	CPOIReportControl(void) {}
	virtual ~CPOIReportControl(void) {}

public:
	BOOL IsVScrollBarVisible() { return m_bVScrollBarVisible; }
};
