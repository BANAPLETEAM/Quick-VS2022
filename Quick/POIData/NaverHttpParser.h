#pragma once

#include "HttpParser.h"


class CNaverHttpParser : public CHttpParser
{
public:
	CNaverHttpParser(void);
	virtual ~CNaverHttpParser(void);
	CString OpenNaver(CString strLocation);
	void Refresh2(QUERY_INFO &QI);

	void ParseJSON4NaverLocalValues(CString strHtml, vector<SEARCH_RESULT_INFO> *vec);

};
