#pragma once

#include <string>
#include <QLibrary>
#include "CommonStruct.h"
#define ANT_SDK_SUCCESS		0

#define ANT_SDK_ERR_BASE	1	
#define ANT_SDK_ERR_INVALID_VER (ANT_SDK_ERR_BASE + 0)
#define ANT_SDK_CAN_NOT_LOAD_INTERFACE (ANT_SDK_ERR_BASE + 1)
#define ANT_SDK_COMMAND_FAILED			(ANT_SDK_ERR_BASE + 2)
#define ANT_SDK_COMMAND_NO_RECORD		(ANT_SDK_ERR_BASE + 3)
#define ANT_SDK_CONTAINER_GETDAYLISTFAIL (ANT_SDK_ERR_BASE + 4)



#define ANT_SDK_ERR_MAX		500	

class CANTOfflineFileSDKAdapter
{
public:
	CANTOfflineFileSDKAdapter(void);
	~CANTOfflineFileSDKAdapter(void);

	typedef int (*FUNC_SET_ANTSDK_REALDATACALLBACK) (void * pThis,int nChannel, unsigned int nExtraDataFlag,const char * szPlateNumber, struct tagGps * pGPSItem, const char * szWWANRxLevel,const char * nAlarmType,const char * szTime,unsigned int nFileDuration,unsigned int nCurSecond);

	typedef int (*FUNC_SET_ANTSDK_REALDATACALLBACK2) (void * pThis,int nChannel, unsigned int nExtraDataFlag,const char * szPlateNumber, const char* szExtend, const char * szWWANRxLevel,const char * nAlarmType,const char * szTime,unsigned int nFileDuration,unsigned int nCurSecond);

	typedef int (*FUNC_SET_ANTSDK_CONTAINER_WRITELOG) (void * pThis,const char * szLog,...);

	typedef int (*FUNC_SET_ANTSDK_CONTAINER_MESSAGEBOX) (void * pThis,const char * szMsg);

	typedef int (*FUNC_SET_ANTSDK_CONTAINER_DAYFILELISTDIALOG) (void * pThis,const char * szDayList,char * szResultSelectDay,int * nChannelFlag);


	typedef unsigned int ( * lpfnANTOfflineFileSDK_Init)(int nVersion,
														FUNC_SET_ANTSDK_CONTAINER_WRITELOG pFuncWriteLog,
														FUNC_SET_ANTSDK_CONTAINER_MESSAGEBOX pFuncMessageBox,
														FUNC_SET_ANTSDK_CONTAINER_DAYFILELISTDIALOG pFuncDayFileListDialog);
	typedef unsigned int ( * lpfnANTOfflineFileSDK_Exit)(void);

	typedef unsigned int ( * lpfnANTOfflineFileSDK_Config_SetVideoHWND)(void * pThis,unsigned int * szArrageHWND,int nHWNDCount);

	

	typedef unsigned int ( * lpfnANTOfflineFileSDK_Config_SetCallbackExtraData)(FUNC_SET_ANTSDK_REALDATACALLBACK pFunc);

	typedef unsigned int ( * lpfnANTOfflineFileSDK_Config_SetCallbackExtraData2)(FUNC_SET_ANTSDK_REALDATACALLBACK2 pFunc);

	typedef unsigned int ( * lpfnANTOfflineFileSDK_Control_OpenDir)(const char * szPathDiskDirName,
		BOOL		  bWithChannel_No1,
		BOOL		  bWithChannel_No2,
		BOOL		  bWithChannel_No3,
		BOOL		  bWithChannel_No4,
		BOOL		  bWithChannel_No5,
		BOOL		  bWithChannel_No6,
		BOOL		  bWithChannel_No7,
		BOOL		  bWithChannel_No8); 
	typedef int (*lpfnANTOfflineFileSDK_Control_OpenDirWithDuration)(const char * szPathDiskDirName,
		BOOL		  bWithChannel_No1,
		BOOL		  bWithChannel_No2,
		BOOL		  bWithChannel_No3,
		BOOL		  bWithChannel_No4,
		BOOL		  bWithChannel_No5,
		BOOL		  bWithChannel_No6,
		BOOL		  bWithChannel_No7,
		BOOL		  bWithChannel_No8,
		int		  *pnFileGroupCount,
		int		  **pnEndTime,
		int       **pnStartTime,
		int       **pnType); 
	typedef unsigned int ( * lpfnANTOfflineFileSDK_Control_OpenSDCard)(const char * szPathDiskDirName,
		BOOL		  bWithChannel_No1,
		BOOL		  bWithChannel_No2,
		BOOL		  bWithChannel_No3,
		BOOL		  bWithChannel_No4,
		BOOL		  bWithChannel_No5,
		BOOL		  bWithChannel_No6,
		BOOL		  bWithChannel_No7,
		BOOL		  bWithChannel_No8); 
	typedef int (* lpfnANTOfflineFileSDK_Control_OpenSDCardWithDuration)(const char * szPathDiskDirName,
		BOOL		  bWithChannel_No1,
		BOOL		  bWithChannel_No2,
		BOOL		  bWithChannel_No3,
		BOOL		  bWithChannel_No4,
		BOOL		  bWithChannel_No5,
		BOOL		  bWithChannel_No6,
		BOOL		  bWithChannel_No7,
		BOOL		  bWithChannel_No8,
		int		  *pnFileGroupCount,
		int		  **pnEndTime,
		int       **pnStartTime,
		int       **pnType); 

	typedef int (* lpfnANTOfflineFileSDK_Control_OpenGroup)(char * szFile[],int nChannelFlag,int nCount);
	typedef unsigned int ( * lpfnANTOfflineFileSDK_Control_OpenFile)(const char * szPathFileName,unsigned int nChannelNumber);

	typedef unsigned int ( * lpfnANTOfflineFileSDK_Control_PlayAllChannel)();

	typedef unsigned int ( * lpfnANTOfflineFileSDK_Control_PauseAllChannel)();

	typedef unsigned int ( * lpfnANTOfflineFileSDK_Control_StopAllChannel)();

	//nSpeed 1/16 1/8 1/4 1/2 1 2 4 8 16
	typedef unsigned int ( * lpfnANTOfflineFileSDK_Control_SetSpeedAllChannel)(int nIndex);

	typedef unsigned int ( * lpfnANTOfflineFileSDK_Control_SeekAllChannel)(unsigned int nOffsetSecond);

	typedef unsigned int ( * lpfnANTOfflineFileSDK_Control_PlayTheChannel)(int nChannelNumber);

	typedef unsigned int ( * lpfnANTOfflineFileSDK_Control_PauseTheChannel)(int nChannelNumber);

	typedef unsigned int ( * lpfnANTOfflineFileSDK_Control_StopTheChannel)(int nChannelNumber);

	typedef unsigned int ( * lpfnANTOfflineFileSDK_Control_SeekTheChannel)(int nChannelNumber,unsigned int nOffsetSecond);

	typedef unsigned int ( * lpfnANTOfflineFileSDK_Control_SetSpeedTheChannel)(int nIndex,int nChannelNumber);
    
	typedef int (* lpfnANTOfflineFileSDK_Control_GetProgress)(int nChannelNumber,long * lTotal,long * lCur);
	
	typedef int (* lpfnANTOfflineFileSDK_Control_GetFileInfo)(int nChannelNumber,long* lStart, long * lEnd,long * lTotal);
	
    typedef int (* lpfnANTOfflineFileSDK_Control_SetSound) (int nChannelNumber,int nFile,bool bOpen);

	typedef int (* lpfnANTOfflineFileSDK_Control_SetVolume)(int nChannelNumber,int nVolume);
	BOOL LoadInterface(QLibrary* pdll,const char * szModuleFileName);

	lpfnANTOfflineFileSDK_Init  m_pfnANTOfflineFileSDK_Init;

	lpfnANTOfflineFileSDK_Exit  m_pfnANTOfflineFileSDK_Exit;

	lpfnANTOfflineFileSDK_Config_SetVideoHWND m_pfnANTOfflineFileSDK_Config_SetVideoHWND;

	lpfnANTOfflineFileSDK_Config_SetCallbackExtraData m_pfnANTOfflineFileSDK_Config_SetCallbackExtraData;

	lpfnANTOfflineFileSDK_Config_SetCallbackExtraData2 m_pfnANTOfflineFileSDK_Config_SetCallbackExtraData2;

	lpfnANTOfflineFileSDK_Control_OpenDir m_pfnANTOfflineFileSDK_Control_OpenDir; 

	lpfnANTOfflineFileSDK_Control_OpenDirWithDuration m_pfnANTOfflineFileSDK_Control_OpenDirWithDuration;

	lpfnANTOfflineFileSDK_Control_OpenSDCard m_pfnANTOfflineFileSDK_Control_OpenSDCard; 

	lpfnANTOfflineFileSDK_Control_OpenSDCardWithDuration m_pfnANTOfflineFileSDK_Control_OpenSDCardWithDuration;

	lpfnANTOfflineFileSDK_Control_OpenGroup m_pfnANTOfflineFileSDK_Control_OpenGroup;

	lpfnANTOfflineFileSDK_Control_OpenFile m_pfnANTOfflineFileSDK_Control_OpenFile;

	lpfnANTOfflineFileSDK_Control_PlayAllChannel m_pfnANTOfflineFileSDK_Control_PlayAllChannel;

	lpfnANTOfflineFileSDK_Control_PauseAllChannel m_pfnANTOfflineFileSDK_Control_PauseAllChannel;

	lpfnANTOfflineFileSDK_Control_StopAllChannel m_pfnANTOfflineFileSDK_Control_StopAllChannel;

	//nSpeed 1/16 1/8 1/4 1/2 1 2 4 8 16
	lpfnANTOfflineFileSDK_Control_SetSpeedAllChannel m_pfnANTOfflineFileSDK_Control_SetSpeedAllChannel;

	lpfnANTOfflineFileSDK_Control_SeekAllChannel m_pfnANTOfflineFileSDK_Control_SeekAllChannel;

	lpfnANTOfflineFileSDK_Control_PlayTheChannel m_pfnANTOfflineFileSDK_Control_PlayTheChannel;

	lpfnANTOfflineFileSDK_Control_PauseTheChannel m_pfnANTOfflineFileSDK_Control_PauseTheChannel;

	lpfnANTOfflineFileSDK_Control_StopTheChannel m_pfnANTOfflineFileSDK_Control_StopTheChannel;

	lpfnANTOfflineFileSDK_Control_SeekTheChannel m_pfnANTOfflineFileSDK_Control_SeekTheChannel;

	lpfnANTOfflineFileSDK_Control_SetSpeedTheChannel m_pfnANTOfflineFileSDK_Control_SetSpeedTheChannel;

	lpfnANTOfflineFileSDK_Control_GetProgress   m_pfnANTOfflineFileSDK_Control_GetProgress;

	lpfnANTOfflineFileSDK_Control_GetFileInfo   m_pfnANTOfflineFileSDK_Control_GetFileInfo;

	lpfnANTOfflineFileSDK_Control_SetSound      m_pfnANTOfflineFileSDK_Control_SetSound;

	lpfnANTOfflineFileSDK_Control_SetVolume     m_pfnANTOfflineFileSDK_Control_SetVolume;
public:


	int ANTOfflineFileSDK_Init(int nVersion,
								FUNC_SET_ANTSDK_CONTAINER_WRITELOG pFuncWriteLog,
								FUNC_SET_ANTSDK_CONTAINER_MESSAGEBOX pFuncMessageBox,
								FUNC_SET_ANTSDK_CONTAINER_DAYFILELISTDIALOG pFuncDayFileListDialog);

	int ANTOfflineFileSDK_Exit(void);

	int ANTOfflineFileSDK_Config_SetVideoHWND(void * pThis,unsigned int * szArrageHWND,int nHWNDCount);

	int ANTOfflineFileSDK_Config_SetCallbackExtraData(FUNC_SET_ANTSDK_REALDATACALLBACK pFunc);

	int ANTOfflineFileSDK_Config_SetCallbackExtraData2(FUNC_SET_ANTSDK_REALDATACALLBACK2 pFunc);

	int ANTOfflineFileSDK_Control_OpenDir(const char * szPathDiskDirName,
		BOOL		  bWithChannel_No1,
		BOOL		  bWithChannel_No2,
		BOOL		  bWithChannel_No3,
		BOOL		  bWithChannel_No4,
		BOOL		  bWithChannel_No5,
		BOOL		  bWithChannel_No6,
		BOOL		  bWithChannel_No7,
		BOOL		  bWithChannel_No8); 

	int ANTOfflineFileSDK_Control_OpenDirWithDuration(const char * szPathDiskDirName,
		BOOL		  bWithChannel_No1,
		BOOL		  bWithChannel_No2,
		BOOL		  bWithChannel_No3,
		BOOL		  bWithChannel_No4,
		BOOL		  bWithChannel_No5,
		BOOL		  bWithChannel_No6,
		BOOL		  bWithChannel_No7,
		BOOL		  bWithChannel_No8,
		int		  *pnFileGroupCount,
		int		  **pnEndTime,
		int       **pnStartTime,
		int       **pnType); 

	int ANTOfflineFileSDK_Control_OpenSDCard(const char * szPathDiskDirName,
		BOOL		  bWithChannel_No1,
		BOOL		  bWithChannel_No2,
		BOOL		  bWithChannel_No3,
		BOOL		  bWithChannel_No4,
		BOOL		  bWithChannel_No5,
		BOOL		  bWithChannel_No6,
		BOOL		  bWithChannel_No7,
		BOOL		  bWithChannel_No8); 
	int ANTOfflineFileSDK_Control_OpenSDCard_WithDuration(const char * szPathDiskDirName,
		BOOL		  bWithChannel_No1,
		BOOL		  bWithChannel_No2,
		BOOL		  bWithChannel_No3,
		BOOL		  bWithChannel_No4,
		BOOL		  bWithChannel_No5,
		BOOL		  bWithChannel_No6,
		BOOL		  bWithChannel_No7,
		BOOL		  bWithChannel_No8,
		int		  *pnFileGroupCount,
		int		  **pnEndTime,
		int       **pnStartTime,
		int       **pnType); 
    int ANTOfflineFileSDK_Control_OpenGroupFile(char * szFile[],int nChannelFlag,int nCount);
	int ANTOfflineFileSDK_Control_OpenFile(const char * szPathFileName,unsigned int nChannelNumber);

	int ANTOfflineFileSDK_Control_PlayAllChannel();

	int ANTOfflineFileSDK_Control_PauseAllChannel();

	int ANTOfflineFileSDK_Control_StopAllChannel();

	//nSpeed 1/16 1/8 1/4 1/2 1 2 4 8 16
	int ANTOfflineFileSDK_Control_SetSpeedAllChannel(int nIndex);

	int ANTOfflineFileSDK_Control_SeekAllChannel(unsigned int nOffsetSecond);

	int ANTOfflineFileSDK_Control_PlayTheChannel(int nChannelNumber);

	int ANTOfflineFileSDK_Control_PauseTheChannel(int nChannelNumber);

	int ANTOfflineFileSDK_Control_StopTheChannel(int nChannelNumber);

	int ANTOfflineFileSDK_Control_SeekTheChannel(int nChannelNumber,unsigned int nOffsetSecond);

	int ANTOfflineFileSDK_Control_SetSpeedTheChannel(int nIndex,int nChannelNumber);

	int ANTOfflineFileSDK_Control_GetProgress(int nChannelNumber,long * lTotal,long * lCur);

	int ANTOfflineFileSDK_Control_GetFileInfo(int nChannelNumber,long* lStart, long * lEnd,long * lTotal);

	int ANTOfflineFileSDK_Control_SetSound(int nChannelNumber,int nFile,bool bOpen);

	int ANTOfflineFileSDK_Control_SetVolume(int nChannelNumber,int nVolume);
	std::string & GetType() 
	{
		return m_strType;
	}
	std::string m_strType;
};
