// ��ǻ�Ϳ��� ���� ���̺귯�� �������� [Ŭ���� �߰�]�� ����Ͽ� ������ IDispatch ���� Ŭ�����Դϴ�.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXMapPos3D ���� Ŭ����

class CXMapPos3D : public COleDispatchDriver
{
public:
	CXMapPos3D(){} // COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	CXMapPos3D(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXMapPos3D(const CXMapPos3D& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Ư��
public:

	// �۾�
public:


	// IXMapPos3D �޼���
public:
	void SetLon(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetLon()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put__Lon(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get__Lon()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetLat(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetLat()
	{
		long result;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put__Lat(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get__Lat()
	{
		long result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetAltitude(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetAltitude()
	{
		long result;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put__Altitude(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get__Altitude()
	{
		long result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}

	// IXMapPos3D �Ӽ�
public:

};
