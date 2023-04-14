#pragma once


// CRcpPowerDlg 대화 상자입니다.
class CMkDatabase;
class CMakeRcpPower;

class CRcpPowerDlg : public CXTResizeDialog
{
	DECLARE_DYNAMIC(CRcpPowerDlg)

public:
	CRcpPowerDlg(CWnd* pParent = NULL, BOOL bSelectMode = FALSE);   // 표준 생성자입니다.
	virtual ~CRcpPowerDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_RCP_POWER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()


public:
	afx_msg void OnBnClickedOkBtn();
	//afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnBnClickedPartSaveBtn();
	afx_msg void OnBnClickedCopyPowerBtn();

	afx_msg void OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/);
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);	

protected:
	CXTPGridControl m_wndReportCtrl;
	CImageList m_ilIcons;
	BOOL m_bSelectMode;
	CButton m_CopyPowerBtn;
	CButton m_PartSaveBtn;
	CButton m_OkBtn;

public:
	virtual BOOL OnInitDialog();
	void RefreshList();
	void SaveList();

	BOOL m_bDragMode;
	CString m_strDstName;
	long m_nSrcCompany;
	long m_nSrcWNo;
	CString m_strSrcName;

	CFlatEdit2 m_edtBranch;
	CFlatEdit2 m_edtRNo;
	CFlatEdit2 m_edtName;
	CFlatEdit2 m_edtID;

	void FilterList();

	afx_msg void OnEnChangeBranchEdit();
	afx_msg void OnEnChangeRnoEdit();
	afx_msg void OnEnChangeNameEdit();
	afx_msg void OnEnChangeIdEdit();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};



