#pragma once
#include "afxwin.h"

typedef struct  
{
	int nID;
	CString strWName;
	COleDateTime dtChange;
	int nCompany;
	int nRNo;
	CString strName;
	CString strTel;
	CString strHp;
	CString strID;
	CString strBankAccountOwner;
	CString strBankAccount;
	COleDateTime dtEnter;
	int nCarType;
	int nAllocGroup;
	CString strAddress;
	CString strEtc;
	CString strInnerMemo;
	int nDepositType;
	int nDepositAllocateType;
	int nBankID;
	CString strRTID;
	int nAllocType;
	int nPanaltyTypeShowOrder;
	int nLockTime;
	int nLockCount;
	BOOL bAutoShow;
	BOOL bBigAutoShow;
	BOOL bDamaShow;
	BOOL bRaboShow;
	BOOL bBanShow;
	BOOL bTruckShow;
	BOOL bSubwayShow;
	BOOL b6BanShow;
	BOOL bParcelServiceShow;
	int nThShareExceptType;
	int nWithdrawType;
	int nMaxWithdrawMoneyPerDay;
	int nMinLeftMoneyForWithdraw;
	BOOL bUseRiderTax;
	CString strRTSerial;
	BOOL bAutoAlloc;
	int nMyCallRateType;
	CString strMyCallRateType;
	int nOtherCallRateType;
	CString strOtherCallRateType;
	int nDailyDepositCharge;
	int nTruckMyDepositRate;
	int nTruckOtherDepositRate;
	int nAllocMinCharge;
	CString strCarNo;
	BOOL bInsRegister;
	CString strVRCardNumber;
	long nPreInfoID;
}ST_RIDER_INFO_LOG;

typedef map<int, ST_RIDER_INFO_LOG*> MAP_INFO_DATA;


class CRiderInfoLogDetailRecord : public CXTPGridRecord
{
public:
	CRiderInfoLogDetailRecord(CString strCount, int nRNo, CString strWName, CString strDate,	
		CString strState, CString strBeforeEtc, CString strAfterEtc)
	{
		AddItem(new CXTPGridRecordItemText(strCount));
		AddItem(new CXTPGridRecordItemNumber(nRNo));
		AddItem(new CXTPGridRecordItemText(strWName));
		AddItem(new CXTPGridRecordItemText(strDate));
		AddItem(new CXTPGridRecordItemText(strState));
		AddItem(new CXTPGridRecordItemText(strBeforeEtc));
		AddItem(new CXTPGridRecordItemText(strAfterEtc));
	}
	CRiderInfoLogDetailRecord(CString strCount, CString strState, CString strBeforeEtc, CString strAfterEtc)
	{
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(strState));
		AddItem(new CXTPGridRecordItemText(strBeforeEtc));
		AddItem(new CXTPGridRecordItemText(strAfterEtc));
	}
};

class CRiderInfoLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderInfoLogDlg)

public:
	CRiderInfoLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRiderInfoLogDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_RIDER_INFO_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRefresh();
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnEnChangeSearchEdit();
	DECLARE_MESSAGE_MAP()

public:
	void InitControlData();
	void RemoveControlData();
	void SelectControlData(ST_RIDER_INFO_LOG *pData);
	void RefreshList();
	void InsertListData(CString strCount, ST_RIDER_INFO_LOG *pData);
	CXTPGridRecord * InsertChangeRecord(CString strCount, int nRNo, CString strWName, CString strDate, CString strChange, 
		CString strBefore, CString strAfter, CXTPGridRecord* pMainRecord);


	CString GetDepositType(long nDepositType);
	CString GetDepositAllocateType(long nDepositAllocateType);
	CString GetShareLimit(long nPanaltyTypeShowOrder);
	

public: 
	CXTPListCtrl2 m_List;
	CXTPGridControl m_ListDetail;

	CComboBox m_cmbBankID;

	CFlatEdit2 m_edtSearch;
	MAP_INFO_DATA m_mapData;
};
