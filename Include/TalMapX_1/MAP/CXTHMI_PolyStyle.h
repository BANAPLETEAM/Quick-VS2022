// ��ǻ�Ϳ��� ���� ���̺귯�� �������� [Ŭ���� �߰�]�� ����Ͽ� ������ IDispatch ���� Ŭ�����Դϴ�.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXTHMI_PolyStyle ���� Ŭ����

class CXTHMI_PolyStyle : public COleDispatchDriver
{
public:
	CXTHMI_PolyStyle(){} // COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	CXTHMI_PolyStyle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXTHMI_PolyStyle(const CXTHMI_PolyStyle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Ư��
public:

	// �۾�
public:


	// IXTHMI_PolyStyle �޼���
public:
	unsigned char GetVisible()
	{
		unsigned char result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	unsigned char GetAlpha()
	{
		unsigned char result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	unsigned char GetPen()
	{
		unsigned char result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	unsigned char GetPen1()
	{
		unsigned char result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	unsigned char GetBrush()
	{
		unsigned char result;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}

	// IXTHMI_PolyStyle �Ӽ�
public:

};
