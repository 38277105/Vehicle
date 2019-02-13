#include <QtUiTools/QtUiTools>
#include <QPushButton>
#include <QDialog>
#include <QTextEdit>
#include <string>
#include "CommonStruct.h"
enum EloginStatus
{
    LoginSuccess=1,
	NamePwdError=2,
	NotConnect=3,
	CreateFailed=4,
	HasServer=5
};
class CLogin
{
	
public:
	CLogin();
	
	~CLogin();
	static BOOL CheckNameAndPwdValid(QString & strName,QString & strPwd);
	static int LoginAnt(std::string & strLoginUrl,QString & strName,QString & strPwd);
	static void rc4_setup( rc4_state *s, unsigned char *key,  int length );
	static void rc4_crypt( rc4_state *s, unsigned char *data, int length );
	

public:
	static char szName[NAMELEN];
	static char szPwd[NAMELEN];
	static BOOL bRememberPwd;
	static ENetType eNetType;
	static std::string strLoginUrlDCI;
	static std::string strLoginUrlDCE;
	static std::string strLoginUrlBCI;
	static std::string strLoginUrlBCE;
	
	
};
