#pragma once


class CPOIUnit;

class CRcpDlg;

#define  CAR_TYPE 21

#define TYPE_A 0
#define TYPE_B 1
#define TYPE_C 2
#define TYPE_D 3
#define TYPE_GNO 4

#define T_AUTO 0
#define T_DAMA 1
#define T_RABO 2
#define T_BAN 3
#define T_TRUCK 4
#define T_SUBWAY 5

#define T_T2ton  6
#define T_T3ton  7
#define T_T5ton  8


/* GlobalDefType.h�� ���� �Ǿ� ����
enum { PAY_PRE = 0, PAY_AFTER, PAY_CREDIT, PAY_ONLINE, PAY_DIRECT, PAY_IMSI, PAY_IMSI2, PAY_CARD = 7};
enum { CAR_AUTO = 0, CAR_BIGBIKE, CAR_DAMA, CAR_LABO, CAR_VAN, CAR_TRUCK};
enum { CHARGE_TYPE_A = 0, CHARGE_TYPE_B, CHARGE_TYPE_C, CHARGE_TYPE_D, CHARGE_TYPE_GNO};
*/
#define CHARGE_TYPE 5
#define CAR_TYPE_COUNT 6

typedef struct{
	long nType;
	long nStartID;
	long nDestID;
	long nCharge[CAR_TYPE_COUNT][CHARGE_TYPE];
} CHARGE_STRUCT;

typedef struct{
	long nCharge;
	long nChargeRider;
	long nDiscount;	
} CHARGE_GNO_STRUCT;

typedef map<long, CHARGE_STRUCT> CHARGE_MAP;

typedef map<pair<long, long>, CHARGE_GNO_STRUCT> CHARGE_GNO_MAP;

class CCharge
{
public:
	CCharge(CWnd *pwndParent);
	~CCharge(void);

	CPOIUnit* m_pStartPoi;
	CPOIUnit* m_pDestPoi;
	CRcpDlg *m_pRcpDlg;

	BOOL m_bChargeTypeCelChange;
	
	long	m_nCharge;  // ������ ��
	int		m_nChargeType;
	int		m_nCarType;	
	int		m_nRealCarType;
	float m_lfDistance;
	long m_nGNo;
	CBranchInfo *m_pBi;
	
	BOOL m_bMemCharge;
	long m_nMemCharge;
	long m_nEmergency;
	BOOL m_bGroupCharge;
	CString m_strInfoTotal;

	long m_nExCharge;	
	BOOL m_bExCharge;
public:
	CBranchInfo* GetBI();

	void InitBranchInfo(CWnd *pWnd, CBranchInfo *pBi);
	BOOL IsSameRunType(int nRunType);
	long DefaultCharge(long nCharge);          // �⺻���
	long m_nDefaultCharge; // ����� ������ �⺻���
	BOOL m_bDefaultCharge; 

	long MinCharge(long nCharge);          // �������  ���������� ����
	long m_nMinCharge; // ����� ������ �⺻���
	BOOL m_bMinCharge;	
	BOOL m_bNotMemberCharge; // ��ü��� ������.
	BOOL m_bMemChaNoGeneralData;  // ��ü��ݻ��� �Ϲݿ�� 
	void NewDongCharge();			// ���������
	//long m_nNewDongCharge[CHARGE_TYPE][CAR_TYPE]; // �������
	CHARGE_GNO_MAP m_nNewDongCharge;
	BOOL m_bNewDongCharge;  // 

	CHARGE_GNO_MAP::iterator GetGNoMapIterator(long nChargeType, long nCarType);
	
	long m_nDistanceCharge;
	BOOL m_bDistanceCharge;

	int DistanceTypeCharge();		// ���ÿ����
	
	long m_nDistanceTypeCharge[CHARGE_TYPE][CAR_TYPE]; // ���ÿ����
	BOOL m_bDistanceTypeCharge;  // 
	CString m_strKmNameType; // �Ÿ�����̸�
	int m_nAmountType;

	long GetDistanceTypeCharge() { return m_nAmountType; }

	BOOL m_bNoGroupCharge;
	BOOL IsMinCharge(long nCharge);							// �ּұݾ�
	BOOL IsDefaultCharge(long nCharge);						// �⺻�ݾ�
	
	BOOL m_bCashCharge;
	BOOL IsCashCharge(){return m_bCashCharge;}  // �⺻NewDongCharge, ����DistanceTypeCharge ,�Ÿ��� �̾ȿ��� TRUE
																			// FALSE �ʱ�ȭ�� Init
	void SetCashCharge(BOOL bTRUE){ m_bCashCharge = bTRUE ;}  // 
	void SetNullData(); 
	CString GetDistanceTypeString(int nAmountType, CString strDeistanceType );

public:
	BOOL IsOptionNewDongCharge();		// �⺻���
	BOOL IsOptionOnlyDistanceCharge();		// km ��  �Ÿ����
	BOOL IsOptionDistanceTypeCharge();// ���ÿ��	
	
	BOOL IsGroupChargeApply()	{ return  m_bGroupCharge && !m_bNoGroupCharge ?  TRUE : FALSE ;} //�⺻���
	BOOL IsMemberChargeApply()	{ return  m_bMemCharge ?  TRUE : FALSE ;} //�⺻���
	
	BOOL IsNewDongChargeApply()	
	{ 
		CHARGE_GNO_MAP::iterator it = m_nNewDongCharge.find(make_pair(m_nChargeType, m_nCarType));
		
		if(it == m_nNewDongCharge.end())
			return FALSE;

		return it->second.nCharge > 0;

	} //�⺻���

	BOOL IsDistanceChargeTypeApply()	{ return  m_nDistanceTypeCharge[m_nChargeType] > 0 ? TRUE : FALSE ;} //�Ÿ����	
	BOOL IsDistanceChargeApply() 	{	return	(m_bDistanceCharge && !m_pBi->bDistanceCharge) ? TRUE : FALSE;	}
	BOOL IsDefaultChargeApply() 	{	return	(m_bDefaultCharge ) ? TRUE : FALSE;	}
	BOOL IsMinChargeApply() 	{	return	(m_bMinCharge && m_pBi->bDistanceCharge) ? TRUE : FALSE;	}

	long GetNewDongCharge() 
	{ 
		CHARGE_GNO_MAP::iterator it = m_nNewDongCharge.end();

		if(m_nChargeType ==  TYPE_GNO)
			it = m_nNewDongCharge.find(make_pair(TYPE_A, m_nCarType));
		else
			it = m_nNewDongCharge.find(make_pair(m_nChargeType, m_nCarType));

		if(it == m_nNewDongCharge.end())
			return 0;

		return it->second.nCharge;

		/*
		if(m_nChargeType ==  TYPE_GNO)
			return m_nNewDongCharge[TYPE_A][m_nCarType]; 
		else
			return m_nNewDongCharge[m_nChargeType][m_nCarType]; 
		*/
	}
	long GetGroupCharge(int nCarType)
	{	
		CHARGE_GNO_MAP::iterator it = m_nNewDongCharge.find(make_pair(TYPE_GNO, m_nCarType));

		if(it == m_nNewDongCharge.end())
			return 0;

		return it->second.nChargeRider;

		//return m_nNewDongCharge[TYPE_GNO][nCarType];
	}	
	long GetMemberCharge(int nCarType)
	{
		CHARGE_GNO_MAP::iterator it = m_nNewDongCharge.find(make_pair(TYPE_GNO, m_nCarType));

		if(it == m_nNewDongCharge.end())
			return 0;

		return it->second.nChargeRider;

		//return m_nNewDongCharge[TYPE_GNO][nCarType];
	}
	

	long GetDefaultCharge() { return m_nDefaultCharge; }
	long GetMinCharge() { return m_nMinCharge; }
	//long	 GetViaCountCharge() { return m_nViaCharge;}
	
	BOOL RemoveAllData(); // �ܺο��� ������ �ʱ�ȭ
	
	CString GetDistanceLableView();		
	CString GetChargeTypeString(int nInputType = -1);

	long GetTotalCharge(long nMemCharge, CPOIUnit *m_pStartPoi, CPOIUnit *m_pDestPoi,long nGNo,
		CBranchInfo *m_pBi, long &nChargeDriving, long &nDiscount, float nDistance = 0, 
		int nChargeType = 0, int nCarType = 0, BOOL bNoGroupCharge = FALSE, int nEmergency = 0, int nRealCarType = 0
		);  //����� ���� ���


	long GetCashCharge(long nMemCharge, CPOIUnit *pStartPoi, CPOIUnit *pDestPoi,long nGNo,
		CBranchInfo *pBi, long &nChargeDriving, long &nDiscount, float nDistance , int nChargeType, int nCarType, BOOL bChargeTypeCelChange);
	CPOIUnit* GetStartPoi();
	CPOIUnit* GetDestPoi();

	BOOL IsGNo();

public:
	CHARGE_MAP m_mapChargeGeneral;
	CHARGE_MAP m_mapChargeGNo;

	BOOL m_bHasCharge;
	long m_nPreGNo;
	long m_nPreStartID;
	long m_nPreDestID;
	long m_nChargeTotal[CAR_TYPE_COUNT][CHARGE_TYPE];
};



typedef struct{
	int nCompany;
	int nPOIType;
	int nExChargeStart;
	int nExChargeDest;
	CString strPOIName;
	CString strEtc;
	CPOIUnit *pPOI;
} CHARGE_DONG_EX2011;

typedef map<pair<long, long>, CHARGE_DONG_EX2011> CHARGE_DONG_EX_MAP2011;

#define  DISTANCE_EMPTY 0
#define  DISTANCE_SEARCH 1
#define  DISTANCE_FINISH 2

#define  DEFAULT_CHARGE 0
#define  MIN_CHARGE 1
#define  NEWDONG_CHARGE 2
#define  DISTANCE_CHARGE 4
#define  DISTANCETYPE_CHARGE 8
//
//
class CCharge;


class CDisplayChargeInfo
{
public:

	CDisplayChargeInfo(CWnd *pwndParent);	
	~CDisplayChargeInfo();
	void RemoveAllData();
	CRcpDlg *m_pRcpDlg;
	void SetRcpDlg(CRcpDlg *pRcpDlg){m_pRcpDlg = pRcpDlg;}
	CCharge *m_pCharge;
	void SetChargeClass(CCharge *pCharge){m_pCharge = pCharge;}

	//------------------------------------  �Ÿ�	
	CString GetDistance();
	
	//------------------------------------ ��->��	
	CString GetStartDestInfo();
	//------------------------------------  ���(�⺻, �Ϲ�, �Ÿ�)
	
	CString GetCharge();

	CString GetGeneralDisplay()
	{
		CString strTemp = "";
		strTemp =	GetStartDestInfo().GetLength() > 0?	GetStartDestInfo() + "," : "" ;
		strTemp =	GetDistance().GetLength() > 0		?	GetDistance() + "," : "";
		strTemp =	GetCharge().GetLength() > 0		?	GetCharge() : "";
		//strTemp 
		return strTemp;
		 
	}
/*
	// �߰����
	BOOL m_bAddCharge;
	CString m_sAddCharge;

	CString m_sGeneralDisplay;

	
	CString GetChargeAddDisplay()
	{
		
	}
*/
};