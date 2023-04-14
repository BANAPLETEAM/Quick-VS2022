#pragma once




class CAllocGroupRecord : public CXTPGridRecord
{
public:
	class CCheckRecord : public CXTPGridRecordItem
	{
	public:
		CCheckRecord(BOOL bCheck)
		{
			HasCheckbox(TRUE);
			SetChecked(bCheck);
		}
	};
public:
	CAllocGroupRecord::CAllocGroupRecord(long nItem, BOOL bCheck, CString strAllocGroup)
	{ 
		AddItem(new CCheckRecord(bCheck));
		AddItem(new CXTPGridRecordItemText(strAllocGroup));
		
		m_nItem = nItem;


		
	}

	virtual void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
	{
		int nCol = pDrawArgs->pColumn->GetItemIndex();
		int nRow = pDrawArgs->pRow->GetIndex();		

	}

	long m_nItem;
							 
	BOOL GetCheck() { return ((CCheckRecord*)GetItem(0))->IsChecked();}
	void SetCheck(BOOL bCheck) { ((CCheckRecord*)GetItem(0))->SetChecked(bCheck);}
};
// CAllocGroupListDlg ��ȭ �����Դϴ�.

class CAllocGroupListDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAllocGroupListDlg)

public:
	CAllocGroupListDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAllocGroupListDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ALLOC_GROUP_LIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CWnd *m_pParent;
	void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	void RefreshList();
	virtual BOOL OnInitDialog();
	CXTPListCtrl2 m_lstAlloc;
	afx_msg void OnBnClickedCloseBtn();
	afx_msg void OnBnClickedRefreshBtn();
};
