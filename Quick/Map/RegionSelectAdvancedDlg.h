#pragma once


class CLogiMapBase;
class CSearchRegionSimpleDlg;

// CRegionSelectAdvancedDlg ��ȭ �����Դϴ�.

class CRegionSelectAdvancedDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRegionSelectAdvancedDlg)

public:
	CRegionSelectAdvancedDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRegionSelectAdvancedDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_REGION_SELECT_ADVANCED_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();

	CComboBox m_cmbSido;
	CComboBox m_cmbGugun;
	CComboBox m_cmbDong;
	CLogiMapBase *m_pMap;
	CSearchRegionSimpleDlg *m_pSearchRegionDlg;
	CEdit m_edtSearch;

	afx_msg void OnCbnSelchangeSidoCombo();
	afx_msg void OnCbnSelchangeGugunCombo();
	afx_msg void OnCbnSelchangeDongCombo();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnSelectPOI();
};
