#pragma once


// CDummyView ���Դϴ�.

class CDummyView : public CView
{
	DECLARE_DYNCREATE(CDummyView)

protected:
	CDummyView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CDummyView();

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


