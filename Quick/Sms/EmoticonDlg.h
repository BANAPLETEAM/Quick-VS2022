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
// CEmoticonDlg ��ȭ �����Դϴ�.

class CEmoticonDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CEmoticonDlg)

public:
	CEmoticonDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CEmoticonDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_EMOTICON_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
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
