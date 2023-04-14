// ChargeListSetDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ChargeListSetDlg.h"

#include "VarietyDlg.h"
#include "POIDataNew.h"

// CChargeListSetDlg ��ȭ �����Դϴ�.

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


// CChargeListSetDlg �޽��� ó�����Դϴ�.


void CChargeListSetDlg::OnBnClickedDongOutBtn()
{
	try
	{
		if(m_RegisterDongList.GetSelectedCount() <= 0)
			throw "�����Ͻ� ������ 1���� �����Ͽ� �ּ���";

		CString sChareList = "";
		m_cmbChargeList.GetLBText(m_cmbChargeList.GetCurSel(), sChareList);
		if(sChareList.GetLength() <= 0)
			throw "���ǥ�̸��� �����ϴ�.";

		for(int i = 0; i < m_RegisterDongList.GetSelectedCount(); i++)
		{

			CMyXTPGridRecord *pReocrd = m_RegisterDongList.GetSelectedRecord(i);
			long nID = pReocrd->GetItemDataLong();		
			int nGrade = pReocrd->GetItemDataLong2();

			m_RegisterDongList.CreateComandSetQuery("update_charge_list_output_dong");
			m_RegisterDongList.AddParameter(GetCurBranchInfo()->nPayTable);
			m_RegisterDongList.AddParameter(nID);
			m_RegisterDongList.AddParameter(sChareList);
			m_RegisterDongList.ExcuteCmd();

			CXTPGridRow *pRow = m_RegisterDongList.GetSelectedRows()->GetAt(i);	
			
			if(nGrade != 3)
			{
				if(pRow->GetChilds()->GetCount() > 0 )
				{
					int nRows = pRow->GetChilds()->GetCount();
					for(int nRow = 0; nRow < nRows; nRow++)
					{
						CXTPGridRow *pChildRow = pRow->GetChilds()->GetAt(nRow);
					}
				}
				
			}
			
		}

		OnCbnSelchangeChargelistCombo();
	}
	catch (char* e)
	{
		MsgBox(e, "Ȯ��");
	}
	catch (CString s)
	{
		MsgBox(s, "Ȯ��");
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
			throw("�������� �������� �ʽ��ϴ�. �˻��� �ٽ��Ͽ� �ּ���");

		
		CString sChareList = "";
		m_cmbChargeList.GetLBText(m_cmbChargeList.GetCurSel(), sChareList);
		if(sChareList.GetLength() <= 0)
			throw "���ǥ �̸��� ���ų� ���ǥ�̸��� �����ϼ���";


		if(m_nDongID <= 0 )
			throw("�������� �������� �ʽ��ϴ�. �˻��� �ٽ��Ͽ� �ּ���");

		m_DongList.CreateComandSetQuery("update_charge_list_input_dong");
		m_DongList.AddParameter(GetCurBranchInfo()->nPayTable);
		m_DongList.AddParameter(m_nDongID);
		m_DongList.AddParameter(sChareList);
		m_DongList.AddParameter(sNickName);
		m_DongList.ExcuteCmd();

		

	}
	catch (char* e)
	{
		MsgBox(e, "Ȯ��");
	}
	catch (CString s)
	{
		MsgBox(s, "Ȯ��");
	}
}


void CChargeListSetDlg::OnBnClickedDongInputBtn()
{
	
	try
	{
		if(m_DongList.GetSelectedCount() <= 0 )
			throw("����������Ʈ���� �Է��Ͻ� �����͸� �����ϼ���");

		CString sChareList = "";
		m_cmbChargeList.GetLBText(m_cmbChargeList.GetCurSel(), sChareList);
		if(sChareList.GetLength() <= 0)
			throw "���ǥ�̸��� �����ϴ�.";

		for(int i =0; i < m_DongList.GetSelectedCount(); i++)
		{
			CMyXTPGridRecord *pReocrd = m_DongList.GetSelectedRecord(i);
			long nID = pReocrd->GetItemDataLong();		

			m_DongList.CreateComandSetQuery("update_charge_list_input_dong");
			m_DongList.AddParameter(GetCurBranchInfo()->nPayTable);
			m_DongList.AddParameter(nID);
			m_DongList.AddParameter(sChareList);
			m_DongList.ExcuteCmd();

		}
		OnCbnSelchangeChargelistCombo();

	}
	catch (char* e)
	{
		MsgBox(e, "Ȯ��");
	}
	catch (CString s)
	{
		MsgBox(s, "Ȯ��");
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
	pCmd.AddParameter(GetCurBranchInfo()->nPayTable);

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

};
void CChargeListSetDlg::RefreshLegalDong()
{

		
	m_DongList.CreateRsSetQuery("select_web_dongpos_all");
	m_DongList.AddParameter(1);
	CMkRecordset *pRs = m_DongList.Excute();
	CString  sPreKeyRef,sKeyRef,sTempSiGu = "", sDong = "", sSido = "", sGugun = "";
	long nGrade=0, nParentNo=0,nID=0, nPreGrade=0;

	
	
	if(!pRs) return;

	while(!pRs->IsEOF())
	{		

		pRs->GetFieldValue("nID", nID);
		pRs->GetFieldValue("sSido", sSido);
		pRs->GetFieldValue("sGugun", sGugun);		
		pRs->GetFieldValue("sDong", sDong);
		pRs->GetFieldValue("nGrade", nGrade);
		pRs->GetFieldValue("nParentNo", nParentNo);

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

		m_DongList.TreeChildDepthAddItem(0,sKeyRef, nParentNo,sTempSiGu,"����", 180, FALSE, DT_LEFT	);
		CMyXTPGridRecord *pReocrd = m_DongList.MyAddItem(1,sDong, "�ش絿",70, FALSE,DT_LEFT);
		pReocrd->SetItemDataLong(nID);
		//m_DongList.MySetItemData(nID);
		//m_DongList.SetItemRow(pRow);
		m_DongList.EndItem();


		nPreGrade  = nGrade;
		sPreKeyRef = sKeyRef;
		pRs->MoveNext();

	}
	m_DongList.Populate();	
	m_DongList.RecordSetCloseRelease(pRs);

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
	pCmd.AddParameter(GetCurBranchInfo()->nPayTable);
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

		m_RegisterDongList.TreeChildDepthAddItem(0,sKeyRef, nParentNo,sTempSiGu,"����", 150, FALSE, DT_LEFT	);		
		CMyXTPGridRecord *pRecord =	m_RegisterDongList.MyAddItem(1,sDong, "��", 60, FALSE, DT_LEFT);
															m_RegisterDongList.MyAddItem(2,sNickName, "��Ī", 70, FALSE, DT_LEFT);
		pRecord->SetItemDataLong(nID);
		pRecord->SetItemDataLong2(nGrade);


		//m_RegisterDongList.SetItemRow(pRow);
		m_RegisterDongList.EndItem();

			
		nPreGrade  = nGrade;
		sPreKeyRef = sKeyRef;
		pRs.MoveNext();

	}
	m_RegisterDongList.Populate();	


}

void CChargeListSetDlg::OnBnClickedChargelistNewBtn()
{
	CVarietyDlg dlg;
	dlg.m_sTitleDlg = "����� ���ǥ �̸��� �Է��ϼ���";
	if(dlg.DoModal() == IDOK)
	{
		if(dlg.m_sValue.GetLength() > 0)
		{
			int nResult = 0;
			CMkRecordset pRs(m_pMkDb); 
			CMkCommand pCmd(m_pMkDb, "insert_chargelist_create_name");
			pCmd.AddParameter(GetCurBranchInfo()->nPayTable);
			pCmd.AddParameter(dlg.m_sValue);				

			if(!pRs.Execute(&pCmd)) return;
	
			for(int i = 0; i < pRs.GetRecordCount(); i++)
                pRs.GetFieldValue("nResult",nResult);

			if(nResult == 100)
			{
				MsgBox("�����̸��� �����մϴ�.");
				return;
			}
			else if(nResult == 10)
			{
				MsgBox("���ǥ�̸��� �����Ǿ����ϴ�.");
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
			MsgBox("���ǥ�̸��� �Է��ϼ���");
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
	dlg.m_sTitleDlg = "�����Ͻ� ���ǥ �̸��� �Է��ϼ���";
	if(dlg.DoModal() == IDOK)
	{
		if(dlg.m_sValue.GetLength() > 0)
		{

			CString sChargeName = "";
			m_cmbChargeList.GetLBText(m_cmbChargeList.GetCurSel(), sChargeName);
			if(sChargeName.GetLength() == 0)
			{
				MsgBox("���� ���ǥ �̸��� �����ϴ�.");
				return;
			}

			int nResult = 0;
			CMkRecordset pRs(m_pMkDb); 
			CMkCommand pCmd(m_pMkDb, "insert_chargelist_copy_name");
			pCmd.AddParameter(GetCurBranchInfo()->nPayTable);
			pCmd.AddParameter(sChargeName);
			pCmd.AddParameter(dlg.m_sValue);				

			if(!pRs.Execute(&pCmd)) return;
			int i = 0;
			for(i = 0; i < pRs.GetRecordCount(); i++)
				pRs.GetFieldValue("nResult",nResult);

			if(nResult == 100)
			{
				MsgBox("������ ���ǥ�� �����̸��� �����մϴ�.");
				return;
			}
			else if(nResult == 10)
			{
				MsgBox("���ǥ�� ����Ǿ����ϴ�.");
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
			MsgBox("���ǥ�̸��� �Է��ϼ���");
		}
	}
}

void CChargeListSetDlg::OnBnClickedChargelistDelBtn()
{
	if(MessageBox("�ش� ���ǥ�� ������ �����Ͻðڽ��ϱ�", "Ȯ��", MB_ICONINFORMATION | MB_YESNO) == IDYES)
	{
		CString sChargeName = "";
		m_cmbChargeList.GetLBText(m_cmbChargeList.GetCurSel(), sChargeName);
		if(sChargeName.GetLength() == 0)
		{
			MsgBox("���ǥ�̸��� �����ϴ�.");
			return;
		}

		CMkRecordset pRs(m_pMkDb); 
		CMkCommand pCmd(m_pMkDb, "delete_chargelist_name");
		pCmd.AddParameter(GetCurBranchInfo()->nPayTable);
		pCmd.AddParameter(sChargeName);				
		if(!pRs.Execute(&pCmd)) return;

		ChargeListInputCommbo();
		m_cmbChargeList.SetCurSel(0);
		
	}
}