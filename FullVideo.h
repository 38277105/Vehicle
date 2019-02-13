#ifndef FULLVIDEOHEADER
#define FULLVIDEOHEADER
#include <QFrame>
#include "CommonStruct.h"
class CFullVideo:public QFrame
{
	Q_OBJECT
public:
	CFullVideo(char nIndex,QWidget* pParent=0);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseDoubleClickEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
public:
	char m_nIndex;
	QWidget* m_pParent;
	BOOL     m_bFull;
	//QRect m_rcRestore;
	//QWidget* m_pParent;
};
#endif