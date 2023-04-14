// ��ǻ�Ϳ��� ���� ���̺귯�� �������� [Ŭ���� �߰�]�� ����Ͽ� ������ IDispatch ���� Ŭ�����Դϴ�.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXGPS_Satellite ���� Ŭ����

class CXGPS_Satellite : public COleDispatchDriver
{
public:
	CXGPS_Satellite(){} // COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	CXGPS_Satellite(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXGPS_Satellite(const CXGPS_Satellite& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Ư��
public:

	// �۾�
public:


	// IXGPS_Satellite �޼���
public:
	unsigned char GetUsedForFix()
	{
		unsigned char result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	unsigned char GetSatelliteID()
	{
		unsigned char result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	unsigned char GetElevation()
	{
		unsigned char result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	long GetAzimuth()
	{
		long result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetSnr()
	{
		long result;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}

	// IXGPS_Satellite �Ӽ�
public:

};
