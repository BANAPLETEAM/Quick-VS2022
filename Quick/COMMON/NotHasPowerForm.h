#pragma once

// CNotHasPowerForm 폼 뷰입니다.

class CNotHasPowerForm : public CMyFormView
{
	DECLARE_DYNCREATE(CNotHasPowerForm)

protected:
	CNotHasPowerForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CNotHasPowerForm();

public:
	enum { IDD = IDD_NOT_HAS_POWER_FORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};


