#pragma once

class CImageHtmlView;
// CImageViewDlg 대화 상자입니다.

class CImageViewDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CImageViewDlg)

public:
	CImageViewDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CImageViewDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_IMAGE_VIEW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CImageHtmlView *m_pView;
	CString m_strUrl;
	virtual BOOL OnInitDialog();
	CCreateContext m_context;
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
