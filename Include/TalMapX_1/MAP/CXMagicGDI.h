// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXMagicGDI 래퍼 클래스

class CXMagicGDI : public COleDispatchDriver
{
public:
	CXMagicGDI(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXMagicGDI(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXMagicGDI(const CXMagicGDI& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXMagicGDI 메서드
public:
	void SetAutoDestroy(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2329, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}

	// IXMagicGDI 속성
public:

};
