#pragma once

#include "MyButton.h"

class CMentAddDlg;

#define MAX_COUNT 14
// CSpecialCharDlg 대화 상자입니다.

class CSpecialCharDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSpecialCharDlg)

public:
	CSpecialCharDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSpecialCharDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SPECIAL_CHAR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCloseBtn();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedMemoRdo();
	afx_msg void OnBnClickedTitleRdo();
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	int ReturnType(CString strType);
	void InitChar();
	void MoveDialog();
	void onClickBtn(UINT nFlag);
	void PrintList(UINT Flags, int nPage);
	void Close();
	void MoveFocus();

	CMentAddDlg *m_pParent;

	CMyButton m_CharBtn[14];
	CMyButton m_CloseBtn;
	
	CListCtrl m_List;
	CScrollBar m_Scroll;
	CRect m_Rect;

	int m_nCharCount[MAX_COUNT];
	UINT m_Flag; //현재보고 있는 플래그

	CMyStatic m_stcCharCount;

	CButton m_rdoMemo;
	CButton m_rdoTitle;

	CString m_strCharGroup[MAX_COUNT][100];

};
