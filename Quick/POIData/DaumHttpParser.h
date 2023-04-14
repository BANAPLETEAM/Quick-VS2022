#pragma once



#include "HttpParser.h"

class CDaumHttpParser : public CHttpParser
{
public:
	CDaumHttpParser(void);
	virtual ~CDaumHttpParser(void);

	void Refresh2(QUERY_INFO &QI);
	void ParseJSON4NaverLocalValues(CString strHtml, vector<SEARCH_RESULT_INFO> *vec);

	CString m_strKakaoKey;
	BOOL m_bLoadKakaoKey;
	void GetKakaoKey();
	CString OpenKakaoLocation(CString strKey, CString strSearch);
};
