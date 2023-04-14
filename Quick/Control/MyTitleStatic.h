#pragma once


// CMyTitleStatic

class CMyTitleStatic : public CStatic
{
	DECLARE_DYNAMIC(CMyTitleStatic)

public:
	CMyTitleStatic();
	virtual ~CMyTitleStatic();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

	long m_nCNo;
	long m_nTodaycount;
	long m_nUseCount;
	long m_nCancelCount;
	long m_nMileageBalance;

	void SetInfo(long nCNo, long nTodayCount = 0, long nUseCount = 0, long nCancelCount = 0, long nMileageBalance = 0)
	{
		m_nCNo = nCNo;
		m_nTodaycount = nTodayCount;
		m_nUseCount = nUseCount;
		m_nCancelCount = nCancelCount;
		m_nMileageBalance = nMileageBalance; 

		Invalidate(TRUE);
	}

};


