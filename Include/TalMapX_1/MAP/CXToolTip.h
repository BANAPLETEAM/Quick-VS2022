// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXToolTip 래퍼 클래스

class CXToolTip : public COleDispatchDriver
{
public:
	CXToolTip(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXToolTip(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXToolTip(const CXToolTip& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXToolTip 메서드
public:
	void SetFont(long Type, LPCTSTR Name, long Size, BOOL Bold, BOOL Italic, BOOL Underline, BOOL StrikeOut)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_I4 VTS_BOOL VTS_BOOL VTS_BOOL VTS_BOOL ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type, Name, Size, Bold, Italic, Underline, StrikeOut);
	}
	void SetFontColor(long Type, unsigned long Value)
	{
		static BYTE parms[] = VTS_I4 VTS_UI4 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type, Value);
	}
	void SetBrush(long Type, unsigned long Value)
	{
		static BYTE parms[] = VTS_I4 VTS_UI4 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type, Value);
	}

	// IXToolTip 속성
public:

};
