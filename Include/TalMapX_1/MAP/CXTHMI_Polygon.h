// ��ǻ�Ϳ��� ���� ���̺귯�� �������� [Ŭ���� �߰�]�� ����Ͽ� ������ IDispatch ���� Ŭ�����Դϴ�.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXTHMI_Polygon ���� Ŭ����

class CXTHMI_Polygon : public COleDispatchDriver
{
public:
	CXTHMI_Polygon(){} // COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	CXTHMI_Polygon(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXTHMI_Polygon(const CXTHMI_Polygon& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Ư��
public:

	// �۾�
public:


	// IXTHMI_Polygon �޼���
public:
	LPDISPATCH GetInfo()
	{
		LPDISPATCH result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetStyle(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}

	// IXTHMI_Polygon �Ӽ�
public:

};
