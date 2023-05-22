#pragma once


class CLogiFunc
{
public:
	CLogiFunc();
	virtual ~CLogiFunc();

	MAP_PHONE m_mapRiderPhone;
	MAP_VEC_PHONE m_mapNosmsPhone;
	MAP_EMOTICON m_mapEmoticon;

	DWORD m_dwLastInput;
	CArray<MONITORINFOEX, MONITORINFOEX> m_aryMonitors;
	
	CString	GetMyNumberFormat(CString strNumber);
	CString	GetMyNumberFormat(long nNumber);
	CString	GetNoneDashNumber(CString strPhoneNumber);
	BOOL IsStringDigit(CString &strText);
	BOOL IsPhoneNumber(CString &strText);
	CString GetModuleFullPath();
	void FillBackground(CDC *pDC, CWnd *pWnd, 
		COLORREF clrTop = COLOR_DEFAULT_TOP_WND, 
		COLORREF clrBottom = COLOR_DEFAULT_DOWN_WND);
	COLORREF GetRiderColor(int nColorType);
	CString GetRiderColorString(int nColorType);
	CString GetTwoToneMarkup(CString strMsg1, CString strMsg2, 
		BOOL bHasHead = FALSE, BOOL bHasTail = FALSE,
		CString strColor1 = "Black", CString strColor2 = "Green",
		BOOL bBold1 = FALSE, BOOL bBold2 = TRUE);
	void GetAutoGradientColor(COLORREF crSrc, COLORREF &crDst1, COLORREF &crDst2, long nScale = 0);
	void FillGradient(CDC *pDC, COLORREF crBack, CRect rcClient, long nScale = 20);
	BOOL OnMyCtlColor(CDC* pDC, CWnd* pWnd, UINT &nCtlColor, HBRUSH &hRetBrush);
	CString GetMyFileVersion();
	BOOL DllRegOcx(CString strPath);
	BOOL IsAllocOrder(int nState, BOOL bIncludeFinishOrder = TRUE);
	void RepositionLogConsole();
	void GetMonitorArray();
	CString GetZeroPadding(int nNumber, int nLen = 6);
	CString GetElapsedTimeString(COleDateTimeSpan span, BOOL bRemoveSec = 0);
	BOOL GetHandleScreenSize(CWnd *pWnd, CRect &rcScreen);
	void HideBehindControl(CWnd *pParent, CWnd *pWnd, BOOL bHide, CPtrArray *ppaExceptWnd = NULL);
	long GetControlDigit(CEdit *pEdit);

	void DrawRoundRect(CDC *pDC, CWnd *pMain, CWnd *pWnd1, CWnd *pWnd2 = NULL, long nLeftMargin = 0, long nTopMargin = 0, long nRightMargin = 0, long nBottomMargin = 0, COLORREF rgb = RGB(245, 245, 245), BOOL bRound = TRUE);
	void DrawRoundRect(CDC *pDC, CWnd *pMain, CRect rc, long nLeftMargin = 0, long nTopMargin = 0, long nRightMargin = 0, long nBottomMargin = 0, COLORREF rgb = RGB(245, 245, 245), BOOL bRound = TRUE);
	void MakeLineVertical(CDC *pDC, CWnd *pMain, CWnd *pLeftWnd, CWnd *RightWnd, long nTopMargin = 0, long nBottomMargin = 0, long nSize = 1, COLORREF rgb = RGB(0xbb, 0xbb, 0xbb));

	void LoadRiderPhone();
	void LoadNoSmsPhone(long nCompany);
	MAP_PHONE* GetRiderPhoneMap() {return &m_mapRiderPhone;};
	MAP_PHONE* GetNosmsPhoneMap(long nCompany) 
	{ 
		MAP_VEC_PHONE::iterator it = m_mapNosmsPhone.find(nCompany);
		return &it->second;
	};


	MAP_EMOTICON *GetEmoticonMap() {return &m_mapEmoticon;};
	void FillEmotioconMap();

protected:
	BOOL m_bGroup;

};
