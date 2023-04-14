// ChargeSectionTypeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ChargeSectionTypeDlg.h"



// CChargeSectionTypeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChargeSectionTypeDlg, CMyDialog)
CChargeSectionTypeDlg::CChargeSectionTypeDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CChargeSectionTypeDlg::IDD, pParent)
{
	m_strTitle = "요금";
	m_strValueName = "요금";
	m_nValueType = 0;
	m_nInitClass = 0;
	m_nCompany = 0;
}

CChargeSectionTypeDlg::~CChargeSectionTypeDlg()
{
}

void CChargeSectionTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_TYPE_COMBO, m_cmbTypeName);

	
	DDX_Control(pDX, IDC_BRANCH_STATIC, m_stcBranch);
	//DDX_Control(pDX, IDC_CARTYPE_COMBO, m_cmbCarType);
	//DDX_Control(pDX, IDC_COUNT_DATE, m_dtpCountType);
	//DDX_Control(pDX, IDC_COUNTDATE_STATIC, m_stcCountType);
	//DDX_Control(pDX, IDC_CARTYPE_STATIC, m_stcCount);
}


BEGIN_MESSAGE_MAP(CChargeSectionTypeDlg, CMyDialog)
	ON_BN_CLICKED(IDC_ADD_ROW_BTN, OnBnClickedAddRowBtn)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_TYPE_COMBO, OnCbnSelchangeTypeCombo)
	ON_BN_CLICKED(IDCANCEL, &CChargeSectionTypeDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CChargeSectionTypeDlg 메시지 처리기입니다.


BOOL CChargeSectionTypeDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	if(m_nValueType == CST_DISCOUNT)
	{
		m_strTitle = "디스카운트";
		m_strValueName = "할인액";
	}
	else if(m_nValueType == CST_COUPON)
	{
		m_strTitle = "쿠폰";
		m_strValueName = "쿠폰값";
	}
	else if(m_nValueType == CST_MILEAGE)
	{
		m_strTitle = "마일리지";
		m_strValueName = "마일리지";
	}
	else if(m_nValueType == CST_BATCH_MILEAGE)
	{
		m_strTitle = "일괄 마일리지";
		m_strValueName = "일괄 마일리지";

		m_cmbTypeName.ResetContent();
		
		m_cmbTypeName.InsertString(0,"오토,짐받이");
		m_cmbTypeName.InsertString(1,"다마,라보");
		m_cmbTypeName.InsertString(2,"벤");
		m_cmbTypeName.InsertString(3,"트럭");
		
	}
	/*else if(m_nValueType == CST_BATCH_MILEAGE_COUNT) 
	{
		m_strTitle = "일괄 마일리지(사용횟수)";
		m_strValueName = "일괄 마일리지(사용횟수)";		

		m_stcCount.ShowWindow(SW_SHOW);
		m_stcCountType.ShowWindow(SW_SHOW);

		m_cmbCarType.ShowWindow(SW_SHOW);
		m_dtpCountType.ShowWindow(SW_SHOW);


		m_cmbTypeName.InsertString(4,"전체적용");
		m_cmbTypeName.SetCurSel(4);
		
	}*/
	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 

	m_List.ModifyStyle(NULL, LVS_EDITLABELS | LVS_REPORT);
	m_List.SetExtendedStyle( LVS_EX_FLATSB | LVS_EX_FULLROWSELECT |
		LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);

	m_List.InsertColumn(0, "순서", LVCFMT_CENTER, 50);
	if(m_nValueType == CST_BATCH_MILEAGE_COUNT)
		m_List.InsertColumn(1, "시작횟수",LVCFMT_CENTER, 70);
	else
		m_List.InsertColumn(1, "시작요금",LVCFMT_CENTER, 70);
	m_List.InsertColumn(2, "~",LVCFMT_CENTER, 30);
	if(m_nValueType == CST_BATCH_MILEAGE_COUNT)
		m_List.InsertColumn(3, "끝횟수",LVCFMT_CENTER, 70);
	else
		m_List.InsertColumn(3, "끝요금",LVCFMT_CENTER, 70);
	m_List.InsertColumn(4, m_strValueName+ "(100미만%)",LVCFMT_RIGHT, 140);		

	m_List.SetDisableCol(0);	
	m_List.SetDisableCol(2);

	SetWindowText(m_strTitle + " 타입설정창");

	m_cmbTypeName.SetCurSel(m_nInitClass);

	m_stcBranch.SetWindowText(m_ci.GetBranchName(m_nCompany));
	
	if(RefreshList() == FALSE)
		OnCancel();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CChargeSectionTypeDlg::RefreshList()
{
	m_List.DeleteAllItems();

	char buffer[10];
	int nItem = 0;

	if(m_nCompany <= 0 )
	{
		MessageBox("회사설정이 올바르지 않습니다.", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_charge_section_type3");
	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(m_nValueType);
	pCmd.AddParameter(m_cmbTypeName.GetCurSel());	
	
	if(pRs.Execute(&pCmd))
	{
		while(!pRs.IsEOF())
		{
			long nNum, nStart, nEnd, nAmount;

			pRs.GetFieldValue("nNum", nNum);
			pRs.GetFieldValue("nStartValue", nStart);
			pRs.GetFieldValue("nEndValue", nEnd);
			pRs.GetFieldValue("nAmount", nAmount);
			
			m_List.InsertItem(nItem, ltoa(nNum, buffer, 10));
			m_List.SetItemText(nItem, 1, ltoa(nStart, buffer, 10));
			m_List.SetItemText(nItem, 3, ltoa(nEnd, buffer, 10));
			m_List.SetItemText(nItem, 4, ltoa(nAmount, buffer, 10));

			nItem++;
			pRs.MoveNext();
		}
	}

	for(int i = nItem; i < 20; i++)
		m_List.InsertItem(i, ltoa(i, buffer,10));

	m_List.ResetDirtyFlag();

	return TRUE;
}


BOOL CChargeSectionTypeDlg::CheckData()
{
	try
	{
		long nFrontStartKm, nFrontDestKm, nFrontAmount;
		nFrontStartKm = nFrontDestKm = nFrontAmount = 0;
		long nStartKm, nDestKm, nAmount;
		nStartKm = nDestKm = nAmount = 0;


		CString strError, sStartKm, sDestKm, sAmount = "", sTempAmount = "";

		if(m_List.GetItemCount() <= 0)
			throw("최소 한행 이상 입력바랍니다.");


		for(int i = 0; i< m_List.GetItemCount(); i++)
		{		
			sStartKm = m_List.GetItemText(i,1);
			sDestKm  = m_List.GetItemText(i,3);
			sAmount = m_List.GetItemText(i,4);

			sStartKm.Replace(",","");
			sDestKm.Replace(",","");
			sAmount.Replace(",","");


			nStartKm = atoi(sStartKm);
			nDestKm = atoi(sDestKm);
			nAmount = atoi(sAmount);

			if(nDestKm == 0)
				return TRUE;

			sTempAmount = sAmount;
			sTempAmount.Replace("-", "");
			if(!IsStringDigit(sStartKm) ||!IsStringDigit(sDestKm)||!IsStringDigit(sTempAmount) )
			{
				strError.Format("%d번째 행의 데이터에 숫자를 기입하세요", i);
				throw(strError);
			}


			if(i == 0){
				if( nDestKm <= 0 )
				{
					strError.Format("0번째 행의 데이터에 끝요금및 값이 0 이면 안됩니다.");
					throw(strError);
				}
			}
			else			
			{

				if(nStartKm <= 0 || nDestKm <= 0 )
				{	
					if(m_List.GetItemText(i,1).GetLength() == 0 && 
						m_List.GetItemText(i,3).GetLength() == 0 &&
						m_List.GetItemText(i,4).GetLength() == 0)
						continue;
					else
					{
						strError.Format("%d 행에 시작요금, 끝요금, 값중에 데이터가 0으로 되어있습니다.\n\n "\
							"0값을 삭제하여 주세요", i);
						throw(strError);					
					}
				}
				if(nStartKm >= nDestKm)
				{
					strError.Format("%d번째행 끝나는 요금이 시작되는 요금과 같거나 작습니다.", i);
					throw(strError);					
				}

				if(nFrontStartKm > nStartKm || nFrontDestKm >= nStartKm)
				{
					strError.Format("%d번째행 시작요금이 이전행보다 같거나 작습니다.", i);
					throw(strError);					
				}

				if(nFrontDestKm >= nDestKm || nFrontDestKm > nStartKm)
				{
					strError.Format("%d번째행 도착요금이 이전행보다 같거나 작습니다.", i);
					throw(strError);					
				}
			}

			nFrontStartKm = nStartKm;
			nFrontDestKm = nDestKm;
		}
		return TRUE;
	}
	catch(CString strMsg)
	{
		MessageBox(strMsg,"확인",MB_ICONINFORMATION);
		return FALSE;
	}
}


BOOL CChargeSectionTypeDlg::SaveData()
{
	UpdateData();
	if(!CheckData())  
		return FALSE;

	if(m_nCompany <= 0 )
	{
		MessageBox("회사설정이 올바르지 않습니다.", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	for(int i = 0; i < m_List.GetItemCount(); i++)
	{
		CString strStart = m_List.GetItemText(i, 1);
		CString strEnd = m_List.GetItemText(i, 3);
		CString strAmount = m_List.GetItemText(i, 4);

		strStart.Replace(",", "");
		strEnd.Replace(",", "");
		strAmount.Replace(",", "");

		if(atol(strEnd) == 0)
			break;

		CMkCommand pCmd(m_pMkDb, "update_charge_section_type4");
		pCmd.AddParameter(m_nCompany);
		pCmd.AddParameter(m_nValueType);
		pCmd.AddParameter(m_cmbTypeName.GetCurSel());
		pCmd.AddParameter(i);
		pCmd.AddParameter(atol(strStart));
		pCmd.AddParameter(atol(strEnd));
		pCmd.AddParameter(atol(strAmount));
		

		if(!pCmd.Execute())
		{
			MessageBox("업데이트 과정에서 에러가 발생했습니다.\n재시도 바랍니다.\n", 
				"확인", MB_ICONEXCLAMATION);
			return FALSE;
		}
	}

	MessageBox("정상적으로 등록되었습니다. 본인자리에서는 업데이트 되었지만\n\r다른접수자는 재로그인을 해야 합니다. ", "확인", MB_ICONINFORMATION);
	LU->MakeChargeSectionType();
	m_List.ResetDirtyFlag();
	return TRUE;
}


void CChargeSectionTypeDlg::OnBnClickedAddRowBtn()
{
	char buffer[10];
	int nItem = m_List.GetSelectionMark();
	if(nItem > 0)
		m_List.InsertItem(nItem, itoa(nItem,buffer,10) );
	else
		m_List.InsertItem(m_List.GetItemCount(),"");


	int nCount = m_List.GetItemCount() - 1;
	for(int i = 0; i < 20; i++)
	{
		if(i > nCount)
			m_List.InsertItem(i,itoa(i, buffer,10));
		else
			m_List.SetItemText(i,0,itoa(i,buffer,10));
	}
}

void CChargeSectionTypeDlg::OnOK()
{
	SaveData();
}

void CChargeSectionTypeDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}

void CChargeSectionTypeDlg::OnCbnSelchangeTypeCombo()
{
	if(m_List.GetDirtyFlag())
	{
		if(IDYES == MessageBox("현재 타입에 변경내용을 저장하시겠습니까?", "변경 내용저장", MB_YESNO))
		{
			if(!SaveData())
				return;
		}
	}

	RefreshList();
}

void CChargeSectionTypeDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}
