// ��ǻ�Ϳ��� ���� ���̺귯�� �������� [Ŭ���� �߰�]�� ����Ͽ� ������ IDispatch ���� Ŭ�����Դϴ�.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXTHMI_Text ���� Ŭ����

class CXTHMI_Text : public COleDispatchDriver
{
public:
	CXTHMI_Text(){} // COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	CXTHMI_Text(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXTHMI_Text(const CXTHMI_Text& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Ư��
public:

	// �۾�
public:


	// IXTHMI_Text �޼���
public:
	LPDISPATCH GetInfo()
	{
		LPDISPATCH result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void SetInfo(LPDISPATCH Info)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Info);
	}
	LPDISPATCH GetStyle(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}
	void SetStyle(long Index, LPDISPATCH TextStyle)
	{
		static BYTE parms[] = VTS_I4 VTS_DISPATCH ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, TextStyle);
	}

	// IXTHMI_Text �Ӽ�
public:

};
