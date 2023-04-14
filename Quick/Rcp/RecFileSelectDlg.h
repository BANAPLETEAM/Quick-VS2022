#pragma once


typedef struct{
	COleDateTime dtDate;
	CString strKeyPhoneID;
	CString strFileName;
	long nBound;
	CString strOperator;
} ST_REC_FILE;
// CRecFileSelectDlg ��ȭ �����Դϴ�.

class CRecFileSelectDlg : public CDialog
{
	DECLARE_DYNAMIC(CRecFileSelectDlg)

public:
	CRecFileSelectDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRecFileSelectDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_REC_FILE_SELECT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
