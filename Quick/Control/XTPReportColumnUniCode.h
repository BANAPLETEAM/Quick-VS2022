#pragma once


class CXTPGridColumnUniCode : public CXTPGridColumn
{
	
public:
	//DECLARE_DYNAMIC(CXTPGridColumnUniCode);

	CXTPGridColumnUniCode(int nItemIndex, LPCTSTR strName, int nWidth, BOOL bAutoSize = TRUE, int nIconID = XTP_GRID_NOICON, BOOL bSortable = TRUE, BOOL bVisible = TRUE);
	CXTPGridColumnUniCode(int nItemIndex, LPCTSTR strDisplayName, LPCTSTR strInternalName, int nWidth, BOOL bAutoSize = TRUE, int nIconID = XTP_GRID_NOICON, BOOL bSortable = TRUE, BOOL bVisible = TRUE);
	~CXTPGridColumnUniCode();
	 
	void ResetMarkupUIElement();

};

