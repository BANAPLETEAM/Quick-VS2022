#pragma once

// CNotHasPowerForm �� ���Դϴ�.

class CNotHasPowerForm : public CMyFormView
{
	DECLARE_DYNCREATE(CNotHasPowerForm)

protected:
	CNotHasPowerForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CNotHasPowerForm();

public:
	enum { IDD = IDD_NOT_HAS_POWER_FORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};


