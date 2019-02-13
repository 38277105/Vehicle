#include <QThread>
class CThreadCheckFile:public QThread
{
	CThreadCheckFile(QObject* pParent=NULL);
public:
	static CThreadCheckFile* GetInstance(QObject* pParent = NULL);
	virtual void run();
public:
	static CThreadCheckFile* m_pInstance;
};