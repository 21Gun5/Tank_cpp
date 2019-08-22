#pragma once
#include <windows.h>
#include <vector>
#include "Bullet.h"
using namespace std;

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
	bool m_isHided;			//是否隐藏（是否能被找、能被打、能开火
	int m_killCount = 0;//杀敌数
	CBullet m_bullet;
	int m_power = 1;
public:
	CTank(COORD core, enum direction dir, int blood, int who,int power=1);
	void SetTankShape();								//设置坦克形态
	void CleanTankTail(COORD oldCore, PCOORD oldBody);	//清除旧坦克
	void ManipulateTank(vector<CTank>& myTank, vector<CTank>& enemyTank, CMap map, CGame& game);
	bool IsTankMeetOther(int dir, vector<CTank>& myTank,vector<CTank> &enemyTank, CMap map);//阻挡我方坦克
	void DrawTank();	//打印坦克
};

//int GetLiveEnemyAmount(vector<CTank>& enemyTank);					  //存活敌军数量