#pragma once
#include "afxwin.h"

class CProperChargePaintManager;
// CProperChargeDlg 대화 상자입니다.



class CProperChargeDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CProperChargeDlg)

public:
	CProperChargeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CProperChargeDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PROPER_CHARGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CXTPGridControl m_lstReport;
	CProperChargePaintManager *m_pReportPaint;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCloseBtn();
	void RefreshList();
	long m_nStartID;
	long m_nDestID;
	long m_nCarType;
	long m_nCharge;
	long m_nProperCharge;
	long m_nProperCharge1;
	long m_nProperCharge2;
	afx_msg void OnEnChangeEdit1();
	CFlatEdit2 m_edtCharge;
	CFlatEdit2 m_edtProperCharge;
	CFlatEdit2 m_edtProperCharge2;
	afx_msg void OnBnClickedSelectBtn1();
	afx_msg void OnBnClickedSelectBtn2();
	CComboBox m_cmbCarType;
	afx_msg void OnCbnSelchangeCarTypeCombo();

	long GetCarTypeIndex();
	void SetCarTypeIndex();
	void DeleteList();
	void SetHilight();
};
