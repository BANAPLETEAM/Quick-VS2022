// ��ǻ�Ϳ��� ���� ���̺귯�� �������� [Ŭ���� �߰�]�� ����Ͽ� ������ IDispatch ���� Ŭ�����Դϴ�.

//#import "C:\\Users\\TAEIN\\Documents\\eKsys\\Library\\DLL\\SmartSR\\SmartSRX_1.0.0.88.dll" no_namespace
// CXRouteInfo3 ���� Ŭ����

class CXRouteInfo3 : public COleDispatchDriver
{
public:
	CXRouteInfo3(){} // COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	CXRouteInfo3(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXRouteInfo3(const CXRouteInfo3& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Ư��
public:

	// �۾�
public:


	// IXRouteInfo3 �޼���
public:
	long GetResult()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetTotalDistance()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetTotalTime()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetTotalToll()
	{
		long result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}

	// IXRouteInfo3 �Ӽ�
public:

};
