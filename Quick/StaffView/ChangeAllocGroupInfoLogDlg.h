#pragma once


// CChangeAllocGroupInfoLogDlg 대화 상자입니다.

class CChangeAllocGroupInfoLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChangeAllocGroupInfoLogDlg)

public:
	CChangeAllocGroupInfoLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChangeAllocGroupInfoLogDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHANGE_ALLOC_GROUP_INFO_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	long m_nGroupAllocID;
	afx_msg void OnBnClickedRefreshBtn();
	CXTPListCtrl2 m_lst;
	void RefreshList();
	virtual BOOL OnInitDialog();
};
