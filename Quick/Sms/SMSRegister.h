#pragma once

#include "BranchSel.h" 
#include "XTPListCtrl_Branch.h"
// CSMSRegister 대화 상자입니다.

class CSMSRegister : public CMyDialog
{
	DECLARE_DYNAMIC(CSMSRegister)

public:
	CSMSRegister(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSMSRegister();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_SMS_REGISTER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()


	CXTPListCtrl_Branch m_lstBranch;
	CBranchSel m_cBranch;
	CFlatMainEdit m_edtMain;
	CFlatSubEdit m_edtSub;
	CBranchMainBtn m_btnMain;
	CBranchSubBtn m_btnSub;

	CFlatEdit2		m_edtSMSCallBack;
	CButton			m_btnHelp;
	CComboBox		m_cmbCallBackType;
	CButton			m_btnHPRegister;

	CMyStatic		m_stcHPRegister;
	CFlatEdit2		m_edtHPRegister;


	CFlatEdit2		m_edtSMSCallBackEtc;
	CButton			m_rdoCorp;
	CButton			m_rdoCorpNot;
	CButton			m_rdoUse;
	CButton			m_rdoUseNot;


	CButton			m_btnRegister;
	CButton			m_btnClose;
	CMyStatic		m_stcRegisterNo;

	CFlatEdit2		m_edtTelecomDoc;
	CButton			m_btnTelecomUpload;
	CFlatEdit2		m_edtBussinessDoc;
	CButton			m_btnBussindessUpload;

	CFlatEdit2		m_edtContactName;
	CFlatEdit2		m_edtContactJobTitle;
	CFlatEdit2		m_edtContactNumber;


	//CString			m_strRegisterCompanyList;

	long			m_nLoadTelecomState;
	long			m_nLoadIdentityCardState;
	CString			m_strLoadTelecomUrl;
	CString			m_strLoadIdentityCardUrl;

	BOOL			m_bInitDialog;
	BOOL			m_bModifyData;

public:

	long			m_nModifyCompany;
	BOOL			m_bNew;
	long			m_nModifyNo;
	CString			m_strInsertedSMSCallBackNo;
	CWnd			*m_pParent;
	BOOL CheckData();
	void AddNew();
	void InitData();
	void OneBranchList();
	void ModifyEdit();
	void AllControlClear(BOOL bHP);
	void HPRegiserViewType(BOOL bTrue);
	BOOL HPCheckData(CString strCallBackPhone);
	void LoadModifyData();
	BOOL FileUpload(int nType, CString strOldFileName);
	BOOL FileUploads(int nType);

	static BOOL FileUpload(int nType, int nCompany, int nNo, CString strSMSCallback,  BOOL bMsgBox);


	afx_msg void OnCbnSelchangeTelTypeCombo();
	afx_msg void OnBnClickedRegister();
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedTelecomUpload();
	afx_msg void OnBnClickedBussinessUpload();

	afx_msg void OnBnClickedHpRegisterBtn();
	afx_msg void OnBnClickedCloseBtn2();
	afx_msg void OnClose();
};
