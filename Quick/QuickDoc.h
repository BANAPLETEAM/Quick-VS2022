// QuickDoc.h : CQuickDoc Ŭ������ �������̽�
//
#include "afxcoll.h"
#include "afxtempl.h"


#pragma once

class CQuickDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CQuickDoc();
	DECLARE_DYNCREATE(CQuickDoc)

// Ư��
public:

// �۾�
public:

// ������
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ����
public:
	virtual ~CQuickDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �޽��� �� �Լ��� �����߽��ϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};


