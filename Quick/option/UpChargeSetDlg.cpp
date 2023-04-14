// UpChargeSetDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "UpChargeSetDlg.h"

#define DAY_COUNT 7

int _nDayCheck[] = {IDC_SUNDAY_CHECK, IDC_MONDAY_CHECK, IDC_TUESDAY_CHECK, IDC_WEDNESDAY_CHECK, IDC_THURSDAY_CHECK, IDC_FRIDAY_CHECK, IDC_SATURDAY_CHECK};

int _nDayTimeComboStart[] = {IDC_SUNDAY_START_COMBO, IDC_MONDAY_START_COMBO, IDC_TUESDAY_START_COMBO, IDC_WEDNESDAY_START_COMBO, IDC_THURSDAY_START_COMBO, IDC_FRIDAY_START_COMBO, IDC_SATURDAY_START_COMBO};
int _nDayTimeComboEnd[] = {IDC_SUNDAY_END_COMBO, IDC_MONDAY_END_COMBO, IDC_TUESDAY_END_COMBO, IDC_WEDNESDAY_END_COMBO, IDC_THURSDAY_END_COMBO, IDC_FRIDAY_END_COMBO, IDC_SATURDAY_END_COMBO};


// CUpChargeSetDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CUpChargeSetDlg, CMyDialog)

CUpChargeSetDlg::CUpChargeSetDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CUpChargeSetDlg::IDD, pParent)
{

}

CUpChargeSetDlg::~CUpChargeSetDlg()
{
}

void CUpChargeSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USE_TIME_SET_CHECK, m_chkUseTimeSet);
}


BEGIN_MESSAGE_MAP(CUpChargeSetDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &CUpChargeSetDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CUpChargeSetDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


BOOL CUpChargeSetDlg::CheckControl()
{
	char *szDayOfWeek[] = {"��", "��", "ȭ", "��", "��", "��", "��"};

	for(int i=0; i<DAY_COUNT; i++)
	{
		long nStart = ((CComboBox*)GetDlgItem(_nDayTimeComboStart[i]))->GetCurSel();
		long nDest = ((CComboBox*)GetDlgItem(_nDayTimeComboEnd[i]))->GetCurSel();

		if(nStart > nDest)
		{
			CString strTemp;
			strTemp.Format("%s���� ���۽ð��� ����ð����� Ů�ϴ�", szDayOfWeek[i]);
			MessageBox(strTemp, "Ȯ��", MB_ICONINFORMATION);
			return FALSE;
		}
	}

	return TRUE;
}

// CUpChargeSetDlg �޽��� ó�����Դϴ�.

void CUpChargeSetDlg::OnBnClickedOk()
{
	if(!CheckControl())
		return;

	CMkCommand cmd(m_pMkDb, "update_up_charge_time_set");
	cmd.AddParameter(m_nCompany);
	cmd.AddParameter(m_chkUseTimeSet.GetCheck());

	for(int i=0; i<DAY_COUNT; i++)
	{
		cmd.AddParameter(((CButton*)GetDlgItem(_nDayCheck[i]))->GetCheck());
		cmd.AddParameter(GetCombo(_nDayTimeComboStart[i]));
		cmd.AddParameter(GetCombo(_nDayTimeComboEnd[i]));
	}

	if(cmd.Execute())
	{
		MessageBox("����Ǿ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		OnOK();
	}
}

void CUpChargeSetDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}

BOOL CUpChargeSetDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	for(int i=0; i<DAY_COUNT; i++)
	{
		((CButton*)GetDlgItem(_nDayCheck[i]))->SetCheck(FALSE);
		((CComboBox*)GetDlgItem(_nDayTimeComboStart[i]))->SetCurSel(0);
		((CComboBox*)GetDlgItem(_nDayTimeComboEnd[i]))->SetCurSel(0);
	}

	RefreshDlg();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CUpChargeSetDlg::RefreshDlg()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_up_charge_time_set");
	cmd.AddParameter(m_nCompany);

	if(!rs.Execute(&cmd))
		return;

	if(rs.GetRecordCount() == 0)
		return;

	BOOL bTemp; long nTemp;
	rs.GetFieldValue("bUseTimeSet", bTemp); m_chkUseTimeSet.SetCheck(bTemp);
	rs.GetFieldValue("bSunday", bTemp); ((CButton*)GetDlgItem(IDC_SUNDAY_CHECK))->SetCheck(bTemp);
	rs.GetFieldValue("nSundayStart", nTemp); SetCombo(nTemp, IDC_SUNDAY_START_COMBO);
	rs.GetFieldValue("nSundayEnd", nTemp); SetCombo(nTemp, IDC_SUNDAY_END_COMBO);
	rs.GetFieldValue("bMonday", bTemp); ((CButton*)GetDlgItem(IDC_MONDAY_CHECK))->SetCheck(bTemp);
	rs.GetFieldValue("nMondayStart", nTemp); SetCombo(nTemp, IDC_MONDAY_START_COMBO);
	rs.GetFieldValue("nMondayEnd", nTemp); SetCombo(nTemp, IDC_MONDAY_END_COMBO);
	rs.GetFieldValue("bTuesday", bTemp); ((CButton*)GetDlgItem(IDC_TUESDAY_CHECK))->SetCheck(bTemp);
	rs.GetFieldValue("nTuesdayStart", nTemp); SetCombo(nTemp, IDC_TUESDAY_START_COMBO);
	rs.GetFieldValue("nTuesdayEnd", nTemp); SetCombo(nTemp, IDC_TUESDAY_END_COMBO);
	rs.GetFieldValue("bWednesday", bTemp); ((CButton*)GetDlgItem(IDC_WEDNESDAY_CHECK))->SetCheck(bTemp);
	rs.GetFieldValue("nWednesdayStart", nTemp); SetCombo(nTemp, IDC_WEDNESDAY_START_COMBO);
	rs.GetFieldValue("nWednesdayEnd", nTemp); SetCombo(nTemp, IDC_WEDNESDAY_END_COMBO);
	rs.GetFieldValue("bThursday", bTemp); ((CButton*)GetDlgItem(IDC_THURSDAY_CHECK))->SetCheck(bTemp);
	rs.GetFieldValue("nThursdayStart", nTemp); SetCombo(nTemp, IDC_THURSDAY_START_COMBO);
	rs.GetFieldValue("nThursdayEnd", nTemp); SetCombo(nTemp, IDC_THURSDAY_END_COMBO);
	rs.GetFieldValue("bFriday", bTemp); ((CButton*)GetDlgItem(IDC_FRIDAY_CHECK))->SetCheck(bTemp);
	rs.GetFieldValue("nFridayStart", nTemp); SetCombo(nTemp, IDC_FRIDAY_START_COMBO);
	rs.GetFieldValue("nFridayEnd", nTemp); SetCombo(nTemp, IDC_FRIDAY_END_COMBO);
	rs.GetFieldValue("bSaturday", bTemp); ((CButton*)GetDlgItem(IDC_SATURDAY_CHECK))->SetCheck(bTemp);
	rs.GetFieldValue("nSaturdayStart", nTemp); SetCombo(nTemp, IDC_SATURDAY_START_COMBO);
	rs.GetFieldValue("nSaturdayEnd", nTemp); SetCombo(nTemp, IDC_SATURDAY_END_COMBO);
}

void CUpChargeSetDlg::SetCombo(long nTime, UINT nID)
{
	CComboBox *pBox = (CComboBox*)GetDlgItem(nID);

	for(int i=0; i<pBox->GetCount(); i++)
	{
		CString strTime; pBox->GetLBText(i, strTime);

		if(atoi(strTime) == nTime)
		{
			pBox->SetCurSel(i);
			return;
		}
	}

	pBox->SetCurSel(0);
}

long CUpChargeSetDlg::GetCombo(UINT nID)
{
	CComboBox *pBox = (CComboBox*)GetDlgItem(nID);
	long nIndex = pBox->GetCurSel();

	if(nIndex == -1)
		return 7;

	CString strTime; pBox->GetLBText(nIndex, strTime);

	return atoi(strTime);
}
