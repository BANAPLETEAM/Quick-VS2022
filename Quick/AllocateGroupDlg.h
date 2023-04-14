#pragma once



class CAllocateGroupDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAllocateGroupDlg)

public:
	CAllocateGroupDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAllocateGroupDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ALLOCATE_GROUP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	
	DECLARE_MESSAGE_MAP()

public:
	CXTPListCtrl2 m_List;
	int m_nItem;
	
	void RefreshList();
	BOOL CheckIntegrity();

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDelBtn();
	afx_msg void OnLbnDblclkListSearch(NMHDR * pNotifyStruct, LRESULT *result);
	afx_msg void OnBnClickedClose();
};
