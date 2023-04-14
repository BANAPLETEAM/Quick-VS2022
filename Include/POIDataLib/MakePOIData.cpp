#include "StdAfx.h"
#include "MakePOIData.h"
#include "DisplayBarThread.h"
#include "POIdataNew.h"
#include "POIBoundary.h"
#include "INI.h"

#define POI_INI_FILE			"poi.ini"
#define POI_FREE_SPACE_RATE		5

#define SYSTEM_CODE_THREE 3


CMakePOIData::CMakePOIData(CPOIDataNew *pPOINew, CMkDatabase *pMkDb, CString strCity, 
						BOOL bCapitalArea, BOOL bUpdatePOINameForUserPOI, 
						BOOL bNotUseParitalUpdate, long nSystemCode)
{
	m_pPOINew = pPOINew;
	m_pMkDb = pMkDb;
	m_strCity = strCity;
	m_bCapitalArea = bCapitalArea;
	m_nSystemCode = nSystemCode;
	//m_pPOINew->SetCapitalArea(bCapitalArea);
	m_pPOINew->SetCapitalArea(m_nSystemCode == SYSTEM_CODE_THREE ? TRUE : FALSE);
	//m_bUpdatePOINameForUserPOI = !m_bCapitalArea && m_strCity.Find("���") < 0 && bUpdatePOINameForUserPOI;
	m_bUpdatePOINameForUserPOI = FALSE;
	m_bNotUseParitalUpdate = bNotUseParitalUpdate;

#ifndef _LOGIDB2012
	m_pDBT = m_pMkDb->m_pDBT;
#else
	m_pDBT = CMkDatabase::GetDBTPool()->GetTop();
#endif
}

CMakePOIData::~CMakePOIData(void)
{
}

BOOL CMakePOIData::MakeDongDataFromFile()
{
	CDisplayBarThreadText dbt(m_pDBT, "POI �������͸� �ε����Դϴ�.", TRUE, 0);
	if(m_pPOINew->LoadDongPOI())
	{
		dbt.SetText("POI ���������� �������� ������Ʈ���Դϴ�.");

		if(!m_pPOINew->UpdateDongHasPOI(TRUE))
			return FALSE;

		MakeBoundaryInfo();

		dbt.SetText("POI�� ĳ�������͸� �ε����Դϴ�.");
		if(!m_pPOINew->LoadPartDongPOI())
		{
			dbt.SetText("POI ���������� ĳ�������͸� �������Դϴ�.");
			m_pPOINew->MakeDongVector();

			dbt.SetText("POI ���������� ĳ�������͸� �������Դϴ�.");
			m_pPOINew->SavePartDongPOI();
		}

		m_pPOINew->AddSpecialLog("MakeDongDataFromFile: m_vecDong = %d\n", m_pPOINew->m_vecDong.size());
		return TRUE;
	}
	return FALSE;
}

BOOL CMakePOIData::MakeDongDataFromNetwork()
{
	//CDisplayBarThreadText dbt(m_pDBT, "POI �������͸� �������� ���Դϴ�.", TRUE, 0);

	//CDisplayBarThreadText dbt(m_pDBT, "POI �������͸� �������� ���Դϴ�.", TRUE, 0);

	CString strTemp = "";
	strTemp += "POI �������͸� �������� ���Դϴ�.\r\n";
	//strTemp += "�������ͳ����� ��� �� POI �������͸� �������� �߿� �ٿ�Ǵ� ������ ���� �� �ֽ��ϴ�.\r\n";
	//strTemp += "���α׷��� �ٿ�� ���\r\n";
	strTemp += "���α׷��� �ٿ�� ��� \"���_POI���ü���\"���� \"����POI�� �ε���\" üũ�Ͽ��ֽñ� �ٶ��ϴ�.";

	CDisplayBarThreadText dbt(m_pDBT, strTemp, TRUE, 0);

	POI_VEC &vec = m_pPOINew->m_vecDong;
	vec.clear();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_dong_poi_data_new", TRUE, TRUE);
	cmd.AddParameter(0);
	cmd.AddParameter(0);

	if(rs.Execute(&cmd, "POI �������͸� �Է����Դϴ�."))
	{
		dbt.SetText("POI �������͸� �Է����Դϴ�.");

		CString strLi;
		CPOIUnit poi;
		BOOL bLi;

		poi.m_bDongData = TRUE;
		poi.m_bHasChild = FALSE;
		vec.reserve(rs.GetRecordCount());

		while(!rs.IsEOF())
		{
			rs.GetFieldValue("bLi", bLi);
			rs.GetFieldValue("nPosX", poi.m_nPosX);
			rs.GetFieldValue("nPosY", poi.m_nPosY);
			rs.GetFieldValue("sSido", poi.m_szSido);
			rs.GetFieldValue("sGugun", poi.m_szGugun);
			rs.GetFieldValue("sGugun2", poi.m_szGugun2);
			rs.GetFieldValue("sDong", poi.m_szDong);
			rs.GetFieldValue("nParentID", poi.m_nParentID);
			rs.GetFieldValue("nID", poi.m_nID);
			rs.GetFieldValue("nMainDongID", poi.m_nMainDongID);
			rs.GetFieldValue("nClass", poi.m_nClass);
			rs.GetFieldValue("sLi", poi.m_szLi);

			if(poi.m_nID == 3251)
			{ 
				int i = 0; 
			}

			poi.SetPOIType(TRUE);
			vec.push_back(poi);

			rs.MoveNext();
		}

		g_bana_log->Print("dong data = %d\n", vec.size());
		m_pPOINew->SortPOIVector(vec);
		dbt.SetText("POI ���������� �������� ������Ʈ���Դϴ�.");
		m_pPOINew->UpdateDongHasPOI();
		MakeBoundaryInfo();
		dbt.SetText("POI �������͸� �������Դϴ�.");
		m_pPOINew->SaveDongPOI();
		dbt.SetText("POI ���������� ĳ�������͸� �������Դϴ�.");
		m_pPOINew->MakeDongVector();
		dbt.SetText("POI ���������� ĳ�������͸� �������Դϴ�.");
		m_pPOINew->SavePartDongPOI();
		return TRUE;
	}
	return FALSE;
}

BOOL CMakePOIData::MakePOIDataFromFile()
{
	CDisplayBarThreadText dbt(m_pDBT, "POI�� �ε����Դϴ�.", TRUE, 0);
	if(m_pPOINew->LoadPOI(GetRegionFileName(POI_FILE_NAME), 1, m_bCapitalArea ? POI_FREE_SPACE_RATE : 0))
	{
		CIniReader ini(GetModuleFullPath() + POI_INI_FILE_NAME);
		CString strVersion = ini.getKeyValue("Version", GetRegionFileName());
		CString strDate = ini.getKeyValue("Date", GetRegionFileName());

		if(m_bNotUseParitalUpdate)
		{
			g_bana_log->Print("QUICK�̶�, �κо�����Ʈ ��ŵ\n");
		}
		else
		{
			if(m_bCapitalArea && strVersion.GetLength() > 0 && strDate.GetLength() > 0)
			{
				if(StringDateToDate(strDate, m_dtLastRefresh))
				{
					COleDateTimeSpan span = COleDateTime::GetCurrentTime() - m_dtLastRefresh;
					if(span.GetTotalDays() > 100)
						return FALSE;

					int nRet = MakePOIDataFromNetwork(TRUE);
					
					if(nRet == TRUE)
					{
						ini.setKey(DateToStringDate(m_dtLastRefresh), "Date", GetRegionFileName());
						return TRUE;
					}
					else if(nRet == 0)
					{
						return FALSE;
					}
				}
			}
		}


		//�������
		m_pPOINew->AddSpecialLog("MakePOIDataFromFile: m_vecPOI = %d", m_pPOINew->m_vecPOI.size());

		dbt.SetText("POI�� �������� ������Ʈ ���Դϴ�.");
		m_pPOINew->UpdatePOIHasPOI(GetRegionFileName(), TRUE);

		dbt.SetText("POI�� ĳ�������͸� �ε����Դϴ�.");
		if(!m_pPOINew->LoadPartPOI(GetRegionFileName(PART_POI_FILE_NAME)))
		{
			dbt.SetText("POI�� ĳ�������͸� �������Դϴ�.");
			m_pPOINew->MakePartPOIVector();

			dbt.SetText("POI�� ĳ�������͸� �������Դϴ�.");
			m_pPOINew->SavePartPOI(GetRegionFileName(PART_POI_FILE_NAME));
		}

		return TRUE;
	}
	return FALSE;
}


int CMakePOIData::MakePOIDataFromNetwork(BOOL bOnlyChanged)
{
	BOOL bSimple = FALSE, bDualServer = FALSE;
#ifdef _DEBUG
	bSimple = TRUE;
#else
	bSimple = AfxGetApp()->GetProfileInt("POI", "LoadOnlyMainPOI", 0);
#endif

	CDisplayBarThreadText dbt(m_pDBT, "POI�����͸� �������� ���Դϴ�.(���ʽ����/������Ʈ�ø� �����ɸ�)", TRUE, 0);
	POI_VEC &vec = m_pPOINew->m_vecPOI;
	DWORD dwTickCount = GetTickCount();

	CMkDatabase *pMkDb2 = NULL;

#ifndef _LOGIDB2012
	if(m_bCapitalArea && !bSimple && !bOnlyChanged)
	{
		if(!m_pMkDb->CopyDatabase(&pMkDb2))
		{
			delete pMkDb2;
			pMkDb2 = NULL;
		}
	}
#endif

	CString strQuery = "select_custom_poi_2011_6";
	BOOL bRet = FALSE;

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, strQuery);
	CMkCommand cmd2;

	cmd.AddParameter(m_nSystemCode);
	cmd.AddParameter(m_strCity);
	cmd.AddParameter(bSimple);
	cmd.AddParameter(pMkDb2 ? 1 : 0);
	cmd.AddParameter(bOnlyChanged);
	CMkParameter *parOutDate = cmd.AddParameter(m_dtLastRefresh, typeOutput);

	if(pMkDb2)
	{
		cmd2.SetMkCommand(pMkDb2, strQuery);
		cmd2.AddParameter(m_nSystemCode);
		cmd2.AddParameter(m_strCity);
		cmd2.AddParameter(bSimple);
		cmd2.AddParameter(2);
		cmd2.AddParameter(bOnlyChanged);
		cmd2.AddParameter(m_dtLastRefresh, typeOutput);
		bRet = rs.Execute(&cmd, &cmd2, "POI�����͸� �������� ���Դϴ�. (���ʽ����/������Ʈ�ø� �����ɸ�)");
	}
	else
	{
		bRet = rs.Execute(&cmd, "POI�����͸� �������� ���Դϴ�. (���ʽ����/������Ʈ�ø� �����ɸ�)");
	}


	if(bRet)
	{
		dbt.SetText("POI �����͸� �Է����Դϴ�.");
		g_bana_log->Print("NETWORK %dms, RecordCount = %d, LastRefresh = %s\n", 
					GetTickCount() - dwTickCount, rs.GetRecordCount(), 
					m_dtLastRefresh.Format("%Y-%m-%d %H:%M:%S"));

		CPOIUnit poi;
		int nOption;
		poi.m_bDongData = FALSE;
		poi.m_bHasChild = FALSE;

		if(bOnlyChanged)
		{
			if(rs.GetRecordCount() == 0)
				return 2;

			g_bana_log->Print("Free size = %0.0f, count = %d\n", vec.size() * POI_FREE_SPACE_RATE / 100.0, rs.GetRecordCount());

			if(vec.size() * POI_FREE_SPACE_RATE / 100.0 <= rs.GetRecordCount())
				return FALSE;	//POI �������Ͱ�������, ���ڵ�ī��Ʈ�� �� ���� ����̴�. 
		}
		else
		{
			vec.reserve(rs.GetRecordCount());
		}

		map<long, long> mapDaeriDongID;
		FillDaeriDong(&mapDaeriDongID);

		while(!rs.IsEOF())
		{
			if(pMkDb2)
			{
				rs.GetFieldValueS("nUID", poi.m_nID);
				rs.GetFieldValueS("nDongID", poi.m_nDongID);
				rs.GetFieldValueS("sName", poi.m_szName);
				rs.GetFieldValueS("sSubName", poi.m_szSubName);
				rs.GetFieldValueS("nPosX", poi.m_nPosX);
				rs.GetFieldValueS("nPosY", poi.m_nPosY);
				rs.GetFieldValueS("nOption", nOption);
			}
			else
			{
				rs.GetFieldValue("nUID", poi.m_nID);
				rs.GetFieldValue("nDongID", poi.m_nDongID);
				rs.GetFieldValue("sName", poi.m_szName);
				rs.GetFieldValue("sSubName", poi.m_szSubName);
				rs.GetFieldValue("nPosX", poi.m_nPosX);
				rs.GetFieldValue("nPosY", poi.m_nPosY);
				rs.GetFieldValue("nOption", nOption);
			}

			//�븮poi dongid�� ��dongid�� �ٲ��ִ��۾�

			map<long, long>::iterator it = mapDaeriDongID.find(poi.m_nDongID);

			if(it != mapDaeriDongID.end())
				poi.m_nDongID = it->second;
	
			if(m_pPOINew->GetDongPOIFromCache(poi.m_nDongID))
			{
				poi.m_bHasPhone = FALSE;
				poi.m_nClass = (nOption % 10) ? PN_MOBILE : PN_NORMAL;
				poi.m_nPriority = nOption / 10;
				poi.m_szName[29] = 0;
				poi.m_szSubName[28] = 0;
				poi.CheckSubNamePhone();
				poi.SetPOIType(FALSE);

				if(bOnlyChanged)
				{
					CPOIUnit *pPOI = m_pPOINew->GetNormalPOI(poi.m_nID, 0, 0);
					if(pPOI)
					{
						memcpy(pPOI, &poi, sizeof(CPOIUnit));
						g_bana_log->Print("POI UPDATE: %d, %s\n", poi.m_nDongID, poi.m_szName);
						rs.MoveNext();
						continue;
					}
				}

				vec.push_back(poi);

				if(bOnlyChanged)	
					g_bana_log->Print("POI INSERT: %d, %s\n", poi.m_nDongID, poi.m_szName);
			}
			else
			{
				g_bana_log->Print("POI����Ī����: %d, %s\n", poi.m_nDongID, poi.m_szName);
			}

			rs.MoveNext();
		}

		if(pMkDb2)
		{
			pMkDb2->Close();
			delete pMkDb2;
		}

		g_bana_log->Print("INSERT = %dms\n", GetTickCount() - dwTickCount);

		m_dtLastRefresh = parOutDate->GetDate();

		if(m_bUpdatePOINameForUserPOI)
			m_pPOINew->UpdatePOINameForUserPOI();		

		dbt.SetText("POI�� ����ȭ���Դϴ�.");
		m_pPOINew->SortPOIVector(vec);
		g_bana_log->Print("SORT = %dms\n", GetTickCount() - dwTickCount);

		dbt.SetText("POI�� �������� ������Ʈ ���Դϴ�.");
		m_pPOINew->UpdatePOIHasPOI(GetRegionFileName());
		g_bana_log->Print("POIHasPOI = %dms\n", GetTickCount() - dwTickCount);

		dbt.SetText("POI�� �������Դϴ�.");
		m_pPOINew->SavePOI(GetRegionFileName(POI_FILE_NAME));
		g_bana_log->Print("SAVE = %dms\n", GetTickCount() - dwTickCount);

		dbt.SetText("POI�� ĳ�������͸� �������Դϴ�.");
		m_pPOINew->MakePartPOIVector();

		dbt.SetText("POI�� ĳ�������͸� �������Դϴ�.");
		m_pPOINew->SavePartPOI(GetRegionFileName(PART_POI_FILE_NAME));
		return TRUE;
	}
	return FALSE;
}

void CMakePOIData::FillDaeriDong(map<long, long> *pMap)
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_daeri_dong_id");
	cmd.AddParameter(0);

	if(!rs.Execute(&cmd))
		return;

	long nID, nDaeriDongID;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nID", nID);
		rs.GetFieldValue("nDaeriDongID", nDaeriDongID);

		pMap->insert(map<long, long>::value_type(nDaeriDongID, nID));
		rs.MoveNext();
	}
}

BOOL CMakePOIData::MakeAllFromNetwork(BOOL bDongOnly)
{
	CDisplayBarThreadText dbt(m_pDBT, "POI�����͸� �������� ���Դϴ�.", TRUE, 0);
	if(MakeDongDataFromNetwork())
	{
		if(bDongOnly || MakePOIDataFromNetwork())
		{
			if(m_strNewPOIVersion.GetLength() > 0)
			{
				CIniReader ini(GetModuleFullPath() + POI_INI_FILE_NAME);
				ini.setKey(m_strNewPOIVersion, "Version", GetRegionFileName());
				ini.setKey(DateToStringDate(m_dtLastRefresh), "Date", GetRegionFileName());
			}

			m_pPOINew->AddSpecialLog("MakeAllFromNetwork");
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CMakePOIData::MakeAllFromFile(BOOL bDongOnly)
{
	CDisplayBarThreadText dbt(m_pDBT, "POI�����͸� �������� ���Դϴ�.", TRUE, 0);

	if(MakeDongDataFromFile())
	{
		if(bDongOnly || MakePOIDataFromFile())
		{
			m_pPOINew->AddSpecialLog("MakeAllFromFile");
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CMakePOIData::AutoLoad(BOOL bDongOnly)
{
	__try 
	{
		if(!CheckPOIVersion() || !MakeAllFromFile(bDongOnly))
			if(!MakeAllFromNetwork(bDongOnly))
				return FALSE;
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMakePOIData::CheckPOIVersion()
{
	CString strRegionName = m_nSystemCode >= SYSTEM_CODE_THREE ? "������" : m_strCity;

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_poi_version");
	cmd.AddParameter(strRegionName);
	if(rs.Execute(&cmd))
	{
		if(!rs.IsEOF())
		{
			CString strVersion;
			rs.GetFieldValue("sSubValue", strVersion);
			
			CIniReader ini(GetModuleFullPath() + POI_INI_FILE_NAME);
			CString strMyVersion = ini.getKeyValue("Version", strRegionName);

			if(strVersion.GetLength() > 0 && strVersion != strMyVersion)
			{
				m_strNewPOIVersion = strVersion;
				return FALSE;
			}
		}
	}

	return TRUE;
}


void CMakePOIData::SetCity(CString strCity)
{
	m_strCity = strCity;
}

CString CMakePOIData::GetRegionFileName(CString strFileName)
{
	CString strUnderLine;

	if(strFileName.GetLength() > 0)
		strUnderLine = "_";

	//if(m_bCapitalArea)
	if(m_nSystemCode >= SYSTEM_CODE_THREE)
		return "������" + strUnderLine + strFileName;
	else
		return (m_strCity.GetLength() >= 1) ? m_strCity + strUnderLine + strFileName : strFileName;
}

void CMakePOIData::MakeBoundaryInfo(BOOL bFromFile)
{
	CString strCity = m_strCity;

	strCity.Remove('2');
	strCity.Remove('3');
	strCity.Remove('4');

	CPOIBoundary *pHaveSido = NULL;
	CPOIBoundary *pSearchSido = new CPOIBoundary(m_pPOINew);
/*
	if(bFromFile) 
	{
		CPOIBoundary *pHaveSido = new CPOIBoundary(m_pPOINew);
		pHaveSido->Load();
		m_pPOINew->SetHaveSido(pHaveSido);
	}
*/
	//if(m_bCapitalArea)
	if(m_nSystemCode == SYSTEM_CODE_THREE)
		pHaveSido = new CPOIBoundary(m_pPOINew, TRUE, "����", "��õ", "���");
	else
		pHaveSido = new CPOIBoundary(m_pPOINew, TRUE, strCity);

	*pSearchSido = *pHaveSido;

	pHaveSido->Save();
	m_pPOINew->SetHaveSido(pHaveSido);
	m_pPOINew->SetSearchSido(pSearchSido);

	if(!m_pPOINew->SetCenterSido(strCity, "", m_nSystemCode))
	{
		CString strMsg;
		strMsg.Format("POI �߽ɼ��� �����Դϴ�.\n��������Ʈ�� ���ǹٶ��ϴ�.[%s]", strCity);
		MessageBox(AfxGetMainWnd()->GetSafeHwnd(), strMsg, "POI �߽ɼ��� ����", MB_ICONEXCLAMATION);
	}
}

CString CMakePOIData::GetModuleFullPath()
{
	CString strFullPath;
	TCHAR szFullPath[MAX_PATH];
	if (GetModuleFileName(AfxGetInstanceHandle(), szFullPath, _MAX_PATH) > 0)
	{
		int nPos;
		strFullPath = szFullPath;
		if ((nPos = strFullPath.ReverseFind('\\')) != -1)
			strFullPath = strFullPath.Mid(0, ++nPos);
	}

	return strFullPath;
}

BOOL CMakePOIData::StringDateToDate(CString strDate, COleDateTime &dtFileTime)
{
	if(strDate.GetLength() > 0)
	{
		long nYear, nMonth, nDay, nHour, nMin, nSec;
		_stscanf((LPSTR)(LPCTSTR)strDate, _T("%d %d %d %d %d %d"),
			&nYear,&nMonth,&nDay,&nHour,&nMin,&nSec);
		dtFileTime.SetDateTime(nYear, nMonth, nDay, nHour, nMin, nSec);

		if(dtFileTime.GetStatus() != COleDateTime::invalid &&
			dtFileTime.GetStatus() != COleDateTime::null)
		{
			return TRUE;
		}
	}

	return FALSE;
}

CString CMakePOIData::DateToStringDate(COleDateTime dtFileTime)
{
	return dtFileTime.Format("%Y %m %d %H %M %S");
}