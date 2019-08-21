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
	int m_who;				//哪一方的子弹
public:
	CBullet();
	//void SetBullet(COORD core, enum direction dir);
	void SetBullet(CTank tank);
	void MoveBullet();	//移动子弹
	void CleanBullet(COORD oldBulCore);	//清理旧子弹
	//void IsMyBulMeetOther(CTank tank, CTank* pMyTank,CTank * penemytank,CMap &map); //我方子弹碰撞
	//void IsEneBulMeetOther(CTank *pMyTank, CTank* pEnemyTank,  CMap &map);//敌方子弹碰撞
	void IsBulMeetOther(CTank tank, CTank* pMyTank,CTank * penemytank,CMap &map); //我方子弹碰撞

	void DrawBullet( CMap map);				//打印子弹
};

