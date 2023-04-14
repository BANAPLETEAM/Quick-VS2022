// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXTHMI_Class 래퍼 클래스

class CXTHMI_Class : public COleDispatchDriver
{
public:
	CXTHMI_Class(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXTHMI_Class(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXTHMI_Class(const CXTHMI_Class& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXTHMI_Class 메서드
public:
	unsigned short GetSeq()
	{
		unsigned short result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_UI2, (void*)&result, NULL);
		return result;
	}
	unsigned char GetEnabled()
	{
		unsigned char result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	unsigned char GetTp()
	{
		unsigned char result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	unsigned char GetSubtp()
	{
		unsigned char result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetSeq(unsigned short Value)
	{
		static BYTE parms[] = VTS_UI2 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	void SetEnabled(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	void SetTp(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	void SetSubtp(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}

	// IXTHMI_Class 속성
public:

};
