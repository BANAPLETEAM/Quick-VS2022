// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXControlState 래퍼 클래스

class CXControlState : public COleDispatchDriver
{
public:
	CXControlState(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXControlState(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXControlState(const CXControlState& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXControlState 메서드
public:
	long GetState(long StateType)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2329, DISPATCH_METHOD, VT_I4, (void*)&result, parms, StateType);
		return result;
	}
	void SetState(long StateType, long Code)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x232a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, StateType, Code);
	}
	BOOL ValidStateType(long StateType)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x232b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, StateType);
		return result;
	}
	BOOL IsState(long StateType, long Code)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x232c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, StateType, Code);
		return result;
	}
	long ToggleState(long StateType)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x232d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, StateType);
		return result;
	}
	void SetZoom(double Value)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x232e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	double GetZoom()
	{
		double result;
		InvokeHelper(0x232f, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}
	void SetZoomScale(double Value)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x2330, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	double GetZoomScale()
	{
		double result;
		InvokeHelper(0x2331, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}
	void SetDBLevel(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2332, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetDBLevel()
	{
		long result;
		InvokeHelper(0x2333, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetLevel(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2334, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetLevel()
	{
		long result;
		InvokeHelper(0x2335, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	BOOL SetLLCenter(long Lon, long Lat)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x2336, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Lon, Lat);
		return result;
	}
	LPDISPATCH GetLLCenter()
	{
		LPDISPATCH result;
		InvokeHelper(0x2337, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL SetSizeDP(long Width, long Height)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x2338, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Width, Height);
		return result;
	}
	LPDISPATCH GetSizeDP()
	{
		LPDISPATCH result;
		InvokeHelper(0x2339, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetDPRect()
	{
		LPDISPATCH result;
		InvokeHelper(0x233a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetDPCenter()
	{
		LPDISPATCH result;
		InvokeHelper(0x233b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL SetLonLatRate(double Rate)
	{
		BOOL result;
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x233c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Rate);
		return result;
	}
	double GetLonLatRate()
	{
		double result;
		InvokeHelper(0x233d, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}
	BOOL SetCenterRate(LPDISPATCH Rate)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x233e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Rate);
		return result;
	}
	LPDISPATCH GetCenterRate()
	{
		LPDISPATCH result;
		InvokeHelper(0x233f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetMapRect()
	{
		LPDISPATCH result;
		InvokeHelper(0x2340, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long GetAntiAliasing()
	{
		long result;
		InvokeHelper(0x2341, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetAntiAliasing(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2342, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetClipping()
	{
		long result;
		InvokeHelper(0x2343, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetClipping(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2344, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	LPDISPATCH DPToLL(long X, long Y)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x2345, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, X, Y);
		return result;
	}
	LPDISPATCH LLToDP(long Lon, long Lat, long Height)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x2346, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Lon, Lat, Height);
		return result;
	}
	LPDISPATCH GetPerspective()
	{
		LPDISPATCH result;
		InvokeHelper(0x2347, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void SetPerspective(LPDISPATCH Vector)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x2348, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Vector);
	}
	LPDISPATCH GetTranslate()
	{
		LPDISPATCH result;
		InvokeHelper(0x2349, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void SetTranslate(LPDISPATCH Vector)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x234a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Vector);
	}
	LPDISPATCH GetScale()
	{
		LPDISPATCH result;
		InvokeHelper(0x234b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void SetScale(LPDISPATCH Vector)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x234c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Vector);
	}
	LPDISPATCH GetRotate()
	{
		LPDISPATCH result;
		InvokeHelper(0x234d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void SetRotate(LPDISPATCH Vector)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x234e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Vector);
	}
	long SetMapRectLevel(LPDISPATCH MapRect, long Type)
	{
		long result;
		static BYTE parms[] = VTS_DISPATCH VTS_I4 ;
		InvokeHelper(0x234f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, MapRect, Type);
		return result;
	}
	long SetMapRectLevel2(long LLon, long RLon, long ULat, long LLat, long Type)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x2350, DISPATCH_METHOD, VT_I4, (void*)&result, parms, LLon, RLon, ULat, LLat, Type);
		return result;
	}
	void SetMinMaxLevel(long MinLevel, long MaxLevel)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x2351, DISPATCH_METHOD, VT_EMPTY, NULL, parms, MinLevel, MaxLevel);
	}
	LPDISPATCH GetMinMaxLevel()
	{
		LPDISPATCH result;
		InvokeHelper(0x2352, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void SetMapScale(double Value)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x2353, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	double GetMapScale()
	{
		double result;
		InvokeHelper(0x2354, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}

	// IXControlState 속성
public:

};
