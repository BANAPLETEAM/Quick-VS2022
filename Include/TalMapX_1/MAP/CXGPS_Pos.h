// ��ǻ�Ϳ��� ���� ���̺귯�� �������� [Ŭ���� �߰�]�� ����Ͽ� ������ IDispatch ���� Ŭ�����Դϴ�.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXGPS_Pos ���� Ŭ����

class CXGPS_Pos : public COleDispatchDriver
{
public:
	CXGPS_Pos(){} // COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	CXGPS_Pos(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXGPS_Pos(const CXGPS_Pos& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Ư��
public:

	// �۾�
public:


	// IXGPS_Pos �޼���
public:
	VARIANT GetTime()
	{
		VARIANT result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	CString GetTimeToStr()
	{
		CString result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long GetTimeAsSystemTime()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetMapPos()
	{
		LPDISPATCH result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	double GetSpeed()
	{
		double result;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}
	double GetAltitude()
	{
		double result;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}
	double GetAngle()
	{
		double result;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}
	unsigned char GetFixMode()
	{
		unsigned char result;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	double GetPDop()
	{
		double result;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}
	double GetHDop()
	{
		double result;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}
	double GetVDop()
	{
		double result;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}

	// IXGPS_Pos �Ӽ�
public:

};
