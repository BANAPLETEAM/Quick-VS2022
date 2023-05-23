// NoticeDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "SecurityLogDlg.h"


// CSecurityLogDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSecurityLogDlg, CMyDialog)
CSecurityLogDlg::CSecurityLogDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSecurityLogDlg::IDD, pParent)
{
}

CSecurityLogDlg::~CSecurityLogDlg()
{
}

void CSecurityLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_BAR_STATIC, m_BarStatic);
}


BEGIN_MESSAGE_MAP(CSecurityLogDlg, CMyDialog)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnNMClickList1)
END_MESSAGE_MAP()


// CSecurityLogDlg �޽��� ó�����Դϴ�.

BOOL CSecurityLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow(GetDesktopWindow());

	CImageList ImageList; 
	ImageList.Create(1,18,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//LVS_EX_GRIDLINES
	m_List.InsertColumn(0,"��¥",LVCFMT_LEFT, 110);
	m_List.InsertColumn(1,"����",LVCFMT_LEFT, 300);
	m_List.InsertColumn(2,"������ȸ��",LVCFMT_LEFT, 80);
	m_List.InsertColumn(3,"�����ڸ�",LVCFMT_LEFT, 90);
	m_List.InsertColumn(4,"PC��ȣ",LVCFMT_LEFT, 60);
	m_List.InsertColumn(5,"��ũID",LVCFMT_LEFT, 70);
	m_List.InsertColumn(6,"��Ʈ��ũID",LVCFMT_LEFT, 70);
	m_List.InsertColumn(7,"�α��νð�",LVCFMT_LEFT, 80);
	m_List.InsertColumn(8,"ȣ��Ʈ��",LVCFMT_LEFT, 70);

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CSecurityLogDlg::RefreshList()
{
	/*
	m_List.DeleteAllItems();
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_security_log");
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_ci.m_nCompanyCode);
	if(!pRs.Execute(&pCmd)) return;

	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{
		COleDateTime dtWrite;
		long nType, nStaffNo;
		CString strData1, strData2, strData3, strFormat;
		char buffer[20];
		COLOR_STRUCT *pcs = new COLOR_STRUCT;


		pRs.GetFieldValue("nType", nType);
		pRs.GetFieldValue("nStaffNo", nStaffNo);
		pRs.GetFieldValue("sData1", strData1);
		pRs.GetFieldValue("sData2", strData2);
		pRs.GetFieldValue("sData3", strData3);
		pRs.GetFieldValue("dtWrite", dtWrite);

		strFormat = GetSecurityLog(nType, strData1, strData2, strData3);

		m_List.InsertItem(i, dtWrite.Format("%Y/%m/%d"));
		m_List.SetItemText(i, 1, dtWrite.Format("%H:%M"));
		m_List.SetItemText(i, 2, GetSecurityType(nType));
		m_List.SetItemText(i, 3, ltoa(nStaffNo, buffer, 10));
		m_List.SetItemText(i, 4, strFormat);
	
		pcs->crText = RGB(0,0,0);
		if(i % 2 == 0) 
			pcs->crBk = RGB(245, 245, 245);
		else 
			pcs->crBk = RGB(255, 255, 255);

		m_List.SetItemData(i, (DWORD_PTR)pcs); 
		pRs.MoveNext();
	}
	pRs.Close();
	*/
	m_List.DeleteAllItems();
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_security_log_1");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), LF->GetCurBranchInfo()->bIntegrated);
	if(!pRs.Execute(&pCmd)) return;

	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{
		COleDateTime dtWrite;
		long nType, nStaffNo;
		CString strData1, strData2, strData3, strFormat;
		char buffer[20];
		COLOR_STRUCT *pcs = new COLOR_STRUCT;
		long nPCNum;
		CString strStaffInfo, strHddID;
		COleDateTime dtLoginTime;
		CString strMacAddress, strStaffCompanyInfo;
		CString strHostName;

		pRs.GetFieldValue("nType", nType);
		pRs.GetFieldValue("nStaffNo", nStaffNo);
		pRs.GetFieldValue("sData1", strData1);
		pRs.GetFieldValue("sData2", strData2);
		pRs.GetFieldValue("sData3", strData3);
		pRs.GetFieldValue("dtWrite", dtWrite);
		pRs.GetFieldValue("nPCNum", nPCNum);
		pRs.GetFieldValue("sStaffInfo", strStaffInfo);
		pRs.GetFieldValue("sHddID", strHddID);
		pRs.GetFieldValue("dtLoginTime", dtLoginTime);
		pRs.GetFieldValue("sMacAddress", strMacAddress);
		pRs.GetFieldValue("sStaffCompanyInfo", strStaffCompanyInfo);
		pRs.GetFieldValue("sHostName", strHostName);


		strFormat = GetSecurityLog(nType, strData1, strData2, strData3);

		m_List.InsertItem(i, dtWrite.Format("%Y/%m/%d %H:%M"));
		m_List.SetItemText(i, 1, strFormat);
		m_List.SetItemText(i, 2, strStaffCompanyInfo);
		m_List.SetItemText(i, 3, strStaffInfo);
		m_List.SetItemText(i, 4, ltoa(nPCNum, buffer, 10));
		m_List.SetItemText(i, 5, strHddID);
		m_List.SetItemText(i, 6, strMacAddress);
		m_List.SetItemText(i, 7, dtLoginTime.Format("%Y/%m/%d %H:%M"));
		m_List.SetItemText(i, 8, strHostName);

		pcs->crText = RGB(0,0,0);
		if(i % 2 == 0) 
			pcs->crBk = RGB(245, 245, 245);
		else 
			pcs->crBk = RGB(255, 255, 255);

		m_List.SetItemData(i, (DWORD_PTR)pcs); 
		pRs.MoveNext();
	}
	pRs.Close();
}

HBRUSH CSecurityLogDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMyDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(pWnd->GetDlgCtrlID() == IDC_BAR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);	
		return ::CreateSolidBrush(RGB(245,245,245));
	}

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}

CString CSecurityLogDlg::GetSecurityLog(long nType, CString strData1, CString strData2, CString strData3)
{

	//����, ����, ���� �������� �������鼭 case ������ ���׹�����..
	//�ߺ��Ǵ� ��ȣ�� �ִ��� Ȯ���� �߰� �ؾ���!!

	CString strFormat;

	switch(nType)
	{
	case 100:
		strFormat.Format("�Ϸ� ���� ������ ������(������ȣ: %s, �����ݾ�:%s, ���ݾ�:%s)", strData1, strData2, strData3);
		break;
	case 101:
		strFormat.Format("����ȭ�鿡�� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 102:
		strFormat.Format("��������â[����ݳ���]���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 103:
		strFormat.Format("���Ӹ���Ʈ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 104:
		strFormat.Format("������������� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 105:
		strFormat.Format("���������ǿ��� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 106:
		strFormat.Format("�̿������ǿ��� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;

	case 201:
		strFormat.Format("����[������] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 202:
		strFormat.Format("����[�������ȸ] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 203:
		strFormat.Format("����[�ű԰���ȸ] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 204:
		strFormat.Format("����[�ҷ�����ȸ] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 205:
		strFormat.Format("����[�̿�������] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 206:
		strFormat.Format("����[�׷����_�׷�] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 211:
		strFormat.Format("����[�޸��] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 212:
		strFormat.Format("����[�ߺ���] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 213:
		strFormat.Format("����[�Ⱓ����ȸ] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 214:
		strFormat.Format("����[�ҷ�����ȸ2] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 215:
		strFormat.Format("����[���ܹ�ȣ] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;

	case 301:
		strFormat.Format("��������[������] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 351:
		strFormat.Format("��������[�ſ�����] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;

	case 302:
		strFormat.Format("���������[�������] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 303:
		strFormat.Format("���������[��纰�Ǽ�] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	//case 306:
	//	strFormat.Format("������[����������] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
	//	break;
	//case 308:
	//	strFormat.Format("������[��������] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
	//	break;
	case 310:
		strFormat.Format("��������[��ü�ſ�����] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 312:
		strFormat.Format("���������[���ſ�����] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 314:
		strFormat.Format("��������[�׷�����] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 315:
		strFormat.Format("��������[�׷�����][���] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;

	case 316:
		strFormat.Format("��������[�׷�ܿ���] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;


	case 320:
		strFormat.Format("��������[���ϸ���] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 321:
		strFormat.Format("���������[����ϸ���] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 322:
		strFormat.Format("���������[��纰�Ǽ�(���Ա�)] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 323:
		strFormat.Format("��������[ī���õ¡��] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 324:
		strFormat.Format("��������[ī���������] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 325:
		strFormat.Format("���������[���¶������] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 326:
		strFormat.Format("���������[�����ݿ�û] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 327:
		strFormat.Format("���������[�ܸ����̷°���] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 328:
		strFormat.Format("���������[����������] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 329:
		strFormat.Format("���������[��������] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 330:
		strFormat.Format("����[���ݿ�����] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 331:
		strFormat.Format("����[���ϸ�����ݰ���] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;

	case 401:
		strFormat.Format("������[��������] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 402:  
		strFormat.Format("������[������(�Ϻθ������)] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 406:
		strFormat.Format("������[��缼�λ���(�Ϻθ������)] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 404:
		strFormat.Format("������[�����̿��] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 405:
		strFormat.Format("������[��ٰ���] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 407:
		strFormat.Format("������[�������] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;

	case 501:
		strFormat.Format("�Ա���[�Աݰ���] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 502:
		strFormat.Format("�Ա���[����ķα�] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 503:
		strFormat.Format("�Ա���[����ķα�] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 504:
		strFormat.Format("�Ա���[���Աݰ���] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 505:
		strFormat.Format("�Ա���[�������� ��������] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 506:
		strFormat.Format("�Ա���[��簡������Ҵ�] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;

	case 602:
		strFormat.Format("�����[�����ݼ�����] �ǿ��� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 603:
		strFormat.Format("�����[���м�] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 604:
		strFormat.Format("�����[���������] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 605:
		strFormat.Format("�����[���������_�ݼ�] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 304:
		strFormat.Format("�����[�Ϻ��Ǽ�] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 305:
		strFormat.Format("�����[����������] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 306:
		strFormat.Format("�����[���������곻��] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 313: 
		strFormat.Format("�����[������] ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 608:
		strFormat.Format("�����[SMS����] �ǿ��� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 609:
		strFormat.Format("�����[�ڼ�������] �ǿ��� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;
	case 610:
		strFormat.Format("�����[�ű԰���] �ǿ��� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;

	case 701:
		strFormat.Format("��ī��Ʈ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;

	case 801:
		strFormat.Format("��ī��Ʈ���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;

	case 901:
		strFormat.Format("�׷�����[��������]���� %s���� �����Ͱ� ������ ��ȯ��", strData1);
		break;

	//����, ����, ���� �������� �������鼭 case ������ ���׹�����..
		//�ߺ��Ǵ� ��ȣ�� �ִ��� Ȯ���� �߰� �ؾ���!!			
	}
	return strFormat;
}

CString CSecurityLogDlg::GetSecurityType(long nType)
{
	if(nType >= 100 && nType < 200)
		return "����";
	else if(nType >= 200 && nType < 300)
		return "��";

	return "��Ÿ";
}

void CSecurityLogDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
//	if(!(pNMListView->uNewState & LVIS_SELECTED)) return;
	if(pNMListView->iItem < 0) return;

	MessageBox(m_List.GetItemText(pNMListView->iItem, 1), "���ȷα�", MB_ICONINFORMATION);
	*pResult = 0;
}
