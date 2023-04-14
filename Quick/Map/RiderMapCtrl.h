#pragma once


#include "LogiMapNew.h"

enum {	BTN_BAG_TYPE_0 = 1, 
		BTN_BAG_TYPE_1 = 2, 
		BTN_BAG_TYPE_2 = 4, 
		BTN_BAG_TYPE_3 = 8, 
		BTN_BAG_TYPE_ALL = 15};

enum {	BTN_CAR_TYPE_BIGBIKE = 1, 
		BTN_CAR_TYPE_DAMA = 2, 
		BTN_CAR_TYPE_LABO = 4, 
		BTN_CAR_TYPE_VAN = 8, 
		BTN_CAR_TYPE_TRUCK = 16, 
		BTN_CAR_TYPE_ALL = 31};

enum {	BTN_TON_TYPE_1_0 = 1, 
		BTN_TON_TYPE_1_4 = 2, 
		BTN_TON_TYPE_2_5 = 4, 
		BTN_TON_TYPE_3_5 = 8, 
		BTN_TON_TYPE_4_5 = 16, 
		BTN_TON_TYPE_5_0 = 32, 
		BTN_TON_TYPE_11_0= 64,
		BTN_TON_TYPE_ALL = 127};


#define DISPLAY_ORDER_COUNT 4

// CRiderMapCtrl
class CRiderMapCtrl : public CLogiMapNew
{
	DECLARE_DYNAMIC(CRiderMapCtrl)

public:
	CRiderMapCtrl();
	virtual ~CRiderMapCtrl();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()

public:
	afx_msg void OnCreateMap(long Value);
	virtual void OnUIMouseUp(LPDISPATCH Obj, long Flag, long X, long Y);
	virtual void OnChangeMapLevel();
	virtual void OnPOIMouseHover(LPDISPATCH POI);
	virtual void OnPOIMouseLeave(LPDISPATCH POI);


	CXUIStaticText m_uistcLeftArrow;
	CXUIStaticText m_uistcRightArrow;
	CXUIStaticText m_uistcCount;
	CXUIStaticText m_uistcOrderCount;
	CXUIStaticText m_uistcPlay;
	CXUIStaticText m_uistcStop;
	CXUIStaticText m_uistcSpeedUp;
	CXUIStaticText m_uistcSpeedDown;

	CXUIStaticText m_uistcOrder[DISPLAY_ORDER_COUNT];
	CXUIImage m_uiimageOrder[DISPLAY_ORDER_COUNT];

	CXUIImage m_imageOrderCount;

	CXUIImage m_uiimageBag[4];
	CXUIImage m_uiimageCar[5];
	CXUIImage m_uiimageTon[7];

	void CreateTraceNavi();
	CXUIStaticText CreateTraceNaviBtn(CRect rc, int nID, CString strText);
	void DeleteTraceNavi();
	void DeleteTraceNaviBtn(CXUIStaticText uistc);
	void SetBagImage();
	void SetCarImage();
	void SetTonImage();
	void BitToggle(long &nDst, long nValue);
	CString GetBagImage(long nValue, CString strImage);
	CString GetCarImage(long nValue, CString strImage);
	CString GetTonImage(long nValue, CString strImage);
	
	long m_nBagType;
	long m_nCarType;
	long m_nTonType;
	BOOL m_bHoverShowRiderHaveOrder;
	BOOL m_bHasCargoBranch;
	BOOL m_bCargoOnly;

};


