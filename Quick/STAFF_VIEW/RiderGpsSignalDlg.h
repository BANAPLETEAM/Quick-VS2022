#pragma once


// CRiderGpsSignalDlg 대화 상자입니다.

class CRGSPaintManager;



class CRiderGpsSignalDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderGpsSignalDlg)

public:
	CRiderGpsSignalDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRiderGpsSignalDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RIDER_GPS_SIGNAL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CRGSPaintManager* m_pRGS;
	CXTPGridControl m_wndReport;

	void RefreshRiderList();
	void RefreshList();
};
