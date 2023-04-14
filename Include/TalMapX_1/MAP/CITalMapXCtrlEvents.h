// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CITalMapXCtrlEvents 래퍼 클래스

class CITalMapXCtrlEvents : public COleDispatchDriver
{
public:
	CITalMapXCtrlEvents(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CITalMapXCtrlEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CITalMapXCtrlEvents(const CITalMapXCtrlEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// _ITalMapXCtrlEvents 메서드
public:
	void OnCreate(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	void OnMouseDown(long Flag, long X, long Y)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Flag, X, Y);
	}
	void OnMouseUp(long Flag, long X, long Y)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Flag, X, Y);
	}
	void OnMouseMove(long Flag, long X, long Y)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Flag, X, Y);
	}
	void OnKeyDown(unsigned long Code, unsigned long RepCnt, unsigned long Flag)
	{
		static BYTE parms[] = VTS_UI4 VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Code, RepCnt, Flag);
	}
	void OnStateChange(long Code, long Value1, long Value2)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Code, Value1, Value2);
	}
	void OnClickNotify(long Type, long X, long Y)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type, X, Y);
	}
	void OnAreaRect(long Type, LPDISPATCH Rect)
	{
		static BYTE parms[] = VTS_I4 VTS_DISPATCH ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type, Rect);
	}
	void OnDraw(long DrawType, long * hDC, LPDISPATCH CtrlState)
	{
		static BYTE parms[] = VTS_I4 VTS_PI4 VTS_DISPATCH ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DrawType, hDC, CtrlState);
	}
	void OnWindowContextMenu(long X, long Y)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms, X, Y);
	}
	void OnUI_MouseDown(LPDISPATCH Obj, long Flag, long X, long Y)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Obj, Flag, X, Y);
	}
	void OnUI_MouseUp(LPDISPATCH Obj, long Flag, long X, long Y)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Obj, Flag, X, Y);
	}
	void OnUI_MouseMove(LPDISPATCH Obj, long Flag, long X, long Y)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Obj, Flag, X, Y);
	}
	void OnUI_MousePress(LPDISPATCH Obj)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Obj);
	}
	void OnUI_Click(LPDISPATCH Obj, long Flag, long X, long Y)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Obj, Flag, X, Y);
	}
	void OnUI_DblClick(LPDISPATCH Obj, long Flag, long X, long Y)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Obj, Flag, X, Y);
	}
	void OnUI_Move(LPDISPATCH Obj, long Type)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_I4 ;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Obj, Type);
	}
	void OnUI_MouseLeave(LPDISPATCH Obj)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Obj);
	}
	void OnUI_MouseHover(LPDISPATCH Obj)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Obj);
	}
	void OnUI_CreateObject(LPDISPATCH Obj)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Obj);
	}
	void OnUI_DestroyObject(LPDISPATCH Obj)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Obj);
	}
	void OnPOI_MouseUp(LPDISPATCH POI, long nFlag, long X, long Y)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, NULL, parms, POI, nFlag, X, Y);
	}
	void OnPOI_MouseDown(LPDISPATCH POI, long nFlag, long X, long Y)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, POI, nFlag, X, Y);
	}
	void OnPOI_Click(LPDISPATCH POI, long nFlag, long X, long Y)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x2b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, POI, nFlag, X, Y);
	}
	void OnPOI_DblClick(LPDISPATCH POI, long nFlag, long X, long Y)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x2c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, POI, nFlag, X, Y);
	}
	void OnPOI_UIClick(LPDISPATCH POI, long nFlag, long X, long Y, LPDISPATCH Obj)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4 VTS_DISPATCH ;
		InvokeHelper(0x2d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, POI, nFlag, X, Y, Obj);
	}
	void OnPOI_UIDblClick(LPDISPATCH POI, long nFlag, long X, long Y, LPDISPATCH Obj)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4 VTS_DISPATCH ;
		InvokeHelper(0x2e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, POI, nFlag, X, Y, Obj);
	}
	void OnPOI_MouseLeave(LPDISPATCH POI)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x2f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, POI);
	}
	void OnPOI_MouseHover(LPDISPATCH POI)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x30, DISPATCH_METHOD, VT_EMPTY, NULL, parms, POI);
	}
	void OnLayerObject_Create(LPDISPATCH LayerObject)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x3d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerObject);
	}
	void OnLayerObject_Destroy(LPDISPATCH LayerObject)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x3e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerObject);
	}
	void OnLayerObject_Modified(LPDISPATCH LayerObject, long Code)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_I4 ;
		InvokeHelper(0x3f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerObject, Code);
	}
	void OnLayerObject_MouseMove(LPDISPATCH LayerObject, long nFlag, long X, long Y)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x40, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerObject, nFlag, X, Y);
	}
	void OnLayerObject_MouseHover(LPDISPATCH LayerObject)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x41, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerObject);
	}
	void OnLayerObject_MouseLeave(LPDISPATCH LayerObject)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x42, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerObject);
	}
	void OnLayerObject_Click(LPDISPATCH LayerObject, long nFlag, long X, long Y)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x43, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerObject, nFlag, X, Y);
	}
	void OnGPSNotify(LPDISPATCH GPSMan, long EventType, long Data)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 ;
		InvokeHelper(0x51, DISPATCH_METHOD, VT_EMPTY, NULL, parms, GPSMan, EventType, Data);
	}
	void OnScriptMessage(long Type, LPCTSTR Msg, long MsgLen)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_I4 ;
		InvokeHelper(0x5b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type, Msg, MsgLen);
	}
	void OnShapeItem_Click(LPDISPATCH ShapeItem, long X, long Y)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 ;
		InvokeHelper(0x65, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ShapeItem, X, Y);
	}
	void OnTimerEvent(long Code)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xc8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Code);
	}

	// _ITalMapXCtrlEvents 속성
public:

};
