#pragma once

#include "afxcmn.h"

class COL_INFO
{
public:
	int		nIndex;
	CString	strTitle;
	int		nWidth;
	CString strSQLColName;

	COL_INFO(CString str, int nWth, CString strQueryCol, CString strFmt ="") 
		: nIndex(-1), strTitle(str) , nWidth(nWth), strSQLColName(strQueryCol) {}
};


class CXTPListCtrlDiff : public CXTPListCtrl2
{
	DECLARE_DYNAMIC(CXTPListCtrlDiff)

public:
	CXTPListCtrlDiff();
	~CXTPListCtrlDiff();

	void	SetColumnInfo(const vector<COL_INFO*>& rVcColInfo);
	void	ParseColumnInfo(CMkRecordset& rRs);
	void	ClearColumn();
	void	ClearRecordset();
	void	SetShowRecordsetCount(int nCount);
	BOOL	RefreshDiff();
	BOOL	RefreshColumnDiff();
	void	AddRecordSet(CMkRecordset* pRs);
	void	SetSelectedRow(long nRow);

protected:
	BOOL	RefreshFromRecord(CMkRecordset& rs, int nRsIndex);
	void	InitColumnByColumnInfo();
	CString	FormatString(CString strText, int nType);

private:
	vector<COL_INFO*>				m_vcColInfo;
	vector<CMkRecordset*>			m_vecRs;
	map<int, CXTPGridColumn*>		m_mapShowMenu;
	CXTPGridColumn*				m_pSelectedColumn;
	int								m_nShowRecordsetCount;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnFrozenColToHere();
	afx_msg void OnNoFrozenCol();
	afx_msg void OnHideColumn();
	afx_msg void OnShowColumn(UINT nIndex);
	void OnHeaderRClick(CPoint pt);
};
