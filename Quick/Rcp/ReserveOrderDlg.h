#pragma once


class CRcpDlg;
// CReserveOrderDlg ��ȭ �����Դϴ�.

class CReserveOrderDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CReserveOrderDlg)

public:
	CReserveOrderDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CReserveOrderDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RESERVE_ORDER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	virtual void OnOK()	{};

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedReserveChk();
	afx_msg void OnDtnDatetimechangeReserveDateDtp(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeReserveTimeDtp(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeReleaseCombo();
	afx_msg void OnCbnEditchangeReleaseCombo();
	afx_msg void OnCbnSelchangeReleaseStateCombo();
	afx_msg void OnCbnSelchangeAddTimeCombo();
	afx_msg void OnCbnEditchangeReserveReleaseCombo();
	afx_msg	void OnCbnSelchangeReserveReleaseCombo();
	afx_msg void OnDisplayReserveInfo();
	afx_msg void OnBnClickedReserve();

	void InitControl();
	void SetReserve(BOOL bReserve);
	void SetReserveSate(BOOL bReserve);
	void SetReserveTime(COleDateTime dtTime);
	void SetReserveTime(COleDateTime dtDate, COleDateTime dtTime);
	void SetReleaseMin(long nMin);
	void SetReleaseState(BOOL bWait);
	void SetReleaseStateDB(long nStateType);

	BOOL IsReserve();
	long GetChangeRiderForReserve(){ return m_bChangeRiderForReserve; }
	COleDateTime GetReserveTime();
	long GetReleaseMin();
	BOOL IsReleaseAfterWait();
	long GetReleaseStateDB();
	CString GetReserveTimeString();
	void Hide();
	void MakeAddTime();
	void MakerAfxMsgBox();

	CRcpDlg *m_pRcpDlg;
	CDateTimeCtrl m_dtpDate;
	CDateTimeCtrl m_dtpTime;
	long m_bChangeRiderForReserve; //-1 : ���� �ȵ�, 0 : ����ð� �� ����, 1 : ������ �ð� �� ������ ���º���

protected:
	CButton m_chkReserve;
	CComboBox m_cmbReleaseMin;
	CComboBox m_cmbReleaseState;
	CComboBox m_cmbAddTime;
	CMyStatic m_stcInfo;
	COleDateTime m_dtBase;
	long m_nKeyDownCount;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnNMSetfocusReserveTimeDtp(NMHDR *pNMHDR, LRESULT *pResult);
	LONG OnAfxMessageBoxYes(WPARAM wParam, LPARAM lParam);
	LONG OnAfxMessageBoxNo(WPARAM wParam, LPARAM lParam);
};
