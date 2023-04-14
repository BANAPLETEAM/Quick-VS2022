#pragma once


class CCountMileageLogSubDlg;

// CCountMileageLogDlg 대화 상자입니다.

class CCountMileageLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCountMileageLogDlg)

public:
	CCountMileageLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCountMileageLogDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_COUNT_MILEAGE_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void PreInitDialog();
public:
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();

	void MoveControl();
	void RefreshList();
	void RefreshCharge();
	void DeleteMapInfo();
	void RefreshMap();
	CWnd* GetTabItem(int nTab);

	long m_nCompany;
	long m_nCNo;
	MAP_COUNT_MILE m_mapPhone;
	MAP_COUNT_MILE m_mapInternet;
	CXTPListCtrl2 m_List;
	CXTPTabControl m_wndTabControl;
	BOOL m_bFirst;
	CStatic m_stcHelp;
};
