#pragma once
#include <windows.h>
#include "Func.h"

class CTank;
class CMap;

class CBullet
{
public:
	COORD m_core;			//坐标
	enum  direction m_dir;	//方向
	int m_state;			//子弹状态
public:
	CBullet();
	void SetBullet(COORD core, enum direction dir);
	void MoveBullet();	//移动子弹
	void CleanBullet(COORD oldBulCore);	//清理旧子弹
	void IsMyBulMeetOther(CTank tank, CTank * penemytank,CMap &map); //我方子弹碰撞
	void IsEneBulMeetOther(CTank &tank, CTank* penemytank,  CMap &map);//敌方子弹碰撞
	void DrawBullet( CTank tank, CMap map);				//打印子弹
};

