// SMSStateDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SMSStateDlg.h"



// CSMSStateDlg 대화 상자입니다.

IMPLEMENT_DYNCREATE(CSMSStateDlg, CMyDialog)
BEGIN_MESSAGE_MAP(CSMSStateDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SELECT_BTN, OnBnClickedSelectBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
END_MESSAGE_MAP()
CSMSStateDlg::CSMSStateDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CSMSStateDlg::IDD, pParent)
{
	COleDateTimeSpan dtSpan(-1,0,0,0);
	m_dtCur = COleDateTime::GetCurrentTime() - dtSpan;
}

CSMSStateDlg::~CSMSStateDlg()
{
}

void CSMSStateDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_DT_STATIC, m_dtChange);
}

BOOL CSMSStateDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 

	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | 
		LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);

	int nItem = 0;
	m_List.InsertColumn(nItem++, "예약된시간", LVCFMT_CENTER, 80);	
	m_List.InsertColumn(nItem++, "예약비율", LVCFMT_RIGHT, 70);
	m_List.InsertColumn(nItem++, "비고", LVCFMT_LEFT, 120);
	m_List.InsertColumn(nItem++, 
		GetCurBranchInfo()->nCompanyCode == 10 ? "3번서버" : "",LVCFMT_LEFT, 80);


	RefreshList();
	return TRUE;  
}
void CSMSStateDlg::RefreshList()
{
	UpdateData(TRUE);
	COleDateTime dt;
	long nCount, nRate;
	int  nItem = 0;
	COleDateTime dtChange(COleDateTime::GetCurrentTime());

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_sms_state");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), 0);

	if(!pRs.Execute(&pCmd)) return;	

	if(pRs.GetRecordCount() > 0)
	{

		for(nItem = 0; nItem < pRs.GetRecordCount(); nItem++)
		{
			CString sRate = "";

			pRs.GetFieldValue("dt", dt);
			pRs.GetFieldValue("nCount", nCount);
			pRs.GetFieldValue("nRate", nRate);
			pRs.GetFieldValue("dtChange", dtChange);


			sRate.Format("%ld%%", nRate);
			m_List.InsertItem(nItem, dt.Format("%p %I:%M"));
			m_List.SetItemText(nItem, 1, sRate);
			m_List.SetItemText(nItem, 2, GetSMSStateString(nCount));
			if(GetCurBranchInfo()->nCompanyCode == 10)
				m_List.SetItemText(nItem, 3, GetMyNumberFormat(nCount));

			COleDateTime *dtNew = new COleDateTime;
			dtNew->m_dt = dt;

			m_List.SetItemData(nItem, (DWORD_PTR)dtNew);


			pRs.MoveNext();
		}

	}
	else
	{
		m_List.InsertItem(nItem, "예약이");
		m_List.SetItemText(nItem , 1, "없습");
		m_List.SetItemText(nItem , 2, "니다.");	
	}
	CString sMsg = "";
	COleDateTimeSpan dtSpan(0,0,3,0);
	COleDateTime dtNextChange = dtChange + dtSpan;
	dtNextChange.Format("%I:%M");
	sMsg.Format(":%s,  다음갱신시간:%s", dtChange.Format("%p %I:%M"), dtNextChange.Format("%I:%M"));
	m_dtChange.SetWindowText(sMsg);

	pRs.Close();
}

CString CSMSStateDlg::GetSMSStateString(long nCount)
{

	CString sMsg = 	"";
	if(nCount < 50000)
		sMsg = "상태양호";
	else if(nCount >= 50000 && nCount < 70000 )
		sMsg = "SMS발송비중(하)";
	else if(nCount >= 70000 && nCount < 100000 )
		sMsg = "SMS발송비중(중)";
	else if(nCount >= 100000 )
		sMsg = "SMS발송비중(상)";

	return sMsg;
}


COleDateTime CSMSStateDlg::GetSelectTime()
{


	return m_dtCur;
}




void CSMSStateDlg::OnBnClickedSelectBtn()
{
	long nItem = m_List.GetSelectionMark();
	COleDateTime *dt;
	if(nItem < 0 )
	{
		MessageBox("해당시간을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}


	dt = (COleDateTime*)m_List.GetItemData(nItem);
	CString s = dt->Format("%Y-%m-%d %H:%M:%S");
	m_dtCur = dt->m_dt;
	OnOK();
}

void CSMSStateDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}

void CSMSStateDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnBnClickedSelectBtn();
	*pResult = 0;
}
