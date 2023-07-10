#pragma once

#include "poidata.h"
#include "POIDataNew.h"


class CConsignRecord : public CXTPGridRecord
{
public:
	class CConsignRecordItem : public CXTPGridRecordItem
	{
	public:
		CConsignRecordItem(UINT nValue)
		{
			m_nValue = nValue;
			GetEditOptions(NULL)->AddConstraint("고속버스", 0);
			GetEditOptions(NULL)->AddConstraint("시외버스", 1);
			GetEditOptions(NULL)->AddConstraint("KTX", 2);
			GetEditOptions(NULL)->AddConstraint("기차", 3);
			GetEditOptions(NULL)->m_bConstraintEdit = FALSE;
			GetEditOptions(NULL)->m_bAllowEdit = FALSE;
			GetEditOptions(NULL)->AddComboButton(TRUE);
		}

		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			CXTPGridRecordItemConstraint* pConstraint = GetEditOptions(NULL)->FindConstraint(m_nValue);
			//if(pConstraint == NULL || ((CMyRecord*)GetRecord())->m_bNoShareA)
			//{
			//	long nValue = -1;
			//	pConstraint = GetEditOptions(NULL)->FindConstraint(nValue);
			//}
			if (pConstraint == NULL)
				return "";
			//ASSERT(pConstraint);
			return pConstraint->m_strConstraint;
		}

		virtual void OnConstraintChanged(XTP_REPORTRECORDITEM_ARGS* pItemArgs, CXTPGridRecordItemConstraint* pConstraint)
		{
			m_nValue = (long)pConstraint->m_dwData;
		}

		BOOL GetValue()
		{
			return m_nValue;
		}

	protected:
		long m_nValue;
	};

	CConsignRecord(CString sTerminal, CString sKm, int nTranWay, CString sWayEtc, CString sDest, CString sCharge, CString sTel, CString sStart, CString sEnd, CString sInterval)
	{
		AddItem(new CXTPGridRecordItemText(sTerminal));
		AddItem(new CXTPGridRecordItemText(sKm));
		AddItem(new CConsignRecordItem(nTranWay));
		AddItem(new CXTPGridRecordItemText(sWayEtc));
		AddItem(new CXTPGridRecordItemText(sDest));
		AddItem(new CXTPGridRecordItemText(sCharge));
		AddItem(new CXTPGridRecordItemText(sTel));
		AddItem(new CXTPGridRecordItemText(sStart));
		AddItem(new CXTPGridRecordItemText(sEnd));
		AddItem(new CXTPGridRecordItemText(sInterval));
	}
};

// CConsignDlg 대화 상자입니다.

class CConsignDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CConsignDlg)

public:
	CConsignDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CConsignDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CONSIGN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edtDest;
	CString m_sDest;
	CEdit m_edtTerminal;
	CString m_sTerminal;
	CEdit m_edtEtc;
	CXTPListCtrl2 m_Data;
	afx_msg void OnBnClickedSendOk();
	afx_msg void OnBnClickedNewBtn();
	afx_msg void OnBnClickedModifyBtn();
	afx_msg void OnBnClickedCancel();

	void RefreshListArea();
	void RefreshListTerminal();
	CPOIUnit *m_pStartPoi;
	CPOIUnit *m_pDestPoi;
	virtual BOOL OnInitDialog();
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnReportItemChange(NMHDR * pNotifyStruct, LRESULT * result);
	
	
	long m_nCharge;
	
	long GetDistance(long nPOIID);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT nIDEvent);
};
