#pragma once

#include "explorer.h"

// CSignDlg ��ȭ �����Դϴ�.

class CRecPlayerDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRecPlayerDlg)

public:
	CRecPlayerDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRecPlayerDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RECPLAYER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CExplorer m_Explorer;
	COleDateTime m_dtDate;
	CString m_strDate;
	CString m_strKeyPhoenID;
	CString m_strTellNumber;
	CString m_strFileName;
	CString m_strBound;
	CString m_strYY;
	CString m_strMM;
	CString m_strDD;

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();

	HRESULT	GetPostData(CString strKey, LPVARIANT pvPostData);

	void InitPostFormData(COleDateTime date, CString strFolderDate, CString strKeyPhoenID, CString strTellNumber, CString strFileName, int nBound);
	void AddPostFormData(COleDateTime date, CString strFolderDate, CString strKeyPhoenID, CString strTellNumber, CString strFileName, int nBound);
	void RemovePostFormData();
	CString GetPostFormData();

	void Navigate();

};
