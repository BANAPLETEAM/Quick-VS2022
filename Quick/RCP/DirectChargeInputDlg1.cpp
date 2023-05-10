// DirectChargeInputDlg1.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "DirectChargeInputDlg1.h"

#define  ID_CHARGE_REINIT 1001

// CDirectChargeInputDlg1 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDirectChargeInputDlg1, CMyDialog)

CDirectChargeInputDlg1::CDirectChargeInputDlg1(CWnd* pParent /*=NULL*/)
	: CMyDialog(CDirectChargeInputDlg1::IDD, pParent)
{
	m_nStartDongID = 0;
	m_nDestDongID = 0;
	m_nGNo = 0;
	m_nCNo = 0;

	m_pStartPoi = NULL;
	m_pDestPoi = NULL;
}

CDirectChargeInputDlg1::~CDirectChargeInputDlg1()
{
}

void CDirectChargeInputDlg1::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHARGE_LIST, m_lstCharge);
	DDX_Control(pDX, IDC_CHARGE_GNO_LIST, m_lstChargeGNo);
	DDX_Control(pDX, IDC_CHARGE_CNO_LIST, m_lstChargeCNo);
	DDX_Control(pDX, IDC_TWO_WAY_CHECK, m_chkTwoWay);
	DDX_Control(pDX, IDC_TWO_WAY_GNO_CHECK, m_chkTwoWayGNo);
	DDX_Control(pDX, IDC_TWO_WAY_CNO_CHECK, m_chkTwoWayCNo);
}


BEGIN_MESSAGE_MAP(CDirectChargeInputDlg1, CMyDialog)
	ON_BN_CLICKED(IDC_SAVE_BTN, &CDirectChargeInputDlg1::OnBnClickedSaveBtn)
	ON_BN_CLICKED(IDC_SAVE_GNO_BTN, &CDirectChargeInputDlg1::OnBnClickedSaveGnoBtn)
	ON_BN_CLICKED(IDC_SAVE_CNO_BTN, &CDirectChargeInputDlg1::OnBnClickedSaveCnoBtn)
	ON_BN_CLICKED(IDC_HTYPE_MODIFY_BTN, &CDirectChargeInputDlg1::OnBnClickedHtypeModifyBtn)
END_MESSAGE_MAP()

#define COL_AUTO 1
#define COL_DAMA 2
#define COL_RABO 3
#define COL_BAN 4
#define COL_TRUCK 5
#define COL_SUBWAY 6

// CDirectChargeInputDlg1 메시지 처리기입니다.

BOOL CDirectChargeInputDlg1::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CXTPGridColumn *pCharge0 = m_lstCharge.InsertColumnReturn(0, "타입", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pCharge1 = m_lstCharge.InsertColumnReturn(COL_AUTO, "오토", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pCharge2 = m_lstCharge.InsertColumnReturn(COL_DAMA, "다마", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pCharge3 = m_lstCharge.InsertColumnReturn(COL_RABO, "라보", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pCharge4 = m_lstCharge.InsertColumnReturn(COL_BAN, "밴", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pCharge5 = m_lstCharge.InsertColumnReturn(COL_TRUCK, "트럭", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pCharge6 = m_lstCharge.InsertColumnReturn(COL_SUBWAY, "지하철", LVCFMT_RIGHT, 60);

	pCharge0->GetEditOptions()->m_bAllowEdit = FALSE;
	pCharge1->GetEditOptions()->m_bAllowEdit = TRUE;
	pCharge2->GetEditOptions()->m_bAllowEdit = TRUE;
	pCharge3->GetEditOptions()->m_bAllowEdit = TRUE;
	pCharge4->GetEditOptions()->m_bAllowEdit = TRUE;
	pCharge5->GetEditOptions()->m_bAllowEdit = TRUE;
	pCharge6->GetEditOptions()->m_bAllowEdit = TRUE; 

	m_lstCharge.AllowEdit(TRUE);
	m_lstCharge.Populate();

	CXTPGridColumn *pChargeGNo0 = m_lstChargeGNo.InsertColumnReturn(0, "타입", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeGNo1 = m_lstChargeGNo.InsertColumnReturn(1, "오토(고객요금)", LVCFMT_RIGHT, 90);
	CXTPGridColumn *pChargeGNo2 = m_lstChargeGNo.InsertColumnReturn(2, "기사요금", LVCFMT_RIGHT, 55);
	CXTPGridColumn *pChargeGNo3 = m_lstChargeGNo.InsertColumnReturn(3, "할인", LVCFMT_RIGHT, 45);
	CXTPGridColumn *pChargeGNo4 = m_lstChargeGNo.InsertColumnReturn(4, "다마(고객요금)", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeGNo5 = m_lstChargeGNo.InsertColumnReturn(5, "기사요금", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeGNo6 = m_lstChargeGNo.InsertColumnReturn(6, "할인", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeGNo7 = m_lstChargeGNo.InsertColumnReturn(7, "라보(고객요금)", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeGNo8 = m_lstChargeGNo.InsertColumnReturn(8, "기사요금", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeGNo9 = m_lstChargeGNo.InsertColumnReturn(9, "할인", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeGNo10 = m_lstChargeGNo.InsertColumnReturn(10, "밴(고객요금)", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeGNo11 = m_lstChargeGNo.InsertColumnReturn(11, "기사요금", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeGNo12 = m_lstChargeGNo.InsertColumnReturn(12, "할인", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeGNo13 = m_lstChargeGNo.InsertColumnReturn(13, "트럭(고객요금)", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeGNo14 = m_lstChargeGNo.InsertColumnReturn(14, "기사요금", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeGNo15 = m_lstChargeGNo.InsertColumnReturn(15, "할인", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeGNo16 = m_lstChargeGNo.InsertColumnReturn(16, "지하철(고객요금)", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeGNo17 = m_lstChargeGNo.InsertColumnReturn(17, "기사요금", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeGNo18 = m_lstChargeGNo.InsertColumnReturn(18, "할인", LVCFMT_RIGHT, 60);

	pChargeGNo0->GetEditOptions()->m_bAllowEdit = FALSE;
	pChargeGNo1->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeGNo2->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeGNo3->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeGNo4->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeGNo5->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeGNo6->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeGNo7->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeGNo8->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeGNo9->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeGNo10->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeGNo11->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeGNo12->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeGNo13->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeGNo14->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeGNo15->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeGNo16->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeGNo17->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeGNo18->GetEditOptions()->m_bAllowEdit = TRUE;

	m_lstChargeGNo.AllowEdit(TRUE); 
	m_lstChargeGNo.Populate();
 
	CXTPGridColumn *pChargeCNo0 = m_lstChargeCNo.InsertColumnReturn(0, "오토(고객요금)", LVCFMT_RIGHT, 90);
	CXTPGridColumn *pChargeCNo1 = m_lstChargeCNo.InsertColumnReturn(1, "기사요금", LVCFMT_RIGHT, 55);
	CXTPGridColumn *pChargeCNo2 = m_lstChargeCNo.InsertColumnReturn(2, "할인", LVCFMT_RIGHT, 45);
	CXTPGridColumn *pChargeCNo3 = m_lstChargeCNo.InsertColumnReturn(3, "다마(고객요금)", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeCNo4 = m_lstChargeCNo.InsertColumnReturn(4, "기사요금", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeCNo5 = m_lstChargeCNo.InsertColumnReturn(5, "할인", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeCNo6 = m_lstChargeCNo.InsertColumnReturn(6, "라보(고객요금)", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeCNo7 = m_lstChargeCNo.InsertColumnReturn(7, "기사요금", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeCNo8 = m_lstChargeCNo.InsertColumnReturn(8, "할인", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeCNo9 = m_lstChargeCNo.InsertColumnReturn(9, "밴(고객요금)", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeCNo10 = m_lstChargeCNo.InsertColumnReturn(10, "기사요금", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeCNo11 = m_lstChargeCNo.InsertColumnReturn(11, "할인", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeCNo12 = m_lstChargeCNo.InsertColumnReturn(12, "트럭(고객요금)", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeCNo13 = m_lstChargeCNo.InsertColumnReturn(13, "기사요금", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeCNo14 = m_lstChargeCNo.InsertColumnReturn(14, "할인", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeCNo15 = m_lstChargeCNo.InsertColumnReturn(15, "지하철(고객요금)", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeCNo16 = m_lstChargeCNo.InsertColumnReturn(16, "기사요금", LVCFMT_RIGHT, 60);
	CXTPGridColumn *pChargeCNo17 = m_lstChargeCNo.InsertColumnReturn(17, "할인", LVCFMT_RIGHT, 60);

	pChargeCNo0->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeCNo1->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeCNo2->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeCNo3->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeCNo4->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeCNo5->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeCNo6->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeCNo7->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeCNo8->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeCNo9->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeCNo10->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeCNo11->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeCNo12->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeCNo13->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeCNo14->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeCNo15->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeCNo16->GetEditOptions()->m_bAllowEdit = TRUE;
	pChargeCNo17->GetEditOptions()->m_bAllowEdit = TRUE;

	m_lstChargeCNo.AllowEdit(TRUE);
	m_lstChargeCNo.Populate();

	m_nStartDongID = GetExceptionID(m_pStartPoi);
	m_nDestDongID = GetExceptionID(m_pDestPoi);


	RefreshChargeList();
	RefreshChargeGNoList();
	RefreshChargeCNoList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDirectChargeInputDlg1::SetRecordText(CXTPGridRecord *pRecord, long nCol, CString strItem)
{
	pRecord->GetItem(nCol)->SetCaption(strItem);
}

void CDirectChargeInputDlg1::SetRecordText(CXTPGridRecord *pRecord, long nCol, long nItem)
{
	CXTPGridRecordItemText *pItem = (CXTPGridRecordItemText*)pRecord->GetItem(nCol);
	CString strItem = ::RemoveZero(::GetMyNumberFormat(nItem));
 
	pItem->SetValue(strItem);
	//pItem->SetCaption(strItem);
	//pRecord->GetItem(nCol)->SetCaption(::RemoveZero(::GetMyNumberFormat(nItem)));
}

long CDirectChargeInputDlg1::GetRecordText(CXTPGridRecord *pRecord, long nCol)
{
	CXTPGridRecordItemText *pItem = (CXTPGridRecordItemText*)pRecord->GetItem(nCol);
	CString strItem = pItem->GetCaption(NULL);
	strItem.Replace(",", "");
	return atoi(strItem);
}



void CDirectChargeInputDlg1::RefreshChargeList()
{
	m_lstCharge.DeleteAllItems();

	m_lstCharge.InsertItem(0, "A타입");
	m_lstCharge.InsertItem(1, "B타입");
	m_lstCharge.InsertItem(2, "C타입");
	m_lstCharge.InsertItem(3, "D타입");
	m_lstCharge.Populate();



	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_charge_dong_q3");
	cmd.AddParameter(m_nCompany);
	cmd.AddParameter(m_nStartDongID);
	cmd.AddParameter(m_nDestDongID);

	if(!rs.Execute(&cmd))
		return;

	CXTPGridRecords *pRecords = m_lstCharge.GetRecords();
	CXTPGridRecord *pRecord1 = pRecords->GetAt(0);
	CXTPGridRecord *pRecord2 = pRecords->GetAt(1);
	CXTPGridRecord *pRecord3 = pRecords->GetAt(2);
	CXTPGridRecord *pRecord4 = pRecords->GetAt(3);

	long nCharge;
	for(int i=0;i<rs.GetRecordCount(); i++)
	{		
		rs.GetFieldValue("nMotoChargeA", nCharge); SetRecordText(pRecord1, COL_AUTO, nCharge);
		rs.GetFieldValue("nDamaChargeA", nCharge); SetRecordText(pRecord1, COL_DAMA, nCharge);
		rs.GetFieldValue("nRaboChargeA", nCharge); SetRecordText(pRecord1, COL_RABO, nCharge);
		rs.GetFieldValue("nBonggoChargeA", nCharge); SetRecordText(pRecord1, COL_BAN, nCharge);
		rs.GetFieldValue("nTruckChargeA", nCharge); SetRecordText(pRecord1, COL_TRUCK, nCharge);
		rs.GetFieldValue("nSubWayChargeA", nCharge); SetRecordText(pRecord1, COL_SUBWAY, nCharge);
		rs.GetFieldValue("nMotoChargeB", nCharge); SetRecordText(pRecord2, COL_AUTO, nCharge);
		rs.GetFieldValue("nDamaChargeB", nCharge); SetRecordText(pRecord2, COL_DAMA, nCharge);
		rs.GetFieldValue("nRaboChargeB", nCharge); SetRecordText(pRecord2, COL_RABO, nCharge);
		rs.GetFieldValue("nBonggoChargeB", nCharge); SetRecordText(pRecord2, COL_BAN, nCharge);
		rs.GetFieldValue("nTruckChargeB", nCharge); SetRecordText(pRecord2, COL_TRUCK, nCharge);
		rs.GetFieldValue("nSubWayChargeB", nCharge); SetRecordText(pRecord2, COL_SUBWAY, nCharge);
		rs.GetFieldValue("nMotoChargeC", nCharge); SetRecordText(pRecord3, COL_AUTO, nCharge);
		rs.GetFieldValue("nDamaChargeC", nCharge); SetRecordText(pRecord3, COL_DAMA, nCharge);
		rs.GetFieldValue("nRaboChargeC", nCharge); SetRecordText(pRecord3, COL_RABO, nCharge);
		rs.GetFieldValue("nBonggoChargeC", nCharge); SetRecordText(pRecord3, COL_BAN, nCharge);
		rs.GetFieldValue("nTruckChargeC", nCharge); SetRecordText(pRecord3, COL_TRUCK, nCharge);
		rs.GetFieldValue("nSubWayChargeC", nCharge); SetRecordText(pRecord3, COL_SUBWAY, nCharge);
		rs.GetFieldValue("nMotoChargeD", nCharge); SetRecordText(pRecord4, COL_AUTO, nCharge);
		rs.GetFieldValue("nDamaChargeD", nCharge); SetRecordText(pRecord4, COL_DAMA, nCharge);
		rs.GetFieldValue("nRaboChargeD", nCharge); SetRecordText(pRecord4, COL_RABO, nCharge);
		rs.GetFieldValue("nBonggoChargeD", nCharge); SetRecordText(pRecord4, COL_BAN, nCharge);
		rs.GetFieldValue("nTruckChargeD", nCharge); SetRecordText(pRecord4, COL_TRUCK, nCharge);
		rs.GetFieldValue("nSubWayChargeD", nCharge); SetRecordText(pRecord4, COL_SUBWAY, nCharge);

		break;
	}

	m_lstCharge.Populate();
}


     
long CDirectChargeInputDlg1::GetExceptionID(CPOIUnit *pPoi)
{

	long nDongID = 0;
	if(	m_ci.m_bUseDetailDong ||  IsExceptionDetailDongUse(pPoi) )
		nDongID = pPoi->GetID();
	else
	{
		nDongID = (pPoi->m_nClass == 0 && pPoi->GetMainDongID() > 0) ? 
			pPoi->GetMainDongID() : pPoi->GetID();
	}


	return nDongID;
}

void CDirectChargeInputDlg1::RefreshChargeGNoList()
{
	m_lstChargeGNo.DeleteAllItems();

	if(m_nGNo <= 0)
		return;

	m_lstChargeGNo.InsertItem(0, "");
	m_lstChargeGNo.Populate();

	CXTPGridRecord *pRecord = m_lstChargeGNo.GetRecords()->GetAt(0);

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_charge_dong_gno");
	cmd.AddParameter(m_nCompany);
	cmd.AddParameter(m_nGNo);
	cmd.AddParameter(m_nStartDongID);
	cmd.AddParameter(m_nDestDongID);
	CMkParameter *parName = cmd.AddParameter(typeString, typeOutput, 20, "");

	if(!rs.Execute(&cmd))
		return;

	SetRecordText(pRecord, 0, parName->GetString());

	long nCharge;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nMotoCharge", nCharge); SetRecordText(pRecord, 1, nCharge);
		rs.GetFieldValue("nMotoChargeRider", nCharge); SetRecordText(pRecord, 2, nCharge);
		rs.GetFieldValue("nMotoDiscount", nCharge); SetRecordText(pRecord, 3, nCharge);
		rs.GetFieldValue("nDamaCharge", nCharge); SetRecordText(pRecord, 4, nCharge);
		rs.GetFieldValue("nDamaChargeRider", nCharge); SetRecordText(pRecord, 5, nCharge);
		rs.GetFieldValue("nDamaDiscount", nCharge); SetRecordText(pRecord, 6, nCharge);
		rs.GetFieldValue("nRaboCharge", nCharge); SetRecordText(pRecord, 7, nCharge);
		rs.GetFieldValue("nRaboChargeRider", nCharge); SetRecordText(pRecord, 8, nCharge);
		rs.GetFieldValue("nRaboDiscount", nCharge); SetRecordText(pRecord, 9, nCharge);
		rs.GetFieldValue("nBonggoCharge", nCharge); SetRecordText(pRecord, 10, nCharge);
		rs.GetFieldValue("nBonggoChargeRider", nCharge); SetRecordText(pRecord, 11, nCharge);
		rs.GetFieldValue("nBonggoDiscount", nCharge); SetRecordText(pRecord, 12, nCharge);
		rs.GetFieldValue("nTruckCharge", nCharge); SetRecordText(pRecord, 13, nCharge);
		rs.GetFieldValue("nTruckChargeRider", nCharge); SetRecordText(pRecord, 14, nCharge);
		rs.GetFieldValue("nTruckDiscount", nCharge); SetRecordText(pRecord, 15, nCharge);
		rs.GetFieldValue("nSubWayCharge", nCharge); SetRecordText(pRecord, 16, nCharge);
		rs.GetFieldValue("nSubWayChargeRider", nCharge); SetRecordText(pRecord, 17, nCharge);
		rs.GetFieldValue("nSubWayDiscount", nCharge); SetRecordText(pRecord, 18, nCharge);

		break;
	}

	m_lstChargeGNo.Populate();
}

void CDirectChargeInputDlg1::RefreshChargeCNoList()
{
	m_lstChargeCNo.DeleteAllItems();

	if(m_nCNo <= 0)
		return;

	m_lstChargeCNo.InsertItem(0, "");
	m_lstChargeCNo.Populate();

	CXTPGridRecord *pRecord = m_lstChargeCNo.GetRecords()->GetAt(0);

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_charge_dong_cno");
	cmd.AddParameter(m_nCompany);
	cmd.AddParameter(m_nCNo);
	cmd.AddParameter(m_nStartDongID);
	cmd.AddParameter(m_nDestDongID);

	long nCharge;

	if(!rs.Execute(&cmd))
		return;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nMotoCharge", nCharge); SetRecordText(pRecord, 0, nCharge);
		rs.GetFieldValue("nMotoChargeRider", nCharge); SetRecordText(pRecord, 1, nCharge);
		rs.GetFieldValue("nMotoDiscount", nCharge); SetRecordText(pRecord, 2, nCharge);
		rs.GetFieldValue("nDamaCharge", nCharge); SetRecordText(pRecord, 3, nCharge);
		rs.GetFieldValue("nDamaChargeRider", nCharge); SetRecordText(pRecord, 4, nCharge);
		rs.GetFieldValue("nDamaDiscount", nCharge); SetRecordText(pRecord, 5, nCharge);
		rs.GetFieldValue("nRaboCharge", nCharge); SetRecordText(pRecord, 6, nCharge);
		rs.GetFieldValue("nRaboChargeRider", nCharge); SetRecordText(pRecord, 7, nCharge);
		rs.GetFieldValue("nRaboDiscount", nCharge); SetRecordText(pRecord, 8, nCharge);
		rs.GetFieldValue("nBonggoCharge", nCharge); SetRecordText(pRecord, 9, nCharge);
		rs.GetFieldValue("nBonggoChargeRider", nCharge); SetRecordText(pRecord, 10, nCharge);
		rs.GetFieldValue("nBonggoDiscount", nCharge); SetRecordText(pRecord, 11, nCharge);
		rs.GetFieldValue("nTruckCharge", nCharge); SetRecordText(pRecord, 12, nCharge);
		rs.GetFieldValue("nTruckChargeRider", nCharge); SetRecordText(pRecord, 13, nCharge);
		rs.GetFieldValue("nTruckDiscount", nCharge); SetRecordText(pRecord, 14, nCharge);
		rs.GetFieldValue("nSubWayCharge", nCharge); SetRecordText(pRecord, 15, nCharge);
		rs.GetFieldValue("nSubWayChargeRider", nCharge); SetRecordText(pRecord, 16, nCharge);
		rs.GetFieldValue("nSubWayDiscount", nCharge); SetRecordText(pRecord, 17, nCharge);

		break;
	}

	m_lstChargeCNo.Populate();
}

void CDirectChargeInputDlg1::OnBnClickedSaveBtn()
{
	if(!POWER_CHECK(1101, "요금수정/삭제", TRUE))
		return;

	if(!m_bUpdateChargeOk)
	{ 
		MessageBox("요금 링크를 사용하는 업체는 요금을 수정 하실수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}
 
	CXTPGridRecords *pRecords = m_lstCharge.GetRecords();
	CXTPGridRecord *pRecord1 = pRecords->GetAt(0);
	CXTPGridRecord *pRecord2 = pRecords->GetAt(1);
	CXTPGridRecord *pRecord3 = pRecords->GetAt(2);
	CXTPGridRecord *pRecord4 = pRecords->GetAt(3);

	CMkCommand cmd(m_pMkDb, "update_charge_dong_direct_q4");
	cmd.AddParameter(m_nCompany);
	cmd.AddParameter(m_nStartDongID);
	cmd.AddParameter(m_nDestDongID);
	cmd.AddParameter(m_chkTwoWay.GetCheck());;

	cmd.AddParameter(GetRecordText(pRecord1, COL_AUTO));
	cmd.AddParameter(GetRecordText(pRecord1, COL_DAMA));
	cmd.AddParameter(GetRecordText(pRecord1, COL_RABO));
	cmd.AddParameter(GetRecordText(pRecord1, COL_BAN));
	cmd.AddParameter(GetRecordText(pRecord1, COL_TRUCK));
	cmd.AddParameter(GetRecordText(pRecord1, COL_SUBWAY));
	cmd.AddParameter(GetRecordText(pRecord2, COL_AUTO));
	cmd.AddParameter(GetRecordText(pRecord2, COL_DAMA));
	cmd.AddParameter(GetRecordText(pRecord2, COL_RABO));
	cmd.AddParameter(GetRecordText(pRecord2, COL_BAN));
	cmd.AddParameter(GetRecordText(pRecord2, COL_TRUCK));
	cmd.AddParameter(GetRecordText(pRecord2, COL_SUBWAY));
	cmd.AddParameter(GetRecordText(pRecord3, COL_AUTO));
	cmd.AddParameter(GetRecordText(pRecord3, COL_DAMA));
	cmd.AddParameter(GetRecordText(pRecord3, COL_RABO));
	cmd.AddParameter(GetRecordText(pRecord3, COL_BAN));
	cmd.AddParameter(GetRecordText(pRecord3, COL_TRUCK));
	cmd.AddParameter(GetRecordText(pRecord3, COL_SUBWAY));
	cmd.AddParameter(GetRecordText(pRecord4, COL_AUTO));
	cmd.AddParameter(GetRecordText(pRecord4, COL_DAMA));
	cmd.AddParameter(GetRecordText(pRecord4, COL_RABO));
	cmd.AddParameter(GetRecordText(pRecord4, COL_BAN));
	cmd.AddParameter(GetRecordText(pRecord4, COL_TRUCK));
	cmd.AddParameter(GetRecordText(pRecord4, COL_SUBWAY));

	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);

	if(cmd.Execute())
	{
		MessageBox("저장되었습니다", "확인", MB_ICONINFORMATION);
		GetParent()->PostMessage(WM_USER + ID_CHARGE_REINIT);
	}
}

void CDirectChargeInputDlg1::OnBnClickedSaveGnoBtn()
{
	if(!POWER_CHECK(1101, "요금수정/삭제", TRUE))
		return;

	if(m_nGNo <= 0)
	{
		MessageBox("해당 고객은 그룹에 속한 고객이 아닙니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CXTPGridRecords *pRecords = m_lstChargeGNo.GetRecords();
	CXTPGridRecord *pRecord1 = pRecords->GetAt(0);

	CMkCommand cmd(m_pMkDb, "update_charge_dong_direct_gno_1");
	cmd.AddParameter(m_nCompany);
	cmd.AddParameter(m_nGNo);
	cmd.AddParameter(m_nStartDongID);
	cmd.AddParameter(m_nDestDongID);
	cmd.AddParameter(m_chkTwoWayGNo.GetCheck());;

	cmd.AddParameter(GetRecordText(pRecord1, 1));
	cmd.AddParameter(GetRecordText(pRecord1, 2));
	cmd.AddParameter(GetRecordText(pRecord1, 3));
	cmd.AddParameter(GetRecordText(pRecord1, 4));
	cmd.AddParameter(GetRecordText(pRecord1, 5));
	cmd.AddParameter(GetRecordText(pRecord1, 6));
	cmd.AddParameter(GetRecordText(pRecord1, 7));
	cmd.AddParameter(GetRecordText(pRecord1, 8));
	cmd.AddParameter(GetRecordText(pRecord1, 9));
	cmd.AddParameter(GetRecordText(pRecord1, 10));
	cmd.AddParameter(GetRecordText(pRecord1, 11));
	cmd.AddParameter(GetRecordText(pRecord1, 12));
	cmd.AddParameter(GetRecordText(pRecord1, 13));
	cmd.AddParameter(GetRecordText(pRecord1, 14));
	cmd.AddParameter(GetRecordText(pRecord1, 15));
	cmd.AddParameter(GetRecordText(pRecord1, 16));
	cmd.AddParameter(GetRecordText(pRecord1, 17));
	cmd.AddParameter(GetRecordText(pRecord1, 18));

	if(cmd.Execute())
	{
		MessageBox("저장되었습니다", "확인", MB_ICONINFORMATION);
	}
}

void CDirectChargeInputDlg1::OnBnClickedSaveCnoBtn()
{
	if(!POWER_CHECK(1101, "요금수정/삭제", TRUE))
		return;

	if(m_nCNo <= 0)
	{
		MessageBox("고객을 선택 후 저장하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CXTPGridRecords *pRecords = m_lstChargeCNo.GetRecords();
	CXTPGridRecord *pRecord1 = pRecords->GetAt(0);

	CMkCommand cmd(m_pMkDb, "update_charge_dong_direct_cno");
	cmd.AddParameter(m_nCompany);
	cmd.AddParameter(m_nCNo);
	cmd.AddParameter(m_nStartDongID);
	cmd.AddParameter(m_nDestDongID);
	cmd.AddParameter(m_chkTwoWayGNo.GetCheck());;

	cmd.AddParameter(GetRecordText(pRecord1, 0));
	cmd.AddParameter(GetRecordText(pRecord1, 1));
	cmd.AddParameter(GetRecordText(pRecord1, 2));
	cmd.AddParameter(GetRecordText(pRecord1, 3));
	cmd.AddParameter(GetRecordText(pRecord1, 4));
	cmd.AddParameter(GetRecordText(pRecord1, 5));
	cmd.AddParameter(GetRecordText(pRecord1, 6));
	cmd.AddParameter(GetRecordText(pRecord1, 7));
	cmd.AddParameter(GetRecordText(pRecord1, 8));
	cmd.AddParameter(GetRecordText(pRecord1, 9));
	cmd.AddParameter(GetRecordText(pRecord1, 10));
	cmd.AddParameter(GetRecordText(pRecord1, 11));
	cmd.AddParameter(GetRecordText(pRecord1, 12));
	cmd.AddParameter(GetRecordText(pRecord1, 13));
	cmd.AddParameter(GetRecordText(pRecord1, 14));
	cmd.AddParameter(GetRecordText(pRecord1, 15));
	cmd.AddParameter(GetRecordText(pRecord1, 16));
	cmd.AddParameter(GetRecordText(pRecord1, 17));

	if(cmd.Execute())
	{
		MessageBox("저장되었습니다", "확인", MB_ICONINFORMATION);
	}
}

void CDirectChargeInputDlg1::OnBnClickedHtypeModifyBtn()
{
	OnOK();
}
