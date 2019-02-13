#ifndef WINDOWLISTEDITOR_H
#define WINDOWLISTEDITOR_H
#include <QComboBox>
#define  SPACE " "

class WindowListEditor:public QComboBox
{
	Q_OBJECT
		Q_PROPERTY(QString windowName READ windowName WRITE setWindowName USER true)
public:
	WindowListEditor(QWidget *widget = 0);

public:
	QString windowName() const;
	void setWindowName(QString c);
	void readConfig();

private:
	void populateList();
	int m_nTotalWindow;
	QString m_strwindowPre;
};
#endif