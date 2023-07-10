// DbTestDlg.h : 헤더 파일
//

#pragma once


#define  MAX_SUB_COUNT 5
#define  MAX_MAIN_COUNT 3
#define EVERY_DAY_CHECK 2
// CDbTestDlg 대화 상자
class COptionWorkTimeDlg : public CMyDialog
{
// 생성
public:
	COptionWorkTimeDlg(CWnd* pParent = NULL);	// 표준 생성자
	virtual ~COptionWorkTimeDlg();
// 대화 상자 데이터
	enum { IDD = IDD_OPTION_WORK_TIME_DLG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원


// 구현
protected:
	HICON m_hIcon;

	// 메시지 맵 함수를 생성했습니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()

public:
	void InitControl();
	void LoadData();
	void LoadTime();
	void SaveCharge(BOOL bAllBranch = FALSE);
	void SetWorkTime(BOOL bAllBranch = FALSE);
	BOOL CheckCharge();
	void Day9Check(int nWeekDayException = 0);
	//afx_msg void OnBnClickedTestBtn();
	afx_msg void OnBnClickedBranchAllBtn2();
	
	CButton m_chkAll;
	CButton m_chkMain[MAX_MAIN_COUNT];
	CButton m_chkSub[MAX_SUB_COUNT];

	CDateTimeCtrl		m_dtpMainFrom[MAX_MAIN_COUNT];
	CDateTimeCtrl		m_dtpMainTo[MAX_MAIN_COUNT];
	CDateTimeCtrl		m_dtpSubFrom[MAX_SUB_COUNT];
	CDateTimeCtrl		m_dtpSubTo[MAX_SUB_COUNT];
	COleDateTime		m_dtMainFrom[MAX_MAIN_COUNT];
	COleDateTime		m_dtMainTo[MAX_MAIN_COUNT];
	COleDateTime		m_dtSubFrom[MAX_SUB_COUNT];
	COleDateTime 	m_dtSubTo[MAX_SUB_COUNT];

	CButton m_chkNoWork6;
	CButton m_chkNoWork7;
	CButton m_chkInterCallWork;
	CXTPListCtrl2 m_ChargeList;
	CMyStatic m_stcTimeChareDataRow;
	CMyStatic m_stcIntercallTimeDataRow;
	CComboBox m_cmbChargeDay;
	
	BOOL m_bInitData;
	long m_nCompany;

	afx_msg void OnBnClickedDay9Check();
	afx_msg void OnBnClickedDay8Check();
	afx_msg void OnBnClickedBranchAllBtn();
	afx_msg void OnCheckClickedItem(UINT nItem);
	
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnBnClickedAllDelBtn();
	afx_msg void OnBnClickedRowDelBtn();
	afx_msg void OnCbnSelchangeDayCombo();
	afx_msg void OnBnClickedRowAddBtn();
	afx_msg void OnBnClickedBranchBtn2();
	afx_msg void OnBnClickedBranchBtn();
	
	afx_msg void OnBnClickedCancelBtn3();
	afx_msg void OnStnClickedDatarowStatic();
};

