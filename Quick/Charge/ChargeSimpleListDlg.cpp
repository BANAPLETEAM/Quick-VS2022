// ChargeSimpleListDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "ChargeSimpleListDlg.h"
#include "POIDataNew.h"
#include "ChargeDongDlg3.h"
#include "LogiFunc.h"


// CChargeSimpleListDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChargeSimpleListDlg, CMyDialog)

CChargeSimpleListDlg::CChargeSimpleListDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CChargeSimpleListDlg::IDD, pParent)
{

	m_nDongID = 0;
	m_nCompany = 0;
	m_bChargeDongDlg3 = FALSE;

}

CChargeSimpleListDlg::~CChargeSimpleListDlg()
{
	
}

void CChargeSimpleListDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_CUSTOM1,m_RegisterDongList);
	DDX_Control(pDX,IDC_CUSTOM2,m_DongList);


	DDX_Control(pDX, IDC_DONG_INPUT_BTN, m_btnDongInput);
	DDX_Control(pDX, IDC_DONG_OUT_BTN, m_btnDongOutput);
	
}


BEGIN_MESSAGE_MAP(CChargeSimpleListDlg, CMyDialog)
	ON_BN_CLICKED(IDC_DONG_INPUT_BTN, OnBnClickedDongInputBtn)
	ON_BN_CLICKED(IDC_DONG_OUT_BTN, OnBnClickedDongOutBtn)
	ON_BN_CLICKED(IDC_SAVE_BTN, &CChargeSimpleListDlg::OnBnClickedSaveBtn)
END_MESSAGE_MAP()



void CChargeSimpleListDlg::OnBnClickedDongOutBtn()
{
	try
	{
		if(m_RegisterDongList.GetSelectedRows()->GetCount() <= 0)
			throw "삭제하실 지역을 1개라도 선택하여 주세요";

	
		for(int i = 0; i < m_RegisterDongList.GetSelectedRows()->GetCount(); i++)
		{

			CXTPGridRecord *pReocrd = m_RegisterDongList.GetSelectedRows()->GetAt(i)->GetRecord();
			pReocrd->Delete();			

		}
		m_RegisterDongList.Populate();
	}
	catch (char* e)
	{
		LF->MsgBox(e, "확인");
	}
	catch (CString s)
	{
		LF->MsgBox(s, "확인");
	}
}




void CChargeSimpleListDlg::OnBnClickedDongInputBtn()
{

	try
	{
		if(m_DongList.GetSelectedRows()->GetCount() <= 0 )
			throw("도, 시리스트에서 입력하실 데이터를 선택하세요");

		CString sChareList = "";		
		m_setSido.clear();

		CStringArray sArr;

		for(int i =0; i < m_DongList.GetSelectedRows()->GetCount(); i++)
		{
			CXTPGridRecord *pReocrd = m_DongList.GetSelectedRows()->GetAt(i)->GetRecord();
			long nID = m_DongList.GetItemLong(pReocrd);
			CString strSidoList = m_DongList.GetItemDataText(pReocrd);
			sArr.Add(strSidoList);

		}
		
		Compare(sArr);

	}
	catch (char* e)
	{
		LF->MsgBox(e, "확인");
	}
	catch (CString s)
	{
		LF->MsgBox(s, "확인");
	}


}

void CChargeSimpleListDlg::Compare(CStringArray &sArr)
{
	setSido::iterator itSaveSido;

	for (int i = sArr.GetCount() - 1; i >= 0; i--) {
		itSaveSido = m_setSaveSido.find(sArr.GetAt(i));
		if (itSaveSido != m_setSaveSido.end())
			sArr.RemoveAt(i);
	}

	if (sArr.GetCount() > 0) {
		for (int j = 0; j < sArr.GetCount(); j++) {
			m_RegisterDongList.InsertItem(j, sArr.GetAt(j));
			m_setSaveSido.insert(sArr.GetAt(j));
		}
	}

	m_RegisterDongList.Populate();
}


BOOL CChargeSimpleListDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_RegisterDongList.InsertColumn(0, "지역", DT_LEFT,100);
	m_RegisterDongList.Populate();
	
	RefreshSaveList();
	RefreshList();
	return TRUE;  // return TRUE unless you set the focus to a control

}


void CChargeSimpleListDlg::RefreshSaveList()
{
	CString strRegisterSido = "";
	CStringArray strArr;
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_dongpos_save_simple");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);
	if (!pRs.Execute(&pCmd)) return;
	if (pRs.GetRecordCount() == 0) return;

	pRs.GetFieldValue("sRegisterSido", strRegisterSido);

	if (strRegisterSido.GetLength() > 0) {
		LF->MyTokenize(strRegisterSido, ",", FALSE, strArr);

		for (long i = 0; i < strArr.GetCount(); i++) {
			m_RegisterDongList.InsertItem(i, strArr.GetAt(i));
			m_setSaveSido.insert(strArr.GetAt(i));
			pRs.MoveNext();
		}

		m_RegisterDongList.Populate();
	}
}

void CChargeSimpleListDlg::RefreshList()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_dongpos_simple");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);
	if (!pRs.Execute(&pCmd)) return;
	if (pRs.GetRecordCount() == 0) return;

	for (long i = 0; i < pRs.GetRecordCount(); i++) {
		CString sSido;
		long nID = 0;
		pRs.GetFieldValue("sSido", sSido);

		m_DongList.InsertItem(i, sSido);
		m_DongList.SetItemLong(i, nID);
		pRs.MoveNext();
	}

	m_DongList.Populate();
}


void CChargeSimpleListDlg::OnBnClickedSaveBtn()
{
	CString strSaveArea = "", strTemp = "";
	for (int i = 0; i < m_RegisterDongList.GetRecords()->GetCount(); i++)
	{
		strTemp = m_RegisterDongList.GetItemText(i, 0);
		strSaveArea += strTemp + ",";
	}

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_dongpos_simple");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);
	pCmd.AddParameter(typeString, typeInput, strSaveArea.GetLength(), strSaveArea);
	if (!pRs.Execute(&pCmd)) return;

	if (m_bChargeDongDlg3)
		((CChargeDongDlg3*)GetParent())->SetRemoveRefreshList();

	OnOK();
}
