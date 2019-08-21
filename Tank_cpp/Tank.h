#pragma once
#include <windows.h>
#include "Bullet.h"

class CGame;
class CMap;

class CTank
{
public:
	COORD m_core;			//中心点
	COORD m_body[5] = {0};	//其他节点
	enum direction m_dir;	//方向
	unsigned m_blood;		//血量
	bool m_isAlive;			//是否存活
	int m_who;				//哪一方
	CBullet m_bullet;
public:
	CTank(COORD core, enum direction dir, int blood, int who);
	void SetTankShape();								//设置坦克形态
	void CleanTankTail(COORD oldCore, PCOORD oldBody);	//清除旧坦克
	void ManipulateTank(CTank* pMyTank, CTank* pEnemyTank, CMap map, CGame& game);
	bool IsTankMeetOther(int dir, CTank* pMyTank, CTank  *pEnemyTank, CMap map);//阻挡我方坦克
	void DrawTank();	//打印坦克
};

int GetLiveEnemyAmount(CTank* penemytank);					  //存活敌军数量