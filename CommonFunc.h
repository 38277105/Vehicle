#ifndef COMMFUNCHEADER
#define COMMFUNCHEADER
#include <QString>
#include <QStringList>
#include <map>
#include <QRegExp>
#include <set>
class ComFunc
{
public:
	static void GetOriginalVideoPath(QString & strPath,std::map<QString,int>& mpPath);
	static void GetPathList(QString &strPath,std::map<QString,int>& mpPath,QStringList& rsltList);
public:
	static QStringList m_strFilter;
	static QString     m_strPath;
	static std::map<QString,int> m_mpPath;
	static QRegExp     m_regFilter;
	static int         m_nSearchCount;
};
#endif