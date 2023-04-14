// ListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ListCtrl.h"
#include "EditCell.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_EDITCELL 1001

/////////////////////////////////////////////////////////////////////////////
// gxListCtrl

gxListCtrl::gxListCtrl (CString Text /* = "Some Text" */)
{
    DefaultText = Text;
	ZeroMemory((void*)m_bDisableCol, sizeof(BOOL) * MAX_PATH);
	m_nLastEditRow = -1;
	m_nLastEditCol = -1;
	m_bEditing = FALSE;
}

gxListCtrl::~gxListCtrl()
{
}

BEGIN_MESSAGE_MAP(gxListCtrl, CMyListCtrl9)
    //{{AFX_MSG_MAP(gxListCtrl)
    ON_WM_HSCROLL()
    ON_WM_VSCROLL()
    ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndLabelEdit)
    ON_WM_LBUTTONDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// gxListCtrl message handlers

void 
gxListCtrl::Resize (int cx, int cy)
{
    CRect Rect (0, 0, cx, cy);
    MoveWindow (&Rect);
    InvalidateRect (Rect);
    SetColumnWidth (2, LVSCW_AUTOSIZE_USEHEADER);
}

CEdit* 
gxListCtrl::EditSubItem (int Item, int Column)
{
    // The returned pointer should not be saved

    // Make sure that the item is visible
    if (!EnsureVisible (Item, TRUE)) 
    {
		InsertItemEx (Item);
		if (!EnsureVisible (Item, TRUE)) 
			return NULL;
    }

    // Make sure that nCol is valid
    CHeaderCtrl* pHeader = (CHeaderCtrl*) GetDlgItem(0);
    int nColumnCount = pHeader->GetItemCount();
    if (Column >= nColumnCount || GetColumnWidth (Column) < 5)
		return NULL;

    // Get the column offset
    int Offset = 0;
    for (int iColumn = 0; iColumn < Column; iColumn++)
		Offset += GetColumnWidth (iColumn);

    CRect Rect;
    GetItemRect (Item, &Rect, LVIR_BOUNDS);

    // Now scroll if we need to expose the column
    CRect ClientRect;
    GetClientRect (&ClientRect);
    if (Offset + Rect.left < 0 || Offset + Rect.left > ClientRect.right)
    {
		CSize Size;
		if (Offset + Rect.left > 0)
			Size.cx = -(Offset - Rect.left);
		else
			Size.cx = Offset - Rect.left;
		Size.cy = 0;
		Scroll (Size);
		Rect.left -= Size.cx;
    }

    // Get Column alignment
    LV_COLUMN lvCol;
    lvCol.mask = LVCF_FMT;
    GetColumn (Column, &lvCol);
    DWORD dwStyle;
    if ((lvCol.fmt & LVCFMT_JUSTIFYMASK) == LVCFMT_LEFT)
		dwStyle = ES_LEFT;
    else if ((lvCol.fmt & LVCFMT_JUSTIFYMASK) == LVCFMT_RIGHT)
		dwStyle = ES_RIGHT;
    else dwStyle = ES_CENTER;

    Rect.left += Offset+4;
    Rect.right = Rect.left + GetColumnWidth (Column) - 3;
    if (Rect.right > ClientRect.right)
		Rect.right = ClientRect.right;

    dwStyle |= WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL;
    CEdit *pEdit = new gxEditCell (this, Item, Column, GetItemText (Item, Column));
    pEdit->Create (dwStyle, Rect, this, IDC_EDITCELL);

	m_nLastEditRow = Item;
	m_nLastEditCol = Column;
	m_bEditing = TRUE;

	return pEdit;
}

int 
gxListCtrl::HitTestEx (CPoint& Point, int* pColumn)
{
    int ColumnNum = 0;
    int Row = HitTest (Point, NULL);
    
    if (pColumn)
		*pColumn = 0;

    // Make sure that the ListView is in LVS_REPORT
    if ((GetWindowLong (m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT)
		return Row;

    // Get the top and bottom row visible
    Row = GetTopIndex();
    int Bottom = Row + GetCountPerPage();
    if (Bottom > GetItemCount())
	    Bottom = GetItemCount();
    
    // Get the number of columns
    CHeaderCtrl* pHeader = (CHeaderCtrl*) GetDlgItem(0);
    int nColumnCount = pHeader->GetItemCount();

    // Loop through the visible rows
    for(; Row <= Bottom; Row++)
    {
		// Get bounding rect of item and check whether point falls in it.
		CRect Rect;
		GetItemRect (Row, &Rect, LVIR_BOUNDS);
		if (Rect.PtInRect (Point))
		{
			// Now find the column
			for (ColumnNum = 0; ColumnNum < nColumnCount; ColumnNum++)
			{
				int ColWidth = GetColumnWidth (ColumnNum);
				if (Point.x >= Rect.left && Point.x <= (Rect.left + ColWidth))
				{
					if (pColumn)
						*pColumn = ColumnNum;
					return Row;
				}
				Rect.left += ColWidth;
			}
		}
    }
    return -1;
}

BOOL 
hexNumberToInt (CString HexNumber, int& Number)
{
    char* pStopString;
    Number = strtoul (HexNumber, &pStopString, 16);
    return Number != ULONG_MAX;
} // hexNumberToInt

int 
gxListCtrl::InsertItemEx (int Item)
{
    int Result = InsertItem (Item + 1, DefaultText);
    CString ItemVal, Temp;
    if (Item == 0)
		ItemVal = "1000";
    else
	{
		int HexVal;
		Temp = GetItemText (Item - 1, 1);
		hexNumberToInt (Temp, HexVal);
		ItemVal.Format ("%x", HexVal + 1);
	}

    //SetItemText (Item, 1, ItemVal);
    SetItemText (Item, 1, 0);

    SetColumnWidth (2, LVSCW_AUTOSIZE_USEHEADER);

    return Result;
}



int gxListCtrl::InsertItemEx2(int Item)
{
	//int InsertItem(2,DefaultText);
	SetItemText(Item,2,DefaultText);
	return 0;
}

void 
gxListCtrl::OnHScroll (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    if (GetFocus() != this) 
		SetFocus();
    
    CMyListCtrl9::OnHScroll (nSBCode, nPos, pScrollBar);
}

void 
gxListCtrl::OnVScroll (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    if (GetFocus() != this) 
		SetFocus();
    
    CMyListCtrl9::OnVScroll (nSBCode, nPos, pScrollBar);
}

void 
gxListCtrl::OnEndLabelEdit (NMHDR* pNMHDR, LRESULT* pResult) 
{
    LV_DISPINFO *plvDispInfo = (LV_DISPINFO *)pNMHDR;
    LV_ITEM	*plvItem = &plvDispInfo->item;

    if (plvItem->pszText != NULL)
    {
		if(!EndLabelEdit(plvItem))
			SetItemText(plvItem->iItem, plvItem->iSubItem, plvItem->pszText);
    }

	m_nLastEditRow = -1;
	m_nLastEditCol = -1;
	m_bEditing = FALSE;
    *pResult = FALSE;
}

BOOL gxListCtrl::EndLabelEdit(LV_ITEM *plvItem)
{
	return FALSE;
}

void 
gxListCtrl::OnLButtonDown (UINT nFlags, CPoint Point) 
{
    CMyListCtrl9::OnLButtonDown (nFlags, Point);

	   int Index;
    int ColNum;
    if ((Index = HitTestEx (Point, &ColNum)) != -1)
    {
		if(!m_bDisableCol[ColNum])
		{
			if (GetWindowLong (m_hWnd, GWL_STYLE) & LVS_EDITLABELS)
				EditSubItem (Index, ColNum);
		}
    }
}

BOOL gxListCtrl::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN || pMsg->message == WM_CHAR ||
		pMsg->message == WM_KEYUP)
	{
		switch(pMsg->wParam)
		{
			case VK_RETURN:
			case VK_TAB:
				if(m_bEditing && m_nLastEditRow >= 0 && m_nLastEditCol >= 0) 
				{
					if(m_nLastEditCol == GetHeaderCtrl()->GetItemCount() - 1)
					{
						for(int i = 0; i < GetHeaderCtrl()->GetItemCount(); i++)
						{
							if(!m_bDisableCol[i])
							{
								if(pMsg->message == WM_KEYUP)
									EditSubItem(min(m_nLastEditRow + 1, GetItemCount() - 1), i);
								return TRUE;
							}
						}
					}
					else {
						BOOL bFound = FALSE;
						for(int i = m_nLastEditCol + 1; i < GetHeaderCtrl()->GetItemCount(); i++)
						{
							if(!m_bDisableCol[i])
							{
								if(pMsg->message == WM_KEYUP)
									EditSubItem(m_nLastEditRow, i);
								return TRUE;
							}
						}

						if(!bFound)
						{
							for(int i = 0; i < GetHeaderCtrl()->GetItemCount(); i++)
							{
								if(!m_bDisableCol[i])
								{
									if(pMsg->message == WM_KEYUP)
										EditSubItem(min(m_nLastEditRow + 1, GetItemCount() - 1), i);
									return TRUE;
								}
							}
						}
					}
				}
				break;
		}
	}
	
	return CMyListCtrl9::PreTranslateMessage(pMsg);
}
