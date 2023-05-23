// OrderSeeDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "OrderSeeDlg.h"
#include "WebGroupReportDlg.h"
#include "ColumnSelDlg.h"
// COrderSeeDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(COrderSeeDlg, CMyDialog)
COrderSeeDlg::COrderSeeDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(COrderSeeDlg::IDD, pParent)
{
}

COrderSeeDlg::~COrderSeeDlg()
{
}

void COrderSeeDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_lstReport);
	DDX_Control(pDX, IDC_STATIC1, m_stcDiscount);
	DDX_Control(pDX, IDC_ADD_TAX_APPLY_TYPE_COMBO, m_cmbAddTaxApplyType);
	DDX_Control(pDX, IDC_CASH_APPLY_CHECK, m_chkCashApply);
	DDX_Control(pDX, IDC_CREDIT_APPLY_CHECK, m_chkCreditApply);
	DDX_Control(pDX, IDC_ONLINE_APPLY_CHECK, m_chkOnlineApply);
	DDX_Control(pDX, IDC_TRANS_APPLY_CHECK, m_chkTransApply);
}


BEGIN_MESSAGE_MAP(COrderSeeDlg, CMyDialog)
	ON_BN_CLICKED(ID_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_BN_CLICKED(ID_PRINT_BTN, OnBnClickedPrintBtn)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnExcel)
	ON_NOTIFY(NM_RCLICK, IDC_REPORT, OnReportItemRClick)
	ON_COMMAND(ID_VISIBLE_COL, OnVisibleCol)
END_MESSAGE_MAP()


// COrderSeeDlg �޽��� ó�����Դϴ�.

BOOL COrderSeeDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
 
	CenterWindow();
	this->SetWindowText(m_cg.GetGroupData(m_nGNo)->strGroupName + "/" + m_cg.GetGroupData(m_nGNo)->strDept + " [" + m_strDate + "]");

	m_lstReport.InsertColumn(0, "������ȣ", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(1, "������¥", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(2, "���ֻ�", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(3, "����", LVCFMT_CENTER, 40);
	m_lstReport.InsertColumn(4, "�Ƿ���", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(5, "�����", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(6, "��ȭ��ȣ", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(7, "�����", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(8, "���", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(9, "�μ�", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(10, "��ȭ��ȣ", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(11, "������", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(12, "���", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(13, "�μ�", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(14, "��ȭ��ȣ", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(15, "�Աݹ��", LVCFMT_CENTER, 60);
	m_lstReport.InsertColumn(16, "�⺻", LVCFMT_RIGHT, 55);
	m_lstReport.InsertColumn(17, "�߰�", LVCFMT_RIGHT, 55);
	m_lstReport.InsertColumn(18, "����", LVCFMT_RIGHT, 55); 
	m_lstReport.InsertColumn(19, "�հ�", LVCFMT_RIGHT, 55);
	m_lstReport.InsertColumn(20, "���ξ�", LVCFMT_RIGHT, 55);
	m_lstReport.InsertColumn(21, "Ź��", LVCFMT_RIGHT, 55);
	m_lstReport.InsertColumn(22, "�ΰ���", LVCFMT_RIGHT, 55);
	m_lstReport.InsertColumn(23, "���", LVCFMT_RIGHT, 55);
	m_lstReport.InsertColumn(24, "����", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(25, "����", LVCFMT_CENTER, 40);
	m_lstReport.InsertColumn(26, "�պ�", LVCFMT_CENTER, 40);
	m_lstReport.InsertColumn(27, "���", LVCFMT_CENTER, 40);
	m_lstReport.InsertColumn(28, "����", LVCFMT_CENTER, 40);
	m_lstReport.InsertColumn(29, "CID", LVCFMT_CENTER, 80);
	m_lstReport.InsertColumn(30, "����", LVCFMT_CENTER, 150);

	
	/*
	CXTPGridColumn* pCol0 = m_lstReport.AddColumn(new CXTPGridColumn(0, _T("������ȣ"), 70, FALSE));
	CXTPGridColumn* pCol1 = m_lstReport.AddColumn(new CXTPGridColumn(1, _T("������¥"), 80, FALSE));
	CXTPGridColumn* pCol2 = m_lstReport.AddColumn(new CXTPGridColumn(2, _T("���ֻ�"), 100, FALSE));
	CXTPGridColumn* pCol3 = m_lstReport.AddColumn(new CXTPGridColumn(3, _T("����"), 75, FALSE));
	CXTPGridColumn* pCol4 = m_lstReport.AddColumn(new CXTPGridColumn(4, _T("�Ƿ���"), 90, FALSE));
	CXTPGridColumn* pCol5 = m_lstReport.AddColumn(new CXTPGridColumn(5, _T("��ߵ�"), 90, FALSE));
	CXTPGridColumn* pCol6 = m_lstReport.AddColumn(new CXTPGridColumn(6, _T("������"), 90, FALSE));
	CXTPGridColumn* pCol7 = m_lstReport.AddColumn(new CXTPGridColumn(7, _T("�Աݹ��"), 60, FALSE));
	CXTPGridColumn* pCol8 = m_lstReport.AddColumn(new CXTPGridColumn(8, _T("�ݾ�"), 70, FALSE));
	CXTPGridColumn* pCol9 = m_lstReport.AddColumn(new CXTPGridColumn(9, _T("���ξ�"), 70, FALSE));
	CXTPGridColumn* pCol10 = m_lstReport.AddColumn(new CXTPGridColumn(10, _T("Ź��"), 70, FALSE));
	CXTPGridColumn* pCol11 = m_lstReport.AddColumn(new CXTPGridColumn(11, _T("�ΰ���"), 70, FALSE));
	*/
	
	m_lstReport.Populate();
	m_lstReport.LoadReportOrder("COrderSeeDlg", "m_lstReport");
	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void COrderSeeDlg::OnBnClickedRefreshBtn()
{
	m_lstReport.SaveReportOrder("COrderSeeDlg", "m_lstReport");
	RefreshList();
}

void COrderSeeDlg::OnBnClickedPrintBtn()
{
	char buffer[20];
	CWebGroupReportDlg dlg;

	dlg.m_strGNo.Add(_itoa(m_nGNo, buffer, 10));
	dlg.m_strID.Add(_itoa(m_nID, buffer, 10));
	dlg.m_strTitle.Add(m_cg.GetGroupData(m_nGNo)->strGroupName + " [" + m_strDate + "]");

	dlg.m_nCount = 1; 

	dlg.DoModal();
}

void COrderSeeDlg::RefreshList()
{
	m_lstReport.DeleteAllItems();  
 
	long nDiscount, nAddTaxApplyType;
	BOOL bCashApply, bCreditApply, bOnlineApply, bTransApply;
	long nCashCharge, nCreditCharge, nOnlineCharge, nTransCharge;
	long nCashTax, nCreditTax, nOnlineTax, nTransTax;
	long nBillCollection, nUnBillCollection;
	long nChargeBasicS = 0, nChargeAddS = 0, nChargeDisS = 0, nChargeSumS = 0;
	long nChargeDiscountS = 0, nChargeTranS = 0, nTaxS = 0;
	
	CMkRecordset pRs(m_pMkDb);
 
	CMkCommand pCmd(m_pMkDb, "select_group_report_order_7");
	pCmd.AddParameter(m_nID);
	CMkParameter *pDiscount = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *pAddTaxApplyType = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *pCashApply = pCmd.AddParameter(typeLong, typeOutput, sizeof(BOOL), 0);
	CMkParameter *pCreditApply = pCmd.AddParameter(typeLong, typeOutput, sizeof(BOOL), 0);
	CMkParameter *pOnlineApply = pCmd.AddParameter(typeLong, typeOutput, sizeof(BOOL), 0);
	CMkParameter *pTransApply = pCmd.AddParameter(typeLong, typeOutput, sizeof(BOOL), 0);
	CMkParameter *pCashCharge = pCmd.AddParameter(typeLong, typeOutput, sizeof(BOOL), 0);
	CMkParameter *pCreditCharge = pCmd.AddParameter(typeLong, typeOutput, sizeof(BOOL), 0);
	CMkParameter *pOnlineCharge = pCmd.AddParameter(typeLong, typeOutput, sizeof(BOOL), 0);
	CMkParameter *pTransCharge = pCmd.AddParameter(typeLong, typeOutput, sizeof(BOOL), 0);
	CMkParameter *pCashTax = pCmd.AddParameter(typeLong, typeOutput, sizeof(BOOL), 0);
	CMkParameter *pCreditTax = pCmd.AddParameter(typeLong, typeOutput, sizeof(BOOL), 0);
	CMkParameter *pOnlineTax = pCmd.AddParameter(typeLong, typeOutput, sizeof(BOOL), 0);
	CMkParameter *pTransTax = pCmd.AddParameter(typeLong, typeOutput, sizeof(BOOL), 0);
	CMkParameter *pBillCollection = pCmd.AddParameter(typeLong, typeOutput, sizeof(BOOL), 0);
	CMkParameter *pUnBillCollection = pCmd.AddParameter(typeLong, typeOutput, sizeof(BOOL), 0);

	if(!pRs.Execute(&pCmd)) return;
	if(pRs.GetRecordCount() == 0) return;

	pDiscount->GetValue(nDiscount);
	pAddTaxApplyType->GetValue(nAddTaxApplyType);
	pCashApply->GetValue(bCashApply);
	pCreditApply->GetValue(bCreditApply);
	pOnlineApply->GetValue(bOnlineApply);
	pTransApply->GetValue(bTransApply);
	pCashCharge->GetValue(nCashCharge);
	pCreditCharge->GetValue(nCreditCharge);
	pOnlineCharge->GetValue(nOnlineCharge);
	pTransCharge->GetValue(nTransCharge);
	pCashTax->GetValue(nCashTax);
	pCreditTax->GetValue(nCreditTax);
	pOnlineTax->GetValue(nOnlineTax);
	pTransTax->GetValue(nTransTax);
	pBillCollection->GetValue(nBillCollection);
	pUnBillCollection->GetValue(nUnBillCollection);

	BOOL bApply[4] = {bCashApply, bCreditApply, bOnlineApply, bTransApply};

	CString sDiscount;
	sDiscount.Format("���η� %d%%����", nDiscount);
	m_stcDiscount.SetWindowText(sDiscount);

	m_cmbAddTaxApplyType.SetCurSel(nAddTaxApplyType);
	m_chkCashApply.SetCheck(bCashApply);
	m_chkCreditApply.SetCheck(bCreditApply);
	m_chkOnlineApply.SetCheck(bOnlineApply);
	m_chkTransApply.SetCheck(bTransApply);

	long nTNo, nCompany, nPayType, nChargeSum, nChargeTrans, nState, nDiscountCharge, nSignType;
	COleDateTime dt1;
	CString strOName, strSDong, strDDong, strOManager, sRName, strSName, strDName;
	char buffer[20];
	long nTax = 0, nRNo;
	long nTempPayType = 0, nChargeBasic, nChargeDis, nChargeAdd;
	long nChargeTransS, nDiscountChargeS;
	nChargeSumS = nChargeTransS = nDiscountChargeS = 0;
	CString strOPhone, strOMobile, strSPhone, strSMobile, strDPhone, strDMobile;
	CString strSManager, strDManager, strSDepart, strDDepart, strCID, strEtc;
	long nWayType, nRunType, nCarType;
	int nItem = 0;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		nTax = 0;

		pRs.GetFieldValue("nTNo", nTNo);
		pRs.GetFieldValue("dt1", dt1);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("sOName", strOName);
		pRs.GetFieldValue("sSDong", strSDong); 
		pRs.GetFieldValue("sDDong", strDDong);
		pRs.GetFieldValue("nPayType", nPayType);
		pRs.GetFieldValue("nChargeSum", nChargeSum);
		pRs.GetFieldValue("nChargeTrans", nChargeTrans);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("sOManager", strOManager);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sRName", sRName);
		pRs.GetFieldValue("nSignType", nSignType);
		pRs.GetFieldValue("sSName", strSName);
		pRs.GetFieldValue("sDName", strDName);
		pRs.GetFieldValue("sOPhone", strOPhone);
		pRs.GetFieldValue("sOMobile", strOMobile);
		pRs.GetFieldValue("sSPhone", strSPhone);
		pRs.GetFieldValue("sSMobile", strSMobile);
		pRs.GetFieldValue("sDPhone", strDPhone);
		pRs.GetFieldValue("sDMobile", strDMobile);
		pRs.GetFieldValue("sSManager", strSManager);
		pRs.GetFieldValue("sDManager", strDManager);
		pRs.GetFieldValue("nChargeBasic", nChargeBasic);
		pRs.GetFieldValue("nChargeAdd", nChargeAdd);
		pRs.GetFieldValue("nChargeDis", nChargeDis);
		pRs.GetFieldValue("nWayType", nWayType);
		pRs.GetFieldValue("nRunType", nRunType);
		pRs.GetFieldValue("nCarType", nCarType);
		pRs.GetFieldValue("sSDepart", strSDepart);
		pRs.GetFieldValue("sDDepart", strDDepart);
		pRs.GetFieldValue("sCID", strCID);
		pRs.GetFieldValue("sEtc", strEtc);

		if(m_cg.GetGroupData(m_nGNo)->bNotShowCash) 
		{
			if((nPayType == 0) || (nPayType == 1) || (nPayType == 4))
			{
				pRs.MoveNext();
				continue;
			}
		}

		m_lstReport.InsertItem(nItem, itoa(nTNo, buffer, 10));
		m_lstReport.SetItemText(nItem, 1, dt1.Format("%m-%d %H:%M"));
		m_lstReport.SetItemText(nItem, 2, m_ci.GetName(nCompany));
		m_lstReport.SetItemText(nItem, 3, LF->GetStateString(nState));
		m_lstReport.SetItemText(nItem, 4, strOName);
		m_lstReport.SetItemText(nItem, 5, strOManager);
		m_lstReport.SetItemText(nItem, 6, LF->GetTwoPhone(strOPhone, strOMobile));

		m_lstReport.SetItemText(nItem, 7, strSName == strSDong ? strSName : strSName + "(" + strSDong + ")");
		m_lstReport.SetItemText(nItem, 8, strSManager);
		m_lstReport.SetItemText(nItem, 9, strSDepart);
		m_lstReport.SetItemText(nItem, 10, LF->GetTwoPhone(strSPhone, strSMobile));

		m_lstReport.SetItemText(nItem, 11, strDName == strDDong ? strDName : strDName + "(" + strDDong + ")");
		m_lstReport.SetItemText(nItem, 12, strDManager);
		m_lstReport.SetItemText(nItem, 13, strDDepart);
		m_lstReport.SetItemText(nItem, 14, LF->GetTwoPhone(strDPhone, strDMobile));

		if(nPayType == 2 || nPayType == 3 || nPayType == 7)
			m_lstReport.SetItemText(nItem, 15, LF->GetPayTypeFromLong(nPayType) + "r");
		else
			m_lstReport.SetItemText(nItem, 15, LF->GetPayTypeFromLong(nPayType));

		m_lstReport.SetItemText(nItem, 16, LF->GetMyNumberFormat(nChargeBasic));
		m_lstReport.SetItemText(nItem, 17, LF->GetMyNumberFormat(nChargeAdd));
		m_lstReport.SetItemText(nItem, 18, LF->GetMyNumberFormat(nChargeDis));
		m_lstReport.SetItemText(nItem, 19, LF->GetMyNumberFormat(nChargeSum));

		nDiscountCharge = nChargeSum - (nChargeSum * 0.01 * nDiscount);

		if(nPayType != 2 && nPayType != 3 && nPayType != 7)
			nDiscountCharge = 0;

		m_lstReport.SetItemText(nItem, 20, LF->GetMyNumberFormat(nDiscountCharge));
		m_lstReport.SetItemText(nItem, 21, LF->GetMyNumberFormat(nChargeTrans));

		switch(nPayType)
		{
			case 0:
			case 1:
			case 4:
				{
					nTempPayType = 0;
					break;
				}
			case 2:
				{
					nTempPayType = 1;
					break;
				}				
			case 3:
				{
					nTempPayType = 2;
					break;
				}				
		} 

		if(bApply[nTempPayType])
		{
			if(nTempPayType == 0)
				nTax += (nChargeSum * 0.1);
			else if(nAddTaxApplyType == 1)
				nTax += (nChargeSum * 0.1);
			else if(nAddTaxApplyType == 2)
				nTax += ((nChargeSum - (nChargeSum * 0.01 * nDiscount)) * 0.1);

		}

		if(bApply[3])
		{
			if(nAddTaxApplyType == 1)
				nTax += (nChargeTrans * 0.1);
		}

		if(nAddTaxApplyType < 1)
			nTax = 0;
	
		m_lstReport.SetItemText(nItem, 22, LF->GetMyNumberFormat(nTax));
 
		/*
		nChargeSumS += nChargeSum;
		nChargeTransS += nChargeTrans;
		nTaxS += nTax;
		nDiscountChargeS += nDiscountCharge;
		*/

		nChargeBasicS += nChargeBasic;
		nChargeAddS += nChargeAdd;
		nChargeDisS += nChargeDis; 
		nChargeSumS += nChargeSum;
		nChargeDiscountS += nDiscountCharge; 
		nChargeTranS += nChargeTrans;
		nTaxS += nTax;

		m_lstReport.SetItemText(nItem, 16, LF->GetMyNumberFormat(nChargeBasic));
		m_lstReport.SetItemText(nItem, 17, LF->GetMyNumberFormat(nChargeAdd));
		m_lstReport.SetItemText(nItem, 18, LF->GetMyNumberFormat(nChargeDis));
		m_lstReport.SetItemText(nItem, 19, LF->GetMyNumberFormat(nChargeSum));
		m_lstReport.SetItemText(nItem, 20, LF->GetMyNumberFormat(nDiscountCharge));
		m_lstReport.SetItemText(nItem, 21, LF->GetMyNumberFormat(nChargeTrans));
		m_lstReport.SetItemText(nItem, 22, LF->GetMyNumberFormat(nTax));

		m_lstReport.SetItemText(nItem, 23, itoa(nRNo, buffer, 10));
		m_lstReport.SetItemText(nItem, 24, sRName);

		if(nSignType == 3)
			m_lstReport.SetItemText(nItem, 25, "��,��");
		else if(nSignType == 1)
			m_lstReport.SetItemText(nItem, 25, "��");
		else if(nSignType == 2)
			m_lstReport.SetItemText(nItem, 25, "��");
		else 
			m_lstReport.SetItemText(nItem, 25, "");

		m_lstReport.SetItemText(nItem, 26, LF->GetWayTypeFromLong(nWayType));
		m_lstReport.SetItemText(nItem, 27, LF->GetRunTypeFromLong(nRunType));
		m_lstReport.SetItemText(nItem, 28, LF->GetCarTypeFromLong(nCarType));
		m_lstReport.SetItemText(nItem, 29, strCID);
		m_lstReport.SetItemText(nItem, 30, strEtc);

		m_lstReport.SetItemNoSort(nItem++, FALSE);
		
		pRs.MoveNext();
	}

	if(nItem == 0) return;

	m_lstReport.InsertItem(nItem, "");
	m_lstReport.SetItemNoSort(nItem++, TRUE);

	m_lstReport.InsertItem(nItem, "");
	m_lstReport.SetItemText(nItem, 16, LF->GetMyNumberFormat(nChargeBasicS));
	m_lstReport.SetItemText(nItem, 17, LF->GetMyNumberFormat(nChargeAddS));
	m_lstReport.SetItemText(nItem, 18, LF->GetMyNumberFormat(nChargeDisS));
	m_lstReport.SetItemText(nItem, 19, LF->GetMyNumberFormat(nChargeSumS));
	m_lstReport.SetItemText(nItem, 20, LF->GetMyNumberFormat(nChargeDiscountS));
	m_lstReport.SetItemText(nItem, 21, LF->GetMyNumberFormat(nChargeTranS));
	m_lstReport.SetItemText(nItem, 22, LF->GetMyNumberFormat(nTaxS));
	m_lstReport.SetItemNoSort(nItem++, TRUE);
  
	m_lstReport.InsertItem(nItem, "");
	m_lstReport.SetItemNoSort(nItem++, TRUE);

	m_lstReport.InsertItem(nItem, "");
	m_lstReport.SetItemText(nItem, 2, "           ����");
	m_lstReport.SetItemText(nItem, 3, "       �ſ�");
	m_lstReport.SetItemText(nItem, 4, "         �۱�");
	m_lstReport.SetItemText(nItem, 5, "          Ź��");
	m_lstReport.SetItemNoSort(nItem++, TRUE);

	m_lstReport.InsertItem(nItem, "");
	m_lstReport.SetItemText(nItem, 1, "                 �ݾ�");
	m_lstReport.SetItemText(nItem, 2, LF->GetMyNumberFormat(nCashCharge));
	m_lstReport.SetItemText(nItem, 3, nDiscount >  0 ? LF->GetMyNumberFormat(nCreditCharge / ((100 - nDiscount) * 0.01)) : 
								LF->GetMyNumberFormat(nCreditCharge));
	m_lstReport.SetItemText(nItem, 4, nDiscount >  0 ? LF->GetMyNumberFormat(nOnlineCharge / ((100 - nDiscount) * 0.01)) : 
								LF->GetMyNumberFormat(nOnlineCharge));
	m_lstReport.SetItemText(nItem, 5, LF->GetMyNumberFormat(nTransCharge)  + "r");
	m_lstReport.SetItemText(nItem, 7, "   �̼���");
	m_lstReport.SetItemText(nItem, 8, "r" + LF->GetMyNumberFormat(nUnBillCollection) + "r");
	m_lstReport.SetItemNoSort(nItem++, TRUE);

	m_lstReport.InsertItem(nItem, "");
	m_lstReport.SetItemText(nItem, 1, "    ������ �ݾ�");
	m_lstReport.SetItemText(nItem, 2, "");
	m_lstReport.SetItemText(nItem, 3, LF->GetMyNumberFormat(nCreditCharge) + "r");
	m_lstReport.SetItemText(nItem, 4, LF->GetMyNumberFormat(nOnlineCharge) + "r");
	m_lstReport.SetItemText(nItem, 5, "");	
	m_lstReport.SetItemText(nItem, 7, "   ���ݾ�");
	m_lstReport.SetItemText(nItem, 8,"r" + LF->GetMyNumberFormat(nBillCollection) + "b");
	m_lstReport.SetItemNoSort(nItem++, TRUE);

	m_lstReport.InsertItem(nItem, "");
	m_lstReport.SetItemText(nItem, 1, "             �ΰ���");
	m_lstReport.SetItemText(nItem, 2, LF->GetMyNumberFormat(nCashTax) + "r");
	m_lstReport.SetItemText(nItem, 3, LF->GetMyNumberFormat(nCreditTax) + "r");
	m_lstReport.SetItemText(nItem, 4, LF->GetMyNumberFormat(nOnlineTax) + "r");
	m_lstReport.SetItemText(nItem, 5, LF->GetMyNumberFormat(nTransTax) + "r");
	m_lstReport.SetItemNoSort(nItem++, TRUE);

	m_lstReport.Populate();

	if(m_lstReport.GetItemCount() > 0)
	m_lstReport.SetSelectedRow(0);
//	m_lstReport.SetFocusedRow();
	//m_lstReport.RedrawControl();
}

void COrderSeeDlg::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_lstReport, pt);
}

void COrderSeeDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CXTPGridColumn *p = m_lstReport.GetColumns()->GetAt(0); 
	if(p == NULL) return; 

	long h = m_lstReport.GetReportHeader()->GetGroupByHeight();

	CRect rcHeader = p->GetRect(); 
	//ScreenToClient(rcHeader);

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu = NULL;

	if(point.y >= rect.top && 
		//point.y <= rect.top + rcHeader.Height())
		point.y <= rect.top + h )
	{
		pRMenu=rMenu.GetSubMenu(22);
	}
	else
		pRMenu=rMenu.GetSubMenu(2);

	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void COrderSeeDlg::OnExcel()
{
	LF->AddSecurityLog(LF->GetCurBranchInfo()->nCompanyCode, 901, m_ui.nWNo, m_lstReport.GetItemCount());  
	CMyExcel::ToExcel(&m_lstReport);
}

void COrderSeeDlg::OnVisibleCol()
{ 
	CColumnSelDlg dlg;
	dlg.m_plstReport = (CXTPListCtrl2*)&m_lstReport;
	dlg.m_sClass = "COrderSeeDlg";

	if(dlg.DoModal())
	{
		m_lstReport.LoadReportOrder(dlg.m_sClass, "m_lstReport");
		m_lstReport.Populate();
	}
}