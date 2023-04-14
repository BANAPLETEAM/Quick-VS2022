// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXSKMan 래퍼 클래스

class CXSKMan : public COleDispatchDriver
{
public:
	CXSKMan(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXSKMan(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXSKMan(const CXSKMan& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXSKMan 메서드
public:
	void SetCongestionStyle(long Type, LPDISPATCH Style)
	{
		static BYTE parms[] = VTS_I4 VTS_DISPATCH ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type, Style);
	}
	LPDISPATCH GetCongestionStyle(long Type)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type);
		return result;
	}
	BOOL PathStringInput(long lPathID, LPCTSTR bstrLinkID, LPCTSTR bstrLinkSpeed)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lPathID, bstrLinkID, bstrLinkSpeed);
		return result;
	}
	void Route_Clear()
	{
		InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH Route_Find(LPCTSTR Name)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Name);
		return result;
	}
	LPDISPATCH Route_New(LPCTSTR Name)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Name);
		return result;
	}
	void Route_Delete(LPCTSTR Name)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Name);
	}
	BOOL POI_SetDataType(long DataType)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x33, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, DataType);
		return result;
	}
	long POI_GetDataType()
	{
		long result;
		InvokeHelper(0x34, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void POI_Clear()
	{
		InvokeHelper(0x35, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL POI_Search(LPCTSTR URLPath, LPCTSTR SearchStr, long CurPage)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x36, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, URLPath, SearchStr, CurPage);
		return result;
	}
	long POI_GetCount()
	{
		long result;
		InvokeHelper(0x38, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long POI_IsNextList()
	{
		long result;
		InvokeHelper(0x39, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH POI_CenterPos(long Idx)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Idx);
		return result;
	}
	LPDISPATCH POI_EntrancePos(long Idx, long EIdx)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x3b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Idx, EIdx);
		return result;
	}
	CString POI_ID(long Idx)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Idx);
		return result;
	}
	CString POI_TelNumber(long Idx)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Idx);
		return result;
	}
	CString POI_IsParking(long Idx)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Idx);
		return result;
	}
	CString POI_AddrMain(long Idx)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Idx);
		return result;
	}
	CString POI_AddrSub(long Idx)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x40, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Idx);
		return result;
	}
	CString POI_Name(long Idx)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x41, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Idx);
		return result;
	}
	CString POI_DetailInfo(long Idx)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x42, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Idx);
		return result;
	}
	CString POI_Address(long Idx)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x43, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Idx);
		return result;
	}
	void POI_SetFilter_Admin(LPCTSTR AdminString, BOOL AutoClear)
	{
		static BYTE parms[] = VTS_BSTR VTS_BOOL ;
		InvokeHelper(0x50, DISPATCH_METHOD, VT_EMPTY, NULL, parms, AdminString, AutoClear);
	}
	void POI_ClearFilter_Admin()
	{
		InvokeHelper(0x51, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void POI_SetFilter_NearBy(long Lon, long Lat, long Radius, BOOL AutoClear)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0x52, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Lon, Lat, Radius, AutoClear);
	}
	void POI_ClearFilter_NearBy()
	{
		InvokeHelper(0x53, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

	// IXSKMan 속성
public:

};
