#pragma once


// CFakeDlg 대화 상자입니다.

class CFakeDlg : public CDialog
{
	DECLARE_DYNAMIC(CFakeDlg)

public:
	CFakeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CFakeDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_FAKE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
