#pragma once
#include "explorer.h"


// CSignDlg 대화 상자입니다.

class CSignDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSignDlg)

public:
	CSignDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSignDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SIGN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CExplorer m_Explorer;
	long m_nTNo;
	long m_nCNo;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
