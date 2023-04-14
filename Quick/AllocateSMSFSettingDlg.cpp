// AllocateSMSFSettingDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "AllocateSMSFSettingDlg.h"


#define REPLACE_CHAR_COUNT 41

CString sMainChar[REPLACE_CHAR_COUNT] = {"[@고객명]", "[@대표번호]", "[@휴대폰]", "[@부서]", "[@담당자]", "[@출발동]", "[@상세위치]", "[@메모]", "[@마일리지]",
"[@고객명_출]", "[@대표번호_출]", "[@휴대폰_출]", "[@부서_출]", "[@담당자_출]", "[@출발동_출]", "[@상세위치_출]", 
"[@고객명_도]", "[@대표번호_도]", "[@휴대폰_도]", "[@부서_도]", "[@담당자_도]", "[@도착동_도]", "[@상세위치_도]", 
"[@접수시간]", "[@적요]", "[@물품]", "[@인터콜]", "[@지불]", "[@차량]", "[@운송]", "[@급]",
"[@합계]", "[@합계천]", "[@합계백]", "[@탁송]", "[@탁송천]", "[@탁송백]", "[@사번]", "[@기사명]", "[@기사전화번호]", "[@기사위치URL]"};
CString sReplace[REPLACE_CHAR_COUNT] = {"로지소프트", "15990707", "01000000000", "개발팀", "홍길동", "삼성동", "세풍빌딩6층", "수고하세요", "20000", 
"로지소프트", "15990707", "01000000000", "개발팀", "홍길동", "삼성동", "세풍빌딩6층",
"무브소프트", "15990808", "01012345678", "영업팀", "이몽룡", "대치동", "719-33번지",
"14:35", "적요입니다", "물품입니다", "인터콜적요", "선불", "오토", "왕복", "일반",
"8000", "8", "80", "5000", "5", "50", "100", "홍길동", "01012345678", "0070.co.kr/q/1234"};


// CAllocateSMSFSettingDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAllocateSMSFSettingDlg, CMyDialog)
CAllocateSMSFSettingDlg::CAllocateSMSFSettingDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAllocateSMSFSettingDlg::IDD, pParent)
{
}

CAllocateSMSFSettingDlg::~CAllocateSMSFSettingDlg()
{
}

void CAllocateSMSFSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INPUT_EDIT, m_edtInput);
	DDX_Control(pDX, IDC_SMAPLE_EDIT, m_edtSample);
	DDX_Control(pDX, IDC_BYTE_STATIC, m_stcByte);
}


BEGIN_MESSAGE_MAP(CAllocateSMSFSettingDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, OnBnClickedSaveButton)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON, OnBnClickedCloseButton)
	ON_EN_CHANGE(IDC_INPUT_EDIT, OnEnChangeInputEdit)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_MENU_BUTTON11, IDC_MENU_BUTTON64, OnBnClicked)
	
END_MESSAGE_MAP()

void CAllocateSMSFSettingDlg::OnBnClicked(UINT nFlag)
{
	CString sChar = sMainChar[nFlag - IDC_MENU_BUTTON11];
	CString sInput; m_edtInput.GetWindowText(sInput);

	CStringW sCharW(sChar);
	CStringW sInputW(sInput);

	int nStartSel, nDestSel; 

	m_edtInput.GetSel(nStartSel, nDestSel);

	if(nStartSel == -1) return; 

	CString sResult = CString(sInputW.Left(nStartSel)) + CString(sCharW) + CString(sInputW.Right(sInputW.GetLength() - nDestSel));
	m_edtInput.SetWindowText(sResult);

	OnEnChangeInputEdit();  

	m_edtInput.SetFocus();
	m_edtInput.SetSel(nStartSel + sCharW.GetLength(), nStartSel + sCharW.GetLength());

}

// CAllocateSMSFSettingDlg 메시지 처리기입니다.

BOOL CAllocateSMSFSettingDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	FillMap();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAllocateSMSFSettingDlg::FillMap(CMkRecordset *pRs)
{
	m_map.clear();

	if(pRs == NULL)
	{
		for(int i=0; i<REPLACE_CHAR_COUNT; i++)
			m_map.insert(SMS_RELACE_MAP::value_type(sMainChar[i], sReplace[i]));

		m_edtInput.SetWindowText(m_strInput);
		m_edtSample.SetWindowText(GetReplaceChar((CStringW)m_strInput));
		m_stcByte.SetWindowText(::GetStringFromLong(m_edtSample.GetWindowTextLength()) + " Byte");
	}
	else
	{
		for(int i=0; i<REPLACE_CHAR_COUNT; i++)
		{
			CString sData = "";
			pRs->GetFieldValue(i, sData);
			m_map.insert(SMS_RELACE_MAP::value_type(sMainChar[i], sData));
		}
	}	
}

void CAllocateSMSFSettingDlg::OnBnClickedSaveButton()
{
	m_edtInput.GetWindowText(m_strInput);
	OnOK();
}

void CAllocateSMSFSettingDlg::OnBnClickedCloseButton()
{
	OnCancel();
}

void CAllocateSMSFSettingDlg::OnEnChangeInputEdit()
{
	CString sInput; m_edtInput.GetWindowText(sInput);
	CStringW sInputW(sInput);

    m_edtSample.SetWindowText(GetReplaceChar(sInputW));
	m_stcByte.SetWindowText(::GetStringFromLong(m_edtSample.GetWindowTextLength()) + " Byte");
}

CString CAllocateSMSFSettingDlg::GetReplaceChar(CStringW &sInputW, long nNextStartIndex)
{	
	SMS_RELACE_MAP::iterator it;

	for(it = m_map.begin(); it != m_map.end(); it++)
	{
		long nLastIndex = 0; 
		long nStartIndex = 0;

		CString sCount = "";
		long nLength = sInputW.GetLength();
		nStartIndex = sInputW.Find((CStringW)it->first, nNextStartIndex);
 
		long nFIndNextStartIndex = sInputW.Find((CStringW)it->first, nStartIndex+1);

		if(nFIndNextStartIndex != -1)
			GetReplaceChar(sInputW, nFIndNextStartIndex);

		if(nStartIndex >= 0)
		{
			GetLastIndex(sInputW, nStartIndex, nLastIndex, sCount);

			if(nLastIndex == 0)
				nLastIndex = nStartIndex + ((CStringW)it->first).GetLength() -1;

			CStringW sLeftW(sInputW.Left(max(nStartIndex, 0)));
			CStringW sMiddleW(it->second);
			CStringW sRightW(sInputW.Mid(nLastIndex+1, sInputW.GetLength() - nStartIndex));

			if(sCount != "")
			{
				sMiddleW = sMiddleW.Left(atoi(sCount));
			}

			sInputW = sLeftW + sMiddleW+ sRightW;

			/*
			CString sMain;
			CStringW sReplaceW = (CStringW)it->second;

			if(sCount == "")
			{
				sMain = (it->first);
			}
			else
			{
				sMain = (it->first + "." + sCount);
				sReplaceW = sReplaceW.Left(atoi((sCount)));
			}			

			CString sReplace(sReplaceW);

			sInput.Replace(sMain, sReplace);
			*/			
		}
	}

	CString sOutput(sInputW);
	return sOutput;
}

void CAllocateSMSFSettingDlg::GetLastIndex(CStringW sInput, long nStartIndex, long &nLastIndex, CString &sCount)
{
	BOOL bFInd = FALSE;
	BOOL bFindDash = FALSE;
	long nFIndIndex = 0;

	for(int j=nStartIndex; j<sInput.GetLength(); j++)
	{
		if((sInput.Mid(j,1) == ']') && (bFindDash == FALSE))
		{
			nFIndIndex = j + 1;
			bFindDash = TRUE;  
			nLastIndex = j;
			continue;
		}

		if((bFindDash == TRUE) && (bFInd == FALSE))
		{
			if(sInput.Mid(nFIndIndex,1) == '.')
			{
				bFInd = TRUE;  
				continue;
			}
			else
				break;
		}
		
		if(bFInd)
		{
            if(IsNumeric((CString)sInput.Mid(j,1)) == TRUE)
			{
				sCount += sInput.Mid(j,1);
				nLastIndex = j;
			}
			else
			{
				break;
			}
		}
	}

	return;
}