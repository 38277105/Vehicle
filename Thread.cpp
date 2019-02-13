#include "Thread.h"
#include "FramelessDialog.h"
CThreadCheckFile* CThreadCheckFile::m_pInstance = NULL;

CThreadCheckFile::CThreadCheckFile(QObject * pParent):QThread(pParent)
{

}
CThreadCheckFile* CThreadCheckFile::GetInstance(QObject * pParent)
{
	if (!m_pInstance)
	{
		m_pInstance = new CThreadCheckFile(pParent);
	}
	return m_pInstance;

}
void CThreadCheckFile::run()
{
	QString strFile;
	CFramelessDialog* pMainDlg = (CFramelessDialog*)pDialog;
	CFramelessDialog::m_memShared.create(MAXFILELEN);
	//EnterCriticalSection(&(CFramelessDialog::m_crCheckFile));
	while(CFramelessDialog::m_bIsRun && pMainDlg)
	{

		CFramelessDialog::m_memShared.lock();

		char * szMem = static_cast<char*>(CFramelessDialog::m_memShared.data());
		strFile = szMem;
		memset(szMem,0,CFramelessDialog::m_memShared.size());
		CFramelessDialog::m_memShared.unlock();
		//CFramelessDialog::m_memShared.detach();

		if (strFile.contains(JNPREFIX))
		{
			pMainDlg->m_strFileImmediate = strFile;
			emit(pMainDlg->newTsFile());
		}
		else
		{
			sleep(2);
		}
	}
	CFramelessDialog::m_memShared.detach();
	//LeaveCriticalSection(&(CFramelessDialog::m_crCheckFile));
}