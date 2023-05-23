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
		if(m_RegisterDongList.GetSelectedCount() <= 0)
			throw "삭제하실 지역을 1개라도 선택하여 주세요";

	
		for(int i = 0; i < m_RegisterDongList.GetSelectedCount(); i++)
		{

			CMyXTPGridRecord *pReocrd = m_RegisterDongList.GetSelectedRecord(i);
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
		if(m_DongList.GetSelectedCount() <= 0 )
			throw("도, 시리스트에서 입력하실 데이터를 선택하세요");

		CString sChareList = "";		
		m_setSido.clear();

		CStringArray sArr;

		for(int i =0; i < m_DongList.GetSelectedCount(); i++)
		{
			CMyXTPGridRecord *pReocrd = m_DongList.GetSelectedRecord(i);
			long nID = pReocrd->GetItemDataLong();	
			CString strSidoList = pReocrd->GetItemDataString();
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
	
	
	for(int i = sArr.GetCount() - 1; i >= 0; i--)
	{
		
		itSaveSido = 	m_setSaveSido.find(sArr.GetAt(i));
		if(itSaveSido != m_setSaveSido.end())
			sArr.RemoveAt(i);
		
	}

	if(sArr.GetCount() > 0)
	{
		for(int j = 0; j < sArr.GetCount(); j++)
		{
			CMyXTPGridRecord *pRecord =  m_RegisterDongList.MyAddItem(0,sArr.GetAt(j), "지역", 100, FALSE, DT_LEFT	); 
			pRecord->SetItemDataString(sArr.GetAt(j));
			m_RegisterDongList.EndItem();
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
	if(!pRs.Execute(&pCmd)) return;

	if(pRs.GetRecordCount() == 0 )
	{
		//MessageBox("데이터가 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}


	pRs.GetFieldValue("sRegisterSido", strRegisterSido);

	if(strRegisterSido.GetLength() > 0)
	{
		LF->MyTokenize(strRegisterSido,",", FALSE, strArr);

		for(long i=0; i<strArr.GetCount(); i++)
		{
			CString  strSido = "";			

			strSido = strArr.GetAt(i);


			CMyXTPGridRecord *pRecord = m_RegisterDongList.MyAddItem(0,strSido, "지역", 100, FALSE, DT_LEFT	);			
			pRecord->SetItemDataString(strSido);
			m_setSaveSido.insert(strSido);
			m_RegisterDongList.EndItem();
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
	if(!pRs.Execute(&pCmd)) return;

	if(pRs.GetRecordCount() == 0 )
	{
		MessageBox("데이터가 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	for(long i=0; i<pRs.GetRecordCount(); i++)
	{
		CString  sPreKeyRef,sKeyRef,sTempSiGu = "", sDong = "", sSido = "", sGugun = "";
		long nGrade=0, nParentNo=0,nID=0, nPreGrade=0;

		pRs.GetFieldValue("sSido", sSido);


		CMyXTPGridRecord *pRecord = m_DongList.MyAddItem(0,sSido, "지역", 100, FALSE, DT_LEFT	);

		pRecord->SetItemDataLong(nID);		
		pRecord->SetItemDataString(sSido);
		m_DongList.EndItem();
		pRs.MoveNext();
	}


	m_DongList.Populate();		

}


void CChargeSimpleListDlg::OnBnClickedSaveBtn()
{
	
	 /*if(m_RegisterDongList.GetRecords()->GetCount() <= 0)
	 {
		 OnOK();
	 }*/

	 CString strSaveArea = "",strTemp = "";
	 for(int i = 0; i < m_RegisterDongList.GetRecords()->GetCount(); i++)
	 {	
		 strTemp = m_RegisterDongList.GetItemDataString(i);
		 strSaveArea += strTemp + ",";

	 }
		 
	 
		 CMkRecordset pRs(m_pMkDb);
		 CMkCommand pCmd(m_pMkDb, "update_dongpos_simple");
		 pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);
		 pCmd.AddParameter(typeString, typeInput, strSaveArea.GetLength(), strSaveArea);
		 if(!pRs.Execute(&pCmd)) return;

		 if(m_bChargeDongDlg3)
			((CChargeDongDlg3*)GetParent())->SetRemoveRefreshList();
		
		 OnOK();
		

	 

}
