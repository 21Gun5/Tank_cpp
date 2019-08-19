#pragma once

class CTank;//解决相互包含问题

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

	void IsMyBulMeetOther(CTank tank, CTank * penemytank ); //我方子弹碰撞

	void IsEneBulMeetOther(CTank tank, CTank* penemytank);//敌方子弹碰撞
};

