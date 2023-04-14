// MsgPowerDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MsgPowerDlg.h"
#include "MyReportPaintManager.h"

// CMsgPowerDlg 대화 상자입니다.


class CPowerRecord : public CXTPGridRecord
{
protected:
	class CPowerRecordItemLong : public CXTPGridRecordItem
	{
	public:
		CPowerRecordItemLong(UINT nValue)
		{
			m_nValue = nValue;
			GetEditOptions(NULL)->AddConstraint(_T("전체공유회사 보이기"), 0);
			GetEditOptions(NULL)->AddConstraint(_T("1차채널내에서 보이기"), 1);
			GetEditOptions(NULL)->AddConstraint(_T("지사내에서 보이기"), 2);
			GetEditOptions(NULL)->AddConstraint(_T("매니저에게만 보이기"), 3);
			GetEditOptions(NULL)->m_bConstraintEdit = FALSE;
			GetEditOptions(NULL)->m_bAllowEdit = FALSE;		
			GetEditOptions(NULL)->AddComboButton();
		}

		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			CXTPGridRecordItemConstraint* pConstraint = GetEditOptions(NULL)->FindConstraint(m_nValue);
			ASSERT(pConstraint);
			return pConstraint->m_strConstraint;
		}

		void OnConstraintChanged(XTP_REPORTRECORDITEM_ARGS* /*pItemArgs*/, CXTPGridRecordItemConstraint* pConstraint)
		{
			m_nValue = (BOOL)pConstraint->m_dwData;
			((CPowerRecord*)GetRecord())->SetDirtyFlag();
		}
		BOOL GetValue()
		{
			return m_nValue;
		}
	protected:
		BOOL m_nValue;
	};


	class CManagerRecordItemLong : public CXTPGridRecordItem
	{
	public:
		CManagerRecordItemLong(UINT nValue)
		{
			m_nValue = nValue;
			GetEditOptions(NULL)->AddConstraint(_T("일반"), 0);
			GetEditOptions(NULL)->AddConstraint(_T("매니저"), 1);
			GetEditOptions(NULL)->m_bConstraintEdit = FALSE;
			GetEditOptions(NULL)->m_bAllowEdit = FALSE;		
			GetEditOptions(NULL)->AddComboButton();
		}

		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			CXTPGridRecordItemConstraint* pConstraint = GetEditOptions(NULL)->FindConstraint(m_nValue);
			ASSERT(pConstraint);
			return pConstraint->m_strConstraint;
		}

		void OnConstraintChanged(XTP_REPORTRECORDITEM_ARGS* /*pItemArgs*/, CXTPGridRecordItemConstraint* pConstraint)
		{
			m_nValue = (BOOL)pConstraint->m_dwData;
			RefreshIconIndex();
			((CPowerRecord*)GetRecord())->SetDirtyFlag();
		}
		BOOL GetValue()
		{
			return m_nValue;
		}

		void RefreshIconIndex()
		{
			if(m_nValue == 0)
				((CPowerRecord*)GetRecord())->GetItem(0)->SetIconIndex(0);
			else
				((CPowerRecord*)GetRecord())->GetItem(0)->SetIconIndex(3);
		}
		
		protected:
			BOOL m_nValue;
	};

	class CTakeRecordItemLong : public CXTPGridRecordItem
	{
	public: 
		CTakeRecordItemLong(UINT nValue)
		{ 
			m_nValue = nValue;
			GetEditOptions(NULL)->AddConstraint(_T("X"), 0);
			GetEditOptions(NULL)->AddConstraint(_T("ㅇ"), 1);
			GetEditOptions(NULL)->m_bConstraintEdit = FALSE;
			GetEditOptions(NULL)->m_bAllowEdit = FALSE;		
			GetEditOptions(NULL)->AddComboButton();
		}

		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			CXTPGridRecordItemConstraint* pConstraint = GetEditOptions(NULL)->FindConstraint(m_nValue);
			ASSERT(pConstraint);
			return pConstraint->m_strConstraint;
		}

		void OnConstraintChanged(XTP_REPORTRECORDITEM_ARGS* /*pItemArgs*/, CXTPGridRecordItemConstraint* pConstraint)
		{
			m_nValue = (BOOL)pConstraint->m_dwData;
			((CPowerRecord*)GetRecord())->SetDirtyFlag();
		}
		BOOL GetValue()
		{
			return m_nValue;
		}
	protected:
		BOOL m_nValue;
	};


	class CNoneVisibleRecordItemLong : public CXTPGridRecordItem
	{
	public:
		CNoneVisibleRecordItemLong(UINT nValue)
		{
			m_nValue = nValue;
			GetEditOptions(NULL)->AddConstraint(_T("표시함"), 0);
			GetEditOptions(NULL)->AddConstraint(_T("표시안함"), 1);
			GetEditOptions(NULL)->m_bConstraintEdit = FALSE;
			GetEditOptions(NULL)->m_bAllowEdit = FALSE;		
			GetEditOptions(NULL)->AddComboButton();
		}

		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			CXTPGridRecordItemConstraint* pConstraint = GetEditOptions(NULL)->FindConstraint(m_nValue);
			ASSERT(pConstraint);
			return pConstraint->m_strConstraint;
		}

		void OnConstraintChanged(XTP_REPORTRECORDITEM_ARGS* /*pItemArgs*/, CXTPGridRecordItemConstraint* pConstraint)
		{
			m_nValue = (BOOL)pConstraint->m_dwData;
			((CPowerRecord*)GetRecord())->SetDirtyFlag();
		}
		BOOL GetValue()
		{
			return m_nValue;
		}


	protected:
		BOOL m_nValue;
	};

	class CDisplayNameRecordItemText : public CXTPGridRecordItemText
	{
	public:

		CDisplayNameRecordItemText(CString strDummy):CXTPGridRecordItemText(strDummy)
		{
		}	

		virtual void OnEditChanged(XTP_REPORTRECORDITEM_ARGS* /*pItemArgs*/, LPCTSTR szText) 
		{
			((CPowerRecord*)GetRecord())->SetDirtyFlag();
			m_strText = szText;
		}


	};



public:
	CPowerRecord(long nCompany, long nWNo, CString strBranchName, CString strName, CString strID, 
				long nPowerType, BOOL bManager, BOOL bTakeChargeRequest,
				BOOL bNoneVisible, CString strDisplayName)
	{
		m_nCompany = nCompany;
		m_nWNo = nWNo;
		m_bDirtyFlag = FALSE;
		AddItem(new CXTPGridRecordItemText(strBranchName));
		AddItem(new CXTPGridRecordItemNumber(nWNo));
		AddItem(new CXTPGridRecordItemText(strName));
		AddItem(new CXTPGridRecordItemText(strID));
		CXTPGridRecordItem* pItem = AddItem(new CPowerRecordItemLong(nPowerType));
		pItem->SetItemData(nPowerType);

		pItem = AddItem(new CManagerRecordItemLong(bManager));
		pItem->SetItemData(bManager);

		((CManagerRecordItemLong*)GetItem(5))->RefreshIconIndex();

		pItem = AddItem(new CTakeRecordItemLong(bTakeChargeRequest));
		pItem->SetItemData(bTakeChargeRequest);

		pItem = AddItem(new CNoneVisibleRecordItemLong(bNoneVisible));
		pItem->SetItemData(bNoneVisible);

		pItem = AddItem(new CDisplayNameRecordItemText(strDisplayName));
		pItem->SetEditable(TRUE);
	}

	virtual void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
	{
		int nCol = pDrawArgs->pColumn->GetIndex();
		if(nCol == 4)
		{
			switch(GetPowerType())
			{
				case 0:
					pItemMetrics->clrBackground = RGB(0, 200, 0);
					pItemMetrics->clrForeground= RGB(255, 255, 255);
					break;

				case 1:
					pItemMetrics->clrBackground = RGB(100, 200, 100);
					break;

				case 2:
					pItemMetrics->clrBackground = RGB(150, 200, 150);
					break;

				default:
					pItemMetrics->clrBackground = RGB(230, 255, 230);
					break;
			}
		}
		else if(nCol == 5)
		{
			if(GetManagerType())
			{
				pItemMetrics->clrBackground = RGB(200, 200, 255);
			}
		}
	}



	BOOL GetDirtyFlag() { return m_bDirtyFlag; }
	void SetDirtyFlag() { m_bDirtyFlag = TRUE;}
	long GetPowerType() { return ((CPowerRecordItemLong*)GetItem(4))->GetValue(); }
	long GetManagerType() { return ((CManagerRecordItemLong*)GetItem(5))->GetValue(); }
	long GetTakeType() { return ((CTakeRecordItemLong*)GetItem(6))->GetValue(); }
	BOOL GetNoneVisible() { return ((CNoneVisibleRecordItemLong*)GetItem(7))->GetValue(); }
	CString GetDisplayName() { return ((CDisplayNameRecordItemText*)GetItem(8))->GetValue(); }

protected:
	BOOL m_bDirtyFlag;

public:
	long m_nCompany;
	long m_nWNo;

/*
	static BOOL GetValue(XTP_NM_REPORTRECORDITEM* pItemNotify)
	{
		return ((CPropertyItemBool*)pItemNotify->pItem)->GetValue();
	}
*/
};


IMPLEMENT_DYNAMIC(CMsgPowerDlg, CMyResizeDialog)

CMsgPowerDlg::CMsgPowerDlg(CWnd* pParent /*=NULL*/)
	: CMyResizeDialog(CMsgPowerDlg::IDD, pParent)
{
	m_pDB = NULL;
}

CMsgPowerDlg::~CMsgPowerDlg()
{
}

void CMsgPowerDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORTCTRL, m_wndReportCtrl);
}


BEGIN_MESSAGE_MAP(CMsgPowerDlg, CMyResizeDialog)
	ON_BN_CLICKED(IDC_OK_BTN, &CMsgPowerDlg::OnBnClickedOkBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, &CMsgPowerDlg::OnBnClickedCancelBtn)
END_MESSAGE_MAP()


// CMsgPowerDlg 메시지 처리기입니다.
BOOL CMsgPowerDlg::OnInitDialog()
{
	CMyResizeDialog::OnInitDialog();

	SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	CBitmap bmp;
	VERIFY(m_ilIcons.Create(16,16, ILC_COLOR24|ILC_MASK, 0, 1));
	VERIFY(bmp.LoadBitmap(IDB_MSN_STATUS));
	m_ilIcons.Add(&bmp, RGB(255, 0, 255));

	m_wndReportCtrl.SetImageList(&m_ilIcons);
	///m_wndReportCtrl.ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP); //by mksong 2010-10-14
	m_wndReportCtrl.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReportCtrl.SetPaintManager(new CMyReportPaintManager());
	m_wndReportCtrl.SetTreeIndent(10);
	m_wndReportCtrl.SetGridColor(RGB(222, 222, 222));
	m_wndReportCtrl.AllowEdit(TRUE);

	CXTPGridColumn *p1 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(0, _T("지사명"), 80, FALSE));
	p1->SetEditable(FALSE);
	p1 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(1, _T("사번"), 30));
	p1->SetEditable(FALSE);
	p1 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(2, _T("이름"), 70));
	p1->SetEditable(FALSE);
	p1 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(3, _T("ID"), 50));
	p1->SetEditable(FALSE);
	p1 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(4, _T("권한"), 100));
	p1->SetEditable(TRUE);
	p1 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(5, _T("타입"), 30));
	p1->SetEditable(TRUE);
	p1 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(6, _T("요금문의받음"), 60));
	p1->SetEditable(TRUE);
	p1 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(7, _T("인터콜상담"), 70));
	p1->SetEditable(TRUE);
	p1 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(8, _T("인터콜표시명"), 150));
	p1->SetEditable(TRUE);

	// Set control resizing.
	SetResize(IDC_REPORTCTRL, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_OK_BTN, SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_CANCEL_BTN, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);

	// Load window placement
	LoadPlacement(_T("CMsgPowerDlg"));

	RefreshList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMsgPowerDlg::RefreshList()
{
	CMkRecordset pRs(m_pDB);
	CMkCommand pCmd(m_pDB, "select_messenger_power_1");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), 1);
 
	m_wndReportCtrl.GetRecords()->RemoveAll();
	UINT nPreMode = m_pDB->AsyncSelect(FD_CLOSE, TRUE);
	BOOL bRet = pRs.Execute(&pCmd);
	m_pDB->AsyncSelect(nPreMode, TRUE);
	if(bRet) {
		for(int i = 0 ; i < pRs.GetRecordCount(); i++)
		{		
			long nCompany, nMNo, nPowerType;
			CString strID, strName, strBranchName;
			BOOL bManager, bTakeChargeRequest;
			BOOL bNoneVisible;
			CString strDisplayName;

			pRs.GetFieldValue("lCode", nCompany);
			pRs.GetFieldValue("nMNo", nMNo);
			pRs.GetFieldValue("sName", strName);
			pRs.GetFieldValue("sBranchName", strBranchName);
			pRs.GetFieldValue("sID", strID);
			pRs.GetFieldValue("nPowerType", nPowerType);
			pRs.GetFieldValue("bManager", bManager);
			pRs.GetFieldValue("bTakeChargeRequest", bTakeChargeRequest);
			pRs.GetFieldValue("bIntercallNoneVisible", bNoneVisible);
			pRs.GetFieldValue("sIntercallDisplayName", strDisplayName);
			
			if(bManager) bManager = TRUE;
			else bManager = FALSE;

			m_wndReportCtrl.AddRecord(new CPowerRecord(nCompany, nMNo, strBranchName, 
						strName, strID, nPowerType, bManager, bTakeChargeRequest, 
						bNoneVisible, strDisplayName));

			pRs.MoveNext();
		}

		m_wndReportCtrl.Populate();
	}

	pRs.Close();

}


void CMsgPowerDlg::OnBnClickedOkBtn()
{
	SaveList();
}

void CMsgPowerDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}

void CMsgPowerDlg::SaveList()
{
	for(int i = 0; i < m_wndReportCtrl.GetRecords()->GetCount(); i++)
	{
		CPowerRecord *pPower = (CPowerRecord*)m_wndReportCtrl.GetRecords()->GetAt(i);
		if(pPower->GetDirtyFlag())
		{
			UINT nPreMode = m_pDB->AsyncSelect(FD_CLOSE, TRUE);
			CMkCommand pCmd(m_pDB, "update_messenger_power3");
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), pPower->m_nCompany);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), pPower->m_nWNo);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), pPower->GetPowerType());
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), pPower->GetManagerType());
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), pPower->GetTakeType());
			pCmd.AddParameter(typeBool, typeInput, sizeof(int), pPower->GetNoneVisible());
			pCmd.AddParameter(typeString, typeInput, pPower->GetDisplayName().GetLength(), pPower->GetDisplayName());
			BOOL bRet = pCmd.Execute();
			m_pDB->AsyncSelect(nPreMode, TRUE);
			if(!bRet)
			{
				MessageBox("저장중에 오류가 발생했습니다.\n다시시도하시기 바랍니다.", "에러", MB_ICONERROR);
				RefreshList();
				return;
			}
		}
	}

	RefreshList();
	MessageBox("저장 되었습니다.", "확인", MB_OK);

}
