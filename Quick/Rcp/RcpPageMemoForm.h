#pragma once
#include "afxwin.h"

static BOOL CALLBACK MyEnumProc(HWND hwnd, LPARAM lParam);

// CRcpPageMemoForm �� ���Դϴ�.

class CRcpPageMemoForm : public CMyFormView
{
	DECLARE_DYNCREATE(CRcpPageMemoForm)

protected:
	CRcpPageMemoForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CRcpPageMemoForm();

public:
	enum { IDD = IDD_RCP_PAGE_MEMO_FORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edtNotePad;
	CButton m_btnOpenNotePad;
	CButton m_btnSaveText;
	CButton m_btnLoadText;
	virtual void OnInitialUpdate();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedOpenNotepadBtn();
	afx_msg void OnEnKillfocusNotepadEdit();
	afx_msg void OnBnClickedSaveTextBtn();
	afx_msg void OnBnClickedLoadTextBtn();

	void OpenNotePad();
	BOOL SendToNotePad(HWND hFindHwd);
	HANDLE RunProgram(CString strFileName, CString strArg, DWORD &pID);
	void SaveText();
	void LoadText();
};


