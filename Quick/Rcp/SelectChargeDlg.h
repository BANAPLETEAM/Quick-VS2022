#pragma once


class CMkRecordset;

// CSelectChargeDlg ��ȭ �����Դϴ�.

class CSelectChargeDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSelectChargeDlg)

public:
	CSelectChargeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSelectChargeDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SELECT_CHARGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	CMkRecordset *m_pRs;
	CListCtrl m_List;

	BOOL m_nRunType;
	BOOL m_nWayType;
	BOOL m_nCarType;
    int m_nChargeBasic;
	int m_nChargeDis;
	int m_nChargeAdd;
	CString m_strDongCharge;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedDongChargeBtn();
	afx_msg void OnBnClickedCancel();
};
