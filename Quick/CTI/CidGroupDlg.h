#pragma once



class CCidGroupDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCidGroupDlg)

public:
	enum ColumnsName
	{
		kNumber = 0,
		kCompanyName,
		kBranchName,
		kPhoneNumber,
		kCentralOfficeGroup,
		kID, //invisiable
		kColumnsNameTotal,
	};
	



public:
	CCidGroupDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCidGroupDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CID_GROUP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedAddBulkBtn();
	
	DECLARE_MESSAGE_MAP()

public:
	CXTPGridControl m_List;
	CFlatEdit2 m_edtLine1;
	CFlatEdit2 m_edtLine2;
	
	void RefreshList();
	BOOL CheckIntegrity();

	afx_msg void OnBnClickedOk();
};
