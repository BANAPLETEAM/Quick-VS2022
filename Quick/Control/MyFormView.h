#pragma once


typedef enum {
	sizingRight, 
	sizingBottom,
	sizingRightBottom
} SIZING_TYPE;

#define RIGHT_HOLD	9999
#define BOTTOM_HOLD	10000


typedef struct {
	int x;
	int y;
} MARGIN_DATA;

typedef map<long, SIZING_TYPE> SIZING_MAP;
typedef map<long, MARGIN_DATA> MARGIN_MAP;


// CMyFormView 폼 뷰입니다.

class CMyFormView : public CFormView
{
	DECLARE_DYNCREATE(CMyFormView)

public:
	CMyFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	CMyFormView(UINT nID);           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMyFormView();

public:
	enum { IDD = 0 };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
public:
	virtual void RefreshList();							// view들을 포함하고 있는 메인Tabview에서 서브view의 갱신을 위해
	virtual void RefreshList2();
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bOptionView;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);

	BOOL m_bChangeCursor;
	BOOL m_bMoveControl;

	HCURSOR m_hcArrow;
	HCURSOR m_hcVertical;
	HCURSOR m_hcMiddle;

	BOOL m_bResizeVer;
	BOOL m_bResizeHori;
	BOOL m_bCopyView = FALSE;

	UINT m_nLeftControl;
	UINT m_nRightControl;
	CXTPTaskPanel *m_pwndTaskPanel;
	CXTPDockingPane *m_pwndPaneNetwork;
	CArray<MONITORINFOEX, MONITORINFOEX> m_aryMonitors;

	static CString m_strLastFormView;

	void MoveList(CPoint pt);
	void ChangeCursor(CPoint pt);
	void SetResizeVer(long nLeft, long nRight);
	void SetResizeHori(long nLeft, long nRight);
	void SetResize(long nID, SIZING_TYPE st, int xMargin = 0, int yMargin = 0);
	void MoveClient();
	void FillForm(CDC *pDC);
	virtual void FirstRefresh();
	void FirstRefresh2();
	BOOL IsFirstRefresh(){return !m_bFirstRefreshList;};
	void SetFirstRefresh(BOOL bFirst) {m_bFirstRefreshList = bFirst;};
	virtual BOOL Save(long nCompany, BOOL bAll = FALSE); //MainOptinoDlg에서씀
	void SetOptiobView(BOOL bOptionView) { m_bOptionView = bOptionView; }

protected:	
	SIZING_MAP m_mapSizing;
	MARGIN_MAP m_mapMargin;
	BOOL m_bFirstRefreshList;
	BOOL m_bFirstRefreshList2;
	BOOL m_bRefreshTimerON;
	BOOL m_bInitialUpdateCalled;
	MAP_WND_BRUSH m_mapWnd;

public:
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCopyFormDlg();
	afx_msg void OnCopyFormDlgNewMonitor();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


