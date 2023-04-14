#pragma once


class CChargeDongDlg2;
class CChargeDongDlg3;
class CChargeDistanceDlg2;
class CSelectChargeType;
class CDistanceChargeDlg;


class CChargeContainer
{
public:
	CChargeContainer();
	CChargeContainer(CWnd *pOwner);
	~CChargeContainer(void);

public:
	
	CChargeDongDlg3		*m_pChargeDongDlg3;	
	CChargeDongDlg2		*m_pChargeDongDlg2;	
	CChargeDistanceDlg2 *m_pChargeDistanceDlg2;
	CSelectChargeType	*m_pSelectChargeTypeDlg;
	CWnd				*m_pwndOwner;


	BOOL IsIntegrated();	
	void ChargeDongDlg3Show();	
	void ChargeDistanceDlgShow(CBranchInfo *pBi = NULL);
	void ChargeShow();
	template<class CMyDlg> 
	void CreateModalessChargeDlg(CMyDlg **pDlg, long nCompany, 
				CString strBranchName = "", void (*pfInit)(CMyDlg*, CChargeContainer*) = NULL);
};
