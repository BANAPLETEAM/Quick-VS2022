#pragma once

#define MENT_COUNT 9

class CEmoticonDlg;
// CSmsNewBulkMentDlg ��ȭ �����Դϴ�.

class CSmsNewBulkMentDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSmsNewBulkMentDlg)

public:
	CSmsNewBulkMentDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSmsNewBulkMentDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SMS_NEW_BULK_MENT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CWnd *m_pParent;

	afx_msg void OnClickedItemSelect(UINT nItem);
	afx_msg void OnClickedItemUpdate(UINT nItem);
	afx_msg void OnClickedItemEmoticon(UINT nItem);

	long m_nLastSelectIndex;
	long m_nCompany;
	long m_nID[MENT_COUNT];
	CEdit m_edtMent[MENT_COUNT];
	CEmoticonDlg *m_pEmoticonDlg;
	virtual BOOL OnInitDialog();
	void LoadSmsBulkMent();
	void InitSmsBulkMent();

	afx_msg LONG OnSendEmoticon(WPARAM wParam, LPARAM lParam);
};
