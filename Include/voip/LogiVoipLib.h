
#define MM_TEXT_DATA					WM_USER+801
#define MM_VOICE_DATA					WM_USER+802

#ifndef _Logi_Voip_Lib_h_
#define _Logi_Voip_Lib_h_

#ifdef _LOGIVOIPLIB_
#define Dllport   __declspec( dllexport )
#else
#define Dllport   extern __declspec( dllimport )
#endif

Dllport void InitializeVoip(CWnd* pWnd);
Dllport void DeinitializeVoip();
Dllport void CreateDefaultVTMSGInfo();
Dllport void Connect(CString sAddress,UINT uPort,CString sLoginInfo);
Dllport BOOL IsConnedted();
Dllport int MakeDirectCall(CString sTo,void* VTMSGInfo,BOOL bForceInvite,CString* pError);
Dllport int MakeGroupCall(CString sTo,void* VTMSGInfo,BOOL bForceInvite,CString* pError);
Dllport int MakeWalkieTalkieGroup(CString sTo,void* VTMSGInfo,BOOL bCompanyWT,CString* pError);
Dllport int MakeInvite(CString sTo,BOOL bInviteForce,CString* pError);
Dllport int MakeHangUp(CString* pError);
Dllport int AcceptInviteCall(CString* pError);
Dllport int ReleaseWakieTalkie(CString* pError);
Dllport int PushWakieTalkie(CString* pError);

Dllport void ChangeVTMSGInfo_VTMsgState(UINT uVTMsgState);
Dllport void ChangeVTMSGInfo_CompanyWT(BOOL bCompanyWT);
Dllport void ChangeVTMSGInfo_WaveST(BOOL bWaveST);
Dllport void ChangeVTMSGInfo_GroupType(int nGroupType);
Dllport void ChangeVTMSGInfo_Channel(const char* sChannel);
Dllport void ChangeVTMSGInfo_CallState(int nCallState);


Dllport BOOL	GetCurIsCaller();
Dllport int		GetCurGroupType();
Dllport BOOL	GetCurCompanyWT();
Dllport BOOL	GetCurWaveST();
Dllport CString GetCurChannel();
Dllport int		GetCurCallStae();



Dllport void* CreatePlaySound(CWnd* pWnd);
Dllport void* CreateCaller(CWnd* pWnd,void* Play,void* Record );
Dllport void* CreateRecordSound(CWnd* pWnd);
Dllport void Connect(void* Caller,CString sAddress,UINT uPort,CString sLoginInfo);
Dllport void Destory(void* play,void* record, void* caller);

Dllport void RecordSoundStart();
Dllport void RecordSoundStop();

Dllport void* CreateVTMSGInfo(UINT uVTMsgState,BOOL bCompanyWT,BOOL bWaveST, CString sChannel,int nGroupType,BOOL bCaller);
Dllport void DestroyVTMSGInfo(void* p);
Dllport void SetCurVTMsgInfo(void* p);
Dllport void* GetCurVTMsgInfo();

Dllport void ChangeVTMSGInfo_VTMsgState(void* p,UINT uVTMsgState);
Dllport void ChangeVTMSGInfo_CompanyWT(void* p,BOOL bCompanyWT);
Dllport void ChangeVTMSGInfo_WaveST(void* p,BOOL bWaveST);
Dllport void ChangeVTMSGInfo_GroupType(void* p,int nGroupType);
Dllport void ChangeVTMSGInfo_Channel(void* p,const char* sChannel);
Dllport void ChangeVTMSGInfo_CallState(void* p,int nCallState);

Dllport int MakeDirectCall(CString sTo,void* play,void* record,void* caller,void* VTMSGInfo,BOOL bForceInvite,CString* pError);
Dllport int MakeGroupCall(CString sTo,void* play,void* record,void* caller,void* VTMSGInfo,BOOL bForceInvite,CString* pError);
Dllport int MakeWalkieTalkieGroup(CString sTo,void* play,void* record,void* caller,void* VTMSGInfo,BOOL bCompanyWT,CString* pError);
Dllport int MakeInvite(CString sTo,void* caller,void* p,BOOL bInviteForce,CString* pError);
Dllport int MakeHangUp(void* play,void* record,void* caller,void* p,CString* pError);
#endif