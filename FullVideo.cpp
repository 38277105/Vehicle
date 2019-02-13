#include "FullVideo.h"
#include "FramelessDialog.h"
CFullVideo::CFullVideo(char nIndex,QWidget* pParent):QFrame(pParent)
{
	m_nIndex = nIndex;
	m_pParent = pParent;
	m_bFull = FALSE;
	//m_pParent = pParent;
}
void CFullVideo::mousePressEvent(QMouseEvent *pEvent)
{
	/*if(pEvent->button() == Qt::LeftButton && pDialog && ((CFramelessDialog*)pDialog)->m_nCurWndIndex != m_nIndex )
	{
		((CFramelessDialog*)pDialog)->updateCurVideo(m_nIndex);
	}*/

}
void CFullVideo::mouseMoveEvent(QMouseEvent *pEvent)
{
	if (pDialog && !((CFramelessDialog*)pDialog)->m_bMouseDown)
	{
		if (cursor().shape()==Qt::SizeHorCursor)
		{
			QCursor curs(Qt::ArrowCursor);
			setCursor(curs);
		}
	}
}
void CFullVideo::mouseDoubleClickEvent(QMouseEvent *pEvent)
{
    if (!isFullScreen())
    {
		setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
		showFullScreen();
		m_bFull = TRUE;
    } 
    else
    {
		setWindowFlags(Qt::Widget);
		showNormal();
		
		m_bFull = FALSE;
    }
	return;
}