// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXLayerCircle 래퍼 클래스

class CXLayerCircle : public COleDispatchDriver
{
public:
	CXLayerCircle(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXLayerCircle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXLayerCircle(const CXLayerCircle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXLayerCircle 메서드
public:
	void SetVisible(unsigned char newVal)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x2329, DISPATCH_METHOD, VT_EMPTY, NULL, parms, newVal);
	}
	unsigned char GetVisible()
	{
		unsigned char result;
		InvokeHelper(0x232a, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetVisibleLevel(unsigned char Level, unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 VTS_UI1 ;
		InvokeHelper(0x232b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Level, Value);
	}
	unsigned char GetVisibleLevel(unsigned char Level)
	{
		unsigned char result;
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x232c, DISPATCH_METHOD, VT_UI1, (void*)&result, parms, Level);
		return result;
	}
	void SetShowCaption(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x232d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetShowCaption()
	{
		long result;
		InvokeHelper(0x232e, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetShowImage(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x232f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetShowImage()
	{
		long result;
		InvokeHelper(0x2330, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetShowHint(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x2331, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetShowHint()
	{
		long result;
		InvokeHelper(0x2332, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetSelected(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x2333, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetSelected()
	{
		long result;
		InvokeHelper(0x2334, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetCanClick(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x2335, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetCanClick()
	{
		long result;
		InvokeHelper(0x2336, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetCanSelect(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x2337, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetCanSelect()
	{
		long result;
		InvokeHelper(0x2338, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetCanFocus(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x2339, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetCanFocus()
	{
		long result;
		InvokeHelper(0x233a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetCursor(unsigned char Value)
	{
		long result;
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x233b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetCursor()
	{
		long result;
		InvokeHelper(0x233c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetObjectID()
	{
		long result;
		InvokeHelper(0x1f41, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long IsObjectID(long ID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1f42, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID);
		return result;
	}
	void Register_TimerEvent(long Interval, long Continue_Event, long ID)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x1f43, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Interval, Continue_Event, ID);
	}
	void Unregister_TimerEvent(long ID)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1f44, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ID);
	}
	long SetValue(long Type, long Code, LPDISPATCH Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_DISPATCH ;
		InvokeHelper(0x1f45, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Type, Code, Value);
		return result;
	}
	long GetValue(long Type, long Code, LPDISPATCH Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_DISPATCH ;
		InvokeHelper(0x1f46, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Type, Code, Value);
		return result;
	}
	BOOL IsModified()
	{
		BOOL result;
		InvokeHelper(0x2135, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL IsUpdating()
	{
		BOOL result;
		InvokeHelper(0x2136, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void BeginUpdate()
	{
		InvokeHelper(0x2137, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void EndUpdate()
	{
		InvokeHelper(0x2138, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetModified(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2139, DISPATCH_METHOD, VT_EMPTY, NULL, parms, newValue);
	}
	long GetModified()
	{
		long result;
		InvokeHelper(0x213a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetEventMode(long Type)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x213b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Type);
		return result;
	}
	void SetEventMode(long Mode)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x213c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Mode);
	}
	void AddEventMode(long Type)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x213d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type);
	}
	void DeleteEventMode(long Type)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x213e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type);
	}
	void SetData(long * Value)
	{
		static BYTE parms[] = VTS_PI4 ;
		InvokeHelper(0x213f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetData()
	{
		long result;
		InvokeHelper(0x2140, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetTag(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2141, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetTag()
	{
		long result;
		InvokeHelper(0x2142, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetString(LPCTSTR Str)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2143, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Str);
	}
	CString GetString()
	{
		CString result;
		InvokeHelper(0x2144, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long GetID()
	{
		long result;
		InvokeHelper(0x1b59, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetStyle(LPDISPATCH Style)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x1b5a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style);
	}
	LPDISPATCH GetStyle()
	{
		LPDISPATCH result;
		InvokeHelper(0x1b5b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void NeedUpdate()
	{
		InvokeHelper(0x1b5c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetHint(LPCTSTR Hint)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1b5d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Hint);
	}
	CString GetHint()
	{
		CString result;
		InvokeHelper(0x1b5e, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetHintContents(LPCTSTR HintContents)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1b5f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, HintContents);
	}
	CString GetHintContents()
	{
		CString result;
		InvokeHelper(0x1b60, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void DestroyLayerObject()
	{
		InvokeHelper(0x1771, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long HitTest(long X, long Y)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1772, DISPATCH_METHOD, VT_I4, (void*)&result, parms, X, Y);
		return result;
	}
	void ShiftTo(LPDISPATCH Offset)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x1773, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Offset);
	}
	long PtInObject(long Lon, long Lat)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1774, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Lon, Lat);
		return result;
	}
	void FreeObject()
	{
		InvokeHelper(0x1775, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetStateModeNew()
	{
		InvokeHelper(0x1776, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetIndex(long Index)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1777, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
	}
	long GetIndex()
	{
		long result;
		InvokeHelper(0x1778, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetLayer()
	{
		LPDISPATCH result;
		InvokeHelper(0x1779, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long GetLayerID()
	{
		long result;
		InvokeHelper(0x177a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long AddPoint(long Lon, long Lat)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1389, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Lon, Lat);
		return result;
	}
	long AddPointList(LPDISPATCH PosList)
	{
		long result;
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x138a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, PosList);
		return result;
	}
	long AddMapPointList(LPDISPATCH MapPosList)
	{
		long result;
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x138b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, MapPosList);
		return result;
	}
	long DeletePoint(long Index)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x138c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Index);
		return result;
	}
	long DeletePointDP(long X, long Y)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x138d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, X, Y);
		return result;
	}
	long SetClosed(long Closed)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x138e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Closed);
		return result;
	}
	long GetClosed()
	{
		long result;
		InvokeHelper(0x138f, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long InsertPoint(long Index, long Lon, long Lat)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x1390, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Index, Lon, Lat);
		return result;
	}
	void SetPoint(long Index, long Lon, long Lat)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x1391, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, Lon, Lat);
	}
	BOOL SeparateLine(long X, long Y)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1392, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, X, Y);
		return result;
	}
	LPDISPATCH GetPoint(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1393, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}
	long GetPointCount()
	{
		long result;
		InvokeHelper(0x1394, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long LayerCustomListHitTest(long X, long Y)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1395, DISPATCH_METHOD, VT_I4, (void*)&result, parms, X, Y);
		return result;
	}
	long LayerCustomListPtInObject(long Lon, long Lat)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1396, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Lon, Lat);
		return result;
	}
	long SetUseClipping(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1397, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetUseClipping()
	{
		long result;
		InvokeHelper(0x1398, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	double GetIndexDistance(long StartIdx, long EndIdx)
	{
		double result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1399, DISPATCH_METHOD, VT_R8, (void*)&result, parms, StartIdx, EndIdx);
		return result;
	}
	double GetDistance()
	{
		double result;
		InvokeHelper(0x139a, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}
	double GetArea()
	{
		double result;
		InvokeHelper(0x139b, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}
	BOOL MakePolygon(long Distance)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x139c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Distance);
		return result;
	}
	LPDISPATCH GetMapRect()
	{
		LPDISPATCH result;
		InvokeHelper(0x139d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void SetStartFont(LPDISPATCH Font)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x139e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Font);
	}
	LPDISPATCH GetStartFont()
	{
		LPDISPATCH result;
		InvokeHelper(0x139f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void SetEndFont(LPDISPATCH Font)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x13a0, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Font);
	}
	LPDISPATCH GetEndFont()
	{
		LPDISPATCH result;
		InvokeHelper(0x13a1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void SetStartFontScale(float Scale)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x13a2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Scale);
	}
	float GetStartFontScale()
	{
		float result;
		InvokeHelper(0x13a3, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
		return result;
	}
	void SetEndFontScale(float Scale)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x13a4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Scale);
	}
	float GetEndFontScale()
	{
		float result;
		InvokeHelper(0x13a5, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
		return result;
	}
	BOOL IntersectPolygon(LPDISPATCH Plgn1, LPDISPATCH Plgn2)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH ;
		InvokeHelper(0x13a6, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Plgn1, Plgn2);
		return result;
	}
	BOOL UnionPolygon(LPDISPATCH Plgn1, LPDISPATCH Plgn2)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH ;
		InvokeHelper(0x13a7, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Plgn1, Plgn2);
		return result;
	}
	long IntersectRect(LPDISPATCH MapRect)
	{
		long result;
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x13a8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, MapRect);
		return result;
	}
	long IntersectRadius(LPDISPATCH CenterPos, long Radius)
	{
		long result;
		static BYTE parms[] = VTS_DISPATCH VTS_I4 ;
		InvokeHelper(0x13a9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, CenterPos, Radius);
		return result;
	}
	long SetStrokeCap(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x13aa, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetStrokeCap()
	{
		long result;
		InvokeHelper(0x13ab, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetCenter(LPDISPATCH Center)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Center);
	}
	LPDISPATCH GetCenter()
	{
		LPDISPATCH result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void SetRadius(long Radius)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Radius);
	}
	long GetRadius()
	{
		long result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetShowDistance(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetShowDistance()
	{
		long result;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetShowArea(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetShowArea()
	{
		long result;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}

	// IXLayerCircle 속성
public:

};
