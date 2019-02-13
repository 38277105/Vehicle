#include "ANTOfflineFileSDKAdapter.h"
#include "FramelessDialog.h"

CANTOfflineFileSDKAdapter::CANTOfflineFileSDKAdapter(void)
{
}

CANTOfflineFileSDKAdapter::~CANTOfflineFileSDKAdapter(void)
{
}

BOOL CANTOfflineFileSDKAdapter::LoadInterface(QLibrary* pdll,const char * szModuleFileName)
{
    if (!pdll)
    {
        return FALSE;
    }
    std::string strModuleFileName = szModuleFileName;
    if(strModuleFileName.find("RM",0) != -1)
    {
        m_strType = "RM";
    }
    else if(strModuleFileName.find("WKP",0) != -1)
    {
        m_strType = "WKP";
    }
    /*else if(strModuleFileName.find("SC",0) != -1)
    {
        m_strType = "SC";
    }
    if(strModuleFileName.find("JN",0) != -1)
    {
        m_strType = "JN";
    }*/
    m_pfnANTOfflineFileSDK_Init = (lpfnANTOfflineFileSDK_Init)pdll->resolve("ANTOfflineFileSDK_Init");
    if (!m_pfnANTOfflineFileSDK_Init)
    {
        SHOW_ERROR_BOX("initFuncFaild");

        return FALSE;
    }

    m_pfnANTOfflineFileSDK_Exit = (lpfnANTOfflineFileSDK_Exit)pdll->resolve("ANTOfflineFileSDK_Exit");
    if(!m_pfnANTOfflineFileSDK_Exit)
    {
        SHOW_ERROR_BOX("exitFuncFaild");

        return FALSE;
    }

    m_pfnANTOfflineFileSDK_Config_SetVideoHWND = (lpfnANTOfflineFileSDK_Config_SetVideoHWND)pdll->resolve("ANTOfflineFileSDK_Config_SetVideoHWND");
    if(!m_pfnANTOfflineFileSDK_Config_SetVideoHWND)
    {
        SHOW_ERROR_BOX("updateFaild");

        return FALSE;
    }

    m_pfnANTOfflineFileSDK_Config_SetCallbackExtraData = (lpfnANTOfflineFileSDK_Config_SetCallbackExtraData)pdll->resolve("ANTOfflineFileSDK_Config_SetCallbackExtraData");
    if(!m_pfnANTOfflineFileSDK_Config_SetCallbackExtraData)
    {
        SHOW_ERROR_BOX("setCallbackFaild");

        return FALSE;
    }

    m_pfnANTOfflineFileSDK_Config_SetCallbackExtraData2 = (lpfnANTOfflineFileSDK_Config_SetCallbackExtraData2)pdll->resolve("ANTOfflineFileSDK_Config_SetCallbackExtraData2");
    if(!m_pfnANTOfflineFileSDK_Config_SetCallbackExtraData2)
    {
        SHOW_ERROR_BOX("setCallbackFaild");

        return FALSE;
    }


    m_pfnANTOfflineFileSDK_Control_OpenDir = (lpfnANTOfflineFileSDK_Control_OpenDir)pdll->resolve("ANTOfflineFileSDK_Control_OpenDir");
    if(!m_pfnANTOfflineFileSDK_Control_OpenDir)
    {
        SHOW_ERROR_BOX("openDirFailed");

        return FALSE;
    }

    m_pfnANTOfflineFileSDK_Control_OpenDirWithDuration = (lpfnANTOfflineFileSDK_Control_OpenDirWithDuration)pdll->resolve("ANTOfflineFileSDK_Control_OpenDir_WithDuration");
    if (!m_pfnANTOfflineFileSDK_Control_OpenDirWithDuration)
    {
        SHOW_ERROR_BOX("openDirFailed");

        return FALSE;
    }
    m_pfnANTOfflineFileSDK_Control_OpenSDCard = (lpfnANTOfflineFileSDK_Control_OpenDir)pdll->resolve("ANTOfflineFileSDK_Control_OpenSDCard");
    if(!m_pfnANTOfflineFileSDK_Control_OpenSDCard)
    {
        SHOW_ERROR_BOX("openSDFailed");

        return FALSE;
    }

    m_pfnANTOfflineFileSDK_Control_OpenSDCardWithDuration = (lpfnANTOfflineFileSDK_Control_OpenSDCardWithDuration)pdll->resolve("ANTOfflineFileSDK_Control_OpenSDCard_WithDuration");
    if (!m_pfnANTOfflineFileSDK_Control_OpenSDCardWithDuration)
    {
        SHOW_ERROR_BOX("openSDFailed");

        return FALSE;
    }
    m_pfnANTOfflineFileSDK_Control_OpenGroup = (lpfnANTOfflineFileSDK_Control_OpenGroup)pdll->resolve("ANTOfflineFileSDK_Control_OpenGroupFile");
    if (!m_pfnANTOfflineFileSDK_Control_OpenGroup)
    {
        SHOW_ERROR_BOX("openSDFailed");

        return FALSE;
    }

    m_pfnANTOfflineFileSDK_Control_OpenFile = (lpfnANTOfflineFileSDK_Control_OpenFile)pdll->resolve("ANTOfflineFileSDK_Control_OpenFile");
    if(!m_pfnANTOfflineFileSDK_Control_OpenFile)
    {
        SHOW_ERROR_BOX("openFileFailed");

        return FALSE;
    }


    m_pfnANTOfflineFileSDK_Control_PlayAllChannel = (lpfnANTOfflineFileSDK_Control_PlayAllChannel)pdll->resolve("ANTOfflineFileSDK_Control_PlayAllChannel");
    if(!m_pfnANTOfflineFileSDK_Control_PlayAllChannel)
    {
        SHOW_ERROR_BOX("playFailed");

        return FALSE;
    }


    m_pfnANTOfflineFileSDK_Control_PauseAllChannel = (lpfnANTOfflineFileSDK_Control_PauseAllChannel)pdll->resolve("ANTOfflineFileSDK_Control_PauseAllChannel");
    if(!m_pfnANTOfflineFileSDK_Control_PauseAllChannel)
    {
        SHOW_ERROR_BOX("pauseFailed");

        return FALSE;
    }


    m_pfnANTOfflineFileSDK_Control_StopAllChannel = (lpfnANTOfflineFileSDK_Control_StopAllChannel)pdll->resolve("ANTOfflineFileSDK_Control_StopAllChannel");
    if(!m_pfnANTOfflineFileSDK_Control_StopAllChannel)
    {
        SHOW_ERROR_BOX("stopFailed");

        return FALSE;
    }


    m_pfnANTOfflineFileSDK_Control_SetSpeedAllChannel = (lpfnANTOfflineFileSDK_Control_SetSpeedAllChannel)pdll->resolve("ANTOfflineFileSDK_Control_SetSpeedAllChannel");
    if(!m_pfnANTOfflineFileSDK_Control_SetSpeedAllChannel)
    {
        SHOW_ERROR_BOX("speedFailed");

        return FALSE;
    }


    m_pfnANTOfflineFileSDK_Control_SeekAllChannel = (lpfnANTOfflineFileSDK_Control_SeekAllChannel)pdll->resolve("ANTOfflineFileSDK_Control_SeekAllChannel");
    if(!m_pfnANTOfflineFileSDK_Control_SeekAllChannel)
    {
        SHOW_ERROR_BOX("locFailed");

        return FALSE;
    }

    m_pfnANTOfflineFileSDK_Control_PlayTheChannel = (lpfnANTOfflineFileSDK_Control_PlayTheChannel)pdll->resolve("ANTOfflineFileSDK_Control_PlayTheChannel");
    if(!m_pfnANTOfflineFileSDK_Control_PlayTheChannel)
    {
        SHOW_ERROR_BOX("playFailed");

        return FALSE;
    }


    m_pfnANTOfflineFileSDK_Control_PauseTheChannel = (lpfnANTOfflineFileSDK_Control_PauseTheChannel)pdll->resolve("ANTOfflineFileSDK_Control_PauseTheChannel");
    if(!m_pfnANTOfflineFileSDK_Control_PauseTheChannel)
    {
        SHOW_ERROR_BOX("pauseFailed");

        return FALSE;
    }

    m_pfnANTOfflineFileSDK_Control_StopTheChannel = (lpfnANTOfflineFileSDK_Control_StopTheChannel)pdll->resolve("ANTOfflineFileSDK_Control_StopTheChannel");
    if(!m_pfnANTOfflineFileSDK_Control_StopTheChannel)
    {
        SHOW_ERROR_BOX("stopFailed");

        return FALSE;
    }

    m_pfnANTOfflineFileSDK_Control_SeekTheChannel = (lpfnANTOfflineFileSDK_Control_SeekTheChannel)pdll->resolve("ANTOfflineFileSDK_Control_SeekTheChannel");
    if(!m_pfnANTOfflineFileSDK_Control_SeekTheChannel)
    {
        SHOW_ERROR_BOX("locFailed");

        return FALSE;
    }

    m_pfnANTOfflineFileSDK_Control_SetSpeedTheChannel = (lpfnANTOfflineFileSDK_Control_SetSpeedTheChannel)pdll->resolve("ANTOfflineFileSDK_Control_SetSpeedTheChannel");
    if(!m_pfnANTOfflineFileSDK_Control_SetSpeedTheChannel)
    {
        SHOW_ERROR_BOX("speedFailed");

        return FALSE;
    }

    m_pfnANTOfflineFileSDK_Control_GetProgress = (lpfnANTOfflineFileSDK_Control_GetProgress)pdll->resolve("ANTOfflineFileSDK_Control_GetProcess");
    if (!m_pfnANTOfflineFileSDK_Control_GetProgress)
    {
        SHOW_ERROR_BOX("progressFailed");

        return FALSE;
    }

    m_pfnANTOfflineFileSDK_Control_GetFileInfo = (lpfnANTOfflineFileSDK_Control_GetFileInfo)pdll->resolve("ANTOfflineFileSDK_Control_GetFileTimeInfo");
    if (!m_pfnANTOfflineFileSDK_Control_GetFileInfo)
    {
        SHOW_ERROR_BOX("videoInfoFailed");

        return FALSE;
    }
    m_pfnANTOfflineFileSDK_Control_SetSound = (lpfnANTOfflineFileSDK_Control_SetSound)pdll->resolve("ANTOfflineFileSDK_Control_SetSound");
    if (!m_pfnANTOfflineFileSDK_Control_SetSound)
    {
        SHOW_ERROR_BOX("soundFailed");

        return FALSE;
    }
    m_pfnANTOfflineFileSDK_Control_SetVolume = (lpfnANTOfflineFileSDK_Control_SetVolume)pdll->resolve("ANTOfflineFileSDK_Control_SetVolume");
    if (!m_pfnANTOfflineFileSDK_Control_SetVolume)
    {
        SHOW_ERROR_BOX("volumeFailed");

        return FALSE;
    }
    return TRUE;
}

int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Init(int nVersion,
                                                      FUNC_SET_ANTSDK_CONTAINER_WRITELOG pFuncWriteLog,
                                                      FUNC_SET_ANTSDK_CONTAINER_MESSAGEBOX pFuncMessageBox,
                                                      FUNC_SET_ANTSDK_CONTAINER_DAYFILELISTDIALOG pFuncDayFileListDialog)
{
    if(m_pfnANTOfflineFileSDK_Init == NULL)
        return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
    return (*m_pfnANTOfflineFileSDK_Init)(nVersion,pFuncWriteLog,pFuncMessageBox,pFuncDayFileListDialog);
}

int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Exit(void)
{
    if(m_pfnANTOfflineFileSDK_Exit == NULL)
        return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
    return (*m_pfnANTOfflineFileSDK_Exit)();
}

int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Config_SetVideoHWND(void * pThis,unsigned int * szArrageHWND,int nHWNDCount)
{
    if(m_pfnANTOfflineFileSDK_Config_SetVideoHWND == NULL)
        return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
    return (*m_pfnANTOfflineFileSDK_Config_SetVideoHWND)(pThis,szArrageHWND,nHWNDCount);
}

int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Config_SetCallbackExtraData(FUNC_SET_ANTSDK_REALDATACALLBACK pFunc)
{
    if(m_pfnANTOfflineFileSDK_Config_SetCallbackExtraData == NULL)
        return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
    return (*m_pfnANTOfflineFileSDK_Config_SetCallbackExtraData)(pFunc);
}

int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Config_SetCallbackExtraData2(FUNC_SET_ANTSDK_REALDATACALLBACK2 pFunc)
{
    if(m_pfnANTOfflineFileSDK_Config_SetCallbackExtraData2 == NULL)
        return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
    return (*m_pfnANTOfflineFileSDK_Config_SetCallbackExtraData2)(pFunc);
}

int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Control_OpenDir(const char * szPathDiskDirName,
                                      BOOL		  bWithChannel_No1,
                                      BOOL		  bWithChannel_No2,
                                      BOOL		  bWithChannel_No3,
                                      BOOL		  bWithChannel_No4,
                                      BOOL		  bWithChannel_No5,
                                      BOOL		  bWithChannel_No6,
                                      BOOL		  bWithChannel_No7,
                                      BOOL		  bWithChannel_No8)
{
    if(m_pfnANTOfflineFileSDK_Control_OpenDir == NULL)
        return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
    return (*m_pfnANTOfflineFileSDK_Control_OpenDir)(szPathDiskDirName,
                                                    bWithChannel_No1,
                                                    bWithChannel_No2,
                                                    bWithChannel_No3,
                                                    bWithChannel_No4,
                                                    bWithChannel_No5,
                                                    bWithChannel_No6,
                                                    bWithChannel_No7,
                                                    bWithChannel_No8);
}

int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Control_OpenDirWithDuration(const char * szPathDiskDirName,
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
																			 int       **pnType)
{
	if (!m_pfnANTOfflineFileSDK_Control_OpenDirWithDuration)
	   return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
	return m_pfnANTOfflineFileSDK_Control_OpenDirWithDuration(szPathDiskDirName,
																bWithChannel_No1,
																bWithChannel_No2,
																bWithChannel_No3,
																bWithChannel_No4,
																bWithChannel_No5,
																bWithChannel_No6,
																bWithChannel_No7,
																bWithChannel_No8,
																pnFileGroupCount,
																pnEndTime,
																pnStartTime,
																pnType);
}

int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Control_OpenSDCard(const char * szPathDiskDirName,
                                                                    BOOL		  bWithChannel_No1,
                                                                    BOOL		  bWithChannel_No2,
                                                                    BOOL		  bWithChannel_No3,
                                                                    BOOL		  bWithChannel_No4,
                                                                    BOOL		  bWithChannel_No5,
                                                                    BOOL		  bWithChannel_No6,
                                                                    BOOL		  bWithChannel_No7,
                                                                    BOOL		  bWithChannel_No8)
{
    if(m_pfnANTOfflineFileSDK_Control_OpenSDCard == NULL)
        return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
    return (*m_pfnANTOfflineFileSDK_Control_OpenSDCard)(szPathDiskDirName,
        bWithChannel_No1,
        bWithChannel_No2,
        bWithChannel_No3,
        bWithChannel_No4,
        bWithChannel_No5,
        bWithChannel_No6,
        bWithChannel_No7,
        bWithChannel_No8);
}
int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Control_OpenSDCard_WithDuration(const char * szPathDiskDirName,
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
																				 int       **pnType)
{
	if (NULL == m_pfnANTOfflineFileSDK_Control_OpenSDCardWithDuration)
	{
		return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
	}
	return (*m_pfnANTOfflineFileSDK_Control_OpenSDCardWithDuration)(szPathDiskDirName,
		bWithChannel_No1,
		bWithChannel_No2,
		bWithChannel_No3,
		bWithChannel_No4,
		bWithChannel_No5,
		bWithChannel_No6,
		bWithChannel_No7,
		bWithChannel_No8,
		pnFileGroupCount,
		pnEndTime,
		pnStartTime,
		pnType); 
}
int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Control_OpenGroupFile(char * szFile[],int nChannelFlag,int nCount)
{
    if (NULL == m_pfnANTOfflineFileSDK_Control_OpenGroup)
    {
        return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
    }
    return(*m_pfnANTOfflineFileSDK_Control_OpenGroup)(szFile,nChannelFlag,nCount);
}
int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Control_OpenFile(const char * szPathFileName,unsigned int nChannelNumber)
{
    if(m_pfnANTOfflineFileSDK_Control_OpenFile == NULL)
        return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
    return (*m_pfnANTOfflineFileSDK_Control_OpenFile)(szPathFileName,nChannelNumber);
}

int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Control_PlayAllChannel()
{
    if(m_pfnANTOfflineFileSDK_Control_PlayAllChannel == NULL)
        return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
    return (*m_pfnANTOfflineFileSDK_Control_PlayAllChannel)();
}

int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Control_PauseAllChannel()
{
    if(m_pfnANTOfflineFileSDK_Control_PauseAllChannel == NULL)
        return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
    return (*m_pfnANTOfflineFileSDK_Control_PauseAllChannel)();
}

int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Control_StopAllChannel()
{
    if(m_pfnANTOfflineFileSDK_Control_StopAllChannel == NULL)
        return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
    return (*m_pfnANTOfflineFileSDK_Control_StopAllChannel)();
}

//nSpeed 1/16 1/8 1/4 1/2 1 2 4 8 16
int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Control_SetSpeedAllChannel(int nIndex)
{
    if(m_pfnANTOfflineFileSDK_Control_SetSpeedAllChannel == NULL)
        return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
    return (*m_pfnANTOfflineFileSDK_Control_SetSpeedAllChannel)(nIndex);
}

int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Control_SeekAllChannel(unsigned int nOffsetSecond)
{
    if(m_pfnANTOfflineFileSDK_Control_SeekAllChannel == NULL)
        return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
    return (*m_pfnANTOfflineFileSDK_Control_SeekAllChannel)(nOffsetSecond);
}

int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Control_PlayTheChannel(int nChannelNumber)
{
    if(m_pfnANTOfflineFileSDK_Control_PlayTheChannel == NULL)
        return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
    return (*m_pfnANTOfflineFileSDK_Control_PlayTheChannel)(nChannelNumber);
}

int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Control_PauseTheChannel(int nChannelNumber)
{
    if(m_pfnANTOfflineFileSDK_Control_PauseTheChannel == NULL)
        return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
    return (*m_pfnANTOfflineFileSDK_Control_PauseTheChannel)(nChannelNumber);
}

int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Control_StopTheChannel(int nChannelNumber)
{
    if(m_pfnANTOfflineFileSDK_Control_StopTheChannel == NULL)
        return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
    return (*m_pfnANTOfflineFileSDK_Control_StopTheChannel)(nChannelNumber);
}

int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Control_SeekTheChannel(int nChannelNumber,unsigned int nOffsetSecond)
{
    if(m_pfnANTOfflineFileSDK_Control_SeekTheChannel == NULL)
        return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
    return (*m_pfnANTOfflineFileSDK_Control_SeekTheChannel)(nChannelNumber,nOffsetSecond);
}

int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Control_SetSpeedTheChannel(int nIndex,int nChannelNumber)
{
    if(m_pfnANTOfflineFileSDK_Control_SetSpeedTheChannel == NULL)
        return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
    return (*m_pfnANTOfflineFileSDK_Control_SetSpeedTheChannel)(nIndex,nChannelNumber);
}
int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Control_GetProgress(int nChannelNumber,long * lTotal,long * lCur)
{
    if (NULL == m_pfnANTOfflineFileSDK_Control_GetProgress)
    {
        return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
    }
    return (*m_pfnANTOfflineFileSDK_Control_GetProgress)(nChannelNumber,lTotal,lCur);
}
int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Control_GetFileInfo(int nChannelNumber,long* lStart, long * lEnd,long * lTotal)
{
    if (NULL == m_pfnANTOfflineFileSDK_Control_GetFileInfo)
    {
        return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
    }
    return(*m_pfnANTOfflineFileSDK_Control_GetFileInfo)(nChannelNumber,lStart,lEnd,lTotal);
}
int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Control_SetSound(int nChannelNumber,int nFile,bool bOpen)
{
    if (NULL == m_pfnANTOfflineFileSDK_Control_SetSound)
    {
        return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
    }
    return (*m_pfnANTOfflineFileSDK_Control_SetSound)(nChannelNumber,nFile,bOpen);
}
int CANTOfflineFileSDKAdapter::ANTOfflineFileSDK_Control_SetVolume(int nChannelNumber,int nVolume)
{
    if (NULL == m_pfnANTOfflineFileSDK_Control_SetVolume)
    {
        return ANT_SDK_CAN_NOT_LOAD_INTERFACE;
    }
    return (*m_pfnANTOfflineFileSDK_Control_SetVolume)(nChannelNumber,nVolume);
}
