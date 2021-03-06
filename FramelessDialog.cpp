
#include "FramelessDialog.h"
#include "windowlisteditor.h"
#include "CommonFunc.h"
#include <Oaidl.h>
#include "./json/value.h"
#include "./json/reader.h"
#include "LoginDialog.h"
#include "LanguageProcessor.h"
#include "DllFunc.h"
#include "Thread.h"
#pragma comment(lib,"Urlmon.lib")
#pragma comment(lib,"shell32.lib")
#pragma comment(lib,"User32.lib")
BOOL CFramelessDialog::g_bThreadCompletedFlag = TRUE;

QDialog* CFramelessDialog:: m_pSelectDay = NULL;

SDKTMAP CFramelessDialog::m_mpSDKTimeInfo;
SDKFMAP CFramelessDialog::m_mpSDKFileInfo;
std::map<int,std::string> CFramelessDialog::m_mpStrPlate;
std::map<int,std::string> CFramelessDialog::m_mpStrExtend;
QDialog* CFramelessDialog::m_pTipsDialog = NULL;
BOOL CFramelessDialog::m_bSetConnect = FALSE;
BOOL CFramelessDialog::m_bCancelLogin = FALSE;
QSharedMemory CFramelessDialog::m_memShared("VehicleVideoPlayerShareMemory");
extern QWidget* pDialog;
extern QApplication* pApplication;
extern QString strPicError;
extern QString strPicWarning;
extern QString strPicInfo;
double arraySpeed[SPEEDCOUNT] ={1.0/16.0,1.0/8.0,1.0/4.0,1.0/2.0,1,2,4,8,16};

char szLoc[50]={0};
char szWWanrx[50]={0};
int gMin = 860;
BOOL gbIsRun = TRUE;
BOOL CFramelessDialog::m_bIsRun = TRUE;
//HANDLE g_hTsTimeEvent = NULL;
//CRITICAL_SECTION g_crCheckFile;
//CRITICAL_SECTION g_crTsTime;

//
//////
CFramelessDialog::CFramelessDialog(QWidget* pParent):QFrame(pParent,Qt::Window)
{
	//setWindowFlags(Qt::FramelessWindowHint |Qt::Tool | Qt::X11BypassWindowManagerHint| Qt::WindowStaysOnTopHint);//| Qt::WindowStaysOnTopHint 
   setAttribute( Qt::WA_QuitOnClose, true);    
	setWindowFlags(Qt::FramelessWindowHint);
	m_bOpenSound = TRUE;

	m_bShowMap = FALSE;
	m_bFull = FALSE;
	m_bShowOpen = TRUE;
	m_bMouseDown = FALSE;
	m_bMax = FALSE;
	//m_bsetTableItem = FALSE;
	m_bPlayOrPauseFlagLB = FALSE;
	m_bPlayOrPauseFlagLT = FALSE;
	m_bPlayOrPauseFlagRB = FALSE;
	m_bPlayOrPauseFlagRT = FALSE;

	m_bPlayingFlagRB = FALSE;
	m_bPlayingFlagLB = FALSE;
	m_bPlayingFlagLT = FALSE;
	m_bPlayingFlagRT = FALSE;

	m_bSoundOrNotFlagLT = TRUE;
	m_bSoundOrNotFlagRT = TRUE;
	m_bSoundOrNotFlagLB = TRUE;
	m_bSoundOrNotFlagRB = TRUE;

	m_bSDK = FALSE;
	m_bMoveToRight = TRUE;


	m_bLeft = FALSE;
	m_bRight = FALSE;
	m_bPlayImmediately = FALSE;
	m_bSetConnect = FALSE;
    m_nTimeID = 0;
	m_nClearTimer = 0;
	m_nLoginErrorTimer = 0;
	m_nNoInterNetTimer = 0;
	m_nLoginFailedTimer - 0;
	m_nServiceErrorTimer = 0;
	m_nMoveTimer = 0;
	m_nMove = 0;
	m_pChild = NULL;
	m_pvideoLT = NULL;
	m_pvideoLB = NULL;
	m_pvideoRB = NULL;
	m_pvideoRT = NULL;
	m_pdllVideoRB = NULL;
	m_pdllVideoRT = NULL;
	m_pdllVideoLT = NULL;
	m_pdllVideoLB = NULL;
	m_pLT = NULL;
	m_pLB = NULL;
	m_pRT = NULL;
	m_pRB = NULL;
	m_pPLT = NULL;
	m_pPLB = NULL;
	m_pPRT = NULL;
	m_pPRB = NULL;
	m_pPLeft = NULL;
	m_pPRight = NULL;
	m_pCurFull = NULL;
    //m_pcurVideo = NULL;
	m_pMap = NULL;
	m_pBtnGps = NULL;
	m_pBtnMax = NULL;
	m_pBtnUpdate = NULL;
	m_pRight = NULL;
	m_pvideoBk = NULL;
	m_pOpenCombox = NULL;
	m_pTableList = NULL;
    //m_pTableSDK = NULL;
    m_pProgress = NULL;
	m_pNameLabel = NULL;
	m_pBtnVolume = NULL;
	m_pBtnPlay = NULL;
	m_pVolumeBar = NULL;
	m_psystemTray = NULL;

	m_pCurTime = NULL;
	m_pTotalTime = NULL;

	m_pWWANRLevelLT = NULL;
	m_pWWANRLevelLB = NULL;
	m_pWWANRLevelRT = NULL;
	m_pWWANRLevelRB = NULL;
	m_pGpsLT = NULL;
	m_pGpsLB = NULL;
	m_pGpsRT = NULL;
	m_pGpsRB = NULL;
	m_pExitAction = NULL;
    
	m_pLoginWidget = NULL;
	m_pUserNameEdit = NULL;
	m_pPwdEdit = NULL;
	m_pBtnSet = NULL;
	m_pLanguageMenu = NULL;
	m_pEngAction = NULL;
	m_pEspAction = NULL;
	m_pChnAction = NULL;
	m_pLoginWidget = NULL;
    //m_pLoginMovie = NULL;
	m_pTopLay = NULL;
	m_pvideoDll = NULL;
	m_pLogining = NULL;
	m_nCurWndIndex = 0;

	m_iVolumeRB = 50;
	m_iVolumeRT = 50;
	m_iVolumeLT = 50;
	m_iVolumeLB = 50;

	m_iSpeedIndexLT = 4;
	m_iSpeedIndexRT = 4;
	m_iSpeedIndexRB = 4;
	m_iSpeedIndexLB = 4;
	m_iSpeedIndex = 4;

	m_nCurFileIndex = 0;
	m_nChannelFlag = 0;
	m_nRestoreChannelFlag = 0;
	m_nCurSecond = 0;
	m_nStartSecond = 0;
	m_nCurDuration = 0;
	memset(m_szSDKPath,0,JSLEN);
	m_brAlarm.setStyle(Qt::SolidPattern);
	m_brNormal.setStyle(Qt::SolidPattern);
	m_brAlarm.setColor(QColor(255,0,0));
	m_brNormal.setColor(QColor(0,128,0));
	readConfig();
	m_nModeIndex = -1;

	m_bExtendFlagLT = TRUE;
	m_bExtendFlagRB = TRUE;
	m_bExtendFlagLB = TRUE;
	m_bExtendFlagRT = TRUE;

	m_bUpdate = FALSE;
	m_bShowUpdate = FALSE;
	m_bOnLine = FALSE;
	m_bSetEventFilter = FALSE;
	//m_pFuncParaRealPlay  = NULL;
	m_pFuncParaFileList =  NULL;
	m_pFuncPlayImpl       = NULL;
	m_pFuncUpdateVideoWnd = NULL;
	m_pFuncDispose        = NULL;
	m_pFuncDisconnect     = NULL;
	m_pFuncSetEventCallBack  = NULL;
	m_pFuncSetControlInfo = NULL;
	m_pFuncSetCustomFlag = NULL;

	m_pvideoDll = new QLibrary(QCoreApplication::applicationDirPath()+"/CEIECVideoPlayer.dll");
	if (m_pvideoDll && m_pvideoDll->load())
	{
		//m_pFuncParaRealPlay  = (ParaRealPlay)m_pvideoDll->resolve("ANT2_Para_RealPlay");
		m_pFuncParaFileList =  (ParaRealPlay)m_pvideoDll->resolve("ANT2_Para_FileList");
		m_pFuncPlayImpl       = (PlayVideo)m_pvideoDll->resolve("ANT2_Play_Impl");
		m_pFuncUpdateVideoWnd = (UpdateWnd)m_pvideoDll->resolve("ANT2_Update_Wnd");
		m_pFuncDispose        = (DisposCtrl)m_pvideoDll->resolve("ANT2_Dispose");
		m_pFuncDisconnect     = (Disconnect)m_pvideoDll->resolve("ANT2_Disconnect");
		m_pFuncSetEventCallBack  = (SetEventCallBack)m_pvideoDll->resolve("ANT2_SetEventCallBack");
		m_pFuncSetControlInfo = (SetControlInfo)m_pvideoDll->resolve("ANT2_SetControl_Info");
		m_pFuncSetCustomFlag = (SetCustomFlag)m_pvideoDll->resolve("ANT2_SetCustom_Flag");
	}
 
	
}
/************************************************************************/
/*
Mouse press down event save the point of press down for the mouse
move event
* param[in] pMouseEvent
* return none
*/
/************************************************************************/

void CFramelessDialog::mousePressEvent(QMouseEvent *pMouseEvent)
{
	m_bMouseDown = TRUE;
	m_ptDown = QCursor::pos();//pMouseEvent->pos();
	m_ptMove = pMouseEvent->pos();
	m_rcGeometry = geometry();	
}
/************************************************************************/
/*
Mouse release event,mark the flag for mouse down be FALSE
if the mouse is over the volume bar reset it's width
param[i] pMouseEvent
return   none
*/
/************************************************************************/
void CFramelessDialog::mouseReleaseEvent(QMouseEvent *pMouseEvent)
{
	m_bMouseDown = FALSE;
	QCursor curs(Qt::ArrowCursor);
	setCursor(curs);	
	if (m_bPlayingFlagLT && m_pVolumeBar)
	{
		QRect rc = m_pVolumeBar->geometry();
		QPoint pt1 = ((QWidget*)m_pVolumeBar->parent())->mapFromGlobal(pMouseEvent->globalPos());
		if (pt1.x()>=rc.left() && pt1.y()>=rc.top() && pt1.y()<=rc.bottom())
		{
			if (pt1.x()<=rc.left()+m_nVolumeWidth)
			{
				m_pVolumeBar->setGeometry(rc.left(),rc.top(),pt1.x()-rc.left(),rc.height());
			} 
			else
			{
				m_pVolumeBar->setGeometry(rc.left(),rc.top(),m_nVolumeWidth,rc.height());
			}

			setVolume(m_pVolumeBar->width()*2);
			updateVolume();
		}
	}	
}
/************************************************************************/
/*
Mouse move Event,move or resize the window
param[in]  pMouseEvent
return     none
*/
/************************************************************************/
void CFramelessDialog::mouseMoveEvent(QMouseEvent *pMouseEvent)
{
	if (m_bMouseDown)
	{
		if (cursor().shape()==Qt::SizeHorCursor)
		{
			QPoint pt = QCursor::pos()-m_ptDown;//pMouseEvent->pos()-m_ptDown;
			if (m_bLeft)
			{
				if (m_rcGeometry.width() - pt.x() > gMin)
				{
					setGeometry(m_rcGeometry.left()+pt.x(),m_rcGeometry.top(),m_rcGeometry.width()-pt.x(),m_rcGeometry.height());
				}
                
			} 
			else if (m_bRight)
			{
				setGeometry(m_rcGeometry.left(),m_rcGeometry.top(),m_rcGeometry.width()+pt.x(),m_rcGeometry.height());
			}
			
		}
		else
		{
			move(pMouseEvent->globalPos()-m_ptMove);
			//move(QCursor::pos()-m_ptDown);
		}	
	}
	else
	{
		QRect rc = rect();
		QPoint pt1 = QCursor::pos();
		QPoint pt = mapFromGlobal(pt1);
		if((pt.x()>=rc.width()-RESIZEWIDTH && pt.x() <= rc.right()) || (pt.x()>= 0&& pt.x()<=RESIZEWIDTH))//if ((pt.x()<=rc.width() && pt.x()>=rc.width()-m_nMarginR+1)||(pt.x()>=0 && pt.x()<=m_nMarginL-1))
		{
			if (pt.x()>= 0&& pt.x()<=RESIZEWIDTH)
			{
				m_bLeft = TRUE;
				m_bRight = FALSE;
			} 
			else
			{
                m_bRight = TRUE;
				m_bLeft = FALSE;
			}
			if (cursor().shape()!=Qt::SizeHorCursor)
			{
				QCursor curs(Qt::SizeHorCursor);
				setCursor(curs);
			}
			
		}
		else if (cursor().shape()!=Qt::ArrowCursor)
		{
			QCursor curs(Qt::ArrowCursor);
			setCursor(curs);
		}
	}
}
/************************************************************************/
/*
Timer event,handle all the timer
param[in] tevent
return    none
*/
/************************************************************************/
void CFramelessDialog::timerEvent(QTimerEvent * tevent)
{
	if (!tevent)
	{
		return;
	}
    if(tevent->timerId() == m_nTimeID)
    {
		if (CDllFunc::m_pFuncSwithLanguage)
		{
			if (TRUE == (*CDllFunc::m_pFuncSwithLanguage)(CLanguage::m_eLanguageType,eOfflinePlay))
			{
				killTimer(m_nTimeID);
			}
		}
    }
	else if(tevent->timerId() == m_nClearTimer)
	{
		if (CDllFunc::m_pFuncClearPath)
		{
			m_mpStrExtend.clear();
			m_setTime.clear();
			m_nCurSecond=0;
			(*CDllFunc::m_pFuncClearPath)(0,eOfflinePlay);
			killTimer(m_nClearTimer);
		}
	}
	else if (tevent->timerId() == m_nLoginErrorTimer)
	{
		QLabel* pNoInternetLabel = qFindChild<QLabel*>(m_pLoginWidget,"noInternetLabel");
		if (pNoInternetLabel)
		{
			pNoInternetLabel->hide();
		}
		QLabel* pLoginFailedLabel = qFindChild<QLabel*>(m_pLoginWidget,"loginFailedLabel");
		if (pLoginFailedLabel)
		{
			pLoginFailedLabel->hide();
		}
		QLabel* pNoServiceLabel = qFindChild<QLabel*>(m_pLoginWidget,"noServiceLabel");
		if (pNoServiceLabel)
		{
			pNoServiceLabel->hide();
		}
		
		killTimer(m_nLoginErrorTimer);

	}
	else if (tevent->timerId() == m_nNoInterNetTimer)
	{
		QLabel* pNoInternetLabel = qFindChild<QLabel*>(m_pLoginWidget,"noInternetLabel");
		if (pNoInternetLabel)
		{
			pNoInternetLabel->show();
		}
		ShowLoging(FALSE);
		killTimer(m_nNoInterNetTimer);
		m_nLoginErrorTimer = startTimer(5000);
	}
	else if (tevent->timerId() == m_nLoginFailedTimer)
	{
		QLabel* pLoginFailedLabel = qFindChild<QLabel*>(m_pLoginWidget,"loginFailedLabel");
		if (pLoginFailedLabel)
		{
			pLoginFailedLabel->show();
		}
		ShowLoging(FALSE);
		killTimer(m_nLoginFailedTimer);
		m_nLoginErrorTimer = startTimer(5000);
	}
	else if (tevent->timerId() == m_nServiceErrorTimer)
	{
		QLabel* pNoServiceLabel = qFindChild<QLabel*>(m_pLoginWidget,"noServiceLabel");
		if (pNoServiceLabel)
		{
			pNoServiceLabel->show();
		}
		ShowLoging(FALSE);
		killTimer(m_nServiceErrorTimer);
		m_nLoginErrorTimer = startTimer(5000);
	}
	else if (tevent->timerId() == m_nMoveTimer)
	{
		if (m_pLogining)
		{
			QRect rc = m_pLogining->geometry();
			int nw = rc.width();
			if (m_bMoveToRight)
			{
				m_pLogining->setGeometry(rc.left() + m_nMoveSpace,rc.top(),nw,rc.height());
				if (rc.left()>m_nMargin)
				{
					m_bMoveToRight = FALSE;
				}
			} 
			else
			{
				m_pLogining->setGeometry(rc.left() - m_nMoveSpace,rc.top(),nw,rc.height());
				if (rc.left()<0 && (-1*rc.left())>m_nMargin)
				{
					m_bMoveToRight = TRUE;
				}
			}
		}
	}
	
}
/************************************************************************/
/*
Event filter
param[in] obj     the object triger the event
param[in] event          
return bool       flag whether the event has be handled
*/
/************************************************************************/
bool CFramelessDialog::eventFilter ( QObject * obj, QEvent * event )
{
	
	if (event->type() == QEvent::MouseMove) 
	{
        QFrame::eventFilter(obj, event);
		return false;
	} 
	 else 
	 {
		 if (QEvent::Resize == event->type())
		 {
			 if (obj == m_pMap)
			 {
				 resizeMap();
				 updateOSD(ANYINDEX);
			 } 
			 else if(obj == m_pRight)
			 {
				  updateOSD(ANYINDEX);
			 }
			 else if (obj == m_pLT)
			 {
				 updateOSD(LTWNDINDEX);
				 if (m_pFuncUpdateVideoWnd && m_pvideoLT)
				 {
					 char szWnd[50]={0};
					 sprintf(szWnd,"0x%08x",(HWND)m_pvideoLT->winId());
					 m_pFuncUpdateVideoWnd(LTWNDINDEX,szWnd);
				 }
			 }
			 else if (obj == m_pLB)
			 {
				 updateOSD(LBWNDINDEX);
				 if (m_pFuncUpdateVideoWnd && m_pvideoLB)
				 {
					 char szWnd[50]={0};
					 sprintf(szWnd,"0x%08x",(HWND)m_pvideoLB->winId());
					 m_pFuncUpdateVideoWnd(LTWNDINDEX,szWnd);
				 }
			 }
			 else if (obj == m_pRT)
			 {
				 updateOSD(RTWNDINDEX);
				 if (m_pFuncUpdateVideoWnd && m_pvideoRT)
				 {
					 char szWnd[50]={0};
					 sprintf(szWnd,"0x%08x",(HWND)m_pvideoRT->winId());
					 m_pFuncUpdateVideoWnd(LTWNDINDEX,szWnd);
				 }
			 }
			 else if (obj == m_pRB)
			 {
				 updateOSD(RBWNDINDEX);
				 if (m_pFuncUpdateVideoWnd && m_pvideoRB)
				 {
					 char szWnd[50]={0};
					 sprintf(szWnd,"0x%08x",(HWND)m_pvideoRB->winId());
					 m_pFuncUpdateVideoWnd(LTWNDINDEX,szWnd);
				 }
			 }
		 } 
		return QFrame::eventFilter(obj, event);
	  }
}
/************************************************************************/
/*
SetAllConnect   connect all the SIGNAL and SLOT
param[in]  none
return     none
*/
/************************************************************************/
void CFramelessDialog::setAllConnect()
{
	
	QPushButton* pCloseBtn = qFindChild<QPushButton*>(m_pChild,"closeBtn");
	QPushButton* pMinBtn = qFindChild<QPushButton*>(m_pChild,"minBtn");
	QPushButton* pMaxBtn = qFindChild<QPushButton*>(m_pChild,"maxBtn");
	QPushButton* pMapBtn = qFindChild<QPushButton*>(m_pChild,"mapBtn");
	QPushButton* pPauseBtn = qFindChild<QPushButton*>(m_pChild,"pauseBtn");
	QPushButton* pOpenBtn = qFindChild<QPushButton*>(m_pChild,"openBtn");
	QPushButton* pFullBtn = qFindChild<QPushButton*>(m_pChild,"fullBtn");
	QPushButton* pSoundBtn = qFindChild<QPushButton*>(m_pChild,"soundBtn");
	//m_pBtnUpdate = qFindChild<QPushButton*>(m_pChild,"updateBtn");
	QWidget* pVolumeBar = qFindChild<QWidget*>(m_pChild,"volumeBar");
	m_pBtnGps = qFindChild<QPushButton*>(m_pChild,"btnGps");
	m_pBtnMax = pMaxBtn;
	//QSplitter* pLRspliter = qFindChild<QSplitter*>(m_pChild,"splitter_left_right");
	connect((const QObject*)pCloseBtn,SIGNAL(clicked()),SLOT(quitApp()));
	connect((const QObject*)pMinBtn,SIGNAL(clicked()),SLOT(showMinimized()));
	connect((const QObject*)pMaxBtn,SIGNAL(clicked()),SLOT(clickMaxBtn()));
	connect((const QObject*)pMapBtn,SIGNAL(clicked()),SLOT(clickedMap()));
	connect((const QObject*)pPauseBtn,SIGNAL(clicked()),SLOT(clickedPlay()));
	connect((const QObject*)pOpenBtn,SIGNAL(clicked()),SLOT(clickedStop()));
	connect((const QObject*)pFullBtn,SIGNAL(clicked()),SLOT(clickedFullScreen()));
	connect((const QObject*)pSoundBtn,SIGNAL(clicked()),SLOT(clickedSound()));
	connect((const QObject*)m_pBtnSet,SIGNAL(clicked()),SLOT(clickSetLanguage()));
	connect((const QObject*)m_pBtnGps,SIGNAL(clicked()),SLOT(clickedGps()));
	connect((const QObject*)m_pBtnUpdate,SIGNAL(clicked()),SLOT(clickedUpdate()));
   // connect((const QObject*)pVolumeBar,SIGNAL(clicked()),SLOT(clickedVolumeBar()));
	//connect((const QObject*)pVolumeBar,SIGNAL(pressed()),SLOT(pressVolumeBar()));
	QPushButton* pSlow = qFindChild<QPushButton*>(m_pChild,"slowBtn");
	QPushButton* pFast = qFindChild<QPushButton*>(m_pChild,"fastBtn");
	QSlider* pProgress = qFindChild<QSlider*>(m_pChild,"timeSlider");
	m_pTotalTime = qFindChild<QLabel*>(m_pChild,"totalTimeLabel");
	m_pCurTime = qFindChild<QLabel*>(m_pChild,"curTimeLabel");
	connect((const QObject*)pSlow,SIGNAL(clicked()),SLOT(clickedSlow()));
	connect((const QObject*)pFast,SIGNAL(clicked()),SLOT(clickedFast()));
    connect((const QObject*)pProgress,SIGNAL(actionTriggered(int)),SLOT(progressBarAction(int)));
    connect((const QObject*)pProgress,SIGNAL(sliderMoved(int)),SLOT(progressBarMoved(int)));
	connect((const QObject*)pProgress,SIGNAL(sliderReleased()),SLOT(progressBarReleased()));
	QComboBox* pcombox = qFindChild<QComboBox*>(m_pChild,"comboBox");
	//connect((const QObject*)pcombox,SIGNAL(currentIndexChanged(int)),SLOT(openModeChange(int)));
	connect((const QObject*)pcombox,SIGNAL(activated(int)),SLOT(openModeActivated(int)));//highlighted
	//connect((const QObject*)pcombox,SIGNAL(highlighted(int)),SLOT(openModeClicked(int)));
   // connect((const QObject*)m_psystemTray,SIGNAL(messageClicked()),SLOT(clickTrayIcon()));
	connect((const QObject*)m_psystemTray,SIGNAL(activated( QSystemTrayIcon::ActivationReason)),SLOT(activedTrayIcon(QSystemTrayIcon::ActivationReason)));
	//connect((const QObject*)this,SIGNAL(newGps(int,int,int,int,long,int )),SLOT(showGps(int,int,int,int,long,int)));
	connect((const QObject*)this,SIGNAL(newPrivateInfo(int,int)),SLOT(updatePrivateInfo(int,int)));
	connect((const QObject*)this,SIGNAL(nextItem(int,int)),SLOT(PlayNextItem(int,int)));
	//connect((const QObject*)this,SIGNAL(clearloc()),SLOT(clearGps()));
	connect((const QObject*)this,SIGNAL(extendInfo(int,const char*,const char*)),SLOT(showExtend(int,const char*,const char*)));
	connect((const QObject*)this,SIGNAL(updateInfo()),SLOT(showUpdate()));
	connect((const QObject*)this,SIGNAL(newTsFile()),SLOT(playNewTsFile()));
	if (pPauseBtn)
	{
		m_strStylePlay = pPauseBtn->styleSheet();
		m_strStylePause = m_strStylePlay + m_strStylePause;
		m_pBtnPlay = pPauseBtn;
	}
	if (m_pBtnGps)
	{
		m_strStyleExtend = m_pBtnGps->styleSheet();

	}
	if (m_pBtnMax)
	{
		m_strStyleMax = m_pBtnMax->styleSheet();
	}
	if (pSoundBtn)
	{
		m_strStyleVolume1 = pSoundBtn->styleSheet();
		m_strStyleVolume0 = m_strStyleVolume1 + m_strStyleVolume0;
		m_strStyleVolume2 = m_strStyleVolume1 + m_strStyleVolume2;
		m_strStyleVolume3 = m_strStyleVolume1 + m_strStyleVolume3;
		m_pBtnVolume = pSoundBtn;
	}
	if (pVolumeBar)
	{
		m_pVolumeBar = pVolumeBar;
		m_nVolumeWidth = pVolumeBar->width();
		QRect rc = m_pVolumeBar->geometry();
		m_pVolumeBar->setGeometry(rc.left(),rc.top(),m_iVolumeLT/2,rc.height());
	}
	
	//connect(m_pTrayMenu,SIGNAL(triggered ( QAction *)),SLOT(trigerExitMenu(QAction*)));
	connect(m_pLanguageMenu,SIGNAL(triggered ( QAction *)),SLOT(trigerLanguageMenu(QAction*)));
	QWidget* widget_6 = qFindChild<QWidget*>(m_pChild,"topframe");
	if(widget_6)
	{
		widget_6->installEventFilter(this);
	}
	QWidget* frameUpdate = qFindChild<QWidget*>(m_pChild,"frameUpdateInfo");
	if (frameUpdate)
	{
		frameUpdate->setMouseTracking(true);
		frameUpdate->installEventFilter(this);
	}
	QWidget* widget_8 = qFindChild<QWidget*>(m_pChild,"widget_4");
	if(widget_8)
	{
		widget_8->installEventFilter(this);
	}
	
	if (m_pRight)
	{
		m_pRight->installEventFilter(this);
	}
	QWidget* widget_left = qFindChild<QWidget*>(m_pChild,"leftWidget");
	if (widget_left)
	{
		widget_left->installEventFilter(this);
	}
	QWidget* plist = qFindChild<QWidget*>(m_pChild,"list");
	if (plist)
	{
		plist->installEventFilter(this);
		plist->setMouseTracking(true);
	}
    QLayout* pLay = NULL;
	if (m_pTableList)
	{
		m_pTableList->installEventFilter(this);
		QHeaderView * phead = m_pTableList->horizontalHeader();
		if (phead)
		{
			phead->setMouseTracking(true);
			phead->installEventFilter(this);
			connect((const QObject*)m_pTableList,SIGNAL(viewportEntered()),SLOT(tableViewPortEnter()));
			connect((const QObject*)m_pTableList,SIGNAL(entered(const QModelIndex &)),SLOT(tableItemEnter(const QModelIndex &)));
			connect((const QObject*)phead,SIGNAL(entered(const QModelIndex &)),SLOT(tableItemEnter(const QModelIndex &)));
            connect((const QObject*)m_pTableList,SIGNAL(cellDoubleClicked(int,int)),SLOT(cellClicked(int,int)));
		}
		pLay = m_pTableList->layout();
	}

	pLay = qFindChild<QLayout*>(widget_left,"sdkfileLayout");
	if (pLay)
	{
		pLay->installEventFilter(this);
		
	}
	if (m_pMap)
	{
		m_pMap->installEventFilter(this);
	}
	QWidget* pSpliter = qFindChild<QWidget*>(m_pChild,"splitter_map_table");
	if (pSpliter)
	{
		pSpliter->setMouseTracking(true);
		pSpliter->installEventFilter(this);
		connect((const QObject*)pSpliter,SIGNAL(splitterMoved(int,int)),SLOT(moveMapFileSpliter(int,int)));
	}	
	if (m_pNameLabel)
	{
        m_pNameLabel->setMouseTracking(true);
		m_pNameLabel->installEventFilter(this);
	}
	if (m_pBtnUpdate)
	{
		m_pBtnUpdate->setMouseTracking(true);
		m_pBtnUpdate->installEventFilter(this);
	}
	QWidget* pR = qFindChild<QWidget*>(m_pChild,"rightWidget");
	QSplitter* p =(QSplitter*) pR->parent();
	if(p)
	{
		connect((const QObject*)p,SIGNAL(splitterMoved(int,int)),SLOT(moveLeftRightSpliter(int,int)));
	}
	if (0 == m_nTimeID)
	{
		m_nTimeID = startTimer(10000);
	}
    if (m_pBtnUpdate && m_bShowUpdate)
    {
		m_pBtnUpdate->show();
    }
	HANDLE hUpdate = ::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadCheckUpdate,NULL,0,NULL);
	CloseHandle(hUpdate);
    //HANDLE hCheckFile = ::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadCheckPlayFile,NULL,0,NULL);
	//CloseHandle(hCheckFile);
	CThreadCheckFile * pThreadCheck = CThreadCheckFile::GetInstance(NULL);
	if (pThreadCheck)
	{
		pThreadCheck->start();
	}
	m_bSetConnect = TRUE;
	//start the CEIECMediaPlayer.exe
	QString strTs("error.ts");
	createVideo(LTWNDINDEX,strTs);
	if (m_pvideoLT)
	{
		if (m_pFuncSetCustomFlag)
		{
			m_pFuncSetCustomFlag(LTWNDINDEX,CUSTOMFLAG);
		}
		if (m_pFuncParaFileList)
		{
			strTs = "http://0.0.0.0/error.ts,180";
			char szWnd[50]={0};
			sprintf(szWnd,"0x%08x",(HWND)m_pvideoLT->winId());
			
			m_pFuncParaFileList(strTs.toStdWString().c_str(),LTWNDINDEX,szWnd);
		}
	}
	
}
/************************************************************************/
/*
createBkVideo  load the video.ui for all the video window.
create one CFullVideo for each video window in video.ui.
it has both video widget for OCX and widget for video from device factory,
in each CFullVideo window.
param[in]  none
return     none
*/
/************************************************************************/
void CFramelessDialog::createBkVideo()
{
	QWidget* qpic = qFindChild<QWidget*>(m_pChild,"bkpic");
	if (qpic)
	{
		m_pRight = qpic;
		QUiLoader loader;
		QString curPath = QCoreApplication::applicationDirPath()+DIR+UIPATH+DIR+"video.ui";
		QFile file(curPath);
		file.open(QFile::ReadOnly);
		QWidget* pvideo = loader.load(&file,qpic);
		if (pvideo)
		{
			m_pvideoBk = pvideo;
			m_pRight->setMouseTracking(true);
			m_pRight->installEventFilter(this);
			m_pvideoBk->setMouseTracking(true);
			m_pvideoBk->installEventFilter(this);
		}
		m_pPLeft = qFindChild<QWidget*>(m_pvideoBk,"videoLeft");
		m_pPRight = qFindChild<QWidget*>(m_pvideoBk,"videoRight");
		QWidget* pvLT = qFindChild<QWidget*>(m_pvideoBk,"videoLT");
		if (pvLT)
		{
			m_pPLT = pvLT;
			m_pLT = new CFullVideo(1,pvLT);
			QLayout* pLayLT = pvLT->layout();
			if (pLayLT && m_pLT)
			{
				pLayLT->addWidget(m_pLT);
			}
		}

		QWidget* pvRT = qFindChild<QWidget*>(m_pvideoBk,"videoRT");
		if (pvRT)
		{
			m_pPRT = pvRT;
			m_pRT = new CFullVideo(2,pvRT);
			QLayout* pLayRT = pvRT->layout();
			if (pLayRT && m_pRT)
			{
				pLayRT->addWidget(m_pRT);
			}
		}

		QWidget* pvLB = qFindChild<QWidget*>(m_pvideoBk,"videoLB");
		if (pvLB)
		{
			m_pPLB = pvLB;
			m_pLB = new CFullVideo(4,pvLB);
			QLayout* pLayLB = pvLB->layout();
			if (pLayLB && m_pLB)
			{
				pLayLB->addWidget(m_pLB);
			}
		}

		QWidget* pvRB = qFindChild<QWidget*>(m_pvideoBk,"videoRB");
		if (pvRB)
		{
			m_pPRB = pvRB;
			m_pRB = new CFullVideo(8,pvRB);
			QLayout* pLayRB = pvRB->layout();
			if (pLayRB && m_pRB)
			{
				pLayRB->addWidget(m_pRB);
			}
		}
		QWidget* video = qFindChild<QWidget*>(m_pvideoBk,"video");
		if (video)
		{
			video->installEventFilter(this);
			//m_strStyleVideoFrame = video->styleSheet();
			m_pCurFull = m_pLT;
			if (m_pLT && m_pRT && m_pRB && m_pLB)
			{
				m_pLT->setObjectName("videoLT");
				m_pRT->setObjectName("videoRT");
				m_pLB->setObjectName("videoLB");
				m_pRB->setObjectName("videoRB");

				m_pRT->setMouseTracking(true);
				m_pLT->setMouseTracking(true);
				m_pLB->setMouseTracking(true);
				m_pRB->setMouseTracking(true);
				m_pLT->installEventFilter(this);
				m_pRT->installEventFilter(this);
				m_pRB->installEventFilter(this);
				m_pLB->installEventFilter(this);
				
			}
			
		}
	
		QVBoxLayout* lLT = new QVBoxLayout;
		QVBoxLayout* lRT = new QVBoxLayout;
		QVBoxLayout* lLB = new QVBoxLayout;
		QVBoxLayout* lRB = new QVBoxLayout;
		if (lLT)
		{
			lLT->setContentsMargins(0,0,0,0);
		}
		if (lRT)
		{
			lRT->setContentsMargins(0,0,0,0);
		}
		if (lLB)
		{
			lLB->setContentsMargins(0,0,0,0);
		}
		if (lRB)
		{
			lRB->setContentsMargins(0,0,0,0);
		}
		
		if (m_pLT)
		{
			m_pLT->setLayout(lLT);
		}
		if (m_pRT)
		{
			m_pRT->setLayout(lRT);
		}
		if (m_pLB)
		{
			m_pLB->setLayout(lLB);
		}
		if (m_pRB)
		{
			m_pRB->setLayout(lRB);
		}
        if (m_pFuncSetEventCallBack)
        {
			m_pFuncSetEventCallBack((LONG_PTR)OnEventCallBack);
        }
	
	}
}
/************************************************************************/
/*
Create widget for containing OCX
param[in] 
iWndIndex     
          1:left top 
		  2:right top
		  3:left botto
		  4:right bottom
param[in] strFileName    the *.ts file name
return    none
*/
/************************************************************************/
void CFramelessDialog::createVideo(int iWndIndex,QString & strFileName)
{
	if (!m_pvideoBk)
	{
		createBkVideo();
	}
	//return;
	BOOL bJN = FALSE;
	if (strFileName.contains(JNPREFIX)/* || strFileName.contains(WKPPREFIX)*/)
	{
		bJN = TRUE;
	}
	if (bJN)
	{
		switch(iWndIndex)
		{
		case LTWNDINDEX:
			{
				if (!m_pvideoLT)
				{
					m_pvideoLT = new QWidget(m_pLT);
					if (m_pvideoLT)
					{
						m_pvideoLT->setMouseTracking(true);
						m_pvideoLT->installEventFilter(this);
					}
					if (m_pWWANRLevelLT)
					{
						m_pWWANRLevelLT->close();
						delete m_pWWANRLevelLT;
						m_pWWANRLevelLT = NULL;
					}
					if (m_pGpsLT)
					{
						m_pGpsLT->close();
						delete m_pGpsLT;
						m_pGpsLT = NULL;
					}
					QLabel* plabel = new QLabel(CLanguage::strSignal,m_pLT);
					if (plabel)
					{
						plabel->setWindowFlags(Qt::WindowStaysOnTopHint);
						plabel->setStyleSheet(m_strStyleOSD);
						m_pWWANRLevelLT = plabel;
					}
					QLabel* plabelGps = new QLabel(CLanguage::strGps,m_pLT);
					if (plabelGps)
					{
						plabelGps->setWindowFlags(Qt::WindowStaysOnTopHint);
						plabelGps->setStyleSheet(m_strStyleOSD);
						m_pGpsLT = plabelGps;
					}
					QVBoxLayout* lLT = (QVBoxLayout*)m_pLT->layout();
					if (lLT)
					{
						lLT->addWidget(m_pvideoLT);
					}
					
				}
				break;
			}
		case LBWNDINDEX:
			{
				if (!m_pvideoLB)
				{
					m_pvideoLB = new QWidget(m_pLB);
					if (m_pWWANRLevelLB)
					{
						m_pWWANRLevelLB->close();
						delete m_pWWANRLevelLB;
						m_pWWANRLevelLB = NULL;
					}
					if (m_pGpsLB)
					{
						m_pGpsLB->close();
						delete m_pGpsLB;
						m_pGpsLB = NULL;
					}
					QLabel* plabel = new QLabel(CLanguage::strSignal,m_pLB);
					if (plabel)
					{
						plabel->setWindowFlags(Qt::WindowStaysOnTopHint);
						plabel->setStyleSheet(m_strStyleOSD);
                        //plabel->hide();
						m_pWWANRLevelLB = plabel;
					}
					QLabel* plabelGps = new QLabel(CLanguage::strGps,m_pLB);
					if (plabelGps)
					{
						plabelGps->setWindowFlags(Qt::WindowStaysOnTopHint);
						plabelGps->setStyleSheet(m_strStyleOSD);
						//plabelGps->hide();
						m_pGpsLB = plabelGps;
					}
					
					QVBoxLayout* lLB = (QVBoxLayout*)m_pLB->layout();
					if (lLB)
					{
						lLB->addWidget(m_pvideoLB);
					}
					
				}
				break;
			}
		case RTWNDINDEX:
			{
				if (!m_pvideoRT)
				{
					m_pvideoRT = new QWidget(m_pRT);
					if (m_pWWANRLevelRT)
					{
						m_pWWANRLevelRT->close();
						delete m_pWWANRLevelRT;
						m_pWWANRLevelRT = NULL;
					}
					if (m_pGpsRT)
					{
						m_pGpsRT->close();
						delete m_pGpsRT;
						m_pGpsRT = NULL;
					}
					QLabel* plabel = new QLabel(CLanguage::strSignal,m_pRT);
					if (plabel)
					{
						plabel->setWindowFlags(Qt::WindowStaysOnTopHint);
						plabel->setStyleSheet(m_strStyleOSD);
						m_pWWANRLevelRT = plabel;
						//plabel->hide();
					}
					QLabel* plabelGps = new QLabel(CLanguage::strGps,m_pRT);
					if (plabelGps)
					{
						plabelGps->setWindowFlags(Qt::WindowStaysOnTopHint);
						plabelGps->setStyleSheet(m_strStyleOSD);
						m_pGpsRT = plabelGps;
						//plabelGps->hide();
					}
					QVBoxLayout* lRT = (QVBoxLayout*)m_pRT->layout();
					if (lRT)
					{
						lRT->addWidget(m_pvideoRT);
					}					
				}
				break;
			}
		case RBWNDINDEX:
			{
				if (!m_pvideoRB)
				{
					m_pvideoRB = new QWidget(m_pRB);
					if (m_pWWANRLevelRB)
					{
						m_pWWANRLevelRB->close();
						delete m_pWWANRLevelRB;
						m_pWWANRLevelRB = NULL;
					}
					if (m_pGpsRB)
					{
						m_pGpsRB->close();
						delete m_pGpsRB;
						m_pGpsRB = NULL;
					}
					QLabel* plabel = new QLabel(CLanguage::strSignal,m_pRB);
					if (plabel)
					{
						plabel->setWindowFlags(Qt::WindowStaysOnTopHint);
						plabel->setStyleSheet(m_strStyleOSD);
						m_pWWANRLevelRB = plabel;
						//plabel->hide();
					}
					QLabel* plabelGps = new QLabel(CLanguage::strGps,m_pRB);
					if (plabelGps)
					{
						plabelGps->setWindowFlags(Qt::WindowStaysOnTopHint);
						plabelGps->setStyleSheet(m_strStyleOSD);
						m_pGpsRB= plabelGps;
						//plabelGps->hide();
					}
					QVBoxLayout* lRB = (QVBoxLayout*)m_pRB->layout();
					if (lRB)
					{
						lRB->addWidget(m_pvideoRB);
					}
					
				}
				break;
			}
		default:
			{
				break;
			}
		}
	} 
	
}
/************************************************************************/
/*
setEventFilterGpsAndWWanrx
let's the widgets used to show the signal and gps info don't get
the mouse event.
param[in] none
return    none
*/
/************************************************************************/
void CFramelessDialog::setEventFilterGpsAndWWanrx()
{
	if (m_pWWANRLevelLT)
	{
		m_pWWANRLevelLT->setMouseTracking(true);
		m_pWWANRLevelLT->installEventFilter(this);
	}
	if (m_pGpsLT)
	{
		m_pGpsLT->setMouseTracking(true);
		m_pGpsLT->installEventFilter(this);
	}
	if (m_pWWANRLevelRT)
	{
		m_pWWANRLevelRT->setMouseTracking(true);
        m_pWWANRLevelRT->installEventFilter(this);
	}
	if (m_pGpsRT)
	{
		m_pGpsRT->setMouseTracking(true);
		m_pGpsRT->installEventFilter(this);
	}
	if (m_pWWANRLevelLB)
	{
		m_pWWANRLevelLB->setMouseTracking(true);
		m_pWWANRLevelLB->installEventFilter(this);
	}
	if (m_pGpsLB)
	{
		m_pGpsLB->setMouseTracking(true);
		m_pGpsLB->installEventFilter(this);
	}
	if (m_pWWANRLevelRB)
	{
		m_pWWANRLevelRB->setMouseTracking(true);
		m_pWWANRLevelRB->installEventFilter(this);
	}
	if (m_pGpsRB)
	{
		m_pGpsRB->setMouseTracking(true);
		m_pGpsRB->installEventFilter(this);
	}
	
}
/************************************************************************/
/*
createDllVideo  create all widgets to contain the video window for
play video from factory device via their SDK
param[in] none
return    none
*/
/************************************************************************/
void CFramelessDialog::createDllVideo()
{

	if (!m_pvideoBk)
	{
		createBkVideo();
	}
	
	if (!m_pdllVideoLT)
	{
		m_pdllVideoLT = new  QWidget(m_pLT);
		QVBoxLayout* lLT = (QVBoxLayout*)m_pLT->layout();
		if (lLT && m_pdllVideoLT)
		{
			m_pdllVideoLT->setMouseTracking(true);
			m_pdllVideoLT->installEventFilter(this);
			lLT->addWidget(m_pdllVideoLT);
			if (!m_pWWANRLevelLT)
			{
				QLabel* plabel = new QLabel(CLanguage::strSignal,m_pLT);
				plabel->setWindowFlags(Qt::WindowStaysOnTopHint);
				plabel->setStyleSheet(m_strStyleOSD);
				//plabel->hide();
				m_pWWANRLevelLT = plabel;
			}
			if (!m_pGpsLT)
			{
				QLabel* plabel = new QLabel(CLanguage::strGps,m_pLT);
				plabel->setWindowFlags(Qt::WindowStaysOnTopHint);
				plabel->setStyleSheet(m_strStyleOSD);
				//plabel->hide();
				m_pGpsLT = plabel;	
			}
		}
	}
	if (!m_pdllVideoLB)
	{
		m_pdllVideoLB = new QWidget(m_pLB);
		QVBoxLayout* lLB = (QVBoxLayout*)m_pLB->layout();
		if (lLB && m_pdllVideoLB)
		{
			m_pdllVideoLB->setMouseTracking(true);
			m_pdllVideoLB->installEventFilter(this);
			lLB->addWidget(m_pdllVideoLB);
			if (!m_pWWANRLevelLB)
			{
				QLabel* plabel = new QLabel(CLanguage::strSignal,m_pLB);
				plabel->setWindowFlags(Qt::WindowStaysOnTopHint);
				plabel->setStyleSheet(m_strStyleOSD);
				//plabel->hide();
				m_pWWANRLevelLB = plabel;
			}
			if (!m_pGpsLB)
			{
				QLabel* plabel = new QLabel(CLanguage::strGps,m_pLB);
				plabel->setWindowFlags(Qt::WindowStaysOnTopHint);
				plabel->setStyleSheet(m_strStyleOSD);
				//plabel->hide();
				m_pGpsLB = plabel;
			}
		}
	}

	if (!m_pdllVideoRT)
	{
		m_pdllVideoRT = new QWidget(m_pRT);
		QVBoxLayout* lRT = (QVBoxLayout*)m_pRT->layout();
		if (lRT && m_pdllVideoRT)
		{
			m_pdllVideoRT->setMouseTracking(true);
			m_pdllVideoRT->installEventFilter(this);
			lRT->addWidget(m_pdllVideoRT);
			if (!m_pWWANRLevelRT)
			{
				QLabel* plabel = new QLabel(CLanguage::strSignal,m_pRT);
				plabel->setWindowFlags(Qt::WindowStaysOnTopHint);
				plabel->setStyleSheet(m_strStyleOSD);
				//plabel->hide();
				m_pWWANRLevelRT = plabel;
				
			}
			if (!m_pGpsRT)
			{
				QLabel* plabel = new QLabel(CLanguage::strGps,m_pRT);
				plabel->setWindowFlags(Qt::WindowStaysOnTopHint);
				plabel->setStyleSheet(m_strStyleOSD);
				//plabel->hide();
				m_pGpsRT = plabel;

			}
		}
	}

	if (!m_pdllVideoRB)
	{
		m_pdllVideoRB = new QWidget(m_pRB);
		QVBoxLayout* lRB = (QVBoxLayout*)m_pRB->layout();
		if (lRB && m_pdllVideoRB)
		{
			m_pdllVideoRB->installEventFilter(this);
			m_pdllVideoRB->setMouseTracking(true);
			lRB->addWidget(m_pdllVideoRB);
			if (!m_pWWANRLevelRB)
			{
				QLabel* plabel = new QLabel(CLanguage::strSignal,m_pRB);
				plabel->setWindowFlags(Qt::WindowStaysOnTopHint);
				plabel->setStyleSheet(m_strStyleOSD);
				//plabel->hide();
				m_pWWANRLevelRB = plabel;
			}
			if (!m_pGpsRB)
			{
				QLabel* plabel = new QLabel(CLanguage::strGps,m_pRB);
				plabel->setWindowFlags(Qt::WindowStaysOnTopHint);
				plabel->setStyleSheet(m_strStyleOSD);
				//plabel->hide();
				m_pGpsRB = plabel;
			}
		}
	}
	if (m_vtPluginInterface.size()<1)
	{
		if(m_pdllVideoLT)
		{
			m_hPlayWnd[0] = (unsigned int)m_pdllVideoLT->winId();
		}
        if (m_pdllVideoRT)
        {
			m_hPlayWnd[1] = (unsigned int)m_pdllVideoRT->winId();
        }
		if(m_pdllVideoLB)
		{
			m_hPlayWnd[2] = (unsigned int)m_pdllVideoLB->winId();
		}
		if (m_pdllVideoRB)
		{
			m_hPlayWnd[3] = (unsigned int)m_pdllVideoRB->winId();
		}
		m_nMaxChannel = 4;
		LANGID langID = GetSystemDefaultLangID();
		SetLangID( langID & 0x00FF);
		LoadDLLs();
		CreatePluginInterface();

		AllSDK_Init();

		AllSDK_Config_SetVideoHWND(this,m_hPlayWnd,m_nMaxChannel);

		AllSDK_Config_SetCallBackExtraData(ANTSDK_REALDATACALLBACK);

		QString strOldMoudle = QCoreApplication::applicationDirPath()+DIR;
		SetCurrentDirectoryA(strOldMoudle.toStdString().c_str());
	}
}
/************************************************************************/
/*
createMainPage
   load the mainWindow of the program from vehiclevideoplayer.ui
   load mapDll
   show it in the middle of the screen
param[in]  none
return     none
*/
/************************************************************************/
void CFramelessDialog::createMainPage()
{
	QUiLoader loader;
	QString curPath = QCoreApplication::applicationDirPath()+DIR+UIPATH+DIR+"vehiclevideoplayer.ui";
	QFile file(curPath);
	
	if (!file.open(QFile::ReadOnly))
	{
		return;
	}
	
	QWidget* form = loader.load(&file,this);
	
	QWidget* p1 = qFindChild<QWidget*>(form,"Form");
	QWidget* p2 = qFindChild<QWidget*>(form,"splitter_map_table");
	QWidget* pweb = qFindChild<QWidget*>(form,"web");
	file.close();
	
	CLanguage::ReadTxtByUi(form,"vehiclevideoplayer");
	
	if (QLocale::Chinese == CLanguage::m_langId)
	{
		CLanguage::ReadTxtByUi(form,"vehiclevideoplayer",TRUE);
	}
	CLanguage::ReadTxtByUi(this,"other");
	if (QLocale::Chinese == CLanguage::m_langId)
	{
		CLanguage::ReadTxtByUi(this,"other",TRUE);
	}
	
	if (pweb)
	{
		form->setWindowFlags(Qt::FramelessWindowHint);
		m_pMap = pweb;
	}
	else
	{
		QMessageBox::warning(NULL,"no web","can't find web");
	}
	
	QSlider* pSlider = qFindChild<QSlider*>(form,"timeSlider");
	if (pSlider)
	{
		m_pProgress = pSlider;
		pSlider->setEnabled(false);
	}
	m_pBtnUpdate = qFindChild<QPushButton*>(form,"btnUpdate");
	if (m_pBtnUpdate)
	{
		m_pBtnUpdate->hide();
	}
	QComboBox* pcombox = qFindChild<QComboBox*>(form,"comboBox");
	if (pcombox)
	{
		m_pOpenCombox = pcombox;
		pcombox->addItem("Open Download Files");
		pcombox->addItem("Open SD Card");
		pcombox->addItem("Open Direction");
		pcombox->setCurrentIndex(0);
		QAbstractItemView* pList = pcombox->view();
		if (pList)
		{
			pList->setStyleSheet("{background-color:rgb(52,52,52)}");
		}
	}
   
	m_pBtnSet = qFindChild<QPushButton*>(form,"btnSet");
	QLabel* pNameLable = qFindChild<QLabel*>(form,"fileNameLabel");
	if (pNameLable)
	{
		m_pNameLabel = pNameLable;
	}
    gMin = form->width();
	int nWidth = form->width()+100;
	int nHeight = form->height();
	 m_pChild = form;
	 
	createFileListTable();
	createLanguageMenu();
	m_pTopLay = new QVBoxLayout;
	if (m_pTopLay)
	{
		m_pTopLay->addWidget(form);
		setLayout(m_pTopLay);
		m_pTopLay->setContentsMargins(0,0,0,0);
	}
	switch(CLogin::eNetType)
	{
	case DataCenterInner:
		{
			m_strMapUrl = m_strMapDCI;
			m_strUpdateUrl = m_strUpdateDCI;
			break;
		}
	case DataCenterExter:
		{
			m_strMapUrl = m_strMapDCE;
			m_strUpdateUrl = m_strUpdateDCE;
			break;
		}
	case BackupCenterInner:
		{
			m_strMapUrl = m_strMapBCI;
			m_strUpdateUrl = m_strUpdateBCI;
			break;
		}
	case BackupCenterExter:
		{
			m_strMapUrl = m_strMapBCE;
			m_strUpdateUrl = m_strUpdateBCE;
			break;
		}
	default:
		{
			m_strMapUrl = m_strMapDCI;
			m_strUpdateUrl = m_strUpdateDCI;
			break;
		}
	}
	QDesktopWidget* pdesk = QApplication::desktop();
	int nx = 0;
	int ny = 0;
	if (pdesk)
	{
		int nIndex = pdesk->screenNumber();
		QRect rcScreen = pdesk->screenGeometry(nIndex);
		nx = (rcScreen.width()-nWidth)/2;//(pdesk->width()-nWidth)/2;
		ny = (rcScreen.height()-nHeight)/2;//(pdesk->height()-nHeight)/2;
	}
	if (nx <0)
	{
		nx = 0;
	}
	if (ny < 0)
	{
		ny = 0;
	}
	CLanguage::GetSignalText();
	setGeometry(nx,ny,nWidth,nHeight);
	CLanguage::UpdatePageLanguage(form);
	CLanguage::UpdateMenuComboBoxText();
	
	setMouseTracking(true);
	form->setMouseTracking(true);
	createDllVideo();
	showVideo(TRUE);
	showOpen();
	
	QString strOldMoudle = QCoreApplication::applicationDirPath()+DIR;
	QString strNewMoudle = QCoreApplication::applicationDirPath()+DIR+"controlPlugin";
	SetCurrentDirectoryA(strNewMoudle.toStdString().c_str());
	CDllFunc::LoadMapPlugin();
	if (CDllFunc::m_pFunCreateMap)
	{
		HWND pHwndMap = 0;
		(*CDllFunc::m_pFunCreateMap)((HWND)pweb->winId(),&pHwndMap,eOfflinePlay);
		if (CDllFunc::m_pFunMoveMap)
		{
			QRect mapRc = pweb->geometry();
			(*CDllFunc::m_pFunMoveMap)(0,0,mapRc.width(),mapRc.height(),eOfflinePlay);
		}
		if (CDllFunc::m_pFunGoToPage)
		{
			(*CDllFunc::m_pFunGoToPage)(m_strMapUrl.toStdString().c_str(),eOfflinePlay);
		}

	}
  
	SetCurrentDirectoryA(strOldMoudle.toStdString().c_str());
	
	QWidget* pLeftWidget = qFindChild<QWidget*>(form,"leftWidget");
	if (pLeftWidget)
	{
		pLeftWidget->hide();
	}
	show();
}
/************************************************************************/
/*
createFileListTable
   create the table used to show the video info
param[in]   none
return      none
*/
/************************************************************************/
void CFramelessDialog::createFileListTable()
{
	QTableWidget *table = qFindChild<QTableWidget*>(m_pChild,"fileList");
	if (!table)
	{
		return;
	}
	QItemEditorFactory *factory = new QItemEditorFactory;

	QItemEditorCreatorBase *windowListCreator =new QStandardItemEditorCreator<WindowListEditor>();

	factory->registerEditor(QVariant::String, windowListCreator);

	QItemEditorFactory::setDefaultFactory(factory);
	//QItemEditorFactory::setDefaultFactory(NULL);
	table->setColumnCount(4);
	table->setHorizontalHeaderLabels(QStringList() << m_strCol1Caption
		//<< m_strCol2Caption
		<< m_strCol3Caption
		<< m_strCol4Caption
		<<""
		);
	table->verticalHeader()->setVisible(false);
	table->setColumnWidth(0,100);
	table->horizontalHeader()->setStretchLastSection(true);  
    table->setSelectionBehavior(QAbstractItemView::SelectRows);    
	m_pTableList = table;

}
/************************************************************************/
/*
showVideo
      show the current video windows which choose to play the video
      could be any combination of all the four video windows,like
      only show one of them,
      show any two of them,
      show any three of them.
param[in] bShow
      bShow = TRUE  show any combination of the windows
	  bShow = FALSE hide all the windows
return    none
*/
/************************************************************************/
void CFramelessDialog::showVideo(BOOL bShow)
{
	if (m_pLT && m_pRT && m_pLB && m_pRB)
	{
		if (m_bSDK)
		{
			if (bShow)
			{
				if (m_pCurFull && TRUE == m_pCurFull->m_bFull)
				{
					switch(m_nChannelFlag)
					{
					case 1:
						{
							if (m_pPLeft)
							{
								m_pPLeft->show();
							}
							if (m_pPRight)
							{
								m_pPRight->hide();
							}
							if (m_pPLT)
							{
								m_pPLT->show();
							}
							if (m_pPRT)
							{
								m_pPRT->hide();
							}
							if (m_pPLB)
							{
								m_pPLB->hide();
							}
							if (m_pPRB)
							{
								m_pPRB->hide();
							}
							break;
						}
					case 2:
						{
							if (m_pPLeft)
							{
								m_pPLeft->hide();
							}
							if (m_pPRight)
							{
								m_pPRight->show();
							}
							if (m_pPLT)
							{
								m_pPLT->hide();
							}
							if (m_pPRT)
							{
								m_pPRT->show();
							}
							if (m_pPLB)
							{
								m_pPLB->hide();
							}
							if (m_pPRB)
							{
								m_pPRB->hide();
							}
							break;
						}
					case 4:
						{
							if (m_pPLeft)
							{
								m_pPLeft->show();
							}
							if (m_pPRight)
							{
								m_pPRight->hide();
							}
							if (m_pPLT)
							{
								m_pPLT->hide();
							}
							if (m_pPRT)
							{
								m_pPRT->hide();
							}
							if (m_pPLB)
							{
								m_pPLB->show();
							}
							if (m_pPRB)
							{
								m_pPRB->hide();
							}
							break;
						}
					case 8:
						{
							if (m_pPLeft)
							{
								m_pPLeft->hide();
							}
							if (m_pPRight)
							{
								m_pPRight->show();
							}
							if (m_pPLT)
							{
								m_pPLT->hide();
							}
							if (m_pPRT)
							{
								m_pPRT->hide();
							}
							if (m_pPLB)
							{
								m_pPLB->hide();
							}
							if (m_pPRB)
							{
								m_pPRB->show();
							}
							break;
						}
					default:
						{
							break;
						}
					}
					return;
				}
				int nTotal = 0;
				if (m_nChannelFlag & 1)
				{
					nTotal++;
				}
				if (m_nChannelFlag & 2)
				{
					nTotal++;
				}
				if (m_nChannelFlag & 4)
				{
					nTotal++;
				}
				if (m_nChannelFlag & 8)
				{
					nTotal++;
				}
				if (nTotal>=1)
				{
					if (m_pPLeft)
					{
						m_pPLeft->show();
					}
				}
				else
				{
					if (m_pPLeft)
					{
						m_pPLeft->hide();
					}
				}
				if (nTotal>=2)
				{
					if (m_pPRight)
					{
						m_pPRight->show();
					}
				} 
				else
				{
					if (m_pPRight)
					{
						m_pPRight->hide();
					}
				}
				if (nTotal > 0 )
				{
					if (m_pPLT)
					{
						m_pPLT->show();
					}
					m_pLT->show();
					
					if (m_pdllVideoLT)
					{
						m_pdllVideoLT->show();
					}
				}
				else
				{
					if (m_pPLT)
					{
						m_pPLT->hide();
					}
					m_pLT->hide();
					if (m_pdllVideoLT)
					{
						m_pdllVideoLT->hide();
					}
				}

				if (nTotal > 1)
				{
					if (m_pPRT)
					{
						m_pPRT->show();
					}
					m_pRT->show();
					if (m_pdllVideoRT)
					{
						m_pdllVideoRT->show();
					}
				} 
				else
				{
					if (m_pPRT)
					{
						m_pPRT->hide();
					}
					m_pRT->hide();
					if (m_pdllVideoRT)
					{
						m_pdllVideoRT->hide();
					}
				}
				if(nTotal > 2)
				{
					if (m_pPLB)
					{
						m_pPLB->show();
					}
					m_pLB->show();
					if (m_pdllVideoLB)
					{
						m_pdllVideoLB->show();
					}
				}
				else
				{
					if (m_pPLB)
					{
						m_pPLB->hide();
					}
					m_pLB->hide();
					if (m_pdllVideoLB)
					{
						m_pdllVideoLB->hide();
					}
				}
				if(nTotal > 3)
				{
					if (m_pPRB)
					{
						m_pPRB->show();
					}
					m_pRB->show();
					if (m_pdllVideoRB)
					{
						m_pdllVideoRB->show();
					}
				}
				else
				{
					if (m_pPRB)
					{
						m_pPRB->hide();
					}
					m_pRB->hide();
					if (m_pdllVideoRB)
					{
						m_pdllVideoRB->hide();
					}
				}
				
				if (m_pvideoLT)
				{
					m_pvideoLT->hide();
				}
				if (m_pvideoLB)
				{
					m_pvideoLB->hide();
				}
				if (m_pvideoRT)
				{
					m_pvideoRT->hide();
				}
				if (m_pvideoRB)
				{
					m_pvideoRB->hide();
				}
			} 
			else
			{
				if (m_pPLeft)
				{
					m_pPLeft->hide();
				}
				if (m_pPRight)
				{
					m_pPRight->hide();
				}
			}
		} 
		else
		{
			
			BOOL bJN = FALSE;
            if (m_pPRight)
            {
				m_pPRight->hide();
            }
			if (m_pPLeft)
			{
				m_pPLeft->show();
			}

			if (IsVideoShow(LTWNDINDEX,bJN))
			{
				if (m_pPLT)
				{
					m_pPLT->show();
				}
				m_pLT->show();	
				if (bJN)
				{
					if (m_pvideoLT)
					{			
						m_pvideoLT->show();
					}
					if (m_pdllVideoLT)
					{
						m_pdllVideoLT->hide();
					}
				} 
				else
				{
					if (m_pvideoLT)
					{
						m_pvideoLT->hide();
					}
					if (m_pdllVideoLT)
					{
						m_pdllVideoLT->show();
					}
				}
			} 
			else
			{
				if (m_pPLT)
				{
					m_pPLT->hide();
				}
				m_pLT->hide();
			}
			if (IsVideoShow(RTWNDINDEX,bJN))
			{
				if (m_pPRT)
				{
					m_pPRT->show();
				}
				m_pRT->show();
				if (bJN)
				{
					if (m_pvideoRT)
					{
						m_pvideoRT->show();
					}
					if (m_pdllVideoRT)
					{
						m_pdllVideoRT->hide();
					}	
				} 
				else
				{
					if (m_pvideoRT)
					{
						m_pvideoRT->hide();
					}
					if (m_pdllVideoRT)
					{
						m_pdllVideoRT->show();
					}
				}
			} 
			else
			{
				if (m_pPRT)
				{
					m_pPRT->hide();
				}
				m_pRT->hide();
			}
			if (IsVideoShow(LBWNDINDEX,bJN))
			{
				if (m_pPLB)
				{
					m_pPLB->show();
				}
				m_pLB->show();
				if (bJN)
				{
					if (m_pvideoLB)
					{
						m_pvideoLB->show();
					}
					if (m_pdllVideoLB)
					{
						m_pdllVideoLB->hide();
					}
				} 
				else
				{
					if (m_pvideoLB)
					{
						m_pvideoLB->hide();
					}
					if (m_pdllVideoLB)
					{
						m_pdllVideoLB->show();
					}
				}

			} 
			else
			{
				if (m_pPLB)
				{
					m_pPLB->hide();
				}
				m_pLB->hide();
			}
			if (IsVideoShow(RBWNDINDEX,bJN))
			{
				if (m_pPRB)
				{
					m_pPRB->show();
				}
				m_pRB->show();
				if (bJN)
				{
					if (m_pvideoRB)
					{
						m_pvideoRB->show();
					}
					if (m_pdllVideoRB)
					{
						m_pdllVideoRB->hide();
					}
				} 
				else
				{
					if (m_pvideoRB)
					{
						m_pvideoRB->hide();
					}
					if (m_pdllVideoRB)
					{
						m_pdllVideoRB->show();
					}
				}
			} 
			else
			{
				if (m_pPRB)
				{
					m_pPRB->hide();
				}
				m_pRB->hide();
			}
		}		
	}
    if (FALSE == m_bShowOpen)
    {
		return;
    }
	QLayout* preLay = m_pRight->layout();
	if (preLay)
	{
		delete preLay;
		preLay = NULL;
	}

	if (m_pOpenCombox)
	{
		m_pOpenCombox->hide();
	}
	if (m_pvideoBk)
	{
		m_pvideoBk->show();
	}	
	QVBoxLayout* lay = new QVBoxLayout;
	lay->addWidget(m_pvideoBk);
	lay->setContentsMargins(0,0,0,0);
	lay->setSpacing(0);
	m_pRight->setLayout(lay);
	m_bShowOpen = FALSE;
	
}
/************************************************************************/
/*
showOpen
      show the default window
param[in]   none
return      none
*/
/************************************************************************/
void CFramelessDialog::showOpen()
{
	if (m_bShowOpen)
	{
		return;
	}
	QLayout* preLay = m_pRight->layout();
	if (preLay)
	{
		delete preLay;
		preLay = NULL;
	}

	if (m_pOpenCombox)
	{
		m_pOpenCombox->show();
	}
	if (m_pvideoBk)
	{
		m_pvideoBk->hide();
	}
	QHBoxLayout* hlay = new QHBoxLayout;
	QComboBox* pCombox = qFindChild<QComboBox*>(m_pRight,"comboBox");
	if (pCombox && hlay)
	{     
		hlay->addWidget(pCombox);					
		m_pRight->setLayout(hlay);
	}
	m_bShowOpen = TRUE;
}
/************************************************************************/
/*
readConfig
     read the login url,map url and url for updating from conf.ini and
	 qss.ini
param[in]    none
return       none
*/
/************************************************************************/
void CFramelessDialog::readConfig()
{
	QString strConfigFile = QApplication::applicationDirPath()+DIR+CONFIGPATH;
	char strTemp[JSLEN]={0};
	m_strCtrlFast = "Speed:1";
	m_strCtrlSlow = "Speed:-1";
	m_strCtrlPlay = "PlayOrPause:0";
	m_strCtrlPause = "PlayOrPause:1";
	m_strCtrlFullSize = "FullSize:1";
	m_strCtrlSound = "MuteOrSound:1";
	m_strCtrlNotSound = "MuteOrSound:0";
	m_strCtrlExtInfo = "HideOrShowExtend:1";
	m_strCtrlNotExtInfo = "HideOrShowExtend:0";
	m_strCtrlVolume = "Volume:";
	m_strCtrlUpdateProgress = "UpdateProgressFlag:1";
	m_strCtrlNotUpdateProgress = "UpdateProgressFlag:0";
	m_strCtrlSetProgress = "Progress:";

	m_strRecvProgress = "Progress";
	m_strRecvSpeed = "ShowSpeed";
	m_strRecvDuration = "ReportDuration";
	m_strRecvPlay = "PlayOrPause";
	m_strRecvNext = "NextOrLast";
	m_strRecvStop = "StopPlay";
    m_strRecvSound = "MuteOrSound";
	m_strRecvVolume = "Volume";
    
	GetPrivateProfileStringA("QSS","PauseBtn","QPushButton#pauseBtn{background-image: url(:/VehicleVideoPlayer/Resources/img/icon10.png);}QPushButton#pauseBtn:hover{background-image: url(:/onMouse/Resources/img/on_mouse/icon10.png);}",strTemp,JSLEN-1,strConfigFile.toStdString().c_str());//;
    m_strStylePause = strTemp;
	GetPrivateProfileStringA("QSS","Sound0","QPushButton#soundBtn{background-image: url(:/VehicleVideoPlayer/Resources/img/icon12.png);}QPushButton#pauseBtn:hover{background-image: url(:/onMouse/Resources/img/on_mouse/icon12.png);}",strTemp,JSLEN-1,strConfigFile.toStdString().c_str());//;
	m_strStyleVolume0 = strTemp;
	GetPrivateProfileStringA("QSS","Sound1","QPushButton#soundBtn{background-image: url(:/VehicleVideoPlayer/Resources/img/icon8.png);}QPushButton#pauseBtn:hover{background-image: url(:/onMouse/Resources/img/on_mouse/icon8.png);}",strTemp,JSLEN-1,strConfigFile.toStdString().c_str());//;
	m_strStyleVolume2 = strTemp;
	GetPrivateProfileStringA("QSS","Sound2","QPushButton#soundBtn{background-image: url(:/VehicleVideoPlayer/Resources/img/icon8_2.png);}QPushButton#pauseBtn:hover{background-image: url(:/onMouse/Resources/img/on_mouse/icon8_2.png);}",strTemp,JSLEN-1,strConfigFile.toStdString().c_str());//;
	m_strStyleVolume3 = strTemp;
	GetPrivateProfileStringA("QSS","OSD","background-color: rgba(92, 104, 103,128);color: rgba(250,250,250,200)",strTemp,JSLEN-1,strConfigFile.toStdString().c_str());
	m_strStyleOSD = strTemp;
	//GetPrivateProfileStringA("QSS","FullVideo","CFullVideo{border: 0px;}",strTemp,JSLEN-1,strConfigFile.toStdString().c_str());
	//m_strStyleVideoNoFrame = strTemp;
	GetPrivateProfileStringA("QSS","NoExtend","QPushButton#btnGps{background-image: url(:/VehicleVideoPlayer/Resources/img/locations.png);}",strTemp,JSLEN-1,strConfigFile.toStdString().c_str());
	m_strStyleNoExtend = strTemp;
	GetPrivateProfileStringA("QSS","RestoreStyle","QPushButton#maxBtn{background-image: url(:/VehicleVideoPlayer/Resources/img/icon5.png);}",strTemp,JSLEN-1,strConfigFile.toStdString().c_str());//;
	m_strStyleRestore = strTemp;
	GetPrivateProfileStringA("QSS","ErrorPic","background-image: url(:/VehicleVideoPlayer/Resources/img/locations.png);",strTemp,JSLEN-1,strConfigFile.toStdString().c_str());
	strPicError = strTemp;
	GetPrivateProfileStringA("QSS","WarningPic","background-image: url(:/VehicleVideoPlayer/Resources/img/locations.png);",strTemp,JSLEN-1,strConfigFile.toStdString().c_str());
	strPicWarning = strTemp;
	GetPrivateProfileStringA("QSS","InfoPic","background-image: url(:/VehicleVideoPlayer/Resources/img/locations.png);",strTemp,JSLEN-1,strConfigFile.toStdString().c_str());
	strPicInfo = strTemp;
	memset(strTemp,0,JSLEN);

	DWORD dwlen = GetPrivateProfileStringA("MAP","DataCenterInner",MAPURLDCI,strTemp,JSLEN-1,strConfigFile.toStdString().c_str());
	m_strMapDCI = strTemp;
	memset(strTemp,0,JSLEN);
	
	GetPrivateProfileStringA("MAP","DataCenterExter",MAPURLDCE,strTemp,JSLEN-1,strConfigFile.toStdString().c_str());
	m_strMapDCE = strTemp;
	memset(strTemp,0,JSLEN);

	GetPrivateProfileStringA("MAP","BackupCenterInner",MAPURLBCI,strTemp,JSLEN-1,strConfigFile.toStdString().c_str());
	m_strMapBCI = strTemp;
	memset(strTemp,0,JSLEN);

	GetPrivateProfileStringA("MAP","BackupCenterExter",MAPURLBCE,strTemp,JSLEN-1,strConfigFile.toStdString().c_str());
	m_strMapBCE = strTemp;

	GetPrivateProfileStringA("UPDATE","DataCenterInner",UPDATEURLDCI,strTemp,JSLEN-1,strConfigFile.toStdString().c_str());
    m_strUpdateDCI = strTemp;
    memset(strTemp,0,JSLEN);

	GetPrivateProfileStringA("UPDATE","DataCenterExter",UPDATEURLDCE,strTemp,JSLEN-1,strConfigFile.toStdString().c_str());
	m_strUpdateDCE = strTemp;
	memset(strTemp,0,JSLEN);

	GetPrivateProfileStringA("UPDATE","BackupCenterInner",UPDATEURLBCI,strTemp,JSLEN-1,strConfigFile.toStdString().c_str());
	m_strUpdateBCI = strTemp;
	memset(strTemp,0,JSLEN);

	GetPrivateProfileStringA("UPDATE","BackupCenterExter",UPDATEURLBCE,strTemp,JSLEN-1,strConfigFile.toStdString().c_str());
    m_strUpdateBCE = strTemp;
	memset(strTemp,0,JSLEN);

	GetPrivateProfileStringA("LOGIN","DataCenterInner",LOGINDCI,strTemp,JSLEN-1,strConfigFile.toStdString().c_str());
	CLogin::strLoginUrlDCI = strTemp;
	memset(strTemp,0,JSLEN);

	GetPrivateProfileStringA("LOGIN","DataCenterExter",LOGINDCE,strTemp,JSLEN-1,strConfigFile.toStdString().c_str());
	CLogin::strLoginUrlDCE = strTemp;
	memset(strTemp,0,JSLEN);

	GetPrivateProfileStringA("LOGIN","BackupCenterInner",LOGINBCI,strTemp,JSLEN-1,strConfigFile.toStdString().c_str());
	CLogin::strLoginUrlBCI = strTemp;
	memset(strTemp,0,JSLEN);

	GetPrivateProfileStringA("LOGIN","BackupCenterExter",LOGINBCE,strTemp,JSLEN-1,strConfigFile.toStdString().c_str());
	CLogin::strLoginUrlBCE = strTemp;

	m_nMoveSpace = GetPrivateProfileIntA("LOGIN","MoveSpace",MOVSPACE,strConfigFile.toStdString().c_str());
    m_nMargin = GetPrivateProfileIntA("LOGIN","Margin",SPACEMARGIN,strConfigFile.toStdString().c_str());
    //read user info
	strConfigFile = QApplication::applicationDirPath()+DIR+USERCONFIG;
	memset(strTemp,0,JSLEN);
	memset(CLogin::szName,0,NAMELEN);
	memset(CLogin::szPwd,0,NAMELEN);
	GetPrivateProfileStringA("USER","N","",CLogin::szName,NAMELEN,strConfigFile.toStdString().c_str());
	GetPrivateProfileStringA("USER","P","",CLogin::szPwd,NAMELEN,strConfigFile.toStdString().c_str());
	CLogin::bRememberPwd = GetPrivateProfileIntA("USER","R",0,strConfigFile.toStdString().c_str());

	CLanguage::m_eLanguageType =(ElanguageType)GetPrivateProfileIntA("LANG","LangType",1,strConfigFile.toStdString().c_str());
	GetPrivateProfileStringA("DIR","OpenPath","",strTemp,JSLEN-1,strConfigFile.toStdString().c_str());
	m_strPreFileDir = strTemp;

	CLogin::eNetType = (ENetType)GetPrivateProfileIntA("LOGIN","Etype",0,strConfigFile.toStdString().c_str());
	m_strCol1Caption = "Name";
	m_strCol3Caption = "Size";
	m_strCol4Caption = "Path";

	m_strColNum = "Number";
	m_strColTime = "Start-End-Time";
	m_strColLen = "Time Length";
	m_strColType ="Video Type";
	//m_nPlatformVersion = 10;

	m_nVLevel1 = 70;
	m_nVLevel3 = 150;
	WORD versionRequest;
	WSADATA wsa;
	int err;
	versionRequest=MAKEWORD(2,2);
	err=WSAStartup(versionRequest,&wsa);
	if(err!=0)
	{
		return;
	}
	if(LOBYTE(wsa.wVersion)!=2||HIBYTE(wsa.wVersion!=2))
	{
		WSACleanup();
		return;
	}
}
/************************************************************************/
/*
saveConfig
     save the user info and location of server to qss.ini
param[in]   none
return      none
*/
/************************************************************************/
void CFramelessDialog::saveConfig()
{
	QString strConfigFile = QApplication::applicationDirPath()+DIR+USERCONFIG;
    WritePrivateProfileStringA("DIR","OpenPath",m_strPreFileDir.toStdString().c_str(),strConfigFile.toStdString().c_str());
	char szTemp[10]={0};
	sprintf_s(szTemp,9,"%d",CLanguage::m_eLanguageType);
	WritePrivateProfileStringA("LANG","LangType",szTemp,strConfigFile.toStdString().c_str());
	memset(szTemp,0,10);
	rc4_state rcState;

	CLogin::rc4_crypt(&rcState,(unsigned char*)CLogin::szName,strlen(CLogin::szName));
	CLogin::rc4_crypt(&rcState,(unsigned char*)CLogin::szPwd,strlen(CLogin::szPwd));
	WritePrivateProfileStringA("USER","N",CLogin::szName,strConfigFile.toStdString().c_str());
	WritePrivateProfileStringA("USER","P",CLogin::szPwd,strConfigFile.toStdString().c_str());
	itoa(CLogin::bRememberPwd,szTemp,10);
	WritePrivateProfileStringA("USER","R",szTemp,strConfigFile.toStdString().c_str());

	memset(szTemp,0,10);
	itoa(CLogin::eNetType,szTemp,10);
	WritePrivateProfileStringA("LOGIN","Etype",szTemp,strConfigFile.toStdString().c_str());
	
}
/************************************************************************/
/*
clearFileListInfo
     empty the table for show the video info and the vector used to
	 save the video file info
param[in]   none
return      none
*/
/************************************************************************/
void CFramelessDialog::clearFileListInfo()
{
	for (int i=0;i<m_VectorFileInfo.size();i++)
	{
		FileInfo* info = m_VectorFileInfo[i];
		if (info)
		{
			delete info;
		}
	}
	m_VectorFileInfo.clear();

	if (m_pTableList)
	{
		int nRow = m_pTableList->rowCount();
		int nCol = m_pTableList->columnCount();
		for (int nr=0;nr<nRow;nr++)
		{
			for (int nc=0;nc<nCol;nc++)
			{
				QTableWidgetItem* pItem = m_pTableList->item(nr,nc);
				if (pItem)
				{
					delete pItem;
				}
			}
		}
		m_pTableList->clearContents();
	}
	m_mpSDKTimeInfo.clear();
	m_mpSDKFileInfo.clear();
}
/************************************************************************/
/*
setCurFileList 
     save all the video info in the vector,and play the first video
param[in]   strFiles  all the video files the user choose to play
return      none
*/
/************************************************************************/
void CFramelessDialog::setCurFileList(QStringList & strFiles)
{
	clearFileListInfo();
	QString strFileSize;
	QString strPath;
	for (int i=0;i<strFiles.size();i++)
	{
		AddFile(strFiles[i]);
	}
	if (m_VectorFileInfo.size()<1)
	{
		return;
	}
	if (m_pRight && m_pLT)
	{
		if (m_pLB)
		{
			m_pLB->hide();
		}
		if (m_pRT)
		{
			m_pRT->hide();
		}
		if (m_pRB)
		{
			m_pRB->hide();
		}
		QRect rc = m_pRight->geometry();
		m_pvideoBk->setGeometry(0,0,rc.width(),rc.height());
		m_pLT->setGeometry(0,0,rc.width(),rc.height());
		updateOSD(ANYINDEX);
	}

	if (m_VectorFileInfo.size()>0)
	{
		createVideo(LTWNDINDEX,m_VectorFileInfo[0]->strFileName);
		if (m_pFuncSetCustomFlag)
		{
			m_pFuncSetCustomFlag(LTWNDINDEX,CUSTOMFLAG);
		}
		PlayVideoByFileInfo(m_VectorFileInfo[0],PLAYED);
	}
	showVideo();
	updateCurVideo(LTWNDINDEX);
	setListInfo();
	if (m_pProgress)
	{
		m_pProgress->setEnabled(true);
	}
	if (m_pTableList)
	{
		m_pTableList->selectRow(0);
	}
}
/************************************************************************/
/*
setListInfo
    show the video info in the table
param[in]   none
return      none
*/
/************************************************************************/
void CFramelessDialog::setListInfo()
{
    if (m_pTableList)
    {
		if (m_bSDK)
		{
			m_pTableList->setRowCount(m_mpSDKTimeInfo.size());
			int nNumber = 1;
			for(SDKTMAP::iterator it = m_mpSDKTimeInfo.begin();it != m_mpSDKTimeInfo.end();it++)
			{
				QTableWidgetItem* pNumberItem = new QTableWidgetItem();
				QTableWidgetItem* pTimeItem = new QTableWidgetItem();
				QTableWidgetItem* pLenItem = new QTableWidgetItem();
				QTableWidgetItem* pTypeItem = new QTableWidgetItem();
				if(pNumberItem)
				{
					//pNumberItem->setFlags(Qt::ItemIsUserCheckable);
					pNumberItem->setData(Qt::DisplayRole,nNumber);
					m_pTableList->setItem(nNumber-1,0,pNumberItem);
				}
				if (pTimeItem)
				{
					char szT[50]={0};

					{
						int nMinutes = it->first/TIMELEN;
						int nMinutee = it->second.first/TIMELEN;
                        //pTimeItem->setFlags(Qt::ItemIsUserCheckable);
						sprintf_s(szT,49,"%02d:%02d:%02d-%02d:%02d:%02d",nMinutes/TIMELEN,nMinutes%TIMELEN,it->first%TIMELEN,nMinutee/TIMELEN,nMinutee%TIMELEN,it->second.first%TIMELEN);
						QStringList strl(szT);
						pTimeItem->setData(Qt::DisplayRole,strl);
						m_pTableList->setItem(nNumber-1,3,pTimeItem);
					}
				}
				if (pLenItem)
				{
					int nLen = (it->second.first - it->first)/TIMELEN;
                    if (nLen<1)
                    {
						nLen = 1;
                    }
					else if ((it->second.first-it->first)%TIMELEN != 0)
					{
						nLen+=1;
					}
					pLenItem->setData(Qt::DisplayRole,nLen);
					m_pTableList->setItem(nNumber-1,2,pLenItem);
				}
				if (pTypeItem)
				{
					if (it->second.second)
					{
						QStringList str(CLanguage::strAlarmVideo);
						pTypeItem->setData(Qt::DisplayRole,str);
						pTypeItem->setBackground(m_brAlarm);
					} 
					else
					{
						QStringList str(CLanguage::strNormalVideo);
						pTypeItem->setData(Qt::DisplayRole,str);
						pTypeItem->setBackground(m_brNormal);
					}
					m_pTableList->setItem(nNumber-1,1,pTypeItem);
				}
				nNumber++;
			}
		} 
		else
		{
			m_pTableList->setRowCount(m_VectorFileInfo.size());
			for (int i=0;i<m_VectorFileInfo.size();i++)
			{
				AddRow(i);
			}
		}
		
    }
	CLanguage::UpdateTableText();
	SetTableColWidth();
}
/************************************************************************/
/*
PlayVideoByFileInfo
      start or stop play the *.ts file via OCX,start a thread to 
	  calculate the duration first if it's duration is unknown
param[in]    none
return       none
*/
/************************************************************************/
void CFramelessDialog::PlayVideoByFileInfo(FileInfo* pFileInfo,int iActionFlag)
{
	if (!pFileInfo)
	{
		return;
	}   
	FileSourceType fType = UnknowType;
	if (pFileInfo->strFileName.contains(JNPREFIX) /*|| pFileInfo->strFileName.contains(WKPPREFIX)*/)
	{
		fType = JNType;
	} 
	else if (pFileInfo->strFileName.contains(RMPREFIX))
	{
		fType = RmType;
	}
	else if (pFileInfo->strFileName.contains(WKPPREFIX))
	{
		fType = WkpType;
	}
	if (NOTSETDURATION == pFileInfo->iDuration)
	{
		m_nCurDuration = NOTSETDURATION;
		if (JNType == fType)
		{
			g_bThreadCompletedFlag = FALSE;
			HANDLE hDuration = ::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadCalDurationAccordingFile,(void*)pFileInfo,0,NULL);
			CloseHandle(hDuration);
			pFileInfo->bCalDurationFlag = TRUE;
		} 		
	}  
    QWidget* pVideo = NULL;
	BOOL *bPlaying = NULL;
	BOOL *pbPlayOrPauseFlag = NULL;
	switch(pFileInfo->iVideoWndIndex)
	{
	case LTWNDINDEX:
		{
			pVideo = m_pvideoLT;
			bPlaying = &m_bPlayingFlagLT;
			pbPlayOrPauseFlag = &m_bPlayOrPauseFlagLT;
			break;
		}
	case RTWNDINDEX:
		{
			pVideo = m_pvideoRT;
			bPlaying = &m_bPlayingFlagRT;
			pbPlayOrPauseFlag = &m_bPlayOrPauseFlagRT;
			break;
		}
	case LBWNDINDEX:
		{
			pVideo = m_pvideoLB;
			bPlaying = &m_bPlayingFlagLB;
			pbPlayOrPauseFlag = &m_bPlayOrPauseFlagLB;
			break;
		}
	case RBWNDINDEX:
		{
			pVideo = m_pvideoRB;
			bPlaying = &m_bPlayingFlagRB;
			pbPlayOrPauseFlag = &m_bPlayOrPauseFlagRB;
			break;
		}
	default:
		{
			return;
			pVideo = m_pvideoLT;
			break;
		}
	}
	
	if (TRUE == *bPlaying && 0 == iActionFlag)//stop
	{
		if (JNType == fType && m_pFuncDisconnect)
		{
			m_pFuncDisconnect(pFileInfo->iVideoWndIndex);
		} 
		else
		{
			CANTOfflineFileSDKAdapter* pAdapter = GetPlugin(fType);
			if (pAdapter)
			{
				pAdapter->ANTOfflineFileSDK_Control_StopTheChannel(pFileInfo->iVideoWndIndex-1);
			}
		}
		*bPlaying = FALSE;
		*pbPlayOrPauseFlag = FALSE;
		pFileInfo->iPlayingStateFlag = PLAYED;
	} 
	else if (FALSE == *bPlaying && PLAY == iActionFlag)//play
	{
		*bPlaying = TRUE;
		*pbPlayOrPauseFlag = TRUE;
		pFileInfo->iPlayingStateFlag = PLAYING;
		if (JNType == fType && pVideo)
		{
			QString strInfo = pFileInfo->strFilePath;
			strInfo+=DIR;
			strInfo+=pFileInfo->strFileName;
			strInfo+=",2400;";
			char szWnd[50]={0};
			sprintf(szWnd,"0x%08x",(HWND)pVideo->winId());
			if (m_pFuncParaFileList)
			{
				m_pFuncParaFileList(strInfo.toStdWString().c_str(),pFileInfo->iVideoWndIndex,szWnd);
			}
			
			if (m_pFuncPlayImpl)
			{
				m_pFuncPlayImpl(pFileInfo->iVideoWndIndex);
			}
			
			updateControlState(LTWNDINDEX);
		} 
		else
		{			
			CANTOfflineFileSDKAdapter* pAdapter = GetPlugin(fType);
			if (pAdapter)
			{
				QString strInfo = pFileInfo->strFilePath;
				strInfo+=DIR;
				strInfo+=pFileInfo->strFileName;
				pAdapter->ANTOfflineFileSDK_Control_OpenFile(strInfo.toStdString().c_str(),pFileInfo->iVideoWndIndex-1);
			}
		}	
	}
	if (NOTSETDURATION == pFileInfo->iDuration && fType != JNType)
	{
		CANTOfflineFileSDKAdapter* pAdapter = GetPlugin(fType);
		if (pAdapter)
		{
			long ls=0;
			long le=0;
			long lt=0;
			pAdapter->ANTOfflineFileSDK_Control_GetFileInfo(pFileInfo->iVideoWndIndex-1,&ls,&le,&lt);
			
			lt = lt/1000;
			if(0 == lt)
			{
				lt = NOTSETDURATION;
			}
			pFileInfo->iDuration = lt;
			
		}
	}
}
/************************************************************************/
/*
SetVideoPlayerControlInfo
    control the playing.slow,fast,pause,mute,sound,volume 
param[in]   iWndIndex
            iWndIndex = 1 left top
			iWndIndex = 2 right top
			iWndIndex = 3 left bottom
			iWndIndex = 4 right bottom
param[in]   strCtrlInfo
return      none
*/
/************************************************************************/
void CFramelessDialog::SetVideoPlayerControlInfo(int iWndIndex,QString &strCtrlInfo)
{
	if (m_VectorFileInfo.size()>0 && m_pFuncSetControlInfo)
	{
		m_pFuncSetControlInfo(LTWNDINDEX,strCtrlInfo.toStdString().c_str());
	}	
	else
	{
		CANTOfflineFileSDKAdapter* pPlugin = NULL;
		if (FALSE == m_bSDK)
		{
			pPlugin = GetPlugin(iWndIndex);
		}
		if (strCtrlInfo == m_strCtrlPlay)
		{
			if (pPlugin)
			{
				pPlugin->ANTOfflineFileSDK_Control_PlayTheChannel(m_nCurWndIndex-1);
			} 
			else
			{
				for (int i=0;i<m_vtPluginInterface.size();i++)
				{
					m_vtPluginInterface[i]->ANTOfflineFileSDK_Control_PlayAllChannel();
				}
			}
		}
		else if (strCtrlInfo == m_strCtrlPause)
		{
			if (pPlugin)
			{
				pPlugin->ANTOfflineFileSDK_Control_PauseTheChannel(m_nCurWndIndex-1);
			} 
			else
			{
				for (int i=0;i<m_vtPluginInterface.size();i++)
				{
					m_vtPluginInterface[i]->ANTOfflineFileSDK_Control_PauseAllChannel();
				}
			}
		}
		else if (strCtrlInfo.contains(m_strCtrlVolume))
		{
			int nIndex = strCtrlInfo.indexOf(':');
			if (-1 != nIndex)
			{
				int nVolume = strCtrlInfo.mid(nIndex+1).toInt();
				float fvol = nVolume/VOLUMELEN;
				nVolume = fvol*100.0;
				if (pPlugin)
				{
					pPlugin->ANTOfflineFileSDK_Control_SetVolume(iWndIndex-1,nVolume);
				} 
				else
				{
					for (int i=0;i<m_vtPluginInterface.size();i++)
					{
						m_vtPluginInterface[i]->ANTOfflineFileSDK_Control_SetVolume(iWndIndex-1,nVolume);
					}
				}
			}
		}
		else if (strCtrlInfo == m_strCtrlNotSound)
		{
			if (pPlugin)
			{
				pPlugin->ANTOfflineFileSDK_Control_SetSound(iWndIndex-1,0,false);	
			} 
			else
			{
				for (int i=0;i<m_vtPluginInterface.size();i++)
				{
					m_vtPluginInterface[i]->ANTOfflineFileSDK_Control_SetSound(-1,0,false);
				}
			}
		}
		else if (strCtrlInfo == m_strCtrlSound)
		{
			if (pPlugin)
			{
				pPlugin->ANTOfflineFileSDK_Control_SetSound(iWndIndex-1,0,true);	
			} 
			else
			{
				for (int i=0;i<m_vtPluginInterface.size();i++)
				{
					m_vtPluginInterface[i]->ANTOfflineFileSDK_Control_SetSound(-1,0,true);
				}
			}
		}
		else if (strCtrlInfo == m_strCtrlSlow || strCtrlInfo == m_strCtrlFast)
		{
			unsigned char & nSpeedIndex = getSpeedIndex();
			if (strCtrlInfo == m_strCtrlFast)
			{
				nSpeedIndex++;
			} 
			else
			{
				nSpeedIndex--;
			}
			if (nSpeedIndex<0)
			{
				nSpeedIndex = 0;
			}
			if (nSpeedIndex>=SPEEDCOUNT)
			{
				nSpeedIndex = SPEEDCOUNT - 1;
			}
			if (pPlugin)
			{
				pPlugin->ANTOfflineFileSDK_Control_SetSpeedTheChannel(nSpeedIndex,m_nCurWndIndex-1);
			} 
			else
			{
				for (int i=0;i<m_vtPluginInterface.size();i++)
				{
					m_vtPluginInterface[i]->ANTOfflineFileSDK_Control_SetSpeedAllChannel(nSpeedIndex);
				}
			}
		}
		else if (strCtrlInfo.contains(m_strCtrlSetProgress))
		{
			
			int nPos = m_pProgress->sliderPosition();
			int nIndex1 = strCtrlInfo.indexOf(SEP);
			int nIndex2 = strCtrlInfo.indexOf(ITEMSEP);
			if (m_mpSDKTimeInfo.size()>0 && nIndex2-nIndex1>1)
			{
				nPos = strCtrlInfo.mid(nIndex1+1,nIndex2-nIndex1-1).toInt();				
			}
            m_nCurSecond = nPos;
			if (pPlugin)
			{
				pPlugin->ANTOfflineFileSDK_Control_SeekTheChannel(m_nCurWndIndex-1,nPos);
			} 
			else
			{
				for (int i=0;i<m_vtPluginInterface.size();i++)
				{
					m_vtPluginInterface[i]->ANTOfflineFileSDK_Control_SeekAllChannel(nPos);
				}
			}
		}
	}
}

/************************************************************************/
/*
PlayNextItem
    it will continue to play video once the current video is finished
param[in] iWndIndex
param[in] iStep   it present the next iStep video
return BOOL
*/
/************************************************************************/
BOOL CFramelessDialog::PlayNextItem(int iWndIndex,int iStep)
{
	if (m_bSDK)
	{
		m_nCurFileIndex++;
		if (m_nCurFileIndex>=m_mpSDKTimeInfo.size())
		{
			m_nCurFileIndex = 0;
		}
		m_mpStrExtend.clear();
        PlayGroupInRow(m_nCurFileIndex);
		return TRUE;
	}
	FileInfo* finfo = NULL;
	if (m_nCurFileIndex>=0 && m_nCurFileIndex<m_VectorFileInfo.size())
	{
		finfo = m_VectorFileInfo[m_nCurFileIndex];
	}
 
	if (finfo &&(PLAYING == finfo->iPlayingStateFlag))
	{
		
		PlayVideoByFileInfo(finfo,STOP);
		finfo->iPlayingStateFlag = PLAYED;
		finfo->iCurTime = 0;
	} 
	m_nCurFileIndex++;
	if (m_nCurFileIndex>=m_VectorFileInfo.size())
	{
		m_nCurFileIndex = 0;
	}
	finfo = NULL;
	if (m_nCurFileIndex>=0 && m_nCurFileIndex<m_VectorFileInfo.size())
	{
		finfo = m_VectorFileInfo[m_nCurFileIndex];
	}
	if (finfo)
	{
		m_mpStrExtend.clear();
		createVideo(LTWNDINDEX,finfo->strFileName);	
		PlayVideoByFileInfo(finfo,PLAYED);
		showVideo();
		if(m_pTableList)
		{
			m_pTableList->selectRow(m_nCurFileIndex);
		}
		updateCurVideo(m_nCurWndIndex,TRUE);	
		return TRUE;
	}
	return FALSE;
}
/************************************************************************/
/*
IsVideoShow
    judge whether the video window is now playing the video
param[in] iWndIndex
param[in] bJN
          bJN = TRUE   is *.ts file
		  bJN = FALSE  is not *.ts file
return    none
   
*/
/************************************************************************/
BOOL CFramelessDialog::IsVideoShow(int iWndIndex,BOOL &bJN)
{
	for (int i=0;i<m_VectorFileInfo.size();i++)
	{
		FileInfo* finfo = m_VectorFileInfo[i];
		if (finfo && iWndIndex == finfo->iVideoWndIndex)
		{
			if (PLAYING == finfo->iPlayingStateFlag)
			{
				if (finfo->strFileName.contains(JNPREFIX)/* || finfo->strFileName.contains(WKPPREFIX)*/)
				{
					bJN = TRUE;
				} 
				else
				{
					bJN = FALSE;
				}
				return TRUE;
			}
		}
	}
	return FALSE;
}
/************************************************************************/
/*
clickMaxBtn 
     maximize or restore the mainwindow
param[in]  none
return     none
*/
/************************************************************************/
void CFramelessDialog::clickMaxBtn()
{
  if (m_pChild)
  {
	  if (m_bMax)
	  {
		  if (m_pBtnMax)
		  {
			  m_pBtnMax->setStyleSheet(m_strStyleMax);
		  }
		  showNormal();
		  m_bMax = FALSE;
	  } 
	  else
	  {
		  if (m_pBtnMax)
		  {
			  m_pBtnMax->setStyleSheet(m_strStyleRestore);
		  }
		 showMaximized();
		 m_bMax = TRUE;
	  }
	 resizeMap();
	 
  }
}
/************************************************************************/
/*
updateRangeForProgress
    refresh the range for the time bar
param[in] nMax   the max value for range
return    none
*/
/************************************************************************/
void CFramelessDialog::updateRangeForProgress(int nMax)
{
	if (m_pProgress)
	{
		m_pProgress->setRange(0,nMax);
		m_pProgress->setSliderPosition(0);
	}
	
	char szCur[20]={0};
	if(m_pTotalTime)
	{
		
		char szTotal[20]={0};
		
		if (nMax/TIMELEN > TIMELIMIT)
		{
			int nMinutes = nMax/TIMELEN;
			sprintf_s(szTotal,20,"%02d:%02d:%02d",nMinutes/TIMELEN,nMinutes%TIMELEN,nMax%TIMELEN);
			sprintf_s(szCur,20,"00:00:00");
		}
		else
		{
			char sz[20]={0};
			sprintf_s(szTotal,20,"%02d:%02d",nMax/TIMELEN,nMax%TIMELEN);
			sprintf_s(szCur,20,"00:00");
		}
		
		m_pTotalTime->setText(szTotal);
	}
	
	if (m_pCurTime)
	{
		m_pCurTime->setText(szCur);
	}
}
/************************************************************************/
/*
updateProgress
      refresh the current position of time bar
param[in]nPos   the cur pos
return   none
*/
/************************************************************************/
void CFramelessDialog::updateProgress(int nPos)
{
	if (m_pProgress)
	{
		m_pProgress->setSliderPosition(nPos);
	}
	
	if(m_pCurTime)
	{
		char szCur[20]={0};
		if (m_pProgress->maximum()/TIMELEN > TIMELIMIT)
		{
			int nMinutes = nPos/TIMELEN;
			sprintf_s(szCur,20,"%02d:%02d:%02d",nMinutes/TIMELEN,nMinutes%TIMELEN,nPos%TIMELEN);
			
		}
		else
		{
			sprintf_s(szCur,20,"%02d:%02d",nPos/TIMELEN,nPos%TIMELEN);
		}
		m_pCurTime->setText(szCur);
	}
}
/************************************************************************/
/*
updateVolume
    refresh the state of the volume button
	mute,volume small,volume medium,volume loud
param[in]  none
return     none
*/
/************************************************************************/
void CFramelessDialog::updateVolume()
{
	if (!m_pBtnVolume)
	{
		return;
	}
	int* pvolume = NULL;
	BOOL * bSound = NULL;
	switch(m_nCurWndIndex)
	{
	case LTWNDINDEX:
		{
			bSound = &m_bSoundOrNotFlagLT;
			pvolume = &m_iVolumeLT;
			break;
		}
	case RTWNDINDEX:
		{
			bSound = &m_bSoundOrNotFlagRT;
			pvolume = &m_iVolumeRT;
			break;
		}
	case LBWNDINDEX:
		{
			bSound = &m_bSoundOrNotFlagLB;
			pvolume = &m_iVolumeLB;
			break;
		}
	case RBWNDINDEX:
		{
			bSound = &m_bSoundOrNotFlagRB;
            pvolume = &m_iVolumeRB;
			break;
		}
	default:
		{
			bSound = &m_bSoundOrNotFlagLT;
			pvolume = &m_iVolumeLT;
			break;
		}
	}
	if (bSound)
	{
		if (*bSound)
		{
			if (*pvolume<m_nVLevel1)
			{
				m_pBtnVolume->setStyleSheet(m_strStyleVolume1);
			}
			else if (*pvolume>m_nVLevel3)
			{
				m_pBtnVolume->setStyleSheet(m_strStyleVolume3);
			}
			else
			{
				m_pBtnVolume->setStyleSheet(m_strStyleVolume2);
			}
			if (m_pVolumeBar)
			{
				QRect rc = m_pVolumeBar->geometry();
				m_pVolumeBar->setGeometry(rc.left(),rc.top(),*pvolume/2,rc.height());
			}
		} 
		else
		{
			m_pBtnVolume->setStyleSheet(m_strStyleVolume0);
			if (m_pVolumeBar)
			{
				QRect rc = m_pVolumeBar->geometry();
				m_pVolumeBar->setGeometry(rc.left(),rc.top(),0,rc.height());
			}
		}
	}
	
}
/************************************************************************/
/*
updatePlayBtn
     fefresh state of play button.pause and play 
param[in]   none
return      none
*/
/************************************************************************/
void CFramelessDialog::updatePlayBtn()
{
	if (!m_pBtnPlay)
	{
		return;
	}

	if (m_bPlayOrPauseFlagLT)
	{
		m_pBtnPlay->setStyleSheet(m_strStylePause);
	} 
	else
	{
		m_pBtnPlay->setStyleSheet(m_strStylePlay);
	}
}
void CFramelessDialog::updateGpsBtn()
{
	if (!m_pBtnGps)
	{
		return;
	}
	BOOL bExtend = FALSE;
	switch(m_nCurWndIndex)
	{
	case LTWNDINDEX:
		{
			bExtend = m_bExtendFlagLT;
			break;
		}
	case RTWNDINDEX:
		{
			bExtend = m_bExtendFlagRT;
			break;
		}
	case LBWNDINDEX:
		{
			bExtend = m_bExtendFlagLB;
			break;
		}
	case RBWNDINDEX:
		{
			bExtend = m_bExtendFlagRB;
			break;
		}
	default:
		{
			bExtend = m_bExtendFlagLT;
			break;
		}
	}
	if (bExtend)
	{
		m_pBtnGps->setStyleSheet(m_strStyleExtend);
	} 
	else
	{
		m_pBtnGps->setStyleSheet(m_strStyleNoExtend);
	}
}
/************************************************************************/
/*
updateTitle
    refresh current video file on the top of the window
param[in]    strName     *.ts file name
return       none
*/
/************************************************************************/
void CFramelessDialog::updateTitle(QString &strName)
{
	if (m_pNameLabel)
	{
		m_pNameLabel->setText(strName);
	}
}
void CFramelessDialog::updateCurVideo(int iWndIndex,BOOL bForce)
{
	
	if (m_bSDK && ANYINDEX != iWndIndex)
	{
		m_nCurWndIndex = iWndIndex;
		if (m_pProgress)
		{
			m_pProgress->setEnabled(true);
		}
		updateRangeForProgress(m_nCurDuration);
		updatePlayBtn();
		updateGpsBtn();
		m_mpStrExtend.clear();
		hideExtend();
		m_nClearTimer = startTimer(CLEARINVAL);	
		return;
	}
	
	if ((ANYINDEX != iWndIndex) || bForce)
	{
		FileInfo* finfo = NULL;
		for (int i=0;i<m_VectorFileInfo.size();i++)
		{
			finfo = m_VectorFileInfo[i];
			if (finfo && iWndIndex == finfo->iVideoWndIndex && PLAYING == finfo->iPlayingStateFlag)
			{
				break;
			}
		}
		
		m_nCurWndIndex = iWndIndex;
		if (finfo)
		{
			m_nCurDuration = finfo->iDuration;
			updateRangeForProgress(finfo->iDuration);
			updateProgress(finfo->iCurTime);
			updateTitle(finfo->strFileName);
		}		
		updateVolume();
		updatePlayBtn();
		updateGpsBtn();
	}
	else if(ANYINDEX == iWndIndex)
	{
		showAllGps(TRUE);
		m_nCurDuration = 0;
		updateRangeForProgress(0);
		updateProgress(0);
		QString str("");
		updateTitle(str);
		updateGpsBtn();
		if (m_pBtnVolume)
		{
			m_pBtnVolume->setStyleSheet(m_strStyleVolume1);
			if (m_pVolumeBar)
			{
				QRect rc = m_pVolumeBar->geometry();
				m_pVolumeBar->setGeometry(rc.left(),rc.top(),DEFAULTVOLUEM/2,rc.height());
			}
		}
		if (m_pBtnPlay)
		{
			m_pBtnPlay->setStyleSheet(m_strStylePlay);
		}		
		SetVideoPlayerControlInfo(LTWNDINDEX,m_strCtrlExtInfo);
		m_nCurWndIndex = iWndIndex;
	}
	if (CDllFunc::m_pFuncClearPath)
	{
		m_setTime.clear();
		m_nCurSecond = 0;
		(*CDllFunc::m_pFuncClearPath)(0,eOfflinePlay);
	}
    hideExtend();
	
}

void CFramelessDialog::setVolume(int nVolume)
{
	
	BOOL bSound = FALSE;
	switch(m_nCurWndIndex)
	{
	case LTWNDINDEX:
		{
			m_iVolumeLT = nVolume;
			bSound = m_bSoundOrNotFlagLT;
			break;
		}
	case RTWNDINDEX:
		{
			m_iVolumeRT = nVolume;
			bSound = m_bSoundOrNotFlagRT;
			break;
		}
	case LBWNDINDEX:
		{
			m_iVolumeLB = nVolume;
			bSound = m_bSoundOrNotFlagLB;
			break;
		}
	case RBWNDINDEX:
		{
			m_iVolumeRB = nVolume;
			bSound = m_bSoundOrNotFlagRB;
			break;
		}
	default:
		{
			m_iVolumeLT = nVolume;
			bSound = m_bSoundOrNotFlagLT;
			break;
		}
	}
	if (bSound)
	{
		QString strVolume = m_strCtrlVolume+QString::number(nVolume);
		SetVideoPlayerControlInfo(m_nCurWndIndex,strVolume);
	}
}

unsigned char &CFramelessDialog::getSpeedIndex()
{
	switch(m_nCurWndIndex)
	{
	case LTWNDINDEX:
		{
			return m_iSpeedIndexLT ;

		}
	case RTWNDINDEX:
		{
			return m_iSpeedIndexRT ;

		}
	case LBWNDINDEX:
		{
			return m_iSpeedIndexLB ;

		}
	case RBWNDINDEX:
		{
			return m_iSpeedIndexRB ;

		}
	default:
		{
			return m_iSpeedIndexLT;

		}
	}
}

BOOL CFramelessDialog::createSystemTray()
{
	m_icoTray.addFile(QCoreApplication::applicationDirPath() + DIR + UIPATH + "\\img\\VehicleVideoPlayer.ico");
	if (NULL == m_psystemTray)
	{
		m_pTrayMenu = new QMenu(this);
		m_pExitAction = new QAction(m_icoTray,"exit",m_pTrayMenu);
		if (m_pTrayMenu)
		{
			m_pTrayMenu->addAction(m_pExitAction);
			connect(m_pTrayMenu,SIGNAL(triggered ( QAction *)),SLOT(trigerExitMenu(QAction*)));
		}
		
		m_psystemTray = new QSystemTrayIcon(m_icoTray);	
		if (m_psystemTray)
		{
			m_psystemTray->setContextMenu(m_pTrayMenu);
			m_psystemTray->show();
		}	
	}
	return FALSE;
}

FileInfo* CFramelessDialog::getPlagFile(int iWndIndex)
{
	for (int i=0;i<m_VectorFileInfo.size();i++)
	{
		if (m_VectorFileInfo[i] && iWndIndex == m_VectorFileInfo[i]->iVideoWndIndex && PLAYING == m_VectorFileInfo[i]->iPlayingStateFlag)
		{
			return m_VectorFileInfo[i];		
		}
	}
	return NULL;
}

void CFramelessDialog::pauseAll(BOOL bPause)
{
	m_bPlayOrPauseFlagLT = bPause;
	m_bPlayOrPauseFlagLB = bPause;
	m_bPlayOrPauseFlagRT = bPause;
	m_bPlayOrPauseFlagRB = bPause;
}
void CFramelessDialog::playAll(BOOL bPlay)
{
	m_bPlayingFlagLT = bPlay;
	m_bPlayingFlagLB = bPlay;
	m_bPlayingFlagRT = bPlay;
	m_bPlayingFlagRB = bPlay;
}
void CFramelessDialog::showAllGps(BOOL bShow)
{
	m_bExtendFlagLB = bShow;
	m_bExtendFlagLT = bShow;
	m_bExtendFlagRB = bShow;
	m_bExtendFlagRT = bShow;
}
void CFramelessDialog::soundAll(BOOL bSound)
{
	m_bSoundOrNotFlagLT = bSound;
	m_bSoundOrNotFlagLB = bSound;
	m_bSoundOrNotFlagRT = bSound;
	m_bSoundOrNotFlagRB = bSound;
}
void CFramelessDialog::updateControlState(int iWndIndex)
{
	BOOL* pbSound = NULL;
	BOOL* pbExtend = NULL;
	int * pnVolume = NULL;
	switch(iWndIndex)
	{
	case LTWNDINDEX:
		{
			pbSound = &m_bSoundOrNotFlagLT;
			pbExtend = &m_bExtendFlagLT;
			pnVolume = &m_iVolumeLT;
			break;
		}
	case RTWNDINDEX:
		{
			pbSound = &m_bSoundOrNotFlagRT;
			pbExtend = &m_bExtendFlagRT;
			pnVolume = &m_iVolumeRT;
			break;
		}
	case LBWNDINDEX:
		{
			pbSound = &m_bSoundOrNotFlagLB;
			pbExtend = &m_bExtendFlagLB;
			pnVolume = &m_iVolumeLB;
			break;
		}
	case RBWNDINDEX:
		{
			pbSound = &m_bSoundOrNotFlagRB;
			pbExtend = &m_bExtendFlagRB;
			pnVolume = &m_iVolumeRB;
			break;
		}
	default:
		{
			break;
		}
	}
	if (pbSound)
	{
		if (*pbSound)
		{
			SetVideoPlayerControlInfo(iWndIndex,m_strCtrlSound);
			
		} 
		else
		{
			SetVideoPlayerControlInfo(iWndIndex,m_strCtrlNotSound);
			
		}
	}
	if (pbExtend)
	{
		if (*pbExtend)
		{
			SetVideoPlayerControlInfo(iWndIndex,m_strCtrlExtInfo);
		} 
		else
		{
			SetVideoPlayerControlInfo(iWndIndex,m_strCtrlNotExtInfo);
		}
	}
}
void CFramelessDialog::updateOSD(int iWndIndex)
{
	switch(iWndIndex)
	{
	case LTWNDINDEX:
		{
			if (m_pLT)
			{
				QRect rc = m_pLT->geometry();
				int nFontsize = min(rc.width(),rc.height())/FONTSIZE;

				if (m_pWWANRLevelLT)
				{
					QFont ft = m_pWWANRLevelLT->font();
					ft.setPixelSize(nFontsize);
					if (0 == m_pWWANRLevelLT->text().length())
					{
						m_pWWANRLevelLT->setText(CLanguage::strSignal);
					}
					int nWidth = m_pWWANRLevelLT->fontMetrics().width(m_pWWANRLevelLT->text());
				
					int nHeight = m_pWWANRLevelLT->fontMetrics().height();
					m_pWWANRLevelLT->setWindowFlags(Qt::WindowStaysOnTopHint);
					m_pWWANRLevelLT->setGeometry(XOFFSET,rc.height()-YOFFSET-nHeight,nWidth,nHeight);
					
					m_pWWANRLevelLT->update();
				}
				if (m_pGpsLT)
				{
					QFont ft = m_pGpsLT->font();
					ft.setPixelSize(nFontsize);
					if (0 == m_pGpsLT->text().length())
					{
						m_pGpsLT->setText(CLanguage::strGps);
					}
					int nWidth = m_pGpsLT->fontMetrics().width(m_pGpsLT->text());
					int nHeight = m_pGpsLT->fontMetrics().height();

					m_pGpsLT->setGeometry(rc.width()-XOFFSET-nWidth,rc.height()-YOFFSET-nHeight,nWidth,nHeight);
					m_pGpsLT->update();
					
				}
			}
			break;
		}
	case LBWNDINDEX:
		{
			if (m_pLB)
			{
				QRect rc = m_pLB->geometry();
				int nFontsize = min(rc.width(),rc.height())/FONTSIZE;
				if (m_pWWANRLevelLB)
				{
					QFont ft = m_pWWANRLevelLB->font();
					ft.setPixelSize(nFontsize);
					if (0 == m_pWWANRLevelLB->text().length())
					{
						m_pWWANRLevelLB->setText(CLanguage::strSignal);
					}
					int nWidth = m_pWWANRLevelLB->fontMetrics().width(m_pWWANRLevelLB->text());
					int nHeight = m_pWWANRLevelLB->fontMetrics().height();
					m_pWWANRLevelLB->setGeometry(XOFFSET,rc.height()-YOFFSET-nHeight,nWidth,nHeight);
					m_pWWANRLevelLB->update();
				}
				if (m_pGpsLB)
				{
					QFont ft = m_pGpsLB->font();
					ft.setPixelSize(nFontsize);
					if (0 == m_pGpsLB->text().length())
					{
						m_pGpsLB->setText(CLanguage::strGps);
					}
					int nWidth = m_pGpsLB->fontMetrics().width(m_pGpsLB->text());
					int nHeight = m_pGpsLB->fontMetrics().height();
					m_pGpsLB->setGeometry(rc.width()-nWidth-XOFFSET,rc.height()-YOFFSET-nHeight,nWidth,nHeight);
					m_pGpsLB->update();
				}
			}	
			break;
		}
	case RTWNDINDEX:
		{
			if (m_pRT)
			{
				QRect rc = m_pRT->geometry();
				int nFontsize = min(rc.width(),rc.height())/FONTSIZE;
				if (m_pWWANRLevelRT)
				{
					QFont ft = m_pWWANRLevelRT->font();
					ft.setPixelSize(nFontsize);
					if (0 == m_pWWANRLevelRT->text().length())
					{
						m_pWWANRLevelRT->setText(CLanguage::strSignal);
					}
					int nWidth = m_pWWANRLevelRT->fontMetrics().width(m_pWWANRLevelRT->text());
					int nHeight = m_pWWANRLevelRT->fontMetrics().height();
					m_pWWANRLevelRT->setGeometry(XOFFSET,rc.height()-YOFFSET-nHeight,nWidth,nHeight);
					m_pWWANRLevelRT->update();
				}
				if (m_pGpsRT)
				{
					QFont ft = m_pGpsRT->font();
					ft.setPixelSize(nFontsize);
					if (0 == m_pGpsRT->text().length())
					{
						m_pGpsRT->setText(CLanguage::strGps);
					}
					int nWidth = m_pGpsRT->fontMetrics().width(m_pGpsRT->text());
					int nHeight = m_pGpsRT->fontMetrics().height();
					m_pGpsRT->setGeometry(rc.width()-nWidth-XOFFSET,rc.height()-YOFFSET-nHeight,nWidth,nHeight);
					m_pGpsRT->update();
				}
			}
			break;
		}
	case RBWNDINDEX:
		{
			if (m_pRB)
			{
				QRect rc = m_pRB->geometry();
				int nFontsize = min(rc.width(),rc.height())/FONTSIZE;
				if (m_pWWANRLevelRB)
				{
					QFont ft = m_pWWANRLevelRB->font();
					ft.setPixelSize(nFontsize);
					if (0 == m_pWWANRLevelRB->text().length())
					{
						m_pWWANRLevelRB->setText(CLanguage::strSignal);
					}
					int nWidth = m_pWWANRLevelRB->fontMetrics().width(m_pWWANRLevelRB->text());
					int nHeight = m_pWWANRLevelRB->fontMetrics().height();
					m_pWWANRLevelRB->setGeometry(XOFFSET,rc.height()-YOFFSET-nHeight,nWidth,nHeight);
					m_pWWANRLevelRB->update();
				}
				if (m_pGpsRB)
				{
					QFont ft = m_pGpsRB->font();
					ft.setPixelSize(nFontsize);
					if (0 == m_pGpsRB->text().length())
					{
						m_pGpsRB->setText(CLanguage::strGps);
					}
					int nWidth = m_pGpsRB->fontMetrics().width(m_pGpsRB->text());
					int nHeight = m_pGpsRB->fontMetrics().height();
					m_pGpsRB->setGeometry(rc.width()-nWidth-XOFFSET,rc.height()-YOFFSET-nHeight,nWidth,nHeight);
					m_pGpsRB->update();
				}
			}
			break;
		}
	case ANYINDEX:
		{
			if (m_pLT)
			{
				QRect rc = m_pLT->geometry();
				int nw = rc.width();
				int nh = rc.height();
				int nFontsize = min(nw,nh)/FONTSIZE;
				if (m_pWWANRLevelLT)
				{
					QFont ft = m_pWWANRLevelLT->font();
					ft.setPixelSize(nFontsize);
					if (0 == m_pWWANRLevelLT->text().length())
					{
						m_pWWANRLevelLT->setText(CLanguage::strSignal);
					}
					int nWidth = m_pWWANRLevelLT->fontMetrics().width(m_pWWANRLevelLT->text());
					
					int nHeight = m_pWWANRLevelLT->fontMetrics().height();
					m_pWWANRLevelLT->setGeometry(XOFFSET,nh-YOFFSET-nHeight,nWidth,nHeight);
					
					m_pWWANRLevelLT->update();
				}
				if (m_pGpsLT)
				{
					QFont ft = m_pGpsLT->font();
					ft.setPixelSize(nFontsize);
					if (0 == m_pGpsLT->text().length())
					{
						m_pGpsLT->setText(CLanguage::strGps);
					}
					int nWidth = m_pGpsLT->fontMetrics().width(m_pGpsLT->text());
					
					int nHeight = m_pGpsLT->fontMetrics().height();
					m_pGpsLT->setGeometry(nw-XOFFSET-nWidth,nh-YOFFSET-nHeight,nWidth,nHeight);
					m_pGpsLT->update();
				}
			}
			if (m_pLB)
			{
				int nw = m_pLB->rect().width();
				int nh = m_pLB->rect().height();
				int nFontsize = min(nw,nh)/FONTSIZE;
				if (m_pWWANRLevelLB)
				{
					QFont ft = m_pWWANRLevelLB->font();
					ft.setPixelSize(nFontsize);
					if (0 == m_pWWANRLevelLB->text().length())
					{
						m_pWWANRLevelLB->setText(CLanguage::strSignal);
					}
					int nWidth = m_pWWANRLevelLB->fontMetrics().width(m_pWWANRLevelLB->text());
					
					int nHeight = m_pWWANRLevelLB->fontMetrics().height();
					m_pWWANRLevelLB->setGeometry(XOFFSET,nh-YOFFSET-nHeight,nWidth,nHeight);
					m_pWWANRLevelLB->update();
				}
				if (m_pGpsLB)
				{
					QFont ft = m_pGpsLB->font();
					ft.setPixelSize(nFontsize);
					if (0 == m_pGpsLB->text().length())
					{
						m_pGpsLB->setText(CLanguage::strGps);
					}
					int nWidth = m_pGpsLB->fontMetrics().width(m_pGpsLB->text());
					
					int nHeight = m_pGpsLB->fontMetrics().height();
					m_pGpsLB->setGeometry(nw-nWidth-XOFFSET,nh-YOFFSET-nHeight,nWidth,nHeight);
					m_pGpsLB->update();
				}
			}
			if (m_pRT)
			{
				int nw = m_pRT->rect().width();
				int nh = m_pRT->rect().height();
				int nFontsize = min(nw,nh)/FONTSIZE;
				if (m_pWWANRLevelRT)
				{
					QFont ft = m_pWWANRLevelRT->font();
					ft.setPixelSize(nFontsize);
					if (0 == m_pWWANRLevelRT->text().length())
					{
						m_pWWANRLevelRT->setText(CLanguage::strSignal);
					}
					int nWidth = m_pWWANRLevelRT->fontMetrics().width(m_pWWANRLevelRT->text());
					
					int nHeight = m_pWWANRLevelRT->fontMetrics().height();
					m_pWWANRLevelRT->setGeometry(XOFFSET,nh-YOFFSET-nHeight,nWidth,nHeight);
					m_pWWANRLevelRT->update();
				}
				if (m_pGpsRT)
				{
					QFont ft = m_pGpsRT->font();
					ft.setPixelSize(nFontsize);
					if (0 == m_pGpsRT->text().length())
					{
						m_pGpsRT->setText(CLanguage::strGps);
					}
					int nWidth = m_pGpsRT->fontMetrics().width(m_pGpsRT->text());
				
					int nHeight = m_pGpsRT->fontMetrics().height();
					m_pGpsRT->setGeometry(nw-nWidth-XOFFSET,nh-YOFFSET-nHeight,nWidth,nHeight);
					m_pGpsRT->update();
				}
			}
		    if (m_pRB)
		    {
				int nw = m_pRB->rect().width();
				int nh = m_pRB->rect().height();
				int nFontsize = min(nw,nh)/FONTSIZE;
				if (m_pWWANRLevelRB)
				{
					QFont ft = m_pWWANRLevelRB->font();
					ft.setPixelSize(nFontsize);
					if (0 == m_pWWANRLevelRB->text().length())
					{
						m_pWWANRLevelRB->setText(CLanguage::strSignal);
					}
					int nWidth = m_pWWANRLevelRB->fontMetrics().width(m_pWWANRLevelRB->text());
				
					int nHeight = m_pWWANRLevelRB->fontMetrics().height();
					m_pWWANRLevelRB->setGeometry(XOFFSET,nh-YOFFSET-nHeight,nWidth,nHeight);
					m_pWWANRLevelRB->update();
				}
				if (m_pGpsRB)
				{
					QFont ft = m_pGpsRB->font();
					ft.setPixelSize(nFontsize);
					if (0 == m_pGpsRB->text().length())
					{
						m_pGpsRB->setText(CLanguage::strGps);
					}
					int nWidth = m_pGpsRB->fontMetrics().width(m_pGpsRB->text());
				
					int nHeight = m_pGpsRB->fontMetrics().height();
					m_pGpsRB->setGeometry(nw-nWidth-XOFFSET,nh-YOFFSET-nHeight,nWidth,nHeight);
					m_pGpsRB->update();
				}
		    }
		
			break;
		}
	default:
		{
			break;
		}
	}
}
BOOL CFramelessDialog::loginANT()
{
	QUiLoader loader;
	QString curPath = QCoreApplication::applicationDirPath()+DIR+UIPATH+"\\login.ui";
	QFile file(curPath);
	file.open(QFile::ReadOnly);
	m_pLoginWidget = (QDialog*)loader.load(&file,this);
	if(!m_pLoginWidget)
	{

		return FALSE;
	}
	m_pLoginWidget->setModal(true);
	m_pLoginWidget->setWindowFlags(Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
	QFrame* pLoging = qFindChild<QFrame*>(m_pLoginWidget,"loginingWidget");
	if(pLoging)
	{
		pLoging->hide();

	}
	QLabel* pLoginFailedLabel = qFindChild<QLabel*>(m_pLoginWidget,"loginFailedLabel");
	if (pLoginFailedLabel)
	{
		pLoginFailedLabel->hide();
	}
	QLabel* pNoInternetLabel = qFindChild<QLabel*>(m_pLoginWidget,"noInternetLabel");
	if (pNoInternetLabel)
	{
		pNoInternetLabel->hide();
	}
	QLabel* pNoServiceLabel = qFindChild<QLabel*>(m_pLoginWidget,"noServiceLabel");
	if (pNoServiceLabel)
	{
		pNoServiceLabel->hide();
	}
	CLanguage::ReadTxtByUi(m_pLoginWidget,"login");
	if (QLocale::Chinese == CLanguage::m_langId)
	{
		CLanguage::ReadTxtByUi(m_pLoginWidget,"login",TRUE);
	}

	
	QPushButton* pBtnOk = qFindChild<QPushButton*>(m_pLoginWidget,"btnOk");
	QPushButton* pBtnCancel = qFindChild<QPushButton*>(m_pLoginWidget,"btnCancel");
	QPushButton* pBtnClose = qFindChild<QPushButton*>(m_pLoginWidget,"btnClose");
	QCheckBox* pCheck = qFindChild<QCheckBox*>(m_pLoginWidget,"pwdCheck");
	m_pUserNameEdit = qFindChild<QLineEdit*>(m_pLoginWidget,"userNameEdit");
	m_pPwdEdit = qFindChild<QLineEdit*>(m_pLoginWidget,"passWordEdit");
	if (m_pPwdEdit)
	{
		m_pPwdEdit->setEchoMode(QLineEdit::Password);
		connect((const QObject*)m_pPwdEdit,SIGNAL(returnPressed()),SLOT(clickLogin()));
		if (CLogin::bRememberPwd)
		{
			rc4_state rcstate;
			CLogin::rc4_crypt(&rcstate,(unsigned char*)CLogin::szPwd,strlen(CLogin::szPwd));
			m_pPwdEdit->setText(CLogin::szPwd);
		}	
	}
	if (m_pUserNameEdit && CLogin::bRememberPwd)
    {
		rc4_state rcstate;
		CLogin::rc4_crypt(&rcstate,(unsigned char*)CLogin::szName,strlen(CLogin::szName));
		m_pUserNameEdit->setText(CLogin::szName);
    }
	if (pBtnOk)
	{
		connect((const QObject*)pBtnOk,SIGNAL(clicked()),SLOT(clickLogin()));
	}
	if (pBtnCancel)
	{
		connect((const QObject*)pBtnCancel,SIGNAL(clicked()),SLOT(clickCancelInLogin()));
	}
	if (pBtnClose)
	{
		connect((const QObject*)pBtnClose,SIGNAL(clicked()),SLOT(quitApp()));
	}
	if (pCheck)
	{
		connect((const QObject*)pCheck,SIGNAL(stateChanged(int)),SLOT(checkRemember(int)));
		pCheck->setChecked(CLogin::bRememberPwd!=0);
	}
	connect((const QObject*)pDialog,SIGNAL(loginResult(int)),SLOT(showLoginResult(int)));
	CLanguage::UpdatePageLanguage(m_pLoginWidget);
	QRect rc = m_pLoginWidget->geometry();
	QDesktopWidget* pdesk = QApplication::desktop();
	int nx = 0;
	int ny = 0;
	int nWidth = rc.width();
	int nHeight = rc.height();
	if (pdesk)
	{
		int nIndex = pdesk->screenNumber();
		QRect rcScreen = pdesk->screenGeometry(nIndex);
		nx = (rcScreen.width()-nWidth)/2;//(pdesk->width()-nWidth)/2;
		ny = (rcScreen.height()-nHeight)/2;//(pdesk->height()-nHeight)/2;
	}
	if (nx <0)
	{
		nx = 0;
	}
	if (ny < 0)
	{
		ny = 0;
	}
	setGeometry(nx,ny,nWidth,nHeight);
	m_pLoginWidget->setGeometry(0,0,nWidth,nHeight);
	show();
	return FALSE;
}
void CFramelessDialog::createLanguageMenu()
{
	m_pLanguageMenu = new QMenu((QWidget*)m_pBtnSet->parent());
	if (m_pLanguageMenu)
	{
		m_pEngAction = new QAction("English",m_pLanguageMenu);//new QAction(m_icoTray,"English",m_pLanguageMenu);
		m_pEspAction = new QAction("Spanish",m_pLanguageMenu);//new QAction(m_icoTray,"Spanish",m_pLanguageMenu);
		m_pLanguageMenu->addAction(m_pEspAction);
		m_pLanguageMenu->addAction(m_pEngAction);
		if (QLocale::Chinese == CLanguage::m_langId)
		{
			m_pChnAction = new QAction("chinese",m_pLanguageMenu); //QAction(m_icoTray,"chinese",m_pLanguageMenu);
			m_pLanguageMenu->addAction(m_pChnAction);
		}
        if (m_pBtnSet)
        {
			m_pBtnSet->setMenu(m_pLanguageMenu);
        }
	}
}
void CFramelessDialog::resizeMap()
{
	if (CDllFunc::m_pFunMoveMap && m_pMap)
	{
		QRect rc = m_pMap->geometry();
		(*CDllFunc::m_pFunMoveMap)(0,0,rc.width(),rc.height(),eOfflinePlay);
	}
}
void CFramelessDialog::showMap(BOOL bShow)
{
	QWidget* pLeftWidget = qFindChild<QWidget*>(m_pChild,"leftWidget");
	if (pLeftWidget)
	{
		if (bShow)
		{
			pLeftWidget->show();	
		} 
		else
		{
			pLeftWidget->hide();	
		}

	}
	if (focusWidget())
	{
		focusWidget()->clearFocus();
	}
	resizeMap();
}

void CFramelessDialog::clickedMap()
{
	QWidget* pLeftWidget = qFindChild<QWidget*>(m_pChild,"leftWidget");
	if (pLeftWidget)
	{
		if (pLeftWidget->isVisible())
		{
			pLeftWidget->hide();
			m_bShowMap = FALSE;
		}
		else
		{
			pLeftWidget->show();
			m_bShowMap = TRUE;
			m_bFull = FALSE;
			if (m_pLT)
			{
				m_pLT->m_bFull = FALSE;
			}
			if (m_pLB)
			{
				m_pLB->m_bFull = FALSE;
			}
			if (m_pRT)
			{
				m_pRT->m_bFull = FALSE;
			}
			if (m_pRB)
			{
				m_pRB->m_bFull = FALSE;
			}
		}
	}
	if (focusWidget())
	{
		focusWidget()->clearFocus();
	}
	resizeMap();
	
}
void CFramelessDialog::clickedFullScreen()
{
	if (m_bShowOpen)
	{
		return;
	}
    if (m_pCurFull)
    {
		m_pCurFull->mouseDoubleClickEvent(NULL);
    }
	updateOSD(ANYINDEX);
}
void CFramelessDialog::clickedPlay()
{
	if (focusWidget())
	{
		focusWidget()->clearFocus();
	}
	if (!m_pRight || (!m_bSDK && m_VectorFileInfo.size()<1))
	{
		return;
	}
	
	int nVideoIndex = m_nCurWndIndex;
	if (0 == nVideoIndex)
	{
		return;
	}
	BOOL *bPlaying = NULL;
	BOOL *pbPlayOrPauseFlag = &m_bPlayOrPauseFlagLT;
	
	FileInfo* pPlayInfo = NULL;
	if (m_nCurFileIndex>=0 && m_nCurFileIndex<m_VectorFileInfo.size())
	{
		pPlayInfo = m_VectorFileInfo[m_nCurFileIndex];
	}
	if (*pbPlayOrPauseFlag == FALSE)//go to play
	{
		if (m_pBtnPlay)
		{
			m_pBtnPlay->setStyleSheet(m_strStylePause);
		}
		if (m_bSDK)
		{
			pauseAll(TRUE);
			if (m_bShowOpen)
			{
				PlayGroupInRow(0);
			} 
			else
			{
				for(int k=0;k<m_vtPluginInterface.size();k++)
				{
					m_vtPluginInterface[k]->ANTOfflineFileSDK_Control_PlayAllChannel();
				}
			}
			
		} 
		else
		{
			if (pPlayInfo != NULL && PLAYING == pPlayInfo->iPlayingStateFlag)
			{
				SetVideoPlayerControlInfo(m_nCurWndIndex,m_strCtrlPlay);

				*pbPlayOrPauseFlag = TRUE;
			}
			else
			{
				if (pPlayInfo)
				{
					createVideo(pPlayInfo->iVideoWndIndex,pPlayInfo->strFileName);				
					PlayVideoByFileInfo(pPlayInfo,PLAY);
					updateCurVideo(LTWNDINDEX);
					showVideo();
				}
			}
		}
		
	}
	else//go to pause
	{
		if (m_bSDK)
		{
			if (m_pBtnPlay)
			{
				m_pBtnPlay->setStyleSheet(m_strStylePlay);
			}
			for(int k=0;k<m_vtPluginInterface.size();k++)
			{
				m_vtPluginInterface[k]->ANTOfflineFileSDK_Control_PauseAllChannel();
			}
			pauseAll(FALSE);
		} 
		else
		{
			if (pPlayInfo != NULL)
			{
				if (m_pBtnPlay)
				{
					m_pBtnPlay->setStyleSheet(m_strStylePlay);
				}
				SetVideoPlayerControlInfo(m_nCurWndIndex,m_strCtrlPause);
				*pbPlayOrPauseFlag = FALSE;
			}
		}				
	}	
}
void CFramelessDialog::clickedStop()
{
	if (!m_pRight || (!m_bSDK &&m_VectorFileInfo.size()<1))
	{
		return;
	}
	if (m_bSDK)
	{
		for (int i=0;i<m_vtPluginInterface.size();i++)
		{
			m_vtPluginInterface[i]->ANTOfflineFileSDK_Control_StopAllChannel();
		}
		if (CDllFunc::m_pFuncClearPath)
		{
			m_setTime.clear();
			m_nCurSecond = 0;
			(*CDllFunc::m_pFuncClearPath)(0,eOfflinePlay);
		}
		m_nCurSecond=0;
		m_nStartSecond=0;
		m_nCurDuration = 0;
	} 
	else
	{
		int nVideoIndex = m_nCurWndIndex;
		if (0 == nVideoIndex)
		{
			return;
		}
		FileInfo* fInfo = NULL;
		if (m_nCurFileIndex>=0 && m_nCurFileIndex<m_VectorFileInfo.size())
		{
			fInfo = m_VectorFileInfo[m_nCurFileIndex];
		}
		if (fInfo)
		{
			PlayVideoByFileInfo(fInfo,STOP);
			m_mpStrExtend.clear();
			fInfo->iPlayingStateFlag = NOTPLAY;
			fInfo->iCurTime = 0;
		}  
	}
	playAll(FALSE);
	pauseAll(FALSE);
	showVideo(FALSE);
	soundAll(TRUE);
	showAllGps(TRUE);
	updateCurVideo(ANYINDEX);	
	showOpen();
	if (m_pLT)
	{
		m_pLT->m_bFull = FALSE;
	}
	if (m_pLB)
	{
		m_pLB->m_bFull = FALSE;
	}
	if (m_pRT)
	{
		m_pRT->m_bFull = FALSE;
	}
	if (m_pRB)
	{
		m_pRB->m_bFull = FALSE;
	}
	m_pCurFull = m_pLT;
	
}
void CFramelessDialog::clickedSound()
{
	int iWndIndex = m_nCurWndIndex;
	if (0 == iWndIndex)
	{
		return;
	}
	BOOL * bSound = NULL;
	int iVolume = 0;
	switch(iWndIndex)
	{
	case LTWNDINDEX:
		{
			bSound = &m_bSoundOrNotFlagLT;
			iVolume = m_iVolumeLT;
			break;
		}
	case RTWNDINDEX:
		{
			bSound = &m_bSoundOrNotFlagRT;
			iVolume = m_iVolumeRT;
			break;
		}
	case LBWNDINDEX:
		{
			bSound = &m_bSoundOrNotFlagLB;
			iVolume = m_iVolumeLB;
			break;
		}
	case RBWNDINDEX:
		{
			bSound = &m_bSoundOrNotFlagRB;
			iVolume = m_iVolumeRB;
			break;
		}
	}
	if (!bSound)
	{
		return;
	}
	if (*bSound)
	{
		SetVideoPlayerControlInfo(m_nCurWndIndex,m_strCtrlNotSound);
		*bSound = FALSE;
	} 
	else
	{
		SetVideoPlayerControlInfo(m_nCurWndIndex,m_strCtrlSound);
		*bSound = TRUE;
	}
	updateVolume();
}
void CFramelessDialog::clickedGps()
{
	int iWndIndex = m_nCurWndIndex;
	if (0 == iWndIndex)
	{
		return;
	}
	BOOL * bExtend = NULL;
	bExtend = &m_bExtendFlagLT;
	if (!bExtend)
	{
		return;
	}
	if (*bExtend)
	{
		showAllGps(FALSE);
		if (m_pBtnGps)
		{
			m_pBtnGps->setStyleSheet(m_strStyleNoExtend);
		}
		SetVideoPlayerControlInfo(LTWNDINDEX,m_strCtrlNotExtInfo);

		*bExtend = FALSE;
		if (m_pWWANRLevelLB)
		{
			m_pWWANRLevelLB->hide();
		}
		if (m_pWWANRLevelLT)
		{
			m_pWWANRLevelLT->hide();
		}
		if (m_pWWANRLevelRB)
		{
			m_pWWANRLevelRB->hide();
		}
		if (m_pWWANRLevelRT)
		{
			m_pWWANRLevelRT->hide();
		}
		if (m_pGpsLT)
		{
			m_pGpsLT->hide();
		}
		if (m_pGpsLB)
		{
			m_pGpsLB->hide();
		}
		if (m_pGpsRT)
		{
			m_pGpsRT->hide();
		}
		if (m_pGpsRB)
		{
			m_pGpsRB->hide();
		}
	} 
	else
	{
		showAllGps(TRUE);
		if (m_pBtnGps)
		{
			m_pBtnGps->setStyleSheet(m_strStyleExtend);
		}
		SetVideoPlayerControlInfo(m_nCurWndIndex,m_strCtrlExtInfo);
		*bExtend = TRUE;
		
		if (m_pWWANRLevelLB)
		{
			m_pWWANRLevelLB->show();
		}
		if (m_pWWANRLevelLT)
		{
			m_pWWANRLevelLT->show();
		}
		if (m_pWWANRLevelRB)
		{
			m_pWWANRLevelRB->show();
		}
		if (m_pWWANRLevelRT)
		{
			m_pWWANRLevelRT->show();
		}
		if (m_pGpsLT)
		{
			m_pGpsLT->show();
		}
		if (m_pGpsLB)
		{
			m_pGpsLB->show();
		}
		if (m_pGpsRT)
		{
			m_pGpsRT->show();
		}
		if (m_pGpsRB)
		{
			m_pGpsRB->show();
		}
	}
}
void CFramelessDialog::clickedSlow()
{
	SetVideoPlayerControlInfo(m_nCurWndIndex,m_strCtrlSlow);
}
void CFramelessDialog::clickedFast()
{
	SetVideoPlayerControlInfo(m_nCurWndIndex,m_strCtrlFast);
}
void CFramelessDialog::clickedUpdate()
{
	if (m_listUpdate.size()>0)
	{
		if (!ShowMessageBox("strUpdate","strUpdateClose",eInfoTip))
		{
			return;
		}
		m_bUpdate = TRUE;
		wchar_t strParam[3000]={0};
		wchar_t strFile[500]={0};
		QString strUpdate = m_listUpdate.join(FILESEP);
		SHELLEXECUTEINFO updateProcess;
		//QString strExe = QCoreApplication::applicationDirPath();
		QString strUpdateFile = QCoreApplication::applicationDirPath()+"/Update.exe";
		wsprintf(strParam,L"%s %s",m_strUpdateUrl.toStdWString().c_str(),strUpdate.toStdWString().c_str());
		wsprintf(strFile,L"%s",strUpdateFile.toStdWString().c_str());
		memset(&updateProcess,0,sizeof(updateProcess));
		updateProcess.cbSize = sizeof(SHELLEXECUTEINFO);
		updateProcess.fMask=(SEE_MASK_DOENVSUBST|SEE_MASK_FLAG_DDEWAIT|0x04000000|SEE_MASK_NOCLOSEPROCESS|SEE_MASK_NO_CONSOLE);
		updateProcess.hwnd = NULL;
		updateProcess.lpVerb=L"Open";
		updateProcess.lpFile = strFile;
		updateProcess.lpParameters = strParam;
        updateProcess.lpDirectory = NULL;
		updateProcess.nShow = SW_HIDE;
		updateProcess.hInstApp = NULL;
		updateProcess.lpIDList = NULL;
		updateProcess.hIcon = NULL;
		updateProcess.lpClass = NULL;
		updateProcess.hkeyClass = NULL;
		updateProcess.hMonitor = NULL;
		updateProcess.dwHotKey = NULL;
        updateProcess.hProcess = NULL;
		ShellExecuteEx(&updateProcess);
		quitApp();
	}
}
void CFramelessDialog::clickedVolumeBar()
{
	if (!m_pVolumeBar)
	{
		return;
	}
	if (focusWidget())
	{
		focusWidget()->clearFocus();
	}
	QPoint pt1 = QCursor::pos();
	QPoint pt = m_pVolumeBar->mapFromGlobal(pt1);
	QRect rc = m_pVolumeBar->geometry();
    m_pVolumeBar->setGeometry(rc.left(),rc.top(),pt.x(),rc.height());
}
void CFramelessDialog::pressVolumeBar()
{
	if (focusWidget())
	{
		focusWidget()->clearFocus();
	}
}
void CFramelessDialog::clickTrayIcon()
{
	showNormal();
}
void CFramelessDialog::ShowLoging(BOOL bShow)
{
	if (m_pLoginWidget)
	{
		QWidget* pLogin = qFindChild<QWidget*>(m_pLoginWidget,"loginWidget");
		if (pLogin)
		{
			if (bShow)
			{
				pLogin->hide();
			} 
			else
			{
				pLogin->show();
			}
		}
		QWidget* pBtnOk = qFindChild<QWidget*>(m_pLoginWidget,"btnOk");
		QFrame* pLoging = qFindChild<QFrame*>(m_pLoginWidget,"loginingWidget");
		if (pBtnOk)
		{
			if (bShow)
			{
				pBtnOk->hide();
			} 
			else
			{
				pBtnOk->show();
			}
		}
		if(pLoging)
		{
			m_pLogining = pLoging;
	        if (bShow)
	        {
				pLoging->show();
				m_nMoveTimer = startTimer(MOVEINVAL);
	        } 
	        else
	        {
				pLoging->hide();
				if (0 != m_nMoveTimer)
				{
					killTimer(m_nMoveTimer);
				}
	        }
		}
	}
}
void CFramelessDialog::clickLogin()
{
	m_bCancelLogin = FALSE;
	QLabel* pNoInternetLabel = qFindChild<QLabel*>(m_pLoginWidget,"noInternetLabel");
	if (pNoInternetLabel)
	{
		pNoInternetLabel->hide();
	}
	QLabel* pLoginFailedLabel = qFindChild<QLabel*>(m_pLoginWidget,"loginFailedLabel");
	if (pLoginFailedLabel)
	{
		pLoginFailedLabel->hide();
	}
	if (m_pLoginWidget)
	{
		ShowLoging(TRUE);
	}
	QString strName("");
	QString strPwd("");
	if (m_pUserNameEdit)
	{
		strName = m_pUserNameEdit->text();
	}
	if (m_pPwdEdit)
	{
		strPwd = m_pPwdEdit->text();
	}
	memset(CLogin::szName,0,NAMELEN);
	memcpy(CLogin::szName,strName.toStdString().c_str(),strName.length());
	memset(CLogin::szPwd,0,NAMELEN);
	memcpy(CLogin::szPwd,strPwd.toStdString().c_str(),strPwd.length());
	if (strName.length()<1 || strPwd.length()<1)
	{
		ShowMessageBox(ERRORTIP,"userNameEmpty",eErrorTip);
		ShowLoging(FALSE);
		return;
	}
	HANDLE hLogin = ::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)CFramelessDialog::ThreadLogin,NULL,0,NULL);
	CloseHandle(hLogin);
}
void CFramelessDialog::clickCancelInLogin()
{
	m_bCancelLogin = TRUE;
	QFrame* pLoging = qFindChild<QFrame*>(m_pLoginWidget,"loginingWidget");
	if (pLoging)
	{
		if (pLoging->isVisible())
		{
			ShowLoging(FALSE);
		}
		else
		{
			quitApp();
		}
	}
}
void CFramelessDialog::clickSetLanguage()
{
	if (m_pLanguageMenu)
	{
		int x = 0;
		int y = 0;
		if (m_pBtnSet)
		{
			QRect rc = m_pBtnSet->geometry();
			x = rc.left();
			y = rc.bottom();
		}
		if (m_pLanguageMenu->isVisible())
		{
			m_pLanguageMenu->hide();
		} 
		else
		{
			QRect rc = m_pLanguageMenu->geometry();
			m_pLanguageMenu->show();
		}
	}
}
void CFramelessDialog::clickOkInSelectChannel()
{
	if (m_pSelectDay)
	{
		BOOL bChannel1 = FALSE;
		BOOL bChannel2 = FALSE;
		BOOL bChannel3 = FALSE;
		BOOL bChannel4 = FALSE;
		QCheckBox* pCheck1 = qFindChild<QCheckBox*>(m_pSelectDay,"channel1");
		QCheckBox* pCheck2 = qFindChild<QCheckBox*>(m_pSelectDay,"channel2");
		QCheckBox* pCheck3 = qFindChild<QCheckBox*>(m_pSelectDay,"channel3");
		QCheckBox* pCheck4 = qFindChild<QCheckBox*>(m_pSelectDay,"channel4");
		int nChannel = 0;
		if (pCheck1)
		{
			bChannel1 = Qt::Checked == pCheck1->checkState();
			if (bChannel1)
			{
				nChannel |= 1;
			}
		}
		if (pCheck2)
		{
			bChannel2 = Qt::Checked == pCheck2->checkState();
			if (bChannel2)
			{
				nChannel |= 2;
			}
		}
		if (pCheck3)
		{
			bChannel3 = Qt::Checked == pCheck3->checkState();
			if (bChannel3)
			{
				nChannel |= 4;
			}
		}
		if (pCheck4)
		{
			bChannel4 = Qt::Checked == pCheck4->checkState();
			if (bChannel4)
			{
				nChannel |= 8;
			}
		}
		if (0 == nChannel)
		{
			ShowMessageBox(WARNINGTIP,"strSelectCamera",eWarningTip);
		} 
		else
		{
			m_pSelectDay->accept();
		}
	}
}
void CFramelessDialog::checkRemember(int nState)
{
	CLogin::bRememberPwd = nState;
}
void CFramelessDialog::checkAll(int nState)
{
	QCheckBox* pCheck1 = qFindChild<QCheckBox*>(m_pSelectDay,"channel1");
	QCheckBox* pCheck2 = qFindChild<QCheckBox*>(m_pSelectDay,"channel2");
	QCheckBox* pCheck3 = qFindChild<QCheckBox*>(m_pSelectDay,"channel3");
	QCheckBox* pCheck4 = qFindChild<QCheckBox*>(m_pSelectDay,"channel4");
	if (pCheck1)
	{
		pCheck1->setChecked(nState!=0);
	}
	if (pCheck2)
	{
		pCheck2->setChecked(0 != nState);
	}
	if(pCheck3)
	{
		pCheck3->setChecked(0 != nState);
	}
	if(pCheck4)
	{
		pCheck4->setChecked(0!=nState);
	}
}
void CFramelessDialog::activedTrayIcon ( QSystemTrayIcon::ActivationReason reason )
{
	if (QSystemTrayIcon::Trigger == reason)
	{
		showNormal();
	}	
}
void CFramelessDialog::tableViewPortEnter()
{
	if (!m_bMouseDown)
	{
		QCursor curs(Qt::ArrowCursor);
		setCursor(curs);
	}
}
void CFramelessDialog::tableItemEnter(const QModelIndex & index)
{
	if (!m_bMouseDown)
	{
		QCursor curs(Qt::ArrowCursor);
		setCursor(curs);
	}
}

void CFramelessDialog::cellClicked(int row,int column)
{
	if (m_bSDK)
	{
		pauseAll(TRUE);
		if (m_nCurFileIndex != row || m_bShowOpen)
		{
			PlayGroupInRow(row);
			m_nCurFileIndex = row;
		}	
	} 
	else
	{
		if (m_nCurFileIndex != row || m_bShowOpen)
		{
			if (m_nCurFileIndex >=0 && m_nCurFileIndex < m_VectorFileInfo.size() && m_VectorFileInfo[m_nCurFileIndex])
			{
				PlayVideoByFileInfo(m_VectorFileInfo[m_nCurFileIndex],STOP);
				m_mpStrExtend.clear();
				if (CDllFunc::m_pFuncClearPath)
				{
					m_setTime.clear();
					m_nCurSecond = 0;
					(*CDllFunc::m_pFuncClearPath)(0,eOfflinePlay);
				}
			}
			if (row >=0 && row < m_VectorFileInfo.size() && m_VectorFileInfo[row])
			{
				PlayVideoByFileInfo(m_VectorFileInfo[row],PLAY);
			}
			m_nCurFileIndex = row;
			showVideo();
			updateCurVideo(LTWNDINDEX);
		}		
	}
}

void CFramelessDialog::progressBarAction(int nAction)
{
	if (QAbstractSlider::SliderPageStepAdd == nAction || QAbstractSlider::SliderPageStepSub == nAction)
	{
		QPoint pt = QCursor::pos();
		if (m_pProgress)
		{
			QPoint pt2 = m_pProgress->mapFromGlobal(pt);
			
			float fRate = (float)pt2.x()/(float)m_pProgress->width();
			int nCurTime = fRate*m_pProgress->maximum();
            updateProgress(nCurTime);
			if (m_bSDK && m_mpSDKFileInfo.size()<1)
			{
				nCurTime += m_nStartSecond;
			}
			QString str = m_strCtrlSetProgress +QString::number(nCurTime)+ITEMSEP+QString::number(m_pProgress->maximum()) + ",1";
			SetVideoPlayerControlInfo(m_nCurWndIndex,str);
		}
	}
	
}
void CFramelessDialog::progressBarMoved(int nValue)
{
	if (m_pProgress  && m_pProgress->maximum()>0)
	{
		updateProgress(nValue);
	}
}
void CFramelessDialog::progressBarReleased()
{
	if (m_pProgress  && m_pProgress->maximum()>0)
	{
		int nValue = m_pProgress->value();
		if (m_bSDK && m_mpSDKFileInfo.size()<1)
		{
			nValue += m_nStartSecond;
		}
		QString str = m_strCtrlSetProgress +QString::number(nValue)+ITEMSEP+QString::number(m_pProgress->maximum()) + ",1";
		SetVideoPlayerControlInfo(LTWNDINDEX,str);		
	}
}

void CFramelessDialog::openModeActivated(int nIndex)
{
	m_nStartSecond = 0;
	if (0 == nIndex )//LOCAL 
	{
		m_bSDK = FALSE;
		
		QStringList filters;
		filters //<<"all files(*.*)"
			//<< "H264 files (*.264)"
			//<<"avi files (*.avi)"
			<< "ts files (*.ts)";

		QFileDialog fileD(this,tr("select one or more file"), m_strPreFileDir,"ts files (*.ts)");
		
		fileD.setNameFilters(filters);
		QStringList fileNameList= fileD.getOpenFileNames(this,tr("select one or more file"), m_strPreFileDir,"ts files (*.ts)");
		if (fileNameList.size()>0)
		{
			setCurFileList(fileNameList);
			int n = fileNameList[0].lastIndexOf(DIR);
			if (-1 == n)
			{
				n = fileNameList[0].lastIndexOf(HTTPTAIL);
				if (-1 != fileNameList[0].lastIndexOf(HTTPTAIL))
				{
					m_strPreFileDir = fileNameList[0].left(n);
				}
			}
			else
			{
				m_strPreFileDir = fileNameList[0].left(n);
			}
		}
		if (FALSE == m_bSetEventFilter)
		{
			m_bSetEventFilter = TRUE;
			setEventFilterGpsAndWWanrx();
		}
		
		m_nModeIndex = FILEINDEX;
		updateOSD(ANYINDEX);
		m_nCurFileIndex = 0;
		if (m_pTableList)
		{
			m_pTableList->selectRow(m_nCurFileIndex);
		}
	} 
	else if (1 == nIndex || 2 == nIndex)//SDK DIR
	{
		m_bSDK = TRUE;
		
		if (!m_pdllVideoLT)
		{
			QString str;
			createVideo(ANYINDEX,str);
		}
		QString strDir;

		if (CDllFunc::m_pFunGetSdCardPath)
		{
			if(FALSE == (CDllFunc::m_pFunGetSdCardPath)((HWND)winId(),m_szSDKPath))
			{
				return;
			}
			strDir = m_szSDKPath;	
		}
		if(strDir.length() >0)   
		{
			clearFileListInfo();
			m_nCurFileIndex = 0;
			QDir sdDir(strDir);
			QStringList strList = sdDir.entryList(QDir::Dirs);
			QStringList listDate;
			bool bRm = false;
			int isSuccess = FALSE;
			if (strList.size()<1)
			{
				bRm = true;
			}
			if (SDKINDEX == nIndex && bRm)
			{
				m_nCurSecond = 0;
				
				int nFileGroupCount = FILECOUNT;
				int * npEndTime = new int[FILECOUNT];
				int * npStartTime = new int[FILECOUNT];
				int * npType = new int[FILECOUNT];
				memset(npEndTime,0,sizeof(int) * FILECOUNT);
				memset(npStartTime,0,sizeof(int) * FILECOUNT);
				memset(npType,0,sizeof(int) * FILECOUNT);
				CANTOfflineFileSDKAdapter* pAdapter = GetPlugin(RmType);
				if (pAdapter)
				{
					int nRet = pAdapter->ANTOfflineFileSDK_Control_OpenSDCard_WithDuration(
						strDir.toStdString().c_str(),
						TRUE,
						TRUE,
						TRUE,
						FALSE,
						FALSE,
						FALSE,
						FALSE,
						FALSE,
						&nFileGroupCount,
						&npEndTime,
						&npStartTime,
						&npType);
					if(nRet == 0)
					{
						isSuccess = TRUE;
					}
					else
					{
						delete [] npEndTime;
						delete [] npStartTime;
						delete [] npType;
						return;
					}
				}
				for (int kk=0;kk<nFileGroupCount;kk++)
				{
					m_mpSDKTimeInfo[npStartTime[kk]].first = npEndTime[kk];
					m_mpSDKTimeInfo[npStartTime[kk]].second = 0 == npType[kk]?false:true;
				}
				delete [] npEndTime;
				delete [] npStartTime;
				delete [] npType;
				
			}
			else 
			{
				QStringList listPath;
				ComFunc::m_mpPath.clear();
				ComFunc::GetOriginalVideoPath(strDir,ComFunc::m_mpPath);
                ComFunc::GetPathList(strDir,ComFunc::m_mpPath,listPath);
		
				ComFunc::m_nSearchCount = 0;
				if (listPath.size()<1)
				{
					return;
				} 
				char szDay[JSLEN]={0};
				m_nChannelFlag = 0;
				m_nRestoreChannelFlag = 0;
				int nItem=-1;
				if (ANT_SDK_SUCCESS != ShowSelectDayAndChannelDialog(listPath,szDay,&m_nChannelFlag,nItem))
				{
					return;
				}
				if (strlen(szDay)<1)
				{
					return;
				}
				if (nItem<0 || nItem>=listPath.size())
				{
					return;
				}
				int nType = ComFunc::m_mpPath[listPath[nItem]];
				strDir = listPath[nItem];
				if (WkpType == nType)
				{
					
					if(((CFramelessDialog*)pDialog)->GetPathFileInfo(strDir))
					{
						if (m_mpSDKFileInfo.size() < 1)
						{
							return;
						}
						SDKFMAP::iterator it = m_mpSDKFileInfo.begin();
						if (it->second.size()<1)
						{
							return;
						}
						//m_nStartSecond = it->first;
					    isSuccess = TRUE;
						PlayGroup(it);

					}
				} 
				else if(RmType == nType)
				{
					CANTOfflineFileSDKAdapter* pAdapter = GetPlugin(RmType);
					if (pAdapter)
					{
						int nFileGroupCount = FILECOUNT;
						int * npEndTime = new int[FILECOUNT];
						int * npStartTime = new int[FILECOUNT];
						int * npType = new int[FILECOUNT];
						memset(npEndTime,0,sizeof(int) * FILECOUNT);
						memset(npStartTime,0,sizeof(int) * FILECOUNT);
						memset(npType,0,sizeof(int) * FILECOUNT);
						int nRet = pAdapter->ANTOfflineFileSDK_Control_OpenDirWithDuration(
							strDir.toStdString().c_str(),
							m_nChannelFlag & 1,
							m_nChannelFlag & 2,
							m_nChannelFlag & 4,
							m_nChannelFlag & 8,
							FALSE,
							FALSE,
							FALSE,
							FALSE,
							&nFileGroupCount,
							&npEndTime,
							&npStartTime,
							&npType);
						if(nRet == 0)
						{
							isSuccess = TRUE;
						}
						else
						{
							delete [] npEndTime;
							delete [] npStartTime;
							delete [] npType;
							return;
						}
						for (int kk=0;kk<nFileGroupCount;kk++)
						{
							m_mpSDKTimeInfo[npStartTime[kk]].first = npEndTime[kk];
							m_mpSDKTimeInfo[npStartTime[kk]].second = 0 == npType[kk]?false:true;
						}
						delete [] npEndTime;
						delete [] npStartTime;
						delete [] npType;
					}
				}
				
			}
			if (isSuccess)
			{
				playAll(TRUE);

				pauseAll(TRUE);

				showVideo(TRUE);
				updateCurVideo(LTWNDINDEX);
				SDKTMAP::iterator itt = m_mpSDKTimeInfo.begin();
				if (itt != m_mpSDKTimeInfo.end())
				{
					m_nCurDuration = itt->second.first - itt->first;
					m_nStartSecond = itt->first;
					updateRangeForProgress(m_nCurDuration);
				}
			}
			setListInfo();
			m_nModeIndex = nIndex;
			if (m_pTableList)
			{
				m_pTableList->selectRow(m_nCurFileIndex);
			}
			updateOSD(ANYINDEX);

		}
	}
}

void CFramelessDialog::updateDuration(FileInfo* info)
{
	if (!info)
	{
		return;
	}
	if (m_nCurWndIndex == info->iVideoWndIndex)
	{
		m_nCurDuration = info->iDuration;
		updateRangeForProgress(info->iDuration);
	}
}

void CFramelessDialog::quitApp()
{
	if (!m_bUpdate)
	{
		if (!ShowMessageBox("strExit","strExitOrNot",eInfoTip))
		{
			return;
		}
	}
	if (m_pTipsDialog )
	{
		m_pTipsDialog->hide();
		m_pTipsDialog->close();
	}
	killTimer(m_nTimeID);
	clickedStop();
	m_bIsRun = FALSE;
	
	if (m_pvideoDll)
	{
		char szWnd[50]={0};
		if (m_pLT && m_pFuncDispose)
		{
			m_pFuncDispose(1);
		}
		if (m_pLB && m_pFuncDispose)
		{
			m_pFuncDispose(3);
		}
		if (m_pRT && m_pFuncDispose)
		{
			m_pFuncDispose(2);
		}
		if (m_pRB && m_pFuncDispose)
		{
			m_pFuncDispose(4);
		}
		//m_pFuncParaRealPlay  = NULL;
		m_pFuncParaFileList =  NULL;
		m_pFuncPlayImpl       = NULL;
		m_pFuncUpdateVideoWnd = NULL;
		m_pFuncDispose        = NULL;
		m_pFuncDisconnect     = NULL;
		m_pFuncSetEventCallBack  = NULL;
		m_pFuncSetControlInfo = NULL;
		m_pFuncSetCustomFlag = NULL;
		m_pvideoDll->unload();
		delete m_pvideoDll;
		m_pvideoDll = NULL;
	}

	if (CDllFunc::m_pFunDeleteMap)
	{
		
		(*CDllFunc::m_pFunDeleteMap)(eOfflinePlay);
	}
	if (CDllFunc::m_pLibMap)
	{
		CDllFunc::m_pFuncSwithLanguage = NULL;
		CDllFunc::m_pFuncClearPath = NULL;
		CDllFunc::m_pFuncRefreshExtendInfo = NULL;
		CDllFunc::m_pLibMap->unload();
		CDllFunc::m_pLibMap = NULL;
	}
	for (int i=0;i<m_vtPluginDLL.size();i++)
	{
		if (m_vtPluginDLL[i].first)
		{
			m_vtPluginDLL[i].first->unload();
		}
	}
	
	SaveUserInfo();
	WSACleanup();
	
	if (m_pWWANRLevelLT)
	{
		m_pWWANRLevelLT->hide();
		delete m_pWWANRLevelLT;
		m_pWWANRLevelLT = NULL;
	}
	if (m_pWWANRLevelLB)
	{
		m_pWWANRLevelLB->hide();
		delete m_pWWANRLevelLB;
		m_pWWANRLevelLB = NULL;
	}
	if (m_pWWANRLevelRT)
	{
		m_pWWANRLevelRT->hide();
		delete m_pWWANRLevelRT;
		m_pWWANRLevelRT = NULL;
	}
	if (m_pWWANRLevelRB)
	{
		m_pWWANRLevelRB->hide();
		delete m_pWWANRLevelRB;
		m_pWWANRLevelRB = NULL;
	}
	if (m_pGpsLT)
	{
		m_pGpsLT->hide();
		delete m_pGpsLT;
		m_pGpsLT = NULL;
	}
	if (m_pGpsLB)
	{
		m_pGpsLB->hide();
		delete m_pGpsLB;
		m_pGpsLB = NULL;
	}
	if (m_pGpsRT)
	{
		m_pGpsRT->hide();
		delete m_pGpsRT;
		m_pGpsRT = NULL;
	}
	if (m_pGpsRB)
	{
		m_pGpsRB->hide();
		delete m_pGpsRB;
		m_pGpsRB = NULL;
	}
	if (m_pdllVideoLT)
	{
		m_pdllVideoLT->hide();
		delete m_pdllVideoLT;
		m_pdllVideoLT = NULL;
	}
	if (m_pdllVideoLB)
	{
		m_pdllVideoLB->hide();
		delete m_pdllVideoLB;
		m_pdllVideoLB = NULL;
	}
	if (m_pdllVideoRT)
	{
		m_pdllVideoRT->hide();
		delete m_pdllVideoRT;
		m_pdllVideoRT = NULL;
	}
	if (m_pdllVideoRB)
	{
		m_pdllVideoRB->hide();
		delete m_pdllVideoRB;
		m_pdllVideoRB = NULL;
	}
	if (m_pvideoLT)
	{
		m_pvideoLT->hide();
		delete m_pvideoLT;
		m_pvideoLT = NULL;
	}
	if (m_pvideoLB)
	{
		m_pvideoLB->hide();
		delete m_pvideoLB;
		m_pvideoLB = NULL;
	}
	if (m_pvideoRT)
	{
		m_pvideoRT->hide();
		delete m_pvideoRT;
		m_pvideoRT = NULL;
	}
	if (m_pvideoRB)
	{
		m_pvideoRB->hide();
		delete m_pvideoRB;
		m_pvideoRB = NULL;
	}
	if (m_pLT)
	{
		m_pLT->hide();
		delete m_pLT;
		m_pLT = NULL;
	}
	m_pCurFull = NULL;
	if (m_pLB)
	{
		m_pLB->hide();
		delete m_pLB;
		m_pLB = NULL;
	}
	if (m_pRT)
	{
		m_pRT->hide();
		delete m_pRT;
		m_pRT = NULL;
	}
	if (m_pRB)
	{
		m_pRB->hide();
		delete m_pRB;
		m_pRB = NULL;
	}

	
	if (m_pTopLay)
	{
		delete m_pTopLay;
		m_pTopLay = NULL;
	}
	
	if (m_pSelectDay)
	{
		m_pSelectDay->hide();
	}
	
	saveConfig();
	
	if (m_psystemTray)
	{
		m_psystemTray->hide();
		m_psystemTray->setVisible(false);
		
		delete m_psystemTray;
		m_psystemTray = NULL;
		
	}
	
	
	if (m_pExitAction)
	{
		delete m_pExitAction;
		m_pExitAction = NULL;
	}
	if (m_pEngAction)
	{
		delete m_pEngAction;
		m_pEngAction = NULL;
	}
	if (m_pEspAction)
	{
		delete m_pEspAction;
		m_pEspAction = NULL;
	}
	if (m_pChnAction)
	{
		delete m_pChnAction;
		m_pChnAction = NULL;
	}
	if (m_pTrayMenu)
	{
		delete m_pTrayMenu;
		m_pTrayMenu = NULL;
	}
	if (m_pLanguageMenu)
	{
		delete m_pLanguageMenu;
		m_pLanguageMenu = NULL;
	}
	
	
	//DeleteCriticalSection(&g_crCheckFile);
	//DeleteCriticalSection(&g_crTsTime);
	CThreadCheckFile * pThreadCheck = CThreadCheckFile::GetInstance(this);
	if (pThreadCheck)
	{
		pThreadCheck->terminate();
	}
	
   close();
   
   if (pApplication)
   {
	   pApplication->quit();
   }
   
}
void CFramelessDialog::showExtend(int nWndIndex,const char* str,const char* szWWANRxLevel)
{
	if (!szWWANRxLevel || !str)
	{
		return;
	}
	bool bUpdate = false;
	
	switch(nWndIndex)
	{
	case LTWNDINDEX:
		{
			if (m_pWWANRLevelLT)
			{
				if (m_pWWANRLevelLT->text().length() != strlen(szWWANRxLevel))
				{
					bUpdate = true;
				}
				m_pWWANRLevelLT->setText(szWWANRxLevel);
			}
			if (m_pGpsLT)
			{
				
				if(m_pGpsLT->text().length() != strlen(str))
				{
					bUpdate = true;
				}
				m_pGpsLT->setText(str);	
			}
			if (bUpdate)
			{
				updateOSD(LTWNDINDEX);
			}
            
			break;
		}
	case LBWNDINDEX:
		{
			if (m_pWWANRLevelLB)
			{
				if (m_pWWANRLevelLB->text().length() != strlen(szWWANRxLevel))
				{
					bUpdate = true;
				}
				m_pWWANRLevelLB->setText(szWWANRxLevel);
			}
			if (m_pGpsLB)
			{
				if (m_pGpsLB->text().length() != strlen(str))
				{
					bUpdate = true;
				}
				m_pGpsLB->setText(str);
			}
			if (bUpdate)
			{
				updateOSD(LBWNDINDEX);
			}
			
			break;
		}
	case RTWNDINDEX:
		{
			if (m_pWWANRLevelRT)
			{
				if (m_pWWANRLevelRT->text().length() != strlen(szWWANRxLevel))
				{
					bUpdate = true;
				}
				m_pWWANRLevelRT->setText(szWWANRxLevel);
			}
			if (m_pGpsRT)
			{
				if (m_pGpsRT->text().length() != strlen(str))
				{
					bUpdate = true;
				}
				m_pGpsRT->setText(str);
			}
			if (bUpdate)
			{
				updateOSD(RTWNDINDEX);
			}
			
			break;
		}
	case RBWNDINDEX:
		{
			if (m_pWWANRLevelRB)
			{
				if (m_pWWANRLevelRB->text().length() != strlen(szWWANRxLevel))
				{
					bUpdate = true;
				}
				m_pWWANRLevelRB->setText(szWWANRxLevel);
			}
			if (m_pGpsRB)
			{
				if (m_pGpsRB->text().length() != strlen(str))
				{
					bUpdate = true;
				}
				m_pGpsRB->setText(str);	
			}
			if (bUpdate)
			{
				updateOSD(RBWNDINDEX);
			}
			
			break;
		}
	default:
		{
			int nLenGps = strlen(str);
			int nLenSignal = strlen(szWWANRxLevel);
			if (m_pWWANRLevelLT)
			{
				if (m_pWWANRLevelLT->text().length() != nLenSignal)
				{
					bUpdate = true;
				}
				m_pWWANRLevelLT->setText(szWWANRxLevel);
			}
			if (m_pWWANRLevelLB)
			{
				m_pWWANRLevelLB->setText(szWWANRxLevel);
			}
			if (m_pWWANRLevelRT)
			{
				m_pWWANRLevelRT->setText(szWWANRxLevel);
			}
			if (m_pWWANRLevelRB)
			{
				m_pWWANRLevelRB->setText(szWWANRxLevel);
			}

			if (m_pGpsLT)
			{
				if (m_pGpsLT->text().length() != nLenGps)
				{
					bUpdate = true;
				}
				m_pGpsLT->setText(str);	
			}
			if (m_pGpsLB)
			{
				m_pGpsLB->setText(str);
			}
			if (m_pGpsRT)
			{
				m_pGpsRT->setText(str);
			}
			if (m_pGpsRB)
			{
				m_pGpsRB->setText(str);	
			}
			if (bUpdate)
			{
				updateOSD(ANYINDEX);
			}
			break;
		}
	}
}
void CFramelessDialog::showUpdate()
{
	if (m_pBtnUpdate)
	{
		m_pBtnUpdate->show();
	}
	
}
void CFramelessDialog::showLoginResult(int nStatus)
{
	if (m_bCancelLogin)
	{
		return;
	}
	if (LoginSuccess == nStatus)
	{
		ShowMainPage();
	}
	else if (NamePwdError == nStatus)
	{
		m_nLoginFailedTimer = startTimer(2000);
	}
	else if(NotConnect == nStatus)
	{
		/*if (0 == strcmp(CLogin::szName,SPECIALNAME) && 0 == strcmp(CLogin::szPwd,SPECIALPWD))
		{
			ShowMainPage();
			return;
		}*/
		m_nNoInterNetTimer = startTimer(1000);
	}
	else if (HasServer == nStatus)
	{
		/*if (0 == strcmp(CLogin::szName,SPECIALNAME) && 0 == strcmp(CLogin::szPwd,SPECIALPWD))
		{
			ShowMainPage();
			return;
		}*/
		m_nServiceErrorTimer = startTimer(1000);
	}
}
void CFramelessDialog::playNewTsFile()
{
    m_bPlayImmediately = TRUE;
	WId id = pDialog->winId();
	AttachThreadInput(GetWindowThreadProcessId(GetForegroundWindow(),NULL),GetCurrentThreadId(),true);
	SetForegroundWindow(id);
	SetFocus(id);
	AttachThreadInput(GetWindowThreadProcessId(GetForegroundWindow(),NULL),GetCurrentThreadId(),false);
	if (m_bSetConnect)
	{
		PlayImmediately(m_strFileImmediate);
	}
}
void CFramelessDialog::hideExtend()
{
	if (m_pWWANRLevelLB)
	{
		m_pWWANRLevelLB->setText(CLanguage::strSignal);
		//m_pWWANRLevelLB->hide();
	}
	if (m_pGpsLB)
	{
		m_pGpsLB->setText(CLanguage::strGps);
		//m_pGpsLB->hide();
	}
	if (m_pWWANRLevelLT)
	{
		m_pWWANRLevelLT->setText(CLanguage::strSignal);
		//m_pWWANRLevelLT->hide();
	}
	if (m_pGpsLT)
	{
		m_pGpsLT->setText(CLanguage::strGps);
		//m_pGpsLT->hide();
	}
	if (m_pWWANRLevelRB)
	{
		m_pWWANRLevelRB->setText(CLanguage::strSignal);
		//m_pWWANRLevelRB->hide();
	}
	if (m_pGpsRB)
	{
		m_pGpsRB->setText(CLanguage::strGps);
		//m_pGpsRB->hide();
	}
	if (m_pWWANRLevelRT)
	{
		m_pWWANRLevelRT->setText(CLanguage::strSignal);
		//m_pWWANRLevelRT->hide();
	}
	if (m_pGpsRT)
	{
		m_pGpsRT->setText(CLanguage::strGps);
		//m_pGpsRT->hide();
	}
	updateOSD(ANYINDEX);
}
void CFramelessDialog::moveLeftRightSpliter(int nPos,int nIndex)
{
	//updateOSD(ANYINDEX);
	//resizeMap();
}
void CFramelessDialog::moveMapFileSpliter(int nPos,int nIndex)
{
	//resizeMap();
}
void CFramelessDialog::trigerExitMenu(QAction* pAction)
{
	if (pAction == m_pExitAction)
	{
		quitApp();
	}
}
void CFramelessDialog::trigerLanguageMenu(QAction* pAction)
{
	if (pAction == m_pEngAction)
	{
		if (languageEng == CLanguage::m_eLanguageType)
		{
			return;
		}
		CLanguage::m_eLanguageType = languageEng;
	}
	else if (pAction == m_pEspAction)
	{
		if (languageEsp == CLanguage::m_eLanguageType)
		{
			return;
		}
		CLanguage::m_eLanguageType = languageEsp;
	}
	else if (pAction == m_pChnAction)
	{
		if (languageChn == CLanguage::m_eLanguageType)
		{
			return;
		}
		CLanguage::m_eLanguageType = languageChn;
	}
	CLanguage::UpdatePageLanguage(this,TRUE);
	m_nTimeID = startTimer(1000);
}

void CFramelessDialog::updatePrivateInfo(int iWndIndex,int iIndex)
{
	    if (strlen(m_mpStrExtend[iWndIndex].c_str())<JSONLEN)
	    {
			return;
	    }
		std::set<int>::iterator it = m_setTime.find(m_nCurSecond);
		int nIndex = 1;
		if (m_setTime.end() == it)
		{
			m_setTime.insert(m_nCurSecond);
		} 
		else
		{
			nIndex= -1;
		}
		it = m_setTime.begin();
		int i = 0;
		std::set<int>::iterator itself = m_setTime.find(m_nCurSecond);
		for (it;it!=itself;it++)
		{
			i++;
		}
		nIndex = nIndex*i;
		
		(*CDllFunc::m_pFuncRefreshExtendInfo)(m_mpStrExtend[iWndIndex].c_str(),eOfflinePlay,nIndex,TRUE,eOfflinePlay);
}
void CFramelessDialog::ShowPrivateInfo(const char* szInfo)
{
	if (!CDllFunc::m_pFuncRefreshExtendInfo || !szInfo)
	{
		return;
	}
	std::set<int>::iterator it = m_setTime.find(m_nCurSecond);
	int nIndex = 1;
	if (m_setTime.end() == it)
	{
		m_setTime.insert(m_nCurSecond);
	} 
	else
	{
		nIndex= -1;
	}
	it = m_setTime.begin();
	int i = 0;
	std::set<int>::iterator itself = m_setTime.find(m_nCurSecond);
	for (it;it!=itself;it++)
	{
		i++;
	}
	nIndex = nIndex*i;
	(*CDllFunc::m_pFuncRefreshExtendInfo)(szInfo,eOfflinePlay,nIndex,TRUE,eOfflinePlay);

}
void CFramelessDialog::ShowMainPage()
{
	if (m_pLoginWidget)
	{
		m_pLoginWidget->hide();
	}
	if (0 != m_nMoveTimer)
	{
		killTimer(m_nMoveTimer);
	}
	
	hide();
	createMainPage();
	setAllConnect();
	if (m_bPlayImmediately && m_strFileImmediate.length()>3)
	{
		PlayImmediately(m_strFileImmediate);
	}
}
void CFramelessDialog::PlayImmediately(QString & strFile)
{
	m_nStartSecond = 0;
	m_bSDK = FALSE;
	
	if (m_VectorFileInfo.size()>0)
	{
		int nRowIndex = FindTsFile(strFile);//AddFile(m_strFileImmediate);
		if (INVALID == nRowIndex)
		{
			nRowIndex = AddFile(strFile);
			if(INVALID != nRowIndex)
			{
				m_pTableList->setRowCount(m_VectorFileInfo.size());
				AddRow(nRowIndex);
			}
		}
		if (INVALID != nRowIndex)
		{
			cellClicked(nRowIndex,0);
			if (m_pTableList)
			{
				m_pTableList->selectRow(m_nCurFileIndex);
			}
		}
	} 
	else
	{
		QStringList listFile(strFile);
		setCurFileList(listFile);
		if (FALSE == m_bSetEventFilter)
		{
			m_bSetEventFilter = TRUE;
			setEventFilterGpsAndWWanrx();
		}

		m_nModeIndex = FILEINDEX;
		updateOSD(ANYINDEX);
		m_nCurFileIndex = 0;
		if (m_pTableList)
		{
			m_pTableList->selectRow(m_nCurFileIndex);
		}
	}
	
}
int CFramelessDialog::AddFile(QString & strFile)
{
	QString strFileSize;
	QString strPath;
	QFileInfo info(strFile);
	if (!info.exists())
	{
		return -1;
	}
	long lFileSize = info.size();

	if (lFileSize>1000000)
	{
		float fFileSize = lFileSize/1000000.0;
		strFileSize = QString::number(fFileSize,'g',5)+" MB";

	}
	else
	{
		int iFileSize = lFileSize /1000;
		strFileSize = QString::number(iFileSize)+" KB";
	}
	FileInfo* pInfo = new FileInfo;
	pInfo->iVideoWndIndex = LTWNDINDEX;
	pInfo->lFileSize = lFileSize;
	pInfo->strFileName = info.fileName();
	strPath = info.path();
	if (strPath.endsWith(DIR))
	{
		pInfo->strFilePath = strPath.left(strPath.length()-1);
	} 
	else
	{
		pInfo->strFilePath = info.path();
	}

	pInfo->strFileSize = strFileSize;
	pInfo->iDuration = NOTSETDURATION;
	pInfo->iPlayingStateFlag = NOTPLAY;
	pInfo->bCalDurationFlag = FALSE;
	m_VectorFileInfo.push_back(pInfo);
	return m_VectorFileInfo.size()-1;
}
int CFramelessDialog::AddRow(int i)
{
	if (i >= m_VectorFileInfo.size() || i < 0)
	{
		return FALSE;
	}
	FileInfo* finfo = m_VectorFileInfo[i];
	if (!finfo)
	{
		return FALSE;
	}
	QTableWidgetItem* nameItem = new QTableWidgetItem;
	QTableWidgetItem* pathItem = new QTableWidgetItem;
	QTableWidgetItem* sizeItem = new QTableWidgetItem;
	if (nameItem)
	{
		QStringList strlName;
		strlName<<finfo->strFileName;
		nameItem->setData(Qt::DisplayRole,strlName);
		m_pTableList->setItem(i,0,nameItem);
	}

	if (sizeItem)
	{
		QStringList strSize;
		strSize<<finfo->strFileSize;
		sizeItem->setData(Qt::DisplayRole,strSize);
		m_pTableList->setItem(i,1,sizeItem);
	}
	if (pathItem)
	{
		QStringList strPath;
		strPath<<finfo->strFilePath;
		pathItem->setData(Qt::DisplayRole,strPath);
		m_pTableList->setItem(i,2,pathItem);
	}
	return TRUE;
}
int CFramelessDialog::FindTsFile(QString & strFile)
{
	for (int i=0;i<m_VectorFileInfo.size();i++)
	{
		FileInfo * qInfo = m_VectorFileInfo[i];
		if (!qInfo)
		{
			continue;
		}
		if (strFile.contains(qInfo->strFileName))
		{
			return i;
		}
	}
	return INVALID;
}
unsigned int CFramelessDialog::ThreadCalDurationAccordingFile(void* lpPara)
{
	/*if (NULL ==  g_hTsTimeEvent)
	{
		g_hTsTimeEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
	}*/
	FileInfo* pInfo = (FileInfo*)lpPara;
	if (pInfo == NULL)
	{
		/*if (NULL != g_hTsTimeEvent)
		{
			SetEvent(g_hTsTimeEvent);
		}*/
		return 0;
	}
	//ResetEvent(g_hTsTimeEvent);
	QString strInfo = pInfo->strFilePath + "/" + pInfo->strFileName;
	pInfo->iDuration = GetDurationFromTs(strInfo);

	/*int iWaitCount = 0;
	while(pInfo->bBeginPlayFlag == FALSE)
	{
		Sleep(10);
		iWaitCount++;
		if (iWaitCount>300)
		{
			break;
		}
	}*/
	if (pDialog)
	{
		((CFramelessDialog*)pDialog)->updateDuration(pInfo);	
	}
	g_bThreadCompletedFlag = TRUE;
	//SetEvent(g_hTsTimeEvent);
	return 0;
}
void CFramelessDialog::ReadUpdateInfo(QString & strFile,QStringList & listUpdate,QString & strVersion,BOOL bOnlyVersion)
{
	QFile updateFile(strFile);
	if (!updateFile.open(QIODevice::ReadOnly))
	{
		return;
	}
	QDomDocument xmlDoc("mydoc");
	QString error;  
	int row = 0, column = 0;  

	if (!xmlDoc.setContent(&updateFile,false,&error,&row,&column))
	{
		updateFile.close();
		return;
	}
	if (xmlDoc.isNull())
	{
		updateFile.close();
		return;
	}
	QDomElement updateRoot = xmlDoc.documentElement();
	QString rootName = updateRoot.attributeNode("name").value();
	if ("update" == rootName)
	{
		strVersion = updateRoot.attributeNode("version").value();
		if (bOnlyVersion)
		{
			updateFile.close();
			return;
		}
		QDomNodeList updateList = updateRoot.childNodes();
		QDomElement  updateEle;
		QDomNode     updateNode;
		int nCount = updateList.size();
		for (int i=0;i<nCount;i++)
		{
			updateNode = updateList.item(i);
            updateEle = updateNode.toElement();
			QString strName = updateEle.attributeNode("file").value();
			if (strName.length()>0)
			{
				listUpdate<<strName;
			}
		}
	}
	updateFile.close();
}
unsigned int CFramelessDialog::ThreadCheckUpdate(void* lpPara)
{
	if (!pDialog)
	{
		return 0;
	}
	QString strUpdatePath = QCoreApplication::applicationDirPath()+DIR+"config/updateList.xml";
	if (!QFile::exists(strUpdatePath))
	{
		return 0;
	}
    QString strVersionLocal;
	QStringList listUpdate;
	((CFramelessDialog*)pDialog)->ReadUpdateInfo(strUpdatePath,listUpdate,strVersionLocal);

	QString strTempPath = QCoreApplication::applicationDirPath()+TEMPUPDATE+"/config";
	QDir dirTemp(strTempPath);
	if (!dirTemp.exists())
	{
		dirTemp.mkpath(strTempPath);
	}
	strTempPath+="/updateList.xml";
	if (QFile::exists(strTempPath))
	{
		QFile::remove(strTempPath);
	}
	QString strServFile = ((CFramelessDialog*)pDialog)->m_strUpdateUrl+"/config/updateList.xml";
	URLDownloadToFile(NULL,strServFile.toStdWString().c_str(),strTempPath.toStdWString().c_str(),0,0);
	
	if (!QFile::exists(strTempPath))
	{
		((CFramelessDialog*)pDialog)->m_bOnLine = FALSE;
		return 0;
	}
	else
	{
		((CFramelessDialog*)pDialog)->m_bOnLine = TRUE;
	}
	QString strVersionServer;
	((CFramelessDialog*)pDialog)->ReadUpdateInfo(strTempPath,((CFramelessDialog*)pDialog)->m_listUpdate,strVersionServer,FALSE);
    if (strVersionServer != strVersionLocal)
    {
		((CFramelessDialog*)pDialog)->m_bShowUpdate = TRUE;
		emit ((CFramelessDialog*)pDialog)->updateInfo();
    }
	return 0;
}
unsigned int CFramelessDialog::ThreadLogin(void* lpPara)
{
	if (!pDialog)
	{
		return 0;
	}
	DWORD dFlag;
	std::string strLoginUrl("");
	int nStatus = -1;
	int nMinStatus = 99;
	QString strName(CLogin::szName);
	QString strPwd(CLogin::szPwd);
	for (int i=0;i<NETCOUNT;i++)
	{
		if (m_bCancelLogin)
		{
			return 0;
		}
		strLoginUrl = "";
		switch(CLogin::eNetType)
		{
		case DataCenterInner:
			{
				strLoginUrl = CLogin::strLoginUrlDCI;
				break;
			}
		case DataCenterExter:
			{
				strLoginUrl = CLogin::strLoginUrlDCE;
				break;
			}
		case BackupCenterInner:
			{
				strLoginUrl = CLogin::strLoginUrlBCI;
				break;
			}
		case BackupCenterExter:
			{
				strLoginUrl = CLogin::strLoginUrlBCE;
				break;
			}
		case NoInternet:
			{
				break;
			}
		default:
			{
				break;
			}
		}
		if (strLoginUrl.length()>0)
		{
			nStatus = CLogin::LoginAnt(strLoginUrl,strName,strPwd);
			if (nStatus < nMinStatus)
			{
				nMinStatus = nStatus;
			}
			if (/*NamePwdError == nStatus ||*/ LoginSuccess == nStatus /*|| HasServer == nStatus*/)
			{
				break;
			}
		}
		int ntype = CLogin::eNetType;
		ntype+=1;
		CLogin::eNetType = (ENetType)(ntype%NETCOUNT);
	}
	if (nStatus < nMinStatus)
	{
		nMinStatus = nStatus;
	}
	emit ((CFramelessDialog*)pDialog)->loginResult(nMinStatus);
	return 0;
}
unsigned int CFramelessDialog::ThreadCheckPlayFile(void* lpPara)
{
	
	QString strFile;
	CFramelessDialog* pMainDlg = (CFramelessDialog*)pDialog;
	CFramelessDialog::m_memShared.create(MAXFILELEN);
	//EnterCriticalSection(&g_crCheckFile);
	while(CFramelessDialog::m_bIsRun && pMainDlg)
	{
		
		CFramelessDialog::m_memShared.lock();
	
        char * szMem = static_cast<char*>(CFramelessDialog::m_memShared.data());
		strFile = szMem;
		memset(szMem,0,CFramelessDialog::m_memShared.size());
		CFramelessDialog::m_memShared.unlock();
		//CFramelessDialog::m_memShared.detach();
		
		if (strFile.contains(JNPREFIX))
		{
			pMainDlg->m_strFileImmediate = strFile;
			emit(pMainDlg->newTsFile());
		}
	}
	CFramelessDialog::m_memShared.detach();
	//LeaveCriticalSection(&g_crCheckFile);
	return 0;
}
void CFramelessDialog::OnEventCallBack(int iWndIndex,int nType,char* szPara,char* szWanrx,char* szGps)
{
	if (FALSE == m_bIsRun)
	{
		return;
	}
	if (pDialog)
	{
		switch(nType)
		{
		case EVENT_TYPE_LBCLICK:
			{
				break;
			}
		case EVENT_TYPE_PROGRESS:
			{
				if (((CFramelessDialog*)pDialog)->m_pProgress && ((CFramelessDialog*)pDialog)->m_pProgress->isSliderDown())
				{
					break;
				}
				if (iWndIndex == LTWNDINDEX)
				{
					int nPos = atoi(szPara);
					((CFramelessDialog*)pDialog)->updateProgress(nPos);
					((CFramelessDialog*)pDialog)->m_nCurSecond = nPos;
					
                    if(((CFramelessDialog*)pDialog)->m_nCurDuration >0 && nPos >= ((CFramelessDialog*)pDialog)->m_nCurDuration-1)
					{
					   ((CFramelessDialog*)pDialog)->PlayNextItem(iWndIndex,1);
					}
				}
				break;
			}
		case EVENT_TYPE_BEGINPLAY:
			{
				break;
			}
		case EVENT_TYPE_STOPPLAY:
			{
				
				if (((CFramelessDialog*)pDialog)->m_nCurDuration  <= 0)
				{
					break;
				}
                if (((CFramelessDialog*)pDialog)->m_nCurDuration > 0 && ((CFramelessDialog*)pDialog)->m_nCurSecond < ((CFramelessDialog*)pDialog)->m_nCurDuration)
                {
					break;
                }
				((CFramelessDialog*)pDialog)->PlayNextItem(iWndIndex,1);
				break;
			}
		case EVENT_TYPE_PRIVATEINFO:
			{
				if (szPara && strlen(szPara)>0)
				{
					((CFramelessDialog*)pDialog)->m_mpStrExtend[LTWNDINDEX]=szPara;
					emit ((CFramelessDialog*)pDialog)->newPrivateInfo(LTWNDINDEX,0);
					emit ((CFramelessDialog*)pDialog)->extendInfo(LTWNDINDEX,szGps,szWanrx);	
				}
				break;
			}
		case EVENT_TYPE_DBCLICK:
			{

				if (((CFramelessDialog*)pDialog)->m_pCurFull)
				{
					((CFramelessDialog*)pDialog)->m_pCurFull->mouseDoubleClickEvent(NULL);
				}
				break;
			}
		}
	}
}
BOOL CFramelessDialog::LoadDLLs()
{
	QString strdllpath = QCoreApplication::applicationDirPath()+DIR+PLUGINPATH;//"D:/ANT/stuff/ANT2 20160115/ANT2/bin/Plugin";
	QDir dllDir(strdllpath);
	if (dllDir.exists())
	{
		QStringList strFilter;
		strFilter<<"*.dll";
		dllDir.setNameFilters(strFilter);
		QStringList strDllList = dllDir.entryList(strFilter);
		if (strDllList.size()>0)
		{
			QString strOldMoudle = QCoreApplication::applicationDirPath()+DIR;
			QString strNewMoudle("");
			for (int i=0;i<strDllList.size();i++)
			{
				if (strDllList[i].contains(RMSDK))
				{
				  strNewMoudle = strOldMoudle +SDKPATH + DIR + RMSDK + DIR;
				  SetCurrentDirectoryA(strNewMoudle.toStdString().c_str());
				}
				else if (strDllList[i].contains(WKPSDK))
				{
					strNewMoudle = strOldMoudle +SDKPATH + DIR + WKPSDK + DIR;
					SetCurrentDirectoryA(strNewMoudle.toStdString().c_str());
				}
				QLibrary* pdll = new QLibrary(strdllpath + DIR + strDllList[i],pDialog);
				if (pdll && pdll->load())
				{
					std::pair<QLibrary*,std::string> aPair(pdll,strDllList[i].toStdString());
					m_vtPluginDLL.push_back(aPair);
				}
			}
			return TRUE;		
		}
	}
	return FALSE;
}

/*****************************************************************************
* 函数名:  CreatePluginInterface
* 描述:   创建插件
* 相关文档: 本函数参数类型定义     
* 函数存储类型:                                                                
* 参数:0                                                                                                                                            
* 参数名                 类型                   输入/输出   描述                               
* 返回值:
BOOL
*****************************************************************************/
BOOL CFramelessDialog::CreatePluginInterface()
{
	//遍历所有的PluginDll
	unsigned short size = m_vtPluginDLL.size();

	unsigned short nCurrent = 0;
	std::vector < unsigned char > vtExportType;
	std::vector < CANTOfflineFileSDKAdapter *> vtExportInterface;
	for (unsigned short i = 0 ; i < size; i++)
	{
		CANTOfflineFileSDKAdapter * pAdapter = new CANTOfflineFileSDKAdapter;
		if(pAdapter == NULL)
		{
			return FALSE;
		}

		BOOL bRet = pAdapter->LoadInterface(m_vtPluginDLL[i].first,m_vtPluginDLL[i].second.c_str());
		if(!bRet)
		{
            ShowMessageBox("strError","loadSDKFaild",eErrorTip);
			return FALSE;
		}

		m_vtPluginInterface.push_back(pAdapter);

	}
	return TRUE;

}
int CFramelessDialog::ANTSDK_REALDATACALLBACK(void * pThis,int nChannel, unsigned int nExtraDataFlag,const char * szPlateNumber, struct tagGps * pGPSItem, const char * szWWANRxLevel,const char * nAlarmType,const char * szTime,unsigned int nFileDuration,unsigned int nCurSecond)

{
	return 0;
}

int CFramelessDialog::ANTSDK_REALDATACALLBACK2(void * pThis,int nChannel, unsigned int nExtraDataFlag,const char * szPlateNumber, const char* szExtend, const char * szWWANRxLevel,const char * nAlarmType,const char * szTime,unsigned int nFileDuration,unsigned int nCurSecond)
{
	if (nCurSecond > nFileDuration)
	{
		return FALSE;
	}
	static char tempt[JSLEN]={0};
  
	if (pDialog)
	{
		if(((CFramelessDialog*)pDialog)->m_pProgress && !((CFramelessDialog*)pDialog)->m_pProgress->isSliderDown())
		{
			if (((CFramelessDialog*)pDialog)->m_bSDK && ((CFramelessDialog*)pDialog)->m_mpSDKFileInfo.size() <1)
			{

				if (szTime && 14 == strlen(szTime))
				{
					strncpy(tempt,szTime+8,2);

					int nHour = atoi(tempt);
					strncpy(tempt,szTime+10,2);
					int nMinute = atoi(tempt);
					strncpy(tempt,szTime+12,2);
					int nSecond = atoi(tempt);
					int ntemp = nHour*3600 + nMinute*60 + nSecond-((CFramelessDialog*)pDialog)->m_nStartSecond;
					if (ntemp<0)
					{
						ntemp = 0;
					}
					nCurSecond =  ntemp;//nHour*3600 + nMinute*60 + nSecond-((CFramelessDialog*)pDialog)->m_nStartSecond;
					nFileDuration = ((CFramelessDialog*)pDialog)->m_nCurDuration;
					
				}
			} 
			if (0 == nCurSecond)//esle
			{
				emit ((CFramelessDialog*)pDialog)->clearloc();
			}
			else if (nCurSecond!=0)
			{
				((CFramelessDialog*)pDialog)->m_nCurSecond = nCurSecond;
				if (((CFramelessDialog*)pDialog)->m_bSDK)
				{
					if ((nCurSecond>=((CFramelessDialog*)pDialog)->m_nCurDuration && ((CFramelessDialog*)pDialog)->m_nCurDuration>0) ||(nFileDuration>0 && nCurSecond >= nFileDuration) )
					{
						emit ((CFramelessDialog*)pDialog)->nextItem(nChannel,1);
					}	
					else if (((CFramelessDialog*)pDialog)->m_nCurFileIndex == m_mpSDKTimeInfo.size()-1 && nCurSecond>=((CFramelessDialog*)pDialog)->m_nCurDuration-1)
					{
						emit ((CFramelessDialog*)pDialog)->nextItem(nChannel,1);
					}
					((CFramelessDialog*)pDialog)->updateProgress(((CFramelessDialog*)pDialog)->m_nCurSecond);
				} 
				else
				{
					FileInfo * pFinfo = ((CFramelessDialog*)pDialog)->getPlagFile(nChannel);

					if (pFinfo && NOTSETDURATION == pFinfo->iDuration)
					{
						pFinfo->iDuration = nFileDuration;
						if (nChannel == ((CFramelessDialog*)pDialog)->m_nCurWndIndex)
						{
							((CFramelessDialog*)pDialog)->updateRangeForProgress(nFileDuration);
						}

					}else if (pFinfo)
					{
						pFinfo->iCurTime = nCurSecond;
                        if (nChannel == ((CFramelessDialog*)pDialog)->m_nCurWndIndex)
                        {
							((CFramelessDialog*)pDialog)->updateProgress(nCurSecond);
                        }
						if ( pFinfo->iDuration >0 && pFinfo->iCurTime>=pFinfo->iDuration)
						{
							emit ((CFramelessDialog*)pDialog)->nextItem(nChannel,1);
						}
					}	
				}
			}
		}
		int iwndIndex = nChannel;//((CFramelessDialog*)pDialog)->GetVideoIndex(pHWND);
		if (-1 == nChannel)
		{
			iwndIndex = LTWNDINDEX;
		}
		if (iwndIndex<LTWNDINDEX || iwndIndex>RBWNDINDEX)
		{
			return FALSE;
		}
		if (EXTRAFLAG_GPS & nExtraDataFlag && szExtend)
		{
			m_mpStrExtend[iwndIndex] = szExtend;
			if (strlen(m_mpStrPlate[LTWNDINDEX].c_str())>0)
			{
				emit ((CFramelessDialog*)pDialog)->newPrivateInfo(LTWNDINDEX,eOfflinePlay);
			}
			
			char szRealLon[30]={0};
			char szRealLat[30]={0};
			char* szTemp = (char*)strstr(szExtend,LONGITUDE);
			if (szTemp && strlen(szTemp)>strlen(LONGITUDE))
			{
				char* szLon = szTemp+strlen(LONGITUDE);
				char* szQuote = strstr(szLon,QUOTE);
				if (szQuote)
				{
					int nLen = szQuote-szLon;
					strncpy(szRealLon,szLon,nLen);
				}
			}
			szTemp = (char*)strstr(szExtend,LATITUDE);
			if (szTemp && strlen(szTemp)>strlen(LATITUDE))
			{
				char* szLat = szTemp+strlen(LATITUDE);
				char* szQuote = strstr(szLat,QUOTE);
				if (szQuote)
				{
					int nLen = szQuote-szLat;
                    strncpy_s(szRealLat,EXTENDINFLEN,szLat,nLen);
				}
			}
             strcat_s(szRealLon,EXTENDINFLEN," ");
             strcat_s(szRealLon,EXTENDINFLEN,szRealLat);
            if (szRealLon)
			{
                memset(szLoc,0,EXTENDINFLEN);
                memcpy(szLoc,szRealLon,strlen(szRealLon));
			}
			
			if (szWWANRxLevel)
			{
                memset(szWWanrx,0,EXTENDINFLEN);
				memcpy(szWWanrx,szWWANRxLevel,strlen(szWWANRxLevel));
			}	
			emit ((CFramelessDialog*)pDialog)->extendInfo(nChannel,szLoc,szWWanrx);	
		}

		if (szPlateNumber && strlen(szPlateNumber)>0)
		{
			sprintf_s(tempt,JSLEN,PLATEFORMAT,szPlateNumber,ITEMSEP);
			m_mpStrPlate[LTWNDINDEX]=tempt;
		}		
	}
	return 0;
}

int CFramelessDialog::ANTSDK_CONTAINER_WRITELOG(void * pThis,const char * szLog,...)
{

    char pFileBuffer[LOGLEN] = {0};

	unsigned int nFileBufferHeaderLen = 0;
	va_list argptr;
	QDateTime tm = QDateTime::currentDateTime();
	QString strTm = tm.toString("yyyy-MM-dd hh:mm:ss");
	va_start(argptr, szLog);

    nFileBufferHeaderLen = sprintf_s(pFileBuffer,LOGLEN,"%s ",strTm.toStdString().c_str());
    vsnprintf_s(pFileBuffer+nFileBufferHeaderLen,LOGLEN,LOGLEN - nFileBufferHeaderLen,szLog, argptr);
	va_end(argptr);
	return 0;
}

int CFramelessDialog::ANTSDK_CONTAINER_MESSAGEBOX(void * pThis,const char * szMsg)
{
    ShowMessageBox(ERRORTIP,szMsg,eErrorTip);
	return 0;
}

int CFramelessDialog::ANTSDK_CONTAINER_DAYFILELISTDIALOG(void * pThis,const char * szDayList,char * szResultSelectDay,int * pnChannelFlag)
{
	Json::Value GetVal;
	Json::Reader reader;
	char* m_pBuf = (char*)szDayList;
	QStringList listDate;
	
	if(reader.parse(m_pBuf, GetVal))
	{
		int n = GetVal["RESPONSE"]["COUNT"].asUInt();
		for(int i = 0; i < n; i++)
		{
			QString str(GetVal["RESPONSE"]["DAY"][i].asCString());
			listDate<<str;
		}
	}
	if (listDate.size()<1)
	{
		return ANT_SDK_CONTAINER_GETDAYLISTFAIL;
	}
	int nType = -1;
    nType = ShowSelectDayAndChannelDialog(listDate,szResultSelectDay,pnChannelFlag,nType);
	if (ANT_SDK_SUCCESS == nType && pDialog)
	{
		((CFramelessDialog*)pDialog)->playAll(TRUE);

		((CFramelessDialog*)pDialog)->pauseAll(TRUE);

		((CFramelessDialog*)pDialog)->showVideo(TRUE);
		((CFramelessDialog*)pDialog)->updateCurVideo(LTWNDINDEX);
	}
	return nType;
}
int CFramelessDialog::ShowSelectDayAndChannelDialog(QStringList & strDayList,char * szResultSelectDay,int * pnChannelFlag,int &nType)
{
	if (!m_pSelectDay)
	{
		QUiLoader loader;
		QString curPath = QCoreApplication::applicationDirPath()+DIR+UIPATH+"\\selectSDKChannel.ui";
		QFile file(curPath);
		file.open(QFile::ReadOnly);

		m_pSelectDay = (QDialog*)loader.load(&file,NULL);

		if (m_pSelectDay)
		{
			CLanguage::ReadTxtByUi(m_pSelectDay,"selectSDKChannel");
			if (QLocale::Chinese == CLanguage::m_langId)
			{
				CLanguage::ReadTxtByUi(m_pSelectDay,"selectSDKChannel",TRUE);
			}
			
			QWidget* pBtnOk = qFindChild<QWidget*>(m_pSelectDay,"btnOk");
			if (pBtnOk)
			{
				pBtnOk->connect((const QObject*)pBtnOk,SIGNAL(clicked()),pDialog,SLOT(clickOkInSelectChannel()));
			}
			QWidget* pBtnCancel = qFindChild<QWidget*>(m_pSelectDay,"btnCancel");
			if (pBtnCancel)
			{
				pBtnCancel->connect((const QObject*)pBtnCancel,SIGNAL(clicked()),m_pSelectDay,SLOT(reject()));
			}
			QWidget* pBtnClose = qFindChild<QWidget*>(m_pSelectDay,"btnClose");
			if (pBtnClose)
			{
				pBtnClose->connect((const QObject*)pBtnClose,SIGNAL(clicked()),m_pSelectDay,SLOT(reject()));
			}
			QCheckBox* pCheck = qFindChild<QCheckBox*>(m_pSelectDay,"allCheck");
			if (pCheck)
			{
				pCheck->connect((const QObject*)pCheck,SIGNAL(stateChanged(int)),pDialog,SLOT(checkAll(int)));
			}
			m_pSelectDay->setModal(true);
		}
		
	}
	if (m_pSelectDay)
	{
        CLanguage::UpdatePageLanguage(m_pSelectDay);

		Json::Value GetVal;
		Json::Reader reader;
		
		QListWidget* pList = qFindChild<QListWidget*>(m_pSelectDay,"daylist");
		if(pList)
		{
			pList->clear();
			for(int i = 0; i < strDayList.size(); i++)
			{
				int nIndex = strDayList[i].lastIndexOf(ComFunc::m_regFilter);
				
				if (-1 != nIndex)
				{
					pList->addItem(strDayList[i].mid(nIndex,DATELEN));
				}
				else
				{
					pList->addItem(strDayList[i]);
				}
			}
			if (pList->count()>0)
			{
				pList->setCurrentItem(0);
			}	
		}
		if (TRUE == m_pSelectDay->exec())
		{
			BOOL isSuccess = FALSE;
			BOOL bChannel1 = FALSE;
			BOOL bChannel2 = FALSE;
			BOOL bChannel3 = FALSE;
			BOOL bChannel4 = FALSE;
			QCheckBox* pCheck1 = qFindChild<QCheckBox*>(m_pSelectDay,"channel1");
			QCheckBox* pCheck2 = qFindChild<QCheckBox*>(m_pSelectDay,"channel2");
			QCheckBox* pCheck3 = qFindChild<QCheckBox*>(m_pSelectDay,"channel3");
			QCheckBox* pCheck4 = qFindChild<QCheckBox*>(m_pSelectDay,"channel4");
			int nChannel = 0;
			if (pCheck1)
			{
				bChannel1 = Qt::Checked == pCheck1->checkState();
				if (bChannel1)
				{
					nChannel |= 1;

				}
			}
			if (pCheck2)
			{
				bChannel2 = Qt::Checked == pCheck2->checkState();
				if (bChannel2)
				{
					nChannel |= 2;
				}
			}
			if (pCheck3)
			{
				bChannel3 = Qt::Checked == pCheck3->checkState();
				if (bChannel3)
				{
					nChannel |= 4;
				}
			}
			if (pCheck4)
			{
				bChannel4 = Qt::Checked == pCheck4->checkState();
				if (bChannel4)
				{
					nChannel |= 8;
				}
			}
			if (pnChannelFlag)
			{
				*pnChannelFlag = nChannel;
			}
			
			((CFramelessDialog*)pDialog)->m_nChannelFlag = nChannel;
            ((CFramelessDialog*)pDialog)->m_nRestoreChannelFlag = nChannel;
			if (pList)
			{
				int nRow = pList->currentRow();
				if (-1 == nRow)
				{
					nRow = pList->count()-1;
				}
				QListWidgetItem* pitem = pList->item(nRow);
				m_pSelectDay->hide();
				if (pitem)
				{
					QString str = pitem->text();
					
					strcpy(szResultSelectDay,str.toStdString().c_str());
					
                    nType = nRow;
					
				}
				if (0 == nChannel)
				{
				}
				if (0 != nChannel)
				{
					return ANT_SDK_SUCCESS;
				}
			}
		}
	}
	return ANT_SDK_CONTAINER_GETDAYLISTFAIL;
}
int CFramelessDialog::AllSDK_Init()
{
	unsigned short size = m_vtPluginInterface.size();

	unsigned short nCurrent = 0;
	std::vector < unsigned char > vtExportType;
	std::vector < CANTOfflineFileSDKAdapter *> vtExportInterface;
	for (unsigned short i = 0 ; i < size; i++)
	{

		int nRet = m_vtPluginInterface[i]->ANTOfflineFileSDK_Init(2,ANTSDK_CONTAINER_WRITELOG,ANTSDK_CONTAINER_MESSAGEBOX,ANTSDK_CONTAINER_DAYFILELISTDIALOG);
		if(nRet)
		{
			SHOW_ERROR_BOX("initFuncFailed");

			return FALSE;
		}
	} 
	return TRUE;
}

int CFramelessDialog::AllSDK_Exit()
{
	unsigned short size = m_vtPluginInterface.size();

	unsigned short nCurrent = 0;
	std::vector < unsigned char > vtExportType;
	std::vector < CANTOfflineFileSDKAdapter *> vtExportInterface;
	for (unsigned short i = 0 ; i < size; i++)
	{
		int nRet = m_vtPluginInterface[i]->ANTOfflineFileSDK_Exit();
		if(nRet)
		{
			SHOW_ERROR_BOX("exitFuncFailed");
			return FALSE;
		}
	}
	return TRUE;
}
int CFramelessDialog::AllSDK_Config_SetVideoHWND(void * pThis,unsigned int * szArrageHWND,int nHWNDCount)
{
	unsigned short size = m_vtPluginInterface.size();

    //unsigned short nCurrent = 0;
	std::vector < unsigned char > vtExportType;
	std::vector < CANTOfflineFileSDKAdapter *> vtExportInterface;
	for (unsigned short i = 0 ; i < size; i++)
	{
		int nRet = m_vtPluginInterface[i]->ANTOfflineFileSDK_Config_SetVideoHWND(pThis,szArrageHWND,nHWNDCount);
		if(nRet)
		{
			SHOW_ERROR_BOX("updateFailed");
			return FALSE;
		}
	}
	return TRUE;
}
int CFramelessDialog::AllSDK_Config_SetCallBackExtraData(CANTOfflineFileSDKAdapter::FUNC_SET_ANTSDK_REALDATACALLBACK pFunc)
{
	unsigned short size = m_vtPluginInterface.size();
//	unsigned short nCurrent = 0;
	std::vector < unsigned char > vtExportType;
	std::vector < CANTOfflineFileSDKAdapter *> vtExportInterface;
	for (unsigned short i = 0 ; i < size; i++)
	{
		if(m_vtPluginInterface[i])
		{
		   int nRet = m_vtPluginInterface[i]->ANTOfflineFileSDK_Config_SetCallbackExtraData(pFunc);
		   nRet = m_vtPluginInterface[i]->ANTOfflineFileSDK_Config_SetCallbackExtraData2(ANTSDK_REALDATACALLBACK2);
		}
	}

	return 0;
}
/************************************************************************/
/*
GetPlugin
    get the right SDK plugin by video type 
	current window
param[in]     fileType 
              fileType=0   RM      *.h264
              fileType=1   WKP     *.avi
              fileType=2,  TSFile  *.ts
              fileType=-1  unknown type
return        CANTOfflineFileSDKAdapter
              which will be RM , WKP or NULL
*/
/************************************************************************/
CANTOfflineFileSDKAdapter* CFramelessDialog::GetPlugin(FileSourceType fileType)
{
	QString strSDKType = "";
	if (RmType == fileType)
	{
		strSDKType = RMSDK;
	} 
	else if(WkpType == fileType)
	{
		strSDKType = WKPSDK;
	}
	unsigned short size = m_vtPluginInterface.size();

	for (unsigned short i = 0 ; i < size; i++)
	{
		if(m_vtPluginInterface[i]->GetType() == strSDKType.toStdString())
		{
			return m_vtPluginInterface[i];
		}
	}
	return NULL;
}
/************************************************************************/
/*
GetPlugin
    get the right SDK plugin which process the video info in 
	current window
param[in]     iWndIndex     video window index
return        CANTOfflineFileSDKAdapter
which will be RM or WKP
*/
/************************************************************************/
CANTOfflineFileSDKAdapter* CFramelessDialog::GetPlugin(int iWndIndex)
{
	FileInfo* pFileInfo = getPlagFile(iWndIndex);
	if (pFileInfo)
	{
		QString strSDKType = "";
		if (pFileInfo->strFileName.contains(RMPREFIX))
		{
			strSDKType = RMSDK;
		} 
		else if(pFileInfo->strFileName.contains(WKPPREFIX))
		{
			strSDKType = WKPSDK;
		}
		for (unsigned short i = 0 ; i < m_vtPluginInterface.size(); i++)
		{
			if(m_vtPluginInterface[i]->GetType() == strSDKType.toStdString())
			{
				return m_vtPluginInterface[i];
			}
		}	
	}
	return NULL;
}
/************************************************************************/
/*
GetPathFileInfo
    get all the video file which suffix is .avi in the directory
param[in]    strPath   the directory in which we want get the video file
return       none
*/
/************************************************************************/
BOOL CFramelessDialog::GetPathFileInfo(QString & strPath)
{
	QDir theDir(strPath);
	if (theDir.exists())
	{
		QStringList strFilter(WKPFILTER);
		QFileInfoList listFile = theDir.entryInfoList(strFilter);
		if (listFile.size()>0)
		{
			QString strFileName;
			int ts;
			int te=0;
            //int nYear;
            //int nMonth;
            //int nDay;
			int nHours;
			int nMinutes;
			int nSeconds;
			int nHoure;
			int nMinutee;
			int nSeconde;
			int nChannel;
            //struct tm tt;
			QString strType;
			for (int i=0;i<listFile.size();i++)
			{
				if(AVILEN == listFile[i].fileName().length())
				{
					strFileName = listFile[i].fileName();
					nHours = strFileName.mid(10,2).toInt();
					nMinutes = strFileName.mid(12,2).toInt();
					nSeconds = strFileName.mid(14,2).toInt();
					nChannel = strFileName.mid(19,1).toInt();
					strType = strFileName.mid(18,1);
					
				    ts = nHours*3600 + nMinutes*60 + nSeconds;
					QTime tet= listFile[i].lastModified().time();
					nHoure = tet.hour();
					nMinutee = tet.minute();
					nSeconde = tet.second();
					if (nMinutee>nMinutes)
					{
						nHoure = nHours;
					} 
					else
					{
						nHoure = nHours + 1;
					}
					
					te = nHoure*3600 + nMinutee*60 + nSeconde;
					bool bAlarm = false;
					if (strType.contains(ALARMPRE))
					{
						bAlarm = true;
					}
					
					if(m_mpSDKTimeInfo.find(ts) == m_mpSDKTimeInfo.end())
					{
						m_mpSDKTimeInfo.insert(std::pair<time_t,std::pair<unsigned int,bool>>(ts,std::pair<unsigned int,bool>(te,bAlarm))) ;

					}
					
					m_mpSDKFileInfo[ts][nChannel] = listFile[i].absoluteFilePath().toStdString();
					
					
				}
			}
			//setListInfo();
			return TRUE;
		}
	}
	return FALSE;
}
/************************************************************************/
/*
PlayGroup
    play the WKP or SC video via it's SDK
param[in]   itf  the videos of all channel in certain period
return      none
*/
/************************************************************************/
void CFramelessDialog::PlayGroup(SDKFMAP::iterator itf)
{
	if (itf != m_mpSDKFileInfo.end())
	{
		if (itf->second.size()>MAXCHANNEL)
		{
			return;
		}
		char * szfile[MAXCHANNEL]={0};
		int jj = 0;
		std::map<unsigned char,std::string>::iterator it = itf->second.begin();
        for (it;it!=itf->second.end();it++)
        {
			if (it->first)
			{
				szfile[it->first-1] = (char*)it->second.c_str();
			}
			jj++;
        }
		int isSuccess = FALSE;
		
		for (unsigned short k = 0 ; k < m_vtPluginInterface.size(); k++)
		{
			int nRet = m_vtPluginInterface[k]->ANTOfflineFileSDK_Control_OpenGroupFile(szfile,m_nChannelFlag,jj);
			if(nRet == 0)
			{
				isSuccess = TRUE;
				m_vtPluginInterface[k]->GetType();
				break;
			}
		}
	}
}

/************************************************************************/
/*PlayGroupInRow
     play the factory video by row in the table widget
param[in]    nRow    row index of table widget
return       none
*/
/************************************************************************/
void CFramelessDialog::PlayGroupInRow(int nRow)
{
	
	SDKTMAP::iterator it = m_mpSDKTimeInfo.begin();
	for (int i=0;i<nRow && it!=m_mpSDKTimeInfo.end();it++,i++)
	{
	}
	if (it != m_mpSDKTimeInfo.end())
	{
		m_nCurDuration = it->second.first - it->first;
	}
	if (m_mpSDKFileInfo.size()>0)
	{
		SDKFMAP::iterator itf = m_mpSDKFileInfo.begin();
		for (int i=0;i<nRow && itf!=m_mpSDKFileInfo.end();itf++,i++)
		{
		}
		if (itf != m_mpSDKFileInfo.end())
		{
			m_nStartSecond = itf->first;
			m_nCurSecond = 0;
			PlayGroup(itf);
			//updateProgress(m_nStartSecond);
			updateRangeForProgress(m_nCurDuration);
			showVideo(TRUE);
		}
	} 
	else
	{
		bool bSuccess = false;
		if (it != m_mpSDKTimeInfo.end())
		{
			if (m_bShowOpen)
			{
				CANTOfflineFileSDKAdapter* pPlugin = GetPlugin(RmType);
				if (!pPlugin)
				{
					return;
				}
				if (SDKINDEX == m_nModeIndex)
				{
					
						int nRet = pPlugin->ANTOfflineFileSDK_Control_OpenSDCard_WithDuration(
							NULL,
							TRUE,
							TRUE,
							TRUE,
							FALSE,
							FALSE,
							FALSE,
							FALSE,
							FALSE,
							NULL,
							NULL,
							NULL,
							NULL);
						if(nRet == 0)
						{
							bSuccess = true;
							//break;
						}
					
				} 
				else
				{
						int nRet = pPlugin->ANTOfflineFileSDK_Control_OpenDirWithDuration(
							NULL,
							m_nChannelFlag & 1,
							m_nChannelFlag & 2,
							m_nChannelFlag & 4,
							m_nChannelFlag & 8,
							FALSE,
							FALSE,
							FALSE,
							FALSE,
							NULL,
							NULL,
					        NULL,
							NULL);
						if(nRet == 0)
						{
							bSuccess = true;
							//break;
						}


				} 
				if (bSuccess)
				{
					showVideo(TRUE);
				}
			}
			m_nCurSecond = 0;
			m_nStartSecond = it->first;
			updateRangeForProgress(m_nCurDuration);
			{
				QString str = m_strCtrlSetProgress +QString::number(m_nCurSecond+m_nStartSecond)+ITEMSEP+QString::number((float)m_nCurSecond/(float)m_pProgress->maximum()) + ",1";
				SetVideoPlayerControlInfo(m_nCurWndIndex,str);	
			}
		}
	}
	if (m_pTableList)
	{
		m_pTableList->selectRow(nRow);
	}
	updateCurVideo(LTWNDINDEX);
}
/************************************************************************/
/*
SetTableColWidth
    set the width of the table widget,distinguish the situation of
	showing *.ts file info from showing video info from factory video
param[in]  none
return     none
*/
/************************************************************************/
void CFramelessDialog::SetTableColWidth()
{
	if (m_pTableList)
	{
		if (m_bSDK)
		{
			m_pTableList->setColumnWidth(0,50);
			m_pTableList->setColumnWidth(1,50);
			m_pTableList->setColumnWidth(2,50);
		} 
		else
		{
			m_pTableList->setColumnWidth(0,160);
			m_pTableList->setColumnWidth(1,80);
			m_pTableList->setColumnWidth(2,80);
		}
	}
}
/************************************************************************/
/*
saveUserInfo
    save usser name and pwd to qss.ini
param[in]    none
return       none
*/
/************************************************************************/
void CFramelessDialog::SaveUserInfo()
{
	if (CLogin::bRememberPwd)
	{
		if (m_pUserNameEdit)
		{
			QString str = m_pUserNameEdit->text();
			memset(CLogin::szName,0,NAMELEN);
			memcpy(CLogin::szName,str.toStdString().c_str(),min(strlen(str.toStdString().c_str()),NAMELEN));
			m_pUserNameEdit->close();
			//delete m_pUserNameEdit;
			m_pUserNameEdit = NULL;
		}
		if (m_pPwdEdit)
		{
			QString str = m_pPwdEdit->text();
			memset(CLogin::szPwd,0,NAMELEN);
			memcpy(CLogin::szPwd,str.toStdString().c_str(),min(strlen(str.toStdString().c_str()),NAMELEN));
			m_pPwdEdit->close();
			//delete m_pPwdEdit;
			m_pPwdEdit = NULL;
		}
	}
	if (m_pLoginWidget)
	{
		m_pLoginWidget->close();
	}
}
