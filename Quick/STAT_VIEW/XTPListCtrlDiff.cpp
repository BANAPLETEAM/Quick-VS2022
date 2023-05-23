#include "stdafx.h"
#include "XTPListCtrlDiff.h"

#define		ID_FROZEN_COL_TO_HERE	WM_USER + 1
#define		ID_NO_FROZEN_COL		WM_USER + 2
#define		ID_HIDE_COLUMN			WM_USER + 1000
#define		ID_SHOW_COLUMN			WM_USER + 2000

IMPLEMENT_DYNAMIC(CXTPListCtrlDiff, CXTPListCtrl2)

CXTPListCtrlDiff::CXTPListCtrlDiff()
:m_pSelectedColumn(NULL), m_nShowRecordsetCount(0)
{
}

CXTPListCtrlDiff::~CXTPListCtrlDiff()
{
	ClearColumn();
	ClearRecordset();
}

BEGIN_MESSAGE_MAP(CXTPListCtrlDiff, CXTPListCtrl2)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_FROZEN_COL_TO_HERE,	OnFrozenColToHere)
	ON_COMMAND(ID_NO_FROZEN_COL,		OnNoFrozenCol)
	ON_COMMAND(ID_HIDE_COLUMN,			OnHideColumn)
	ON_COMMAND_RANGE(ID_SHOW_COLUMN,ID_SHOW_COLUMN+1000,OnShowColumn)
END_MESSAGE_MAP()

void CXTPListCtrlDiff::SetColumnInfo(const vector<COL_INFO*>& rVcColInfo)
{
	ClearColumn();

	m_vcColInfo.insert(m_vcColInfo.begin(),rVcColInfo.begin(),rVcColInfo.end());

	// test
	for( int i = 0, iSize = m_vcColInfo.size(); i < iSize; ++i)
	{
		COL_INFO* pCol = m_vcColInfo[i];
		if(pCol == NULL) return;

		//GetLog()->Print("DEBUG : %d, %d, %s \n", pCol->nIndex, pCol->nWidth, pCol->strTitle);
	}
}

void CXTPListCtrlDiff::ParseColumnInfo( CMkRecordset& rRs )
{
	for( int i = 0, iSize = m_vcColInfo.size(); i < iSize; ++i)
	{
		COL_INFO* pCol = m_vcColInfo[i];
		if(pCol == NULL)
		{
			//GetLog()->Print("CXTPListCtrlDiff::ParseColumnInfo() null column pointer");		
			return;
		}

		for(int j = 0, jSize = rRs.GetFiledCount(); j < jSize; ++j)
		{
			CString strRsField = rRs.GetFieldName(j);
			if(pCol->strSQLColName == strRsField)
				pCol->nIndex = j;
		}
	}

}



void CXTPListCtrlDiff::ClearColumn()
{
	for( int i = 0, iSize = m_vcColInfo.size(); i < iSize; ++i)
	{
		if(m_vcColInfo[i] == NULL)
		{
			//GetLog()->Print("CXTPListCtrlDiff::ClearColumn NULL pointer\n");
			continue;
		}
		delete m_vcColInfo[i];
	}
}

void CXTPListCtrlDiff::ClearRecordset()
{
	m_vecRs.clear();
}



void CXTPListCtrlDiff::InitColumnByColumnInfo()
{
	GetRecords()->RemoveAll();
	GetColumns()->Clear();

	for( int i = 0, iSize = m_vcColInfo.size(); i < iSize; ++i)
	{
		COL_INFO* pCol = m_vcColInfo[i];
		if(pCol == NULL)
		{
			//GetLog()->Print("CXTPListCtrlDiff::InitColumnByColumnInfo() : NULL pointer\n");
			return;
		}

		for(int j = 0; j < m_nShowRecordsetCount; ++j)
		{
			InsertColumn(i * m_nShowRecordsetCount + j,	pCol->strTitle,	LVCFMT_RIGHT, pCol->nWidth);
			//GetLog()->Print("%d, %s, %d, %d\n", i,	pCol->strTitle,	LVCFMT_RIGHT, pCol->nWidth);
		}
	}

	Populate();
}

void CXTPListCtrlDiff::AddRecordSet(CMkRecordset* pRs)
{
	m_vecRs.push_back(pRs);
	m_nShowRecordsetCount = m_vecRs.size();
}

void CXTPListCtrlDiff::SetShowRecordsetCount( int nCount )
{
	//if( nCount > m_nShowRecordsetCount)
		//GetLog()->Print("CXTPListCtrlDiff::SetShowRecordsetCount 잘못된 인수 nCount > m_nShowRecordsetCount\n");


}

BOOL CXTPListCtrlDiff::RefreshDiff()
{
	if( m_vecRs.empty() )
	{
		//GetLog()->Print("CXTPListCtrlDiff::RefreshDiff() : no recordset data \n");
		return FALSE;
	}

	for( int i = 0, iSize = m_vecRs.size(); i < iSize; ++i)
	{
		CMkRecordset* pRs = m_vecRs[i];
		if(pRs == NULL)
		{
			//GetLog()->Print("CXTPListCtrlDiff::RefreshDiff() : null pointer \n");
			return FALSE;
		}

		if( pRs->GetRecordCount() == 0)
		{
			//GetLog()->Print("CXTPListCtrlDiff::RefreshDiff() : Invaild RecordSet \n");
			return FALSE;
		}
	}

	GetRecords()->RemoveAll();
	GetColumns()->Clear();
	
	ParseColumnInfo(*(m_vecRs[0]) );
	InitColumnByColumnInfo();

	int nMaxRecordNum = 0;
	for(DWORD t = 0;  t < m_vecRs.size(); ++t)
	{
		if(m_vecRs[t]->GetRecordCount() >= nMaxRecordNum)
			nMaxRecordNum = m_vecRs[t]->GetRecordCount();
	}

	for(int n = 0;  n <nMaxRecordNum; n++)
		InsertItem(n, "");

	for(int i = 0; i < m_nShowRecordsetCount; ++i)
		RefreshFromRecord(*m_vecRs[i],i);
	
	Populate();
	return FALSE;
}

BOOL CXTPListCtrlDiff::RefreshColumnDiff()
{
	GetRecords()->RemoveAll();
	GetColumns()->Clear();

	InitColumnByColumnInfo();

	Populate();
	return FALSE;
}

BOOL CXTPListCtrlDiff::RefreshFromRecord(CMkRecordset& rs, int nRsIndex)
{
	rs.MoveFirst();
	for(int n = 0;  n < rs.GetRecordCount(); n++)
	{
		for( int i = 0, iSize = m_vcColInfo.size(); i < iSize; ++i)
		{
			COL_INFO* pCol = m_vcColInfo[i];
			if(pCol == NULL)
			{
				//GetLog()->Print("RefreshFromRecord::RefreshFromRecord() : NULL pointer\n");
				return FALSE;
			}

			CString strFiledName = rs.GetFieldName(pCol->nIndex);
			CString strFiledValue = "";
			if( rs.GetFieldType(pCol->nIndex) != typeFloat )
				strFiledValue = rs.GetFieldValueToString(pCol->nIndex);
			else
			{
				double f;
				rs.GetFieldValue(pCol->strSQLColName, f);
				strFiledValue.Format("%.1f", f);
			}
			strFiledValue = FormatString(strFiledValue, rs.GetFieldType(pCol->nIndex));
			SetItemText(n, i * m_nShowRecordsetCount + nRsIndex,strFiledValue);
			//GetLog()->Print("%d, %d, %s\n", n, i * m_nShowRecordsetCount + nRsIndex,strFiledValue);
		}
		rs.MoveNext();
	}
	return TRUE;
}


CString CXTPListCtrlDiff::FormatString( CString strText, int nType )
{
	if(typeLong == nType || typeInt == nType)
	{
		return LF->GetMyNumberFormat(strText);
	}
	else if(typeFloat == nType)
	{
		// 100이 넘는 float 값에 대해서는 정수값만 표시(이 경우는 실제로 int형인데 오버플로때문에 float로 변환한 결과일 경우가 많다.
		if( strText.Left(strText.Find('.')).GetLength() > 3 ) 
			return LF->GetMyNumberFormat(strText.Left(strText.Find('.'))) ;
		// 100 이하의 float값에 대해서는 소수 아래 자리를 표시함
		else
			return LF->GetMyNumberFormat(strText.Left(strText.Find('.'))) + strText.Right(strText.GetLength() - strText.Find('.'));
	}
	return strText;
}

void CXTPListCtrlDiff::SetSelectedRow(long nRow)
{
	CXTPGridRows *pRows = GetRows();
	CXTPGridRow *pRow = pRows->GetAt(nRow);

	GetSelectedRows()->Select(pRow);
}

void CXTPListCtrlDiff::OnFrozenColToHere( )
{
	if( !m_pSelectedColumn ) return;

	CXTPGridColumns* pColumns = GetColumns();
	int j = 0;
	for( int i = 0, iSize = m_pSelectedColumn->GetIndex(); i < iSize; ++i )
	{
		CXTPGridColumn* pColumn = pColumns->GetAt(i);
		if(pColumn->IsVisible()) ++j;
	}

	SetFreezeColumnsCount(j+1);

}

void CXTPListCtrlDiff::OnShowColumn( UINT nIndex )
{
	if( nIndex < 0 ) return;

	if( m_mapShowMenu.find(nIndex) == m_mapShowMenu.end() ) return;
	CXTPGridColumn* pColumn = m_mapShowMenu.find(nIndex)->second;
	pColumn->SetVisible(TRUE);
	GetColumns()->ChangeColumnOrder(m_pSelectedColumn->GetIndex(), pColumn->GetIndex() );
//by mksong (2010-11-11 오후 7:59)
//	GetColumns()->GetReportHeader()->OnColumnsChanged();
}

void CXTPListCtrlDiff::OnNoFrozenCol()
{
	SetFreezeColumnsCount(0);
}

void CXTPListCtrlDiff::OnHideColumn()
{
	if(!m_pSelectedColumn) return;

	m_pSelectedColumn->SetVisible(FALSE);
}


void CXTPListCtrlDiff::OnHeaderRClick(CPoint pt)
{
	CMenu menu;
	VERIFY(menu.CreatePopupMenu());

	CXTPGridColumns* pColumns = GetColumns();

	m_mapShowMenu.clear();
	int j = 0;
	for( int i = 0, iSize = pColumns->GetCount(); i < iSize; ++i )
	{
		CXTPGridColumn* pColumn = pColumns->GetAt(i);
		if(!pColumn->IsVisible())
		{
			m_mapShowMenu.insert(map<int, CXTPGridColumn*>::value_type(ID_SHOW_COLUMN + j, pColumn) );
			++j;
		}
	}

	m_pSelectedColumn = GetReportHeader()->HitTest(pt);

	// create main menu items
	menu.AppendMenu(MF_STRING,		ID_FROZEN_COL_TO_HERE,	"여기까지 고정 열로 만듬");
	menu.AppendMenu(MF_STRING,		ID_NO_FROZEN_COL,		"고정행렬 사용안함");
	menu.AppendMenu(MF_SEPARATOR,	(UINT)-1,				(LPCTSTR)NULL);
	menu.AppendMenu(MF_STRING,		ID_HIDE_COLUMN,			"[" + m_pSelectedColumn->GetCaption() + "]" + "표시하지 않음");

	for( map<int,CXTPGridColumn*>::iterator iter = m_mapShowMenu.begin(); iter != m_mapShowMenu.end(); ++iter)
	{
		int nMenuID					= iter->first;
		CXTPGridColumn* pColumn2	= iter->second;

		menu.AppendMenu(MF_STRING,		nMenuID,	"여기에 [" + pColumn2->GetCaption() + "] 표시");
	}

	CPoint point = pt;
	ClientToScreen(&point);

	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CXTPListCtrlDiff::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CPoint pt = point;
	ScreenToClient(&pt);

	if(m_rcHeaderArea.PtInRect(pt))
	{
		if(!GetColumns()->GetFirstVisibleColumn() ) return;
		OnHeaderRClick(pt);
		return;
	}

	CXTPGridRow *pRow = this->HitTest(pt);	
	//.	GetSelectedRows()->Select(pRow);
	GetParent()->PostMessage(WM_CONTEXTMENU, (WPARAM)pWnd, MAKELPARAM(point.x, point.y));
}