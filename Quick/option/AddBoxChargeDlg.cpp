// AddBoxChargeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "AddBoxChargeDlg.h"

#define OPTION_COUNT 10
#define OPTION_BIKE_WEIGHT_COUNT 5

UINT _nSmallBoxStart[] = {IDC_SMALL_BOX_START_COMBO1, IDC_SMALL_BOX_START_COMBO2, IDC_SMALL_BOX_START_COMBO3, IDC_SMALL_BOX_START_COMBO4, IDC_SMALL_BOX_START_COMBO5,
						IDC_SMALL_BOX_START_COMBO6, IDC_SMALL_BOX_START_COMBO7, IDC_SMALL_BOX_START_COMBO8, IDC_SMALL_BOX_START_COMBO9, IDC_SMALL_BOX_START_COMBO10};
UINT _nSmallBoxEnd[] = {IDC_SMALL_BOX_END_COMBO1, IDC_SMALL_BOX_END_COMBO2, IDC_SMALL_BOX_END_COMBO3, IDC_SMALL_BOX_END_COMBO4, IDC_SMALL_BOX_END_COMBO5,
						IDC_SMALL_BOX_END_COMBO6, IDC_SMALL_BOX_END_COMBO7, IDC_SMALL_BOX_END_COMBO8, IDC_SMALL_BOX_END_COMBO9, IDC_SMALL_BOX_END_COMBO10};
UINT _nSmallBoxOption[] = {IDC_SMALL_BOX_OPTION_COMBO1, IDC_SMALL_BOX_OPTION_COMBO2, IDC_SMALL_BOX_OPTION_COMBO3, IDC_SMALL_BOX_OPTION_COMBO4, IDC_SMALL_BOX_OPTION_COMBO5,
							IDC_SMALL_BOX_OPTION_COMBO6, IDC_SMALL_BOX_OPTION_COMBO7, IDC_SMALL_BOX_OPTION_COMBO8, IDC_SMALL_BOX_OPTION_COMBO9, IDC_SMALL_BOX_OPTION_COMBO10};
UINT _nBigBoxStart[] = {IDC_BIG_BOX_START_COMBO1, IDC_BIG_BOX_START_COMBO2, IDC_BIG_BOX_START_COMBO3, IDC_BIG_BOX_START_COMBO4, IDC_BIG_BOX_START_COMBO5,
							IDC_BIG_BOX_START_COMBO6, IDC_BIG_BOX_START_COMBO7, IDC_BIG_BOX_START_COMBO8, IDC_BIG_BOX_START_COMBO9, IDC_BIG_BOX_START_COMBO10};
UINT _nBigBoxEnd[] = {IDC_BIG_BOX_END_COMBO1, IDC_BIG_BOX_END_COMBO2, IDC_BIG_BOX_END_COMBO3, IDC_BIG_BOX_END_COMBO4, IDC_BIG_BOX_END_COMBO5,
							IDC_BIG_BOX_END_COMBO6, IDC_BIG_BOX_END_COMBO7, IDC_BIG_BOX_END_COMBO8, IDC_BIG_BOX_END_COMBO9, IDC_BIG_BOX_END_COMBO10};
UINT _nBigBoxOption[] = {IDC_BIG_BOX_OPTION_COMBO1, IDC_BIG_BOX_OPTION_COMBO2, IDC_BIG_BOX_OPTION_COMBO3, IDC_BIG_BOX_OPTION_COMBO4, IDC_BIG_BOX_OPTION_COMBO5,
						IDC_BIG_BOX_OPTION_COMBO6, IDC_BIG_BOX_OPTION_COMBO7, IDC_BIG_BOX_OPTION_COMBO8, IDC_BIG_BOX_OPTION_COMBO9, IDC_BIG_BOX_OPTION_COMBO10};

UINT _nBikeWeightStart[] = {IDC_BIKE_WEIGHT_START_COMBO1, IDC_BIKE_WEIGHT_START_COMBO2, IDC_BIKE_WEIGHT_START_COMBO3, IDC_BIKE_WEIGHT_START_COMBO4, IDC_BIKE_WEIGHT_START_COMBO5};
UINT _nBikeWeightEnd[] = {IDC_BIKE_WEIGHT_END_COMBO1, IDC_BIKE_WEIGHT_END_COMBO2, IDC_BIKE_WEIGHT_END_COMBO3, IDC_BIKE_WEIGHT_END_COMBO4, IDC_BIKE_WEIGHT_END_COMBO5};
UINT _nBikeWeightOption[] = {IDC_BIKE_WEIGHT_OPTION_COMBO1, IDC_BIKE_WEIGHT_OPTION_COMBO2, IDC_BIKE_WEIGHT_OPTION_COMBO3, IDC_BIKE_WEIGHT_OPTION_COMBO4, IDC_BIKE_WEIGHT_OPTION_COMBO5};


// CAddBoxChargeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAddBoxChargeDlg, CMyDialog)

CAddBoxChargeDlg::CAddBoxChargeDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CAddBoxChargeDlg::IDD, pParent)
{
	m_nCompany = 0;
}

CAddBoxChargeDlg::~CAddBoxChargeDlg()
{
}

void CAddBoxChargeDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USE_LARGE_SUM_CHECK, m_chkUseLargeSum);
	DDX_Control(pDX, IDC_DOCUMENT_LIST, m_lstDocument);
	DDX_Control(pDX, IDC_DOCUMENT_EDIT, m_edtDocument);
	DDX_Control(pDX, IDC_DOCUMENT_ADD_EDIT, m_edtDocumentAdd);
}


BEGIN_MESSAGE_MAP(CAddBoxChargeDlg, CMyDialog)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_CLOSE_BTN, OnBnClickedCloseBtn)
	ON_BN_CLICKED(IDC_SAVE_BTN, OnBnClickedSaveBtn)
	ON_BN_CLICKED(IDC_INSERT_DOCUMENT_OPTION_BTN, OnBnClickedInsertDocumentOptionBtn)
	ON_COMMAND(ID_UP, OnUp)
	ON_COMMAND(ID_DOWN, OnDown)
	ON_COMMAND(ID_DELETE, OnDelete)
	
END_MESSAGE_MAP()


BOOL CAddBoxChargeDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_lstDocument.InsertColumn(0, "서류물품", LVCFMT_LEFT, 80);
	m_lstDocument.InsertColumn(1, "할증금액", LVCFMT_RIGHT, 80);
	m_lstDocument.GetReportHeader()->AllowColumnSort(FALSE);
	m_lstDocument.GetPaintManager()->m_strNoItems = "서류 항목을 추가하세요";
	m_lstDocument.Populate();
	

	for(int i=0; i<OPTION_COUNT; i++)
	{
		CComboBox *pSmallBoxStart = (CComboBox*)GetDlgItem(_nSmallBoxStart[i]);
		CComboBox *pSmallBoxEnd = (CComboBox*)GetDlgItem(_nSmallBoxEnd[i]);
		CComboBox *pSmallBoxOption = (CComboBox*)GetDlgItem(_nSmallBoxOption[i]);
		CComboBox *pBigBoxStart = (CComboBox*)GetDlgItem(_nBigBoxStart[i]);
		CComboBox *pBigBoxEnd = (CComboBox*)GetDlgItem(_nBigBoxEnd[i]);
		CComboBox *pBigBoxOption = (CComboBox*)GetDlgItem(_nBigBoxOption[i]);

	
		//for(int j=0; j<50; j++)
		//{
			//pSmallBoxStart->InsertString(j-1, ::GetStringFromLong(j)); //너무느림
		//	pSmallBoxStart->SetItemData(j-1, j);
			//pSmallBoxEnd->InsertString(j-1, ::GetStringFromLong(j));
		//	pSmallBoxEnd->SetItemData(j-1, j);
			//pBigBoxStart->InsertString(j-1, ::GetStringFromLong(j));
		//	pBigBoxStart->SetItemData(j-1, j);
			//pBigBoxEnd->InsertString(j-1, ::GetStringFromLong(j));
		//	pBigBoxEnd->SetItemData(j-1, j);
		//}

		pSmallBoxStart->SetCurSel(0);
		pSmallBoxEnd->SetCurSel(0);
		pBigBoxStart->SetCurSel(0);
		pBigBoxEnd->SetCurSel(0);

		InsertApplyCombo(pSmallBoxOption);
		InsertApplyCombo(pBigBoxOption);
	}

	for(int i=0; i<OPTION_BIKE_WEIGHT_COUNT; i++)
	{
		CComboBox *pBikeWeightStart = (CComboBox*)GetDlgItem(_nBikeWeightStart[i]);
		CComboBox *pBikeWeightEnd = (CComboBox*)GetDlgItem(_nBikeWeightEnd[i]);
		CComboBox *pBikeWeightOption = (CComboBox*)GetDlgItem(_nBikeWeightOption[i]);

		InsertBikeWeightType(pBikeWeightStart);
		InsertBikeWeightType(pBikeWeightEnd);
		InsertApplyBikeWeightCombo(pBikeWeightOption);
	}

	RefreshDlg();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAddBoxChargeDlg::InsertBikeWeightType(CComboBox *pBox)
{ 
	pBox->InsertString(0, "0"); pBox->SetItemData(0, 0);
	pBox->InsertString(1, "1"); pBox->SetItemData(1, 1);
	pBox->InsertString(2, "2"); pBox->SetItemData(2, 2);
	pBox->InsertString(3, "3"); pBox->SetItemData(3, 3);
	pBox->InsertString(4, "4"); pBox->SetItemData(4, 4);
	pBox->InsertString(5, "5"); pBox->SetItemData(5, 5);
	pBox->InsertString(6, "10"); pBox->SetItemData(6, 10);
	pBox->InsertString(7, "15"); pBox->SetItemData(7, 15);
	pBox->InsertString(8, "20"); pBox->SetItemData(8, 20);
	pBox->InsertString(9, "25"); pBox->SetItemData(9, 25);
	pBox->InsertString(10, "30"); pBox->SetItemData(10, 30);
	pBox->InsertString(11, "35"); pBox->SetItemData(11, 35);
	pBox->InsertString(12, "40"); pBox->SetItemData(12, 40);
	pBox->InsertString(13, "45"); pBox->SetItemData(13, 45);
	pBox->InsertString(14, "50"); pBox->SetItemData(14, 50);
	pBox->InsertString(15, "100"); pBox->SetItemData(15, 100);
	pBox->SetCurSel(0);
}

void CAddBoxChargeDlg::InsertApplyBikeWeightCombo(CComboBox *pBox)
{
	pBox->InsertString(0, "적용안함"); pBox->SetItemData(0, 0);
	pBox->InsertString(1, "1,000"); pBox->SetItemData(1, 1000);
	pBox->InsertString(2, "2,000"); pBox->SetItemData(2, 2000);
	pBox->InsertString(3, "3,000"); pBox->SetItemData(3, 3000);
	pBox->InsertString(4, "4,000"); pBox->SetItemData(4, 4000);
	pBox->InsertString(5, "5,000"); pBox->SetItemData(5, 5000);
	pBox->InsertString(6, "6,000"); pBox->SetItemData(6, 6000);
	pBox->InsertString(7, "7,000"); pBox->SetItemData(7, 7000);
	pBox->InsertString(8, "8,000"); pBox->SetItemData(8, 8000);
	pBox->InsertString(9, "9,000"); pBox->SetItemData(9, 9000);
	pBox->InsertString(10, "10,000"); pBox->SetItemData(10, 10000);
	pBox->InsertString(11, "11,000"); pBox->SetItemData(11, 11000);
	pBox->InsertString(12, "12,000"); pBox->SetItemData(12, 12000);
	pBox->InsertString(13, "13,000"); pBox->SetItemData(13, 13000);
	pBox->InsertString(14, "14,000"); pBox->SetItemData(14, 14000);
	pBox->InsertString(15, "15,000"); pBox->SetItemData(15, 15000);
	pBox->InsertString(16, "16,000"); pBox->SetItemData(16, 16000);
	pBox->InsertString(17, "17,000"); pBox->SetItemData(17, 17000);
	pBox->InsertString(18, "18,000"); pBox->SetItemData(18, 18000);
	pBox->InsertString(19, "19,000"); pBox->SetItemData(19, 19000);
	pBox->InsertString(20, "20,000"); pBox->SetItemData(20, 20000);
	pBox->InsertString(21, "23,000"); pBox->SetItemData(21, 23000);
	pBox->InsertString(22, "25,000"); pBox->SetItemData(22, 25000);
	pBox->InsertString(23, "30,000"); pBox->SetItemData(23, 30000);
	pBox->InsertString(24, "35,000"); pBox->SetItemData(24, 35000);
	pBox->InsertString(25, "40,000"); pBox->SetItemData(25, 40000);
	pBox->InsertString(26, "45,000"); pBox->SetItemData(26, 45000);
	pBox->InsertString(27, "50,000"); pBox->SetItemData(27, 50000);
	pBox->SetCurSel(0);
}

void CAddBoxChargeDlg::InsertApplyCombo(CComboBox *pBox)
{
	pBox->InsertString(0, "적용안함"); pBox->SetItemData(0, 0);
	pBox->InsertString(1, "다마스적용"); pBox->SetItemData(1, -1);
	pBox->InsertString(2, "라보적용"); pBox->SetItemData(2, -2);
	pBox->InsertString(3, "밴적용"); pBox->SetItemData(3, -3);
	pBox->InsertString(4, "트럭적용"); pBox->SetItemData(4, -4);
	pBox->InsertString(5, "1,000"); pBox->SetItemData(5, 1000);
	pBox->InsertString(6, "2,000"); pBox->SetItemData(6, 2000);
	pBox->InsertString(7, "3,000"); pBox->SetItemData(7, 3000);
	pBox->InsertString(8, "4,000"); pBox->SetItemData(8, 4000);
	pBox->InsertString(9, "5,000"); pBox->SetItemData(9, 5000);
	pBox->InsertString(10, "6,000"); pBox->SetItemData(10, 6000);
	pBox->InsertString(11, "7,000"); pBox->SetItemData(11, 7000);
	pBox->InsertString(12, "8,000"); pBox->SetItemData(12, 8000);
	pBox->InsertString(13, "9,000"); pBox->SetItemData(13, 9000);
	pBox->InsertString(14, "10,000"); pBox->SetItemData(14, 10000);
	pBox->InsertString(15, "11,000"); pBox->SetItemData(15, 11000);
	pBox->InsertString(16, "12,000"); pBox->SetItemData(16, 12000);
	pBox->InsertString(17, "13,000"); pBox->SetItemData(17, 13000);
	pBox->InsertString(18, "14,000"); pBox->SetItemData(18, 14000);
	pBox->InsertString(19, "15,000"); pBox->SetItemData(19, 15000);
	pBox->InsertString(20, "16,000"); pBox->SetItemData(20, 16000);
	pBox->InsertString(21, "17,000"); pBox->SetItemData(21, 17000);
	pBox->InsertString(22, "18,000"); pBox->SetItemData(22, 18000);
	pBox->InsertString(23, "19,000"); pBox->SetItemData(23, 19000);
	pBox->InsertString(24, "20,000"); pBox->SetItemData(24, 20000);
	pBox->InsertString(25, "23,000"); pBox->SetItemData(25, 23000);
	pBox->InsertString(26, "25,000"); pBox->SetItemData(26, 25000);
	pBox->InsertString(27, "30,000"); pBox->SetItemData(27, 30000);
	pBox->InsertString(28, "35,000"); pBox->SetItemData(28, 35000);
	pBox->InsertString(29, "40,000"); pBox->SetItemData(29, 40000);
	pBox->InsertString(30, "45,000"); pBox->SetItemData(30, 45000);
	pBox->InsertString(31, "50,000"); pBox->SetItemData(31, 50000);
	pBox->SetCurSel(0);
}

void CAddBoxChargeDlg::RefreshDlg()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_box_charge_option_1");
	cmd.AddParameter(m_nCompany);

	CMkParameter *pPar = cmd.AddParameter(typeBool, typeOutput, sizeof(BOOL), 0);

	if(!rs.Execute(&cmd))
		return;

	BOOL bUseLargeSum; pPar->GetValue(bUseLargeSum);

	m_chkUseLargeSum.SetCheck(bUseLargeSum);

	if(rs.GetRecordCount() == 0)
		return;

	long nSmallBox = 0;
	long nBigBox = 0;
	long nBikeWeightBox = 0;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		//if(i > OPTION_COUNT * 2)
		//	break;

		long nType, nStart, nEnd, nApply;

		rs.GetFieldValue("nType", nType);
		rs.GetFieldValue("nStart", nStart);
		rs.GetFieldValue("nEnd", nEnd);
		rs.GetFieldValue("nApply", nApply);

		CComboBox *pBoxStart = NULL;
		CComboBox *pBoxEnd = NULL;
		CComboBox *pBoxOption = NULL;

		CComboBox *pBikeWeightStart = NULL;
		CComboBox *pBikeWeightEnd = NULL;
		CComboBox *pBikeWeightOption = NULL;

		if(nType == 0 )
		{
			pBoxStart = (CComboBox*)GetDlgItem(_nSmallBoxStart[nSmallBox]);
			pBoxEnd = (CComboBox*)GetDlgItem(_nSmallBoxEnd[nSmallBox]);
			pBoxOption =  (CComboBox*)GetDlgItem(_nSmallBoxOption[nSmallBox]);

			nSmallBox++;
		}
		else if(nType == 1)
		{
			pBoxStart = (CComboBox*)GetDlgItem(_nBigBoxStart[nBigBox]);
			pBoxEnd = (CComboBox*)GetDlgItem(_nBigBoxEnd[nBigBox]);
			pBoxOption =  (CComboBox*)GetDlgItem(_nBigBoxOption[nBigBox]);

			nBigBox++;
		}
		else if(nType == 2)
		{
			pBikeWeightStart = (CComboBox*)GetDlgItem(_nBikeWeightStart[nBikeWeightBox]);
			pBikeWeightEnd = (CComboBox*)GetDlgItem(_nBikeWeightEnd[nBikeWeightBox]);
			pBikeWeightOption =  (CComboBox*)GetDlgItem(_nBikeWeightOption[nBikeWeightBox]);
			nBikeWeightBox++;
		}
		else
			return;

		if(nType == 0 || nType == 1)
		{
			pBoxStart->SetCurSel(nStart - 1);
			pBoxEnd->SetCurSel(nEnd - 1);
			//SetComboSelect(pBoxStart, nStart);
			//SetComboSelect(pBoxEnd, nEnd);
			SetComboSelect(pBoxOption, nApply);
		}
		else if(nType == 2)
		{
			//SetComboSelect(pBikeWeightStart, nStart);
			//SetComboSelect(pBikeWeightEnd, nEnd);
			pBikeWeightStart->SetWindowText(::GetMyNumberFormat(nStart));
			pBikeWeightEnd->SetWindowText(::GetMyNumberFormat(nEnd));
			SetComboSelect(pBikeWeightOption, nApply);
		}

		rs.MoveNext();
	}

	RefreshDocumentList();
}

void CAddBoxChargeDlg::RefreshDocumentList()
{
	m_lstDocument.DeleteAllItems();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_document_charge_option");
	cmd.AddParameter(m_nCompany);

	if(!rs.Execute(&cmd))
		return;

	CString strItem;
	long nAddCharge;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("sItem", strItem);
		rs.GetFieldValue("nAddCharge", nAddCharge);

		m_lstDocument.InsertItem(i, strItem);
		m_lstDocument.SetItemText(i, 1, ::GetMyNumberFormat(nAddCharge));

		rs.MoveNext();
	}

	m_lstDocument.Populate();
}

void CAddBoxChargeDlg::SetComboSelect(CComboBox *pBox, long nOption)
{
	long nCount = pBox->GetCount();

	for(int i=0; i<nCount; i++)
	{
		if(pBox->GetItemData(i) == nOption)
		{
			pBox->SetCurSel(i);
			break;
		}
	}
}

void CAddBoxChargeDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}

void CAddBoxChargeDlg::OnBnClickedSaveBtn()
{
	BOOL bSuccess = TRUE;

	for(int i=0; i<OPTION_COUNT; i++ )
	{
		CComboBox *pBoxStart = (CComboBox*)GetDlgItem(_nSmallBoxStart[i]);
		CComboBox *pBoxEnd = (CComboBox*)GetDlgItem(_nSmallBoxEnd[i]);
		CComboBox *pBoxOption =  (CComboBox*)GetDlgItem(_nSmallBoxOption[i]);

		//long nStart = pBoxStart->GetItemData(pBoxStart->GetCurSel());
		//long nEnd = pBoxEnd->GetItemData(pBoxEnd->GetCurSel());
		long nStart = pBoxStart->GetCurSel() + 1;
		long nEnd = pBoxEnd->GetCurSel() + 1;
		long nApply = pBoxOption->GetItemData(pBoxOption->GetCurSel());

		if(InsertBoxChargeOption(0, nStart, nEnd, nApply, i == 0 ? TRUE : FALSE) == FALSE)
		{
			bSuccess = FALSE;
			break;
		}
	}

	if(bSuccess == TRUE)
	{
		for(int i=0; i<OPTION_COUNT; i++ )
		{
			CComboBox *pBoxStart = (CComboBox*)GetDlgItem(_nBigBoxStart[i]);
			CComboBox *pBoxEnd = (CComboBox*)GetDlgItem(_nBigBoxEnd[i]);
			CComboBox *pBoxOption =  (CComboBox*)GetDlgItem(_nBigBoxOption[i]);

			//long nStart = pBoxStart->GetItemData(pBoxStart->GetCurSel());
			//long nEnd = pBoxEnd->GetItemData(pBoxEnd->GetCurSel());
			long nStart = pBoxStart->GetCurSel() + 1;
			long nEnd = pBoxEnd->GetCurSel() + 1;
			long nApply = pBoxOption->GetItemData(pBoxOption->GetCurSel());

			if(InsertBoxChargeOption(1, nStart, nEnd, nApply, FALSE) == FALSE)
				break;
		}
	}

	if(bSuccess == TRUE)
	{
		for(int i=0; i<OPTION_BIKE_WEIGHT_COUNT; i++ )
		{
			CComboBox *pBikeWeightStart = (CComboBox*)GetDlgItem(_nBikeWeightStart[i]);
			CComboBox *pBikeWeightEnd = (CComboBox*)GetDlgItem(_nBikeWeightEnd[i]);
			CComboBox *pBikeWeightOption =  (CComboBox*)GetDlgItem(_nBikeWeightOption[i]);

			//long nStart = pBikeWeightStart->GetItemData(pBikeWeightStart->GetCurSel());
			//long nEnd = pBikeWeightEnd->GetItemData(pBikeWeightEnd->GetCurSel());
			long nStart = ::GetWindowTextLong(pBikeWeightStart);
			long nEnd = ::GetWindowTextLong(pBikeWeightEnd);
			long nApply = pBikeWeightOption->GetItemData(pBikeWeightOption->GetCurSel());

			if(InsertBoxChargeOption(2, nStart, nEnd, nApply, FALSE) == FALSE)
				break;
		}
	}
	
	if(bSuccess == TRUE)
	{
		if(InsertUseLargeSumOption()) //큰요금 선택 체크박스
		{
			if(InsertDocumentChargeOption())
				MessageBox("저장되었습니다", "확인", MB_ICONINFORMATION);
		}
	}
} 

BOOL CAddBoxChargeDlg::InsertBoxChargeOption(long nType, long nStart, long nEnd, long nApply, BOOL bDelete)
{
	CMkCommand cmd(m_pMkDb, "insert_box_charge_option");
	cmd.AddParameter(m_nCompany);
	cmd.AddParameter(nType);
	cmd.AddParameter(nStart);
	cmd.AddParameter(nEnd);
	cmd.AddParameter(nApply);
	cmd.AddParameter(bDelete);

	return cmd.Execute();

}

BOOL CAddBoxChargeDlg::InsertDocumentChargeOption()
{
	CXTPGridRows *pRows = m_lstDocument.GetRows();

	if(pRows->GetCount() == 0)
		return TRUE;

	for(int i=0; i<pRows->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(0)->GetRecord();

		CMkCommand cmd(m_pMkDb, "insert_document_charge_option");
		cmd.AddParameter(m_nCompany);
		cmd.AddParameter(m_lstDocument.GetItemText(i, 0));
		cmd.AddParameter(atoi(::RemoveComma(m_lstDocument.GetItemText(i, 1))));
		cmd.AddParameter(i == 0 ? TRUE : FALSE);

		if(!cmd.Execute())
			return FALSE;
	}

	return TRUE;
}

BOOL CAddBoxChargeDlg::InsertUseLargeSumOption()
{
	CMkCommand cmd(m_pMkDb, "insert_use_large_sum_option");
	cmd.AddParameter(m_nCompany);
	cmd.AddParameter(m_chkUseLargeSum.GetCheck());

	return cmd.Execute();
}

void CAddBoxChargeDlg::OnBnClickedInsertDocumentOptionBtn()
{
	CString strItem; m_edtDocument.GetWindowText(strItem);
	CString strItemAdd; m_edtDocumentAdd.GetWindowText(strItemAdd);

	if(strItem.IsEmpty() || strItemAdd.IsEmpty())
	{
		MessageBox("물품과 금액랑을 모두 채우세요", "확인", MB_ICONINFORMATION);
		return;
	}

	long nCount = m_lstDocument.GetItemCount();

	m_lstDocument.InsertItem(nCount, strItem);
	m_lstDocument.SetItemText(nCount, 1, strItemAdd);

	m_edtDocument.SetWindowText("");
	m_edtDocumentAdd.SetWindowText("");

	m_lstDocument.Populate();
}



void CAddBoxChargeDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CPoint pt;
	GetCursorPos(&pt);

	CRect rtReport;
	m_lstDocument.GetWindowRect(&rtReport);

	if(rtReport.PtInRect(pt))
	{
		BCMenu rMenu;
		rMenu.LoadMenu(IDR_CONTEXT_MENU_1);

		BCMenu* pRMenu = (BCMenu*)rMenu.GetSubMenu(14);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);	
	}
}

void CAddBoxChargeDlg::OnUp()
{
	Swap(TRUE);
}

void CAddBoxChargeDlg::OnDown()
{
	Swap(FALSE);
}

void CAddBoxChargeDlg::OnDelete()
{
	CXTPGridSelectedRows *pRows = m_lstDocument.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	m_lstDocument.RemoveRowEx(pRows->GetAt(0));
	m_lstDocument.Populate();
}

void CAddBoxChargeDlg::Swap(BOOL bUp)
{
	CXTPGridRecord *pSelectRecord = m_lstDocument.GetFirstSelectedRecord();

	if(pSelectRecord == NULL)        
		return;

	long nSelIndex = pSelectRecord->GetIndex();

	if(bUp == TRUE && nSelIndex == 0)
		return;

	if(bUp == FALSE && nSelIndex == m_lstDocument.GetItemCount() - 1)
		return;

	CXTPGridRecord *pRecord = m_lstDocument.GetRecords()->GetAt(bUp ? nSelIndex - 1 : nSelIndex + 1);

	CString strSelectItem = m_lstDocument.GetItemText(pSelectRecord, 0);
	CString strSelectItemCharge = m_lstDocument.GetItemText(pSelectRecord, 1);

	CString strItem = m_lstDocument.GetItemText(pRecord, 0);
	CString strItemCharge = m_lstDocument.GetItemText(pRecord, 1);

	m_lstDocument.SetItemText(pRecord, 0, strSelectItem);
	m_lstDocument.SetItemText(pRecord, 1, strSelectItemCharge);

	m_lstDocument.SetItemText(pSelectRecord, 0, strItem);
	m_lstDocument.SetItemText(pSelectRecord, 1, strItemCharge);

	m_lstDocument.Populate();

	CXTPGridRows* pRows = m_lstDocument.GetRows();
	CXTPGridRow* pRow = pRows->FindInTree(pRecord);

	m_lstDocument.SetSelectedRow(pRecord->GetIndex());
}