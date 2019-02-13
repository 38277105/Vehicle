#include "TipsBox.h"
#include "CommonStruct.h"
#include "LanguageProcessor.h"
#include "FramelessDialog.h"
//QDialog* CFramelessDialog::m_pTipsDialog = NULL;
QString strPicError;
QString strPicWarning;
QString strPicInfo;
int ShowMessageBox(const char*szTitle,const char* szInfo,ETipsType eType)
{
	if (pDialog)
	{
		if (NULL == CFramelessDialog::m_pTipsDialog)
		{
			QUiLoader loader;
			QString curPath = QCoreApplication::applicationDirPath()+DIR+UIPATH+"\\tipsBox.ui";
			QFile file(curPath);
			file.open(QFile::ReadOnly);

			CFramelessDialog::m_pTipsDialog = (QDialog*)loader.load(&file,NULL);//CFramelessDialog::m_bSetConnect?pDialog:NULL

			if (CFramelessDialog::m_pTipsDialog)
			{
				CFramelessDialog::m_pTipsDialog->setWindowTitle("");
				CLanguage::ReadTxtByUi(CFramelessDialog::m_pTipsDialog,"tipsBox");
				if (QLocale::Chinese == CLanguage::m_langId)
				{
					CLanguage::ReadTxtByUi(CFramelessDialog::m_pTipsDialog,"tipsBox",TRUE);
				}
				
				CFramelessDialog::m_pTipsDialog->setModal(true);
				CFramelessDialog::m_pTipsDialog->setWindowFlags(Qt::FramelessWindowHint);
				QWidget* pBtnOk = qFindChild<QWidget*>(CFramelessDialog::m_pTipsDialog,"btnOk");
				if (pBtnOk)
				{
					pBtnOk->connect((const QObject*)pBtnOk,SIGNAL(clicked()),CFramelessDialog::m_pTipsDialog,SLOT(accept()));
				}
				QWidget* pBtnCancel = qFindChild<QWidget*>(CFramelessDialog::m_pTipsDialog,"btnCancel");
				if (pBtnCancel)
				{
					pBtnCancel->connect((const QObject*)pBtnCancel,SIGNAL(clicked()),CFramelessDialog::m_pTipsDialog,SLOT(reject()));
				}
				QWidget* pBtnClose = qFindChild<QWidget*>(CFramelessDialog::m_pTipsDialog,"btnClose");
				if (pBtnClose)
				{
					pBtnClose->connect((const QObject*)pBtnClose,SIGNAL(clicked()),CFramelessDialog::m_pTipsDialog,SLOT(reject()));
				}
			}
		}
		if (CFramelessDialog::m_pTipsDialog)
		{
			CLanguage::UpdatePageLanguage(CFramelessDialog::m_pTipsDialog);
			QWidget* pBtnOk = qFindChild<QWidget*>(CFramelessDialog::m_pTipsDialog,"btnOk");
			QWidget* pBtnCancel = qFindChild<QWidget*>(CFramelessDialog::m_pTipsDialog,"btnCancel");
			if(eInfoTip == eType)
			{
				if(pBtnOk)
				{
					pBtnOk->show();
				}
				if (pBtnCancel)
				{
					pBtnCancel->show();
				}
				
			}
			else
			{
				if(pBtnOk)
				{
					pBtnOk->show();
				}
				if (pBtnCancel)
				{
					pBtnCancel->hide();
				}
			}
			QLabel* pTitle = qFindChild<QLabel*>(CFramelessDialog::m_pTipsDialog,"labelTitle");
			QString strText("");
			if (pTitle)
			{
				CLanguage::GetTxtByStr(szTitle,strText,CFramelessDialog::m_pTipsDialog);
				pTitle->setText(strText);
			}
			QLabel* pInfo = qFindChild<QLabel*>(CFramelessDialog::m_pTipsDialog,"labelInfo");
			if (pInfo)
			{
				CLanguage::GetTxtByStr(szInfo,strText,CFramelessDialog::m_pTipsDialog);
				pInfo->setText(strText);
			}
			QWidget* pPic = qFindChild<QWidget*>(CFramelessDialog::m_pTipsDialog,"pic_widget");
			if (pPic)
			{
				switch(eType)
				{
				case eErrorTip:
					{
						pPic->setStyleSheet(strPicError);
						break;
					}
				case eWarningTip:
					{
						pPic->setStyleSheet(strPicWarning);
						break;
					}
				case eInfoTip:
					{
						pPic->setStyleSheet(strPicInfo);
						break;
					}
				default:
					{
						break;
					}
				}
			}
			return CFramelessDialog::m_pTipsDialog->exec();
		}
	}
	return FALSE;
}