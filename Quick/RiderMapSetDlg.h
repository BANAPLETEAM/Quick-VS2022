#pragma once
#include "afxwin.h"


#ifndef IDD_RIDER_MAP_SET_DLG
	#define IDD_RIDER_MAP_SET_DLG           818
#endif 


// CRiderMapSetDlg ��ȭ �����Դϴ�.

class CRiderMapSetDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderMapSetDlg)

public:
	CRiderMapSetDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRiderMapSetDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RIDER_MAP_SET_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedEditSectorBtn();
	afx_msg void OnBnClickedShowGpsSignalBtn();
	afx_msg void OnBnClickedCheckBox();
	afx_msg void OnCbnSelchangeNearRiderLevelCombo();
	afx_msg void OnCbnSelchangeShowRiderCaptionCombo();

public:
	ST_RIDER_MAP_SET_INFO m_info;
	long m_nCurMapLevel;
	long m_nMaxMapLevel;
	CWnd *m_pParentWnd;

	void RefreshInfo();
	void ResourceToStruct();
	void StructToResource();
	void SetCurMapLevel();
	void InitLevelCombo();
	CButton m_chkLocateRight;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedGpsRiderOnlyCheck();
};
