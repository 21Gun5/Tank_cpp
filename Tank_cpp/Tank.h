#pragma once
#include "Bullet.h"

class CTank
{
public:
	COORD core;			//中心点
	COORD body[5];		//其他节点
	enum direction dir;	//方向
	unsigned blood;		//血量
	bool isAlive;		//是否存活
	int m_who;			//哪一方
	CBullet bullet;
public:
	CTank(COORD cor, enum direction di,int bl,int who) :core(cor) ,body{0},dir(di),blood(bl),isAlive(true),m_who(who)
	{
		SetTankShape();
	}
	void SetTankShape();								  //设置坦克形态

	

	void CleanTankTail(COORD oldCore, PCOORD oldBody);			  //清除旧坦克
	void ManipulateMyTank(CTank * penemytank); //操纵我方坦克
	bool IsMyTankMeetOther(int dir, CTank  *penemytank);//阻挡我方坦克
	void ManipulateEneTank(CTank pmytank, CTank * penemytank);//操纵敌方坦克
	bool IsEneTankMeetOther(int dir, CTank pmytank, CTank * penemytank);//阻挡敌方坦克
};

int GetLiveEnemyAmount(CTank* penemytank);					  //存活敌军数量