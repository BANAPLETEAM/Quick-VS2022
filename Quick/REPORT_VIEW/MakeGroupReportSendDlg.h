#pragma once


//#include "Explorer.h"
#include "WebPage.h"

class CMakeGroupReportSendDlg : public CDHtmlDialog
{
	DECLARE_DYNAMIC(CMakeGroupReportSendDlg)

public:
	CMakeGroupReportSendDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMakeGroupReportSendDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SEND_TAX_EMAIL_DLG, IDH = IDR_SEND_TAX_EMAIL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnDocumentComplete(LPDISPATCH pDisp, LPCTSTR szUrl);

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	BOOL IsTimeValid(COleDateTime dt);
	
	HRESULT OnHideClose(IHTMLElement* pElement);
	void SendKindReportWeb(int nSendType,  BOOL bReSend);
	int m_nTest;
	long m_nGNo;
	long m_nGroupReportID;
	BOOL m_bPayMent;
	BOOL m_bBillCollection;
	//CExplorer m_Explorer;
	COleDateTime m_dtPayMent;
	COleDateTime m_dtBillCollection;
	CString m_strEmail;
	IHTMLDocument2 *m_pDoc2;
	CWebPage m_Js;	
};
