#ifndef DLLFUNCHEADER
#define DLLFUNCHEADER
#include <QWidget>
#include <string>
#include <vector>
#include <QLibrary>
#include "CommonStruct.h"
enum EMapType
{
	eOfflinePlay=0,
	e911RealPlay=1,
	e911WarningPlay=2,
	e911ServiceHis=3,
	e911MdvrHis=4
};

typedef void (* JSCALLBACK)(char* szInfo);
typedef int (*CREATEMAP)(HWND hParent,HWND* pReturnHwnd,EMapType eType);
typedef void (*DELETEMAP)(EMapType eType);
typedef void (*MOVEMAP)(int x,int y,int nWidth,int nHeight,EMapType eType);
typedef void (*CALLJSBYSTR)(const std::string &strIn,std::string &strOut,EMapType eType);
typedef void (*CALLJSBYVEC)(const std::vector<std::string>&vcIn,std::string & strOut,EMapType eType);
typedef void (*CALLJSBYSZ)(const char* szIn,std::string & strOut,EMapType eType);
typedef int  (*SETJSCALLBACK)(JSCALLBACK pFunc,EMapType eType);
typedef void (*GOTOPAGE)(const char* szPageName,EMapType eType);
typedef void (*REFRESHEXTENDINFO)(const char* szInfo,int nWnd,int nIndex,BOOL bHistory,EMapType eType);
typedef int (*SWITCHPATH)(int nWnd,EMapType eType);
typedef int (*SWITHLANGUAGE)(int nLangid,EMapType eType);
typedef int (*SETNETTYPE)(int nType,EMapType eType);
typedef int (*CLEARPATH)(int nWnd,EMapType eType);
typedef int (*GETSDCARDPATH)(HWND hWnd,char* szPath);
class CDllFunc
{
public:
	static void LoadMapPlugin();
public:
    static CREATEMAP m_pFunCreateMap;
	static DELETEMAP m_pFunDeleteMap;
	static MOVEMAP   m_pFunMoveMap;
	//static CALLJSBYSTR m_pFunCallJsByStr;
	//static CALLJSBYVEC m_pFunCallJsByVec;
	//static CALLJSBYSZ  m_pFunCallJsBySz;
	//static SETJSCALLBACK m_pFunSetJsCallBack;
	static GOTOPAGE      m_pFunGoToPage;
	static REFRESHEXTENDINFO m_pFuncRefreshExtendInfo;
	static SWITCHPATH m_pFuncSwitchPath;
	static CLEARPATH  m_pFuncClearPath;
	static SWITHLANGUAGE m_pFuncSwithLanguage;
	//static SETNETTYPE    m_pFuncSetNetType;
	static GETSDCARDPATH m_pFunGetSdCardPath;
	static QLibrary*     m_pLibMap;
};
#endif
