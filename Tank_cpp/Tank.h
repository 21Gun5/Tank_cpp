#pragma once
#include <windows.h>
#include "Bullet.h"
#include "Map.h"

class CTank
{
public:
	COORD m_core;			//中心点
	COORD m_body[5];		//其他节点
	enum direction m_dir;	//方向
	unsigned m_blood;		//血量
	bool m_isAlive;		//是否存活
	int m_who;			//哪一方
	CBullet m_bullet;
public:
	CTank(COORD core, enum direction dir,int blood,int who) :m_core(core) ,m_body{0},m_dir(dir),m_blood(blood),m_isAlive(true),m_who(who)
	{
		SetTankShape();
	}
	void SetTankShape();								//设置坦克形态
	void CleanTankTail(COORD oldCore, PCOORD oldBody);	//清除旧坦克
	void ManipulateMyTank(CTank * penemytank,CMap map);	//操纵我方坦克
	bool IsMyTankMeetOther(int dir, CTank  *penemytank, CMap map);//阻挡我方坦克
	void ManipulateEneTank(CTank pmytank, CTank * penemytank, CMap map);//操纵敌方坦克
	bool IsEneTankMeetOther(int dir, CTank pmytank, CTank * penemytank , CMap map);//阻挡敌方坦克

	void DrawTank();	//打印坦克
};

int GetLiveEnemyAmount(CTank* penemytank);					  //存活敌军数量