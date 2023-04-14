#pragma once


typedef struct{
	COleDateTime dtDate;
	CString strKeyPhoneID;
	CString strFileName;
	long nBound;
	CString strOperator;
} ST_REC_FILE;
// CRecFileSelectDlg 대화 상자입니다.

class CRecFileSelectDlg : public CDialog
{
	DECLARE_DYNAMIC(CRecFileSelectDlg)

public:
	CRecFileSelectDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRecFileSelectDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_REC_FILE_SELECT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	COleDateTime m_dtDate;
	long m_nCompany;
	CString m_strPhone;

	COleDateTime m_dtRetDate;
	CString m_strRetKeyPhoneID;
	CString m_strRetFileName;
	long m_nRetBound;

	CXTPListCtrl2 m_lst;
	virtual BOOL OnInitDialog();
	void SelectRecord(CXTPGridRecord *pRecord);
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);	
};
