// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXPopupMenuItem 래퍼 클래스

class CXPopupMenuItem : public COleDispatchDriver
{
public:
	CXPopupMenuItem(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXPopupMenuItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXPopupMenuItem(const CXPopupMenuItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXPopupMenuItem 메서드
public:
	CString GetCaption()
	{
		CString result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetHint()
	{
		CString result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetContents()
	{
		CString result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long GetID()
	{
		long result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetData()
	{
		long result;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	BOOL GetChecked()
	{
		BOOL result;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void SetChecked(BOOL Value)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	BOOL GetEnabled()
	{
		BOOL result;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void SetEnabled(BOOL Value)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}

	// IXPopupMenuItem 속성
public:

};
