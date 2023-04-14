#pragma once

#include "PSListCtrl.h"
#include "afxwin.h"
#include "afxdtctl.h"


// CChargeSectionTypeDlg ��ȭ �����Դϴ�.

enum { CST_DISCOUNT = 0, CST_COUPON = 1, CST_MILEAGE = 2,CST_BATCH_MILEAGE = 3,CST_BATCH_MILEAGE_COUNT = 4};

class CChargeSectionTypeDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeSectionTypeDlg)

public:
	CChargeSectionTypeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CChargeSectionTypeDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CHARGE_SECTION_TYPE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()


public:
	CPSListCtrl m_List;
	CComboBox m_cmbTypeName;
	//CComboBox m_cmbCarTypeName;
	CStatic m_stcBranch;
	CString m_strValueName;
	CString m_strTitle;
	int m_nValueType;
	int m_nInitClass;

	BOOL RefreshList();
	BOOL SaveData();
	BOOL CheckData();

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedAddRowBtn();
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeTypeCombo();
	//CComboBox m_cmbCarType;
	//CDateTimeCtrl m_dtpCountType;
	//CStatic m_stcCountType;
	//CStatic m_stcCount;
	afx_msg void OnBnClickedCancel();
	long m_nCompany;
};
