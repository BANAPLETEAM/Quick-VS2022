#pragma once

#include "ColorListCtrl.h"

typedef struct{
	long nCompany;
	long nWNo;
	long nANo;
	long nWorkState;
	long nWorkPart;
	CString sID;
	CString sName;
	CString sSSN1;
	CString sSSN2;
	CString sMp;
	CString sPhone;
	long nWorkType;
	CString sAddress;
	CString sMemo;
	COleDateTime dtEnter;
} WNO_STRUCT;

typedef map<long, WNO_STRUCT> WNO_MAP;

class CStaffPage11 : public CMyFormView
{
	DECLARE_DYNCREATE(CStaffPage11)

protected:
	CStaffPage11();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CStaffPage11();

public:
	enum { IDD = IDD_STAFF_PAGE11 };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	WNO_MAP m_WnoMap;
	CXTPListCtrl18 m_List;
	//CXTPListCtrl2 m_List;
	afx_msg void OnBnClickedSearchBtn();
	virtual void OnInitialUpdate();
	void RefreshList();
	CComboBox m_ConWorkingCombo;
	afx_msg void OnBnClickedButtonNew();
	CString GetWorkPart(long nWorkPart);
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeConWorkingCombo();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);

	void ChangeStaff(CDC &pDC);
	
	CFlatEdit2 m_RiderEdt;	
	afx_msg void OnEnChangeRiderEdit();
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	void OnViewExcel();
	void OnWorkOk();
	void OnWorkStop();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnReportItemChange(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	CStatic m_DrawStc;
	afx_msg void OnPaint();
	CString GetWorkType(long nWorkType);
	void PrintLine(CDC *pDC, CRect &rc, CString strTitle, CString strText);
	void InitControl();
};


