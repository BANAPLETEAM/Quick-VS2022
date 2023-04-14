#pragma once
#include "afxcmn.h"


// CAuthManageLog 대화 상자입니다.

class CAuthManageLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAuthManageLogDlg)

public:
	CAuthManageLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAuthManageLogDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_AUTH_MANAGE_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CXTPListCtrl2 m_List;
	void Refresh();
	virtual BOOL OnInitDialog();
};
