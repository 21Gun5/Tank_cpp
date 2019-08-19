#pragma once
#include <windows.h>
#include "Func.h"
#include "Map.h"

//提前声明
//include包含：有完整的tank定义，其中有成员对象bullet，相互包含会出错
//class声明：只声明有此类，而没有具体定义，即没牵涉成员对象，没造成相互包含
class CTank;

class CBullet
{
public:
	COORD m_core;			//坐标
	enum  direction m_dir;//方向
	int m_state;			//子弹状态
public:
	CBullet() :m_core{ 0,0 }, m_dir(UP), m_state(不存在){}
	void SetBullet(COORD core, enum direction dir);
	void MoveBullet();	//移动子弹
	void CleanBullet(COORD oldBulCore);	//清理旧子弹
	void IsMyBulMeetOther(CTank tank, CTank * penemytank,CMap &map); //我方子弹碰撞
	void IsEneBulMeetOther(CTank tank, CTank* penemytank,  CMap &map);//敌方子弹碰撞
	void DrawBullet( CTank tank, CMap map);				//打印子弹
};

