// AddMmsImageDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "AddMmsImageDlg.h"
#include "MmsImageView.h"


// CAddMmsImageDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAddMmsImageDlg, CDialog)

CAddMmsImageDlg::CAddMmsImageDlg(CWnd* pParent /*=NULL*/)
: CDialog(CAddMmsImageDlg::IDD, pParent)
{
	m_nAddImageCount = 0;

	for(int i=0; i<MAX_MMS_IMAGE_COUNT; i++)
	{
		m_nImageSize[i] = 0;
		m_strImage[i] = "";
	}		
}

CAddMmsImageDlg::~CAddMmsImageDlg()
{
}

void CAddMmsImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_IMAGE_STATIC, m_stcImage);

}


BEGIN_MESSAGE_MAP(CAddMmsImageDlg, CDialog)
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_FILE_PATH_BTN1, OnBnClickedFilePathBtn1)
	ON_BN_CLICKED(IDC_FILE_PATH_BTN2, OnBnClickedFilePathBtn2)
	ON_BN_CLICKED(IDC_FILE_PATH_BTN3, OnBnClickedFilePathBtn3)
	ON_BN_CLICKED(IDC_FILE_OPEN_BTN1, OnBnClickedFileOpenBtn1)
	ON_BN_CLICKED(IDC_FILE_OPEN_BTN2, OnBnClickedFileOpenBtn2)
	ON_BN_CLICKED(IDC_FILE_OPEN_BTN3, OnBnClickedFileOpenBtn3)
	ON_BN_CLICKED(IDC_FILE_DELETE_BTN1, OnBnClickedFileDeleteBtn1)
	ON_BN_CLICKED(IDC_FILE_DELETE_BTN2, OnBnClickedFileDeleteBtn2)
	ON_BN_CLICKED(IDC_FILE_DELETE_BTN3, OnBnClickedFileDeleteBtn3)
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOKBtn)
END_MESSAGE_MAP()


BOOL CAddMmsImageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rc; 
	m_stcImage.GetWindowRect(rc);
	ScreenToClient(rc);

	m_context.m_pNewViewClass = RUNTIME_CLASS(CMmsImageView);
	m_pImageView = (CMmsImageView*)((CFrameWnd*)this)->CreateView(&m_context);
	ASSERT(m_pImageView);

	m_pImageView->OnInitialUpdate();
	m_pImageView->ShowWindow(SW_NORMAL);
	m_pImageView->MoveWindow(&rc);

	if(m_nAddImageCount > 0)
	{
		for(int i=0; i<m_nAddImageCount; i++)
			SetFileNameInfo(i, m_strImage[i], m_nImageSize[i], TRUE);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


// CAddMmsImageDlg 메시지 처리기입니다.
void CAddMmsImageDlg::OpenImageFile(long nNumber)
{
	char szFilter[] = "Image Files(*.BMP, *.GIF, *.JPG, *.PNG, *.bmp, *.gif, *.jpg, *.png) | *.BMP;*.GIF;*.JPG;*.PNG;*.bmp;*.gif;*.jpg;*.png | All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);

	if(IDOK != dlg.DoModal()) 
		return;

	CString strFileName = dlg.GetPathName();

	m_pImageView->m_imgMms[nNumber].Destroy();
	if(m_pImageView->m_imgMms[nNumber].Load(strFileName))
	{
		MessageBox("이미지 로드에 실패했습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	if(strFileName.Right(3) != "jpg" && strFileName.Right(3) != "JPG") // 파일변환
	{
		srand(time(NULL)); 
		CString strTemp = "C:\\SmartD\\" + GetOnlyfileName(strFileName) + "_" + ::GetStringFromLong(rand()%1000000)   + ".jpg";

		m_pImageView->m_imgMms[nNumber].Save(strTemp, Gdiplus::ImageFormatJPEG);
		m_pImageView->m_imgMms[nNumber].Destroy();
		if(m_pImageView->m_imgMms[nNumber].Load(strTemp)) 
		{
			MessageBox("이미지 로드에 실패했습니다", "확인", MB_ICONINFORMATION);
			return;
		}

		strFileName = strTemp;
		m_strDeleteFileArry.Add(strTemp);
	}

	long nSize = GetFileSize(strFileName);

	if(GetCurImageSize() + nSize > 700)
	{
		MessageBox("전송 하시려는 파일의 전체 사이즈가 700Kb를 초과 할수 업습니다", "확인", MB_ICONINFORMATION);
		m_pImageView->m_imgMms[nNumber].Destroy();
		return;
	}

	SetFileNameInfo(nNumber, strFileName, nSize); 
}

long CAddMmsImageDlg::GetFileSize(CString strPath)
{
	CStdioFile file;
	file.Open( _T( strPath), CFile::typeBinary );
	return (file.GetLength() / 1024);	
}

CString CAddMmsImageDlg::GetOnlyfileName(CString strPath)
{
	long nIndex = strPath.ReverseFind('\\');
	COleDateTime dtCur(COleDateTime::GetCurrentTime());

	if(nIndex >= 0) 
	{	
		CString strName = strPath.Right(strPath.GetLength() - nIndex - 1);
		return strName.Left(strName.GetLength() - 4);	
	}
	else
	{
		return strPath.Left(strPath.GetLength() - 4);
	}
}

void CAddMmsImageDlg::OnBnClickedFileOpenBtn1()
{
	OpenImageFile(0);
}

void CAddMmsImageDlg::OnBnClickedFileOpenBtn2()
{
	OpenImageFile(1);
} 

void CAddMmsImageDlg::OnBnClickedFileOpenBtn3()
{
	OpenImageFile(2);
}

void CAddMmsImageDlg::OnBnClickedFileDeleteBtn1()
{
	SetFileNameInfo(0, "첨부파일 No1 :", 0);
}

void CAddMmsImageDlg::OnBnClickedFileDeleteBtn2()
{
	SetFileNameInfo(1, "첨부파일 No2 :", 0);
}

void CAddMmsImageDlg::OnBnClickedFileDeleteBtn3()
{
	SetFileNameInfo(2, "첨부파일 No3 :", 0);
}

void CAddMmsImageDlg::OnBnClickedFilePathBtn1()
{
	m_pImageView->SetCurNumber(0);
}

void CAddMmsImageDlg::OnBnClickedFilePathBtn2()
{
	m_pImageView->SetCurNumber(1);
}

void CAddMmsImageDlg::OnBnClickedFilePathBtn3()
{
	m_pImageView->SetCurNumber(2);
}

long CAddMmsImageDlg::GetCurImageSize()
{
	long nSize = 0;
	for(int i=0; i<MAX_MMS_IMAGE_COUNT; i++)
	{
		if(!m_pImageView->m_strImage[i].IsEmpty())
		{
			nSize += m_nImageSize[i];
		}
	}

	return nSize;
}

void CAddMmsImageDlg::OnBnClickedOKBtn()
{
	m_nAddImageCount = 0;

	for(int i=0; i<MAX_MMS_IMAGE_COUNT; i++)
	{
		if(!m_pImageView->m_imgMms[i].IsNull())
		{
			m_strImage[m_nAddImageCount++] = m_pImageView->m_strImage[i];
		}
	} 

	OnOK();
}

void CAddMmsImageDlg::SetFileNameInfo(long nNumber, CString strPath, long nSize, BOOL bLoadImage)
{
	if(nSize == 0)
		m_pImageView->m_imgMms[nNumber].Destroy(); 
	else
	{		
		//CSize sizeTotal = CSize(m_pImageView->m_imgMms[nNumber].GetWidth(), m_pImageView->m_imgMms[nNumber].GetHeight());
		//m_pImageView->SetScrollSizes(MM_TEXT, sizeTotal);
	}

	if(nNumber == 0) GetDlgItem(IDC_FILE_PATH_BTN1)->SetWindowText(strPath);
	else if(nNumber == 1) GetDlgItem(IDC_FILE_PATH_BTN2)->SetWindowText(strPath);
	else if(nNumber == 2) GetDlgItem(IDC_FILE_PATH_BTN3)->SetWindowText(strPath);

	if(bLoadImage)
		m_pImageView->m_imgMms[nNumber].Load(strPath);

	m_strImage[nNumber] = nSize > 0 ? strPath : "";
	m_pImageView->m_strImage[nNumber] = nSize > 0 ? strPath : "";
	m_nImageSize[nNumber] = nSize;
	m_pImageView->SetCurNumber(nSize > 0 ? nNumber : -1);
}


BOOL CAddMmsImageDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{

	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}
