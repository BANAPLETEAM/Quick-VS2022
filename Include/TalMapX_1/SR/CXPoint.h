// CXPoint.h  : Microsoft Visual C++�� ���� ActiveX ��Ʈ�� ���� Ŭ������ �����Դϴ�.

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CXPoint

class CXPoint : public COleDispatchDriver
{
public:
	CXPoint() {}		// COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	CXPoint(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXPoint(const CXPoint& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Ư���Դϴ�.
public:

	// �۾��Դϴ�.
public:

	void SetX(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetX()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get__X()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put__X(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void SetY(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetY()
	{
		long result;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get__Y()
	{
		long result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put__Y(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}


};
