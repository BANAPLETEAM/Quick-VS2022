#pragma once


// CRiderGpsSignalDlg ��ȭ �����Դϴ�.

class CRGSPaintManager;



class CRiderGpsSignalDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderGpsSignalDlg)

public:
	CRiderGpsSignalDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRiderGpsSignalDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RIDER_GPS_SIGNAL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CRGSPaintManager* m_pRGS;
	CXTPGridControl m_wndReport;

	void RefreshRiderList();
	void RefreshList();
};
