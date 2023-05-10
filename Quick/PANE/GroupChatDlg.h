#pragma once



// CGroupChatDlg �� ���Դϴ�.

class CGroupChatDlg : public CMyFormView
{
	DECLARE_DYNCREATE(CGroupChatDlg)

protected:
	CGroupChatDlg();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CGroupChatDlg();

public:
	enum { IDD = IDD_GROUP_CHAT_DLG };
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
	afx_msg void OnBnClickedClearButton();
	afx_msg void OnBnClickedSendButton();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	virtual void OnInitialUpdate();
	void RefreshEdit();
	void GetDataText(CString strName, CString strText);
	void GetDataTextSub(CString strName, CString strText, COleDateTime dtDate);

	CEdit m_edtText;
	CEdit m_edtMent;
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DWORD m_dwLastSend;

	CButton m_btnSend;
	CButton m_btnClear;
};


