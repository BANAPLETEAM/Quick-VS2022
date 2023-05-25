#pragma once

class CBranchSel;

class CXTPListBranch : public CXTPListCtrl2
{
public:
	//by mksong (2010-06-07 오후 9:08)
	//MainBranchDlg에서 동시 사용하기 위해서, m_bItemLongHasBranchInfo 파라메터 추가함
	//MainBrnachDlg의 SetItemLong 사용중임, 주의요망

	void SetItemLongHasBranchInfo(BOOL bHas = TRUE)
	{
		m_bItemLongHasBranchInfo = bHas;
	}

	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{
		CXTPListCtrl2::GetItemMetrics(pDrawArgs, pItemMetrics);

		int nCol = pDrawArgs->pColumn->GetItemIndex();
		int nRow = pDrawArgs->pRow->GetIndex();

		CBranchInfo* pBranchInfo = (CBranchInfo*)(m_bItemLongHasBranchInfo ? GetItemLong(nRow) : GetItemData(nRow));
		if(pBranchInfo)
		{
			if(pBranchInfo->nRcpTextColor == pBranchInfo->nRcpColor)
			{
				pBranchInfo->nRcpColor = RGB(255 -GetRValue(pBranchInfo->nRcpColor), 
					255 - GetGValue(pBranchInfo->nRcpColor), 
					255 - GetBValue(pBranchInfo->nRcpColor));
			}

			pItemMetrics->clrForeground = RGB(GetRValue(pBranchInfo->nRcpTextColor), GetGValue(pBranchInfo->nRcpTextColor), GetBValue(pBranchInfo->nRcpTextColor));
			pItemMetrics->clrBackground = RGB(GetRValue(pBranchInfo->nRcpColor), GetGValue(pBranchInfo->nRcpColor), GetBValue(pBranchInfo->nRcpColor));
		}
	}

protected:
	BOOL m_bItemLongHasBranchInfo;
};

class CBranchSubListDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CBranchSubListDlg)

public:
	CBranchSubListDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CBranchSubListDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_BRANCH_SUB_LIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CXTPListBranch m_lst;
	CBranchSel *m_pBranchSel;
	virtual BOOL OnInitDialog();
	void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedCloseBtn();
	CButton m_btnClose;
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};
