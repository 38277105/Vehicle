//#include "writeLog.h"

#ifndef COMMONSTRUCTHEADER
#define COMMONSTRUCTHEADER
#include <QString>
#include <string>
#include <vector>
#include <map>
#include <QBrush>
#define INVALIDWNDINDEX -1
#define INVALID         -1
#define LTWNDINDEX 1
#define RTWNDINDEX 2
#define LBWNDINDEX 3
#define RBWNDINDEX 4
#define SDKINDEX 1
#define FILEINDEX 0
#define DIRINDEX 2
#define MAXCHANNEL 4
#define NOTPLAY    -1
#define PLAYING    0
#define PLAYED     1
#define PLAY       1
#define STOP       0
#define ANYINDEX   -1
#define SHOWGPS    1
#define SHOWWWANRx 2
#define SHOWALARM  4
#define SDKTIMELEN 3600*24-1
#define NOTSETDURATION -2
#define DATELEN    10
#define SEP        ":"
#define FILESEP    ";"
#define ITEMSEP    ","
#define DIR        "\\"
#define RECORDSEP  "&"
#define FIELDSEP   "_"
#define WKPFILTER  "*.avi"
#define GPSFORMAT  "\"longitude\":\"%.6f\"%s\"latitude\":\"%.6f\"%s\"speed\":\"%d\"%s\"angle\":\"%d\"%s\"UTC\":\"%ld\"%s"
#define WWANRFORMAT "\"signal_type\":\"%s\"%s\"signal_strength\":\"%s\""
#define PLATEFORMAT "\"plate_number\":\"%s\"%s"
#define ALARMFORMAT "\"alarm_number\":\"%s\"%s\"alarm_value\":\"%s\"%s"
#define LONGITUDE "\"longitude\":\""
#define LATITUDE  "\"latitude\":\""
#define QUOTE      "\""
#define UPDATEURLDCI "http://172.26.11.6:8112/offlineplayertool"
#define UPDATEURLDCE "http://172.26.11.6:8112/offlineplayertool"
#define UPDATEURLBCI "http://172.28.11.11:8112/offlineplayertool"
#define UPDATEURLBCE "http://172.28.11.11:8112/offlineplayertool"

#define MAPURLDCI   "http://172.28.11.11:8111/ArcgisMap/Default.htm"
#define MAPURLDCE   "http://190.152.152.2:8086/ArcgisMap/Default.htm"
#define MAPURLBCI   "http://172.28.11.11:8111/ArcgisMap/Default.htm"
#define MAPURLBCE   "http://190.152.152.2:8086/ArcgisMap/Default.htm"

#define LOGINDCI    "http://172.28.2.4/ManagerService/videoUserInfoService.asmx"
#define LOGINDCE    "http://190.152.152.3/ManagerService/videoUserInfoService.asmx"
#define LOGINBCI    "http://172.28.2.4/ManagerService/videoUserInfoService.asmx"
#define LOGINBCE    "http://190.152.152.3/ManagerService/videoUserInfoService.asmx"

#define HTTPHEAD    "http://"
#define HTTPTAIL    "/"
#define PINGSTR     "ping "
#define JSLEN       512
#define LOGLEN      1024
#define LOGINBUFLEN 2048
#define TEMPLEN     50
#define AVILEN      26
#define EXTENDINFLEN      30
#define DEFAULTVOLUEM 50
#define TIMELIMIT     59
#define TIMELEN       60
#define VOLUMELEN     160.0
#define CLEARINVAL     2000
#define JSONLEN       50
#define DIVISOR    1000000.0
#define PIXINVALID 9999
#define DLGW       450
#define DLGH       350
#define UNINVALIDINT -1
#define SPEEDCOUNT  9
#define XOFFSET    5
#define YOFFSET    5
#define FONTSIZE   20
#define FRAMEWIDTH 1
#define RESIZEWIDTH 2
#define MINISECONDUNIT 1000
#define UPDATECOUNT 10
#define NAMELEN     100
#define MINIWIDTH   860
#define WAITTIME   50000
#define DLLPATH    "controlPlugin"
#define SDKPATH    "SDK"
#define PLUGINPATH "plugins"
#define CONFIGPATH "config\\conf.ini"
#define USERCONFIG "config\\qss.ini"
#define TEMPUPDATE "\\UPDATETEMP"
#define UIPATH     "ui"
#define RMPREFIX   ".264"
#define WKPPREFIX  ".avi"
#define JNPREFIX   ".ts"
#define RMFILTER   "*.264"
#define RMDATFILE  "rmdvrrootdir.dat"
#define RMFILELIST "file_list"
#define WKPFILTER  "*.avi"
#define RMSDK      "RM"
#define WKPSDK     "WKP"
#define JNSDK      "JN"
#define ALARMPRE   "A"
#define ERRORTIP   "strError"
#define WARNINGTIP "strWarning"
#define GSZPWD = "jnvision"
#define DATEFILTER "[1-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9]"
#define VALIDUSER1 "<ValidateUserResult>"
#define VALIDUSER2 "</ValidateUserResult>"
#define STRTRUE    "true"
#define STRFALSE   "false"
#define SPECIALNAME "zxcvbnm,"
#define SPECIALPWD  "zxcvbnm,"

#define AVILEN      26
#define DEFAULTVOLUEM 50
#define TIMELIMIT     59
#define TIMELEN       60
#define VOLUMELEN     160.0
#define CLEARINVAL     2000
#define MOVEINVAL     50
#define JSONLEN       50
#define MAXFILELEN    512
#define MOVSPACE      5 
#define SPACEMARGIN   20
#define EXTRAFLAG_INVALID	0x00000000
#define EXTRAFLAG_PLATENUM	0x00000001
#define EXTRAFLAG_GPS		0x00000002
#define EXTRAFLAG_NETWORK	0x00000004
#define EXTRAFLAG_ALARM		0x00000008
#define EXTRAFLAG_TIME		0x00000010
#define EXTRAFLAG_FILE_DURATION	0x00000020
#define EXTRAFLAG_FILE_CURSECOND 0x00000040

#define WWANRXW           0
#define GPSW              0
#define MAXCOUNT          100
#define ALARMBRUSH QBrush(QColor(255,0,0));
#define NORMALBRUSH QBrush(QColor(0,0,255));
#define CUSTOMFLAG 10
#define NETCOUNT    4
#define FILECOUNT   150

//#define  SECURITY_ANONYMOUS_LOGON_RID (0x00000007L)
//#define  SECURITY_SERVER_LOGON_RID    (0x00000009L)
//#define  SE_GROUP_LOGON_ID            (0xC0000000)
typedef int BOOL;
typedef std::map<int,std::pair<int,bool> > SDKTMAP;
typedef std::map<int,std::map<unsigned char,std::string> > SDKFMAP;
typedef std::map<QWidget*,std::map<QString,std::pair<QString,std::pair<QString,QString> > > > LANGMAP;
typedef std::map<QString,std::pair<QString,std::pair<QString,QString> > > TXTMAP;
enum EventType {
	EVENT_TYPE_BEGINPLAY = 1, 
	EVENT_TYPE_STOPPLAY,
	EVENT_TYPE_BEGINRECVDATA,
	EVENT_TYPE_BREAK,
	EVENT_TYPE_PROGRESS,
	EVENT_TYPE_LBCLICK,
	EVENT_TYPE_PRIVATEINFO,
	EVENT_TYPE_DBCLICK
};
typedef struct tagGpsItem
{
	short nSpeed;
	short nAngle;
	short nReserve1;
	short nReserve2;
	int nLat;
	int nLon;
	long lUtcTime;
	tagGpsItem();
	tagGpsItem(int nLat,int nLon,int nSpeed,int nAngle);
}GPSITEM;

typedef struct tagGps
{
	short nSpeed;
	short nAngle;
	short nReserve1;
	short nReserve2;
	int nLat;
	int nLon;
	tagGps();
	tagGps(int nLat,int nLon,int nSpeed,int nAngle);
}GPS2;
typedef struct sctFileInfo
{
	int iVideoWndIndex;
	long iDuration;//s
	int iCurTime;
	int iPlayingStateFlag;//-1,havn't played;0,playing;1,played
	BOOL bCalDurationFlag;//FALSE,needn't calculate the duration.
	BOOL bBeginPlayFlag;
	long lFileSize;
	QString strFileName;
	QString strFileSize;
	QString strFilePath;
	QString strPlateNumber;
	sctFileInfo();
	//QString strDescription;
}FileInfo;

typedef int (* ParaRealPlay)(const wchar_t* szVmsUrl,int nIndex,const char* szWnd);
typedef int (* PlayVideo)(int nIndex);
typedef int (* UpdateWnd)(int nIndex,const char* szWnd);
typedef int (* DisposCtrl)(int nIndex);
typedef int (* Disconnect)(int nIndex);
typedef int (* SetEventCallBack)(long pEnventCallBackPtr);
typedef void (* SetControlInfo)(int nIndex,const char* szInfo);
typedef void (*SetCustomFlag)(int nIndex,int nCustomFlag);
enum MapType
{
	Baidu=0,
	Google=1,
	Arcgic=2,
	Gaode=3,
	UnknowMap=-1
};
enum PrivateInfo
{
	PlateNumber=83,
	GpsInfo=84,
	WWANRx=85,
	AlarmInfo=86
};
enum FileSourceType
{
	RmType=0,
	WkpType=1,
	JNType=2,
	UnknowType=-1
};
struct rc4_state
{
	int x, y, m[256];
};
enum ENetType
{
	DataCenterInner=0,
	DataCenterExter=1,
	BackupCenterInner=2,
	BackupCenterExter=3,
	NoInternet=4
};
#endif
