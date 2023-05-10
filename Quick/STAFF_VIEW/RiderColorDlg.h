#pragma once

#include "MyStatic.h" 
#include "MyDrawButton.h"
// CRiderColorDlg 대화 상자입니다.


class CRiderColorDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderColorDlg)

public:
	CRiderColorDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRiderColorDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_RIDER_COLOR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedWhiteCheck();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBlueCheck();
	afx_msg void OnBnClickedGreenCheck();
	afx_msg void OnBnClickedRedCheck();
	afx_msg void OnBnClickedPurpleCheck();
	afx_msg void OnBnClickedYellowCheck();
	afx_msg void OnBnClickedSkyCheck();
public:
	void SetColorCheck(UINT nFlag);

	CMyDrawButton m_chkWhite;
	CMyDrawButton m_chkBlue;
	CMyDrawButton m_chkGreen;
	CMyDrawButton m_chkRed;
	CMyDrawButton m_chkPurple;
	CMyDrawButton m_chkYellow;
	CMyDrawButton m_chkSky;

	CMyDrawButton m_chkBlack;
	CMyDrawButton m_chkIndigo;
	CMyDrawButton m_chkPink;
	CMyDrawButton m_chkDarkgray;
	CMyDrawButton m_chkLightlategray;
	CMyDrawButton m_chkThistle;
	CMyDrawButton m_chkMidnight;

	CMyStatic m_stc43;

	long m_nColor;

	afx_msg void OnBnClickedBlackCheck();
	afx_msg void OnBnClickedIndigoCheck();
	afx_msg void OnBnClickedPinkCheck();
	afx_msg void OnBnClickedDarkgrayCheck();
	afx_msg void OnBnClickedLightlategrayCheck();
	afx_msg void OnBnClickedThistleCheck();
	afx_msg void OnBnClickedMidnightCheck();
	afx_msg void OnBnClickedClearBtn();
};


