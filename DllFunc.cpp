#include "DllFunc.h"
#include "CommonStruct.h"

#include <QString>
#include <QLibrary>
#include <QCoreApplication>
#include "FramelessDialog.h"
CREATEMAP CDllFunc::m_pFunCreateMap = NULL;
DELETEMAP CDllFunc::m_pFunDeleteMap = NULL;
MOVEMAP   CDllFunc::m_pFunMoveMap = NULL;
//CALLJSBYSTR CDllFunc::m_pFunCallJsByStr = NULL;
//CALLJSBYVEC CDllFunc::m_pFunCallJsByVec = NULL;
//CALLJSBYSZ  CDllFunc::m_pFunCallJsBySz = NULL;
//SETJSCALLBACK CDllFunc::m_pFunSetJsCallBack = NULL;
GOTOPAGE      CDllFunc::m_pFunGoToPage = NULL;
REFRESHEXTENDINFO CDllFunc::m_pFuncRefreshExtendInfo = NULL;
SWITCHPATH    CDllFunc::m_pFuncSwitchPath = NULL;
CLEARPATH     CDllFunc::m_pFuncClearPath = NULL;
SWITHLANGUAGE CDllFunc::m_pFuncSwithLanguage = NULL;
//SETNETTYPE    CDllFunc::m_pFuncSetNetType = NULL;
GETSDCARDPATH CDllFunc::m_pFunGetSdCardPath = NULL;
QLibrary*     CDllFunc::m_pLibMap = NULL;
void CDllFunc::LoadMapPlugin()
{
	
	
	QString strLib = QCoreApplication::applicationDirPath()+DIR+"controlPlugin\\mapPlugin.dll";
	m_pLibMap = new QLibrary(strLib,pDialog);

	if (m_pLibMap && m_pLibMap->load())
	{

		m_pFunCreateMap = (CREATEMAP)m_pLibMap->resolve("CreateMap");
		m_pFunDeleteMap = (DELETEMAP)m_pLibMap->resolve("DeleteMap");
		m_pFunMoveMap = (MOVEMAP)m_pLibMap->resolve("MoveMap");
		//m_pFunCallJsByStr = (CALLJSBYSTR)m_pLibMap->resolve("CallJsByStr");
		//m_pFunCallJsByVec = (CALLJSBYVEC)m_pLibMap->resolve("CallJsByVec");
		//m_pFunSetJsCallBack = (SETJSCALLBACK)m_pLibMap->resolve("SetJsCallBack");
		//m_pFunCallJsBySz = (CALLJSBYSZ)m_pLibMap->resolve("CallJsBySz");
		m_pFunGoToPage = (GOTOPAGE)m_pLibMap->resolve("GoToPage");
		m_pFuncRefreshExtendInfo = (REFRESHEXTENDINFO)m_pLibMap->resolve("RefreshExtendInfo");
		m_pFuncSwitchPath = (SWITCHPATH)m_pLibMap->resolve("SwitchPath");
		m_pFuncClearPath = (CLEARPATH)m_pLibMap->resolve("ClearPath");
		m_pFuncSwithLanguage = (SWITHLANGUAGE)m_pLibMap->resolve("SwitchLanguage");
		//m_pFuncSetNetType = (SETNETTYPE)m_pLibMap->resolve("SetNetType");
        m_pFunGetSdCardPath = (GETSDCARDPATH)m_pLibMap->resolve("GetSDCardPath");
	
	}
	//SetCurrentDirectoryA(strOldMoudle.toStdString().c_str());
}