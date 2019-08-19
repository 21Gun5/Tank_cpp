#pragma once


class CBullet
{
public:
	COORD core;			//坐标
	enum  direction dir;//方向
	int state;			//子弹状态
public:
	CBullet() :core{0,0}, dir(UP), state(不存在)
	{
	}
	void MoveBullet(PBULLET pbullet);	//移动子弹
	void CleanBullet(COORD oldBulCore);	//清理旧子弹
	void IsMyBulMeetOther(PBULLET pbullet, PTANK penemytank, PTANK ptank); //我方子弹碰撞
	void IsEneBulMeetOther(PBULLET pbullet, PTANK penemytank, PTANK ptank);//敌方子弹碰撞
};

