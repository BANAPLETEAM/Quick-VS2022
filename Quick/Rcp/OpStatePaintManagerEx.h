#pragma once
#include "RcpPageCTIForm.h"

enum { NONE_EVENT = 0, MAKE_CALL, TRANSFER_CALL, PICKUP_CALL };

class COPStateRecordItemEx : public CXTPGridRecordItemText
{
public:
	COPStateRecordItemEx(CString strDummy):CXTPGridRecordItemText(strDummy)
	{
		ptCall = CPoint(0, 0);
		ptState = CPoint(0, 0);
		SetTooltip(strDummy);
	}

	int OnImageClickedCall(CPoint pt)
	{
		if(ptCall.x == 0 && ptCall.y == 0)
			return NONE_EVENT;
		else if(pt.y < ptCall.y)
			return NONE_EVENT;
		else if((ptCall.x <= pt.x &&  ptCall.x + 22 >= pt.x) && pOPState->nState == PH_HANG_UP
			&& nMyState == PH_HANG_UP)
			return MAKE_CALL;
		else if((ptCall.x + 25 <= pt.x && ptCall.x + 46 >= pt.x)
			&& (pOPState->nState == PH_RING || pOPState->nState == PH_ANSWER/* || pOPState->nState == PH_OUT_BOUND_CALL*/)
			&& nMyState == PH_HANG_UP)
			return PICKUP_CALL;
		else if((ptCall.x + 49 <= pt.x && ptCall.x + 70 >= pt.x) && pOPState->nState == PH_HANG_UP
			&& nMyState == PH_ANSWER)
			return TRANSFER_CALL;
		else
			return NONE_EVENT;
	}

	CString OnImageTooltipText(CPoint pt)
	{
		if(ptCall.x == 0 && ptCall.y == 0)
			return "";
		else if(pt.y >= ptCall.y)
		{
			if((ptCall.x <= pt.x && ptCall.x + 22 >= pt.x) && pOPState->nState == PH_HANG_UP
				&& nMyState == PH_HANG_UP)
				return "내선연결";
			else if((ptCall.x + 25 <= pt.x && ptCall.x + 47 >= pt.x)
				&& (pOPState->nState == PH_RING || pOPState->nState == PH_ANSWER/* || pOPState->nState == PH_OUT_BOUND_CALL*/)
				&& nMyState == PH_HANG_UP)
				return "당겨받기";
			else if((ptCall.x + 50 <= pt.x && ptCall.x + 73 >= pt.x) && pOPState->nState == PH_HANG_UP
				&& nMyState == PH_ANSWER)
				return "넘겨주기";
			else
				return GetTooltip();
			/*if(ptCall.x <= pt.x && ptCall.x + 22 >= pt.x)
				return "내선연결";
			else if(ptCall.x + 25 <= pt.x && ptCall.x + 46 >= pt.x)
				return "당겨받기";
			else if(ptCall.x + 49 <= pt.x && ptCall.x + 70 >= pt.x)
				return "넘겨주기";
			else
				return "";*/
		}
		else
			return GetTooltip();
	}

public:
	OP_STATE_INFO *pOPState;
	int nMyState;

	CPoint ptCall;
	CPoint ptState;
};


class COPStatePaintManagerEx : public CXTPGridThemeResource
{
	friend class CXTPGridControl;

	
public:
	COPStatePaintManagerEx();
	virtual ~COPStatePaintManagerEx();


public:
	virtual void DrawItemCaption(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pMetrics);
	virtual int GetRowHeight(CDC* pDC, CXTPGridRow* pRow);

	void DrawRectLine(CDC* pDC, CRect rcRect);
	BOOL DrawOPStateImage(Graphics* pGraphics, CRect rcTop, int nState);

	IStream* GDIStream(UINT nResourceID);

	int m_nMyState;

public:
	BOOL m_bShowLastPhoneNumber;
	OP_STATE_MAP m_mapOPState;

	IStream* m_pMakeCallStream;
	IStream* m_pPickUpCallStream;
	IStream* m_pTransferCallStream;

	IStream* m_pOPNoneStream;
	IStream* m_pOPRecvStream;
	IStream* m_pOPPauseStream;
	IStream* m_pOPWorkStream;
	IStream* m_pOPLogOutStream;
	IStream* m_pOPRecordStream;
	IStream* m_pOPMuteStream;
	IStream* m_pOPParkStream;
};
