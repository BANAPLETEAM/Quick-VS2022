#pragma once
#include "afxwin.h"

typedef map<CString, CString> SMS_RELACE_MAP;

// CAllocateSMSFSettingDlg 대화 상자입니다.

class CAllocateSMSFSettingDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAllocateSMSFSettingDlg)

public:
	CAllocateSMSFSettingDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAllocateSMSFSettingDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ALLOCATE_SMS_F_SETTING_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	long m_nCompany;
	SMS_RELACE_MAP m_map;
	afx_msg void OnBnClickedSaveButton();
	afx_msg void OnBnClickedCloseButton();
	CEdit m_edtInput;
	CEdit m_edtSample;
	afx_msg void OnEnChangeInputEdit();
	afx_msg void OnBnClicked(UINT nFlag); 
	void GetLastIndex(CStringW sInput, long nStartIndex, long &nLastIndex, CString &sCount);
	CString GetReplaceChar(CStringW &sInputW, long nNextStartIndex = 0);
	void FillMap(CMkRecordset *pRs = NULL);
	CString m_strInput;
	CStatic m_stcByte;
};
