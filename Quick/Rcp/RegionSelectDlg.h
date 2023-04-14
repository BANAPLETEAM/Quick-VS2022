#pragma once


// CRegionSelectDlg ��ȭ �����Դϴ�.

class CRegionSelectDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRegionSelectDlg)

public:
	CRegionSelectDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRegionSelectDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_REGION_SELECT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnClickedDeleteItem(UINT nFlag);
	afx_msg void OnBnClickedDeleteAllBtn();
	afx_msg void OnBnClickedOkBtn();

public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	long GetAbleIndex();
	void OpenSearchRegionDlg();
	BOOL IsDongInsertOK(long nID);

	CFlatEdit2 m_edtSearch;
	CFlatEdit2 m_edtFirstRegion;
	CFlatEdit2 m_edtSecondRegion;
	CFlatEdit2 m_edtThirdRegion;
	CFlatEdit2 m_edtForthRegion;
	CFlatEdit2 m_edtFifthRegion;

	int m_nSelectedRegionDongID[MAX_REGION_SELECT_COUNT];
	BOOL m_bStart;

	static BOOL IsValidRegionArray(int nRegion[MAX_REGION_SELECT_COUNT]);
	static BOOL IsSelectedRegion(int nDongID, int nRegion[MAX_REGION_SELECT_COUNT]);
};
