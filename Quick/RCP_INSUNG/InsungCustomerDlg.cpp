// InsungCustomerDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "InsungCustomerDlg.h"
#include "SearchDongInsungJibunDlg.h"
#include "POIDataNew.h"
#include "RcpInsungDlg.h"
#include "AddPhoneDlg.h"
#include "RcpDlgMapDlg.h"
#include "RcpDlg.h"

typedef struct{
	int nCompany;
	int nWNo;
	CString strWName;
}SALES_SIMPLE_INFO2;
// CInsungCustomerDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CInsungCustomerDlg, CDialog)

CInsungCustomerDlg::CInsungCustomerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInsungCustomerDlg::IDD, pParent)
{
	m_nCNo = 0;
	m_nCompany = 0;
	m_strPhone = "";
	m_nDongID = 0;
	m_nSalesWNo = 0;
	m_nSalesCompany = 0;
}


CInsungCustomerDlg::~CInsungCustomerDlg()
{
}

void CInsungCustomerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ID_STATIC, m_stcID);
	DDX_Control(pDX, IDC_NAME_STATIC, m_stcName);
	DDX_Control(pDX, IDC_PHONE1_STATIC, m_stcPhone1);
	DDX_Control(pDX, IDC_PHONE2_STATIC, m_stcPhone2);
	DDX_Control(pDX, IDC_DEPART_STATIC, m_stcDepart);
	DDX_Control(pDX, IDC_MANAGER_STATIC, m_stcManager);
	DDX_Control(pDX, IDC_DONG_STATIC, m_stcDong);
	DDX_Control(pDX, IDC_LOCATION_STATIC, m_stcLocation);
	DDX_Control(pDX, IDC_RIDER_MEMO_STATIC, m_stcRiderMemo);
	DDX_Control(pDX, IDC_MEMO_STATIC, m_stcMemo);
	DDX_Control(pDX, IDC_PAY_TYPE_STATIC, m_stcPayTpye);
	DDX_Control(pDX, IDC_CHARGE_TYPE_STATIC, m_stcChargeType);
	DDX_Control(pDX, IDC_DISCOUNT_STATIC, m_stcDiscount);
	DDX_Control(pDX, IDC_DISCOUNT_STATIC1, m_stcDiscount1);
	DDX_Control(pDX, IDC_MILAEGE_STATIC, m_stcMileage);
	DDX_Control(pDX, IDC_MILAEGE_STATIC1, m_stcMileage1);
	DDX_Control(pDX, IDC_ENTER_STATIC, m_stcEnter);
	DDX_Control(pDX, IDC_SALES_STATIC, m_stcSales);
	DDX_Control(pDX, IDC_INTER_NET_ID_STATIC, m_stcInterNetID);
	DDX_Control(pDX, IDC_INTER_NET_PW_STATIC, m_stcInterNerPw);
	DDX_Control(pDX, IDC_EMAIL_STATIC, m_stcEMail);
	DDX_Control(pDX, IDC_FAX_STATIC, m_stcFax);
	DDX_Control(pDX, IDC_HELP_STATIC1, m_stcHelp);

	DDX_Control(pDX, IDC_ID_EDIT, m_edtID);
	DDX_Control(pDX, IDC_NAME_EDIT, m_edtName);
	DDX_Control(pDX, IDC_PHONE1_EDIT, m_edtPhone1);
	DDX_Control(pDX, IDC_PHONE2_EDIT, m_edtPhone2);
	DDX_Control(pDX, IDC_DEPART_EDIT, m_edtDepart);
	DDX_Control(pDX, IDC_MANAGER_EDIT, m_edtManager);
	DDX_Control(pDX, IDC_DONG_EDIT, m_edtDong);
	DDX_Control(pDX, IDC_ADDRESS_EDIT, m_edtAddress);
	DDX_Control(pDX, IDC_LOCATION_EDIT, m_edtLocation);
	DDX_Control(pDX, IDC_RIDER_MEMO_EDIT, m_edtRiderMemo);
	DDX_Control(pDX, IDC_MEMO_EDIT, m_edtMemo);
	DDX_Control(pDX, IDC_PAY_TYPE_0_RADIO, m_rdoPayTpye0);
	DDX_Control(pDX, IDC_PAY_TYPE_1_RADIO, m_rdoPayTpye1);
	DDX_Control(pDX, IDC_PAY_TYPE_2_RADIO, m_rdoPayTpye2);
	DDX_Control(pDX, IDC_PAY_TYPE_3_RADIO, m_rdoPayTpye3);
	DDX_Control(pDX, IDC_CHARGE_TYPE_COMBO, m_cmbChargeType);
	DDX_Control(pDX, IDC_DISCOUNT_0_RADIO, m_rdoDiscount0);
	DDX_Control(pDX, IDC_DISCOUNT_1_RADIO, m_rdoDiscount1);
	DDX_Control(pDX, IDC_DISCOUNT_EDIT, m_edtDiscount);
	DDX_Control(pDX, IDC_DISCOUNT_COMBO, m_cmbDiscount);
	DDX_Control(pDX, IDC_MILEAGE_COMBO, m_cmbMileage);
	DDX_Control(pDX, IDC_MILEAGE_EDIT, m_edtMileage);
	DDX_Control(pDX, IDC_CUR_MILEAGE_EDIT, m_edtCurMileage);
	DDX_Control(pDX, IDC_ENTER_EDIT, m_edtEnter);
	DDX_Control(pDX, IDC_SALES_COMBO, m_cmbSales);
	DDX_Control(pDX, IDC_INTER_NET_ID_EDIT, m_edtInterNetID);
	DDX_Control(pDX, IDC_INTER_NET_PW_EDIT, m_edtInterNetPw);
	DDX_Control(pDX, IDC_EMAIL_EDIT, m_edtEMail);
	DDX_Control(pDX, IDC_FAX_EDIT, m_edtFax);


	DDX_Control(pDX, IDC_TEL_LIST, m_lstTel);

	DDX_Control(pDX, IDC_AUTO_SHARE_ORDER_CHECK, m_chkAutoShareOrder);
	DDX_Control(pDX, IDC_WNAME_STATIC, m_stcWName);
	DDX_Control(pDX, IDC_OTHER_STATIC, m_stcOther);
	DDX_Control(pDX, IDC_PARTENR_STATIC, m_stcPatener);
	DDX_Control(pDX, IDC_USE_STATIC, m_stcUse);
	DDX_Control(pDX, IDC_SEND_STATE_CHANGE_SMS_CHECK, m_chkSendStateChangeSMS);
}


BEGIN_MESSAGE_MAP(CInsungCustomerDlg, CDialog)
	ON_BN_CLICKED(IDC_ADD_PHONE_BTN, &CInsungCustomerDlg::OnBnClickedAddPhoneBtn)
	ON_BN_CLICKED(IDC_SAVE_BTN, &CInsungCustomerDlg::OnBnClickedSaveBtn)
	ON_BN_CLICKED(IDC_MILEAGE_BTN, &CInsungCustomerDlg::OnBnClickedMileageBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CInsungCustomerDlg::OnBnClickedCloseBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_TEL_LIST, OnReportItemDblClick)
	ON_BN_CLICKED(IDC_MAP_BTN, &CInsungCustomerDlg::OnBnClickedMapBtn)
	ON_BN_CLICKED(IDC_COPY_CUSTOMER_BTN, &CInsungCustomerDlg::OnBnClickedCopyCustomerBtn)
	ON_BN_CLICKED(IDC_DELETE_PHONE_BTN, &CInsungCustomerDlg::OnBnClickedDeletePhoneBtn)
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CInsungCustomerDlg::OnBnClickedSearchBtn)
END_MESSAGE_MAP()


void CInsungCustomerDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	if(m_nCNo <= 0)
	{
		MessageBox("고객 등록 후 전화번호를 추가하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CXTPGridRecord *pRecord = m_lstTel.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	CAddPhoneDlg dlg;
	dlg.m_nTelID = m_lstTel.GetItemLong(pRecord);
	dlg.m_nCNo = m_nCNo;
	dlg.m_nCompany = m_nCompany;

	if(dlg.DoModal() == IDOK)
		RefreshCustomerPhone();

}
// CInsungCustomerDlg 메시지 처리기입니다.

void CInsungCustomerDlg::OnBnClickedAddPhoneBtn()
{
	if(m_nCNo <= 0)
	{
		MessageBox("고객 등록 후 전화번호를 추가하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CAddPhoneDlg dlg;
	dlg.m_nCNo = m_nCNo;
	dlg.m_nTelID = 0;
	dlg.m_nCompany = m_nCompany;
	
	if(dlg.DoModal() == IDOK)
		RefreshCustomerPhone();
}

BOOL CInsungCustomerDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN)		 
		{		
			if(pMsg->hwnd == m_edtDong.GetSafeHwnd())
			{
				SearchDong();
			} 

			return TRUE;
		}
	}
	else if(pMsg->message == WM_SYSKEYDOWN)
	{
		OnBnClickedSaveBtn();
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CInsungCustomerDlg::SearchDong()
{
	CSearchDongInsungJibunDlg dlg;

	m_edtDong.GetWindowText(dlg.m_strSearch);

	if(dlg.DoModal() == IDOK)
	{
		CPOIUnit *pUnit = m_poiNew.GetDongPOI(dlg.m_nDongID);
		CString strAddress = pUnit->GetFullName() + " " + dlg.m_strJibun;
		strAddress.Trim();

		if(dlg.m_nJibun1 == 0 && dlg.m_nJibun1 == 0)
		{
			m_nDongID = dlg.m_nDongID;			
			m_nPosX = pUnit->m_nPosX;
			m_nPosY = pUnit->m_nPosY;
		}
		else 
		{
			CRcpInsungDlg::GetJibunPos(dlg.m_nDongID, dlg.m_nRoadID, dlg.m_nRoadSubID, dlg.m_nJibun1, dlg.m_nJibun2, m_nPosX, m_nPosY);

			if(m_nPosX > 0 && m_nPosY > 0)
			{			
				m_nDongID = dlg.m_nDongID;
			}
			else
			{
				m_nDongID = dlg.m_nDongID;
				m_nPosX = pUnit->m_nPosX;
				m_nPosY = pUnit->m_nPosY;
			}
		}

		m_edtAddress.SetWindowText(strAddress);
	}
}

BOOL CInsungCustomerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_stcName.SetTextColor(RGB(255, 0, 0));
	m_stcPhone1.SetTextColor(RGB(255, 0, 0));
	m_stcDong.SetTextColor(RGB(255, 0, 0));


	m_lstTel.InsertColumn(0, "NO", LVCFMT_LEFT, 40);
	m_lstTel.InsertColumn(1, "전화번호", LVCFMT_LEFT, 80);
	m_lstTel.InsertColumn(2, "부서명", LVCFMT_LEFT, 80);
	m_lstTel.InsertColumn(3, "담당/직위", LVCFMT_LEFT, 80);
	m_lstTel.SetOrderIndexCol(0);
	m_lstTel.GetPaintManager()->SetColumnStyle(xtpReportColumnFlat); 
	m_lstTel.SetGridColor(RGB(0xF0, 0xF0, 0xF0));
	m_lstTel.Populate();

	if(m_nCNo > 0)
		m_edtID.SetWindowText(LF->GetStringFromLong(m_nCNo));

	FillDataSalesMan();

	m_cmbMileage.SetCurSel(0);
	m_cmbChargeType.SetCurSel(0);
	m_cmbDiscount.SetCurSel(0);
	m_cmbSales.SetCurSel(0);

	if(m_nCNo > 0)
		RefreshCustomer();

	return TRUE;  
}

void CInsungCustomerDlg::RefreshCustomer()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_customer_from_cno");
	cmd.AddParameter(m_nCNo);

	if(!rs.Execute(&cmd))
		return;

	CString strTemp; long nTemp, nTemp1;

	for(int i=0; i<rs.GetRecordCount(); i++) 
	{
		rs.GetFieldValue("sCompany", strTemp); m_edtName.SetWindowText(strTemp);
		rs.GetFieldValue("sDong", strTemp); m_edtDong.SetWindowText(strTemp);
		rs.GetFieldValue("sAddress", strTemp); m_edtAddress.SetWindowText(strTemp);
		rs.GetFieldValue("sLocation", strTemp); m_edtLocation.SetWindowText(strTemp);
		rs.GetFieldValue("sRiderMemo", strTemp); m_edtRiderMemo.SetWindowText(strTemp);
		rs.GetFieldValue("sMemo", strTemp); m_edtMemo.SetWindowText(strTemp);
		rs.GetFieldValue("bCredit", nTemp); SetCreditType(nTemp);
		rs.GetFieldValue("nDiscount", nTemp); 

		if(nTemp > 0)
		{
			m_rdoDiscount0.SetCheck(FALSE);
			m_rdoDiscount1.SetCheck(TRUE);
		}  
		else
		{
			m_rdoDiscount0.SetCheck(TRUE);
			m_rdoDiscount1.SetCheck(FALSE);			
			nTemp = nTemp * -1;
		}

		m_edtDiscount.SetWindowText(LF->GetStringFromLong(nTemp));
		rs.GetFieldValue("nDiscountType", nTemp); m_cmbDiscount.SetCurSel(nTemp == 0 ? 1 : 0);


		rs.GetFieldValue("nMileageType", nTemp); 
		rs.GetFieldValue("nMileageValue", nTemp1); 

		if(nTemp <= 2)  // 개별 마일리지 or 적용안함.
			m_cmbMileage.SetCurSel(nTemp);
		else
			m_cmbMileage.SetCurSel(3);  // 10 마일리지 개별적용 안함

		if(nTemp == 0 || nTemp == 10)
			m_edtMileage.SetWindowText("");
		else
			m_edtMileage.SetWindowText(LF->GetMyNumberFormat(nTemp1));;

		rs.GetFieldValue("nMileageBalance", nTemp); m_edtCurMileage.SetWindowText(LF->GetMyNumberFormat(nTemp));
		rs.GetFieldValue("nSalesCompany", m_nSalesCompany); m_edtCurMileage.SetWindowText(LF->GetMyNumberFormat(nTemp));
		rs.GetFieldValue("nSalesWNo", m_nSalesWNo); m_edtCurMileage.SetWindowText(LF->GetMyNumberFormat(nTemp));
		
		FindSalesMan();

		rs.GetFieldValue("sLoginID", strTemp); m_edtInterNetID.SetWindowText(strTemp);
		rs.GetFieldValue("sLoginPW", strTemp); m_edtInterNetPw.SetWindowText(strTemp);
		rs.GetFieldValue("sFax", strTemp); m_edtFax.SetWindowText(strTemp);
		rs.GetFieldValue("sEMail", strTemp); m_edtEMail.SetWindowText(strTemp);
		rs.GetFieldValue("bNotAutoShareOrder", nTemp); m_chkAutoShareOrder.SetCheck(nTemp == 1 ? FALSE : TRUE);
		rs.GetFieldValue("nPriceGrade", nTemp); m_cmbChargeType.SetCurSel(nTemp);

		rs.GetFieldValue("nDongID", m_nDongID); 
		rs.GetFieldValue("nPosX", m_nPosX); 
		rs.GetFieldValue("nPosY", m_nPosY); 

		rs.GetFieldValue("nSendStateChangeSMS", m_nSendStateChangeSMS); 

		m_chkSendStateChangeSMS.SetCheck(m_nSendStateChangeSMS);
	} 

	RefreshCustomerPhone();
}


void CInsungCustomerDlg::DeleteSalesCombo()
{
	for(int i=ZERO; i<m_cmbSales.GetCount(); i++)
	{
		SALES_SIMPLE_INFO2 *pData = (SALES_SIMPLE_INFO2*)m_cmbSales.GetItemData(i);

		if(pData != NULL)
		{
			delete pData;
			pData = NULL;
		}
	}

	m_cmbSales.ResetContent();	
}


void CInsungCustomerDlg::FindSalesMan()
{
	BOOL bFind = FALSE;

	for(int i=ZERO; i<m_cmbSales.GetCount(); i++)
	{
		SALES_SIMPLE_INFO2 *pData = (SALES_SIMPLE_INFO2*)m_cmbSales.GetItemData(i);

		if(pData == NULL)
			continue;

		if(pData->nCompany == m_nSalesCompany &&
			pData->nWNo == m_nSalesWNo)
		{
			bFind = TRUE;
			m_cmbSales.SetCurSel(i);
			break;
		}
	}

	if(bFind == FALSE)
		m_cmbSales.SetCurSel(ZERO);
}

void CInsungCustomerDlg::FillDataSalesMan()
{
	DeleteSalesCombo();

	m_cmbSales.InsertString(0, "없음");

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_wno_sales_team");
	pCmd.AddParameter(m_ci.m_nCompanyCode);

	if(pRs.Execute(&pCmd) == FALSE)
		return;

	CString strTemp;

	for(int i=ZERO; i<pRs.GetRecordCount(); i++)
	{
		SALES_SIMPLE_INFO2 *st = new SALES_SIMPLE_INFO2;

		pRs.GetFieldValue("nCompany", st->nCompany);
		pRs.GetFieldValue("nWNo", st->nWNo);
		pRs.GetFieldValue("sWName", st->strWName);

		strTemp.Format("[%d %s]", st->nWNo, st->strWName);

		m_cmbSales.InsertString(i + ONE, strTemp);
		m_cmbSales.SetItemData(i + ONE, (DWORD_PTR)st);

		pRs.MoveNext();
	}
}

long CInsungCustomerDlg::GetCreditType()
{
	if(m_rdoPayTpye0.GetCheck()) return 0;
	if(m_rdoPayTpye1.GetCheck()) return 1;
	if(m_rdoPayTpye2.GetCheck()) return 2;
	if(m_rdoPayTpye3.GetCheck()) return 3;

	return 0;
}

void CInsungCustomerDlg::SetCreditType(long nType)
{
	if(nType == 0)
	{
		m_rdoPayTpye0.SetCheck(TRUE);
		m_rdoPayTpye1.SetCheck(FALSE);
		m_rdoPayTpye2.SetCheck(FALSE);
		m_rdoPayTpye3.SetCheck(FALSE);
	}
	if(nType == 1)
	{
		m_rdoPayTpye0.SetCheck(FALSE);
		m_rdoPayTpye1.SetCheck(TRUE);
		m_rdoPayTpye2.SetCheck(FALSE);
		m_rdoPayTpye3.SetCheck(FALSE);
	}
	else if(nType == 2)
	{
		m_rdoPayTpye0.SetCheck(FALSE);
		m_rdoPayTpye1.SetCheck(FALSE);
		m_rdoPayTpye2.SetCheck(TRUE);
		m_rdoPayTpye3.SetCheck(FALSE);
	}
	else if(nType == 3)
	{
		m_rdoPayTpye0.SetCheck(FALSE);
		m_rdoPayTpye1.SetCheck(FALSE);
		m_rdoPayTpye2.SetCheck(FALSE);
		m_rdoPayTpye3.SetCheck(TRUE);
	}
};

void CInsungCustomerDlg::RefreshCustomerPhone()
{
	m_lstTel.DeleteAllItems();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_customer_tel_from_cno");
	cmd.AddParameter(m_nCNo);

	if(!rs.Execute(&cmd))
		return;

	CString strTel, strDepart, strManager;
	long nType, nTelID;
	long nCount = 0;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nID", nTelID);
		rs.GetFieldValue("sTel", strTel);
		rs.GetFieldValue("sTelDepart", strDepart);
		rs.GetFieldValue("sTelManager", strManager);
		rs.GetFieldValue("nType", nType);

		if(nType == 2)
		{
			m_edtPhone1.SetWindowText(LF->GetDashPhoneNumber(strTel));
			m_edtDepart.SetWindowText(strDepart);
			m_edtManager.SetWindowText(strManager);
		}
		else if(nType == 3)
		{
			m_edtPhone2.SetWindowText(LF->GetDashPhoneNumber(strTel));
		}
		else
		{
			m_lstTel.InsertItem(nCount, "");
			m_lstTel.SetItemText(nCount, 1, LF->GetDashPhoneNumber(strTel));
			m_lstTel.SetItemText(nCount, 2, strDepart);
			m_lstTel.SetItemText(nCount, 3, strManager);
			m_lstTel.SetItemLong(nCount++, nTelID);
		}

		rs.MoveNext();
	}

	m_lstTel.Populate();
}

BOOL CInsungCustomerDlg::CheckItem()
{
	if(m_nDongID < 0)
	{
		MessageBox("동명을 입력하세요", "확인", MB_ICONINFORMATION);
		m_edtDong.SetFocus();
		return FALSE;
	}

	if(m_edtDong.GetWindowTextLength() <= 0)
	{
		MessageBox("동명을 입력하세요", "확인", MB_ICONINFORMATION);
		m_edtDong.SetFocus();
		return FALSE;
	}

	if(m_edtName.GetWindowTextLength() <= 0)
	{
		MessageBox("고객명을 입력하세요", "확인", MB_ICONINFORMATION);
		m_edtName.SetFocus();
		return FALSE;
	}
	if(m_edtPhone1.GetWindowTextLength() <= 0)
	{
		MessageBox("전화번호1을 입력하세요", "확인", MB_ICONINFORMATION);
		m_edtPhone1.SetFocus();
		return FALSE;
	}

	return TRUE;	
}

void CInsungCustomerDlg::OnBnClickedSaveBtn()
{
	if(!CheckItem())
		return;

	if(m_nCNo > 0)
		UpdateCustomer();
	else
		InsertCustomer();

}

void CInsungCustomerDlg::InsertCustomer()
{
	if(MessageBox("변경/입력된자료가 있습니다. 저장 하시겠습니까?", "확인", MB_OKCANCEL) != IDOK)
		return;

	CMkCommand cmd(m_pMkDb, "insert_customer_like_insung");
	cmd.AddParameter(m_nCompany);
	CString strPhone1 = LF->GetStringFromEdit(&m_edtPhone1);
	strPhone1 = LF->GetNoneDashNumberRemoveDDD(strPhone1);
	CString strPhone2 = LF->GetStringFromEdit(&m_edtPhone2);
	strPhone2 = LF->GetNoneDashNumberRemoveDDD(strPhone2);
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtName));
	cmd.AddParameter(strPhone1);
	cmd.AddParameter(strPhone2);

	cmd.AddParameter(LF->GetStringFromEdit(&m_edtDepart));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtManager));
	cmd.AddParameter(m_nDongID);
	cmd.AddParameter(m_nPosX);
	cmd.AddParameter(m_nPosY);
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtDong));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtAddress));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtLocation));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtRiderMemo));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtMemo));
	cmd.AddParameter(GetCreditType());
	cmd.AddParameter(m_cmbChargeType.GetCurSel());

	long nDiscount = atoi(LF->GetStringFromEdit(&m_edtDiscount));

	if(m_rdoDiscount0.GetCheck())
		nDiscount = nDiscount * -1;

	cmd.AddParameter(nDiscount);
	cmd.AddParameter(m_cmbDiscount.GetCurSel());
	cmd.AddParameter(atoi(LF->GetStringFromEdit(&m_edtMileage)));
	cmd.AddParameter(m_cmbMileage.GetCurSel());
	cmd.AddParameter(m_nSalesWNo);
	cmd.AddParameter(m_nSalesCompany);
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtInterNetID));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtInterNetPw));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtEMail));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtFax));
	cmd.AddParameter(!m_chkAutoShareOrder.GetCheck());
	CMkParameter *pParCNo = cmd.AddParameter(0, typeOutput);
	CMkParameter *pParTelID = cmd.AddParameter(0, typeOutput);

	if(cmd.Execute())
	{
		pParCNo->GetValue(m_nCNo);
		pParTelID->GetValue(m_nTelID);

		GetParent()->SendMessage(WM_INSUNG_CUSTOMER_OK, m_nCNo, m_nTelID);
		ShowWindow(FALSE);
		
		//OnOK();
	}
}

void CInsungCustomerDlg::UpdateCustomer()
{
	if(MessageBox("변경/입력된자료가 있습니다. 저장 하시겠습니까?", "확인", MB_OKCANCEL) != IDOK)
		return;

	CString strPhone1 = LF->GetStringFromEdit(&m_edtPhone1);
	strPhone1 = LF->GetNoneDashNumberRemoveDDD(strPhone1);
	CString strPhone2 = LF->GetStringFromEdit(&m_edtPhone2);
	strPhone2 = LF->GetNoneDashNumberRemoveDDD(strPhone2);

	CMkCommand cmd(m_pMkDb, "update_customer_like_insung_1");
	cmd.AddParameter(m_nCNo);
	cmd.AddParameter(m_nCompany);
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtName));
	cmd.AddParameter(strPhone1);
	cmd.AddParameter(strPhone2);

	cmd.AddParameter(LF->GetStringFromEdit(&m_edtDepart));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtManager));
	cmd.AddParameter(m_nDongID);
	cmd.AddParameter(m_nPosX);
	cmd.AddParameter(m_nPosY);
	cmd.AddParameter(m_chkSendStateChangeSMS.GetCheck());
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtDong));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtAddress));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtLocation));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtRiderMemo));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtMemo));
	cmd.AddParameter(GetCreditType());
	cmd.AddParameter(m_cmbChargeType.GetCurSel());

	long nDiscount = atoi(LF->GetStringFromEdit(&m_edtDiscount));

	if(m_rdoDiscount0.GetCheck())
		nDiscount = nDiscount * -1;

	cmd.AddParameter(nDiscount);
	cmd.AddParameter(m_cmbDiscount.GetCurSel());
	cmd.AddParameter(atoi(LF->GetStringFromEdit(&m_edtMileage)));
	cmd.AddParameter(m_cmbMileage.GetCurSel());
	cmd.AddParameter(m_nSalesWNo);
	cmd.AddParameter(m_nSalesCompany);
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtInterNetID));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtInterNetPw));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtEMail));
	cmd.AddParameter(LF->GetStringFromEdit(&m_edtFax));
	cmd.AddParameter(!m_chkAutoShareOrder.GetCheck());

	if(cmd.Execute())
	{
		GetParent()->SendMessage(WM_INSUNG_CUSTOMER_OK, m_nCNo, m_nTelID);
		ShowWindow(FALSE);
		//OnOK();
	}
}

void CInsungCustomerDlg::OnBnClickedMileageBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CInsungCustomerDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}

void CInsungCustomerDlg::OnBnClickedMapBtn()
{
	if(m_nPosX <= 0 || m_nPosY <= 0)
	{
		MessageBox("위치정보가 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CString strAddress;
	m_edtAddress.GetWindowText(strAddress);

	CRcpDlgMapDlg *pRcpDlgMapDlg = LU->GetRcpDlgMap((CRcpDlg*)GetParent());
	pRcpDlgMapDlg->m_bFromCustomerDlg = FALSE;
	CLogiMapNew *pLogiMap = pRcpDlgMapDlg->GetMap();
	pLogiMap->ClearAllLayer();
	pLogiMap->AddPointPOI(TRUE, CString("[" + strAddress + "]") + strAddress, m_nPosX, m_nPosY, strAddress);
	pRcpDlgMapDlg->ShowWindow(SW_SHOW);

}

void CInsungCustomerDlg::OnBnClickedCopyCustomerBtn()
{
	m_nCNo = 0;
	m_nTelID = 0;
	m_edtID.SetWindowText("");
	m_lstTel.DeleteAllItems(); 
	m_lstTel.Populate();
}

void CInsungCustomerDlg::OnBnClickedDeletePhoneBtn()
{
	CXTPGridRecord *pRecord = m_lstTel.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	long nTelID = m_lstTel.GetItemLong(pRecord);

	CMkCommand cmd(m_pMkDb, "delete_customer_tel");
	cmd.AddParameter(nTelID);

	if(cmd.Execute())
		RefreshCustomerPhone();
}

void CInsungCustomerDlg::OnBnClickedSearchBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
