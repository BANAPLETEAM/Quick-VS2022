#pragma once
#include "afxwin.h"


// CEmployMentInsuranceDlg 대화 상자입니다.

class CEmployMentInsuranceDlg : public CDialog
{
	DECLARE_DYNAMIC(CEmployMentInsuranceDlg)

public:
	CEmployMentInsuranceDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CEmployMentInsuranceDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_EMPLOYMENT_INSURANCE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	int company_code_;
	CString m_strBizNoImage;

	CEdit m_edtCompanyBizNo;
	CButton m_btnImageUpload;
	CEdit m_edtCompanyOwner;
	CEdit m_edtCompanyLocation;
	CButton m_btnSave;
	CButton m_btnCanel;
	CEdit m_edtCompanyTel;
	CEdit m_edtCompanyBizName;
	CButton m_btnImageShow;
	CButton m_chkNoUse;
	CEdit m_edtSearch;
	CString m_strBizAddress;
	CString m_strZipNo;

	BOOL Save(int company_code);
	BOOL CheckSave(bool msg_box = true);
	bool IsHangul(const char *text);
	bool IsEnglish(const char *text);
	BOOL CheckSave(CString& strBizNo, CString& strOwner, CString& strTel, CString& strLocation, CString& strImage, CString& strBizName, CString &strOwnerSSN, int& not_use_emp_ins_biz_no, bool msg_box = true);
	void CheckControl();
	void UploadImage(CString &strResult);
	void ShowImage(CString strImage);
	void SearchRegion();
	void SetLocationText(CString address, CString zipno);

	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonImageUpload();
	afx_msg void OnBnClickedButtonImageShow();
	CMyStatic m_stc1;
	CMyStatic m_stc2;
	CMyStatic m_stc3;
	CMyStatic m_stc4;
	CMyStatic m_stc5;
	CMyStatic m_stc6;
	CMyStatic m_stc7;
	CXTPListCtrl2 m_lstBranch;
	afx_msg void OnBnClickedButtonLocationSearchBtn();
	void MakeBranchList();
	afx_msg void OnBnClickedCheckNoUse();
	afx_msg void OnBnClickedApplyAllBtn();
	afx_msg void OnReportItemClick(NMHDR* pNotifyStruct, LRESULT* /*result*/);
	afx_msg void OnEnChangeSearchEdt();
	CEdit m_edtOwnerSSN;
};
