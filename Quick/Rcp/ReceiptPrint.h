#pragma once



typedef struct 
{

		CString sCompany;
		CString sDept;
		CString sName;
		CString sTel;

		CString sDestDong;
		CString sCarNameAndChargeType;
		CString sDestCompany;
	
		CString sDestTel;
		CString sDestDept;
		CString sDestName;

		long nRNo;
		long nTNo;
		CString sRName;

		CStringArray sStartDetail;
		
		CString sDate;

		long nBasicCharge;
		long nAddCharge;
		long nTransCharge;
		long nTotalCharge;

}RECEIPT_INFO;

typedef vector<RECEIPT_INFO* > VEC_RECEIPT_INFO;

class CReceiptPrint
{
public:
	CReceiptPrint(void);
	~CReceiptPrint(void);

	HDC m_hdcPrinter;
	void PrinterSetting();
	BOOL IsPrinterSetting();
	
	BOOL m_bPrinterSetting;
	VEC_RECEIPT_INFO m_vecReceiptInfo;

	HDC *m_phdcPrinter;
	void SetInputData(RECEIPT_INFO *pReceiptInfo);
	void Print();

	void InnerPrintText(CDC &dcPrint,RECEIPT_INFO *pReceiptInfo);

};
