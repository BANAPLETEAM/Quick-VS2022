// ��ǻ�Ϳ��� ���� ���̺귯�� �������� [Ŭ���� �߰�]�� ����Ͽ� ������ IDispatch ���� Ŭ�����Դϴ�.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXGPS_Info ���� Ŭ����

class CXGPS_Info : public COleDispatchDriver
{
public:
	CXGPS_Info(){} // COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	CXGPS_Info(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXGPS_Info(const CXGPS_Info& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Ư��
public:

	// �۾�
public:


	// IXGPS_Info �޼���
public:
	LPDISPATCH GetGPS_Pos()
	{
		LPDISPATCH result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetGPS_Satellite(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}
	long GetGPS_SatelliteCount()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}

	// IXGPS_Info �Ӽ�
public:

};
