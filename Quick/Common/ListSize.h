
#pragma once


class CListSize
{
public:
	CListSize() { m_rcOri = CRect(0, 0, 0, 0); }


	void Set(CXTPGridControl *pControl, CRect rcOri, int nNoSizeMax, int nSizeMax, 
						int nPerHeight, int nHeaderHeight) //PerHeight = 19, nHeaderHeight = 25, noheader = 3
	{
		m_pControl = pControl;
		m_rcOri = rcOri;
		m_rcNew = rcOri;
		m_nNoSizeMax = nNoSizeMax;
		m_nSizeMax = nSizeMax;
		m_nPerHeight = nPerHeight;
		m_nHeaderHeight = nHeaderHeight;
	}

	CXTPGridControl *m_pControl;
	CRect m_rcOri;
	CRect m_rcNew;
	CRect m_rcCur;
	int m_nNoSizeMax;
	int m_nSizeMax;
	int m_nHeaderHeight;
	int m_nPerHeight;

	int GetCount() { return m_pControl->GetRecords()->GetCount(); }
	int GetDesire() { return max(1, min(GetCount(), m_nSizeMax)); }
	BOOL NeedMove() { return GetCount() > m_nNoSizeMax;}
	void Move()  {  if(m_rcNew != m_rcCur) m_pControl->MoveWindow(m_rcNew); }
	void MoveOri()  { if(m_rcOri != m_rcCur) m_pControl->MoveWindow(m_rcOri); }
	void SetCur(CRect rc) { m_rcCur = rc; m_rcNew = m_rcOri;}
	void SetTop(int nTop) { m_rcNew.top = nTop; m_rcNew.bottom = nTop + m_rcOri.Height(); }
	void SetHeight(int nCount) { m_rcNew.bottom = m_rcNew.top + m_nHeaderHeight + nCount * m_nPerHeight; }
	void SetNextTop(CListSize &Next)
	{
		int nGap = Next.m_rcOri.top - m_rcOri.bottom;
		Next.SetTop(m_rcNew.bottom + nGap);
	}

	void MoveTo(CListSize &Next)
	{
		int nD0 = GetDesire();
		int nD1 = Next.m_nNoSizeMax - (m_nNoSizeMax - nD0);

		SetHeight(nD0);
		SetNextTop(Next);

		Next.SetHeight(nD1);
	}

	void MoveTo(CListSize &Next, CListSize &Next2)
	{
		int nD0 = GetDesire();
		int nD1 = Next.GetDesire();
		int nD2 = Next2.GetDesire();
		int nM1 = 0, nM2 = 0;

		if(nD0 > m_nNoSizeMax)
			nM1 = m_nNoSizeMax - nD0;

		if(nD1 > Next.m_nNoSizeMax && nD2 > Next2.m_nNoSizeMax || 
			nD1 <= Next.m_nNoSizeMax && nD2 <= Next2.m_nNoSizeMax)
		{
			nD1 = Next.m_nNoSizeMax;
			nD2 = Next2.m_nNoSizeMax;
		}
		else if(nD1 > Next.m_nNoSizeMax)
		{
			nD1 = min(nD1, (Next.m_nNoSizeMax + Next2.m_nNoSizeMax - nD2));
		}
		else if(nD2 > Next2.m_nNoSizeMax)
		{
			nD2 = min(nD2, (Next2.m_nNoSizeMax + Next.m_nNoSizeMax - nD1));
			nD1 = Next.m_nNoSizeMax + Next2.m_nNoSizeMax - nD2;
		}

		if(nM1 > 0)
		{
			if(nD1 < Next.m_nNoSizeMax)
				nD1 -= nM1;
			else 
				nD2 -= nM1;
		}

		SetHeight(nD0);
		SetNextTop(Next);

		Next.SetHeight(nD1);
		Next.SetNextTop(Next2);

		Next2.SetHeight(nD2);
	}
};

