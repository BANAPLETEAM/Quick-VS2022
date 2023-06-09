// ChargeListSetDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ChargeListSetDlg.h"

#include "VarietyDlg.h"
#include "POIDataNew.h"

// CChargeListSetDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChargeListSetDlg, CMyDialog)
CChargeListSetDlg::CChargeListSetDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CChargeListSetDlg::IDD, pParent)
{
	m_nDongID = 0;
}

CChargeListSetDlg::~CChargeListSetDlg()
{
}

void CChargeListSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHARGELIST_COMBO, m_cmbChargeList);
	DDX_Control(pDX, IDC_CHARGELIST_NEW_BTN, m_btnNewList);
	DDX_Control(pDX, IDC_CHARGELIST_DEL_BTN, m_btnDelList);
	DDX_Control(pDX, IDC_CHARGELIST_COPY_BTN, m_btnCopyList);
	DDX_Control(pDX, IDC_NICKNAME_INPUT_BTN, m_btnNicNameInput);
	DDX_Control(pDX, IDC_DONG_INPUT_BTN, m_btnDongInput);
	DDX_Control(pDX, IDC_DONG_OUT_BTN, m_btnDongOutput);
	DDX_Control(pDX, IDC_DONG_EDIT, m_edtDong);
	DDX_Control(pDX, IDC_NICKNAME_EDIT, m_edtNickName);
	DDX_Control(pDX, IDC_DONGDETAIL_EDIT, m_edtDongDetail);
	DDX_Control(pDX,IDC_CUSTOM1,m_RegisterDongList);
	DDX_Control(pDX,IDC_CUSTOM2,m_DongList);
	
}


BEGIN_MESSAGE_MAP(CChargeListSetDlg, CMyDialog)
	ON_BN_CLICKED(IDC_DONG_INPUT_BTN, OnBnClickedDongInputBtn)
	ON_CBN_SELCHANGE(IDC_CHARGELIST_COMBO, OnCbnSelchangeChargelistCombo)
	ON_BN_CLICKED(IDC_DONG_OUT_BTN, OnBnClickedDongOutBtn)
	ON_BN_CLICKED(IDC_NICKNAME_INPUT_BTN, OnBnClickedNicknameInputBtn)
	ON_BN_CLICKED(IDC_CHARGELIST_NEW_BTN, OnBnClickedChargelistNewBtn)
	ON_BN_CLICKED(IDC_CHARGELIST_DEL_BTN, OnBnClickedChargelistDelBtn)
	ON_BN_CLICKED(IDC_CHARGELIST_COPY_BTN, OnBnClickedChargelistCopyBtn)
	ON_BN_CLICKED(IDC_CHARGELIST_REFRESH_BTN, OnBnClickedChargelistRefreshBtn)
END_MESSAGE_MAP()


// CChargeListSetDlg 메시지 처리기입니다.


void CChargeListSetDlg::OnBnClickedDongOutBtn()
{
	try
	{
		if(m_RegisterDongList.GetSelectedRows()->GetCount() <= 0)
			throw "삭제하실 지역을 1개라도 선택하여 주세요";

		CString sChareList = "";
		m_cmbChargeList.GetLBText(m_cmbChargeList.GetCurSel(), sChareList);
		if(sChareList.GetLength() <= 0)
			throw "요금표이름이 없습니다.";

		for(int i = 0; i < m_RegisterDongList.GetSelectedRows()->GetCount(); i++)
		{
			long nID = m_RegisterDongList.GetItemLong(i);
			int nGrade = m_RegisterDongList.GetItemLong2(i);

			CMkRecordset pRs(m_pMkDb);
			CMkCommand pCmd(m_pMkDb, "update_charge_list_output_dong");
			pCmd.AddParameter(LF->GetCurBranchInfo()->nPayTable);
			pCmd.AddParameter(nID);
			pCmd.AddParameter(sChareList);
			pCmd.Execute();
		}

		OnCbnSelchangeChargelistCombo();
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


void CChargeListSetDlg::OnBnClickedNicknameInputBtn()
{
	try
	{
		CString sDongName, sNickName, sDongDetail = "";
		m_edtDong.GetWindowText(sDongName);
		m_edtNickName.GetWindowText(sNickName);
		m_edtDongDetail.GetWindowText(sDongDetail);
		if(sDongDetail.GetLength() <= 0 && sDongName.GetLength() <= 0)
			throw("동정보가 일정하지 않습니다. 검색을 다시하여 주세요");
		
		CString sChareList = "";
		m_cmbChargeList.GetLBText(m_cmbChargeList.GetCurSel(), sChareList);
		if(sChareList.GetLength() <= 0)
			throw "요금표 이름이 없거나 요금표이름을 섢택하세요";

		if(m_nDongID <= 0 )
			throw("동정보가 일정하지 않습니다. 검색을 다시하여 주세요");

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "update_charge_list_input_dong");
		pCmd.AddParameter(LF->GetCurBranchInfo()->nPayTable);
		pCmd.AddParameter(m_nDongID);
		pCmd.AddParameter(sChareList);
		pCmd.AddParameter(sNickName);
		pCmd.Execute();
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


void CChargeListSetDlg::OnBnClickedDongInputBtn()
{
	try
	{
		if(m_DongList.GetSelectedRows()->GetCount() <= 0 )
			throw("법정동리스트에서 입력하실 데이터를 선택하세요");

		CString sChareList = "";
		m_cmbChargeList.GetLBText(m_cmbChargeList.GetCurSel(), sChareList);
		if(sChareList.GetLength() <= 0)
			throw "요금표이름이 없습니다.";

		for (int i = 0; i < m_DongList.GetSelectedRows()->GetCount(); i++)
		{
			long nID = m_DongList.GetItemLong(i);

			CMkRecordset pRs(m_pMkDb);
			CMkCommand pCmd(m_pMkDb, "update_charge_list_output_dong");
			pCmd.AddParameter(LF->GetCurBranchInfo()->nPayTable);
			pCmd.AddParameter(nID);
			pCmd.AddParameter(sChareList);
			pCmd.Execute();
		}

		OnCbnSelchangeChargelistCombo();

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

BOOL CChargeListSetDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	ChargeListInputCommbo();
	m_cmbChargeList.SetCurSel(0);
	
	if(m_cmbChargeList.GetCount() > 0)
		OnCbnSelchangeChargelistCombo();

	RefreshLegalDong();
	return TRUE;  // return TRUE unless you set the focus to a control
	
}


void CChargeListSetDlg::ChargeListInputCommbo()
{
	m_cmbChargeList.ResetContent();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_charge_list_name");
	pCmd.AddParameter(LF->GetCurBranchInfo()->nPayTable);

	if(!pRs.Execute(&pCmd))
		return;


	CString sChargeList; int i = 0;

	while(!pRs.IsEOF())
	{		

		pRs.GetFieldValue("sChargeList", sChargeList);

		m_cmbChargeList.InsertString(i,sChargeList);

		pRs.MoveNext();		
		i +=1;
	}		
	pRs.Close();	

}

void CChargeListSetDlg::MakeColumn()
{
	m_DongList.AddColumn(new CXTPGridColumn(0, "지역", 180))->SetAlignment(DT_LEFT);
	m_DongList.AddColumn(new CXTPGridColumn(1, "해당동", 70))->SetAlignment(DT_LEFT);
	m_DongList.SetTreeIndent(30);
	m_DongList.SetGridColor(RGB(222, 222, 222));
}

void CChargeListSetDlg::RefreshLegalDong()
{
	m_DongList.ResetContent();
	m_DongList.GetColumns()->Clear();

	MakeColumn();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_web_dongpos_all");
	pCmd.AddParameter(1);
	if (!pRs.Execute(&pCmd)) return;

	CString  sPreKeyRef,sKeyRef,sTempSiGu = "", sDong = "", sSido = "", sGugun = "";
	long nGrade=0, nParentNo=0,nID=0, nPreGrade=0;

	CXTPGridRecord* pRecord = NULL;

	while(!pRs.IsEOF())
	{		
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("sSido", sSido);
		pRs.GetFieldValue("sGugun", sGugun);		
		pRs.GetFieldValue("sDong", sDong);
		pRs.GetFieldValue("nGrade", nGrade);
		pRs.GetFieldValue("nParentNo", nParentNo);

		if(nGrade == 0)
			sKeyRef = "";
		else if (nPreGrade == nGrade )
		{
			CString sAlpha = sPreKeyRef.Right(1);
			int nAscii = __toascii(sAlpha.GetAt(0));		
			int nLen = sPreKeyRef.GetLength()-1;
			sKeyRef.Format("%s%c",sPreKeyRef.Left(nLen), ++nAscii );
		}
		else if(nPreGrade > nGrade)
		{
			CString sAlpha = sPreKeyRef.Left(nGrade);
			int nAscii = __toascii(sAlpha.Right(1).GetAt(0));					
			sKeyRef.Format("%s%c",sPreKeyRef.Left(nGrade-1), ++nAscii );

		}
		else if(nPreGrade < nGrade)
		{			
			int nLen = sPreKeyRef.GetLength();
			sKeyRef.Format("%s%c",sPreKeyRef.Left(nLen), 97 );
		}
		switch(nGrade)
		{
		case 0:
			sTempSiGu = sSido;
			sDong = "";
			break;
		case 1:
		case 2:
			sTempSiGu = sGugun;
			sDong = "";
			break;
		default :
			sTempSiGu = sGugun;
			break;
		}

		if (pRecord) {
			if (sPreKeyRef == sKeyRef) {
				CXTPGridRecord *pChild = new CXTPGridRecord;
				pChild->AddItem(new CXTPGridRecordItemText(sTempSiGu));
				pChild->AddItem(new CXTPGridRecordItemText(sDong));
				pRecord->GetChilds()->Add(pChild);
				m_DongList.SetItemLong(pChild, nID);
				m_DongList.SetItemDataText(pChild, sKeyRef);
			}
		}
		else {
			pRecord = new CXTPGridRecord;
			pRecord->AddItem(new CXTPGridRecordItemText(sTempSiGu));
			pRecord->AddItem(new CXTPGridRecordItemText(sDong));
			m_DongList.AddRecord(pRecord);
			m_DongList.SetItemLong(pRecord, nID);
			m_DongList.SetItemDataText(pRecord, sKeyRef);
		}

		//m_DongList.TreeChildDepthAddItem(0,sKeyRef, nParentNo,sTempSiGu,"지역", 180, FALSE, DT_LEFT	);
		//CXTPGridRecord *pReocrd = m_DongList.MyAddItem(1,sDong, "해당동",70, FALSE,DT_LEFT);
		//pReocrd->SetItemDataLong(nID);
		//m_DongList.EndItem();


		nPreGrade  = nGrade;
		sPreKeyRef = sKeyRef;
		pRs.MoveNext();

	}
	m_DongList.Populate();	
	pRs.Close();
}

void CChargeListSetDlg::OnCbnSelchangeChargelistCombo()
{

	CString sChargeName = "";
	m_cmbChargeList.GetLBText(m_cmbChargeList.GetCurSel() , sChargeName);


	if(sChargeName.GetLength() <= 0 )
		return;

	m_RegisterDongList.DeleteAllItems();	
	
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_charge_list");
	pCmd.AddParameter(LF->GetCurBranchInfo()->nPayTable);
	pCmd.AddParameter(sChargeName);


	if(!pRs.Execute(&pCmd))
		return;


	CString sSido, sGugun2,sGugun, sDong, sPreKeyRef,sKeyRef, sTempSiGu="", sNickName = ""; 
	long i = 0,nID = 0, nGrade =0 , nPreGrade = 0, nParentNo =0;

	while(!pRs.IsEOF())
	{		

		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("sSido", sSido);
		pRs.GetFieldValue("sGugun", sGugun);
		pRs.GetFieldValue("sNickName", sNickName);
		pRs.GetFieldValue("sDong", sDong);
		pRs.GetFieldValue("nGrade", nGrade);
		pRs.GetFieldValue("nParentNo", nParentNo);
		

		if(nGrade == 0)
			sKeyRef = "";
		else if (nPreGrade == nGrade )
		{
			CString sAlpha = sPreKeyRef.Right(1);
			int nAscii = __toascii(sAlpha.GetAt(0));		
			int nLen = sPreKeyRef.GetLength()-1;
			sKeyRef.Format("%s%c",sPreKeyRef.Left(nLen), ++nAscii );
		}
		else if(nPreGrade > nGrade)
		{
			CString sAlpha = sPreKeyRef.Left(nGrade);
			int nAscii = __toascii(sAlpha.Right(1).GetAt(0));		
			//int nLen = sPreKeyRef.GetLength() - 2;
			sKeyRef.Format("%s%c",sPreKeyRef.Left(nGrade-1), ++nAscii );

		}
		else if(nPreGrade < nGrade)
		{
			//CString sAlpha = sPreKeyRef.Left(nGrade);
			//int nAscii = __toascii(sAlpha.GetAt(0));		
			int nLen = sPreKeyRef.GetLength();
			sKeyRef.Format("%s%c",sPreKeyRef.Left(nLen), 97 );

		}
		switch(nGrade)
		{
		case 0:
			sTempSiGu = sSido;
			sDong = "";
			break;
		case 1:
		case 2:
			sTempSiGu = sGugun;
			sDong = "";
			break;
		default :
			sTempSiGu = sGugun;
			break;

		}

		//m_RegisterDongList.TreeChildDepthAddItem(0,sKeyRef, nParentNo,sTempSiGu,"지역", 150, FALSE, DT_LEFT	);		
		//CXTPGridRecord *pRecord =	m_RegisterDongList.MyAddItem(1,sDong, "동", 60, FALSE, DT_LEFT);
		//													m_RegisterDongList.MyAddItem(2,sNickName, "별칭", 70, FALSE, DT_LEFT);
		//pRecord->SetItemDataLong(nID);
		//pRecord->SetItemDataLong2(nGrade);


		////m_RegisterDongList.SetItemRow(pRow);
		//m_RegisterDongList.EndItem();

			
		nPreGrade  = nGrade;
		sPreKeyRef = sKeyRef;
		pRs.MoveNext();

	}
	m_RegisterDongList.Populate();	


}

void CChargeListSetDlg::OnBnClickedChargelistNewBtn()
{
	CVarietyDlg dlg;
	dlg.m_sTitleDlg = "만드실 요금표 이름을 입력하세요";
	if(dlg.DoModal() == IDOK)
	{
		if(dlg.m_sValue.GetLength() > 0)
		{
			int nResult = 0;
			CMkRecordset pRs(m_pMkDb); 
			CMkCommand pCmd(m_pMkDb, "insert_chargelist_create_name");
			pCmd.AddParameter(LF->GetCurBranchInfo()->nPayTable);
			pCmd.AddParameter(dlg.m_sValue);				

			if(!pRs.Execute(&pCmd)) return;
	
			for(int i = 0; i < pRs.GetRecordCount(); i++)
                pRs.GetFieldValue("nResult",nResult);

			if(nResult == 100)
			{
				LF->MsgBox("같은이름이 존재합니다.");
				return;
			}
			else if(nResult == 10)
			{
				LF->MsgBox("요금표이름이 생성되었습니다.");
				ChargeListInputCommbo();
				CString sComboChargeName = "";
				int i = 0;
				for(i =0; i < m_cmbChargeList.GetCount(); i++)
				{

					m_cmbChargeList.GetLBText(i, sComboChargeName);
					if(sComboChargeName == dlg.m_sValue)
						break;
				}
				m_cmbChargeList.SetCurSel(i);
			}			

		}
		else
		{
			LF->MsgBox("요금표이름을 입력하세요");
		}
	}
}

void CChargeListSetDlg::OnBnClickedChargelistRefreshBtn()
{
	ChargeListInputCommbo();
	m_cmbChargeList.SetCurSel(0);
}


void CChargeListSetDlg::OnBnClickedChargelistCopyBtn()
{
	CVarietyDlg dlg;
	dlg.m_sTitleDlg = "복사하실 요금표 이름을 입력하세요";
	if(dlg.DoModal() == IDOK)
	{
		if(dlg.m_sValue.GetLength() > 0)
		{

			CString sChargeName = "";
			m_cmbChargeList.GetLBText(m_cmbChargeList.GetCurSel(), sChargeName);
			if(sChargeName.GetLength() == 0)
			{
				LF->MsgBox("원본 요금표 이름이 없습니다.");
				return;
			}

			int nResult = 0;
			CMkRecordset pRs(m_pMkDb); 
			CMkCommand pCmd(m_pMkDb, "insert_chargelist_copy_name");
			pCmd.AddParameter(LF->GetCurBranchInfo()->nPayTable);
			pCmd.AddParameter(sChargeName);
			pCmd.AddParameter(dlg.m_sValue);				

			if(!pRs.Execute(&pCmd)) return;
			int i = 0;
			for(i = 0; i < pRs.GetRecordCount(); i++)
				pRs.GetFieldValue("nResult",nResult);

			if(nResult == 100)
			{
				LF->MsgBox("복사할 요금표의 같은이름이 존재합니다.");
				return;
			}
			else if(nResult == 10)
			{
				LF->MsgBox("요금표가 복사되었습니다.");
				ChargeListInputCommbo();

				CString sComboChargeName = "";
				for(int i =0; i < m_cmbChargeList.GetCount(); i++)
				{

					m_cmbChargeList.GetLBText(i, sComboChargeName);
					if(sComboChargeName == dlg.m_sValue)
						break;
				}
				m_cmbChargeList.SetCurSel(i);
			}			

		}
		else
		{
			LF->MsgBox("요금표이름을 입력하세요");
		}
	}
}

void CChargeListSetDlg::OnBnClickedChargelistDelBtn()
{ 
	if(MessageBox("해당 요금표를 정말로 삭제하시겠습니까", "확인", MB_ICONINFORMATION | MB_YESNO) == IDYES)
	{
		CString sChargeName = "";
		m_cmbChargeList.GetLBText(m_cmbChargeList.GetCurSel(), sChargeName);
		if(sChargeName.GetLength() == 0)
		{
			LF->MsgBox("요금표이름이 없습니다.");
			return;
		}

		CMkRecordset pRs(m_pMkDb); 
		CMkCommand pCmd(m_pMkDb, "delete_chargelist_name");
		pCmd.AddParameter(LF->GetCurBranchInfo()->nPayTable);
		pCmd.AddParameter(sChargeName);				
		if(!pRs.Execute(&pCmd)) return;

		ChargeListInputCommbo();
		m_cmbChargeList.SetCurSel(0);
		
	}
}