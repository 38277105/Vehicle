#include "LanguageProcessor.h"
#include "FramelessDialog.h"
#include <QCoreApplication>
#include <QFile>
#include <QDomDocument>
#include <QAbstractButton>
#include <QLabel>
#include <QLineEdit>
#include <QDialog>
#include <QDialogButtonBox>
#include <QGroupBox>
PAGELANGUA CLanguage::m_mapLangTable;
ElanguageType CLanguage::m_eLanguageType = languageEsp;
QLocale::Language CLanguage::m_langId = QLocale::English;
QString CLanguage::strAlarmVideo("");
QString CLanguage::strNormalVideo("");
QString CLanguage::strNoSignalEs("");
QString CLanguage::strNoSignalEn("");
QString CLanguage::strNoSignalCh("");
QString CLanguage::strNoGPSEs("");
QString CLanguage::strNoGPSEn("");
QString CLanguage::strNoGPSCh("");
QString CLanguage::strSignal("");
QString CLanguage::strGps("");
void CLanguage::ReadAllTxt()
{

}
void CLanguage::ReadTxtByUi(QWidget* pParent,const char* szUi,BOOL bChn)
{
	PAGELANGUA::iterator it = m_mapLangTable.find(pParent);
	//if (m_mapLangTable.end() == it)
	{
		QString curPath = QCoreApplication::applicationDirPath()+DIR+UIPATH+"\\lang.xml";
		if (1 == bChn)
		{
			curPath = QCoreApplication::applicationDirPath()+DIR+UIPATH+"\\langcn.xml";
		}
		QFile file(curPath);
		if(!file.open(QIODevice::ReadOnly))
		{
			return;
		}
		QDomDocument xmlDoc("mydoc");
		QString error;  
		int row = 0, column = 0;  

        if (!xmlDoc.setContent(&file,false,&error,&row,&column))
        {
			file.close();
			return;
        }
		if (xmlDoc.isNull())
		{
			file.close();
			return;
		}
		QDomElement langRoot = xmlDoc.documentElement();
        QString rootName = langRoot.attributeNode("name").value();
		if ("language" == rootName)
		{
			QDomNodeList uiList = langRoot.childNodes();
			int nCount = uiList.count();
			QDomNode uiNode;
			QDomElement uiElement;
			QDomNodeList widgetList;
			QDomNode widgetNode;
			QDomElement widgetElement;
            QString strEng;
			QString strSpa;
			QString strChn;
			QString strWidgetName;
			for (int i=0;i<nCount;i++)
			{
				uiNode = uiList.item(i);
                uiElement = uiNode.toElement();
				QString uiName = uiElement.attributeNode("ui").value();
				if (szUi == uiName)
				{
					widgetList = uiElement.childNodes();
					int nChilds = widgetList.count();
					for (int k=0;k<nChilds;k++)
					{
                       widgetNode = widgetList.item(k);
					   widgetElement = widgetNode.toElement();
					   strWidgetName="";
                       strWidgetName = widgetElement.attributeNode("name").value();
                       if (!strWidgetName.isEmpty())
                       {
						   if (bChn)
						   {
							   strChn = widgetElement.attributeNode("chinese").value();
							   m_mapLangTable[pParent][strWidgetName].second.second = strChn;
						   } 
						   else
						   {
							   strEng = widgetElement.attributeNode("english").value();
							   strSpa = widgetElement.attributeNode("spanish").value();
							   
							   m_mapLangTable[pParent][strWidgetName].first = strSpa;
							   m_mapLangTable[pParent][strWidgetName].second.first = strEng;
						   }
						  
                       }               

					}
					file.close();
                    return;
				}
			}
		}
		file.close();
	}
}
void CLanguage::UpdatePageLanguage(QWidget* pParent,BOOL bUpdateAll/* =FALSE */)
{
	if (bUpdateAll)
	{
		PAGELANGUA::iterator itUi = m_mapLangTable.begin();
		for (itUi;itUi!=m_mapLangTable.end();itUi++)
		{
			WIDGETLANGUA::iterator itWidget = itUi->second.begin();
			for (itWidget;itWidget!=itUi->second.end();itWidget++)
			{
				if(itWidget->first.contains("btn"))
				{
					QAbstractButton* pBtn = qFindChild<QAbstractButton*>(pParent,itWidget->first);
					if (!pBtn)
					{
						continue;
					}
					if(languageChn == m_eLanguageType)
					{
						pBtn->setText(itWidget->second.second.second);
					}
					else if (languageEsp == m_eLanguageType)
					{
						pBtn->setText(itWidget->second.first);
					} 
					else
					{
						pBtn->setText(itWidget->second.second.first);
					}

				}
				else if (itWidget->first.contains("Edit"))
				{
					QLineEdit* pEdit = qFindChild<QLineEdit*>(pParent,itWidget->first);
					if(!pEdit)
					{
						continue;
					}
					if(languageChn == m_eLanguageType)
					{
						pEdit->setText(itWidget->second.second.second);
					}
					else if (languageEsp == m_eLanguageType)
					{
						pEdit->setText(itWidget->second.first);
					} 
					else
					{
						pEdit->setText(itWidget->second.second.first);
					}
					
				}
				else if (itWidget->first.contains("Label"))
				{
					QLabel* pLabel = qFindChild<QLabel*>(pParent,itWidget->first);
					if(!pLabel)
					{
						continue;
					}
					if(languageChn == m_eLanguageType)
					{
						pLabel->setText(itWidget->second.second.second);
					}
					else if (languageEsp == m_eLanguageType)
					{
						pLabel->setText(itWidget->second.first);
					} 
					else
					{
						pLabel->setText(itWidget->second.second.first);
					}
					
				}
				else if (itWidget->first.contains("Check"))
				{
					QCheckBox* pCheck = qFindChild<QCheckBox*>(pParent,itWidget->first);
					if(!pCheck)
					{
						continue;
					}
					if(languageChn == m_eLanguageType)
					{
						pCheck->setText(itWidget->second.second.second);
					}
					else if (languageEsp == m_eLanguageType)
					{
						pCheck->setText(itWidget->second.first);
					} 
					else
					{
						pCheck->setText(itWidget->second.second.first);
					}
					
				}
				else if (itWidget->first.contains("Box"))
				{
					QGroupBox* pGroupBox = qFindChild<QGroupBox*>(pParent,itWidget->first);
					if (!pGroupBox)
					{
                       continue;
					}
					if (languageChn == m_eLanguageType)
					{
						pGroupBox->setTitle(itWidget->second.second.second);
					}
					else if (languageEsp == m_eLanguageType)
					{
						pGroupBox->setTitle(itWidget->second.first);
					} 
					else
					{
						pGroupBox->setTitle(itWidget->second.second.first);
					}
					
				}
				else if (itWidget->first.contains("Dialog"))
				{
					QDialog* pThis = (QDialog*)(pParent);
					if (!pParent)
					{
						continue;
					}
					if(languageChn)
					{
						pThis->setWindowTitle(itWidget->second.second.second);
					}
					else if (languageEsp == m_eLanguageType)
					{
                        pThis->setWindowTitle(itWidget->second.first);
					}
					else
					{
						pThis->setWindowTitle(itWidget->second.second.first);
					}
					
				}
			}
		}
		UpdateMenuComboBoxText();
	} 
	else
	{
		PAGELANGUA::iterator itUi = m_mapLangTable.find(pParent);
		if (itUi != m_mapLangTable.end())
		{
			WIDGETLANGUA::iterator itWidget = itUi->second.begin();
			for (itWidget;itWidget!=itUi->second.end();itWidget++)
			{
				if(itWidget->first.contains("btn"))
				{
					QAbstractButton* pBtn = qFindChild<QAbstractButton*>(pParent,itWidget->first);
					if (!pBtn)
					{
						continue;
					}
					if(languageChn == m_eLanguageType)
					{
						pBtn->setText(itWidget->second.second.second);
					}
					else if (languageEsp == m_eLanguageType)
					{
						pBtn->setText(itWidget->second.first);
					} 
					else
					{
						pBtn->setText(itWidget->second.second.first);
					}
					

				}
				else if (itWidget->first.contains("Edit"))
				{
					QLineEdit* pEdit = qFindChild<QLineEdit*>(pParent,itWidget->first);
					if(!pEdit)
					{
						continue;
					}
					if(languageChn == m_eLanguageType)
					{
						pEdit->setText(itWidget->second.second.second);
					}
					else if (languageEsp == m_eLanguageType)
					{
						pEdit->setText(itWidget->second.first);
					} 
					else
					{
						pEdit->setText(itWidget->second.second.first);
					}
					
				}
				else if (itWidget->first.contains("Label"))
				{
					QLabel* pLabel = qFindChild<QLabel*>(pParent,itWidget->first);
					if(!pLabel)
					{
						continue;
					}
					if(languageChn == m_eLanguageType)
					{
						pLabel->setText(itWidget->second.second.second);
					}
					else if (languageEsp == m_eLanguageType)
					{
						pLabel->setText(itWidget->second.first);
					} 
					else
					{
						pLabel->setText(itWidget->second.second.first);
					}
					
				}
				else if (itWidget->first.contains("Check"))
				{
					QCheckBox* pCheck = qFindChild<QCheckBox*>(pParent,itWidget->first);
					if(!pCheck)
					{
						continue;
					}
					if(languageChn == m_eLanguageType)
					{
						pCheck->setText(itWidget->second.second.second);
					}
					else if (languageEsp == m_eLanguageType)
					{
						pCheck->setText(itWidget->second.first);
					} 
					else
					{
						pCheck->setText(itWidget->second.second.first);
					}
					
				}
				else if (itWidget->first.contains("Box"))
				{
					QGroupBox* pGroupBox = qFindChild<QGroupBox*>(pParent,itWidget->first);
					if (!pGroupBox)
					{
						continue;
					}
					if(languageChn == m_eLanguageType)
					{
						pGroupBox->setTitle(itWidget->second.second.second);
					}
					else if (languageEsp == m_eLanguageType)
					{
						pGroupBox->setTitle(itWidget->second.first);
					} 
					else
					{
						pGroupBox->setTitle(itWidget->second.second.first);
					}
					
				}
				else if (itWidget->first.contains("Dialog"))
				{
					QDialog* pThis = (QDialog*)(pParent);
					if (!pParent)
					{
						continue;
					}
					if(languageChn == m_eLanguageType)
					{
						pThis->setWindowTitle(itWidget->second.second.second);
					}
					else if (languageEsp == m_eLanguageType)
					{
						pThis->setWindowTitle(itWidget->second.first);
					}
					else
					{
						pThis->setWindowTitle(itWidget->second.second.first);
					}
					
				}
			}
		}
	}
	if (pParent && (Qt::Dialog && pParent->windowFlags()) )
    {
		QDialogButtonBox* pButtonBox = qFindChild<QDialogButtonBox*>(pParent,"buttonBox");
		if (pButtonBox)
		{
			QString strOK;
			QString strCancel;
			if (languageChn == m_eLanguageType)
			{
				strOK = m_mapLangTable[pDialog]["strOk"].second.second;
				strCancel = m_mapLangTable[pDialog]["strCancel"].second.second;	
			}
			else if (languageEsp == m_eLanguageType)
			{
				strOK = m_mapLangTable[pDialog]["strOk"].first;
				strCancel = m_mapLangTable[pDialog]["strCancel"].first;
			} 
			else
			{
				strOK = m_mapLangTable[pDialog]["strOk"].second.first;
				strCancel = m_mapLangTable[pDialog]["strCancel"].second.first;
				
			}
			
			QPushButton* pBtnok = pButtonBox->button(QDialogButtonBox::Ok);
			QPushButton* pBtnCancel = pButtonBox->button(QDialogButtonBox::Cancel);
			if (pBtnok)
			{
				pBtnok->setText(strOK);
			}
			if (pBtnCancel)
			{
				pBtnCancel->setText(strCancel);
			}

		}
    }
}
BOOL CLanguage::GetTxtById(eTextType etype,QString& strResult)
{
	return TRUE;
}
BOOL CLanguage::GetTxtByStr(const char* strSrc,QString &strResult,QWidget* pParent)
{
	if (NULL == pParent)
	{
	} 
	else
	{
		LANGMAP::iterator it = m_mapLangTable.find(pParent);
		if (m_mapLangTable.end() == it)
		{
			return FALSE;
		}
		TXTMAP::iterator itTxt = it->second.find(strSrc);
		if (it->second.end() == itTxt)
		{
			return FALSE;
		}
		if (languageChn == m_eLanguageType)
		{
			strResult = itTxt->second.second.second;
		}
		else if (languageEsp == m_eLanguageType)
		{
			strResult = itTxt->second.first;
		} 
		else
		{
			strResult = itTxt->second.second.first;
		}
		
	}
	return TRUE;
}
void CLanguage::SetLangType(ElanguageType langType)
{
	if (langType != m_eLanguageType)
	{
		m_eLanguageType = langType;
	}
}
void CLanguage::GetSignalText()
{
	strNoSignalEs = m_mapLangTable[pDialog]["noSignal"].first;
	strNoSignalEn = m_mapLangTable[pDialog]["noSignal"].second.first;
	strNoSignalCh = m_mapLangTable[pDialog]["noSignal"].second.second;

	strNoGPSEs = m_mapLangTable[pDialog]["noGps"].first;
	strNoGPSEn = m_mapLangTable[pDialog]["noGps"].second.first;
	strNoGPSCh = m_mapLangTable[pDialog]["noGps"].second.second;
}
void CLanguage::UpdateMenuComboBoxText()
{
	CFramelessDialog* pMaindlg = (CFramelessDialog*)pDialog;
	if (pMaindlg)
	{
		if (pMaindlg->m_pOpenCombox)
		{
			QString strOpenLocal("");
			QString strOpenSD("");
			QString strDirectory("");
			QString strExit("");
			QString strSpa("");
			QString strEng("");
			QString strChn("");
			QString strVideoName("");
			QString strVideoWindow("");
			QString strVideoSize("");
			QString strVideoPath("");
			QString strNumber("");
			QString strTime("");
			QString strLen("");
			QString strType("");
		   
	
			if (languageChn == m_eLanguageType)
			{
				strOpenLocal = m_mapLangTable[pDialog]["strOpenLocal"].second.second;
				strOpenSD = m_mapLangTable[pDialog]["strOpenSD"].second.second;
				strDirectory = m_mapLangTable[pDialog]["strOpenDir"].second.second;
				strExit = m_mapLangTable[pDialog]["strExit"].second.second;
				strSpa = m_mapLangTable[pDialog]["langSpa"].second.second;
				strEng = m_mapLangTable[pDialog]["langEng"].second.second;
				strChn = m_mapLangTable[pDialog]["langChn"].second.second;

				strVideoName = m_mapLangTable[pDialog]["videoName"].second.second;
				strVideoWindow = m_mapLangTable[pDialog]["videoWindow"].second.second;
				strVideoSize = m_mapLangTable[pDialog]["videoSize"].second.second;
				strVideoPath = m_mapLangTable[pDialog]["videoPath"].second.second;

				strNumber = m_mapLangTable[pDialog]["number"].second.second;
				strTime = m_mapLangTable[pDialog]["time"].second.second;
				strLen = m_mapLangTable[pDialog]["duration"].second.second;
				strType = m_mapLangTable[pDialog]["videoType"].second.second;
				strNormalVideo = m_mapLangTable[pDialog]["normal"].second.second;
				strAlarmVideo = m_mapLangTable[pDialog]["alarm"].second.second;

				//strSignal = m_mapLangTable[pDialog]["noSignal"].second.second;
				//strGps = m_mapLangTable[pDialog]["noGps"].second.second;
				strSignal = strNoSignalCh;
				strGps = strNoGPSCh;
			}
			else if (languageEsp == m_eLanguageType)
			{
				strOpenLocal = m_mapLangTable[pDialog]["strOpenLocal"].first;
				strOpenSD = m_mapLangTable[pDialog]["strOpenSD"].first;
				strDirectory = m_mapLangTable[pDialog]["strOpenDir"].first;
				strExit = m_mapLangTable[pDialog]["strExit"].first;
				strSpa = m_mapLangTable[pDialog]["langSpa"].first;
				strEng = m_mapLangTable[pDialog]["langEng"].first;
				strChn = m_mapLangTable[pDialog]["langChn"].first;
				strVideoName = m_mapLangTable[pDialog]["videoName"].first;
				strVideoWindow = m_mapLangTable[pDialog]["videoWindow"].first;
				strVideoSize = m_mapLangTable[pDialog]["videoSize"].first;
				strVideoPath = m_mapLangTable[pDialog]["videoPath"].first;
				strNumber = m_mapLangTable[pDialog]["number"].first;
				strTime = m_mapLangTable[pDialog]["time"].first;
				strLen = m_mapLangTable[pDialog]["duration"].first;
				strType = m_mapLangTable[pDialog]["videoType"].first;

				strNormalVideo = m_mapLangTable[pDialog]["normal"].first;
				strAlarmVideo = m_mapLangTable[pDialog]["alarm"].first;

				//strSignal = m_mapLangTable[pDialog]["noSignal"].first;
				//strGps = m_mapLangTable[pDialog]["noGps"].first;
				strSignal = strNoSignalEs;
				strGps = strNoGPSEs;
			} 
			else
			{
				strOpenLocal = m_mapLangTable[pDialog]["strOpenLocal"].second.first;
				strOpenSD = m_mapLangTable[pDialog]["strOpenSD"].second.first;
				strDirectory = m_mapLangTable[pDialog]["strOpenDir"].second.first;
				strExit = m_mapLangTable[pDialog]["strExit"].second.first;
				strSpa = m_mapLangTable[pDialog]["langSpa"].second.first;
				strEng = m_mapLangTable[pDialog]["langEng"].second.first;
				strChn = m_mapLangTable[pDialog]["langChn"].second.first;

				strVideoName = m_mapLangTable[pDialog]["videoName"].second.first;
				strVideoWindow = m_mapLangTable[pDialog]["videoWindow"].second.first;
				strVideoSize = m_mapLangTable[pDialog]["videoSize"].second.first;
				strVideoPath = m_mapLangTable[pDialog]["videoPath"].second.first;

				strNumber = m_mapLangTable[pDialog]["number"].second.first;
				strTime = m_mapLangTable[pDialog]["time"].second.first;
				strLen = m_mapLangTable[pDialog]["duration"].second.first;
				strType = m_mapLangTable[pDialog]["videoType"].second.first;

				strNormalVideo = m_mapLangTable[pDialog]["normal"].second.first;
				strAlarmVideo = m_mapLangTable[pDialog]["alarm"].second.first;

				//strSignal = m_mapLangTable[pDialog]["noSignal"].second.first;
				//strGps = m_mapLangTable[pDialog]["noGps"].second.first;
			    strSignal = strNoSignalEn;
				strGps = strNoGPSEn;
			}
			
			if ( pMaindlg->m_pOpenCombox->maxCount()>=3)
			{
				
				pMaindlg->m_pOpenCombox->setItemText(0,strOpenLocal);
				pMaindlg->m_pOpenCombox->setItemText(1,strOpenSD);
				pMaindlg->m_pOpenCombox->setItemText(2,strDirectory);
			} 
			if (pMaindlg->m_pEspAction)
			{
				pMaindlg->m_pEspAction->setText(strSpa);
			}
			if (pMaindlg->m_pEngAction)
			{
				pMaindlg->m_pEngAction->setText(strEng);
			}
			if (pMaindlg->m_pChnAction)
			{
				pMaindlg->m_pChnAction->setText(strChn);
			}
			if (pMaindlg->m_pExitAction)
			{
				pMaindlg->m_pExitAction->setText(strExit);
			}
			if (pMaindlg->m_pTableList)
			{
				UpdateTableText();
				
			}
			QString strText("");
			if (pMaindlg->m_pWWANRLevelLT)
			{
				 strText = pMaindlg->m_pWWANRLevelLT->text();
				if(strText.contains(strNoSignalCh) || strText.contains(strNoSignalEn) || strText.contains(strNoSignalEs))
				{
					pMaindlg->m_pWWANRLevelLT->setText(strSignal);
				}
			}
			if (pMaindlg->m_pGpsLT)
			{
				strText = pMaindlg->m_pGpsLT->text();
				if (strText.contains(strNoGPSCh) || strText.contains(strNoGPSEn) || strText.contains(strNoGPSEs))
				{
					pMaindlg->m_pGpsLT->setText(strGps);
				}
			}

			if (pMaindlg->m_pWWANRLevelLB)
			{
				strText = pMaindlg->m_pWWANRLevelLB->text();
				if(strText.contains(strNoSignalCh) || strText.contains(strNoSignalEn) || strText.contains(strNoSignalEs))
				{
					pMaindlg->m_pWWANRLevelLB->setText(strSignal);
				}
			}

			if (pMaindlg->m_pGpsLB)
			{
				strText = pMaindlg->m_pGpsLB->text();
				if (strText.contains(strNoGPSCh) || strText.contains(strNoGPSEn) || strText.contains(strNoGPSEs))
				{
					pMaindlg->m_pGpsLB->setText(strGps);
				}
			}

			if (pMaindlg->m_pWWANRLevelRT)
			{
				strText = pMaindlg->m_pWWANRLevelRT->text();
				if(strText.contains(strNoSignalCh) || strText.contains(strNoSignalEn) || strText.contains(strNoSignalEs))
				{
					pMaindlg->m_pWWANRLevelRT->setText(strSignal);
				}
			}

			if (pMaindlg->m_pGpsRT)
			{
				strText = pMaindlg->m_pGpsRT->text();
				if (strText.contains(strNoGPSCh) || strText.contains(strNoGPSEn) || strText.contains(strNoGPSEs))
				{
					pMaindlg->m_pGpsRT->setText(strGps);
				}
			}

			if (pMaindlg->m_pWWANRLevelRB)
			{
				strText = pMaindlg->m_pWWANRLevelRB->text();
				if(strText.contains(strNoSignalCh) || strText.contains(strNoSignalEn) || strText.contains(strNoSignalEs))
				{
					pMaindlg->m_pWWANRLevelRB->setText(strSignal);
				}
			}

			if (pMaindlg->m_pGpsRB)
			{
				strText = pMaindlg->m_pGpsRB->text();
				if (strText.contains(strNoGPSCh) || strText.contains(strNoGPSEn) || strText.contains(strNoGPSEs))
				{
					pMaindlg->m_pGpsRB->setText(strGps);
				}
			}
            pMaindlg->updateOSD(ANYINDEX);
			
		}
	}
}
void CLanguage::UpdateTableText()
{
	CFramelessDialog* pMaindlg = (CFramelessDialog*)pDialog;
	if(pMaindlg && pMaindlg->m_pTableList)
	{
		QString strVideoName("");
		QString strVideoWindow("");
		QString strVideoSize("");
		QString strVideoPath("");
		QString strNumber("");
		QString strTime("");
		QString strLen("");
		QString strType("");
		if (languageChn == m_eLanguageType)
		{
			strVideoName = m_mapLangTable[pDialog]["videoName"].second.second;
			strVideoWindow = m_mapLangTable[pDialog]["videoWindow"].second.second;
			strVideoSize = m_mapLangTable[pDialog]["videoSize"].second.second;
			strVideoPath = m_mapLangTable[pDialog]["videoPath"].second.second;
			strNumber = m_mapLangTable[pDialog]["number"].second.second;
			strTime = m_mapLangTable[pDialog]["time"].second.second;
			strLen = m_mapLangTable[pDialog]["duration"].second.second;
			strType = m_mapLangTable[pDialog]["videoType"].second.second;
		}
		else if (languageEsp == m_eLanguageType)
		{
			strVideoName = m_mapLangTable[pDialog]["videoName"].first;
			strVideoWindow = m_mapLangTable[pDialog]["videoWindow"].first;
			strVideoSize = m_mapLangTable[pDialog]["videoSize"].first;
			strVideoPath = m_mapLangTable[pDialog]["videoPath"].first;
			strNumber = m_mapLangTable[pDialog]["number"].first;
			strTime = m_mapLangTable[pDialog]["time"].first;
			strLen = m_mapLangTable[pDialog]["duration"].first;
			strType = m_mapLangTable[pDialog]["videoType"].first;
		} 
		else
		{
			strVideoName = m_mapLangTable[pDialog]["videoName"].second.first;
			strVideoWindow = m_mapLangTable[pDialog]["videoWindow"].second.first;
			strVideoSize = m_mapLangTable[pDialog]["videoSize"].second.first;
			strVideoPath = m_mapLangTable[pDialog]["videoPath"].second.first;
			strNumber = m_mapLangTable[pDialog]["number"].second.first;
			strTime = m_mapLangTable[pDialog]["time"].second.first;
			strLen = m_mapLangTable[pDialog]["duration"].second.first;
			strType = m_mapLangTable[pDialog]["videoType"].second.first;
		}
		
		if (pMaindlg->m_bSDK)
		{
			QTableWidgetItem* pItemNumber = pMaindlg->m_pTableList->horizontalHeaderItem(0);
			if (pItemNumber)
			{
				pItemNumber->setText(strNumber);
			}
		
			QTableWidgetItem* pItemLen = pMaindlg->m_pTableList->horizontalHeaderItem(2);
			if (pItemLen)
			{
				pItemLen->setText(strLen);
			}
			QTableWidgetItem* pItemType = pMaindlg->m_pTableList->horizontalHeaderItem(1);
			if (pItemType)
			{
				pItemType->setText(strType);
			}
			QTableWidgetItem* pItemTime = pMaindlg->m_pTableList->horizontalHeaderItem(3);
			if (pItemTime)
			{
				pItemTime->setText(strTime);
			}
			for (int i=0;i<pMaindlg->m_pTableList->rowCount();i++)
			{
				QTableWidgetItem* pItem = pMaindlg->m_pTableList->item(i,1);
				if (pItem && pMaindlg->m_brAlarm == pItem->background())
				{
					pItem->setText(strAlarmVideo);
				}
				else
				{
					pItem->setText(strNormalVideo);
				}
			}
		} 
		else
		{
			QTableWidgetItem* pItemName = pMaindlg->m_pTableList->horizontalHeaderItem(0);
			if (pItemName)
			{
				pItemName->setText(strVideoName);
			}
			/*QTableWidgetItem* pItemWindow = pMaindlg->m_pTableList->horizontalHeaderItem(1);
			if (pItemWindow)
			{
				pItemWindow->setText(strVideoWindow);
			}*/
			QTableWidgetItem* pItemSize = pMaindlg->m_pTableList->horizontalHeaderItem(1);
			if (pItemSize)
			{
				pItemSize->setText(strVideoSize);
			}
			QTableWidgetItem* pItemPath = pMaindlg->m_pTableList->horizontalHeaderItem(2);
			if (pItemPath)
			{
				pItemPath->setText(strVideoPath);
			}
			QTableWidgetItem* pItemWindow = pMaindlg->m_pTableList->horizontalHeaderItem(3);
			if (pItemWindow)
			{
				pItemWindow->setText("");
			}
		}
	}
}
