#pragma once

#define	STATE_COLOR_PENALTY	RGB(255, 150, 150)

// CAllocateBoardTRSSetDlg ��ȭ �����Դϴ�.

class CAllocateBoardTRSSetDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAllocateBoardTRSSetDlg)

public:
	CAllocateBoardTRSSetDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAllocateBoardTRSSetDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ALLOCATE_BOARD_TRS_SET_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();

public:
	void RefreshColor();
	void OnSelEndOkBackColor();

	int m_nOfficeLine1;
	int m_nOfficeLine2;
	int m_nOfficeLine3;
	int m_nOfficeLine4;
	CString m_strServerIP;
	CString m_strServerPort;

	CMyStatic m_stcPenaltyColor1;
	CMyStatic m_stcPenaltyColor2;
	CMyStatic m_stcPenaltyColor3;
	CMyStatic m_stcPenaltyColor4;
	CMyStatic m_stcPenaltyColor5;

	CXTColorPicker m_cpPenaltyColor1;
	CXTColorPicker m_cpPenaltyColor2;
	CXTColorPicker m_cpPenaltyColor3;
	CXTColorPicker m_cpPenaltyColor4;
	CXTColorPicker m_cpPenaltyColor5;

	CComboBox m_cmbPenaltyMin1;
	CComboBox m_cmbPenaltyMin2;
	CComboBox m_cmbPenaltyMin3;
	CComboBox m_cmbPenaltyMin4;
	CComboBox m_cmbPenaltyMin5;
};
