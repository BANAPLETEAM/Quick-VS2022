// ��ǻ�Ϳ��� ���� ���̺귯�� �������� [Ŭ���� �߰�]�� ����Ͽ� ������ IDispatch ���� Ŭ�����Դϴ�.

//#import "C:\\Users\\TAEIN\\Documents\\eKsys\\Library\\DLL\\SmartSR\\SmartSRX_1.0.0.88.dll" no_namespace
// CSmartSRXCtrl ���� Ŭ����

class CSmartSRXCtrl : public COleDispatchDriver
{
public:
	CSmartSRXCtrl(){} // COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	CSmartSRXCtrl(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CSmartSRXCtrl(const CSmartSRXCtrl& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Ư��
public:

	// �۾�
public:


	// ISmartSRXCtrl �޼���
public:
	LPDISPATCH GetAddrMan()
	{
		LPDISPATCH result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetNewAddrMan()
	{
		LPDISPATCH result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetAAdminMan()
	{
		LPDISPATCH result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetBAdminMan()
	{
		LPDISPATCH result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetClassTypeMan()
	{
		LPDISPATCH result;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetAreaTypeMan()
	{
		LPDISPATCH result;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetPOIMan()
	{
		LPDISPATCH result;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetRouteMan()
	{
		LPDISPATCH result;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetKCSNewAddrMan()
	{
		LPDISPATCH result;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetCoordSys()
	{
		LPDISPATCH result;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void SetLicenseType(long Type)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type);
	}
	long GetLicenseType()
	{
		long result;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	BOOL SetLicenseInfo(LPCTSTR ClientID, LPCTSTR ServiceID, LPCTSTR Path, long Type)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, ClientID, ServiceID, Path, Type);
		return result;
	}
	long GetLicenseInfo(LPCTSTR ClientID, LPCTSTR ServiceID, long Type)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ClientID, ServiceID, Type);
		return result;
	}
	BOOL LoadLicense(LPCTSTR Path)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Path);
		return result;
	}

	// ISmartSRXCtrl �Ӽ�
public:

};
