// QuickView.h : iCQuickView Ŭ������ �������̽�
//


#pragma once
#include "afxwin.h"


class CQuickView : public CFormView
{
protected: // serialization������ ��������ϴ�.
	DECLARE_DYNCREATE(CQuickView)

public:
	CQuickView();
	enum{ IDD = IDD_QUICK_FORM };

// Ư��
public:
	CQuickDoc* GetDocument() const;

// �۾�
public:

// ������
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ����
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// ����
public:
	virtual ~CQuickView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �޽��� �� �Լ��� �����߽��ϴ�.
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnLogin();
};

#ifndef _DEBUG  // QuickView.cpp�� ����� ����
inline CQuickDoc* CQuickView::GetDocument() const
   { return reinterpret_cast<CQuickDoc*>(m_pDocument); }
#endif

