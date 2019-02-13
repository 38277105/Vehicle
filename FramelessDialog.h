#ifndef FRAMELESSDIALOG_HEADER
#define FRAMELESSDIALOG_HEADER
#include <QDialog>
#include <QMouseEvent>
#include <QSplitter>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <QSlider>
#include <QLabel>
#include <QtUiTools/QtUiTools>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QTableWidget>
#include <QVector>
#include <QtGui>
#include <QLibrary>
#include <QSharedMemory>
#include <QBuffer>
#include <QTextStream>
#include <map>
#include <set>
#include <string>
#include "windowlisteditor.h"
#include "ANTOfflineFileSDKAdapter.h"
#include "CommonStruct.h"
#include "VehicleVideoPlayerPub.h"
#include "FullVideo.h"
#include "TipsBox.h"
extern QWidget* pDialog;
class CThreadCheckFile;
#define SHOW_ERROR_BOX(x)  ShowMessageBox(ERRORTIP,x,eErrorTip);//QMessageBox::warning(NULL,"Error",x)//::MessageBox(NULL,x,"Error",MB_OK|MB_ICONWARNING)

class CFramelessDialog:public QFrame
{
		Q_OBJECT
public:
	friend class CThreadCheckFile;
public:
	CFramelessDialog(QWidget* pParent=NULL);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void timerEvent(QTimerEvent * tvent);
	virtual bool eventFilter ( QObject * watched, QEvent * event );
	void         loadUi(const char* szFileName);
	void setAllConnect();
	void createVideo(int iWndIndex,QString & strFileName);
	void createDllVideo();
	void createBkVideo();
	void createMainPage();
	void createFileListTable();
	void setEventFilterGpsAndWWanrx();
    void showVideo(BOOL bShow=FALSE);
	void showOpen();
	void readConfig();
	void saveConfig();
	void clearFileListInfo();
	void setCurFileList(QStringList & strFiles);
	void setListInfo();
	void PlayVideoByFileInfo(FileInfo* pFileInfo,int iActionFlag);
	void SetVideoPlayerControlInfo(int iWndIndex,QString & strCtrlInfo);
	
	BOOL IsVideoShow(int iWndIndex,BOOL &bJN);
	void updateRangeForProgress(int nMax);
	void updateProgress(int nPos);
	void updateVolume();
	void updatePlayBtn();
	void updateGpsBtn();
	void updateTitle(QString &strName);
	void updateCurVideo(int iWndIndex,BOOL bForce = FALSE);
	void setVolume(int nVolume);
	unsigned char &getSpeedIndex();
	BOOL createSystemTray();
	
	FileInfo* getPlagFile(int iWndindex);
	void pauseAll(BOOL bPause);
	void playAll(BOOL bPause);
	void showAllGps(BOOL bShow);
	void soundAll(BOOL bSound);
	void updateControlState(int iWndIndex);
	void updateOSD(int iWndIndex);
	BOOL loginANT();
	void ShowLoging(BOOL bShow);
	void createLanguageMenu();
    void resizeMap();
	void showMap(BOOL bShow);
    void hideExtend();
	
	void SetLangID(int nLangID)
	{
		m_nLangID = nLangID;
	}
	BOOL LoadDLLs();                        
	BOOL CreatePluginInterface();
	static int ANTSDK_REALDATACALLBACK(void * pThis,int nChannel, unsigned int nExtraDataFlag,const char * szPlateNumber, struct tagGps * pGPSItem, const char * szWWANRxLevel,const char * nAlarmType,const char * szTime,unsigned int nFileDuration,unsigned int nCurSecond);

	static int ANTSDK_REALDATACALLBACK2(void * pThis,int nChannel, unsigned int nExtraDataFlag,const char * szPlateNumber, const char* szExtend, const char * szWWANRxLevel,const char * nAlarmType,const char * szTime,unsigned int nFileDuration,unsigned int nCurSecond);

	static int ANTSDK_CONTAINER_WRITELOG(void * pThis,const char * szLog,...);

	static int ANTSDK_CONTAINER_MESSAGEBOX(void * pThis,const char * szMsg);

	static int ANTSDK_CONTAINER_DAYFILELISTDIALOG(void * pThis,const char * szDayList,char * szResultSelectDay,int * nChannelFlag);

	static int ShowSelectDayAndChannelDialog(QStringList & strDayList,char * szSelectDay,int * nChannelFlag,int &nType);
	int AllSDK_Init();
	int AllSDK_Exit();

	int AllSDK_Config_SetVideoHWND(void * pThis,unsigned int * szArrageHWND,int nHWNDCount);

	int AllSDK_Config_SetCallBackExtraData(CANTOfflineFileSDKAdapter::FUNC_SET_ANTSDK_REALDATACALLBACK pFunc);
	CANTOfflineFileSDKAdapter* GetPlugin(FileSourceType fileType);
	CANTOfflineFileSDKAdapter* GetPlugin(int iWndIndex);
	BOOL GetPathFileInfo(QString & strPath);

	void PlayGroup(SDKFMAP::iterator itf);
	void PlayGroupInRow(int nRow);
	void SetTableColWidth();
	void SaveUserInfo();
	void ReadUpdateInfo(QString & strFile,QStringList & listUpdate,QString & strVersion,BOOL bOnlyVersion=TRUE);
	void ShowPrivateInfo(const char* szInfo);
	void ShowMainPage();
	void PlayImmediately(QString & strFile);
	int  AddFile(QString & strFile);
	int  AddRow(int nIndex);
	int  FindTsFile(QString & strFile);
	static unsigned int ThreadCalDurationAccordingFile(void* lpPara);
	static unsigned int ThreadCheckUpdate(void* lpPara);
	static unsigned int ThreadLogin(void* lpPara);
	static unsigned int ThreadCheckPlayFile(void* lpPara);
	static void OnEventCallBack(int nIndex,int nType,char* szPara,char* szWanrx,char* szGps);
	Q_SIGNALS:
	void fullScreenVideo();
	void newPrivateInfo(int nWndIndex,int nIndex);
	BOOL nextItem(int iWndIndex,int iStep);
	void clearloc();
	void extendInfo (int nWndIndex,const char* szGps,const char* szWWanrx);
	void updateInfo();
	void loginResult(int nStatus);
	void newTsFile();
	public Q_SLOTS:
		void clickMaxBtn();
		
		void clickedMap();
		void clickedFullScreen();
		void clickedPlay();
		void clickedStop();
		void clickedSound();
		void clickedGps();
		void clickedSlow();
		void clickedFast();
		void clickedUpdate();
		void clickedVolumeBar();
		void pressVolumeBar();
		void clickTrayIcon();
		void clickLogin();
		void clickCancelInLogin();
	    void clickSetLanguage();
		void clickOkInSelectChannel();
		void checkRemember(int nState);
		void checkAll(int nState);
		void activedTrayIcon ( QSystemTrayIcon::ActivationReason reason );
		void tableViewPortEnter();
		void tableItemEnter(const QModelIndex & index);
	
		void cellClicked(int row,int column);
		
		void progressBarAction(int nAction);
		void progressBarMoved(int nValue);
		void progressBarReleased();
		BOOL PlayNextItem(int iWndIndex,int iStep);
        void openModeActivated(int nIndex);

		void updateDuration(FileInfo* info);
		void quitApp();
		void moveLeftRightSpliter(int nPos,int nIndex);
		void moveMapFileSpliter(int nPos,int nIndex);
		void trigerExitMenu(QAction* pAction);
		void updatePrivateInfo(int nWndIndex,int nIndex);
		void trigerLanguageMenu(QAction* pAction);
		
		void showExtend(int nWndIndex,const char* szGps,const char* szWWanrx);
		void showUpdate();
		void showLoginResult(int nStatus);
		void playNewTsFile();
private:
	
	BOOL     m_bMax;
	BOOL     m_bShowOpen;
	BOOL     m_bOpenSound;
	BOOL     m_bProgressPressed;
public:
	BOOL     m_bMouseDown;
	BOOL     m_bFull;
	BOOL     m_bShowMap;
	BOOL     m_bPlayingFlagLT;
	BOOL     m_bPlayingFlagRT;
	BOOL     m_bPlayingFlagLB;
	BOOL     m_bPlayingFlagRB;

	BOOL m_bPlayOrPauseFlagLT;
	BOOL m_bPlayOrPauseFlagRT;
	BOOL m_bPlayOrPauseFlagLB;
	BOOL m_bPlayOrPauseFlagRB;

	BOOL m_bSoundOrNotFlagLT;
	BOOL m_bSoundOrNotFlagRT;
	BOOL m_bSoundOrNotFlagLB;
	BOOL m_bSoundOrNotFlagRB;

	BOOL m_bExtendFlagLT;
	BOOL m_bExtendFlagRT;
	BOOL m_bExtendFlagLB;
	BOOL m_bExtendFlagRB;
	BOOL m_bMoveToRight;
	int  m_nMoveSpace;
	int  m_nMargin;
	int  m_nMove;

	BOOL m_bLeft;
    BOOL m_bRight;
	int      m_iVolumeLT;
	int      m_iVolumeRT;
	int      m_iVolumeLB;
	int      m_iVolumeRB;
	int      m_nVolum;

	unsigned char m_iSpeedIndexLT;
	unsigned char m_iSpeedIndexRT;
	unsigned char m_iSpeedIndexLB;
	unsigned char m_iSpeedIndexRB;
	unsigned char m_iSpeedIndex;
	
	int      m_nVLevel1;
	int      m_nVLevel3;
	int      m_nVolumeWidth;
	int      m_nCurWndIndex;
    BOOL     m_bSDK;
	
	int      m_nTimeID;
	int      m_nClearTimer;
	int      m_nLoginErrorTimer;
	int      m_nNoInterNetTimer;
	int      m_nLoginFailedTimer;
	int      m_nServiceErrorTimer;
	int      m_nMoveTimer;
	static BOOL g_bThreadCompletedFlag;
	QRect    m_rcGeometry;
   
	QPoint   m_ptDown;
	QPoint   m_ptMove;
	QString  m_strPreFileDir;

	QString  m_strCtrlPlay;
	QString  m_strCtrlPause;
	QString  m_strCtrlSlow;
	QString  m_strCtrlFast;
    QString  m_strCtrlFullSize;
	QString  m_strCtrlSound;
	QString  m_strCtrlNotSound;
	QString  m_strCtrlExtInfo;
	QString  m_strCtrlNotExtInfo;
	QString  m_strCtrlVolume;
    QString  m_strCtrlUpdateProgress;
	QString  m_strCtrlNotUpdateProgress;
	QString  m_strCtrlSetProgress;

	QString  m_strMapDCI;
	QString  m_strMapDCE;
	QString  m_strMapBCI;
	QString  m_strMapBCE;
	QString  m_strMapUrl;

	QString  m_strUpdateDCI;
	QString  m_strUpdateDCE;
	QString  m_strUpdateBCI;
	QString  m_strUpdateBCE;
	QString  m_strUpdateUrl;

	QString  m_strCol1Caption;
	QString  m_strCol3Caption;
	QString  m_strCol4Caption;

	QString  m_strColNum;
	QString  m_strColTime;
	QString  m_strColLen;
	QString  m_strColType;

	QString  m_strRecvProgress;
	QString  m_strRecvSpeed;
	QString  m_strRecvDuration;
	QString  m_strRecvPlay;
	QString  m_strRecvNext;
	QString  m_strRecvStop;
	QString  m_strRecvSound;
	QString  m_strRecvVolume;

	//QString  m_strVideoOcxID;

	QString  m_strStylePlay;
	QString  m_strStylePause;
	QString  m_strStyleExtend;
	QString  m_strStyleNoExtend;
	QString  m_strStyleMax;
	QString  m_strStyleRestore;
	QString  m_strStyleVolume0;
	QString  m_strStyleVolume1;
	QString  m_strStyleVolume2;
	QString  m_strStyleVolume3;
	QString  m_strStyleOSD;
	QString  m_strFileImmediate;

	QVector<FileInfo*> m_VectorFileInfo;
	static SDKTMAP m_mpSDKTimeInfo;
	static SDKFMAP    m_mpSDKFileInfo;
	std::set<int> m_setTime;
	int                               m_nChannelFlag;
	int                               m_nRestoreChannelFlag;
    int                               m_nCurFileIndex;
	int                               m_nCurSecond;
	int                               m_nStartSecond;
	int                               m_nCurDuration;

	int                               m_nModeIndex;
	unsigned int m_hPlayWnd[4];
	unsigned int m_nMaxChannel;

	std::vector < std::pair < QLibrary*, std::string > > m_vtPluginDLL;		
	std::vector < CANTOfflineFileSDKAdapter *> 	m_vtPluginInterface;

	char m_szSDKPath[JSLEN];
	
	static std::map<int,std::string> m_mpStrPlate;
	static std::map<int,std::string> m_mpStrExtend;

	int		m_nLangID;
	BOOL    m_bUpdate;
	BOOL    m_bShowUpdate;
	BOOL    m_bOnLine;
	BOOL    m_bSetEventFilter;
	BOOL    m_bPlayImmediately;
	static BOOL    m_bSetConnect;
	static BOOL    m_bCancelLogin;
	static  QSharedMemory m_memShared;
	static BOOL    m_bIsRun;
	
	QStringList m_listUpdate;
    
public:
	QWidget* m_pChild;
	QWidget* m_pvideoBk;
	QWidget* m_pRight;
	QComboBox* m_pOpenCombox;
	QSlider* m_pProgress;
	QLabel*  m_pNameLabel;
	QTableWidget* m_pTableList;
	QWidget* m_pvideoLT;
	QWidget* m_pvideoLB;
	QWidget* m_pvideoRT;
	QWidget* m_pvideoRB;
	QWidget*   m_pdllVideoLT;
	QWidget*   m_pdllVideoLB;
	QWidget*   m_pdllVideoRT;
	QWidget*   m_pdllVideoRB;
	CFullVideo*    m_pLT;
	CFullVideo*    m_pLB;
	CFullVideo*    m_pRT;
	CFullVideo*    m_pRB;
	CFullVideo*    m_pCurFull;
	QWidget*       m_pPLT;
	QWidget*       m_pPLB;
	QWidget*       m_pPRT;
	QWidget*       m_pPRB;
	QWidget*       m_pPLeft;
	QWidget*       m_pPRight;
	QLabel*    m_pWWANRLevelLT;
    QLabel*    m_pWWANRLevelLB;
	QLabel*    m_pWWANRLevelRT;
	QLabel*    m_pWWANRLevelRB;
	
	QLabel*    m_pGpsLT;
	QLabel*    m_pGpsLB;
	QLabel*    m_pGpsRT;
	QLabel*    m_pGpsRB;

	QLabel*    m_pCurTime;
	QLabel*    m_pTotalTime;

	QWidget*  m_pMap;
	QPushButton* m_pBtnPlay;
	QPushButton* m_pBtnMax;
	QPushButton* m_pBtnUpdate;
	QPushButton* m_pBtnVolume;
	QWidget* m_pVolumeBar;
	QPushButton* m_pBtnGps;

	QSystemTrayIcon* m_psystemTray;
	static QDialog*   m_pSelectDay;
	QAction*          m_pExitAction;
	QMenu*            m_pTrayMenu;
	QDialog*          m_pLoginWidget;
	QLineEdit*        m_pUserNameEdit;
	QLineEdit*        m_pPwdEdit;
	QPushButton*      m_pBtnSet;
	QMenu*            m_pLanguageMenu;
	QAction*          m_pEngAction;
	QAction*          m_pEspAction;
	QAction*          m_pChnAction;
	QVBoxLayout*      m_pTopLay;
	QFrame*            m_pLogining;
	QLibrary*  m_pvideoDll;
	static QDialog*   m_pTipsDialog;
	//ParaRealPlay                   m_pFuncParaRealPlay;
	ParaRealPlay                   m_pFuncParaFileList;
	PlayVideo                      m_pFuncPlayImpl;
	UpdateWnd                      m_pFuncUpdateVideoWnd;
	DisposCtrl                     m_pFuncDispose;
	Disconnect                     m_pFuncDisconnect;
	SetEventCallBack			   m_pFuncSetEventCallBack;
	SetControlInfo                 m_pFuncSetControlInfo;
	SetCustomFlag                  m_pFuncSetCustomFlag;
	QIcon    m_icoTray;
	QBrush m_brAlarm;
	QBrush m_brNormal;
	public:
	
	//static std::ofstream m_ofStream;

};

#endif
