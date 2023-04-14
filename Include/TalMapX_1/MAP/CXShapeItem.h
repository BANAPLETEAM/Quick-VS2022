// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXShapeItem 래퍼 클래스

class CXShapeItem : public COleDispatchDriver
{
public:
	CXShapeItem(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXShapeItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXShapeItem(const CXShapeItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXShapeItem 메서드
public:
	CString GetID()
	{
		CString result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetCode()
	{
		CString result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetCode(LPCTSTR Code)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Code);
	}
	CString GetValue()
	{
		CString result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetValue(LPCTSTR Value)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetSHPType()
	{
		long result;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetPOIStyle(LPDISPATCH POIStyle)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, POIStyle);
	}
	void SetCaption(LPCTSTR Caption)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Caption);
	}
	CString GetCaption()
	{
		CString result;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetMapPos()
	{
		LPDISPATCH result;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetMapRect()
	{
		LPDISPATCH result;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void SetHint(LPCTSTR Caption, LPCTSTR Contents)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Caption, Contents);
	}

	// IXShapeItem 속성
public:

};
