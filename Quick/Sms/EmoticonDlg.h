#pragma once


class CXTPEmoticonRecord : public CXTPGridRecord
{
public:

	CXTPEmoticonRecord::CXTPEmoticonRecord(long nCount)
	{
		for(int i=0; i<nCount; i++)
			AddItem(new CXTPGridRecordItemText(""));
	}

	//virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
};
// CEmoticonDlg 대화 상자입니다.

class CEmoticonDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CEmoticonDlg)

public:
	CEmoticonDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CEmoticonDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_EMOTICON_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

public:

	CWnd *m_pParent;

	long m_nEmoticonType;
	CXTPGridControl m_lstReport;

	long GetEmoticonType() {return m_nEmoticonType;}
	void ClearList();
	void RefreshList();
	long GetColSize();

	afx_msg void OnBnClickedEmoticon1Btn();
	afx_msg void OnBnClickedEmoticon2Btn();
	afx_msg void OnBnClickedEmoticon3Btn();
	afx_msg void OnBnClickedEmoticon4Btn();

	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
};
