// ��ǻ�Ϳ��� ���� ���̺귯�� �������� [Ŭ���� �߰�]�� ����Ͽ� ������ IDispatch ���� Ŭ�����Դϴ�.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXCoordSys0 ���� Ŭ����

class CXCoordSys0 : public COleDispatchDriver
{
public:
	CXCoordSys0(){} // COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	CXCoordSys0(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXCoordSys0(const CXCoordSys0& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Ư��
public:

	// �۾�
public:


	// IXCoordSys �޼���
public:
	LPDISPATCH WGS84ToBessel(double Lon, double Lat)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_R8 VTS_R8 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Lon, Lat);
		return result;
	}
	LPDISPATCH BesselToWGS84(double Lon, double Lat)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_R8 VTS_R8 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Lon, Lat);
		return result;
	}
	LPDISPATCH BesselToTM(double Lon, double Lat, double BaseLon, double BaseLat)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Lon, Lat, BaseLon, BaseLat);
		return result;
	}
	LPDISPATCH TMToBessel(double tmX, double tmY, double BaseLon, double BaseLat)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, tmX, tmY, BaseLon, BaseLat);
		return result;
	}
	LPDISPATCH WGS84ToTM(double Lon, double Lat, double BaseLon, double BaseLat)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Lon, Lat, BaseLon, BaseLat);
		return result;
	}
	LPDISPATCH TMToWGS84(double tmX, double tmY, double BaseLon, double BaseLat)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, tmX, tmY, BaseLon, BaseLat);
		return result;
	}
	LPDISPATCH BesselToUTM(double Lon, double Lat)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_R8 VTS_R8 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Lon, Lat);
		return result;
	}
	LPDISPATCH UTMToBessel(double tmX, double tmY)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_R8 VTS_R8 ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, tmX, tmY);
		return result;
	}
	LPDISPATCH BesselToKatec(double Lon, double Lat)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_R8 VTS_R8 ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Lon, Lat);
		return result;
	}
	LPDISPATCH KatecToBessel(double X, double Y)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_R8 VTS_R8 ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, X, Y);
		return result;
	}
	double GetRealDistance(double Lon1, double Lat1, double Lon2, double Lat2)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Lon1, Lat1, Lon2, Lat2);
		return result;
	}
	LPDISPATCH KatecToBesselInt(double X, double Y)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_R8 VTS_R8 ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, X, Y);
		return result;
	}
	CString ToHMSStr(double Value)
	{
		CString result;
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Value);
		return result;
	}

	// IXCoordSys �Ӽ�
public:

};
