#pragma once


class CMmsImageView;
// CAddMmsImageDlg ��ȭ �����Դϴ�.

#include <afxdtctl.h>

class CAddMmsImageDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddMmsImageDlg)

public:
	CAddMmsImageDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAddMmsImageDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ADD_MMS_IMAGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	CStatic m_stcImage; 
	long m_nAddImageCount;

	CCreateContext m_context;
	CMmsImageView *m_pImageView;
	CString m_strImage[MAX_MMS_IMAGE_COUNT];
	long m_nImageSize[MAX_MMS_IMAGE_COUNT];

	virtual BOOL OnInitDialog();

	void OpenImageFile(long nNumber);
	void SetFileNameInfo(long nNumber, CString strPath, long nSzie, BOOL bLoadImage = FALSE);

	afx_msg void OnBnClickedFilePathBtn1();
	afx_msg void OnBnClickedFilePathBtn2();
	afx_msg void OnBnClickedFilePathBtn3();
	afx_msg void OnBnClickedFileOpenBtn1();
	afx_msg void OnBnClickedFileOpenBtn2();
	afx_msg void OnBnClickedFileOpenBtn3();
	afx_msg void OnBnClickedFileDeleteBtn1();
	afx_msg void OnBnClickedFileDeleteBtn2();
	afx_msg void OnBnClickedFileDeleteBtn3();
	afx_msg void OnBnClickedOKBtn();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	CStringArray m_strDeleteFileArry;
	CString GetOnlyfileName(CString strPath);
	long GetFileSize(CString strPath);
	long GetCurImageSize();

};
