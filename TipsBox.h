#ifndef TIPSMESSAGEBOX
#define TIPSMESSAGEBOX

enum ETipsType
{
	eErrorTip=0,
	eWarningTip=1,
	eInfoTip=2
};

int ShowMessageBox(const char*szTitle,const char* szInfo,ETipsType eType);
#endif
