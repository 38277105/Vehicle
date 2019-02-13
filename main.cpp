//#include "vehiclevideoplayer.h"
#include "FramelessDialog.h"
#include <QtGui/QApplication>
#include <map>
#include <QLocale>
#include <Windows.h>

//#include <string>
#include "LoginDialog.h"
#include "LanguageProcessor.h"

//#include <WinNls32.h>
//#include "writeLog.h"
QWidget* pDialog = NULL;
QApplication* pApplication = NULL;

int main(int argc, char *argv[])
{
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");

	QTextCodec::setCodecForTr(codec);

	QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

	//QApplication::setStyle("cleanlooks");  

	QApplication a(argc, argv);
	pApplication = &a;
	//a.setGlobalMouseTracking(true);
	//gnInstance++;

	QString strModulePath = QCoreApplication::applicationDirPath();

	QString strPlugin = strModulePath+DIR+PLUGINPATH;

	QApplication::addLibraryPath(strPlugin);
	//strPlugin =   "./plugins";//

	
	
	CFramelessDialog*  pmainWindow = new CFramelessDialog();
	pDialog = pmainWindow;
    if (!pDialog)
    {
		return 0;
    }
	if (NULL == CreateEventA(NULL,FALSE,FALSE,"VehicleVideoPlayerEvent"))
	{
		return 0;
	}
	else if (ERROR_ALREADY_EXISTS == GetLastError())
	{
		

		if (argc > 1 )
		{
			QString str(argv[1]);
			if (str.contains(JNPREFIX))
			{
				QBuffer buf;
				QDataStream dataStream(&buf);

				//shareMem.setKey("VehicleVideoPlayerShareMemory");


				buf.open(QBuffer::ReadWrite);
				buf.setData(argv[1],strlen(argv[1]));
				dataStream<<argv[1];
				int nSize = strlen(argv[1]);//buf.size();
				if (!CFramelessDialog::m_memShared.attach())
				{
					if(!CFramelessDialog::m_memShared.create(nSize))
					{
						CFramelessDialog::m_memShared.detach();
						return 0;
					}
				}

				CFramelessDialog::m_memShared.lock();
				char * szTo = static_cast<char*>(CFramelessDialog::m_memShared.data());

				if (szTo)
				{
					memcpy(szTo,argv[1],qMin(CFramelessDialog::m_memShared.size(),nSize));
				}
				CFramelessDialog::m_memShared.unlock();
				CFramelessDialog::m_memShared.detach();
			}
			
		}
		delete pmainWindow;
		pmainWindow = NULL;
		pDialog = NULL;
		return 0;
	}
	if (argc>1)
	{
		pmainWindow->m_strFileImmediate = argv[1];
		if (pmainWindow->m_strFileImmediate.contains(JNPREFIX))
		{
			pmainWindow->m_bPlayImmediately = TRUE;
		}
	}
	//QApplication::setMainWidget(pmainWindow);
	pmainWindow->setAttribute(Qt::WA_QuitOnClose);
	pmainWindow->setMouseTracking(true);
	//a.setMainWidget(pmainWindow);
	pmainWindow->createSystemTray();
	a.connect( &a,  
		SIGNAL(lastWindowClosed()),  
		&a,  
		SLOT(quit()));  
	a.setWindowIcon(pmainWindow->m_icoTray);
	QLocale loc = QLocale::system();
	CLanguage::m_langId = loc.language();
	
	pmainWindow->loginANT();
	
	
	return a.exec();
}
