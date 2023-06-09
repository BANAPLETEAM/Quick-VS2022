
#pragma once

class CXTPReportControlUniCode : public CXTPGridControl
{
	//friend class CXTPReportColumnUnicode;
	DECLARE_DYNAMIC(CXTPReportControlUniCode)
		
public:
	CXTPReportControlUniCode();
	~CXTPReportControlUniCode();

	void EnableMarkup(BOOL bEnable = TRUE);
	CXTPGridColumn* InsertColumn(int nItemIndex, LPCTSTR strName, int nWidth);

	CXTPGridRecord* AddRecord(class CXTPGridRecordUniCode*pRecord);

	virtual void DrawNoItems(CDC* pDC, const CRect& rcClient);
	void XTPMarkupDrawText(CXTPMarkupContext* pContext, HDC hDC, LPCTSTR lpszText, LPRECT lpRect, UINT nFormat);

protected:

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};
