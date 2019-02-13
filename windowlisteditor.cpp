#include "windowlisteditor.h"
#include <QTableWidget>
extern QWidget* pDialog;
WindowListEditor::WindowListEditor(QWidget *widget):QComboBox(widget)
{
	readConfig();
	populateList();
	
	
	if (pDialog)
	{
		pDialog->connect((const QObject*)this,SIGNAL(currentIndexChanged(int)),(const QObject*)pDialog,SLOT(windowIndexChanged(int)));
	}
}
QString WindowListEditor::windowName() const
{
	return qVariantValue<QString>(itemData(currentIndex(), Qt::DecorationRole));
}
void WindowListEditor::setWindowName(QString c)
{
	setCurrentIndex(findData(c, int(Qt::DecorationRole)));
	
}
void WindowListEditor::populateList()
{
	
	for (int i = 0; i < m_nTotalWindow; ++i) {
		QString str=m_strwindowPre+SPACE+QString::number(i+1);
		
		insertItem(i, str);
		setItemData(i, str, Qt::DecorationRole);
	}
}
void WindowListEditor::readConfig()
{
	m_nTotalWindow = 4;
	m_strwindowPre = "Window";
}