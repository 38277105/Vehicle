#include <map>
#include <string>
#include <QWidget>
#include "CommonStruct.h"
#include <QLocale>
#ifndef LANGUAGEPROCESSORHEADER
#define LANGUAGEPROCESSORHEADER
enum ElanguageType
{
	languageEsp=1,
	languageEng=2,
	languageChn=3
};
enum eTextType
{
	txtOpenLocal=1,
	txtOpenSDCard=2,
	txtUserName=3,
	txtPWD = 4,
	txtOK = 5,
	txtCancel = 6,
	txtRemberPwd = 7,
	txtName = 8,
	txtWindow = 9,
	txtSize = 10,
	txtPath = 11,
	txtChannel = 12,
	txtAll = 13,
	txtSelectDay = 14,
	txtSelectChannel = 15,
	txtSelectLanguage = 16,
	txtLanguageChn = 17,
	txtLanguageEng = 18,
	txtLanguageEsp = 19,
	txtExit = 20

};
typedef std::map<QWidget*,std::map<QString,std::pair<QString,std::pair<QString,QString> > >> PAGELANGUA;
typedef std::map<QString,std::pair<QString,std::pair<QString,QString> > > WIDGETLANGUA;
class CLanguage
{
public:
	static LANGMAP m_mapLangTable;
	static ElanguageType m_eLanguageType;
	static QLocale::Language           m_langId;
	static void ReadAllTxt();
	static void ReadTxtByUi(QWidget* pParent,const char* szUi,BOOL bChn=FALSE);
	static void UpdatePageLanguage(QWidget* pParent,BOOL bUpdateAll=FALSE);
	static BOOL GetTxtById(eTextType typeId,QString & strResult);
	static BOOL GetTxtByStr(const char* strSrc,QString &strResult,QWidget* pParent = NULL);
	static void SetLangType(ElanguageType langType);
	static void UpdateMenuComboBoxText();
	static void UpdateTableText();
	static void GetSignalText();
	static QString strNormalVideo;
	static QString strAlarmVideo;
	static QString strNoSignalEs;
	static QString strNoSignalEn;
	static QString strNoSignalCh;
	static QString strNoGPSEs;
	static QString strNoGPSEn;
	static QString strNoGPSCh;
	static QString strSignal;
	static QString strGps;
};
#endif
