// QuickDoc.h : CQuickDoc 클래스의 인터페이스
//
#include "afxcoll.h"
#include "afxtempl.h"


#pragma once

class CQuickDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CQuickDoc();
	DECLARE_DYNCREATE(CQuickDoc)

// 특성
public:

// 작업
public:

// 재정의
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 구현
public:
	virtual ~CQuickDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 메시지 맵 함수를 생성했습니다.
protected:
	DECLARE_MESSAGE_MAP()
};


