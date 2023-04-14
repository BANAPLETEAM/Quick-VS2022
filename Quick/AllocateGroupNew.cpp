#include "stdafx.h"
#include "resource.h"
#include "AllocateGroupNew.h"


// CAllocateGroupNew 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAllocateGroupNew, CMyDialog)
CAllocateGroupNew::CAllocateGroupNew(CWnd* pParent /*=NULL*/)
: CMyDialog(CAllocateGroupNew::IDD, pParent)
, m_sGNo("")
, m_sName("")
{
}

CAllocateGroupNew::~CAllocateGroupNew()
{
}

void CAllocateGroupNew::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME_EDIT, m_sName);
	DDX_Text(pDX, IDC_GNO_EDIT, m_sGNo);
//	DDX_Control(pDX, IDC_GNO_EDIT, m_sName);
}


BEGIN_MESSAGE_MAP(CAllocateGroupNew, CMyDialog)
	ON_BN_CLICKED(IDC_OK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_CANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_DEL, &CAllocateGroupNew::OnBnClickedDel)
END_MESSAGE_MAP()


// CAllocateGroupNew 메시지 처리기입니다.
BOOL CAllocateGroupNew::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	if(bNewMode)
	{
		SetWindowText("배차 그룹명 추가");
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "select_allocate_gno");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
		if(!pRs.Execute(&pCmd)) return FALSE;

		if(!pRs.IsEOF())
		{
			int nGNo;
			CString sName;

			pRs.GetFieldValue("nGNo", nGNo);
			m_sGNo.Format("%d", nGNo);

			UpdateData(FALSE);
		}
		pRs.Close();
	}
	else
	{
		SetWindowText("배차 그룹명 수정");
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CAllocateGroupNew::OnBnClickedOk()
{
	if(bNewMode)
	{
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb,"insert_allocate_group");
		UpdateData(TRUE);

		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), atol(m_sGNo));
		pCmd.AddParameter(typeString, typeInput, m_sName.GetLength(), m_sName);

		if(pCmd.Execute())
		{
			MessageBox("배차그룹을 추가하였습니다.", "확인", MB_ICONINFORMATION);
			OnOK();
		}
		else {
			MessageBox("배차그룹 생성을 실패하였습니다.", "확인", MB_ICONINFORMATION);	
			OnCancel();
		}
	}
	else
	{
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb,"update_allocate_group");
		UpdateData(TRUE);

		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), atol(m_sGNo));
		pCmd.AddParameter(typeString, typeInput, m_sName.GetLength(), m_sName);

		if(pCmd.Execute())
		{
			LU->UpdateAllocateGroup(atoi(m_sGNo), m_sName);
			MessageBox("배차그룹을 수정하였습니다.", "확인", MB_ICONINFORMATION);
			OnOK();
		}
		else {
			MessageBox("배차그룹 수정을 실패하였습니다.", "확인", MB_ICONINFORMATION);	
			OnCancel();
		}
	}
}

void CAllocateGroupNew::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();	
}

void CAllocateGroupNew::OnBnClickedDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
