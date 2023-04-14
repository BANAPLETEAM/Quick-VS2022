// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXObjectList 래퍼 클래스

class CXObjectList : public COleDispatchDriver
{
public:
	CXObjectList(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXObjectList(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXObjectList(const CXObjectList& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXObjectList 메서드
public:
	void Destroy()
	{
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long GetCount()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	BOOL GoFirst()
	{
		BOOL result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL Next()
	{
		BOOL result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetPOIItem()
	{
		LPDISPATCH result;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}

	// IXObjectList 속성
public:

};
