#include "LoginDialog.h"
#include "winsock2.h"

#include <comutil.h>
#include <QMessageBox>
#include <QProcess>
#pragma comment(lib,"comsupp.lib")
#pragma comment(lib,"Ws2_32.lib")

char CLogin::szName[]={0};
char CLogin::szPwd[]={0};
ENetType CLogin::eNetType = DataCenterInner;
std::string CLogin::strLoginUrlDCI("");
std::string CLogin::strLoginUrlDCE("");
std::string CLogin::strLoginUrlBCI("");
std::string CLogin::strLoginUrlBCE("");

BOOL CLogin::bRememberPwd = FALSE;
CLogin::CLogin()
{

}

CLogin::~CLogin()
{

}
BOOL CLogin::CheckNameAndPwdValid(QString & strName,QString & strPwd)
{
	QString strWarning("");
	BOOL bValid = TRUE;
	if (strName.size()<1 || strPwd.size()<1)
	{
		bValid = FALSE;
	}
	return bValid;
}
int CLogin::LoginAnt(std::string & _str_LoginServerUrl,QString & strName,QString & strPwd)
{
	fd_set rfd;   
	fd_set wfd;
	struct timeval timeout;  
	FD_ZERO(&rfd);
	FD_ZERO(&wfd);
	timeout.tv_sec = 4;
	timeout.tv_usec = 0;

	int iHttpSocket =0,iPort = 80;
	if(_str_LoginServerUrl.find("http://") == -1)
	{
		_str_LoginServerUrl = "http://" + _str_LoginServerUrl;
	}
	std::string strHost,strRequest;
	std::string strTemp = _str_LoginServerUrl.substr(7,_str_LoginServerUrl.size());
	int iPos = strTemp.find('/');
	std::string strPostHost = strTemp.substr(0,iPos);
	iPos = strPostHost.find(':');
	if(iPos != -1)
	{
		strTemp = strPostHost.substr(0,iPos);
		std::string strPort = strPostHost.substr(strTemp.size()+1,strPostHost.size());
		
		strHost = strTemp;
		iPort = atol(strPort.c_str());
	}
	else
	{
		strHost = strPostHost;
	}
	
	strPostHost = "http://" + strPostHost;
	strRequest = _str_LoginServerUrl.substr(strPostHost.size(),_str_LoginServerUrl.size());

	//creat socket
    if ((iHttpSocket=socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		iHttpSocket = 0;
		return CreateFailed;
	}

	//connect
	struct sockaddr_in serv_addr;
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(iPort);
	PHOSTENT phostent = NULL;
	const char* cHostName = strHost.c_str();
	if ((phostent = gethostbyname(cHostName)) == NULL) 
	{
		closesocket (iHttpSocket);	
		iHttpSocket = 0;
		return NotConnect;
	}
	
	unsigned long ul = 1;// unblocking mode
	ioctlsocket(iHttpSocket,FIONBIO,&ul);
    
	bool bConnectedFlag = false;
	memcpy ((char *)&(serv_addr.sin_addr), phostent->h_addr, phostent->h_length);
	int iConnnectRes = connect( iHttpSocket, ( struct sockaddr*)&serv_addr,sizeof(struct sockaddr)) ;
	FD_SET(iHttpSocket,&rfd);
	FD_SET(iHttpSocket,&wfd);
	ul = 0;//blocking mode
	ioctlsocket(iHttpSocket,FIONBIO,&ul);
	int ret = select(0, NULL, &wfd, NULL, &timeout);
	if (ret <= 0)
	{
		closesocket (iHttpSocket);
		iHttpSocket = 0;
		return NotConnect;
	}
	
	
	//ul = 0;
   // ioctlsocket(iHttpSocket,FIOASYNC,&ul);
	//http post method' header
	char send_str[2048] = {0};
	
	strcat(send_str, "POST ");
	strcat(send_str, strRequest.c_str());
	strcat(send_str, " HTTP/1.1\r\n");
	strcat(send_str, "Host: ");
	strcat(send_str, strHost.c_str());
	strcat(send_str, "\r\n");
	strcat(send_str, "Content-Type: application/soap+xml; charset=utf-8\r\n");
	
	std::string strLog,strTime,strVideoType;
	
	strLog="<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n";
	strLog+="<soap12:Envelope xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:soap12=\"http://www.w3.org/2003/05/soap-envelope\">\r\n";
	strLog+="<soap12:Body>\r\n";
	strLog+="<ValidateUser xmlns=\"http://adservice.com/\">\r\n";
	strLog+="<account>";
	strLog+=strName.toStdString();
	strLog+="</account>\r\n";
	strLog+="<password>";
	strLog+=strPwd.toStdString();
	strLog+="</password>\r\n";
	strLog+="</ValidateUser>\r\n";
	strLog+="</soap12:Body>\r\n";
	strLog+="</soap12:Envelope>\r\n";

	char szLength[50] = {0};
	sprintf(szLength,"Content-Length: %d\r\n\r\n",strLog.size());
	strcat(send_str, szLength);
	strcat(send_str, strLog.c_str());
	strcat(send_str, "\r\n\r\n");
       
	int iRes = send(iHttpSocket,send_str,strlen(send_str),0);
	char szOut[2048]={0};
	int nLen = 2048;
    int nL = 0;
	if (select(0,&rfd,NULL,NULL,&timeout) <= 0)
	{
		return HasServer;
	}
	nL = recv(iHttpSocket,szOut,nLen,0);
	if (nL>0 && strlen(szOut)>0)
	{
		QString sF1(VALIDUSER1);
		QString sF2(VALIDUSER2);
		QString str(szOut);
		int nIndex1 = str.indexOf(sF1);
		int nIndex2 = str.indexOf(sF2);
		if (-1 != nIndex1 && -1 != nIndex2 && nIndex2>nIndex1)
		{
			QString strValide = str.mid(nIndex1,nIndex2-nIndex1);
			if (strValide.contains(STRTRUE))
			{
				closesocket(iHttpSocket);
				iHttpSocket = 0;
				return LoginSuccess;
			}
			else if (strValide.contains(STRFALSE))
			{
				closesocket (iHttpSocket);
				iHttpSocket = 0;
				return NamePwdError;
			}
		}
		
	}
	closesocket (iHttpSocket);
	iHttpSocket = 0;
	return HasServer;
}



void CLogin::rc4_setup(  rc4_state *s, unsigned char *key,  int length )
{
	int i, j, k, *m, a;

	s->x = 0;
	s->y = 0;
	m = s->m;

	for( i = 0; i < 256; i++ )
	{
		m[i] = i;
	}

	j = k = 0;

	for( i = 0; i < 256; i++ )
	{
		a = m[i];
		j = (unsigned char) ( j + a + key[k] );
		m[i] = m[j]; m[j] = a;
		if( ++k >= length ) k = 0;
	}
}

void  CLogin::rc4_crypt(  rc4_state *s, unsigned char *data, int length )
{
	if (length<0 || length>strlen((char*)data))
	{
		return;
	}
	/*int i, x, y, *m, a, b;

	x = s->x;
	y = s->y;
	m = s->m;

	for( i = 0; i < length; i++ )
	{
		x = (unsigned char) ( x + 1 ); a = m[x];
		y = (unsigned char) ( y + a );
		m[x] = b = m[y];
		m[y] = a;
		data[i] ^= m[(unsigned char) ( a + b )];
	}

	s->x = x;
	s->y = y;*/
	int nH = length/2;
	for (int j=0;j<nH;j++)
	{
		unsigned int tep = data[length-j-1];
		data[length-j-1] = data[j];
		data[j] = tep;
	}
	int i=0;
	for(i; i < length; i++ )
	{
		
		data[i] = 255 - data[i];
	}

}
