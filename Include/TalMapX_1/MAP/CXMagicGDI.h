// ��ǻ�Ϳ��� ���� ���̺귯�� �������� [Ŭ���� �߰�]�� ����Ͽ� ������ IDispatch ���� Ŭ�����Դϴ�.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXMagicGDI ���� Ŭ����

class CXMagicGDI : public COleDispatchDriver
{
public:
	CXMagicGDI(){} // COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	CXMagicGDI(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXMagicGDI(const CXMagicGDI& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Ư��
public:

	// �۾�
public:


	// IXMagicGDI �޼���
public:
	void SetAutoDestroy(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2329, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}

	// IXMagicGDI �Ӽ�
public:

};
