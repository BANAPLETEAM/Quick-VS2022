#pragma once
#include "afxwin.h"


typedef struct{
	long nFromCompany;
	long nFromRNo;
	long nToCompany;
	long nToRNo;
	CString strRName;
} ST_MOVE_RIDER;
// CMoveRiderNewDlg 대화 상자입니다.



class CMoveRiderRecord : public CXTPGridRecord
{
public:
	CMoveRiderRecord::CMoveRiderRecord(long nCompany, long nRNo, CString strRName);
	CMoveRiderRecord::~CMoveRiderRecord();

	class CMoveRiderDirtyCheckNumber : public CXTPGridRecordItemNumber
	{
	public:
		CMoveRiderDirtyCheckNumber(long nProcessRate) : CXTPGridRecordItemNumber(nProcessRate)
		{
		}
		
		virtual void OnEditChanged(XTP_REPORTRECORDITEM_ARGS* pItemArgs, LPCTSTR szText)
		{	
			long nValue = atoi(szText);
			SetValue(nValue);

			ST_MOVE_RIDER *st = m_pMoveRiderRecord->GetMoveRiderSturct();
			st->nToRNo = nValue;

			m_pMoveRiderRecord->SetValid(IsMoveRiderOk(st->nToCompany, st->nToRNo));			
		}

		CMoveRiderRecord *m_pMoveRiderRecord;
	};

public:
	ST_MOVE_RIDER* GetMoveRiderSturct(){return m_stMoveRider;};

	void SetCompany(long nCompany, CString strBranch)
	{
		m_stMoveRider->nToCompany = nCompany;
		((CXTPGridRecordItemText*)GetItem(4))->SetValue(strBranch);
		GetItem(4)->SetCaption(strBranch);
	}
	void SetRNo(long nRNo)
	{
		m_stMoveRider->nToRNo = nRNo;
		((CXTPGridRecordItemNumber*)(GetItem(5)))->SetValue(nRNo);
		GetItem(5)->SetCaption(::GetStringFromLong(nRNo));
	}
	void SetValid(CString strText)
	{
		((CXTPGridRecordItemText*)GetItem(7))->SetValue(strText);
		GetItem(7)->SetCaption(strText);
	}

private:
	ST_MOVE_RIDER *m_stMoveRider;
};


class CMoveRiderNewDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CMoveRiderNewDlg)

public:
	CMoveRiderNewDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMoveRiderNewDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MOVE_RIDER_NEW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CXTPListCtrl31 m_lstLeft;
	CXTPListCtrl50 m_lstRight;

	CComboBox m_cmbBranch;

	BOOL m_bDragMode;

	virtual BOOL OnInitDialog();
	long GetValidCount();
	void RefreshRiderList();
	void CheckFilterRight();
	void InsertRightList(long nCompany, long nRNo, CString strRName);
	BOOL CheckRightListLocal(long nCompany, long nRNo);
	afx_msg void OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/);
	afx_msg void OnBnClickedChangeBtn();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CFlatEdit2 m_edtRight;
	CFlatEdit2 m_edtLeft;
	afx_msg void OnEnChangeLeftEdit2();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg	void OnChangeBranch(UINT nFlag);
	afx_msg	void OnMakeNumber();
	afx_msg	void OnDeleteMoveRider();
	afx_msg void OnEnChangeRightEdit();
	afx_msg void OnEnChangeLeftEdit();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
