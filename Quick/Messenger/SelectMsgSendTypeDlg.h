#pragma once


// CSelectMsgSendTypeDlg ��ȭ �����Դϴ�.

class CSelectMsgSendTypeDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSelectMsgSendTypeDlg)

public:
	CSelectMsgSendTypeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSelectMsgSendTypeDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SELECT_MSG_SEND_TYPE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);

public:
	CXTPListCtrl2 m_lstSelect;
	long m_nSelectedType;
	CString m_strTitle;
};
