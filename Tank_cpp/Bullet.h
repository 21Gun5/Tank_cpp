#pragma once

#include "Func.h"

class CTank;//解决相互包含问题
class CMap;

class CBullet
{
public:
	COORD core;			//坐标
	enum  direction dir;//方向
	int state;			//子弹状态
public:
	CBullet() :core{ 0,0 }, dir(UP), state(不存在){}
	void SetBullet(COORD cor, enum direction di);
	void MoveBullet();	//移动子弹
	void CleanBullet(COORD oldBulCore);	//清理旧子弹

	void IsMyBulMeetOther(CTank tank, CTank * penemytank,CMap &map); //我方子弹碰撞

	void IsEneBulMeetOther(CTank tank, CTank* penemytank,  CMap &map);//敌方子弹碰撞

	void DrawBullet( CTank tank, CMap map);				//打印子弹
};

