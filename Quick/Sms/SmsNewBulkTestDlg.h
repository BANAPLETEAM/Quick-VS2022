#pragma once
#include "afxwin.h"

class CEmoticonDlg;
// CSmsNewBulkTestDlg 대화 상자입니다.


class CXTPListCtrlSmsNew :public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{
		int nCol = pDrawArgs->pColumn->GetItemIndex();
		int nRow = pDrawArgs->pRow->GetIndex();

		CXTPGridRecord *pRecord = pDrawArgs->pRow->GetRecord();

		CString strText4 = pRecord->GetItem(4)->GetCaption(NULL);
		CString strText5 = pRecord->GetItem(5)->GetCaption(NULL);

		if(strText5.Find("성공") < 0) 
		{
			pItemMetrics->clrBackground = RGB(255, 200, 220);
		}

	}
};


class CSmsNewBulkTestDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSmsNewBulkTestDlg)

public:
	CSmsNewBulkTestDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSmsNewBulkTestDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_SMS_NEW_BULK_TEST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRefreshListBtn();
	afx_msg void OnBnClickedSendBtn1();
	afx_msg LONG OnSendEmoticon(WPARAM wParam, LPARAM lParam);

	virtual BOOL OnInitDialog();
	void RefreshList();
	void SendTestSms(CString strPhone, CString strMent, CString strBackPhone);
	void ChangeUserState(BOOL bOK);
	void OpenEmoticonDlg(long nUID);
	void SendTextToEdit(long nUID);

	CDateTimeCtrl m_dtpFrom;
	CDateTimeCtrl m_dtpTo;

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;

	CDateButton m_btnData;

	CEdit m_edtMent1;
	CEdit m_edtMent2;
	CEdit m_edtMent3;
	CEdit m_edtPhone1;
	CEdit m_edtPhone2;
	CEdit m_edtPhone3;
	CEdit m_edtBackPhone1;
	CEdit m_edtBackPhone2;
	CEdit m_edtBackPhone3;

	CEmoticonDlg *m_pEmoticonDlg;

	long m_nSelectedID;

	CButton m_chkSK;
	CButton m_chkKT;
	CButton m_chkLGU;

	CMyStatic m_stc1;
	CMyStatic m_stc2;
	CMyStatic m_stc3;

	CXTPListCtrlSmsNew m_lstReport;
	afx_msg void OnBnClickedSendBtn2();
	afx_msg void OnEnChangePhoneEdit1();
	afx_msg void OnEnChangePhoneEdit2();
	afx_msg void OnBnClickedSendBtn3();
	afx_msg void OnEnChangeMentEdit6();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnSmsOk();
	afx_msg void OnSmsNotOk();
	afx_msg void OnTextTo1();
	afx_msg void OnTextTo2();
	afx_msg void OnTextTo3();
	afx_msg void OnBnClickedEmoticonBtn1();
	afx_msg void OnBnClickedEmoticonBtn2();
	afx_msg void OnBnClickedEmoticonBtn3();

	void SearchList();
	CEdit m_edtSearch;
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnBnClickedSktCheck();
	afx_msg void OnBnClickedKtCheck();
	afx_msg void OnBnClickedLguCheck();
	afx_msg void OnEnChangeMentEdit1();
	afx_msg void OnEnChangeMentEdit2();
	afx_msg void OnEnChangeMentEdit3();

	void DisplayByte(UINT nEdit, UINT nStatic);
};
