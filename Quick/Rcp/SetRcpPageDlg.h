#pragma once
#include "afxwin.h"


#define	STATE_COLOR_TX1		RGB(0, 0, 0)
#define	STATE_COLOR_TX2		RGB(0, 0, 0)
#define	STATE_COLOR_TX3		RGB(0, 0, 0)
#define	STATE_COLOR_TX4		RGB(0, 0, 0)
#define	STATE_COLOR_TX5		RGB(0, 0, 0)
#define	STATE_COLOR_TX6		RGB(0, 0, 0)
#define	STATE_COLOR_TX7		RGB(0, 0, 0)
#define	STATE_COLOR_TX8		RGB(0, 0, 0)
#define	STATE_COLOR_TX9		RGB(0, 0, 0)
#define	STATE_COLOR_TX10	RGB(0, 0, 0)
#define	STATE_COLOR_TXA		RGB(0, 100, 0)

#define	STATE_COLOR_BK1		RGB(255, 230, 255) //접수
#define	STATE_COLOR_BK2		RGB(255, 255, 200) //대기
#define	STATE_COLOR_BK3		RGB(255, 255, 150) //예약
#define	STATE_COLOR_BK4		RGB(230, 255, 230) //개별
#define	STATE_COLOR_BK5		RGB(255, 255, 255) //배차
#define	STATE_COLOR_BK6		RGB(235, 235, 235) //픽업
#define	STATE_COLOR_BK7		RGB(255,255,255) //완료
#define	STATE_COLOR_BK8		RGB(230,230,255) //취소
#define	STATE_COLOR_BK9		RGB(200,200,255) //문의
#define	STATE_COLOR_BK10	RGB(255, 230, 230) //인터넷
#define	STATE_COLOR_BK12	RGB(150, 150, 255) //선택오더

#define	STATE_INSUNG_COLOR_TXA		RGB(0, 0, 100)

#define	STATE_INSUNG_COLOR_BK1		RGB(255, 255, 0) //접수
#define	STATE_INSUNG_COLOR_BK2		RGB(255, 255, 128) //대기
#define	STATE_INSUNG_COLOR_BK3		RGB(243, 207, 207) //예약
#define	STATE_INSUNG_COLOR_BK4		RGB(239, 225, 195) //개별
#define	STATE_INSUNG_COLOR_BK5		RGB(219, 234, 200) //배차
#define	STATE_INSUNG_COLOR_BK6		RGB(235, 235, 235) //픽업
#define	STATE_INSUNG_COLOR_BK7		RGB(255, 255, 255) //완료
#define	STATE_INSUNG_COLOR_BK8		RGB(201, 230, 233) //취소
#define	STATE_INSUNG_COLOR_BK9		RGB(200, 200, 255) //문의
#define	STATE_INSUNG_COLOR_BK10		RGB(153, 204, 255) //인터넷
#define	STATE_INSUNG_COLOR_BK12		RGB(051, 051, 255) //선택오더

class CSetRcpPageDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSetRcpPageDlg)

public:
	CSetRcpPageDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSetRcpPageDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SET_RCP_PAGE_DLG };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void SaveOrderStateSort();
	afx_msg void OnBnClickedOk();
	afx_msg void OnSelEndOkTextColor();
	afx_msg void OnSelEndOkBackColor();
	afx_msg void OnBnClickedDefaultColorBtn();
	afx_msg void OnCbnSelchangeFontCombo();
	afx_msg void OnCbnSelchangeFontSizeCombo();
	afx_msg void OnBnClickedBoldCheck();
	afx_msg void OnSelEndOKFontCombo();
	afx_msg void OnBnClickedAddBtn();
	afx_msg void OnBnClickedShowMapForm();
	afx_msg void OnBnClickedApplyHeight();
	afx_msg void OnSaveCompanySettingBtn();
	afx_msg void OnLoadCompanySettingBtn();
	afx_msg void OnBnClickedInsungColorBtn();
	void RefreshColor();
	void RefreshOrderStateSort();
	void RefreshMisc(
		int nState1, 
		int nState2, 
		int nState3, 
		int nState4, 
		int nState5, 
		int nState6, 
		int nState7, 
		int nState8, 
		int nState9, 
		int nStateSecondSort,
		int nNotCreateMapForm,
		int nScrollToTop,
		int nGetCustomerMemo,
		int nUseCardOkNumberAddColumn,
		int nShowReserveOrderDay);

	CComboBox m_cmbReserveCount;

	CMyStatic m_stcColor1;
	CMyStatic m_stcColor2;
	CMyStatic m_stcColor3;
	CMyStatic m_stcColor4;
	CMyStatic m_stcColor5;
	CMyStatic m_stcColor6;
	CMyStatic m_stcColor7;
	CMyStatic m_stcColor8;
	CMyStatic m_stcColor9;
	CMyStatic m_stcColor10;
	CMyStatic m_stcColor12;
	CMyStatic m_stcColor15;
	CMyStatic m_stcColorA;

	CXTColorPicker m_cpTextColor1;
	CXTColorPicker m_cpTextColor2;
	CXTColorPicker m_cpTextColor3;
	CXTColorPicker m_cpTextColor4;
	CXTColorPicker m_cpTextColor5;
	CXTColorPicker m_cpTextColor6;
	CXTColorPicker m_cpTextColor7;
	CXTColorPicker m_cpTextColor8;
	CXTColorPicker m_cpTextColor9;
	CXTColorPicker m_cpTextColor10;
	CXTColorPicker m_cpTextColorA;

	CXTColorPicker m_cpBackColor1;
	CXTColorPicker m_cpBackColor2;
	CXTColorPicker m_cpBackColor3;
	CXTColorPicker m_cpBackColor4;
	CXTColorPicker m_cpBackColor5;
	CXTColorPicker m_cpBackColor6;
	CXTColorPicker m_cpBackColor7;
	CXTColorPicker m_cpBackColor8;
	CXTColorPicker m_cpBackColor9;
	CXTColorPicker m_cpBackColor10;
	CXTColorPicker m_cpBackColor12;
	CXTColorPicker m_cpBackColor15;

	CXTFontCombo m_cmbFont;
	CXTFlatComboBox m_cmbFontSize;
	CButton m_chkBold;
	CFlatEdit2 m_edtFontText;
	CButton m_btnShowMapForm;
	CButton m_chkNotCreateMapForm;
	BOOL m_bShowMapForm; 

	CButton m_chkApplyHeight;
	CComboBox m_cmbApplyCombo;	

	void RefreshColorServer(COLORREF crText1,
		COLORREF crText2,
		COLORREF crText3,
		COLORREF crText4,
		COLORREF crText5,
		COLORREF crText6,
		COLORREF crText7,
		COLORREF crText8,
		COLORREF crText9,
		COLORREF crText10,
		COLORREF crText11,
		COLORREF crTextA,
		COLORREF crBack1, 
		COLORREF crBack2, 
		COLORREF crBack3, 
		COLORREF crBack4, 
		COLORREF crBack5, 
		COLORREF crBack6, 
		COLORREF crBack7, 
		COLORREF crBack8, 
		COLORREF crBack9, 
		COLORREF crBack10, 
		CString strFontName,
		long nFontSize,
		BOOL bBold);
	afx_msg void OnBnClickedUseCardOkNumberAddColumnCheck();
	
	afx_msg void OnBnClickedSaveMainColumnBtn();
	afx_msg void OnBnClickedLoadMainColumnBtn();
	afx_msg void OnBnClickedSaveCtiColumnBtn();
	afx_msg void OnBnClickedLoadCtiColumnBtn();
	CComboBox m_cmbStateNumber1;
	CComboBox m_cmbStateNumber2;
	CComboBox m_cmbStateNumber3;
	CComboBox m_cmbStateNumber4;
	CComboBox m_cmbStateNumber5;
	CComboBox m_cmbStateNumber6;

	void SetCombo(CComboBox *pCmb, long nState);
	CString GetCombo(CComboBox *pCmb);
};
