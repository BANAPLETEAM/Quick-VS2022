// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXTHMI_Polygon 래퍼 클래스

class CXTHMI_Polygon : public COleDispatchDriver
{
public:
	CXTHMI_Polygon(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXTHMI_Polygon(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXTHMI_Polygon(const CXTHMI_Polygon& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXTHMI_Polygon 메서드
public:
	LPDISPATCH GetInfo()
	{
		LPDISPATCH result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetStyle(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}

	// IXTHMI_Polygon 속성
public:

};
