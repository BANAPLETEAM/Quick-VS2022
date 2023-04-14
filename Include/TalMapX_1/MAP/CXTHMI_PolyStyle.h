// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXTHMI_PolyStyle 래퍼 클래스

class CXTHMI_PolyStyle : public COleDispatchDriver
{
public:
	CXTHMI_PolyStyle(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXTHMI_PolyStyle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXTHMI_PolyStyle(const CXTHMI_PolyStyle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXTHMI_PolyStyle 메서드
public:
	unsigned char GetVisible()
	{
		unsigned char result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	unsigned char GetAlpha()
	{
		unsigned char result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	unsigned char GetPen()
	{
		unsigned char result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	unsigned char GetPen1()
	{
		unsigned char result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	unsigned char GetBrush()
	{
		unsigned char result;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}

	// IXTHMI_PolyStyle 속성
public:

};
