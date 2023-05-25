#pragma once

class CBranchSel;
class CMyReportPaintManager;

class CXTPGridRecord_Branch : public CXTPGridRecord
{
public:
	class CRecordItemCheck : public CXTPGridRecordItem
	{
	public:
		CRecordItemCheck(BOOL bCheck)
		{
			HasCheckbox(TRUE);
			SetChecked(bCheck);
		}	
	};

public:
	CXTPGridRecord_Branch(BOOL bCheck, CString sGroupName, CString sBranch)
	{  
		AddItem(new CRecordItemCheck(bCheck));
		AddItem(new CXTPGridRecordItemText(sGroupName));
		AddItem(new CXTPGridRecordItemText(sBranch));
	}

	long IsCheck() { return ((CRecordItemCheck*)GetItem(0))->IsChecked(); }
	void SetCheck(BOOL bChk){((CRecordItemCheck*)GetItem(0))->SetChecked(bChk);}

	DWORD m_dwData;
};


class CXTPListCtrl_Branch : public CXTPGridControl//CXTPListCtrl
{
	DECLARE_DYNAMIC(CXTPListCtrl_Branch)

public:
	CXTPListCtrl_Branch();
	virtual ~CXTPListCtrl_Branch();

protected:
	DECLARE_MESSAGE_MAP()

public:
	CBranchSel *m_pcBranch;
	BOOL m_bFirst;
	MAP_BRANCH *m_map;

	BOOL OnItemClick();
	void SetMapData(CBranchSel *cBranch);
	void InitColumn();
	void RefreshList();
	long GetCheckCount(CStringArray &arry);
	void SetAllNoCheckRow();
	DWORD GetItemData(CXTPGridRecord *pRecord);
	void SetItemData(CXTPGridRecord *pRecord, DWORD dwData);
	void CheckChild();

	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
};


