// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXMagicImagePanel 래퍼 클래스

class CXMagicImagePanel : public COleDispatchDriver
{
public:
	CXMagicImagePanel(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXMagicImagePanel(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXMagicImagePanel(const CXMagicImagePanel& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXMagicImagePanel 메서드
public:
	void SetAutoDestroy(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2329, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	BOOL IsValid()
	{
		BOOL result;
		InvokeHelper(0x1f41, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void ClearImage_NoName()
	{
		InvokeHelper(0x1f42, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH GetImage(long Type)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b59, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type);
		return result;
	}

	// IXMagicImagePanel 속성
public:

};
