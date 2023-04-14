#pragma once
class CIPass
{
public:
	CIPass(CRcpDlg *pRcpDlg);
	~CIPass();

public:
	CRcpDlg *m_pRcpDlg;
	BOOL ClickRcpDlg();
	CWnd* GetRcpWnd();
	void PassData();
	CWnd* GetSubWnd(CWnd *pWnd, long nIndex);

	long GetPayTypeI();
	long GetCarTypeI();
	long GetRunTypeI();
	
	void InsertOrderData(CWnd *pWnd);
	void InsertStartData(CWnd *pWnd);
	void InsertDestData(CWnd *pWnd);
	void InsertOptionData(CWnd *pWnd);
	void InsertChargeData(CWnd *pWnd);
	void AddCharge(CWnd *pWnd, CString strCharge);

	HWND FindExe();
	void GetAllWindowsFromProcessID(DWORD dwProcessID, std::vector <HWND> &vhWnds);
};

