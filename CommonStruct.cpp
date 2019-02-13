#include "CommonStruct.h"
tagGpsItem::tagGpsItem()
{
	memset(this,0,sizeof(tagGpsItem));
}
tagGpsItem::tagGpsItem(int Lat,int Lon,int Speed,int Angle)
{
	nLat = Lat;
	nLon = Lon;
	nSpeed = Speed;
	nAngle = Angle;
	lUtcTime = 0;
}
tagGps::tagGps()
{
	memset(this,0,sizeof(tagGps));
}
tagGps::tagGps(int Lat,int Lon,int Speed,int Angle)
{
	nLat = Lat;
	nLon = Lon;
	nSpeed = Speed;
	nAngle = Angle;
}
sctFileInfo::sctFileInfo()
{
	//memset(this,0,sizeof(sctFileInfo));
	iDuration = NOTSETDURATION;
	iCurTime = 0;
}