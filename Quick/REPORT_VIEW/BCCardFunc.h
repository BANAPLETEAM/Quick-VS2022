#pragma once

#include "stdafx.h"

extern CMkDatabase *m_pMkDb4BCCard;
extern int GetBCCardNumber(const char* szServer, CString sHeadBranchCode,CString strHp,CString& sCardNumber,
							CString& sCustomerName, CString &strBalance, CString& strError);
extern int BCCardRequestOK(const char* szServer,const char* szHeadBranchCode,const char* szPhoneNumber,const char* szCardNumber,const char* szCharge,const char* szInsurance,
						   const char* szSSN,CString& strTransactionNumber, CString& strBalance, CString& strError);
extern int BCCardCancel(const char* szServer,const char* szTNo,const char* szCancelMode,const char* szTransactionNumber, CString& strError);
extern int CardOKRequest(int nTNo,CString& strError);
extern int CardCancelRequest(int nTNo,int nWCompany,int nWNo, const char* szTranNumber,CString& strError);
extern int nCardType(int nTNo,int nCompany);