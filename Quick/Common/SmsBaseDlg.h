#pragma once

#include "BranchSel.h"
#include "BitmapButtonEdit.h"
#include "TransparentStatic.h"
#include "SmsComboBox.h"
// CSmsBaseDlg 대화 상자입니다.

#define MENT_CONTROL_COUNT 4

class CEmoticonDlg;


typedef struct 
{
	CString strDt1;
	CString strName;
	CString strStart;
	CString strDest;
	CString strCharge;
	CString strEtc;
	CString strPayType;
	CString strRiderAutoCharge;
	CString strCompanyName;
	CString strRiderName;
} ST_ALLOCATE_DATA;

class CXTPListCtrlSms : public CXTPListCtrl2
{
public:
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{
		int nCol = pDrawArgs->pColumn->GetItemIndex();
		int nRow = pDrawArgs->pRow->GetIndex();

		BOOL bDefault = GetItemLong2(nRow);

		if(bDefault)
			pItemMetrics->clrBackground = RGB(180, 255, 180);
	}
};


class CSmsBaseDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSmsBaseDlg)

public:
	CSmsBaseDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	CSmsBaseDlg(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	virtual ~CSmsBaseDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = 0 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CWnd *m_pMsgWnd;

	CXTPListCtrl2 m_lstMent;

	long m_nMentEditTop;

	long m_nSendCount;
	long m_nSendType;
	long m_nTNo;
	ST_ALLOCATE_DATA m_stAllocate;

	long m_nCompany;
	long m_nCurBalance;
	long m_nSmsType;

	long m_nMMSImageCount;
	CString m_strImage[MAX_MMS_IMAGE_COUNT];
	long m_nImageSize[MAX_MMS_IMAGE_COUNT];

	long m_nType;
	CBranchSel m_cBranch;
	CFlatMainEdit m_edtMain;
	CFlatSubEdit m_edtSub;
	CBranchMainBtn m_btnMain; 
	CBranchSubBtn m_btnSub;
	CFlatBranchEdit m_edtSearchBranch;

	CMyStatic m_stcByte;
	CMyStatic m_stcTitle;
	CEdit m_edtMent;

	CString m_strTitle;

	CStringArray m_strDeleteFileArry;

	CButton m_btnAddFile;
	CSmsComboBox m_cmbCallBack;
	CEdit m_edtReceiveNumber;

	CString m_strRecvPhone;
	CString m_strCallBackPhone;

	CEdit m_edtCurCharge;
	CEdit m_edtCurAbilCount;
	CBitmapButtonEdit m_edtChargePerOne;
	CEdit m_edtSendCount;
	CBitmapButtonEdit m_edtSendCharge;

	CFlatEdit2 m_edtMMSTitle;

	CTransparentStatic m_picLong;
	CTransparentStatic m_picShort;

	CEdit m_edtSaveMent[MENT_CONTROL_COUNT];
	long m_nMentID[MENT_CONTROL_COUNT];
	CButton m_btnEmoticon[MENT_CONTROL_COUNT];

	afx_msg void OnBnClickedCloseBtn();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void ResetData(BOOL bChangeBranch = FALSE, BOOL bCompanyPhone = FALSE);
	void DisplayByte();
	void LoadSmsBalance();
	CString GetSmsType(long nType);
	void SetMentWindowText(CString strText);
	void DeleteTempFile();
	void DisplaySmsCount();
	void SetSendCount(long nCount) { m_nSendCount = nCount; DisplaySmsCount();}
	void OpenEmotionDlg(long nID, CWnd *pWndMain);
	afx_msg LONG OnSendEmoticon(WPARAM wParam, LPARAM lParam);

	virtual void LoadSaveMent();
	void SaveMentEditTop();
	void MoveControlTop(CWnd *pWnd, long nTop, BOOL bMoveBottom = TRUE);


	afx_msg void OnDelete();
	afx_msg	void OnUpdate();
	afx_msg	void OnInsert();

	afx_msg void OnEnChangeMentEdit();
	afx_msg void OnBnClickedSaveButton();

	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedAddFileBtn();
	afx_msg void OnBnClickedAddSmsBalance();
	afx_msg void OnClickedItemSelect(UINT nID);
	afx_msg void OnClickedItemUpdate(UINT nID);
	afx_msg void OnClickedItemEmoticon(UINT nID);


	void UpLoadFile();
	virtual BOOL OnInitDialog();

	CEmoticonDlg *m_pEmoticonDlg;
	long m_nLastSelectIndex;

	CBitmapButton m_btnSend;
	CBitmapButton m_btnSmsMms;
	CBitmapButton m_btnClose;

	void OnOK();
	virtual void OnCancel();

	void ChangeControl();

	BOOL m_bPreSmsMode;
	BOOL m_bSmsMode;

	CMyStatic m_stc1;
	CMyStatic m_stc2;
	CMyStatic m_stc3;
	CMyStatic m_stc4;
	CMyStatic m_stc5;
	CMyStatic m_stc6;
	CMyStatic m_stc7;
	CMyStatic m_stc8;
	CMyStatic m_stc9;
	CMyStatic m_stc10;
	CMyStatic m_stc11;
	CMyStatic m_stc12;
	CMyStatic m_stc13;
	CMyStatic m_stc14;
	CMyStatic m_stc15;
};
