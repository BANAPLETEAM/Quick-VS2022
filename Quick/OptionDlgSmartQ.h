#pragma once
#include "afxwin.h"



// COptionDlgSmartQ �� ���Դϴ�.

class COptionDlgSmartQ : public CMyFormView
{
	DECLARE_DYNCREATE(COptionDlgSmartQ)

protected:
	COptionDlgSmartQ();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~COptionDlgSmartQ();

public:
	enum { IDD = IDD_OPTION_DLG_SMARTQ };
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
	BOOL Save(long nCompany, BOOL bAll);

	CButton m_chkUseSmartQuick;
	CButton m_chkAbleSmartQuickCancel;
	CEdit m_edtSmartQMent;
	CButton m_chkSendSmartQMent;
	afx_msg void OnEnChangeSendSmartqMentEdit();
	CStatic m_stcLength;
	CButton m_chkUseRcpTimeCheck;
	CComboBox m_cmbRcpTimeStart;
	CComboBox m_cmbRcpTimeEnd;
};


