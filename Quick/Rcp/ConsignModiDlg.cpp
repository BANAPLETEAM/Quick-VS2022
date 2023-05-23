// ConsignModiDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ConsignModiDlg.h"

#include "SearchRegionDlg.h"

// CConsignModiDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CConsignModiDlg, CMyDialog)
CConsignModiDlg::CConsignModiDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CConsignModiDlg::IDD, pParent)
{
	m_nMod = 0;
	m_nPOIID = 0;
	m_pDestPoi = NULL;
}

CConsignModiDlg::~CConsignModiDlg()
{
}

void CConsignModiDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TERMINAL_COMBO, m_cmbTerminal);
	DDX_Control(pDX, IDC_START_EDIT, m_edtStart);
	DDX_Control(pDX, IDC_DETAIL_EDIT, m_edtDetail);
	DDX_Control(pDX, IDC_END_EDIT, m_edtEnd);
	DDX_Control(pDX, IDC_INTERVAL_EDIT, m_edtInterval);
	DDX_Control(pDX, IDC_CARWAY_COMBO, m_cmbCarWay);
	DDX_Control(pDX, IDC_DEST_EDIT, m_edtDest);
	DDX_Control(pDX, IDC_DEST_TAIL_EDIT, m_edtDestDetail);
	DDX_Control(pDX, IDC_ETC_EDIT, m_edtEtc);
	DDX_Control(pDX, IDC_CHARGE_EDIT, m_edtCharge);
	DDX_Control(pDX, IDC_TEL_EDIT, m_edtTel);

}


BEGIN_MESSAGE_MAP(CConsignModiDlg, CMyDialog)
	ON_BN_CLICKED(IDOK2, OnBnClickedOk2)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(ID_SAVE_OK, OnBnClickedSaveOk)
	ON_EN_CHANGE(IDC_DEST_EDIT, OnEnChangeDestEdit)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CConsignModiDlg �޽��� ó�����Դϴ�.

void CConsignModiDlg::OnBnClickedOk2()
{
	NewConsign();
}

void CConsignModiDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}

void CConsignModiDlg::OnBnClickedSaveOk()
{
	if(m_nMod  == 0)
		NewConsign();
	else
		EditConsign();
}

void CConsignModiDlg::NewConsign()
{
	if(m_nMod > 0)
		return;

	CString sTempTerminal;
	CString	sTerminalName, sDest,sWayEtc, sStart,sEnd, sInterval, sEtc,sTel, sCharge;
	long nTranWay, nCharge,nPOIID = 0;
	m_cmbTerminal.GetWindowText(sTerminalName);
	BOOL bFind = FALSE;
	for(int i = 0; i < m_cmbTerminal.GetCount(); i++)
	{
		m_cmbTerminal.GetLBText(i,sTempTerminal);
		if(sTempTerminal == sTerminalName)
		{
			bFind = TRUE;
			break;
		}
			
	}
	if(!bFind )
	{
		sTempTerminal.Format("�űԷ� %s �͹̳�(��)�� ����Ͻðڽ��ϱ�?", sTerminalName);
		if(MessageBox(sTempTerminal, "Ȯ��", MB_ICONINFORMATION | MB_YESNO) == IDNO)
			return;
	}

	nTranWay = m_cmbCarWay.GetCurSel();
	m_edtDest.GetWindowText(sDest);
	m_edtDetail.GetWindowText(sWayEtc);
	m_edtCharge.GetWindowText(sCharge);
	sCharge.Replace(",","");
	nCharge = atol(sCharge);

	m_edtTel.GetWindowText(sTel);
	m_edtStart.GetWindowText(sStart);
	m_edtEnd.GetWindowText(sEnd);
	m_edtInterval.GetWindowText(sInterval);

	sDest.Trim();

	if(sDest.GetLength() == 0 || m_nPOIID <= 0 )
	{
		MessageBox("�������� ������ �Է��ϼ���","Ȯ��",  MB_ICONINFORMATION);
		return;
	}

	CMkCommand pCmd(m_pMkDb, "insert_consign_way");
	pCmd.AddParameter(FALSE);
	pCmd.AddParameter(sTerminalName);	
	pCmd.AddParameter(nTranWay);
	pCmd.AddParameter(sWayEtc);
	pCmd.AddParameter(nCharge);
	pCmd.AddParameter(sDest);	
	pCmd.AddParameter(sTel);
	pCmd.AddParameter(sStart);
	pCmd.AddParameter(sEnd);
	pCmd.AddParameter(sInterval);
	pCmd.AddParameter(m_nPOIID);
	pCmd.AddParameter(sEtc);
	pCmd.Execute();


	MessageBox("�Է��Ͽ����ϴ�.","Ȯ��", MB_ICONINFORMATION);



}

void CConsignModiDlg::SearchStartSection()
{
//by mksong (2010-09-23 ���� 8:22)
//�۾��ʿ���
/*
	POI_MATCH_VECTOR poiMatch;
	POI_MATCH_VECTOR::iterator iter;
	CString strData, strList;
	m_edtDest.GetWindowText(strData);
	ShowSearchDongDlg(IDC_DEST_EDIT);
	m_pSearchDongDlg->ClearList();

	if(strData.GetLength() == 0)
		return;

	DWORD dwTick = GetTickCount();

	if(m_poi.LikeSearch(strData, poiMatch)) 
	{
		//g_bana_log->Print("LikeSearch: %d\n", GetTickCount() - dwTick);
		long nCount = 0;
		for(iter = poiMatch.begin(); iter != poiMatch.end(); iter++)
		{
			if(nCount++ <= 7) 
			{
				if(iter == poiMatch.begin())
				{					
					m_pDestPoi = (*iter)->pPOI;
					m_pSearchDongDlg->SetStartPoi(m_pDestPoi);

					CString strDisplayName;
					m_poi.GetDisplayName(m_pDestPoi, strDisplayName);
					m_edtDestDetail.SetWindowText(strDisplayName);
					m_nPOIID = m_pDestPoi->nID;
				}

				m_pSearchDongDlg->AddItem((*iter)->pPOI);
			}
			delete (*iter);
		}
	}

	poiMatch.clear();
*/
}
void CConsignModiDlg::EditConsign()
{
	if(m_nMod == 0)
		return;

	CString sTempTerminal;
	CString	sTerminalName, sDest,sWayEtc, sStart,sEnd, sInterval, sEtc,sTel, sCharge;
	long nTranWay, nCharge,nPOIID = 0;
	m_cmbTerminal.GetWindowText(sTerminalName);
	BOOL bFind = FALSE;
	for(int i = 0; i < m_cmbTerminal.GetCount(); i++)
	{
		m_cmbTerminal.GetLBText(i,sTempTerminal);
		if(sTempTerminal == sTerminalName)
		{
			bFind = TRUE;
			break;
		}

	}
	if(!bFind )
	{
		sTempTerminal.Format("�űԷ� %s �͹̳�(��)�� ����Ͻðڽ��ϱ�?", sTerminalName);
		if(MessageBox(sTempTerminal, "Ȯ��", MB_ICONINFORMATION | MB_YESNO) == IDNO)
			return;
	}

	nTranWay = m_cmbCarWay.GetCurSel();
	m_edtDest.GetWindowText(sDest);
	m_edtDetail.GetWindowText(sWayEtc);
	m_edtCharge.GetWindowText(sCharge);
	sCharge.Replace(",","");
	nCharge = atol(sCharge);

	m_edtTel.GetWindowText(sTel);
	m_edtStart.GetWindowText(sStart);
	m_edtEnd.GetWindowText(sEnd);
	m_edtInterval.GetWindowText(sInterval);
	m_edtEtc.GetWindowText(sEtc);

	CMkCommand pCmd(m_pMkDb, "insert_consign_way");

	pCmd.AddParameter(m_nMod);
	pCmd.AddParameter(sTerminalName);
	pCmd.AddParameter(nTranWay);
	pCmd.AddParameter(sWayEtc);
	pCmd.AddParameter(nCharge);
	pCmd.AddParameter(sDest);	
	pCmd.AddParameter(sTel);
	pCmd.AddParameter(sStart);
	pCmd.AddParameter(sEnd);
	pCmd.AddParameter(sInterval);
	pCmd.AddParameter(m_nPOIID);
	pCmd.AddParameter(sEtc);
	pCmd.Execute();

	MessageBox("�Է��Ͽ����ϴ�.","Ȯ��", MB_ICONINFORMATION);

}
BOOL CConsignModiDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();


	m_cmbCarWay.SetCurSel(0);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_consign_terminal_name");
	pCmd.AddParameter(1);
	if(!pRs.Execute(&pCmd)) return FALSE;
	
	int i = 0;
	while(!pRs.IsEOF())
	{
		CString	sTerminalName;

		pRs.GetFieldValue("sTerminalName", sTerminalName);
		
		m_cmbTerminal.InsertString(i,sTerminalName);
		i++;
		pRs.MoveNext();
	}
	
	m_cmbTerminal.SetCurSel(0);

	if(m_nMod) //�����̸�
	{
		SearchData();
			

	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
void CConsignModiDlg::SearchData()
{

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_consign_id");
	pCmd.AddParameter(m_nMod);
	if(!pRs.Execute(&pCmd)) return;

	int i = 0;
	while(!pRs.IsEOF())
	{
		CString	sTerminalName, sDest,sWayEtc, sStart,sEnd, sInterval, sEtc, sTel;
		long nTranWay, nCharge,nPOIID = 0;

		pRs.GetFieldValue("sTerminalName", sTerminalName);
		pRs.GetFieldValue("nTranWay", nTranWay);
		pRs.GetFieldValue("sDest", sDest);
		pRs.GetFieldValue("sWayEtc", sWayEtc);
		pRs.GetFieldValue("nCharge", nCharge);
		pRs.GetFieldValue("sTel", sTel);
		pRs.GetFieldValue("sStart", sStart);
		pRs.GetFieldValue("sEnd", sEnd);
		pRs.GetFieldValue("sInterval", sInterval);
		pRs.GetFieldValue("nPOIID", nPOIID);
		pRs.GetFieldValue("sEtc", sEtc);
		
		m_cmbTerminal.SetWindowText(sTerminalName);
		m_cmbCarWay.SetCurSel(nTranWay);
		m_edtDest.SetWindowText(sDest);
		m_edtDetail.SetWindowText(sWayEtc);
		m_edtCharge.SetWindowText(LF->GetMyNumberFormat(nCharge));
		m_edtTel.SetWindowText(sTel);
		m_edtStart.SetWindowText(sStart);
		m_edtEnd.SetWindowText(sEnd);
		m_edtInterval.SetWindowText(sInterval);

		m_nPOIID = nPOIID;
		CString sDisplayName = m_poiNew.GetPOI(m_nPOIID)->GetFullName();
		m_edtDestDetail.SetWindowText(sDisplayName);
		m_edtEtc.SetWindowText(sEtc);

		pRs.MoveNext();
		
	}
	pRs.Close();


}

BOOL CConsignModiDlg::PreTranslateMessage(MSG* pMsg)
{

	long uID = 0;
	if(pMsg->message == WM_LBUTTONDOWN)
	{
		uID = ::GetDlgCtrlID(pMsg->hwnd);

		if(::GetDlgCtrlID(pMsg->hwnd) == IDC_DEST_EDIT)
		{
			SearchRegion(IDC_DEST_EDIT);
			return TRUE;
		}

	}

	if(pMsg->message == WM_KEYDOWN &&
		pMsg->wParam == VK_RETURN)
	{
	
		switch(::GetDlgCtrlID(pMsg->hwnd))
		{
		case IDC_TERMINAL_COMBO:
			m_edtDetail.SetFocus();
			return TRUE;
			break;

		case IDC_DETAIL_EDIT:

			m_cmbCarWay.SetFocus();
			return TRUE;
			break;

		case IDC_CARWAY_COMBO:
			
			m_edtStart.SetFocus();
			
			return TRUE;
			break;

		case IDC_START_EDIT:
			m_edtEnd.SetFocus();
			return TRUE;
			break;

		case IDC_END_EDIT:
			m_edtInterval.SetFocus();
			return TRUE;
			//this->m_edtRicence.SetFocus();
			break;

		case IDC_INTERVAL_EDIT:
			m_edtDest.SetFocus();
			return TRUE;
			break;

		case IDC_DEST_EDIT:
			m_edtCharge.SetFocus();
			return TRUE;
			break;

		case IDC_CHARGE_EDIT:
			m_edtTel.SetFocus();
			return TRUE;
			break;
		case IDC_TEL_EDIT:
			m_edtEtc.SetFocus();
			return TRUE;
			break;
		}
	}
	return CMyDialog::PreTranslateMessage(pMsg);
}

void CConsignModiDlg::OnEnChangeDestEdit()
{
	// TODO:  RICHEDIT ��Ʈ���� ��� �� ��Ʈ����
	// CMyDialog::����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ�
	// CRichEditCtrl().SetEventMask()�� ȣ���ϵ��� OnInitDialog() �Լ��� ���������� ������
	// �� �˸��� ������ �ʽ��ϴ�.

	//CString sDest = "";
	//m_edtDest.GetWindowText(sDest);

	////m_poi.s	

SearchStartSection();

}
//
//void CConsignModiDlg::OnEnSetfocusDestEdit()
//{
//	/*if(m_pSearchDongDlg) {
//		m_pSearchDongDlg->m_nFocusEdit = IDC_DEST_EDIT;
//		m_pSearchDongDlg->ClearList();
//		m_pSearchDongDlg->RefreshTitle();
//		m_pSearchDongDlg->ShowWindow(SW_SHOW);
//	}*/
//	SearchRegion(IDC_DEST_EDIT);
//
//	m_edtCharge.SetFocus();
//}



BOOL CConsignModiDlg::SearchRegion(long nFlag)
{
	CSearchRegionDlg dlg;
	dlg.m_bReturnLiID = TRUE;
	dlg.m_strSearch = "";

	if(dlg.DoModal() == IDOK)
	{
		if(nFlag == IDC_DEST_EDIT)
		{
			
			m_nPOIID = dlg.m_nDongID;

			CPOIUnit *pPoi = m_poiNew.GetDongPOI(m_nPOIID);

			if(pPoi)
			{
				CString strTemp = "";
				strTemp = pPoi->GetFullName(FALSE);
				m_edtDest.SetWindowText(pPoi->GetDong());
				m_edtDestDetail.SetWindowText(strTemp);
			}

			
		}
		

		
		//return TRUE;
	}

	return FALSE;
}


void CConsignModiDlg::OnTimer(UINT nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CMyDialog::OnTimer(nIDEvent);
}
