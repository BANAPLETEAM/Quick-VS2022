#pragma once
#include "afxwin.h"

class CLineReport : public CXTPGridRecord
{
public:
	long m_nType;

public:

	class CXTPGridRecordItemChargeNumber : public CXTPGridRecordItemNumber
	{
	public:
		CXTPGridRecordItemChargeNumber(long nProcessRate):CXTPGridRecordItemNumber(nProcessRate)
		{
		}

		CString GetCaption(CXTPGridColumn*)
		{
			return ::GetMyNumberFormat((long)GetValue());
		}		
	};

    CLineReport::CLineReport(CString sTerminalRegion, CString sDest, long nType, long nCharge)
	{
		AddItem(new CXTPGridRecordItemText(sTerminalRegion));
		AddItem(new CXTPGridRecordItemText(sDest));
		AddItem(new CXTPGridRecordItemChargeNumber(nCharge));

		m_nType = nType;		
	}
};

class CLineDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CLineDlg)

public:
	CLineDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CLineDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_LINE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	long m_nCompany;

	CXTPGridControl m_wndReport;		
	void InitCombo();
	void RefreshList();

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedSaveBtn();
	afx_msg void OnCbnSelchangeRegionCombo();
	CComboBox m_RegionCmb;
	CEdit m_SearchStartEdt;
	CEdit m_SearchDestEdt;
	afx_msg void OnEnChangeSearchStartEdit();
	afx_msg void OnEnChangeSearchDestEdit();
	afx_msg void OnBnClickedRefreshBtn();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CButton m_RefreshBtn;
	CButton m_SaveBtn;
};
