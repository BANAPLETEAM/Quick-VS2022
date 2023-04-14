#pragma once


// CSelectMsgSendTypeDlg 대화 상자입니다.

class CSelectMsgSendTypeDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSelectMsgSendTypeDlg)

public:
	CSelectMsgSendTypeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSelectMsgSendTypeDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SELECT_MSG_SEND_TYPE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);

public:
	CXTPListCtrl2 m_lstSelect;
	long m_nSelectedType;
	CString m_strTitle;
};
