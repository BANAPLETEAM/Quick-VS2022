#pragma once


#include "MyPaintManager.h"
//#include "CountMileageLogDlg.h"
// CCountMileageLogSubDlg �� ���Դϴ�.

class CCountMileageLogSubDlg : public CMyFormView
{
	DECLARE_DYNCREATE(CCountMileageLogSubDlg)

protected:
	CCountMileageLogSubDlg();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CCountMileageLogSubDlg();

public:
	enum { IDD = IDD_COUNT_MILEAGE_LOG_SUB_DLG };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	void RefreshList();
	CMyPaintManager *m_MyPaintManager;
	CXTPGridControl m_List;
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	virtual void OnInitialUpdate();
	long GetColumnCount();

	MAP_COUNT_MILE *m_pMap;
	void SetCountMileMap(MAP_COUNT_MILE *mp){m_pMap = mp; RefreshList();};
	void MoveControl();

	long m_nCMCount;
	long m_nCMCharge;
	long m_nColCount;
	long m_nRowCount;
	long m_nOneRowAbleCount;
};


