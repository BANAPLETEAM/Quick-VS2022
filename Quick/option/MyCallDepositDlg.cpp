// WorkTimeDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "resource.h"
#include "MyCallDepositDlg.h"


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.


// COptionWorkTimeDlg 대화 상자
#define  MAX_COL 3
#define  MAX_ROW 15




CMyCallDepositDlg::CMyCallDepositDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CMyCallDepositDlg::IDD, pParent)	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nCompany = 0;
	m_bInitData = FALSE;
	

	
}

CMyCallDepositDlg::~CMyCallDepositDlg()
{
}

void CMyCallDepositDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	
	DDX_Control(pDX, IDC_CUSTOM1, m_ChargeList);
	


	DDX_Control(pDX, IDC_MAIN_EDIT, m_edtMain);
	DDX_Control(pDX, IDC_SUB_EDIT, m_edtSub);
	DDX_Control(pDX, IDC_MAIN_BUTTON, m_btnMain);
	DDX_Control(pDX, IDC_SUB_BUTTON, m_btnSub);
	DDX_Control(pDX, IDC_BRANCH_LIST, m_lstBranch);
}

BEGIN_MESSAGE_MAP(CMyCallDepositDlg, CMyDialog)
	
	ON_WM_PAINT()
	
	//ON_BN_CLICKED(IDC_TEST_BTN, OnBnClickedTestBtn)
	ON_BN_CLICKED(IDC_BRANCH_ALL_BTN2, OnBnClickedBranchAllBtn2)	
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_BN_CLICKED(IDC_ALL_DEL_BTN, OnBnClickedAllDelBtn)
	ON_BN_CLICKED(IDC_ROW_DEL_BTN, OnBnClickedRowDelBtn)	
	//ON_BN_CLICKED(IDC_ROW_ADD_BTN, OnBnClickedRowAddBtn)	
	ON_MESSAGE(WM_CHANGE_BRANCH_CODE, OnChangeBrachCode)

	
	ON_BN_CLICKED(IDC_BRANCH_BTN2, &CMyCallDepositDlg::OnBnClickedBranchBtn2)
	
END_MESSAGE_MAP()


// CMyCallDepositDlg 메시지 처리기

BOOL CMyCallDepositDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_cBranch.SetParent(this, TRUE);
	m_cBranch.InitData(&m_edtMain, &m_edtSub, &m_btnMain, &m_btnSub);

	m_lstBranch.SetMapData(&m_cBranch);
	
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	
	InitControl();
	m_bInitData = TRUE;
	RefreshList();
	
	return TRUE;  // 컨트롤에 대한 포커스를 설정하지 않을 경우 TRUE를 반환합니다.
}


// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면 
// 아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
// 프레임워크에서 이 작업을 자동으로 수행합니다.

void CMyCallDepositDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
		
	}
	else
	{
		CMyDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다. 
HCURSOR CMyCallDepositDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMyCallDepositDlg::RefreshList()
{
	m_ChargeList.DeleteAllItems();
	UpdateData();

	COleDateTime dt(COleDateTime::GetCurrentTime());;
	CMkRecordset pRs(m_pMkDb);	
	CMkCommand pCmd(m_pMkDb, "select_mycall_rider_deposit");	  	
	pCmd.AddParameter(m_cBranch.GetCompany());	
	if(!pRs.Execute(&pCmd))  return;	

	int nNum = 1;
	
	CMyCallRiderRecord *pRecord = NULL;
	for(int i = 1; i <= MAX_ROW; i++)
	{			
		long nStartValue = 0, nEndValue = 0, nAmount = 0, nCompany, nClass,nID,  nValueType;
		
		
		if( i <= pRs.GetRecordCount())
		{
			pRs.GetFieldValue("nID", nID);
			pRs.GetFieldValue("nCompany", nCompany);
			pRs.GetFieldValue("nValueType", nValueType);
			pRs.GetFieldValue("nClass", nClass);
			pRs.GetFieldValue("nNum", nNum);
			pRs.GetFieldValue("nStartValue", nStartValue);
			pRs.GetFieldValue("nEndValue", nEndValue);
			pRs.GetFieldValue("nAmount", nAmount);			

			m_ChargeList.InsertItem(i, LF->GetMyNumberFormat(nNum) );
			m_ChargeList.SetItemText(i, 1, LF->GetMyNumberFormat(nStartValue));
			m_ChargeList.SetItemText(i, 2, LF->GetMyNumberFormat(nEndValue ));
			m_ChargeList.SetItemText(i, 3, LF->GetMyNumberFormat(nAmount ));
			m_ChargeList.SetItemLong(i, nNum);
			m_ChargeList.SetItemLong2(i, nCompany);
			pRs.MoveNext();
		}
		else
		{
			m_ChargeList.InsertItem(i, LF->GetMyNumberFormat(nNum) );
			m_ChargeList.SetItemText(i, 1, "");
			m_ChargeList.SetItemText(i, 2, "");
			m_ChargeList.SetItemText(i, 3, "");
			m_ChargeList.SetItemLong(i, nNum);
			m_ChargeList.SetItemLong2(i, nCompany);
			nNum++;
		}
	}

	pRs.Close();
	m_ChargeList.Populate();
}


void CMyCallDepositDlg::InitControl()
{
	

	int nCol =0;
	
	CXTPGridColumn* pCol0 =  m_ChargeList.AddColumn(new CXTPGridColumn(0, _T("No"), 50, FALSE, XTP_GRID_NOICON, FALSE, TRUE));
	
	CXTPGridColumn* pCol1 =  m_ChargeList.AddColumn(new CXTPGridColumn(1, _T("시작"), 60, FALSE, XTP_GRID_NOICON, FALSE, TRUE));
	CXTPGridColumn* pCol2 =  m_ChargeList.AddColumn(new CXTPGridColumn(2, _T("종료"), 60, FALSE, XTP_GRID_NOICON, FALSE, TRUE));
	CXTPGridColumn* pCol3 =  m_ChargeList.AddColumn(new CXTPGridColumn(3, _T("금액"), 95, FALSE, XTP_GRID_NOICON, FALSE, TRUE));



	pCol0->SetAlignment(DT_CENTER); pCol0->SetEditable(FALSE);
	pCol1->SetAlignment(DT_RIGHT); pCol1->SetEditable(TRUE);
	pCol2->SetAlignment(DT_RIGHT); pCol2->SetEditable(TRUE);
	
	pCol3->SetAlignment(DT_RIGHT); pCol3->SetEditable(TRUE);
	
	

	m_ChargeList.AllowEdit(TRUE);
	m_ChargeList.GetReportHeader()->AllowColumnRemove(FALSE);
	m_ChargeList.GetReportHeader()->AllowColumnSort(FALSE);
	m_ChargeList.GetReportHeader()->AllowColumnReorder(FALSE);


	
	m_ChargeList.Populate();



}



void CMyCallDepositDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}

void CMyCallDepositDlg::OnBnClickedAllDelBtn()
{

	for(int i = 0; i <MAX_ROW; i++)
	{

		CXTPGridRow *pRow = m_ChargeList.GetRows()->GetAt(i);
		CMyCallRiderRecord *pRecord = (CMyCallRiderRecord *)pRow->GetRecord();
		pRecord->SetItemValue(1, "");
		pRecord->SetItemValue(2, "");
		pRecord->SetItemValue(3, "");
		
	}
	m_ChargeList.Populate();

}

void CMyCallDepositDlg::OnBnClickedRowDelBtn()
{
	for(int i =0; i < m_ChargeList.GetSelectedRows()->GetCount(); i++)
	{
		CXTPGridRow *pRow = m_ChargeList.GetSelectedRows()->GetAt(i);
		CMyCallRiderRecord *pRecord = (CMyCallRiderRecord *)pRow->GetRecord();
		pRecord->SetItemValue(1, "");
		pRecord->SetItemValue(2, "");
		pRecord->SetItemValue(3, "");
	
	}

	m_ChargeList.Populate();
}
//
//
//
//void CMyCallDepositDlg::OnBnClickedRowAddBtn()
//{
//	m_ChargeList.MyAddItem("");
//	m_ChargeList.MyAddItem("");
//	m_ChargeList.MyAddItem("");
//	m_ChargeList.MyAddItem("");
//	m_ChargeList.MyAddItem("");
//	m_ChargeList.MyAddItem("");
//	m_ChargeList.EndItem();
//	m_ChargeList.Populate();
//}

void CMyCallDepositDlg::OnBnClickedBranchBtn2()
{

	if(Save(m_cBranch.GetCompany(), FALSE))
	{
		MessageBox("한개의 지사에 적용 되었습니다", "확인", MB_ICONINFORMATION);
		//OnOK();
	}
}


void CMyCallDepositDlg::OnBnClickedBranchAllBtn2()
{

	CStringArray sCompanyArray;
	long nCount = m_lstBranch.GetCheckCount(sCompanyArray);

	CString sTemp = ""; sTemp.Format("[%d]개의 지사에 적용 하시겠습니까?", nCount);

	if(MessageBox(sTemp, "확인", MB_OKCANCEL) != IDOK)
		return;

	for(int i = 0; i < sCompanyArray.GetCount(); i++)
	{
		if(!Save(atoi(sCompanyArray.GetAt(i)), TRUE))
		{
			MessageBox("설정 저장중에 오류가 발생했습니다.\n재시도 하시기 바랍니다.", 
				"확인", MB_ICONINFORMATION);
			return;
		}
	}

	MessageBox("성공적으로 선택 지사에 적용되었습니다.", "설정변경", MB_ICONINFORMATION);
	OnOK();

}
BOOL CMyCallDepositDlg::Save(long nCompany, BOOL bAll)
{
	if( ExceptionCheckCharge() )
		return FALSE;

 // 건수, 평균 체크작업

	CString sStart = "", sEnd = "", sAmount = "", sAmountA = "", sAmountB = "", sAmountC = "", 
		sClass = "", sCount = "", sAverage = "", sMaxApply = ""; 
	BOOL bCount = FALSE , bAverage = FALSE, bMaxApply = FALSE;


	CString sNewExpireDay = ""; long nExpireDay = 0;
	COleDateTime dtNow(COleDateTime::GetCurrentTime()); COleDateTimeSpan dtSpan;
	dtSpan.SetDateTimeSpan(0,3,0,0);

	dtNow += dtSpan;
	UpdateData();

	

	
		for( int i = 0;  i < m_ChargeList.GetRecords()->GetCount(); i++)
		{
			bCount = bAverage = bMaxApply = FALSE;
			CMyCallRiderRecord *pRecord =   (CMyCallRiderRecord *)m_ChargeList.GetRecords()->GetAt(i);
			sStart +=		EmptyNulllValue(pRecord->GetItemValue(1)) + ",";
			sEnd +=			EmptyNulllValue(pRecord->GetItemValue(2)) + ",";
			sAmount +=	EmptyNulllValue(pRecord->GetItemValue(3)) + ",";

			sAmountA +=	EmptyNulllValue(pRecord->GetItemValue(4)) + ",";
			sAmountB +=	EmptyNulllValue(pRecord->GetItemValue(5)) + ",";
			sAmountC +=	EmptyNulllValue(pRecord->GetItemValue(6)) + ",";
			if(i == 0)
				sClass += "0,";
			else if(i == 1)
				sClass += "1,";
			else if(i == 2)
				sClass += "2,";


		}



	

	COleDateTime dt(COleDateTime::GetCurrentTime());
	CMkCommand pCmd(m_pMkDb, "update_mycall_rider_deposit");
	pCmd.AddParameter(nCompany);
	pCmd.AddParameter(sStart);
	pCmd.AddParameter(sEnd);
	pCmd.AddParameter(sAmount);
	
	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	pCmd.Execute();

	int nReturn = 0;
	pPar->GetValue(nReturn);

	if(nReturn == 0)
	{
		MessageBox("서버에 저장이 실패되었습니다. 다시시도 하여주세요", "확인", MB_ICONINFORMATION);
		return FALSE;
	}
	if(!bAll)
		MessageBox("저장되었습니다.", "확인", MB_ICONINFORMATION);
	return TRUE;
	
}

CString CMyCallDepositDlg::EmptyNulllValue(CString sValue)
{
	if(sValue.GetLength() <= 0)
		return "0";

	sValue.Replace(",", "");

	return sValue;
}

BOOL CMyCallDepositDlg::ExceptionColumnString(CString sRow , int nCol , CString sValue )
{

	try
	{	
		CString sExceptionString = "";
		long nValue;

		sValue.Replace(",", "");
		if(!LF->IsStringDigit(sValue))
		{
			sExceptionString.Format("%s행 %d열의 %s값이 숫자가 아닙니다.", sRow, nCol, sValue);
			throw sExceptionString;

		}

		nValue = LF->GetNoneCommaNumber(sValue);
		if(nCol >= 1 && nCol <= 2 && nValue >= 10000000)
		{
			throw "시작과 끝구간에 천만원 이상은 오류입니다.";
			
		}
		if(nCol > 2 && nCol < 7 && nValue >1000000 )
			throw "금액 구간에 백만원 이상은 오류입니다.";
	}
	catch (char* e)
	{
		MessageBox(e, "확인", MB_ICONINFORMATION);
		return TRUE;
	}
	catch (CString s)
	{
		MessageBox(s, "확인", MB_ICONINFORMATION);
		return TRUE;
	}


	return FALSE;

}

BOOL CMyCallDepositDlg::ExceptionRowString(CMyCallRiderRecord *pRecord ,  CString &sPreEndValue )
{

	try
	{	
		int nStartValue = 0, nEndValue = 0, nAmountValue = 0, nAmountValueA = 0, nAmountValueB = 0,nAmountValueC = 0;
		CString sValue = "",  sPreException  = "", sRowData = "";

		for(int nCol = 0; nCol <= MAX_COL; nCol++)
		{

			sValue = pRecord->GetItemValue(nCol);

			sRowData = pRecord->GetItemValue(0);
			if( ExceptionColumnString( sRowData, nCol, sValue ) )
				return TRUE;


			nStartValue = pRecord->GetItemValue(1).GetLength() <= 0 ? 0 :		LF->GetNoneCommaNumber(pRecord->GetItemValue(1));
			nEndValue = pRecord->GetItemValue(2).GetLength() <= 0 ? 0 :		LF->GetNoneCommaNumber(pRecord->GetItemValue(2));
			nAmountValue = pRecord->GetItemValue(3).GetLength() <= 0 ? 0 :	LF->GetNoneCommaNumber(pRecord->GetItemValue(3));
				


			if( (nCol == 1) && (nStartValue > 0 || nEndValue > 0 || nAmountValue > 0 
						|| nAmountValueA > 0 || nAmountValueB > 0 || nAmountValueC > 0 ) ) 
			{
				if(LF->GetNoneCommaNumber(sPreEndValue) >= LF->GetNoneCommaNumber(sValue) )
				{
					sPreException.Format("%s행 시작 부분이 이전행의 마지막 금액보다  더많아야 합니다.", sRowData );
					MessageBox(sPreException, "확인", MB_ICONINFORMATION	 );
					return TRUE;
				}

				sPreEndValue = pRecord->GetItemValue(2);
			}

			if(nCol == 3 )
			{
				if(nStartValue > 0 && nEndValue <= 0) // || nAmountValue <= 0 			|| nAmountValueA <= 0 || nAmountValueB <= 0 0 || nAmountValueC <= 0 0 ) ) 
				{
					sPreException.Format("%s행 종료끝값 또는  금액이 오류입니다.", sRowData);
					throw sPreException;
				}

				if(nEndValue > 0 && nStartValue <= 0 ) // || nAmountValue <= 0 			|| nAmountValueA < 0 || nAmountValueB < 0 || nAmountValueC < 0 ) ) 
				{
					sPreException.Format("%s행 시작끝값 또는 금액이 오류입니다.", sRowData);
					throw sPreException;
				}

				if(nStartValue > nEndValue ) 
				{
					sPreException.Format("%s행 시작값이 끝값 보다큽니다.", sRowData);
					throw sPreException;
				}

				if(
					(nAmountValue > 0 || nAmountValueA > 0 ||  nAmountValueB > 0 ||  nAmountValueC > 0 )
					&& (nEndValue <= 0 && nStartValue <= 0) ) 
				{
					sPreException.Format("%s행 시작및 종료금액 오류입니다.", sRowData);
					throw sPreException;
				}



			}
		}
	}
	catch (char* e)
	{
		MessageBox(e, "확인", MB_ICONINFORMATION);
		return TRUE;
	}
	catch (CString s)
	{
		MessageBox(s, "확인", MB_ICONINFORMATION);
		return TRUE;
	}



	return FALSE;

}

BOOL CMyCallDepositDlg::ExceptionCheckCharge()
{
	try
	{
		if(m_ChargeList.GetRecords()->GetCount() <= 0)
			throw "입력할 데이터가 없습니다.";

		CString sMsg = "", sPreEndValue = "0", sPreException = "";
		
		for(int i = 0; i < m_ChargeList.GetRecords()->GetCount(); i++)
		{
			CMyCallRiderRecord *pRecord = (CMyCallRiderRecord *)m_ChargeList.GetRecords()->GetAt(i);

			if(ExceptionRowString(pRecord, sPreEndValue) ) 
				return TRUE;		
			
			
			
		}

		CMyCallRiderRecord *pTotal = NULL, *pCustomer = NULL, *pStore = NULL;
		BOOL bTotal = FALSE, bCustomer = FALSE, bStore = FALSE;
		BOOL bTotalTermBlank = FALSE, bCustomerTotalBlank = FALSE, bStoreTotalBlank = FALSE;

		pTotal = (CMyCallRiderRecord *)m_ChargeList.GetRecords()->GetAt(0);
	
		// 구간안에 빈금액

		bTotalTermBlank = IsTermBlank(pTotal);
		
		if(bTotalTermBlank)
			return TRUE;


	
	
		return FALSE;
	}
	
	catch (char* e)
	{
		MessageBox(e, "확인", MB_ICONINFORMATION);
		return TRUE;
	}
	catch (CString s)
	{
		MessageBox(s, "확인", MB_ICONINFORMATION);
		return TRUE;
	}
	return TRUE;



}

BOOL CMyCallDepositDlg::IsTermBlank(CMyCallRiderRecord *pRecord)
{

	if(pRecord->GetRecords()->GetCount() <= 0)
		return TRUE;

	BOOL bContinueBlank = FALSE, bSaveBlank  = FALSE;
	for(int i =  m_ChargeList.GetRecords()->GetCount()-1; i >= 0; i--)
	{
		long nStartValue = 0, nEndValue = 0, nAmountValue = 0;
		CMyCallRiderRecord *pChildRecord = (CMyCallRiderRecord *)m_ChargeList.GetRecords()->GetAt(i);
		nStartValue =		pChildRecord->GetItemValue(1).GetLength() <= 0 ? 0 : LF->GetNoneCommaNumber(pChildRecord->GetItemValue(1));
		nEndValue =		pChildRecord->GetItemValue(2).GetLength() <= 0 ? 0 : LF->GetNoneCommaNumber(pChildRecord->GetItemValue(2));
		nAmountValue =	pChildRecord->GetItemValue(3).GetLength() <= 0 ? 0 : LF->GetNoneCommaNumber(pChildRecord->GetItemValue(3));
	

		if(nStartValue > 0 || nEndValue > 0 ) // || nAmountValue > 0 )
			if(!bSaveBlank)
				bSaveBlank = TRUE;
			
			
		if(bSaveBlank && nStartValue <= 0 && nEndValue <= 0) // && nAmountValue <= 0 )
		{
			MessageBox("중간에 빈행이 있습니다 확인하세요", "확인",  MB_ICONINFORMATION);
			return TRUE;
		}
	}

	if(bSaveBlank)
	{
		long nStartValue = 0, nEndValue = 0, nAmountValue = 0;
		
		nStartValue =		pRecord->GetItemValue(1).GetLength() <= 0 ? 0 : LF->GetNoneCommaNumber(pRecord->GetItemValue(1));
		nEndValue =		pRecord->GetItemValue(2).GetLength() <= 0 ? 0 : LF->GetNoneCommaNumber(pRecord->GetItemValue(2));
		nAmountValue =	pRecord->GetItemValue(3).GetLength() <= 0 ? 0 : LF->GetNoneCommaNumber(pRecord->GetItemValue(3));

		if(nStartValue <= 0 && nEndValue <= 0 ) //&& nAmountValue <= 0 )
		{
			MessageBox("맨앞열에 빈칸이 있습니다." ,"확인", MB_ICONINFORMATION);
			return TRUE;
		}
	}
	return FALSE;

}
//
//BOOL CMyCallDepositDlg::IsTypeData(CMyCallRiderRecord *pRecord)
//{
//
//	long nStartValue = 0, nEndValue = 0, nAmountValue = 0;
//
//	nStartValue =		pRecord->GetItemValue(1).GetLength() <= 0 ? 0 : LF->GetNoneCommaNumber(pRecord->GetItemValue(1));
//	nEndValue =		pRecord->GetItemValue(2).GetLength() <= 0 ? 0 : LF->GetNoneCommaNumber(pRecord->GetItemValue(2));
//	nAmountValue = pRecord->GetItemValue(3).GetLength() <= 0 ? 0 : LF->GetNoneCommaNumber(pRecord->GetItemValue(3));
//
//	if(nStartValue > 0 || nEndValue > 0) // || nAmountValue > 0)
//		return TRUE;
//
//	if(pRecord->GetChilds()->GetCount() > 0)
//	{
//		for(int i = 0; i < pRecord->GetChilds()->GetCount(); i++)
//		{
//			CMyCallRiderRecord *pChildRecord = (CMyCallRiderRecord *)pRecord->GetChilds()->GetAt(i);
//			BOOL bIsData = IsTypeData(pChildRecord);
//			if(bIsData)
//				return TRUE;
//		}
//	}
//	return FALSE;
//
//
//}

LONG CMyCallDepositDlg::OnChangeBrachCode(WPARAM wParam, LPARAM lParam)
{	
	if(m_bInitData )
		RefreshList();
	return 0;
}