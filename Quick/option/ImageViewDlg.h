#pragma once

class CImageHtmlView;
// CImageViewDlg ��ȭ �����Դϴ�.

class CImageViewDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CImageViewDlg)

public:
	CImageViewDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CImageViewDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_IMAGE_VIEW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	CImageHtmlView *m_pView;
	CString m_strUrl;
	virtual BOOL OnInitDialog();
	CCreateContext m_context;
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
