#include "CommonFunc.h"
#include "CommonStruct.h"
#include <QDir>

QStringList ComFunc::m_strFilter("");
QString     ComFunc::m_strPath("");
std::map<QString,int> ComFunc::m_mpPath;
int         ComFunc::m_nSearchCount=0;
QRegExp     ComFunc::m_regFilter(DATEFILTER);

void ComFunc::GetOriginalVideoPath(QString & strPath,std::map<QString,int>& mpPath)
{
	m_nSearchCount++;
	if (strPath.lastIndexOf(DIR)==strPath.length()-1)
	{
		strPath=strPath.mid(0,strPath.length()-1);
	}
	QDir dir(strPath);
	if (dir.exists())
	{
		ComFunc::m_strFilter.clear();
		ComFunc::m_strFilter<<RMFILTER;
		QStringList flist = dir.entryList(ComFunc::m_strFilter,QDir::Files);
		if (flist.size()>0)
		{
			ComFunc::m_strFilter.clear();
			ComFunc::m_strFilter<<RMDATFILE<<RMFILELIST;
			flist.clear();
			flist = dir.entryList(ComFunc::m_strFilter,QDir::Files);
			if (2 == flist.size())
			{
				mpPath[strPath]=RmType;
				return;
			}
			
		} 
	
		ComFunc::m_strFilter.clear();
		ComFunc::m_strFilter<<WKPFILTER;
		flist.clear();
		flist = dir.entryList(ComFunc::m_strFilter,QDir::Files);
		if (flist.size()>0)
		{
			flist.clear();
            flist = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
			if (flist.size()<1)
			{
				mpPath[strPath] = WkpType;
				return;
			}
			
		}
		
		flist.clear();
		flist = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
		if (m_nSearchCount>MAXCOUNT)
		{
			return;
		}
		for (int i=0;i<flist.size();i++)
		{
			QString strTemp = strPath+DIR+flist[i];
			ComFunc::GetOriginalVideoPath(strTemp,mpPath);
		}
		
		return;
			
	}
	else
	{
		std::set<int> ss;
		
		return;
	}
}
void ComFunc::GetPathList(QString &strPath,std::map<QString,int>& mpPath,QStringList& rsltList)
{
	std::map<QString,int>::iterator it = mpPath.begin();
	for (it;it!=mpPath.end();it++)
	{
		if (it->first.contains(strPath))
		{
			rsltList.push_back(it->first);
		}
	}
}