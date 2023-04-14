// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXMagicImage 래퍼 클래스

class CXMagicImage : public COleDispatchDriver
{
public:
	CXMagicImage(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXMagicImage(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXMagicImage(const CXMagicImage& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXMagicImage 메서드
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

	// IXMagicImage 속성
public:

};
