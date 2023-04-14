#pragma once


// CMsgPowerDlg 대화 상자입니다.
class CMkDatabase;

class CMsgPowerDlg : public CMyResizeDialog
{
	DECLARE_DYNAMIC(CMsgPowerDlg)

public:
	CMsgPowerDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMsgPowerDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MSG_POWER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOkBtn();
	afx_msg void OnBnClickedCancelBtn();

protected:
	CXTPGridControl m_wndReportCtrl;
	CImageList m_ilIcons;

public:
	virtual BOOL OnInitDialog();
	void RefreshList();
	void SaveList();

public:
	CMkDatabase *m_pDB;
};
