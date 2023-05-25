#pragma once

// COtherRegionBranchDlg 대화 상자입니다.

typedef map<CString, CXTPGridRecord*> CITY_MAP;
typedef map<CString, CString> GROUP_MAP;

class CORBRecord :public CXTPGridRecord
{
public:
	CORBRecord::CORBRecord(BOOL bMain, CString sCity, CString sName, CString sOfficePhone, CString sTel, CString sOWner,long nShareCode)
	{
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(sCity));
		AddItem(new CXTPGridRecordItemText(sName));
		AddItem(new CXTPGridRecordItemText(LF->GetDashPhoneNumber(sOfficePhone)));
		AddItem(new CXTPGridRecordItemText(LF->GetDashPhoneNumber(sTel)));
		AddItem(new CXTPGridRecordItemText(sOWner));

		sOfficePhone.Replace("-", "");
		sTel.Replace("-", "");

		if(bMain)
			m_sSearchData = sName + "%" + sOfficePhone+ "%" + sTel + "%" + sCity + "%" + sOWner + "%";
		else 
			m_sSearchData = "";

		m_bMain = bMain;
		m_bRegion = FALSE;
		m_nShareCode = nShareCode;
		m_sCity = sCity;
	}

	CORBRecord::CORBRecord(CString sMainCity)
	{
		AddItem(new CXTPGridRecordItemText(sMainCity));
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));
		AddItem(new CXTPGridRecordItemText(""));

		m_sSearchData = "";
		m_bMain = FALSE;
		m_bRegion = TRUE;
		m_sCity = "";
	}


	void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{
		long nCol = pDrawArgs->pColumn->GetItemIndex();
 
		BOOL bMain = ((CORBRecord*)pDrawArgs->pRow->GetRecord())->m_bMain;
  
		if(m_bRegion && nCol == 0)
		{
			pItemMetrics->clrBackground = RGB(200, 255, 200);
			pItemMetrics->pFont = &pDrawArgs->pControl->GetPaintManager()->m_fontBoldText;
		}
		else if(bMain)
			pItemMetrics->clrBackground = RGB(230, 230, 255);
	}

	void AddSearchData(CString sName, CString sBranchName, CString sOfficePhone, CString sTel, CString sCity)
	{
		m_sSearchData += sName + "%" + sBranchName + "%" + sOfficePhone+ "%" + sTel + "%" + sCity + "%";
	}

	CString m_sSearchData;
	BOOL m_bMain;
	BOOL m_bRegion;
	long m_nShareCode;
	CString m_sCity;
};

class COtherRegionBranchDlg : public CMyDialog
{
	DECLARE_DYNAMIC(COtherRegionBranchDlg)

public:
	COtherRegionBranchDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~COtherRegionBranchDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_OTHER_REGION_BRANCH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnEnChangeSearchEdit();

	void RefreshList();
	void InitRegionGroup();
	CString GetGroupRegion(CString sCity);

	CXTPListCtrl2 m_lstReport;

	CITY_MAP m_map;
	GROUP_MAP m_gpMap;
	
	CFlatEdit2 m_edtSearch;
};

