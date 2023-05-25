#pragma once
#include "DataBox.h"

// CTestDlg 대화 상자입니다.


class DataClass
{
public:
	int m_nItem1;
	int m_nItem2;
	CString m_s1;
	COleDateTime m_dt1;

};

typedef map<long , DataClass> MyData2;


class CK2Record :public CXTPGridRecord
{

public:
	 CK2Record();

	int m_nItem1;
	int m_nItem2;
	CString m_s1;
	COleDateTime m_dt1;
	void SetMyRecord();	
	void SetMyRecord2(int nItem);
	int GetMyRecord2(){return m_nItem1;}
	
	MyData2 data;


};

typedef map<long , CK2Record*> MyData;



class CVirtualDataBox :public CDataBox
{
public:
	CK2Record *m_pRecord3;

	void GetItemMetrics (XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{
		int nRow = pDrawArgs->pRow->GetIndex();
		int nCount = pDrawArgs->pControl->GetRows()->GetCount();
		int nCol = pDrawArgs->pColumn->GetIndex();
		int nItemCol = pDrawArgs->pColumn->GetItemIndex();

	/*	char buffer[20];
		if(nCol == 0 )
			pItemMetrics->strText = ltoa(m_pRecord3->data[nRow].m_nItem1 , buffer,10);
		else if(nCol == 1)
			pItemMetrics->strText = ltoa(m_pRecord3->data[nRow].m_nItem2 , buffer,10);
		else if(nCol == 1)
			pItemMetrics->strText = m_pRecord3->data[nRow].m_s1;*/
		CXTPGridRecord *pRecord = pDrawArgs->pRow->GetRecord();
		pRecord = m_Record[nRow];
		
		CXTPGridRecordItem *pSItem = pRecord->GetItem(nCol);
		pDrawArgs->pItem = pSItem;

		//pDrawArgs->pItem
	}
	MyData m_Record;
	void SetRecord(MyData &data){ m_Record = data;}
};


class CTestDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CTestDlg)

public:
	CTestDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTestDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TEST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CVirtualDataBox m_data;
	MyData m_Record;
	MyData m_Record2;	
	MyData *m_pRecord4;	

	CK2Record *m_pRecord3;
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClicked65535();
};
