// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

//#import "C:\\Users\\TAEIN\\Documents\\eKsys\\Library\\DLL\\SmartSR\\SmartSRX_1.0.0.88.dll" no_namespace
// CXRouteInfo4 래퍼 클래스

class CXRouteInfo4 : public COleDispatchDriver
{
public:
	CXRouteInfo4(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXRouteInfo4(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXRouteInfo4(const CXRouteInfo4& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXRouteInfo4 메서드
public:
	long GetTotalDistance()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetTotalTime()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetTotalToll()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetCurrentNodeIndex()
	{
		long result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetCurrentNodeIndex(long Index)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
	}
	long GetNodeCount()
	{
		long result;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetNodeLon()
	{
		long result;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetNodeLat()
	{
		long result;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetNodeID()
	{
		long result;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetNodeAttr()
	{
		long result;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetNodeMapLevel()
	{
		long result;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetNodeLinkIdx()
	{
		long result;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetNodeIsUTurn()
	{
		long result;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetNodeIsSignal()
	{
		long result;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetNodeRemainDist()
	{
		long result;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetNodeRemainTime()
	{
		long result;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString GetNodeName()
	{
		CString result;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetNodeShortName()
	{
		CString result;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetNodeLongName()
	{
		CString result;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long GetCurrentLinkIndex()
	{
		long result;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetCurrentLinkIndex(long Index)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
	}
	long GetLinkCount()
	{
		long result;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetLinkID()
	{
		long result;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetLinkNumPoint()
	{
		long result;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetLinkPointLon(long Index)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Index);
		return result;
	}
	long GetLinkPointLat(long Index)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Index);
		return result;
	}
	long GetLinkDistance()
	{
		long result;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetLinkRoadKind()
	{
		long result;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetLinkLinkKind()
	{
		long result;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetLinkLinkFacility()
	{
		long result;
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString GetLinkRoadName()
	{
		CString result;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString GetLinkFacilName()
	{
		CString result;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long GetCurrentRouteIndex()
	{
		long result;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetCurrentRouteIndex(long Index)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
	}
	long GetRouteCount()
	{
		long result;
		InvokeHelper(0x23, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetRouteStartPosCoordType()
	{
		long result;
		InvokeHelper(0x24, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetRouteStartLon()
	{
		long result;
		InvokeHelper(0x25, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetRouteStartLat()
	{
		long result;
		InvokeHelper(0x26, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetRouteEndPosCoordType()
	{
		long result;
		InvokeHelper(0x27, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetRouteEndLon()
	{
		long result;
		InvokeHelper(0x28, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetRouteEndLat()
	{
		long result;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetRouteDistance()
	{
		long result;
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetRouteTravelTime()
	{
		long result;
		InvokeHelper(0x2b, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetRouteTollFare()
	{
		long result;
		InvokeHelper(0x2c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void ChangeLinkVertexCoordType(long Type)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type);
	}
	long GetResult()
	{
		long result;
		InvokeHelper(0x2e, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}

	// IXRouteInfo4 속성
public:

};
