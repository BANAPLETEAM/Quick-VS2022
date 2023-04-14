#pragma once
#include "afxwin.h"


// CSmartCallBoardAddDlg 대화 상자입니다.

class CSmartCallBoardAddDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSmartCallBoardAddDlg)

public:
	CSmartCallBoardAddDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSmartCallBoardAddDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_SMART_CALL_BOARD_ADD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strTitle;
	CString m_strBody;
	CString m_strUrl;
	CString m_strMileage;
	CStatic m_stc1;
	CEdit m_edtUrl;
	CEdit m_edtMileage;
	BOOL m_bEventBoard;
	afx_msg void OnBnClickedUploadBtn();
	afx_msg void OnBnClickedViewBtn();
	virtual BOOL OnInitDialog();
	CButton m_btnUpload;
	CButton m_btnView;
	afx_msg void OnBnClickedOk();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	CButton m_chkPlaying;
	BOOL m_bPlaying;
	long m_nMinUseCount;
	CComboBox m_cmbMinUseCount;
	int m_nOrderInsertType;
	CString GetFileNameOnly(CString strFullPath);
};
